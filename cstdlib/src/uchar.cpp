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
#include "utf_conv.h"
#include <include\uchar.h>
#include <include\string.h>
#include <include\errno.h>
static mbstate_t g_shared_mbstate;

size_t mbrtoc16(char16_t* restrict pc16,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps)
{
	errno = 0;
	size_t ret = 0;
	char32_t Value = 0;
	char16_t throwaway;
	utf_conv_ctx ctx{};
	if (ps == NULL)
		ps = &g_shared_mbstate;
	if (pc16 == NULL)
		pc16 = &throwaway;
	if (!ps->utf32)
	{
		ret = (int64_t)mbrtoc32(&Value, s, n, ps);
		if (ret >= 0)
		{
			uint8_t size = _tos_UTF16_EncodeSymbol(Value, &ctx);
			if (size > 1)
				ps->utf32 = ctx.buf;
			*pc16 = ctx.wArr[0];
		}
	}
	else
	{
		ctx.buf = ps->utf32;
		memset(ps, 0, sizeof(mbstate_t));
		*pc16 = ctx.wArr[1];
		ret = (size_t)-3;
	}


	return ret;
}
size_t c16rtomb(char* restrict s, char16_t c16,
	mbstate_t* restrict ps)
{
	errno = 0;
	// the way to do this is kind of stupid,
	// read the first word and check if its valid, return 0
	// read the other word and only then return the actual values
	size_t ret = 0;
	utf_conv_ctx ctx{};
	char throwaway[4];
	_tos_UTFValidationResult valres;
	uint8_t Len = 0;
	uint16_t* pSrc = (uint16_t*)&c16;
	if (ps == NULL)
		ps = &g_shared_mbstate;
	if (s == NULL)
		s = throwaway;

	if (ps->utf32 != 0 || ps->Pending) [[unlikely]]
	{
		valres = UTFValidationResult_success;
	}
	else [[likely]]
	{
		valres = _tos_UTF16_ValidateEncodedArray(pSrc, 1, &Len);
	}

	if (valres == UTFValidationResult_success)
	{
		if (ps->Pending)
		{
			*(uint16_t*)&ps->Bytes[2] = (uint16_t)c16;
			pSrc = (uint16_t*)ps->Bytes;
			valres = _tos_UTF16_ValidateEncodedArray(pSrc, 2, &Len);
		}
	}

	ret = (ptrdiff_t)valres;

	if (valres == UTFValidationResult_success)
	{
		uint8_t decoderet = _tos_UTF16_DecodeSymbol(pSrc, &ctx);
		memset(ps, 0, sizeof(mbstate_t));
		if (decoderet != 0)
		{
			ret = c32rtomb(s, ctx.buf, ps);
		}
		else
		{
			ret = (ptrdiff_t)UTFValidationResult_encoding_error;
			errno = EILSEQ;
			memset(ps, 0, sizeof(mbstate_t));
		}
	}
	else if (valres == UTFValidationResult_encoding_error)
	{
		errno = EILSEQ;
		memset(ps, 0, sizeof(mbstate_t));
	}
	else if (valres == UTFValidationResult_null) [[unlikely]]
	{
		ret = 1;
		*s = u8'\0';
		memset(ps, 0, sizeof(mbstate_t));
		
	}
	else if (valres == UTFValidationResult_incomplete)
	{
		*(uint16_t*)&ps->Bytes[0] = (uint16_t)c16;
		ps->ReadSize = 2;
		ps->Pending = 2;
		ret = 0;
	}
	
	return ret;

}


size_t mbrtoc32(char32_t* restrict pc32,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps)
{
	errno = 0;
	size_t ret = 0;
	_tos_UTFValidationResult valres;
	uint8_t Size = 0;
	uint8_t* pSrc = (uint8_t*)s;
	char32_t throwaway;
	if (ps == NULL)
		ps = &g_shared_mbstate;
	if (pc32 == NULL)
		pc32 = &throwaway;

	if (pSrc)
	{
		if (ps->utf32 != 0 || ps->Pending) [[unlikely]]
		{
			valres = UTFValidationResult_success;
		}
		else [[likely]]
		{
			valres = _tos_UTF8_ValidateEncodedArray(pSrc, n, &Size);
		}

		if (valres == UTFValidationResult_success)
		{
			if (ps->Pending)
			{
				if (ps->Pending <= n)
				{
					memcpy(&ps->Bytes[ps->ReadSize], s, ps->Pending);
					ps->ReadSize += n;
				}
				else
				{
					memcpy(&ps->Bytes[ps->ReadSize], s, n);
					ps->Pending -= n;
					ps->ReadSize += n;
				}
				pSrc = ps->Bytes;
				valres = _tos_UTF8_ValidateEncodedArray(pSrc, ps->ReadSize, &Size);
			}
		}

		ret = (ptrdiff_t)valres;

		if (valres == UTFValidationResult_success) [[likely]]
		{
			utf_conv_ctx ctx{};
			uint8_t convret = _tos_UTF8_DecodeSymbol(pSrc, &ctx);
			ret = (ptrdiff_t)convret;
			if (convret)
			{
				*pc32 = ctx.buf;
			}
			else
			{
				//error
				ret = (ptrdiff_t)UTFValidationResult_encoding_error;
				errno = EILSEQ;
			}
			memset(ps, 0, sizeof(mbstate_t));
		}
		else if (valres == UTFValidationResult_null) [[unlikely]]
		{
			*pc32 = U'\0';
			memset(ps, 0, sizeof(mbstate_t));
			ret = 0;
		}
		else if (valres == UTFValidationResult_encoding_error) [[unlikely]]
		{
			errno = EILSEQ;
			memset(ps, 0, sizeof(mbstate_t));
		}
		else if (valres == UTFValidationResult_incomplete) [[unlikely]]
		{
			if (ps->Pending == 0)
			{
				memset(ps->Bytes, 0, 4);
				memcpy(ps->Bytes, s, n);
				ps->Pending = Size - n;
				ps->ReadSize = n;
				ps->utf32 = 0;
			}
		}

	}
	else
	{
		memset(ps, 0, sizeof(mbstate_t));
		ret = UTFValidationResult_null;
	}
	return ret;
}

size_t c32rtomb(char* restrict s, char32_t c32,
	mbstate_t* restrict ps)
{
	errno = 0;
	utf_conv_ctx ctx{};
	char throwaway[4];
	if (s == NULL)
		s = throwaway;
	uint8_t size = _tos_UTF8_EncodeSymbol(c32, &ctx);
	if (size > 0)
		memcpy(s, ctx.chArr, size);
	else
		errno = EILSEQ;
	return (size_t)((intptr_t)size);
}