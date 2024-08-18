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
#include "wprintf_utils.h"
#include <include/string.h>
#include <include/wctype.h>
#include <include/stdlib.h>
#include <include/stdio.h>
//TODO: (wprintf) this entire implementation is suboptimal, redo it sometime


sf_convtype WideParseConvType(wchar_t cType, bool* pBig)
{
	sf_convtype ret = sf_convtype::unknown;
	*pBig = false;

	switch (cType)
	{
	case L'd':
	case L'i':
		ret = sf_convtype::decimal;
		break;
	case L'o':
		ret = sf_convtype::udecimal_oct;
		break;
	case L'u':
		ret = sf_convtype::udecimal_unsigned;
		break;
	case L'X':
		*pBig = true;
	case L'x':
		ret = sf_convtype::udecimal_hex;
		break;
	case L'F':
		*pBig = true;
	case L'f':
		ret = sf_convtype::double_dec;
		break;
	case L'E':
		*pBig = true;
	case L'e':
		ret = sf_convtype::double_exponent;
		break;
	case L'G':
		*pBig = true;
	case L'g':
		ret = sf_convtype::double_dec_or_exp;
		break;
	case L'A':
		*pBig = true;
	case L'a':
		ret = sf_convtype::double_exponent;
		break;
	case L'c':
		ret = sf_convtype::charconv;
		break;
	case L's':
		ret = sf_convtype::string;
		break;
	case L'p':
		ret = sf_convtype::pointer;
		break;
	case L'n':
		ret = sf_convtype::n;
		break;
	case L'%':
		ret = sf_convtype::noconv;
		break;
	default:
		break;
	}

	return ret;
}
sf_bitwidth WideParseBitWidth(const wchar_t* s)
{
	sf_bitwidth ret = sf_bitwidth::unknown;
	switch (*s)
	{
	case L'h':
		if (s[1] == L'h')
			ret = sf_bitwidth::byte;
		else
			ret = sf_bitwidth::word;
		break;
	case L'l':
		if (s[1] == L'l')
			ret = sf_bitwidth::qword;
		else
			ret = sf_bitwidth::dword;
		break;
	case L'j':
		ret = sf_bitwidth::imax;
		break;
	case L'z':
		ret = sf_bitwidth::size;
		break;
	case L't':
		ret = sf_bitwidth::ptrdiff;
		break;
	case L'L':
		ret = sf_bitwidth::longd;
		break;
	}
	return ret;
}


wchar_t Widellutoch(uint64_t i, bool bUpper)
{
	wchar_t ret;
	if (i < 10)
		ret = L'0' + i;
	else if (bUpper)
		ret = L'A' + (i - 10);
	else
		ret = L'a' + (i - 10);
	return ret;
}
wchar_t* Widellutoa(
	uint64_t v,
	uint64_t radix,
	size_t MinimumCharacters,
	bool bUpper,
	bool bSigned,
	wchar_t buffer[23],
	size_t* pOutSize)
{
	wchar_t* pRet = buffer + 22;
	size_t WrittenChars = 0;
	uint64_t div;
	uint64_t org = v;
	bool bMinus = false;
	wmemset(buffer, 0, 23);
	if (MinimumCharacters > 22)
		MinimumCharacters = 22;

	else if (bSigned && *(int64_t*)&org < 0)
	{
		*(int64_t*)&v = -*(int64_t*)&v;
		bMinus = true;
	}
	for (int i = 21; i >= 0 && v != 0; i--)
	{
		pRet--;
		div = v / radix;
		*pRet = Widellutoch(v - (div * radix), bUpper);
		WrittenChars++;
		v = div;
	}


	if (MinimumCharacters > WrittenChars)
	{
		if (bMinus)
		{
			MinimumCharacters--;
			while (WrittenChars < MinimumCharacters)
			{
				pRet--;
				*pRet = L'0';
				WrittenChars++;
			}
			pRet--;
			*pRet = L'-';
			WrittenChars++;
		}
		else
		{
			while (WrittenChars < MinimumCharacters)
			{
				pRet--;
				*pRet = L'0';
				WrittenChars++;
			}
		}
	}
	else if (bMinus)
	{
		pRet--;
		*pRet = L'-';
		WrittenChars++;
	}

	*pOutSize = WrittenChars;

	return pRet;
}

const wchar_t* WideParseSpecial(
	const wchar_t* buffer,
	sf_convtype* conv,
	sf_bitwidth* width,
	bool* pUppercase,
	sf_flags* flags,
	wchar_t TempBuffer[sizeof(dbl_to_str_state::szBuffer)])
{
	const wchar_t* pChar = buffer;
	memset(flags, 0, sizeof(*flags));
	flags->nMinFieldWidth = 0;
	flags->nPrecision = 0;
	*conv = sf_convtype::unknown;
	*width = sf_bitwidth::unknown;
	*pUppercase = false;
	/* flags */
	bool bNBreak = true;
	pChar++;
	while (bNBreak)
	{
		switch (*pChar)
		{
		case L'-':
			flags->bLeftJustified = true;
			pChar++;
			break;
		case L'+':
			flags->bSign = true;
			pChar++;
			break;
		case L' ':
			flags->bSpace = true;
			pChar++;
			break;
		case L'#':
			flags->bAltForm = true;
			pChar++;
			break;
		case L'0':
			flags->bZeroPad = true;
			pChar++;
			break;
		default:
			bNBreak = false;
			break;
		}
	}

	/* padding */
	if (iswdigit(*pChar))
	{
		size_t pos = 0;
		while (iswdigit(pChar[pos]))
			pos++;
		wmemcpy(TempBuffer, pChar, pos);
		TempBuffer[pos] = 0;
		flags->nMinFieldWidth = wcstol(TempBuffer, 0, 10);
		pChar += pos;

	}
	else if (*pChar == L'*')
	{
		// comes from parameter
		flags->nMinFieldWidth = -1;
		pChar++;
	}
	/* precision */
	if (*pChar == L'.')
	{
		pChar++;
		if (iswdigit(*pChar))
		{
			size_t pos = 0;
			while (iswdigit(pChar[pos]))
				pos++;
			wmemcpy(TempBuffer, pChar, pos);
			TempBuffer[pos] = 0;
			flags->nPrecision = wcstol(TempBuffer, 0, 10);
			pChar += pos;

		}
		else if (*pChar == L'*')
		{
			// comes from parameter
			flags->nPrecision = -1;
			pChar++;
		}
		else
			pChar = NULL;
	}
	/* length */
	if (pChar)
	{
		*width = WideParseBitWidth(pChar);
		if (*width != sf_bitwidth::unknown)
		{
			pChar++;
			if (*width == sf_bitwidth::qword || *width == sf_bitwidth::byte)
				pChar++;
		}
	}
	/* conversion */
	if (pChar)
	{
		*conv = WideParseConvType(*pChar, pUppercase);

		if (*conv != sf_convtype::unknown)
			pChar++;
		else
			pChar = NULL;
	}

	return pChar;
}

const wchar_t* WideFindNextSpecial(const wchar_t* format)
{
	const wchar_t* pRet = format;

	while ((*pRet != NULL) && (*pRet != L'%'))
		pRet++;
	if (*pRet == NULL)
		pRet = NULL;
	return pRet;
}

size_t WideCopyTextWithLimits(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	const wchar_t* szSource,
	size_t SourceSize)
{
	size_t Ret = 0;
	if (s)
	{
		if (n > *pWrote + SourceSize)
			Ret = SourceSize;
		else
			Ret = n - *pWrote;

		if (Ret)
		{
			wmemcpy(s, szSource, Ret);
			*pWrote += Ret;
		}
	}
	return Ret;
}

int WideCopyText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const wchar_t* szSource,
	size_t SourceSize)
{
	int nRet;
	nRet = fwrite(szSource, sizeof(wchar_t), SourceSize, stream);
	if (nRet >= 0)
		*pWrote += nRet;
	return nRet;
}

size_t WideSetTextWithLimits(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	const wchar_t chPadding,
	size_t SetSize)
{
	size_t Ret = 0;
	if (s)
	{
		if (n > *pWrote + SetSize)
			Ret = SetSize;
		else if (n > *pWrote)
			Ret = n - *pWrote;

		if (Ret)
		{
			wmemset(s, chPadding, Ret);
			*pWrote += Ret;
		}
	}
	return Ret;
}
int WideSetText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const wchar_t chPadding,
	size_t SetSize)
{
	int nRet = 0;
	wchar_t SetArray[128];
	wmemset(SetArray, chPadding, 128);
	while (SetSize)
	{
		size_t CopySize = SetSize;
		if (SetSize > 128)
			CopySize = 128;
		nRet = fwrite(SetArray, sizeof(wchar_t), CopySize, stream);
		if (nRet >= 0)
			*pWrote += nRet;
		else
			break;
		SetSize -= nRet;
	}
	return nRet;
}

size_t WideWritePaddedTextNoDouble(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	const wchar_t* szSource,
	size_t SourceSize)
{
	size_t Ret = 0;
	*pWrote = 0;
	size_t WriteResult;
	bool bPad = false;
	size_t SizePadded = pFlags->nMinFieldWidth;
	wchar_t chPad = L' ';

	if (pFlags->bZeroPad)
		chPad = L'0';

	bPad = SizePadded > SourceSize;
	if (!bPad)
		SizePadded = SourceSize;
	Ret = SizePadded;

	if (s)
	{
		if (pFlags->bLeftJustified)
		{
			WriteResult = WideCopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
			s += WriteResult;
			WideSetTextWithLimits(s, n, pWrote, chPad, SizePadded - SourceSize);
		}
		else
		{
			WriteResult = WideSetTextWithLimits(s, n, pWrote, chPad, SizePadded - SourceSize);
			s += WriteResult;
			WideCopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
		}
	}
	return Ret;
}
int WideWritePaddedTextNoDouble_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	const wchar_t* szSource,
	size_t SourceSize)
{
	*pWrote = 0;
	int nRet = 0;
	int nWriteResult2 = 0;
	bool bPad = false;
	size_t SizePadded = pFlags->nMinFieldWidth;
	wchar_t chPad = L' ';

	if (pFlags->bZeroPad)
		chPad = L'0';

	bPad = SizePadded > SourceSize;
	if (!bPad)
		SizePadded = SourceSize;

	if (pFlags->bLeftJustified)
	{
		nRet = WideCopyText_File(stream, pWrote, szSource, SourceSize);
		if (nRet >= 0)
		{
			nWriteResult2 = WideSetText_File(stream, pWrote, chPad, SizePadded - SourceSize);
			if (nWriteResult2 >= 0)
				nRet += nWriteResult2;
			else
				nRet = -1;
		}
	}
	else
	{
		nRet = WideSetText_File(stream, pWrote, chPad, SizePadded - SourceSize);
		if (nRet >= 0)
		{
			nWriteResult2 = WideCopyText_File(stream, pWrote, szSource, SourceSize);
			if (nWriteResult2 >= 0)
				nRet += nWriteResult2;
			else
				nRet = -1;
		}
	}
	return nRet;
}

size_t WideWritePaddedTextDoubleReal(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	wchar_t* szSource,
	size_t SourceSize)
{
	size_t Ret = 0;
	wchar_t* szDot = wcschr(szSource, L'.');
	wchar_t chPadding = ' ';
	size_t WriteResult;
	if (pFlags->bZeroPad)
		chPadding = L'0';
	if (!pFlags->nPrecision)
		pFlags->nPrecision = 6;

	//TODO: add seperate function for copy with limits

	if (szDot)
	{
		size_t DigitsBeforeDot = (size_t)szDot - (size_t)szSource;
		size_t DigitsAfterDot = 0;
		ptrdiff_t TrimOrAddAfter = 0;
		size_t ZerosToAddBefore = 0;

		szDot++;
		DigitsAfterDot = wcslen(szDot);
		TrimOrAddAfter = (ptrdiff_t)pFlags->nPrecision - (ptrdiff_t)DigitsAfterDot;
		if (DigitsBeforeDot < pFlags->nMinFieldWidth)
		{
			Ret = pFlags->nMinFieldWidth;
			ZerosToAddBefore = pFlags->nMinFieldWidth - DigitsBeforeDot;
		}
		else
			Ret = DigitsBeforeDot;
		Ret += pFlags->nPrecision + 1;

		if (s)
		{
			if (ZerosToAddBefore)
			{
				WriteResult = WideSetTextWithLimits(s, n, pWrote, chPadding, ZerosToAddBefore);
				s += WriteResult;
			}
			if (DigitsBeforeDot)
			{
				WriteResult = WideCopyTextWithLimits(s, n, pWrote, szSource, DigitsBeforeDot);
				s += WriteResult;
			}

			WriteResult = WideSetTextWithLimits(s, n, pWrote, L'.', 1);
			s += WriteResult;

			if (TrimOrAddAfter < 0)
			{
				//Trim
				WriteResult = WideCopyTextWithLimits(s, n, pWrote, szDot, DigitsAfterDot + TrimOrAddAfter + 1);
				s += WriteResult;
			}
			else
			{
				//Add zeros
				WriteResult = WideCopyTextWithLimits(s, n, pWrote, szDot, DigitsAfterDot);
				s += WriteResult;
				WideSetTextWithLimits(s, n, pWrote, L'0', TrimOrAddAfter);
			}
		}
	}
	else
	{
		size_t PadBefore = 0;
		Ret = SourceSize;
		if (Ret < pFlags->nMinFieldWidth)
		{
			Ret = pFlags->nMinFieldWidth;
			PadBefore = SourceSize - pFlags->nMinFieldWidth;
		}
		Ret += 1 + pFlags->nPrecision;

		if (s)
		{
			if (PadBefore)
			{
				WriteResult = WideSetTextWithLimits(s, n, pWrote, chPadding, 1);
				s += WriteResult;
			}
			WriteResult = WideCopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
			s += WriteResult;
			WriteResult = WideSetTextWithLimits(s, n, pWrote, L'.', 1);
			s += WriteResult;
			WideSetTextWithLimits(s, n, pWrote, L'0', pFlags->nPrecision);
		}
	}


	return Ret;
}

int WideWritePaddedTextDoubleReal_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	wchar_t* szSource,
	size_t SourceSize)
{
	int nRet = 0;
	wchar_t* szDot = wcschr(szSource, L'.');
	wchar_t chPadding = L' ';
	int nWriteResult = 0;
	if (pFlags->bZeroPad)
		chPadding = L'0';
	if (!pFlags->nPrecision)
		pFlags->nPrecision = 6;

	//TODO: add seperate function for copy with limits
	//TODO: add rounding

	if (szDot)
	{
		size_t DigitsBeforeDot = (size_t)szDot - (size_t)szSource;
		size_t DigitsAfterDot = 0;
		ptrdiff_t TrimOrAddAfter = 0;
		size_t ZerosToAddBefore = 0;

		szDot++;
		DigitsAfterDot = wcslen(szDot);
		TrimOrAddAfter = (ptrdiff_t)pFlags->nPrecision - (ptrdiff_t)DigitsAfterDot;
		if (DigitsBeforeDot < pFlags->nMinFieldWidth)
		{
			ZerosToAddBefore = pFlags->nMinFieldWidth - DigitsBeforeDot;
		}

		if (ZerosToAddBefore)
		{
			nRet = WideSetText_File(stream, pWrote, chPadding, ZerosToAddBefore);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}
		if (DigitsBeforeDot)
		{
			nRet = WideCopyText_File(stream, pWrote, szSource, DigitsBeforeDot);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}

		if (pFlags->nPrecision >= 0)
		{
			nRet = WideSetText_File(stream, pWrote, L'.', 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;

			if (TrimOrAddAfter < 0)
			{
				//Trim
				nRet = WideCopyText_File(stream, pWrote, szDot, DigitsAfterDot + TrimOrAddAfter + 1);
				if (nRet >= 0)
					nWriteResult += nRet;
				else
					goto cleanup;
			}
			else
			{
				//Add zeros
				nRet = WideCopyText_File(stream, pWrote, szDot, DigitsAfterDot);
				if (nRet >= 0)
					nWriteResult += nRet;
				else
					goto cleanup;
				nRet = WideSetText_File(stream, pWrote, L'0', TrimOrAddAfter);
				if (nRet >= 0)
					nWriteResult += nRet;
				else
					goto cleanup;
			}
		}
	}
	else
	{
		size_t PadBefore = 0;
		if (SourceSize < pFlags->nMinFieldWidth)
		{
			PadBefore = SourceSize - pFlags->nMinFieldWidth;
		}

		if (PadBefore)
		{
			nRet = WideSetText_File(stream, pWrote, chPadding, 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}
		nRet = WideCopyText_File(stream, pWrote, szSource, SourceSize);
		if (nRet >= 0)
			nWriteResult += nRet;
		else
			goto cleanup;
		if (pFlags->nPrecision >= 0)
		{
			nRet = WideSetText_File(stream, pWrote, L'.', 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
			nRet = WideSetText_File(stream, pWrote, L'0', pFlags->nPrecision);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}
	}

cleanup:
	if (nRet >= 0)
		nRet = nWriteResult;

	return nRet;
}

size_t WideProcessParameter_vsprintf(
	wchar_t* restrict s, size_t n, size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState,
	wchar_t wcsBuffer[sizeof(dbl_to_str_state::szBuffer) / sizeof(dbl_to_str_state::szBuffer[0])]
)
{
	//TODO: finish string, doubles and conforming other stuff
	//TODO: add integration with wcrtomb for %ls
	size_t Ret = 0;
	uint64_t bytestoconv;
	wchar_t* pConvRet = wcsBuffer;
	switch (BitWidth)
	{
	case sf_bitwidth::byte:
		bytestoconv = 1;
		break;
	case sf_bitwidth::word:
		bytestoconv = 2;
		break;
	case sf_bitwidth::dword:
		bytestoconv = 4;
		break;
	case sf_bitwidth::qword:
		bytestoconv = 8;
		break;
	case sf_bitwidth::imax:
		bytestoconv = 8;
		break;
	case sf_bitwidth::size:
		bytestoconv = 8;
		break;
	case sf_bitwidth::ptrdiff:
		bytestoconv = 8;
		break;
	case sf_bitwidth::longd:
		bytestoconv = sizeof(long double);
		break;
	case sf_bitwidth::unknown:
	default:
		bytestoconv = 0;
		break;
	}

	switch (ConvType)
	{
	case sf_convtype::unknown:
		break;
	case sf_convtype::decimal:
	{
		pConvRet = Widellutoa(
			reg->qword,
			10,
			1,
			bUpper,
			true,
			wcsBuffer,
			&Ret);

		break;
	}
	case sf_convtype::udecimal_oct:
	{
		pConvRet = Widellutoa(
			reg->qword,
			8,
			1,
			bUpper,
			false,
			wcsBuffer,
			&Ret
		);
		break;
	}
	case sf_convtype::udecimal_unsigned:
		pConvRet = Widellutoa(
			reg->qword,
			10,
			1,
			bUpper,
			false,
			wcsBuffer,
			&Ret
		);
		break;
	case sf_convtype::udecimal_hex:
		pConvRet = Widellutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			wcsBuffer,
			&Ret
		);
		break;

	case sf_convtype::double_dec:
	{

		mbstate_t mstate = { 0 };
		dbltostr(reg->real8, &pFlags->nPrecision, bUpper, pState);
		Ret = strlen(pState->szBuffer);
		char* ch = pState->szBuffer;
		mbsrtowcs(wcsBuffer, (const char**)&ch, Ret, &mstate);
		break;
	}
	case sf_convtype::double_exponent:
		wcscpy(wcsBuffer, L"unimplemented double_exponent");
		//TODO: implement
		Ret = wcslen(wcsBuffer);
		break;
	case sf_convtype::double_dec_or_exp:
		wcscpy(wcsBuffer, L"unimplemented double_dec_or_exp");
		//TODO: implement
		Ret = wcslen(wcsBuffer);
		break;
	case sf_convtype::double_hex_exp:
		wcscpy(wcsBuffer, L"unimplemented double_hex_exp");
		//TODO: implement
		Ret = wcslen(wcsBuffer);
		break;
	case sf_convtype::charconv:
		if (bytestoconv == 0)
		{
			wcsBuffer[0] = *(wchar_t*)&reg->byte;
			wcsBuffer[1] = '\0';
			Ret = 1;
		}
		else
		{
			//TODO: revisit this
			/*
			uint64_t zero = 0;
			memcpy(wcsBuffer, &reg->qword, bytestoconv);
			memcpy(wcsBuffer + bytestoconv, &zero, bytestoconv);
			Ret = bytestoconv;
			*/
		}
		break;
	case sf_convtype::string:
		break;
	case sf_convtype::pointer:
		pConvRet = Widellutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			wcsBuffer,
			&Ret
		);
		break;
	case sf_convtype::n:
		*(int*)reg->qword = *wrote;
		break;
	case sf_convtype::noconv:
		wcsBuffer[0] = L'%';
		wcsBuffer[1] = L'\0';
		Ret = 1;
		break;
	}

	if (ConvType != sf_convtype::n)
	{
		if (ConvType != sf_convtype::string)
		{
			if (ConvType == sf_convtype::double_dec)
			{
				Ret = WideWritePaddedTextDoubleReal(
					s, n,
					wrote,
					pFlags,
					pConvRet,
					Ret
				);
			}
			else if (ConvType == sf_convtype::double_dec_or_exp ||
				ConvType == sf_convtype::double_exponent ||
				ConvType == sf_convtype::double_hex_exp)
			{
				Ret = WideWritePaddedTextNoDouble(
					s, n,
					wrote,
					pFlags,
					pConvRet,
					Ret
				);
			}
			else
			{
				Ret = WideWritePaddedTextNoDouble(
					s, n,
					wrote,
					pFlags,
					pConvRet,
					Ret
				);
			}
		}
		else
		{
			if (bytestoconv != 0)
			{
				//TODO: implement

				wcscpy(wcsBuffer, L"unimplemented mbstring");
				Ret = wcslen(wcsBuffer);
				WideCopyTextWithLimits(s, n, wrote, wcsBuffer, Ret);
			}
			else
			{
				if (reg->qword)
				{
					Ret = wcslen((wchar_t*)reg->qword);
					WideCopyTextWithLimits(s, n, wrote, (wchar_t*)reg->qword, Ret);
				}
				else
				{
					Ret = 6;
					if (bUpper)
						WideCopyTextWithLimits(s, n, wrote, L"{NULL}", Ret);
					else
						WideCopyTextWithLimits(s, n, wrote, L"{null}", Ret);
				}
			}
		}
	}
	return Ret;
}

int WideProcessParameter_vfprintf(
	FILE* restrict stream,
	size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState,
	wchar_t wcsBuffer[sizeof(dbl_to_str_state::szBuffer) / sizeof(dbl_to_str_state::szBuffer[0])]
)
{
	//TODO: finish string, doubles and conforming other stuff
	//TODO: add integration with wcrtomb for %ls
	int nRet = 0;
	size_t len;
	uint64_t bytestoconv;
	wchar_t* pConvRet = wcsBuffer;
	switch (BitWidth)
	{
	case sf_bitwidth::byte:
		bytestoconv = 1;
		break;
	case sf_bitwidth::word:
		bytestoconv = 2;
		break;
	case sf_bitwidth::dword:
		bytestoconv = 4;
		break;
	case sf_bitwidth::qword:
		bytestoconv = 8;
		break;
	case sf_bitwidth::imax:
		bytestoconv = 8;
		break;
	case sf_bitwidth::size:
		bytestoconv = 8;
		break;
	case sf_bitwidth::ptrdiff:
		bytestoconv = 8;
		break;
	case sf_bitwidth::longd:
		bytestoconv = sizeof(long double);
		break;
	case sf_bitwidth::unknown:
	default:
		bytestoconv = 0;
		break;
	}

	switch (ConvType)
	{
	case sf_convtype::unknown:
		break;
	case sf_convtype::decimal:
	{
		pConvRet = Widellutoa(
			reg->qword,
			10,
			1,
			bUpper,
			true,
			wcsBuffer,
			&len);

		break;
	}
	case sf_convtype::udecimal_oct:
	{
		pConvRet = Widellutoa(
			reg->qword,
			8,
			1,
			bUpper,
			false,
			wcsBuffer,
			&len
		);
		break;
	}
	case sf_convtype::udecimal_unsigned:
		pConvRet = Widellutoa(
			reg->qword,
			10,
			1,
			bUpper,
			false,
			wcsBuffer,
			&len
		);
		break;
	case sf_convtype::udecimal_hex:
		pConvRet = Widellutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			wcsBuffer,
			&len
		);
		break;

	case sf_convtype::double_dec:
	{
		mbstate_t mstate = { 0 };
		dbltostr(reg->real8, &pFlags->nPrecision, bUpper, pState);
		len = strlen(pState->szBuffer);
		char* ch = pState->szBuffer;
		mbsrtowcs(wcsBuffer, (const char**)&ch, len, &mstate);
		break;
	}
	case sf_convtype::double_exponent:
		wcscpy(wcsBuffer, L"unimplemented double_exponent");
		//TODO: implement
		len = wcslen(wcsBuffer);
		break;
	case sf_convtype::double_dec_or_exp:
		wcscpy(wcsBuffer, L"unimplemented double_dec_or_exp");
		//TODO: implement
		len = wcslen(wcsBuffer);
		break;
	case sf_convtype::double_hex_exp:
		wcscpy(wcsBuffer, L"unimplemented double_hex_exp");
		//TODO: implement
		len = wcslen(wcsBuffer);
		break;
	case sf_convtype::charconv:
		if (bytestoconv == 0)
		{
			wcsBuffer[0] = *(wchar_t*)&reg->word;
			wcsBuffer[1] = L'\0';
			len = 1;
		}
		else
		{
			//TODO: revisit this
			/*
			uint64_t zero = 0;
			memcpy(wcsBuffer, &reg->qword, bytestoconv);
			memcpy(wcsBuffer + bytestoconv, &zero, bytestoconv);
			len = bytestoconv;
			*/
		}
		break;
	case sf_convtype::string:
		break;
	case sf_convtype::pointer:
		pConvRet = Widellutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			wcsBuffer,
			&len
		);
		break;
	case sf_convtype::n:
		*(int*)reg->qword = *wrote;
		break;
	case sf_convtype::noconv:
		wcsBuffer[0] = L'%';
		wcsBuffer[1] = L'\0';
		len = 1;
		break;
	}

	if (ConvType != sf_convtype::n)
	{
		if (ConvType != sf_convtype::string)
		{
			if (ConvType == sf_convtype::double_dec)
			{
				nRet = WideWritePaddedTextDoubleReal_File(
					stream,
					wrote,
					pFlags,
					pConvRet,
					len
				);
			}
			else if (ConvType == sf_convtype::double_dec_or_exp ||
				ConvType == sf_convtype::double_exponent ||
				ConvType == sf_convtype::double_hex_exp)
			{
				nRet = WideWritePaddedTextNoDouble_File(
					stream,
					wrote,
					pFlags,
					pConvRet,
					len
				);
			}
			else
			{
				nRet = WideWritePaddedTextNoDouble_File(
					stream,
					wrote,
					pFlags,
					pConvRet,
					len
				);
			}
		}
		else
		{
			if (bytestoconv != 0)
			{
				//TODO: (wprintf) implement multibyte conversion

				wcscpy(wcsBuffer, L"unimplemented mbstring");
				len = wcslen(wcsBuffer);
				if (len)
					nRet = WideCopyText_File(stream, wrote, wcsBuffer, len);
			}
			else
			{
				if (reg->qword)
				{
					len = wcslen((wchar_t*)reg->qword);
					if (len)
						nRet = WideCopyText_File(stream, wrote, (wchar_t*)reg->qword, len);
				}
				else
				{
					len = 6;
					if (bUpper)
						nRet = WideCopyText_File(stream, wrote, L"{NULL}", len);
					else
						nRet = WideCopyText_File(stream, wrote, L"{null}", len);
				}
			}
		}
	}
	return nRet;
}

bool WideReadVararg(va_list* pList, sf_convtype ConvType, sf_bitwidth BitWidth, x86_reg_struct* pReg)
{
	bool bRet = true;
	switch (ConvType)
	{
	case sf_convtype::decimal:
	{
		switch (BitWidth)
		{
		case sf_bitwidth::byte:
			pReg->sqword = (int64_t)((int8_t)va_arg(*pList, int32_t)); break;
		case sf_bitwidth::word:
			pReg->sqword = (int64_t)((int16_t)va_arg(*pList, int32_t)); break;
		case sf_bitwidth::dword:
		case sf_bitwidth::unknown:
			pReg->sqword = va_arg(*pList, int32_t); break;
		case sf_bitwidth::qword:
		case sf_bitwidth::imax:
		case sf_bitwidth::size:
		case sf_bitwidth::ptrdiff:
			pReg->sqword = (uint64_t)va_arg(*pList, int64_t);
			break;
		case sf_bitwidth::longd:
			bRet = false;
			break;
		default:
			break;
		}
		break;
	}
	case sf_convtype::udecimal_oct:
	case sf_convtype::udecimal_unsigned:
	case sf_convtype::udecimal_hex:
	{
		switch (BitWidth)
		{
		case sf_bitwidth::byte:
			pReg->byte = (uint8_t)va_arg(*pList, uint32_t); break;
		case sf_bitwidth::word:
			pReg->word = (uint16_t)va_arg(*pList, uint32_t); break;
		case sf_bitwidth::unknown:
		case sf_bitwidth::dword:
			pReg->dword = va_arg(*pList, uint32_t);
			break;
		case sf_bitwidth::qword:
		case sf_bitwidth::imax:
		case sf_bitwidth::size:
		case sf_bitwidth::ptrdiff:
			pReg->qword = va_arg(*pList, uint64_t);
			break;
		case sf_bitwidth::longd:
			bRet = false;
			break;
		default:
			break;
		}
		break;
	}
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
	{

		switch (BitWidth)
		{
		case sf_bitwidth::byte:
		case sf_bitwidth::word:
		case sf_bitwidth::dword:
		case sf_bitwidth::imax:
		case sf_bitwidth::size:
		case sf_bitwidth::ptrdiff:
		case sf_bitwidth::qword:
			bRet = false;
			break;
		case sf_bitwidth::longd:
			pReg->real10 = va_arg(*pList, long double);
			break;
		case sf_bitwidth::unknown:
			pReg->real8 = va_arg(*pList, double);
			break;
		default:
			break;
		}
		break;
	}
	case sf_convtype::charconv:
	{
		if ((BitWidth == sf_bitwidth::unknown) ||
			(BitWidth == sf_bitwidth::dword))
		{
			pReg->qword = va_arg(*pList, uint64_t);
#ifdef _WIN32
			if (BitWidth == sf_bitwidth::dword)
				BitWidth = sf_bitwidth::word;
#endif // _WIN32
		}
		else
			bRet = false;
		break;
	}
	case sf_convtype::string:
	{
		if ((BitWidth == sf_bitwidth::unknown) ||
			(BitWidth == sf_bitwidth::dword))
		{
			pReg->qword = va_arg(*pList, uint64_t);
#ifdef _WIN32
			if (BitWidth == sf_bitwidth::dword)
				BitWidth = sf_bitwidth::word;
#endif // _WIN32
		}
		else
			bRet = false;
		break;
	}
	case sf_convtype::pointer:
	case sf_convtype::n:
	{
		if (BitWidth != sf_bitwidth::unknown)
			bRet = false;
		else
			pReg->qword = va_arg(*pList, uint64_t);

		break;
	}
	case sf_convtype::noconv:
	{
		if (BitWidth != sf_bitwidth::unknown)
			bRet = false;
		break;
	}
	case sf_convtype::unknown:
	default:
		bRet = false;
		break;
	}
	return bRet;
}