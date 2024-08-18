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
#include <include/wchar.h>
#include <include/string.h>
#include <include/stdlib.h>
#include "wprintf_utils.h"


int vswprintf(wchar_t* restrict s, size_t n,
	const wchar_t* restrict format, va_list arg)
{
	int nRet = -1;
	size_t wrote = 0;
	sf_convtype ConvType;
	sf_bitwidth BitWidth;
	bool bUpperCase;
	sf_flags Flags;
	const wchar_t* szNow = format;
	const wchar_t* szNext;
	x86_reg_struct reg;
	wchar_t* pTmpBuff = NULL;
	dbl_to_str_state* pState = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	if (pState == NULL)
		goto cleanup;
	pTmpBuff = (wchar_t*)malloc(sizeof(wchar_t) * 4096);
	if (pTmpBuff == NULL)
		goto cleanup;
	if (n)
		n--;
	nRet = 0;

	while (szNow)
	{
		szNext = WideFindNextSpecial(szNow);
		if (!szNext)
		{
			size_t actual_write;
			size_t to_write = wcslen(szNow);
			if (to_write && s)
			{
				actual_write = WideCopyTextWithLimits(s, n, &wrote, szNow, to_write);
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
				actual_write = WideCopyTextWithLimits(s, n, &wrote, szNow, to_write);
				s += actual_write;
			}
			nRet += to_write;
		}

		if (szNext)
		{
			memset(&reg, 0, sizeof(reg));
			memset(pState, 0, sizeof(*pState));
			wmemset(pTmpBuff, 0, 4096);
			szNow = WideParseSpecial(szNext,
				&ConvType,
				&BitWidth,
				&bUpperCase,
				&Flags,
				pTmpBuff
			);
			if (szNow)
			{
				if (Flags.nMinFieldWidth == -1)
					Flags.nMinFieldWidth = va_arg(arg, int);
				if (Flags.nPrecision == -1)
					Flags.nPrecision = va_arg(arg, int);

				if (WideReadVararg(&arg, ConvType, BitWidth, &reg))
				{
					size_t len = WideProcessParameter_vsprintf(
						s, n,
						&wrote,
						ConvType,
						BitWidth,
						bUpperCase,
						&reg,
						&Flags,
						pState,
						pTmpBuff
					);
					if (s)
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
	if (pTmpBuff)
		free(pTmpBuff);
	return nRet;
}

int vfwprintf(FILE* restrict stream,
	const wchar_t* restrict format, va_list arg)
{
	int nRet = -1;
	size_t wrote = 0;
	sf_convtype ConvType;
	sf_bitwidth BitWidth;
	bool bUpperCase;
	sf_flags Flags;
	const wchar_t* szNow = format;
	const wchar_t* szNext;
	x86_reg_struct reg;
	wchar_t* pTmpBuff = NULL;
	dbl_to_str_state* pState = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	if (pState == NULL)
		goto cleanup;
	pTmpBuff = (wchar_t*)malloc(sizeof(wchar_t) * 4096);
	if (pTmpBuff == NULL)
		goto cleanup;

	nRet = 0;

	while (szNow)
	{
		szNext = WideFindNextSpecial(szNow);
		if (!szNext)
		{
			size_t actual_write;
			size_t to_write = wcslen(szNow);
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
			wmemset(pTmpBuff, 0, 4096);
			szNow = WideParseSpecial(szNext,
				&ConvType,
				&BitWidth,
				&bUpperCase,
				&Flags,
				pTmpBuff
			);
			if (szNow)
			{
				if (Flags.nMinFieldWidth == -1)
					Flags.nMinFieldWidth = va_arg(arg, int);
				if (Flags.nPrecision == -1)
					Flags.nPrecision = va_arg(arg, int);

				if (WideReadVararg(&arg, ConvType, BitWidth, &reg))
				{
					int nProcessResult = WideProcessParameter_vfprintf(
						stream,
						&wrote,
						ConvType,
						BitWidth,
						bUpperCase,
						&reg,
						&Flags,
						pState,
						pTmpBuff
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
	if (pTmpBuff)
		free(pTmpBuff);
	return nRet;
}


int fwprintf(FILE* restrict stream,
	const wchar_t* restrict format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int nRet = vfwprintf(stream, format, vlist);

	va_end(vlist);
	return nRet;
}
int swprintf(wchar_t* restrict s, size_t n,
	const wchar_t* restrict format, ...)
{

	va_list vlist;
	va_start(vlist, format);
	int nRet = vswprintf(s, n, format, vlist);

	va_end(vlist);
	return nRet;
}
int vwprintf(const wchar_t* restrict format,
	va_list arg)
{
	return vfwprintf(stdout, format, arg);
}
int wprintf(const wchar_t* restrict format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int nRet = vfwprintf(stdout, format, vlist);
	va_end(vlist);
	return nRet;
}

