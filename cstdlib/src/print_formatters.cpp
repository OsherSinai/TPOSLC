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
#include "printf_utils.h"
#include "VariableSizeMath.h"
#include <include/stdio.h>
#include <include/stdlib.h>
#include <include/string.h>

//TODO: (printf) this entire implementation is suboptimal, redo it sometime
//TODO: (printf) add proper precision support
/*
% = convert token
flags = zero or more (any order)
optional precision = minimum number of digits after d,i,o,u,x,X or the number of digit after decimal for a,A,e,E,f,F
optional length
conversion specifier
*/

#define SF_FLAG_LEFT_JUSTIFIED '-'
#define SF_FLAG_SIGN_CONV '+'
#define SF_FLAG_ALT_FORM '#'
#define SF_FLAG_PAD '0'
/*
hh - byte 8bit
h - word 16bit
l - long int (32 windows, 64 linux)
ll- long long int (64 bit)
j - intmax_t
z - size_t
t - ptrdiff_t
L - long double
*/
/*
d,i - int
o,u,x,X - unsigned int, (o)ctal, (u)nsigned, he(x) lower or big
f,F - double normal
e,E - double exponent form
g,G - double decimal or decimal exponent
a,A - double hex exponent notation
c - int converted to unsigned char and written as char
s - string
p - void*
n - The argument shall be a pointer to signed integer into which is written the number of
	characters written to the output stream so far by this call to fprintf. No argument is
	converted, but one is consumed. If the conversion specification includes any flags, a field
	width, or a precision, the behavior is undefined.
# - A % character is written. No argument is converted. The complete conversion specification
	shall be %%.
*/

// returns next char after the substitute


extern "C" int vsnprintf(char* restrict s, size_t n,
	const char* restrict format,
	va_list arg)
{
	int nRet = -1;
	size_t wrote = 0;
	sf_convtype ConvType;
	sf_bitwidth BitWidth;
	bool bUpperCase;
	sf_flags Flags;
	const char* szNow = format;
	const char* szNext;
	x86_reg_struct reg;
	dbl_to_str_state* pState = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	if (pState == NULL)
		goto cleanup;

	if(n)
		n--;
	nRet = 0;

	while (szNow)
	{
		szNext = FindNextSpecial(szNow);
		if (!szNext)
		{
			size_t actual_write;
			size_t to_write = strlen(szNow);
			if (to_write && s)
			{
				actual_write = CopyTextWithLimits(s, n, &wrote, szNow, to_write);
				s += actual_write;
			}
			nRet += to_write;
		}
		else
		{
			size_t actual_write;
			size_t to_write = (size_t)szNext - (size_t)szNow;
			if (to_write && s)
			{
				actual_write = CopyTextWithLimits(s, n, &wrote, szNow, to_write);
				s += actual_write;
			}
			nRet += to_write;
		}

		if (szNext)
		{
			memset(&reg, 0, sizeof(reg));
			memset(pState, 0, sizeof(*pState));
			szNow = ParseSpecial(szNext,
				&ConvType,
				&BitWidth,
				&bUpperCase,
				&Flags,
				pState->szBuffer
			);
			if (szNow)
			{
				if (Flags.nMinFieldWidth == -1)
					Flags.nMinFieldWidth = va_arg(arg, int);
				if (Flags.nPrecision == -1)
					Flags.nPrecision = va_arg(arg, int);

				if (ReadVararg(&arg, ConvType, BitWidth, &reg))
				{
					size_t len = ProcessParameter_vsprintf(
						s, n,
						&wrote,
						ConvType,
						BitWidth,
						bUpperCase,
						&reg,
						&Flags,
						pState
					);
					if(s)
						s += len;
					nRet += len;
				}
				else
				{
					szNow = NULL;
					nRet = -1;
				}
			}
		}
		else
			szNow = NULL;
	}

	if (s && nRet != -1)
		*s = '\0';

cleanup:
	if (pState)
		free(pState);
	return nRet;
}

int vfprintf(FILE* restrict stream,
	const char* restrict format,
	va_list arg)
{
	int nRet = -1;
	size_t wrote = 0;
	sf_convtype ConvType;
	sf_bitwidth BitWidth;
	bool bUpperCase;
	sf_flags Flags;
	const char* szNow = format;
	const char* szNext;
	x86_reg_struct reg;
	dbl_to_str_state* pState = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	if (pState == NULL)
		goto cleanup;

	nRet = 0;

	while (szNow)
	{
		szNext = FindNextSpecial(szNow);
		if (!szNext)
		{
			size_t actual_write;
			size_t to_write = strlen(szNow);
			if (to_write)
			{
				actual_write = fwrite(szNow, 1, to_write, stream);
				wrote += actual_write;
			}
			nRet += to_write;
		}
		else
		{
			size_t actual_write;
			size_t to_write = (size_t)szNext - (size_t)szNow;
			if (to_write)
			{
				actual_write = fwrite(szNow, 1, to_write, stream);
				wrote += actual_write;
			}
			nRet += to_write;
		}

		if (szNext)
		{
			memset(&reg, 0, sizeof(reg));
			memset(pState, 0, sizeof(*pState));
			//TODO: recheck all inputs by the standard, currently it wont print %%
			szNow = ParseSpecial(szNext,
				&ConvType,
				&BitWidth,
				&bUpperCase,
				&Flags,
				pState->szBuffer
			);
			if (szNow)
			{
				if (Flags.nMinFieldWidth == -1)
					Flags.nMinFieldWidth = va_arg(arg, int);
				if (Flags.nPrecision == -1)
					Flags.nPrecision = va_arg(arg, int);

				if (ReadVararg(&arg, ConvType, BitWidth, &reg))
				{
					int nProcessResult = ProcessParameter_vfprintf(
						stream,
						&wrote,
						ConvType,
						BitWidth,
						bUpperCase,
						&reg,
						&Flags,
						pState
					);
					if (nProcessResult < 0)
					{
						nRet = -1;
						goto cleanup;
					}
					nRet += nProcessResult;
				}
				else
				{
					szNow = NULL;
					nRet = -1;
				}
			}
		}
		else
			szNow = NULL;
	}

cleanup:
	if (pState)
		free(pState);
	return nRet;
}

extern "C" int snprintf(char* restrict s, size_t n,
	const char* restrict format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int nRet = vsnprintf(s, n, format, vlist);

	va_end(vlist);
	return nRet;
}

extern "C" int vsprintf(char* restrict s,
	const char* restrict format,
	va_list arg)
{
	return vsnprintf(s, ~0, format, arg);
}

extern "C" int sprintf(char* restrict s,
	const char* restrict format, ...)
{

	va_list vlist;
	va_start(vlist, format);
	int nRet = vsprintf(s, format, vlist);

	va_end(vlist);
	return nRet;
}

extern "C" int fprintf(FILE * restrict stream,
	const char* restrict format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int nRet = vfprintf(stream, format, vlist);

	va_end(vlist);
	return nRet;
}

extern "C" int vprintf(const char* restrict format,
	va_list arg)
{
	return vfprintf(stdout, format, arg);
}
extern "C" int printf(const char* restrict format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int nRet = vfprintf(stdout, format, vlist);
	va_end(vlist);
	return nRet;
}