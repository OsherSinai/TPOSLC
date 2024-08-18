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
#ifdef _WIN32
#include <include\stddef.h>
#include "win32_memory.h"
#include "win32_ntdll.h"
/*
* NtAllocateVirtualMemory 0x18
* NtFreeVirtualMemory 0x1e
* NtProtectVirtualMemory 0x50
* NtQueryVirtualMemory 0x23
*/

/*
* windows calling convention on x64 is 
* 1st - rcx
* 2nd - rdx
* 3rd - r8
* 4rd - r9
* 5th - stack rsp+20h
* 6th - stack rsp+28h
* ...
*/

extern WinNtStatus NtstatToWinNtStatus(NTSTATUS stat);

WinNtStatus Win32NtAllocateVirtualMemory(void** ppAddress, size_t Size, uint32_t dwAllocationType, uint32_t dwProtect, size_t* pActualAllocation)
{
	size_t AA = Size;
	NTSTATUS ntStat = SyscallNtAllocateVirtualMemory(
		~0,
		ppAddress,
		0,
		&AA,
		dwAllocationType,
		dwProtect
	);
	if (pActualAllocation)
		*pActualAllocation = AA;

	return NtstatToWinNtStatus(ntStat);
}

WinNtStatus Win32NtFreeVirtualMemory(void* pAddress, uint64_t Size, uint32_t dwFreeType)
{
	void* ipAddress = pAddress;
	uint64_t iSize = Size;
	NTSTATUS Stat = SyscallNtFreeVirtualMemory(~0, &ipAddress, &iSize, dwFreeType);
	if (Stat == STATUS_INVALID_PAGE_PROTECTION)
	{
		// Ignore this, im not creating reactos 2.0
	}
	return NtstatToWinNtStatus(Stat);
}

WinNtStatus Win32NtProtectVirtualMemory(
	void* pAddr, uint64_t Size,
	uint32_t NewProtect, uint32_t* pOldProtect)
{
	void* ipAddr = pAddr;
	uint64_t iSize = Size;
	NTSTATUS Stat = SyscallNtProtectVirtualMemory(~0, &ipAddr, &iSize, NewProtect, pOldProtect);
	if (Stat == STATUS_INVALID_PAGE_PROTECTION)
	{
		// Ignore this, im not creating reactos 2.0
	}
	return NtstatToWinNtStatus(Stat);
}
/*
long Win32NtQueryVirtualMemory()
{

}
*/
#endif // _WIN32