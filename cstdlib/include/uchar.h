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
//https://datatracker.ietf.org/doc/html/rfc3629 utf-8
//https://datatracker.ietf.org/doc/html/rfc2781 utf-16
//https://datatracker.ietf.org/doc/html/rfc5198 utf-32
#ifndef TOS_UCHAR_H
#define TOS_UCHAR_H
#include "stddef.h"

#ifndef __cplusplus
typedef uint_least8_t char8_t
typedef uint_least16_t char16_t
typedef uint_least32_t char32_t
#endif // !__cplusplus

typedef struct _mbstate_t {
	uint8_t ReadSize;
	uint8_t Pending;
	uint8_t Bytes[4];
	uint32_t utf32;
}mbstate_t;

LIBC_DEF_BEGIN
size_t mbrtoc16(char16_t* restrict pc16,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps);
size_t c16rtomb(char* restrict s, char16_t c16,
	mbstate_t* restrict ps);
size_t mbrtoc32(char32_t* restrict pc32,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps);
size_t c32rtomb(char* restrict s, char32_t c32,
	mbstate_t* restrict ps);
LIBC_DEF_END
#endif // !TOS_UCHAR_H