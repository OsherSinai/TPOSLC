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
#ifndef TOS_STRING_H
#define TOS_STRING_H

#include "stddef.h"

LIBC_DEF_BEGIN
void* memcpy(
	void* restrict s1,
	const void* restrict s2,
	size_t n);

void* memmove(void* s1, const void* s2, size_t n);

char* strcpy(
	char* restrict s1,
	const char* restrict s2
);

char* strncpy(
	char* restrict s1,
	const char* restrict s2,
	size_t n
);

char* strcat(
	char* restrict s1,
	const char* restrict s2
);

char* strncat(
	char* restrict s1,
	const char* restrict s2,
	size_t n
);
size_t strxfrm(char* restrict s1,
	const char* restrict s2,
	size_t n);

int memcmp(const void* s1, const void* s2, size_t b);
int strcmp(const char* s1, const char* s2);
int strcoll(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);

void* memchr(const void* s, int c, size_t n);
char* strchr(const char* s, int c);
size_t strcspn(const char* s1, const char* s2);
char* strpbrk(const char* s1, const char* s2);
char* strrchr(const char* s, int c);
size_t strspn(const char* s1, const char* s2);
char* strstr(const char* s1, const char* s2);

char* strtok(char* restrict s1,
	const char* restrict seq);

void* memset(void* s, int c, size_t n);
char* strerror(int errnum);
size_t strlen(const char* s);

LIBC_DEF_END
#endif // !TOS_STRING_H
