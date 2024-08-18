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
#pragma once
#ifndef TOS_WIN32_MEMORY_H
#define TOS_WIN32_MEMORY_H
#include <include\stdint.h>
#include "win32_base.h"

#define MEM_COMMIT                      0x00001000  
#define MEM_RESERVE                     0x00002000  
#define MEM_RESET                       0x00080000  
#define MEM_LARGE_PAGES                 0x20000000  

#define MEM_DECOMMIT                    0x00004000  
#define MEM_RELEASE                     0x00008000  
#define MEM_FREE                        0x00010000  

#define PAGE_NOACCESS           0x01    
#define PAGE_READONLY           0x02    
#define PAGE_READWRITE          0x04    
#define PAGE_WRITECOPY          0x08    
#define PAGE_EXECUTE            0x10    
#define PAGE_EXECUTE_READ       0x20    
#define PAGE_EXECUTE_READWRITE  0x40    
#define PAGE_EXECUTE_WRITECOPY  0x80    
#define PAGE_GUARD             0x100    
#define PAGE_NOCACHE           0x200    
#define PAGE_WRITECOMBINE      0x400    



WinNtStatus Win32NtAllocateVirtualMemory(
	void** ppAddress, size_t Size, 
	uint32_t dwAllocationType, uint32_t dwProtect, 
	size_t* pActualAllocation);
WinNtStatus Win32NtFreeVirtualMemory(
	void* pAddress, uint64_t Size, uint32_t dwFreeType);
WinNtStatus Win32NtProtectVirtualMemory(
	void* pAddr, uint64_t Size,
	uint32_t NewProtect, uint32_t* pOldProtect);
#endif
