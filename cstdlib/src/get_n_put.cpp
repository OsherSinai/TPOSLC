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
#include <include\stdio.h>
#include <include\string.h>
#include <include\wchar.h>

extern "C" void _tos_FileSetErrorIndication(FILE* stream, int State);

int fgetc(FILE* stream)
{
	int nRet = 0;
	uint8_t u;
	if (feof(stream) == 0 && fwide(stream, 0) == 0)
	{
		size_t ReadSize = fread(&u, 1, 1, stream);
		if (ReadSize != 0)
		{
			if (feof(stream) == 0)
				nRet = u;
			else
				nRet = EOF;
		}
		else
		{
			nRet = EOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = EOF;

	return nRet;
}
int getc(FILE* stream)
{
	int nRet = 0;
	uint8_t u;
	if (feof(stream) == 0 && fwide(stream, 0) == 0)
	{
		size_t ReadSize = fread(&u, 1, 1, stream);
		if (ReadSize != 0)
		{
			if (feof(stream) == 0)
				nRet = u;
			else
				nRet = EOF;
		}
		else
		{
			nRet = EOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = EOF;

	return nRet;
}
char* fgets(char* restrict s, int n,
	FILE* restrict stream)
{
	char* pRet = s;
	if (feof(stream) == 0 && fwide(stream, 0) == 0)
	{
		int TotalSize = 0;
		size_t ReadSize = 0;
		uint8_t ch;
		n--;
		while (TotalSize < n)
		{
			ReadSize = fread(&ch, 1, 1, stream);
			if (ReadSize)
			{
				*s = (char)ch;
				TotalSize++;
				s++;
				if (ch == '\n')
					break;
			}
			else
				break;
		}

		if (TotalSize)
			*s = 0;
		else
			pRet = NULL;
	}
	else
		pRet = NULL;
	if (s)
		*s = '\0';
	return pRet;
}
int fputc(int c, FILE* stream)
{
	int nRet = c;
	if (fwide(stream, 0) == 0)
	{
		size_t wrote = fwrite(&c, 1, 1, stream);
		if (wrote == 0)
		{
			nRet = EOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = EOF;

	return nRet;
}
int putc(int c, FILE* stream)
{
	int nRet = c;
	if (fwide(stream, 0) == 0)
	{
		size_t wrote = fwrite(&c, 1, 1, stream);
		if (wrote == 0)
		{
			nRet = EOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = EOF;
	return nRet;
}
int fputs(const char* restrict s,
	FILE* restrict stream)
{
	int nRet;
	if (fwide(stream, 0) == 0)
	{
		size_t to_write = strlen(s);
		size_t wrote = fwrite(s, 1, to_write, stream);
		nRet = to_write;
		if (wrote != to_write)
			nRet = EOF;
		//else
		//	fwrite("\n", 1, 1, stream);
	}
	else
		nRet = EOF;
	return nRet;
}
int getchar()
{
	return getc(stdin);
}
int putchar(int c)
{
	return putc(c, stdout);
}
int puts(const char* s)
{
	return fputs(s, stdout);
}

wint_t fgetwc(FILE* stream)
{
	wint_t nRet = 0;
	wchar_t u;
	if (feof(stream) == 0 && fwide(stream, 0) == 1)
	{
		size_t ReadSize = fread(&u, sizeof(wchar_t), 1, stream);
		if (ReadSize != 0)
		{
			if (feof(stream) == 0)
				nRet = u;
			else
				nRet = WEOF;
		}
		else
		{
			nRet = WEOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = WEOF;

	return nRet;
}
wchar_t* fgetws(wchar_t* restrict s, int n,
	FILE* restrict stream)
{
	wchar_t* pRet = s;
	if (feof(stream) == 0 && fwide(stream, 0) == 1)
	{
		int TotalSize = 0;
		size_t ReadSize = 0;
		wchar_t ch;
		n--;
		while (TotalSize < n)
		{
			ReadSize = fread(&ch, sizeof(wchar_t), 1, stream);
			if (ReadSize)
			{
				*s = (char)ch;
				TotalSize++;
				s++;
				if (ch == L'\n')
					break;
			}
			else
				break;
		}

		if (TotalSize)
			*s = 0;
		else
			pRet = NULL;
	}
	else
		pRet = NULL;
	if (*s)
		*s = L'\0';
	return pRet;
}
wint_t fputwc(wchar_t c, FILE* stream)
{
	wint_t nRet = c;
	if (fwide(stream, 0) == 1)
	{
		size_t wrote = fwrite(&c, sizeof(wchar_t), 1, stream);
		if (wrote == 0)
		{
			nRet = WEOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = WEOF;

	return nRet;
}
int fputws(const wchar_t* restrict s,
	FILE* restrict stream)
{
	int nRet;
	if (fwide(stream, 0) == 1)
	{
		size_t to_write = wcslen(s);
		size_t wrote = fwrite(s, sizeof(wchar_t), to_write, stream);
		nRet = to_write;
		if (wrote != to_write)
			nRet = WEOF;
	}
	else
		nRet = WEOF;
	return nRet;
}
wint_t getwc(FILE* stream)
{
	wint_t nRet = 0;
	wchar_t u;
	if (feof(stream) == 0 && fwide(stream, 0) == 1)
	{
		size_t ReadSize = fread(&u, sizeof(wchar_t), 1, stream);
		if (ReadSize != 0)
		{
			if (feof(stream) == 0)
				nRet = u;
			else
				nRet = WEOF;
		}
		else
		{
			nRet = WEOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = WEOF;

	return nRet;
}
wint_t getwchar(void)
{
	return getwc(stdin);
}
wint_t putwc(wchar_t c, FILE* stream)
{
	wint_t nRet = c;
	if (fwide(stream, 0) == 1)
	{
		size_t wrote = fwrite(&c, sizeof(wchar_t), 1, stream);
		if (wrote == 0)
		{
			nRet = WEOF;
			_tos_FileSetErrorIndication(stream, 1);
		}
	}
	else
		nRet = WEOF;
	return nRet;
}
wint_t putwchar(wchar_t c)
{
	return putwc(c, stdout);
}