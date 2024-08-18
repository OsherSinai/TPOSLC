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
#include <include\stddef.h>


enum class Win32Version {
	win10_1507 = 0, // 10240
	win10_1511, // 10586
	win10_1607,
	win10_1703,
	win10_1709,
	win10_1803,
	win10_1809,
	win10_1903,
	win10_1909,
	win10_2004,
	win10_20H2,
	win10_21H1,
	win10_21H2,
	win10_22H2,
	winserv2022_21H2,
	win11_21H2,
	win11_22H2,
	win11_23H2,
	winserv2022_23H2,
	Unknown

};
uint16_t gc_wWin32BuildNumbers[] = {
	10240,
	10586,
	14393,
	15063,
	16299,
	17134,
	17763,
	18362,
	18363,
	19041,
	19042,
	19043,
	19044,
	19045,
	20348,
	22000,
	22621,
	22631,
	25398
};

constexpr uint32_t c_NtQuerySystemInformation = 0x0036;
constexpr uint32_t c_NtAllocateVirtualMemory = 0x0018;
constexpr uint32_t c_NtFreeVirtualMemory = 0x001e;
constexpr uint32_t c_NtProtectVirtualMemory = 0x0050;
constexpr uint32_t c_NtTerminateProcess = 0x002c;
constexpr uint32_t c_NtQueryInformationProcess = 0x0019;
constexpr uint32_t c_NtOpenFile = 0x0033;
constexpr uint32_t c_NtClose = 0x000f;
constexpr uint32_t c_NtCreateFile = 0x0055;
constexpr uint32_t c_NtSetInformationFile = 0x0027;
constexpr uint32_t c_NtQueryInformationFile = 0x0011;
constexpr uint32_t c_NtWriteFile = 0x0008;
constexpr uint32_t c_NtReadFile = 0x0006;
constexpr uint32_t c_NtFlushBuffersFile = 0x004b;
constexpr uint32_t c_NtQueryPerformanceCounter = 0x0031;
constexpr uint32_t c_NtDelayExecution = 0x0034;
constexpr uint32_t c_NtTerminateThread = 0x0053;
constexpr uint32_t c_NtQueryInformationThread = 0x0025;
constexpr uint32_t c_NtDuplicateObject = 0x003c;
constexpr uint32_t c_NtCreateThreadEx[] = { 0x00b3, 0x00b4, 0x00b6, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00bd, 0x00c1, 0x00c1, 0x00c1, 0x00c2, 0x00c2, 0x00c5, 0x00c6, 0x00c7, 0x00c7, 0x00c8 };




static Win32Version GetWindowsVersionByBuildNumber(uint16_t BUildNumber)
{
	int Offset;
	for (Offset = 0;
		Offset < (sizeof(gc_wWin32BuildNumbers) / sizeof(gc_wWin32BuildNumbers[0]));
		Offset++)
	{
		if (BUildNumber == gc_wWin32BuildNumbers[Offset])
			break;
	}
	return (Win32Version)Offset;
}

static Win32Version GetOSVer()
{
	uint16_t Build = 0;
	__asm {
		mov rax, qword ptr gs : [60h]
		mov bx, word ptr[rax + 0120h]
		mov word ptr[Build], bx
	}

	Win32Version Version = GetWindowsVersionByBuildNumber(Build);
	return Version;
}

extern "C" uint32_t g_dwNtQuerySystemInformation = 0;
extern "C" uint32_t g_dwNtAllocateVirtualMemory = 0;
extern "C" uint32_t g_dwNtFreeVirtualMemory = 0;
extern "C" uint32_t g_dwNtProtectVirtualMemory = 0;
extern "C" uint32_t g_dwNtTerminateProcess = 0;
extern "C" uint32_t g_dwNtQueryInformationProcess = 0;
extern "C" uint32_t g_dwNtOpenFile = 0;
extern "C" uint32_t g_dwNtClose = 0;
extern "C" uint32_t g_dwNtCreateFile = 0;
extern "C" uint32_t g_dwNtSetInformationFile = 0;
extern "C" uint32_t g_dwNtQueryInformationFile = 0;
extern "C" uint32_t g_dwNtWriteFile = 0;
extern "C" uint32_t g_dwNtReadFile = 0;
extern "C" uint32_t g_dwNtFlushBuffersFile = 0;
extern "C" uint32_t g_dwNtQueryPerformanceCounter = 0;
extern "C" uint32_t g_dwNtDelayExecution = 0;
extern "C" uint32_t g_dwNtTerminateThread = 0;
extern "C" uint32_t g_dwNtQueryInformationThread = 0;
extern "C" uint32_t g_dwNtDuplicateObject = 0;
extern "C" uint32_t g_dwNtCreateThreadEx = 0;

extern "C" int _tos_InitializeSyscallTable()
{
	int nRet = -1;
	Win32Version ver = GetOSVer();
	if (ver != Win32Version::Unknown)
	{
		 g_dwNtQuerySystemInformation = c_NtQuerySystemInformation;
		 g_dwNtAllocateVirtualMemory = c_NtAllocateVirtualMemory;
		 g_dwNtFreeVirtualMemory = c_NtFreeVirtualMemory;
		 g_dwNtProtectVirtualMemory = c_NtProtectVirtualMemory;
		 g_dwNtTerminateProcess = c_NtTerminateProcess;
		 g_dwNtQueryInformationProcess = c_NtQueryInformationProcess;
		 g_dwNtOpenFile = c_NtOpenFile;
		 g_dwNtClose = c_NtClose;
		 g_dwNtCreateFile = c_NtCreateFile;
		 g_dwNtSetInformationFile = c_NtSetInformationFile;
		 g_dwNtQueryInformationFile = c_NtQueryInformationFile;
		 g_dwNtWriteFile = c_NtWriteFile;
		 g_dwNtReadFile = c_NtReadFile;
		 g_dwNtFlushBuffersFile = c_NtFlushBuffersFile;
		 g_dwNtQueryPerformanceCounter = c_NtQueryPerformanceCounter;
		 g_dwNtDelayExecution = c_NtDelayExecution;
		 g_dwNtTerminateThread = c_NtTerminateThread;
		 g_dwNtQueryInformationThread = c_NtQueryInformationThread;
		 g_dwNtDuplicateObject = c_NtDuplicateObject;
		 g_dwNtCreateThreadEx = c_NtCreateThreadEx[(int)ver];
		nRet = 0;
	}
	return nRet;
}