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
#define UTF_8_HEADER_1BYTE_MASK (0x80)
#define UTF_8_HEADER_2BYTE_MASK (0xE0)
#define UTF_8_HEADER_3BYTE_MASK (0xF0)
#define UTF_8_HEADER_4BYTE_MASK (0xF8)

#define UTF_8_HEADER_1BYTE_IDENT (0x00)
#define UTF_8_HEADER_2BYTE_IDENT (0xC0)
#define UTF_8_HEADER_3BYTE_IDENT (0xE0)
#define UTF_8_HEADER_4BYTE_IDENT (0xF0)

#define UTF_8_BYTE_MASK (0xC0)
#define UTF_8_BYTE_IDENT (0x80)

#define UTF_8_INVALID_NUMBER_1 (0xC0)
#define UTF_8_INVALID_NUMBER_2 (0xC1)
#define UTF_8_INVALID_NUMBER_3 (0xF5)
#define UTF_8_INVALID_NUMBER_4 (0xFF)
#define UTF_8_BOM (0xFEFF)

#define UTF_8_MAX_VALUE (0x10FFFF)
#define UTF_8_UNUSED_RANGE_START (0xD800)
#define UTF_8_UNUSED_RANGE_END (0xDFFF)



static inline uint8_t UTF8_IsInvalidByte(uint8_t Byte)
{
	uint8_t ret = 0;
	if ((Byte == UTF_8_INVALID_NUMBER_1) ||
		(Byte == UTF_8_INVALID_NUMBER_2) ||
		(Byte == UTF_8_INVALID_NUMBER_3) ||
		(Byte == UTF_8_INVALID_NUMBER_4))
		ret = -1;
	return ret;
}

static inline uint8_t UTF8_GetDecodeSymbolSize(uint8_t Byte)
{
	uint8_t ret = UTF8_IsInvalidByte(Byte);
	if (ret == 0)
	{
		if ((Byte & UTF_8_HEADER_1BYTE_MASK) == UTF_8_HEADER_1BYTE_IDENT)
			ret = 1;
		else if ((Byte & UTF_8_HEADER_2BYTE_MASK) == UTF_8_HEADER_2BYTE_IDENT)
			ret = 2;
		else if ((Byte & UTF_8_HEADER_3BYTE_MASK) == UTF_8_HEADER_3BYTE_IDENT)
			ret = 3;
		else if ((Byte & UTF_8_HEADER_4BYTE_MASK) == UTF_8_HEADER_4BYTE_IDENT)
			ret = 4;
	}
	return ret;
}

static inline bool UTF8_ValidateContinuation(uint8_t Byte, uint8_t SymSize)
{
	bool b1 = (Byte & UTF_8_BYTE_MASK) == UTF_8_BYTE_IDENT;
	bool b2 = SymSize != 0;
	return b1 && b2;
}

_tos_UTFValidationResult _tos_UTF8_ValidateEncodedArray(uint8_t* pArr, size_t ArrSize, uint8_t* pSize)
{
	_tos_UTFValidationResult ret = _tos_UTFValidationResult::UTFValidationResult_null;
	*pSize = 1;
	if (*pArr != '\0')
	{
		*pSize = UTF8_GetDecodeSymbolSize(*pArr);
		if (*pSize != 0)
		{
			pArr++;
			if (*pSize > ArrSize)
			{
				for (size_t i = 1; i < ArrSize; i++)
				{
					if (*pArr == '\0')
					{
						ret = _tos_UTFValidationResult::UTFValidationResult_incomplete;
						break;
					}
					else if (UTF8_ValidateContinuation(*pArr, 1) == false)
					{
						ret = _tos_UTFValidationResult::UTFValidationResult_encoding_error;
						break;
					}
					pArr++;
				}
				if (ret == _tos_UTFValidationResult::UTFValidationResult_null)
					ret = _tos_UTFValidationResult::UTFValidationResult_incomplete;
			}
			else
			{
				for (uint8_t i = 1; i < *pSize; i++)
				{
					if (*pArr == '\0')
					{
						ret = _tos_UTFValidationResult::UTFValidationResult_incomplete;
						break;
					}
					else if (UTF8_ValidateContinuation(*pArr, 1) == false)
					{
						ret = _tos_UTFValidationResult::UTFValidationResult_encoding_error;
						break;
					}
					pArr++;
				}
				if (ret == _tos_UTFValidationResult::UTFValidationResult_null)
					ret = _tos_UTFValidationResult::UTFValidationResult_success;
			}
		}
		else
			ret = _tos_UTFValidationResult::UTFValidationResult_encoding_error;
	}

	return ret;
}

uint8_t _tos_UTF8_DecodeSymbol(uint8_t* pArr, utf_conv_ctx* pCtx)
{
	uint8_t SymSize = UTF8_GetDecodeSymbolSize(*pArr);
	uint32_t shftreg = 0;
	if (SymSize > 0)
	{
		pCtx->buf = 0;
		switch (SymSize)
		{
		case 1:
			pCtx->buf = *pArr & ~UTF_8_HEADER_1BYTE_MASK;
			break;
		case 2:
			pCtx->buf = *pArr & ~UTF_8_HEADER_2BYTE_MASK;
			break;
		case 3:
			pCtx->buf = *pArr & ~UTF_8_HEADER_3BYTE_MASK;
			break;
		case 4:
			pCtx->buf = *pArr & ~UTF_8_HEADER_4BYTE_MASK;
			break;
		default:
			break;
		}
	}
	for (uint8_t i = 1; i < SymSize; i++)
	{
		pArr++;
		if (UTF8_ValidateContinuation(*pArr, SymSize))
		{
			shftreg = *pArr & ~UTF_8_BYTE_MASK;
			pCtx->buf <<= 6;
			pCtx->buf |= shftreg;
		}
		else
			SymSize = 0;
	}
	return SymSize;
}

static inline uint8_t UTF8_GetEncodeSymbolSize(uint32_t u32Symbol)
{
	// total of useful bits per bytes:
	// 1 byte  = 7bit
	// 2 bytes = 11 bits
	// 3 bytes = 16 bits
	// 4 bytes = 21 bits
	uint8_t ret = 0;
	bool b1 = u32Symbol <= UTF_8_MAX_VALUE;
	bool b2 = (u32Symbol < UTF_8_UNUSED_RANGE_START);
	bool b3 = (UTF_8_UNUSED_RANGE_END < u32Symbol);
	if (b1 && 
		(b2 || 
			b3))
	{
		if (u32Symbol < 128)
			ret = 1;
		else if (u32Symbol < 2048)
			ret = 2;
		else if (u32Symbol < 65536)
			ret = 3;
		else
			ret = 4;
	}
	return ret;
}

uint8_t _tos_UTF8_EncodeSymbol(uint32_t dwSym, utf_conv_ctx* pCtx)
{
	uint8_t SymSize = UTF8_GetEncodeSymbolSize(dwSym);
	uint8_t pos = SymSize - 1;
	if (SymSize)
	{
		pCtx->buf = 0;
		for (uint8_t it = 1; it < SymSize; it++)
		{
			pCtx->chArr[pos] = UTF_8_BYTE_IDENT | (dwSym & ~UTF_8_BYTE_MASK);
			pos--;
			dwSym >>= 6;
		}

		switch (SymSize)
		{
		case 1:
			pCtx->chArr[pos] = (dwSym & ~UTF_8_HEADER_1BYTE_MASK);
			break;
		case 2:
			pCtx->chArr[pos] = UTF_8_HEADER_2BYTE_IDENT | (dwSym & ~UTF_8_HEADER_2BYTE_MASK);
			break;
		case 3:
			pCtx->chArr[pos] = UTF_8_HEADER_3BYTE_IDENT | (dwSym & ~UTF_8_HEADER_3BYTE_MASK);
			break;
		case 4:
			pCtx->chArr[pos] = UTF_8_HEADER_4BYTE_IDENT | (dwSym & ~UTF_8_HEADER_4BYTE_MASK);
			break;
		}
	}
	return SymSize;
}