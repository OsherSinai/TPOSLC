/*
	TPOSLC
	A LibC implementation for TPOS (Testing and Prototyping Operating System).

	Copyright © 2024 by Osher Sinai.

	This file is part of TPOSLC (Testing and Prototyping Operating System LibC).

	TPOSLC is free software:
	you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
	either version 3 of the License, or (at your option) any later version.

	TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with TPOSLC.
	If not, see <https://www.gnu.org/licenses/>.
*/
#include <include\stdlib.h>
#include <include\stdio.h>
#include <include\string.h>
#include <include\wchar.h>
#include <include\errno.h>
#ifdef _WIN32
#include "win32/win32_ntdll.h"
#include "win32/win32_file.h"
#endif // _WIN32

#include "lock.h"
#include "LinkedList.h"
#include "FiloQueue.h"

enum class FileMode : uint8_t {
	undef,
	Read,
	Write,
	WriteExclusive,
	Append,
	ReadBinary,
	WriteBinary,
	WriteBinaryExclusive,
	AppendBinary,
	ReadUpdate,
	WriteUpdate,
	WriteUpdateExclusive,
	AppendUpdate,
	ReadUpdateBinary,
	WriteUpdateBinary,
	WriteUpdateBinaryExclusive,
	AppendUpdateBinary
};

union FioFlags {
	struct {
		FileMode Mode : 5;
		uint8_t DeleteOnClose : 1;
		uint8_t buffered: 1;
		uint8_t eof : 1;
		uint8_t error_indicator : 1;
		uint8_t Wide : 1;
		uint8_t BOMType : 1;
	} bitfield;
	uint8_t mem;
};
struct FioInternalJournal {
	TosLinkedListEntry llistent;
	FioFlags Flags;
	size_t Position;
	void* pHandle;
	bool bModeLock;
	char szName[FILENAME_MAX];
	//Added this just in case i'll implement this some day.
	//uint8_t Buffer[BUFSIZ];
	FiloQueue<unsigned char, BUFSIZ> PushbackQueue;
	tos_lock FileLock;
};

// stdin, stdout, stderr, all others
struct FileioGlobalContext {
	FioInternalJournal StdEntries[3];
	tos_lock ListLock;
	TosLinkedList OpenFilesList;
};

static FileioGlobalContext g_FileioGlobalContext;

enum class InternalOpenRet {
	Ok,
	Mode,
	CreateFile,
	Position
};

static HANDLE GetStdFileHandle(uint64_t num)
{
	HANDLE hRet = 0;
	RTL_USER_PROCESS_PARAMETERS* pRtl;
#ifdef _WIN32
	//Windows values
	//constexpr size_t StdInNum = (size_t)-10ll;
	//constexpr size_t StdOutNum = (size_t)-11ll;
	//constexpr size_t StdErrNum = (size_t)-12ll;
	//my values
	constexpr size_t StdInNum = (size_t)0ll;
	constexpr size_t StdOutNum = (size_t)1ll;
	constexpr size_t StdErrNum = (size_t)2ll;
	__asm {
		mov rax, qword ptr gs : [60h]
		mov rax, qword ptr[rax + 20h]
		mov qword ptr[pRtl], rax
	}

	if (num == StdInNum)
	{
		if ((pRtl->WindowFlags & 0x200) == 0)
			hRet = pRtl->StandardInput;
	}
	else if (num == StdOutNum)
	{
		if ((pRtl->WindowFlags & 0x400) == 0)
			hRet = pRtl->StandardOutput;
	}
	else if (num == StdErrNum)
	{
		hRet = pRtl->StandardError;
	}
#endif
	return hRet;
}

void _tos_Initialize_stdio()
{
#ifdef _WIN32
	memset(&g_FileioGlobalContext, 0, sizeof(g_FileioGlobalContext));
	LListInitialize(&g_FileioGlobalContext.OpenFilesList);

	g_FileioGlobalContext.StdEntries[(size_t)stdin].pHandle = GetStdFileHandle((uint64_t)stdin);
	strcpy(g_FileioGlobalContext.StdEntries[(size_t)stdin].szName, "stdin");
	g_FileioGlobalContext.StdEntries[(size_t)stdin].Flags.bitfield.Mode = FileMode::Read;
	InitializeLock(&g_FileioGlobalContext.StdEntries[(size_t)stdin].FileLock);
	g_FileioGlobalContext.StdEntries[(size_t)stdin].PushbackQueue.DelayedInitialize();

	g_FileioGlobalContext.StdEntries[(size_t)stdout].pHandle = GetStdFileHandle((uint64_t)stdout);
	strcpy(g_FileioGlobalContext.StdEntries[(size_t)stdout].szName, "stdout");
	g_FileioGlobalContext.StdEntries[(size_t)stdout].Flags.bitfield.Mode = FileMode::Write;
	InitializeLock(&g_FileioGlobalContext.StdEntries[(size_t)stdout].FileLock);
	g_FileioGlobalContext.StdEntries[(size_t)stdout].PushbackQueue.DelayedInitialize();

	g_FileioGlobalContext.StdEntries[(size_t)stderr].pHandle = GetStdFileHandle((uint64_t)stderr);
	strcpy(g_FileioGlobalContext.StdEntries[(size_t)stderr].szName, "stderr");
	g_FileioGlobalContext.StdEntries[(size_t)stderr].Flags.bitfield.Mode = FileMode::Write;
	InitializeLock(&g_FileioGlobalContext.StdEntries[(size_t)stderr].FileLock);
	g_FileioGlobalContext.StdEntries[(size_t)stderr].PushbackQueue.DelayedInitialize();
#endif // WIN32
}
void _tos_Uninitialize_stdio()
{
	FioInternalJournal* pTmp;
	while (!LListIsEmpty(&g_FileioGlobalContext.OpenFilesList))
	{
		if (g_FileioGlobalContext.OpenFilesList.pStart)
		{
			pTmp = (FioInternalJournal*)g_FileioGlobalContext.OpenFilesList.pStart;
			fclose((FILE*)pTmp);
		}
		else if(g_FileioGlobalContext.OpenFilesList.pEnd)
		{
			pTmp = (FioInternalJournal*)g_FileioGlobalContext.OpenFilesList.pEnd;
			fclose((FILE*)pTmp);
		}
	}
}


static void TranslateFileCreateFlags(FioFlags flags,
	uint64_t* pDesiredAccess,
	uint64_t* pFileAttributes,
	uint64_t* pSharedAccess,
	uint64_t* pCreateDisposition
)
{
	*pDesiredAccess = 0;
	*pSharedAccess = 0;
	*pCreateDisposition = 0;
	/*
		uint8_t read : 1;
		uint8_t write : 1;
		uint8_t append : 1;
		uint8_t trunc : 1;
		uint8_t binary : 1;
		uint8_t exclusive : 1;
		uint8_t buffered: 1;
		uint8_t create : 1;
	*/
#ifdef _WIN32
	*pFileAttributes = FILE_ATTRIBUTE_NORMAL;

	FileMode mode = flags.bitfield.Mode;
	switch (mode)
	{
	case FileMode::Read:
		*pDesiredAccess = FILE_GENERIC_READ;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN;
		break;
	case FileMode::Write:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OVERWRITE_IF;
		break;
	case FileMode::WriteExclusive:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pCreateDisposition = FILE_CREATE;
		break;
	case FileMode::Append:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN_IF;
		break;
	case FileMode::ReadBinary:
		*pDesiredAccess = FILE_GENERIC_READ;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN;
		break;
	case FileMode::WriteBinary:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OVERWRITE_IF;
		break;
	case FileMode::WriteBinaryExclusive:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pCreateDisposition = FILE_CREATE;
		break;
	case FileMode::AppendBinary:
		*pDesiredAccess = FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN_IF;
		break;
	case FileMode::ReadUpdate:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN;
		break;
	case FileMode::WriteUpdate:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OVERWRITE_IF;
		break;
	case FileMode::WriteUpdateExclusive:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pCreateDisposition = FILE_CREATE;
		break;
	case FileMode::AppendUpdate:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN_IF;
		break;
	case FileMode::ReadUpdateBinary:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN;
		break;
	case FileMode::WriteUpdateBinary:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OVERWRITE_IF;
		break;
	case FileMode::WriteUpdateBinaryExclusive:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pCreateDisposition = FILE_CREATE;
		break;
	case FileMode::AppendUpdateBinary:
		*pDesiredAccess = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
		*pSharedAccess = FILE_SHARE_VALID_FLAGS;
		*pCreateDisposition = FILE_OPEN_IF;
		break;
	default:
		break;
	}

#endif // _WIN32


}

static FioFlags translate_fopen_mode(const char* restrict szMode)
{
	FioFlags ret = { .mem = 0 };
	if (strcmp(szMode, "r") == 0)
		ret.bitfield.Mode = FileMode::Read;
	else if (strcmp(szMode, "w") == 0)
		ret.bitfield.Mode = FileMode::Write;
	else if (strcmp(szMode, "wx") == 0)
		ret.bitfield.Mode = FileMode::WriteExclusive;
	else if (strcmp(szMode, "a") == 0)
		ret.bitfield.Mode = FileMode::Append;
	else if (strcmp(szMode, "rb") == 0)
		ret.bitfield.Mode = FileMode::ReadBinary;
	else if (strcmp(szMode, "wb") == 0)
		ret.bitfield.Mode = FileMode::WriteBinary;
	else if (strcmp(szMode, "wbx") == 0)
		ret.bitfield.Mode = FileMode::WriteBinaryExclusive;
	else if (strcmp(szMode, "ab") == 0)
		ret.bitfield.Mode = FileMode::AppendBinary;
	else if (strcmp(szMode, "r+") == 0)
		ret.bitfield.Mode = FileMode::ReadUpdate;
	else if (strcmp(szMode, "w+") == 0)
		ret.bitfield.Mode = FileMode::WriteUpdate;
	else if (strcmp(szMode, "w+x") == 0)
		ret.bitfield.Mode = FileMode::WriteUpdateExclusive;
	else if (strcmp(szMode, "a+") == 0)
		ret.bitfield.Mode = FileMode::AppendUpdate;
	else if ((strcmp(szMode, "r+b") == 0) || (strcmp(szMode, "rb+") == 0))
		ret.bitfield.Mode = FileMode::ReadUpdateBinary;
	else if ((strcmp(szMode, "w+b") == 0) || (strcmp(szMode, "wb+") == 0))
		ret.bitfield.Mode = FileMode::WriteUpdateBinary;
	else if ((strcmp(szMode, "w+bx") == 0) || (strcmp(szMode, "wb+x") == 0))
		ret.bitfield.Mode = FileMode::WriteUpdateBinaryExclusive;
	else if ((strcmp(szMode, "a+b") == 0) || (strcmp(szMode, "ab+") == 0))
		ret.bitfield.Mode = FileMode::AppendUpdateBinary;
	return ret;
}

static InternalOpenRet InternalOpen(const char* restrict szFilename,
	const char* restrict szMode,
	bool bDeleteOnClose,
	FioInternalJournal* pJournal)
{
	InternalOpenRet Ret = InternalOpenRet::Ok;
	void* pHandle = NULL;
	FioFlags flags = translate_fopen_mode(szMode);
	uint64_t DesiredAccess;
	uint64_t FileAttributes;
	uint64_t SharedAccess;
	uint64_t CreateDisposition;
#ifdef _WIN32
	WinNtStatus stat;
	uint64_t CreateOptions = FILE_SYNCHRONOUS_IO_NONALERT;
#endif
	if (flags.mem == 0)
	{
		Ret = InternalOpenRet::Mode;
		goto cleanup;
	}

	TranslateFileCreateFlags(flags, &DesiredAccess, &FileAttributes, &SharedAccess, &CreateDisposition);


#ifdef _WIN32
	stat = Win32NtCreateFile(&pHandle, szFilename, DesiredAccess, FileAttributes, SharedAccess, CreateDisposition, CreateOptions);
	if (stat != WinNtStatus::Success)
	{
		Ret = InternalOpenRet::CreateFile;
		goto cleanup;
	}

	if (flags.bitfield.Mode == FileMode::Append ||
		flags.bitfield.Mode == FileMode::AppendBinary ||
		flags.bitfield.Mode == FileMode::AppendUpdate ||
		flags.bitfield.Mode == FileMode::AppendUpdateBinary)
	{
		stat = Win32NtSetFilePosition(pHandle, 0, MovePositionMethod::End);
		if (stat != WinNtStatus::Success)
		{
			Ret = InternalOpenRet::Position;
			goto cleanup;
		}
	}
#endif // _WIN32

	//memset(pJournal->Buffer, 0, BUFSIZ);
	memset(pJournal->szName, 0, FILENAME_MAX);
	strcpy(pJournal->szName, szFilename);
	InitializeLock(&pJournal->FileLock);
	pJournal->Position = 0;
	pJournal->Flags = flags;
	pJournal->Flags.bitfield.DeleteOnClose = bDeleteOnClose ? 1 : 0;
	pJournal->pHandle = pHandle;
	pHandle = 0;
cleanup:
#ifdef _WIN32
	if (pHandle)
		Win32NtClose(pHandle);
#endif // _WIN32
	return Ret;
}


static int InternalClose(FioInternalJournal* stream)
{
	int nRet = -1;
#ifdef _WIN32
	//if (stream->Position)
	//{
	//	uint32_t buffsize = stream->Position;
	//	Win32NtWriteFile(stream->pHandle, stream->Buffer, &buffsize);
	//}
	WinNtStatus stat = Win32NtClose(stream->pHandle);
	if (stat == WinNtStatus::Success)
		nRet = 0;
#endif // _WIN32
	return nRet;
}


int remove(const char* szFilename)
{
	int nRet = 0;
#ifdef _WIN32
	HANDLE handle = { 0 };
	WinNtStatus stat = Win32NtOpenFile(
		&handle,
		szFilename,
		FILE_READ_ATTRIBUTES | DELETE,
		FILE_SHARE_VALID_FLAGS,
		FILE_DELETE_ON_CLOSE
	);
	if (stat == WinNtStatus::Success)
		Win32NtClose(handle);
	else
		nRet = -1;

#else
#endif // _WIN32
	return nRet;
}

int rename(const char* szOld, const char* szNew)
{
	int nRet = 0;
#ifdef _WIN32

	HANDLE Source = { 0 };
	HANDLE Destination = { 0 };

	WinNtStatus stat = Win32NtCreateFile(
		&Source,
		szOld,
		FILE_GENERIC_READ | FILE_GENERIC_WRITE,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_VALID_FLAGS,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT
	);
	if (stat == WinNtStatus::Success)
	{
		stat = Win32NtCreateFile(
			&Destination,
			szNew,
			FILE_GENERIC_READ | FILE_GENERIC_WRITE,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_VALID_FLAGS,
			FILE_OVERWRITE_IF,
			FILE_SYNCHRONOUS_IO_NONALERT
		);
		if (stat == WinNtStatus::Success)
		{
			uint32_t ChunkSize = 512;
			uint8_t Chunk[512];
			while (1)
			{
				stat = Win32NtReadFile(Source, Chunk, &ChunkSize);
				if (stat != WinNtStatus::Success)
				{
					if (stat != WinNtStatus::EndOfFile)
						nRet = -1;
					break;
				}
				if (!ChunkSize)
					break;
				if (Win32NtWriteFile(Destination, Chunk, &ChunkSize) != WinNtStatus::Success)
				{
					break;
				}
			}


			Win32NtClose(Destination);
		}
		else
		{
			nRet = -1;
		}

		Win32NtClose(Source);
		if (nRet == 0)
		{
			remove(szOld);
		}
	}
	else
	{
		nRet = -1;
	}
#else
#endif // _WIN32
	return nRet;
}

union tmpn_totalstr {
	struct {
		uint64_t low;
		uint32_t mid;
		uint16_t high;
		uint8_t zero;
	};
	char str[15];
};

static void IncrementTmpnInternal(char* s)
{
	constexpr tmpn_totalstr mx = { .str = "4294967295.tmp" };
	tmpn_totalstr* p = (tmpn_totalstr*)s;
	if (
		p->low == mx.low &&
		p->mid == mx.mid &&
		p->high == mx.high
		)
	{
		p->low = 0x3030303030303030;
		p->mid = 0x742e3030;
		p->high = 0x706d;
	}
	else
	{
		for (int i = 9; i >= 0; i--)
		{
			s[i]++;
			if (s[i] > '9')
				s[i] = '0';
			else
				break;
		}
	}
}
char* tmpnam(char* s)
{
	static char internal_state[L_tmpnam] = "4294967295.tmp";
	static tos_lock tl = 0;
	uint64_t itrctr = 0;
	char* pRet = s;
	bool bSuccess = false;

	if (pRet == NULL)
		pRet = internal_state;

	AquireLock(&tl);
	while (itrctr < ULONG_MAX)
	{
		IncrementTmpnInternal(internal_state);
		FILE* pf = fopen(internal_state, "r");
		if (pf == NULL)
		{
			if (pRet != internal_state)
				strcpy(pRet, internal_state);
			bSuccess = true;
			break;
		}
		else
			fclose(pf);
		itrctr++;
	}
	FreeLock(&tl);
	if (!bSuccess)
		pRet = NULL;
	return pRet;
}

FILE* tmpfile()
{
	FioInternalJournal* pFile = NULL;
	char tname[L_tmpnam];
	if (tmpnam(tname))
	{

		pFile = (FioInternalJournal*)malloc(sizeof(FioInternalJournal));
		if (pFile)
		{
			InternalOpenRet IOR = InternalOpen(tname, "wb+", true, pFile);
			if (IOR != InternalOpenRet::Ok)
			{
				free(pFile);
				pFile = 0;
			}
			else
			{
				AquireLock(&g_FileioGlobalContext.ListLock);
				LListInsertAtEnd(&g_FileioGlobalContext.OpenFilesList, &pFile->llistent);
				FreeLock(&g_FileioGlobalContext.ListLock);
			}
		}
	}
	return (FILE*)pFile;
}







FILE* fopen(const char* restrict szFilename,
	const char* restrict szMode)
{
	FioInternalJournal* pFile = NULL;

	pFile = (FioInternalJournal*)malloc(sizeof(FioInternalJournal));
	if (pFile)
	{
		InitializeLock(&pFile->FileLock);
		pFile->PushbackQueue.DelayedInitialize();
		InternalOpenRet IOR = InternalOpen(szFilename, szMode, false, pFile);
		if (IOR != InternalOpenRet::Ok)
		{
			free(pFile);
			pFile = 0;
		}
		else
		{
			AquireLock(&g_FileioGlobalContext.ListLock);
			LListInsertAtEnd(&g_FileioGlobalContext.OpenFilesList, &pFile->llistent);
			FreeLock(&g_FileioGlobalContext.ListLock);
		}
	}
	return (FILE*)pFile;
}

int fclose(FILE* stream)
{
	int nRet = -1;
	if (stream)
	{
		FioInternalJournal* pfij = (FioInternalJournal*)stream;

		AquireLock(&g_FileioGlobalContext.ListLock);
		LListRemoveEntry(&g_FileioGlobalContext.OpenFilesList, &pfij->llistent);
		FreeLock(&g_FileioGlobalContext.ListLock);

		nRet = InternalClose(pfij);
		if (pfij->Flags.bitfield.DeleteOnClose)
		{
			remove(pfij->szName);
		}
		free(pfij);
	}
	return nRet;
}
int fflush(FILE* stream)
{
	int nRet = EOF;
	if (stream)
	{
		FioInternalJournal* pfij = (FioInternalJournal*)stream;
		AquireLock(&pfij->FileLock);
		pfij->bModeLock = true;
#ifdef _WIN32
		//if (pfij->Position)
		//{
		//	uint32_t buffsize = pfij->Position;
		//	Win32NtWriteFile(pfij->pHandle, pfij->Buffer, &buffsize);
		//	pfij->Position = 0;
		//}
		WinNtStatus stat = Win32FlushBuffer(pfij->pHandle);
		if (stat == WinNtStatus::Success)
			nRet = 0;
#endif // _WIN32
		if (nRet == -1)
			pfij->Flags.bitfield.error_indicator = 1;
		FreeLock(&pfij->FileLock);
	}
	
	return nRet;
}

bool _tos_IsStdStream(FILE* stream)
{
	return stream <= stderr;
}
FILE* freopen(const char* restrict filename,
	const char* restrict mode,
	FILE* restrict stream)
{
	FioInternalJournal* pfij = (FioInternalJournal*)stream;
	char szFileName[FILENAME_MAX] = { 0 };
	
	InternalClose(pfij);

	if (filename)
		strcpy(szFileName, filename);
	else
		strcpy(szFileName, pfij->szName);

	InternalOpenRet IOR = InternalOpen(szFileName, mode, pfij->Flags.bitfield.DeleteOnClose, pfij);
	if (IOR != InternalOpenRet::Ok)
	{
		free(pfij);
		pfij = 0;
	}

	return (FILE*)pfij;
}

size_t fread(void* restrict ptr,
	size_t size, size_t nmemb,
	FILE* restrict stream)
{
	size_t Ret = 0;
	uint32_t Size = size * nmemb;
	FioInternalJournal* pfij;
	uint8_t* pOffset = (uint8_t*)ptr;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;

	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
	while (Size && pfij->PushbackQueue.CountInQueue())
	{
		*pOffset = pfij->PushbackQueue.Pop();
		pOffset++;
		Size -= 1;
		Ret++;
	}
#ifdef _WIN32
	if (Size)
	{
		auto ntret = Win32NtReadFile(pfij->pHandle, pOffset, &Size);
		if (ntret == WinNtStatus::Success)
		{
			Ret += (size_t)Size;
		}
		else if (ntret == WinNtStatus::EndOfFile)
		{
			pfij->Flags.bitfield.eof = 1;
		}
	}
#else
#error Not Implemented (filectrl.cpp)
#endif // _WIN32
	FreeLock(&pfij->FileLock);
	return Ret;
}

extern "C" void _tos_FileSetErrorIndication(FILE* stream, int State)
{
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->Flags.bitfield.error_indicator = State;
	FreeLock(&pfij->FileLock);
}

size_t fwrite(const void* restrict ptr,
	size_t size, size_t nmemb,
	FILE* restrict stream)
{
	size_t Ret = 0;
	uint32_t Size = size * nmemb;
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
#ifdef _WIN32
	auto ntret = Win32NtWriteFile(pfij->pHandle, (void*)ptr, &Size);
	if (ntret == WinNtStatus::Success)
	{
		Ret = (size_t)Size / size;
	}
#else
#error Not Implemented (filectrl.cpp)
#endif // _WIN32
	FreeLock(&pfij->FileLock);
	return Ret;
}

void clearerr(FILE* stream)
{
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
	pfij->Flags.bitfield.eof = 0;
	pfij->Flags.bitfield.error_indicator = 0;
	FreeLock(&pfij->FileLock);
}
int feof(FILE* stream)
{
	int nRet;
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
	nRet = pfij->Flags.bitfield.eof;
	FreeLock(&pfij->FileLock);
	return nRet;
}
int ferror(FILE* stream)
{
	int nRet;
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
	nRet = pfij->Flags.bitfield.error_indicator;
	FreeLock(&pfij->FileLock);
	return nRet;
}

int ungetc(int c, FILE* stream)
{
	int nRet;
	FioInternalJournal* pfij;
	unsigned char ch;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	if (pfij->Flags.bitfield.Wide == 0)
	{
		pfij->bModeLock = true;
		if (!pfij->PushbackQueue.IsFull())
		{
			ch = (unsigned char)(c & 0xFF);
			pfij->PushbackQueue.Push(ch);
			nRet = ch;
		}
		else
		{
			nRet = EOF;
		}
	}
	else
	{
		nRet = EOF;
	}
	FreeLock(&pfij->FileLock);
	return nRet;
}
wint_t ungetwc(wint_t c, FILE* stream)
{
	wint_t nRet;
	FioInternalJournal* pfij;
	unsigned char ch;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	if (pfij->Flags.bitfield.Wide == 1)
	{
		pfij->bModeLock = true;
		if (!pfij->PushbackQueue.IsFull())
		{
			if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
			{
				ch = (unsigned char)((c >> 8) & 0xFF);
				pfij->PushbackQueue.Push(ch);
				ch = (unsigned char)(c & 0xFF);
				pfij->PushbackQueue.Push(ch);
			}
			else
			{
				ch = (unsigned char)((c >> 24) & 0xFF);
				pfij->PushbackQueue.Push(ch);
				ch = (unsigned char)((c >> 16) & 0xFF);
				pfij->PushbackQueue.Push(ch);
				ch = (unsigned char)((c >> 8) & 0xFF);
				pfij->PushbackQueue.Push(ch);
				ch = (unsigned char)(c & 0xFF);
				pfij->PushbackQueue.Push(ch);
			}
			nRet = ch;
		}
		else
		{
			nRet = WEOF;
		}
	}
	else
	{
		nRet = WEOF;
	}
	FreeLock(&pfij->FileLock);
	return nRet;
}

void perror(const char* s)
{
	const char* szError = strerror(0);
	if (s)
	{
		fwrite(s, 1, strlen(s), stderr);
		fwrite(": ", 1, 2, stderr);
	}
	fwrite(szError, 1, strlen(szError), stderr);
}


int fgetpos(FILE* restrict stream,
	fpos_t* restrict pos)
{
	int nRet = -1;
	FioInternalJournal* pfij;
	int64_t BasePos;
	errno = 0;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
#ifdef _WIN32
	WinNtStatus wnts = Win32GetFilePosition(pfij->pHandle, &BasePos);
	if (wnts == WinNtStatus::Success)
	{
		nRet = 0;
		if (pos)
			*pos = BasePos;
	}
#else
#error fgetpos unimplemented (filectrl.cpp)
#endif // _WIN32
	FreeLock(&pfij->FileLock);
	if (nRet != 0)
		errno = EIO;
	return nRet;
}

int fseek(FILE* stream, long int offset, int whence)
{
	int nRet = -1;
	FioInternalJournal* pfij;
	bool bCorrectWhench = true;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->bModeLock = true;
	pfij->PushbackQueue.Clear();
#ifdef _WIN32
	MovePositionMethod SeekType;
	switch (whence)
	{
	case SEEK_SET:
		SeekType = MovePositionMethod::Begin;
		break;
	case SEEK_END:
		SeekType = MovePositionMethod::End;
		break;
	case SEEK_CUR:
		SeekType = MovePositionMethod::Curr;
		break;
	default:
		bCorrectWhench = false;
		break;
	}
	if (bCorrectWhench)
	{
		WinNtStatus wnts = Win32NtSetFilePosition(
			pfij->pHandle, offset, SeekType);
		if (wnts == WinNtStatus::Success)
		{
			nRet = 0;
		}
		else if (wnts != WinNtStatus::EndOfFile)
		{
			pfij->Flags.bitfield.error_indicator = 1;
		}
	}
#else
#error fgetpos unimplemented (filectrl.cpp)
#endif // _WIN32
	FreeLock(&pfij->FileLock);
	return nRet;
}

int fsetpos(FILE* stream, const fpos_t* pos)
{
	int nRet = -1;
	FioInternalJournal* pfij;
	errno = 0;
	if (pos)
	{
		if (_tos_IsStdStream(stream))
			pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
		else
			pfij = (FioInternalJournal*)stream;
		AquireLock(&pfij->FileLock);
		pfij->bModeLock = true;
		pfij->PushbackQueue.Clear();
#ifdef _WIN32
		WinNtStatus wnts = Win32NtSetFilePosition(
			pfij->pHandle, *pos, MovePositionMethod::Begin);
		if (wnts == WinNtStatus::Success)
		{
			nRet = 0;
		}
		else
		{
			pfij->Flags.bitfield.error_indicator = 1;
		}
#else
#error fgetpos unimplemented (filectrl.cpp)
#endif // _WIN32
		FreeLock(&pfij->FileLock);
	}
	if (nRet != 0)
		errno = EIO;
	return nRet;
}

long int ftell(FILE* stream)
{
	long int ret = -1;
	fpos_t fp = 0;
	if (fgetpos(stream, &fp) == 0)
		ret = fp;
	if(ret != 0)
		errno = EIO;
	return ret;
}

void rewind(FILE* stream)
{
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
	pfij->Flags.bitfield.error_indicator = 0;
	pfij->bModeLock = true;
	pfij->PushbackQueue.Clear();
#ifdef _WIN32
	Win32NtSetFilePosition(pfij->pHandle, 0, MovePositionMethod::Begin);
#else
#error rewind unimplemented (filectrl.cpp)
#endif // _WIN32
	FreeLock(&pfij->FileLock);
}


void setbuf(FILE* restrict stream,
	char* restrict buf)
{
	int nMode = buf ? _IOFBF : _IONBF;
	setvbuf(stream, buf, nMode, BUFSIZ);
}

int setvbuf(FILE* restrict stream,
	char* restrict buf,
	int mode, size_t size)
{
	int nRet = -1;
	FioInternalJournal* pfij;
	
	if ((mode != _IOFBF) && (mode != _IOLBF) && (mode != _IONBF))
	{
		nRet = -1;
		goto cleanup;
	}

	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;

	AquireLock(&pfij->FileLock);
	if (pfij->bModeLock == false)
	{
		/*
			As per the description of the function:
			"If buf is not a null pointer, the array it points to may
			be used instead of a buffer allocated by the setvbuf function ..."
			May is the key word here, the actual buffer wont be changed.
		*/

		if (mode == _IOFBF)
		{
			pfij->Flags.bitfield.buffered = 1;
		}
		else if (mode == _IOLBF)
		{
			pfij->Flags.bitfield.buffered = 1;
		}
		else
		{
			//_IONBF
			pfij->Flags.bitfield.buffered = 0;
		}

		nRet = 0;
	}
	FreeLock(&pfij->FileLock);
cleanup:
	return nRet;
}

int fwide(FILE* stream, int mode)
{
	int nRet = 0;
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);

	if (mode != 0 && !pfij->bModeLock)
	{
		pfij->Flags.bitfield.Wide = mode > 0 ? 1 : 0;
	}
	nRet = pfij->Flags.bitfield.Wide;
	FreeLock(&pfij->FileLock);
	return nRet;
}

extern "C" void _tos_stdio_AquireLock(FILE* stream)
{
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	AquireLock(&pfij->FileLock);
}
extern "C" void _tos_stdio_FreeLock(FILE* stream)
{
	FioInternalJournal* pfij;
	if (_tos_IsStdStream(stream))
		pfij = &g_FileioGlobalContext.StdEntries[(size_t)stream];
	else
		pfij = (FioInternalJournal*)stream;
	FreeLock(&pfij->FileLock);
}