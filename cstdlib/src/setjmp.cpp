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
#include <include\setjmp.h>

extern "C" int setjmp(jmp_buf env)
{
#ifdef _WIN32
	__asm {
		mov         qword ptr[rcx], rdx
		mov         qword ptr[rcx + 8], rbx
#ifndef NDEBUG
		lea         rax, [rsp + 16]
#else
		lea         rax, [rsp + 8]
#endif // !NDEBUG
		mov         qword ptr[rcx + 10h], rax
		mov         qword ptr[rcx + 18h], rbp
		mov         qword ptr[rcx + 20h], rsi
		mov         qword ptr[rcx + 28h], rdi
		mov         qword ptr[rcx + 30h], r12
		mov         qword ptr[rcx + 38h], r13
		mov         qword ptr[rcx + 40h], r14
		mov         qword ptr[rcx + 48h], r15
#ifndef NDEBUG
		mov         rax, qword ptr[rsp + 8]
#else
		mov         rax, qword ptr[rsp + 0]
#endif // !NDEBUG

		mov         qword ptr[rcx + 50h], rax
		stmxcsr     dword ptr[rcx + 58h]
		fnstcw      word ptr[rcx + 5Ch]
		MOVDQU      xmmword ptr[rcx + 60h], xmm6
		MOVDQU      xmmword ptr[rcx + 70h], xmm7
		MOVDQU      xmmword ptr[rcx + 80h], xmm8
		MOVDQU      xmmword ptr[rcx + 90h], xmm9
		MOVDQU      xmmword ptr[rcx + 0A0h], xmm10
		MOVDQU      xmmword ptr[rcx + 0B0h], xmm11
		MOVDQU      xmmword ptr[rcx + 0C0h], xmm12
		MOVDQU      xmmword ptr[rcx + 0D0h], xmm13
		MOVDQU      xmmword ptr[rcx + 0E0h], xmm14
		MOVDQU      xmmword ptr[rcx + 0F0h], xmm15
	}
#else
	_asm {

	}
#endif // _WIN32
	return 0;
}

extern "C" _Noreturn void longjmp(jmp_buf env, int val)
{
#ifdef _WIN32
	//jmp_state_x86_64_msft* p = (jmp_state_x86_64_msft*)env;
	__asm {
		xor			eax, eax
		mov			rax, val
		mov         rdx, qword ptr[rcx]
		mov         rbx, qword ptr[rcx + 8]
		mov         rbp, qword ptr[rcx + 18h]
		mov         rsi, qword ptr[rcx + 20h]
		mov         rdi, qword ptr[rcx + 28h]
		mov         r12, qword ptr[rcx + 30h]
		mov         r13, qword ptr[rcx + 38h]
		mov         r14, qword ptr[rcx + 40h]
		mov         r15, qword ptr[rcx + 48h]

		ldmxcsr     dword ptr[rcx + 58h]
		FLDCW      word ptr[rcx + 5Ch]

		MOVDQU      xmm6, xmmword ptr[rcx + 60h]
		MOVDQU      xmm7, xmmword ptr[rcx + 70h]
		MOVDQU      xmm8, xmmword ptr[rcx + 80h]
		MOVDQU      xmm9, xmmword ptr[rcx + 90h]
		MOVDQU      xmm10, xmmword ptr[rcx + 0A0h]
		MOVDQU      xmm11, xmmword ptr[rcx + 0B0h]
		MOVDQU      xmm12, xmmword ptr[rcx + 0C0h]
		MOVDQU      xmm13, xmmword ptr[rcx + 0D0h]
		MOVDQU      xmm14, xmmword ptr[rcx + 0E0h]
		MOVDQU      xmm15, xmmword ptr[rcx + 0F0h]

		mov         rsp, qword ptr[rcx + 10h]
		mov         rcx, qword ptr[rcx + 50h]

		jmp			rcx
	}
#else
	_asm {

	}
#endif // _WIN32
}