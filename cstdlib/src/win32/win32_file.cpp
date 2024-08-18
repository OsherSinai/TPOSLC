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
#include "win32_file.h"
#include "win32_ntdll.h"
#include <include\string.h>
#include <include\stdlib.h>

extern WinNtStatus NtstatToWinNtStatus(NTSTATUS stat);


const wchar_t* GetCurrentDirectory()
{
	wchar_t* Ret = 0;
	RTL_USER_PROCESS_PARAMETERS* pRtl;
	__asm {
		mov rax, qword ptr gs : [60h]
		mov rax, qword ptr[rax + 20h]
		mov qword ptr[pRtl], rax
	}
	if (pRtl)
	{
		Ret = pRtl->CurrentDirectory.DosPath.Buffer;
	}

	return Ret;
}

static size_t ntdll_wcslen(const wchar_t* p)
{
	size_t ret = 0;
	while (*p != 0)
	{
		p++;
		ret++;
	} 
	return ret;
}
static wchar_t* ntdll_wcsconcat(wchar_t* pD, const wchar_t* pS)
{
	wchar_t* ret = pD;
	while (*pS != 0)
	{
		*ret = *pS;
		pS++;
		ret++;
	}
	*ret = *pS;
	return ret;
}

static wchar_t* ntdll_ascii_to_wcs(wchar_t* pD, const char* pStr)
{
	wchar_t* ret = pD;
	
	while (*pStr)
	{
		*(uint8_t*)ret = *pStr;
		if (*(uint8_t*)ret == '/')
			*(uint8_t*)ret = '\\';
		*((uint8_t*)ret + 1) = 0;
		ret++;
		pStr++;
	}
	*ret = 0;
	return ret;

}

static bool GenerateUnicodeRelPath(const char* szFileName, UNICODE_STRING* pString)
{
	bool bRet = false;
	const wchar_t* pCurrentDir = GetCurrentDirectory();
	bool bConcatFullPath = false;
	size_t TotalSize;
	wchar_t* pitr;
	if (!szFileName)
		goto cleanup;
	
	TotalSize = strlen(szFileName) + 5;
	if (szFileName[1] != ':')
	{
		bConcatFullPath = true;
		TotalSize += ntdll_wcslen(pCurrentDir);
	}

	pString->MaximumLength = TotalSize * 2;
	if (pString->MaximumLength & 0xF)
		pString->MaximumLength = (pString->MaximumLength & ~0xFLLU) + 16;
	pString->Length = (TotalSize * 2) - 2;
	pString->Buffer = (wchar_t*)aligned_alloc(16, pString->MaximumLength);
	if (!pString->Buffer)
		goto cleanup;


	pitr = ntdll_wcsconcat(pString->Buffer, L"\\??\\");
	if (bConcatFullPath)
	{
		pitr = ntdll_wcsconcat(pitr, pCurrentDir);
		pitr = ntdll_ascii_to_wcs(pitr, szFileName);
	}
	else
	{
		pitr = ntdll_ascii_to_wcs(pitr, szFileName);

	}
	
	bRet = true;
cleanup:
	return bRet;
}
static void DestroyUnicodeString(UNICODE_STRING* pString)
{
	free(pString->Buffer);
}

WinNtStatus Win32NtOpenFile(
	HANDLE* ppHandle,
	const char* szFileName,
	uint64_t DesiredAccess,
	uint64_t SharedAccess,
	uint64_t OpenOption
)
{
	OBJECT_ATTRIBUTES ObjAtr = {0};
	IO_STATUS_BLOCK IoBlock = { {0} };
	UNICODE_STRING us = {0};
	ObjAtr.Length = sizeof(ObjAtr);
	ObjAtr.RootDirectory = NULL;
	ObjAtr.ObjectName = &us;
	ObjAtr.Attributes = OBJ_CASE_INSENSITIVE;
	ObjAtr.SecurityDescriptor = NULL;
	ObjAtr.SecurityQualityOfService = NULL;
	
	NTSTATUS nStat = STATUS_NO_MEMORY;
	if (GenerateUnicodeRelPath(szFileName, ObjAtr.ObjectName))
	{
		nStat = SyscallNtOpenFile(
			ppHandle, 
			DesiredAccess,
			&ObjAtr,
			&IoBlock,
			SharedAccess,
			OpenOption);
		DestroyUnicodeString(ObjAtr.ObjectName);
	}

	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32NtClose(
	HANDLE pHandle
)
{
	NTSTATUS nStat = SyscallNtClose(pHandle);
	return NtstatToWinNtStatus(nStat);

}

WinNtStatus Win32NtCreateFile(
	HANDLE* ppHandle,
	const char* szFileName,
	uint64_t DesiredAccess,
	uint64_t FileAttributes,
	uint64_t SharedAccess,
	uint64_t CreateDisposition,
	uint64_t CreateOptions
)
{
	OBJECT_ATTRIBUTES ObjAtr;
	IO_STATUS_BLOCK IoBlock = { {0} };
	UNICODE_STRING us;
	memset(&ObjAtr, 0, sizeof(ObjAtr));
	memset(&us, 0, sizeof(us));
	ObjAtr.Length = sizeof(ObjAtr);
	ObjAtr.RootDirectory = NULL;
	ObjAtr.ObjectName = &us;
	ObjAtr.Attributes = OBJ_CASE_INSENSITIVE;
	ObjAtr.SecurityDescriptor = NULL;
	ObjAtr.SecurityQualityOfService = NULL;

	NTSTATUS nStat = STATUS_NO_MEMORY;
	if (GenerateUnicodeRelPath(szFileName, ObjAtr.ObjectName))
	{
		nStat = SyscallNtCreateFile(
			ppHandle,
			DesiredAccess,
			&ObjAtr,
			&IoBlock,
			0,
			FileAttributes,
			SharedAccess,
			CreateDisposition,
			CreateOptions,
			0,
			0);
		DestroyUnicodeString(ObjAtr.ObjectName);
	}

	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32GetFilePosition(
	HANDLE hFile,
	int64_t* pFilePosition
)
{
	NTSTATUS nStat = STATUS_SUCCESS;
	IO_STATUS_BLOCK IoBlock = { {0} };
	int64_t ActualPosition = 0;

	nStat = SyscallNtQueryInformationFile(
		hFile,
		&IoBlock,
		&ActualPosition,
		sizeof(ActualPosition),
		FILE_INFORMATION_CLASS::FilePositionInformation
	);
	if (nStat == STATUS_SUCCESS)
		*pFilePosition = ActualPosition;
	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32NtSetFilePosition(
	HANDLE hFile, 
	int64_t FilePosition, 
	MovePositionMethod MoveMethod)
{
	NTSTATUS nStat = STATUS_SUCCESS;
	IO_STATUS_BLOCK IoBlock = { {0} };
	int64_t ActualPosition = 0;


	FILE_STANDARD_INFORMATION fsi;
	nStat = SyscallNtQueryInformationFile(
		hFile,
		&IoBlock,
		&fsi,
		sizeof(fsi),
		FILE_INFORMATION_CLASS::FileStandardInformation
	);
	if (nStat == STATUS_SUCCESS)
	{
		if (MoveMethod <= MovePositionMethod::End)
		{
			if (MoveMethod == MovePositionMethod::Begin)
			{
				ActualPosition = (int64_t)llabs(FilePosition);
			}
			else
			{
				if (MoveMethod == MovePositionMethod::Curr)
				{
					nStat = SyscallNtQueryInformationFile(
						hFile,
						&IoBlock,
						&ActualPosition,
						sizeof(ActualPosition),
						FILE_INFORMATION_CLASS::FilePositionInformation
					);
					if (nStat == STATUS_SUCCESS)
					{
						ActualPosition += FilePosition;
					}
				}
				else
				{
					ActualPosition = fsi.EndOfFile;
				}

				ActualPosition += FilePosition;
				if (ActualPosition < 0)
					ActualPosition = 0;
			}

			if (nStat == STATUS_SUCCESS)
			{
				if (ActualPosition > fsi.EndOfFile)
					ActualPosition = fsi.EndOfFile;

				nStat = SyscallNtSetInformationFile(
					hFile,
					&IoBlock,
					&ActualPosition,
					sizeof(ActualPosition),
					FILE_INFORMATION_CLASS::FilePositionInformation
				);
			}
		}
		else
			nStat = STATUS_INVALID_PARAMETER;
	}

	
	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32NtWriteFile(HANDLE hFile, const void* pBuffer, uint32_t* pdwSize)
{
	NTSTATUS nStat;
	IO_STATUS_BLOCK IoBlock = { {0} };
	nStat = SyscallNtWriteFile(hFile,
		0, 0, 0,
		&IoBlock,
		pBuffer, *pdwSize,
		0, 0);
	*pdwSize = (uint32_t)IoBlock.Information;
	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32NtReadFile(HANDLE hFile, void* pBuffer, uint32_t* pdwSize)
{
	NTSTATUS nStat;
	IO_STATUS_BLOCK IoBlock = { {0} };
	nStat = SyscallNtReadFile(hFile,
		0, 0, 0,
		&IoBlock,
		pBuffer, *pdwSize,
		0, 0);
	*pdwSize = (uint32_t)IoBlock.Information;
	return NtstatToWinNtStatus(nStat);
}

WinNtStatus Win32FlushBuffer(HANDLE hFile)
{
	IO_STATUS_BLOCK IoBlock = { {0} };
	NTSTATUS nStat = SyscallNtFlushBuffersFile(hFile, &IoBlock);
	return NtstatToWinNtStatus(nStat);
}
