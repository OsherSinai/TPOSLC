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
#ifndef VARIABLE_SIZE_MATH_H
#define VARIABLE_SIZE_MATH_H
#include <include\stddef.h>

//Since im using clang I can just use __int128
LIBC_DEF_BEGIN
uint64_t VariSizeDiv64(uint64_t* pBuffer, uint64_t Divisor, uint64_t ChunkCount);
void VariSizeMult64(uint64_t* pBuffer, uint64_t Multi, uint64_t ChunkCount);
void VariSizeAdd64(uint64_t* pBuffer, uint64_t* pAdd, uint64_t ChunkCount);
void VariSizeSub64(uint64_t* pBuffer, uint64_t* pSub, uint64_t ChunkCount);
bool VariSizeBiggerEq(uint64_t* pBuffer, uint64_t* pRef, uint64_t ChunkCount);
LIBC_DEF_END
#endif // !VARIABLE_SIZE_MATH_H
