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
#include "lock.h"

extern "C" void InitializeLock(tos_lock * pLock)
{
	*pLock = 0;
}

extern "C" int TryAquireLock(tos_lock* pLock)
{
	int ret;
	__asm {
		mov rcx, qword ptr[pLock];
		xor eax, eax
		xor edx, edx
		inc edx
		lock cmpxchg dword ptr[rcx], edx
		neg eax
		mov dword ptr[ret], eax
	}
	return ret;
}

extern "C" void AquireLock(volatile tos_lock* pLock)
{
	//TODO: add signal for deadlock
	__asm {
		mov rcx, qword ptr[pLock];
		xor edx, edx
			inc edx
			jmp AquireLock_loop_start
			AquireLock_loop :
		pause
			AquireLock_loop_start :
		lock xchg edx, dword ptr[rcx]
			test edx, edx
			jnz AquireLock_loop
	}
}
extern "C" int FreeLock(volatile  tos_lock* pLock)
{
	int nRet;
	__asm {
		mov rcx, qword ptr[pLock];
		xor edx, edx
			lock xchg edx, dword ptr[rcx]
			mov dword ptr[nRet], edx
	}
	return nRet;
}


extern "C" void InitializeLock64(tos_lock64* pLock)
{
	*pLock = 0;
}
extern "C" uint64_t TryAquireLock64(tos_lock64* pLock, uint64_t val)
{
	uint64_t ret;
	__asm {
		xor eax, eax
		mov rdx, qword ptr [val]
		lock cmpxchg qword ptr[rcx], rdx
		mov qword ptr[ret], rax
	}
	return ret;
}
extern "C" void AquireLock64(tos_lock64* pLock, uint64_t val)
{
	//TODO: add signal for deadlock
	//TODO: add sleap on nth iteration
	__asm {
		xor eax, eax
		mov rdx, qword ptr[val]
		jmp AquireLock_loop_start
		AquireLock_loop :
	pause
		AquireLock_loop_start :
	lock cmpxchg qword ptr[rcx], rdx
		test rax, rax
		jnz AquireLock_loop
	}
}
extern "C" void FreeLock64(tos_lock64* pLock, uint64_t val)
{
	__asm {
		mov rax, qword ptr [val]
		xor edx, edx
		lock cmpxchg dword ptr[rcx], edx
	}
}