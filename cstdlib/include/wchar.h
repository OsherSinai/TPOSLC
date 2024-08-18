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
#ifndef TOS_WCHAR_T
#define TOS_WCHAR_T

#include "stddef.h"
#include "stdarg.h"
#include "uchar.h"
#include "stdio.h"
#ifndef __cplusplus
#ifdef _WIN32
typedef uint16_t wchar_t;
#else
typedef uint32_t wchar_t;
#endif // _WIN32
#endif // !__cplusplus

typedef int64_t wint_t;
#define WEOF ((wint_t)-1)
LIBC_DEF_BEGIN
int fwprintf(FILE* restrict stream,
	const wchar_t* restrict format, ...);
int fwscanf(FILE* restrict stream,
	const wchar_t* restrict format, ...);
int swprintf(wchar_t* restrict s, size_t n,
	const wchar_t* restrict format, ...);
int swscanf(const wchar_t* restrict s,
	const wchar_t* restrict format, ...);
int vfwprintf(FILE* restrict stream,
	const wchar_t* restrict format, va_list arg);
int vfwscanf(FILE* restrict stream,
	const wchar_t* restrict format, va_list arg);
int vswprintf(wchar_t* restrict s, size_t n,
	const wchar_t* restrict format, va_list arg);
int vswscanf(const wchar_t* restrict s,
	const wchar_t* restrict format, va_list arg);
int vwprintf(const wchar_t* restrict format,
	va_list arg);
int vwscanf(const wchar_t* restrict format,
	va_list arg);
int wprintf(const wchar_t* restrict format, ...);
int wscanf(const wchar_t* restrict format, ...);
wint_t fgetwc(FILE* stream);
wchar_t* fgetws(wchar_t* restrict s, int n,
	FILE* restrict stream);
wint_t fputwc(wchar_t c, FILE* stream);
int fputws(const wchar_t* restrict s,
	FILE* restrict stream);
int fwide(FILE* stream, int mode);
wint_t getwc(FILE* stream);
wint_t getwchar(void);
wint_t putwc(wchar_t c, FILE* stream);
wint_t putwchar(wchar_t c);
wint_t ungetwc(wint_t c, FILE* stream);
double wcstod(const wchar_t* restrict nptr,
	wchar_t** restrict endptr);
float wcstof(const wchar_t* restrict nptr,
	wchar_t** restrict endptr);
long double wcstold(const wchar_t* restrict nptr,
	wchar_t** restrict endptr);
long int wcstol(const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);
long long int wcstoll(const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);
unsigned long int wcstoul(const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);
unsigned long long int wcstoull(
	const wchar_t* restrict nptr,
	wchar_t** restrict endptr, int base);

//wcs_string.cpp
wchar_t* wcscpy(wchar_t* restrict s1,
	const wchar_t* restrict s2);
wchar_t* wcsncpy(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n);
wchar_t* wmemcpy(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n);
wchar_t* wmemmove(wchar_t* s1, const wchar_t* s2,
	size_t n);
wchar_t* wcscat(wchar_t* restrict s1,
	const wchar_t* restrict s2);
wchar_t* wcsncat(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n);
int wcscmp(const wchar_t* s1, const wchar_t* s2);
int wcscoll(const wchar_t* s1, const wchar_t* s2);
int wcsncmp(const wchar_t* s1, const wchar_t* s2,
	size_t n);
size_t wcsxfrm(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n);
int wmemcmp(const wchar_t* s1, const wchar_t* s2,
	size_t n);
wchar_t* wcschr(const wchar_t* s, wchar_t c);
size_t wcscspn(const wchar_t* s1, const wchar_t* s2);
wchar_t* wcspbrk(const wchar_t* s1, const wchar_t* s2);
wchar_t* wcsrchr(const wchar_t* s, wchar_t c);
size_t wcsspn(const wchar_t* s1, const wchar_t* s2);
wchar_t* wcsstr(const wchar_t* s1, const wchar_t* s2);
wchar_t* wcstok(wchar_t* restrict s1,
	const wchar_t* restrict s2,
	wchar_t** restrict ptr);
wchar_t* wmemchr(const wchar_t* s, wchar_t c, size_t n);
size_t wcslen(const wchar_t* s);
wchar_t* wmemset(wchar_t* s, wchar_t c, size_t n);

//
size_t wcsftime(wchar_t* restrict s, size_t maxsize,
	const wchar_t* restrict format,
	const struct tm* restrict timeptr);
wint_t btowc(int c);
int wctob(wint_t c);
int mbsinit(const mbstate_t* ps);
size_t mbrlen(const char* restrict s, size_t n,
	mbstate_t* restrict ps);
size_t mbrtowc(wchar_t* restrict pwc,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps);
size_t wcrtomb(char* restrict s, wchar_t wc,
	mbstate_t* restrict ps);
size_t mbsrtowcs(wchar_t* restrict dst,
	const char** restrict src, size_t len,
	mbstate_t* restrict ps);
size_t wcsrtombs(char* restrict dst,
	const wchar_t** restrict src, size_t len,
	mbstate_t* restrict ps);
LIBC_DEF_END
#endif // !TOS_WCHAR_T
