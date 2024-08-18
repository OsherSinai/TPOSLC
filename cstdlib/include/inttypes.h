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
#ifndef TOS_INT_TYPES_H
#define TOS_INT_TYPES_H

#include "stddef.h"


typedef struct _imaxdiv_t {
	intmax_t rem;
	intmax_t quot;
} imaxdiv_t;

LIBC_DEF_BEGIN
intmax_t imaxabs(intmax_t j);
imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);

intmax_t strtoimax(const char* restrict nptr,
	char** restrict endptr, int base);
uintmax_t strtoumax(const char* restrict nptr,
	char** restrict endptr, int base);

intmax_t wcstoimax(const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);
uintmax_t wcstoumax(const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);
LIBC_DEF_END
#endif // !TOS_INT_TYPES_H
