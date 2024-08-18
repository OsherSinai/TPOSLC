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
#ifndef TOS_STDIO_H
#define TOS_STDIO_H

#include "stdint.h"
#include "stddef.h"
#include "limits.h"
#include "stdarg.h"
typedef struct { void* p; } FILE;

typedef ptrdiff_t fpos_t;
#define EOF (-1)

#define _IOFBF 0x1
#define _IOLBF 0x2
#define _IONBF 0x3

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif 

#define FOPEN_MAX 16
#define FILENAME_MAX 260

/*
* temp file format is 0000000000.tmp to 4294967295.tmp
* so we need 15 bytes including the null terminator
*/
#define L_tmpnam 15

#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0

#define TMP_MAX LONG_MAX

#define stderr ((FILE*)2)
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
LIBC_DEF_BEGIN
	int remove(const char* szFilename);
	int rename(const char* szOld, const char* szNew);

	FILE* tmpfile();
	/*not thread safe*/
	char* tmpnam(char* s);
	int fclose(FILE* stream);
	int fflush(FILE* stream);
	FILE* fopen(const char* restrict szFilename,
		const char* restrict szMode);
	FILE* freopen(const char* restrict filename,
		const char* restrict mode,
		FILE* restrict stream);
	void setbuf(FILE* restrict stream,
		char* restrict buf);
	int setvbuf(FILE* restrict stream,
		char* restrict buf,
		int mode, size_t size);

	int fprintf(FILE* restrict stream,
		const char* restrict format, ...);

	int fscanf(FILE* restrict stream,
		const char* restrict format, ...);

	int printf(const char* restrict format, ...);
	int scanf(const char* restrict format, ...);

	int snprintf(char* restrict s, size_t n,
		const char* restrict format, ...);
	int sprintf(char* restrict s,
		const char* restrict format, ...);
	int sscanf(const char* restrict s,
		const char* restrict format, ...);
	int vfprintf(FILE* restrict stream,
		const char* restrict format,
		va_list arg);

	int vfscanf(FILE* restrict stream,
		const char* restrict format,
		va_list arg);

	int vprintf(const char* restrict format,
		va_list arg);
	int vscanf(const char* restrict format,
		va_list arg);
	int vsnprintf(char* restrict s, size_t n,
		const char* restrict format,
		va_list arg);
	int vsprintf(char* restrict s,
		const char* restrict format,
		va_list arg);
	int vsscanf(const char* restrict s,
		const char* restrict format,
		va_list arg);

	int fgetc(FILE* stream);
	char* fgets(char* restrict s, int n,
		FILE* restrict stream);
	int fputc(int c, FILE* stream);
	int fputs(const char* restrict s,
		FILE* restrict stream);
	int getc(FILE* stream);
	int getchar(void);
	int putc(int c, FILE* stream);
	int putchar(int c);
	int puts(const char* s);
	int ungetc(int c, FILE* stream);
	size_t fread(void* restrict ptr,
		size_t size, size_t nmemb,
		FILE* restrict stream);
	size_t fwrite(const void* restrict ptr,
		size_t size, size_t nmemb,
		FILE* restrict stream);

	int fgetpos(FILE* restrict stream,
		fpos_t* restrict pos);
	int fseek(FILE* stream, long int offset, int whence);
	int fsetpos(FILE* stream, const fpos_t* pos);
	long int ftell(FILE* stream);
	void rewind(FILE* stream);

	void clearerr(FILE* stream);
	int feof(FILE* stream);
	int ferror(FILE* stream);
	void perror(const char* s);

LIBC_DEF_END
#endif // !TOS_STDIO_H
