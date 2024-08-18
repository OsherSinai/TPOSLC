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
#include "VariableSizeMath.h"
#include <include\limits.h>



uint64_t VariSizeDiv64(uint64_t* pBuffer, uint64_t Divisor, uint64_t ChunkCount)
{
	uint64_t ret;
	__asm {
		mov r9, qword ptr[pBuffer]
		mov rcx, qword ptr[Divisor]
		mov r8, qword ptr[ChunkCount]
		xor edx, edx
		dec r8

		loop :
		lea rbx, [r9 + r8 * 8]
			mov rax, qword ptr[rbx]
			div rcx
			mov qword ptr[rbx], rax
			dec r8
			cmp r8, 0
			jge loop
			mov qword ptr[ret], rdx
	}
	return ret;
}

void VariSizeMult64(uint64_t* pBuffer, uint64_t Multi, uint64_t ChunkCount)
{
	__asm {
		mov rbx, qword ptr[pBuffer]
		mov rcx, qword ptr[Multi]
		mov r8, qword ptr[ChunkCount]
		dec r8
		xor r10, r10
		xor r12, r12
		inc r12
		loop :
		mov rax, qword ptr[rbx]
			mul rcx

			xor r11, r11
			add rax, r10
			cmovc r11, r12
			add rdx, r11

			mov r10, rdx
			mov qword ptr[rbx], rax

			lea rbx, [rbx + 8]
			dec r8
			cmp r8, 0
			jge loop
	}
}

void VariSizeAdd64(uint64_t* pBuffer, uint64_t* pAdd, uint64_t ChunkCount)
{
	int64_t ChunkAlias = ChunkCount;
	uint64_t Overflow1 = 0;
	uint64_t Overflow2 = 0;
	uint64_t tmp1;
	uint64_t tmp2;
	while (ChunkAlias > 0)
	{
		tmp1 = *pBuffer;
		tmp2 = *pAdd;
		Overflow2 = 0;

		if (tmp2 > ULLONG_MAX - tmp1)
			Overflow2++;

		tmp1 += tmp2;
		if (Overflow1 > ULLONG_MAX - tmp1)
			Overflow2++;

		tmp1 += Overflow1;
		*pBuffer = tmp1;
		Overflow1 = Overflow2;
		pBuffer++;
		pAdd++;
		ChunkAlias--;
	}
}

void VariSizeSub64(uint64_t* pBuffer, uint64_t* pSub, uint64_t ChunkCount)
{
	int64_t ChunkAlias = ChunkCount;
	uint64_t Underflow1 = 0;
	uint64_t Underflow2 = 0;
	uint64_t tmp1;
	uint64_t tmp2;
	while (ChunkAlias > 0)
	{
		tmp1 = *pBuffer;
		tmp2 = *pSub;
		Underflow2 = 0;

		if (tmp1 < (tmp1 - tmp2))
			Underflow2++;

		tmp1 -= tmp2;
		if (tmp1 < (tmp1 - Underflow1))
			Underflow2++;

		tmp1 -= Underflow1;
		*pBuffer = tmp1;
		Underflow1 = Underflow2;
		pBuffer++;
		pSub++;
		ChunkAlias--;
	}
}
bool VariSizeBiggerEq(uint64_t* pBuffer, uint64_t* pRef, uint64_t ChunkCount)
{
	bool bRet = true;
	for (int64_t i = ChunkCount - 1; (i >= 0) && (bRet == true); i--)
		bRet = pBuffer[i] >= pRef[i];
	return bRet;
}