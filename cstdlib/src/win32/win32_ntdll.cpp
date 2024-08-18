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
#include "win32_ntdll.h"

WinNtStatus NtstatToWinNtStatus(NTSTATUS stat)
{
	WinNtStatus ret = WinNtStatus::Unknown;
	switch (stat)
	{

	case STATUS_SUCCESS: ret = WinNtStatus::Success; break;
	case STATUS_INVALID_HANDLE: ret = WinNtStatus::InvalidHandle; break;
	case STATUS_NO_MEMORY: ret = WinNtStatus::NoMemory; break;
	case STATUS_CONFLICTING_ADDRESSES: ret = WinNtStatus::ConflictingAddress; break;
	case STATUS_ALREADY_COMMITTED: ret = WinNtStatus::AlreadyCommitted; break;
	case STATUS_ACCESS_DENIED: ret = WinNtStatus::AccessDenied; break;
	case STATUS_OBJECT_TYPE_MISMATCH: ret = WinNtStatus::ObjectTypeMismatch; break;
	case STATUS_INVALID_PAGE_PROTECTION: ret = WinNtStatus::InvalidPageProtection; break;
	case STATUS_INSUFFICIENT_RESOURCES: ret = WinNtStatus::InsufficientResources; break;
	case STATUS_PROCESS_IS_TERMINATING: ret = WinNtStatus::ProcessIsTerminating; break;
	case STATUS_COMMITMENT_LIMIT: ret = WinNtStatus::CommitmentLimit; break;
	case STATUS_HANDLE_NOT_CLOSABLE: ret = WinNtStatus::HandleNotCloseable; break;
	case STATUS_INVALID_PARAMETER: ret = WinNtStatus::InvalidHandle; break;
	case STATUS_OBJECT_PATH_SYNTAX_BAD: ret = WinNtStatus::PathSyntaxBad; break;
	case STATUS_OBJECT_NAME_INVALID: ret = WinNtStatus::ObjectNameInvalid; break;
	case STATUS_END_OF_FILE: ret = WinNtStatus::EndOfFile; break;
	default:
		break;
	}
	return ret;
}

NTSTATUS RtlInitUnicodeStringEx(UNICODE_STRING* pDest, wchar_t* pSrc)
{
	NTSTATUS Ret = 0;
	uint32_t Len = 0; 
	pDest->Length = 0;
	pDest->MaximumLength = 0;
	pDest->Buffer = pSrc;
	if (pSrc)
	{
		while (*pSrc != L'\0')
		{
			Len++;
			pSrc++;
		}
		if (Len < 0x7FFF) [[likely]]
		{
			pDest->Length = Len*2;
			pDest->MaximumLength = pDest->Length + sizeof(wchar_t);
		}
		else [[unlikely]]
		{
			Ret = STATUS_NAME_TOO_LONG;
		}
	}
	return Ret;
}

NTSTATUS RtlDosPathNameToNtPathName_U_WithStatus(
	wchar_t* DosFileName,
	PUNICODE_STRING NtFileName,
	PWSTR* FilePart,
	PVOID Reserved
)
{
	return 0;
}


HANDLE GetCurrentProcess()
{
	return (HANDLE)~0llu;
}

uint64_t GetCurrentProcessId(HANDLE hProcess)
{
	uint64_t Ret = 0;
	PROCESS_BASIC_INFORMATION v = { 0 };
	NTSTATUS ntStat = SyscallNtQueryInformationProcess(hProcess,
		PROCESSINFOCLASS::ProcessBasicInformation,
		&v,
		sizeof(v),
		0);
	if (ntStat == STATUS_SUCCESS)
		Ret = v.UniqueProcessId;
	return Ret;
}

void GetSystemTimeAsFileTime(FILETIME* pTime)
{
	//windows magic, because why not
	//probably different in every version of windows
	//cant test it due to only having win10, build 19045
	//blame microsoft due to the value being hardcoded in KernelBase.dll
	uint64_t Systime = *(uint64_t*)0x7FFE0014; 
	pTime->dwLowDateTime = (uint32_t)Systime;
	pTime->dwHighDateTime = (uint32_t)(Systime >> 32);
}

uint32_t GetTickCount()
{
	//sigh... see comment of GetSystemTimeAsFileTime
	uint64_t Systick1 = *(uint64_t*)0x7FFE0320;
	uint64_t Systick2 = (uint64_t)(*(uint32_t*)0x7FFE0004);
	uint64_t ret = Systick2 * Systick1;
	ret = ret >> 24;
	return ret;
}

extern "C" bool RtlQueryPerformanceFrequency(LARGE_INTEGER * pFrequency)
{
	pFrequency->QWord = *(uint64_t*)0x7ffe0300;
	return 1;
}
struct THREAD_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	void* TebBaseAddress;
	CLIENT_ID ClientId;
	uint64_t AffinityMask;
	uint32_t Priority;
	uint32_t BasePriority;
};

uint64_t GetThreadId(HANDLE hThread)
{
	uint64_t tid = ~0;
	THREAD_BASIC_INFORMATION ThreadInfo;
	NTSTATUS nStat = SyscallNtQueryInformationThread(hThread, ThreadBasicInformation, &ThreadInfo, sizeof(ThreadInfo), 0);
	if (nStat == 0)
		tid = (uint64_t)ThreadInfo.ClientId.UniqueThread;
	return tid;
}


static HANDLE GetStdFileHandle(uint64_t num)
{
	HANDLE hRet = 0;
	RTL_USER_PROCESS_PARAMETERS* pRtl;
	//Windows values
	constexpr size_t StdInNum = (size_t)-10ll;
	constexpr size_t StdOutNum = (size_t)-11ll;
	constexpr size_t StdErrNum = (size_t)-12ll;
	//my values
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

	return hRet;
}


BOOL DuplicateHandle(
	HANDLE hSourceProcessHandle, 
	HANDLE hSourceHandle, 
	HANDLE hTargetProcessHandle, 
	HANDLE* lpTargetHandle, 
	DWORD dwDesiredAccess, 
	BOOL bInheritHandle, 
	DWORD dwOptions)
{
	NTSTATUS ntStat;
	HANDLE htmp = GetStdFileHandle((uint64_t)hSourceHandle);
	if (htmp)
		hSourceHandle = htmp;

	ntStat = SyscallNtDuplicateObject(
		hSourceProcessHandle,
		hSourceHandle,
		hTargetProcessHandle,
		lpTargetHandle,
		dwDesiredAccess,
		-(uint32_t)(bInheritHandle != 0) & 2,
		dwOptions
	);

	return (BOOL)(ntStat >= 0);
}

uint64_t* GetThreadLocalStoragePointer()
{
	uint64_t* pRet;
	__asm {
		mov rax, gs:[58h]
		mov qword ptr[pRet], rax
	}
	return pRet;
}
