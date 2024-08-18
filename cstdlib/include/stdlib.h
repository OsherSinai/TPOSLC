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
#ifndef TOS_STDLIB_H
#define TOS_STDLIB_H
#include "stddef.h"

typedef struct {
	int q;
	int rem;
}div_t;
typedef struct {
	int q;
	int rem;
}ldiv_t;
typedef struct {
	long long q;
	long long rem;
}lldiv_t;

#define TOS_NS_PAGE_SIZE 4096

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX ((int)(~0))
#define MB_CUR_MAX ((size_t)4)

LIBC_DEF_BEGIN
//atoi.c
int atoi(const char* nptr);
long int atol(const char* nptr);
long long int atoll(const char* nptr);
double atof(const char* nptr);

double strtod(const char* restrict nptr,
	char** restrict endptr);
float strtof(const char* restrict nptr,
	char** restrict endptr);
long double strtold(const char* restrict nptr,
	char** restrict endptr);

long int strtol(
	const char* restrict nptr,
	char** restrict endptr,
	int base);
long long int strtoll(
	const char* restrict nptr,
	char** restrict endptr,
	int base);
unsigned long int strtoul(
	const char* restrict nptr,
	char** restrict endptr,
	int base);
unsigned long long int strtoull(
	const char* restrict nptr,
	char** restrict endptr,
	int base);

//rand.c
int rand(void);
void srand(unsigned int seed);

//memman.cpp
void* aligned_alloc(size_t alignment, size_t size);
void* calloc(size_t nmemb, size_t size);
void free(void* ptr);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);

//progcontrol.c
_Noreturn void abort(void);
int atexit(void (*func)(void));
int at_quick_exit(void (*func)(void));
_Noreturn void exit(int status);
_Noreturn void _Exit(int status);
char* getenv(const char* name);
_Noreturn void quick_exit(int status);
int system(const char* string);


//sort.c
void* bsearch(const void* key, const void* base,
	size_t nmemb, size_t size,
	int (*compar)(const void*, const void*));
void qsort(void* base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*));


//stdlib_arith.c
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);

//multibyte.c
int mblen(const char* s, size_t n);
int mbtowc(wchar_t* restrict pwc,
	const char* restrict s,
	size_t n);
int wctomb(char* s, wchar_t wc);
size_t mbstowcs(wchar_t* restrict pwcs,
	const char* restrict s,
	size_t n);
size_t wcstombs(char* restrict s,
	const wchar_t* restrict pwcs,
	size_t n);

LIBC_DEF_END
#endif // !TOS_STDLIB_H