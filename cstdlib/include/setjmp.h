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
#ifndef TOS_SETJMP_H
#define TOS_SETJMP_H
#include "stdint.h"
#ifdef _WIN32
typedef struct _jmp_state_x86_64_msft {
	uint64_t rdx;
	uint64_t rbx;
	uint64_t rsp;
	uint64_t rbp;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t r12;
	uint64_t r13;
	uint64_t r14;
	uint64_t r15;
	uint64_t rip;
	uint32_t mxcsr;
	uint16_t fpcsr;
	uint16_t spare;

	uint64_t XMM6[2];
	uint64_t XMM7[2];
	uint64_t XMM8[2];
	uint64_t XMM9[2];
	uint64_t XMM10[2];
	uint64_t XMM11[2];
	uint64_t XMM12[2];
	uint64_t XMM13[2];
	uint64_t XMM14[2];
	uint64_t XMM15[2];
}jmp_state_x86_64_msft;
typedef uint64_t jmp_buf[sizeof(jmp_state_x86_64_msft)/8];
#else

#endif // _WIN32

//typedef uint64_t jmp_buf[32];
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


int setjmp(jmp_buf env);
_Noreturn void longjmp(jmp_buf env, int val);

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // !TOS_SETJMP_H
