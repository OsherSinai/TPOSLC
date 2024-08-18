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
#include <include\uchar.h>
#include "utf_conv.h"

#define UTF16_MASK (0xFC00)
#define UTF16_WORD1_IDENT (0xD800)
#define UTF16_WORD2_IDENT (0xDC00)

#define UTF16_DWORD1_LIMIT_START UTF16_WORD1_IDENT
#define UTF16_DWORD1_LIMIT_END (0xDBFF)
#define UTF16_DWORD2_LIMIT_START UTF16_WORD2_IDENT
#define UTF16_DWORD2_LIMIT_END (0xDFFF)

static inline uint8_t SizeOfUTF16SymbolEncode(uint32_t dwSym)
{
	uint8_t ret = 1;
	if (dwSym >= 0x10000)
		ret++;
	return ret;
}

static inline bool IsUTF16DWord1Value(uint16_t word)
{
	return (UTF16_DWORD1_LIMIT_START <= word) && (word <= UTF16_DWORD1_LIMIT_END);
}
static inline bool IsUTF16DWord2Value(uint16_t word)
{
	return (UTF16_DWORD2_LIMIT_START <= word) && (word <= UTF16_DWORD2_LIMIT_END);
}

_tos_UTFValidationResult _tos_UTF16_ValidateEncodedArray(uint16_t* pArr, size_t ArrLen, uint8_t* pLen)
{
	_tos_UTFValidationResult Ret = UTFValidationResult_null;
	if (!IsUTF16DWord1Value(pArr[0]))
	{
		if (pArr[0] != u'\0')
		{
			Ret = UTFValidationResult_success;
			*pLen = 2;
		}
		else
			Ret = UTFValidationResult_null;
	}
	else
	{
		if (ArrLen > 1)
		{
			if (IsUTF16DWord2Value(pArr[1]))
			{
				Ret = UTFValidationResult_success;
				*pLen = 4;
			}
			else
				Ret = UTFValidationResult_encoding_error;
		}
		else
			Ret = UTFValidationResult_incomplete;
	}

	return Ret;
}

uint8_t _tos_UTF16_DecodeSymbol(uint16_t* pArr, utf_conv_ctx* pCtx)
{
	uint8_t ret;
	pCtx->buf = 0;
	if (IsUTF16DWord1Value(pArr[0]))
	{
		if (IsUTF16DWord2Value(pArr[1]))
		{
			pCtx->buf = (pArr[0] & 0x3FF) << 10;
			pCtx->buf |= pArr[1] & 0x3FF;
			pCtx->buf += 0x10000;
			ret = 2;
		}
		else
			ret = 0;
	}
	else
	{
		pCtx->buf = *pArr;
		ret = 1;
	}

	return ret;
}
uint8_t _tos_UTF16_EncodeSymbol(uint32_t dwSym, utf_conv_ctx* pCtx)
{
	uint8_t ret = SizeOfUTF16SymbolEncode(dwSym);
	pCtx->buf = 0;
	if (ret == 1)
	{
		pCtx->wArr[0] = dwSym;
	}
	else
	{
		dwSym -= 0x10000;
		pCtx->wArr[0] = UTF16_WORD1_IDENT | ((dwSym >> 10) & 0x3FF);
		pCtx->wArr[1] = UTF16_WORD2_IDENT | (dwSym & 0x3FF);
	}

	return ret;
}