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
#include <include/string.h>
#include <include/ctype.h>
#include <include/stdlib.h>
#include <include/stdio.h>

sf_convtype ParseConvType(char cType, bool* pBig)
{
	sf_convtype ret = sf_convtype::unknown;
	*pBig = false;

	switch (cType)
	{
	case 'd':
	case 'i':
		ret = sf_convtype::decimal;
		break;
	case 'o':
		ret = sf_convtype::udecimal_oct;
		break;
	case 'u':
		ret = sf_convtype::udecimal_unsigned;
		break;
	case 'X':
		*pBig = true;
	case 'x':
		ret = sf_convtype::udecimal_hex;
		break;
	case 'F':
		*pBig = true;
	case 'f':
		ret = sf_convtype::double_dec;
		break;
	case 'E':
		*pBig = true;
	case 'e':
		ret = sf_convtype::double_exponent;
		break;
	case 'G':
		*pBig = true;
	case 'g':
		ret = sf_convtype::double_dec_or_exp;
		break;
	case 'A':
		*pBig = true;
	case 'a':
		ret = sf_convtype::double_exponent;
		break;
	case 'c':
		ret = sf_convtype::charconv;
		break;
	case 's':
		ret = sf_convtype::string;
		break;
	case 'p':
		ret = sf_convtype::pointer;
		break;
	case 'n':
		ret = sf_convtype::n;
		break;
	case '%':
		ret = sf_convtype::noconv;
		break;
	default:
		break;
	}

	return ret;
}
sf_bitwidth ParseBitWidth(const char* s)
{
	sf_bitwidth ret = sf_bitwidth::unknown;
	switch (*s)
	{
	case 'h':
		if (s[1] == 'h')
			ret = sf_bitwidth::byte;
		else
			ret = sf_bitwidth::word;
		break;
	case 'l':
		if (s[1] == 'l')
			ret = sf_bitwidth::qword;
		else
			ret = sf_bitwidth::dword;
		break;
	case 'j':
		ret = sf_bitwidth::imax;
		break;
	case 'z':
		ret = sf_bitwidth::size;
		break;
	case 't':
		ret = sf_bitwidth::ptrdiff;
		break;
	case 'L':
		ret = sf_bitwidth::longd;
		break;
	}
	return ret;
}


char llutoch(uint64_t i, bool bUpper)
{
	char ret;
	if (i < 10)
		ret = '0' + i;
	else if (bUpper)
		ret = 'A' + (i - 10);
	else
		ret = 'a' + (i - 10);
	return ret;
}
char* llutoa(
	uint64_t v,
	uint64_t radix,
	size_t MinimumCharacters,
	bool bUpper,
	bool bSigned,
	char buffer[23],
	size_t* pOutSize)
{
	char* pRet = buffer + 22;
	size_t WrittenChars = 0;
	uint64_t div;
	uint64_t org = v;
	bool bMinus = false;
	memset(buffer, 0, 23);
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
		*pRet = llutoch(v - (div * radix), bUpper);
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
				*pRet = '0';
				WrittenChars++;
			}
			pRet--;
			*pRet = '-';
			WrittenChars++;
		}
		else
		{
			while (WrittenChars < MinimumCharacters)
			{
				pRet--;
				*pRet = '0';
				WrittenChars++;
			}
		}
	}
	else if (bMinus)
	{
		pRet--;
		*pRet = '-';
		WrittenChars++;
	}

	*pOutSize = WrittenChars;

	return pRet;
}

const char* ParseSpecial(
	const char* buffer,
	sf_convtype* conv,
	sf_bitwidth* width,
	bool* pUppercase,
	sf_flags* flags,
	char TempBuffer[sizeof(dbl_to_str_state::szBuffer)])
{
	const char* pChar = buffer;
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
		case '-':
			flags->bLeftJustified = true;
			pChar++;
			break;
		case '+':
			flags->bSign = true;
			pChar++;
			break;
		case ' ':
			flags->bSpace = true;
			pChar++;
			break;
		case '#':
			flags->bAltForm = true;
			pChar++;
			break;
		case '0':
			flags->bZeroPad = true;
			pChar++;
			break;
		default:
			bNBreak = false;
			break;
		}
	}

	/* padding */
	if (isdigit(*pChar))
	{
		size_t pos = 0;
		while (isdigit(pChar[pos]))
			pos++;
		memcpy(TempBuffer, pChar, pos);
		TempBuffer[pos] = 0;
		flags->nMinFieldWidth = strtol(TempBuffer, 0, 10);
		pChar += pos;

	}
	else if (*pChar == '*')
	{
		// comes from parameter
		flags->nMinFieldWidth = -1;
		pChar++;
	}
	/* precision */
	if (*pChar == '.')
	{
		pChar++;
		if (isdigit(*pChar))
		{
			size_t pos = 0;
			while (isdigit(pChar[pos]))
				pos++;
			memcpy(TempBuffer, pChar, pos);
			TempBuffer[pos] = 0;
			flags->nPrecision = strtol(TempBuffer, 0, 10);
			pChar += pos;

		}
		else if (*pChar == '*')
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
		*width = ParseBitWidth(pChar);
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
		*conv = ParseConvType(*pChar, pUppercase);

		if (*conv != sf_convtype::unknown)
			pChar++;
		else
			pChar = NULL;
	}

	return pChar;
}

const char* FindNextSpecial(const char* format)
{
	const char* pRet = format;

	while ((*pRet != NULL) && (*pRet != '%'))
		pRet++;
	if (*pRet == NULL)
		pRet = NULL;
	return pRet;
}

size_t CopyTextWithLimits(
	char* restrict s, size_t n,
	size_t* pWrote,
	const char* szSource,
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
			memcpy(s, szSource, Ret);
			*pWrote += Ret;
		}
	}
	return Ret;
}

int CopyText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const char* szSource,
	size_t SourceSize)
{
	int nRet;
	nRet = fwrite(szSource, 1, SourceSize, stream);
	if(nRet >= 0)
		*pWrote += nRet;
	return nRet;
}

size_t SetTextWithLimits(
	char* restrict s, size_t n,
	size_t* pWrote,
	const char chPadding,
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
			memset(s, chPadding, Ret);
			*pWrote += Ret;
		}
	}
	return Ret;
}
int SetText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const char chPadding,
	size_t SetSize)
{
	int nRet = 0;
	char SetArray[128];
	memset(SetArray, chPadding, 128);
	while (SetSize)
	{
		size_t CopySize = SetSize;
		if (SetSize > 128)
			CopySize = 128;
		nRet = fwrite(SetArray, 1, CopySize, stream);
		if (nRet >= 0)
			*pWrote += nRet;
		else
			break;
		SetSize -= nRet;
	}
	return nRet;
}

size_t WritePaddedTextNoDouble(
	char* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	const char* szSource,
	size_t SourceSize)
{
	size_t Ret = 0;
	*pWrote = 0;
	size_t WriteResult;
	bool bPad = false;
	size_t SizePadded = pFlags->nMinFieldWidth;
	char chPad = ' ';

	if (pFlags->bZeroPad)
		chPad = '0';

	bPad = SizePadded > SourceSize;
	if (!bPad)
		SizePadded = SourceSize;
	Ret = SizePadded;

	if (s)
	{
		if (pFlags->bLeftJustified)
		{
			WriteResult = CopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
			s += WriteResult;
			SetTextWithLimits(s, n, pWrote, chPad, SizePadded - SourceSize);
		}
		else
		{
			WriteResult = SetTextWithLimits(s, n, pWrote, chPad, SizePadded - SourceSize);
			s += WriteResult;
			CopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
		}
	}
	return Ret;
}
int WritePaddedTextNoDouble_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	const char* szSource,
	size_t SourceSize)
{
	*pWrote = 0;
	int nRet = 0;
	int nWriteResult2 = 0;
	bool bPad = false;
	size_t SizePadded = pFlags->nMinFieldWidth;
	char chPad = ' ';

	if (pFlags->bZeroPad)
		chPad = '0';

	bPad = SizePadded > SourceSize;
	if (!bPad)
		SizePadded = SourceSize;

	if (pFlags->bLeftJustified)
	{
		nRet = CopyText_File(stream, pWrote, szSource, SourceSize);
		if (nRet >= 0)
		{
			nWriteResult2 = SetText_File(stream, pWrote, chPad, SizePadded - SourceSize);
			if (nWriteResult2 >= 0)
				nRet += nWriteResult2;
			else
				nRet = -1;
		}
	}
	else
	{
		nRet = SetText_File(stream, pWrote, chPad, SizePadded - SourceSize);
		if (nRet >= 0)
		{
			nWriteResult2 = CopyText_File(stream, pWrote, szSource, SourceSize);
			if (nWriteResult2 >= 0)
				nRet += nWriteResult2;
			else
				nRet = -1;
		}
	}
	return nRet;
}

size_t WritePaddedTextDoubleReal(
	char* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	char* szSource,
	size_t SourceSize)
{
	size_t Ret = 0;
	char* szDot = strchr(szSource, '.');
	char chPadding = ' ';
	size_t WriteResult;
	if (pFlags->bZeroPad)
		chPadding = '0';
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
		DigitsAfterDot = strlen(szDot);
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
				WriteResult = SetTextWithLimits(s, n, pWrote, chPadding, ZerosToAddBefore);
				s += WriteResult;
			}
			if (DigitsBeforeDot)
			{
				WriteResult = CopyTextWithLimits(s, n, pWrote, szSource, DigitsBeforeDot);
				s += WriteResult;
			}

			WriteResult = SetTextWithLimits(s, n, pWrote, '.', 1);
			s += WriteResult;

			if (TrimOrAddAfter < 0)
			{
				//Trim
				WriteResult = CopyTextWithLimits(s, n, pWrote, szDot, DigitsAfterDot + TrimOrAddAfter + 1);
				s += WriteResult;
			}
			else
			{
				//Add zeros
				WriteResult = CopyTextWithLimits(s, n, pWrote, szDot, DigitsAfterDot);
				s += WriteResult;
				SetTextWithLimits(s, n, pWrote, '0', TrimOrAddAfter);
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
				WriteResult = SetTextWithLimits(s, n, pWrote, chPadding, 1);
				s += WriteResult;
			}
			WriteResult = CopyTextWithLimits(s, n, pWrote, szSource, SourceSize);
			s += WriteResult;
			WriteResult = SetTextWithLimits(s, n, pWrote, '.', 1);
			s += WriteResult;
			SetTextWithLimits(s, n, pWrote, '0', pFlags->nPrecision);
		}
	}


	return Ret;
}

int WritePaddedTextDoubleReal_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	char* szSource,
	size_t SourceSize)
{
	int nRet = 0;
	char* szDot = strchr(szSource, '.');
	char chPadding = ' ';
	int nWriteResult = 0;
	if (pFlags->bZeroPad)
		chPadding = '0';
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
		DigitsAfterDot = strlen(szDot);
		TrimOrAddAfter = (ptrdiff_t)pFlags->nPrecision - (ptrdiff_t)DigitsAfterDot;
		if (DigitsBeforeDot < pFlags->nMinFieldWidth)
		{
			ZerosToAddBefore = pFlags->nMinFieldWidth - DigitsBeforeDot;
		}

		if (ZerosToAddBefore)
		{
			nRet = SetText_File(stream, pWrote, chPadding, ZerosToAddBefore);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}
		if (DigitsBeforeDot)
		{
			nRet = CopyText_File(stream, pWrote, szSource, DigitsBeforeDot);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}

		if (pFlags->nPrecision >= 0)
		{
			nRet = SetText_File(stream, pWrote, '.', 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;

			if (TrimOrAddAfter < 0)
			{
				//Trim
				nRet = CopyText_File(stream, pWrote, szDot, DigitsAfterDot + TrimOrAddAfter + 1);
				if (nRet >= 0)
					nWriteResult += nRet;
				else
					goto cleanup;
			}
			else
			{
				//Add zeros
				nRet = CopyText_File(stream, pWrote, szDot, DigitsAfterDot);
				if (nRet >= 0)
					nWriteResult += nRet;
				else
					goto cleanup;
				nRet = SetText_File(stream, pWrote, '0', TrimOrAddAfter);
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
			nRet = SetText_File(stream, pWrote, chPadding, 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
		}
		nRet = CopyText_File(stream, pWrote, szSource, SourceSize);
		if (nRet >= 0)
			nWriteResult += nRet;
		else
			goto cleanup;
		if (pFlags->nPrecision >= 0)
		{
			nRet = SetText_File(stream, pWrote, '.', 1);
			if (nRet >= 0)
				nWriteResult += nRet;
			else
				goto cleanup;
			nRet = SetText_File(stream, pWrote, '0', pFlags->nPrecision);
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

size_t ProcessParameter_vsprintf(
	char* restrict s, size_t n, size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState
)
{
	//TODO: finish string, doubles and conforming other stuff
	//TODO: add integration with wcrtomb for %ls
	size_t Ret = 0;
	uint64_t bytestoconv;
	char* pConvRet = pState->szBuffer;
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
		pConvRet = llutoa(
			reg->qword,
			10,
			1,
			bUpper,
			true,
			pState->szBuffer,
			&Ret);

		break;
	}
	case sf_convtype::udecimal_oct:
	{
		pConvRet = llutoa(
			reg->qword,
			8,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&Ret
		);
		break;
	}
	case sf_convtype::udecimal_unsigned:
		pConvRet = llutoa(
			reg->qword,
			10,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&Ret
		);
		break;
	case sf_convtype::udecimal_hex:
		pConvRet = llutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&Ret
		);
		break;

	case sf_convtype::double_dec:
		dbltostr(reg->real8, &pFlags->nPrecision, bUpper, pState);
		Ret = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_exponent:
		strcpy(pState->szBuffer, "unimplemented double_exponent");
		//TODO: implement
		Ret = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_dec_or_exp:
		strcpy(pState->szBuffer, "unimplemented double_dec_or_exp");
		//TODO: implement
		Ret = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_hex_exp:
		strcpy(pState->szBuffer, "unimplemented double_hex_exp");
		//TODO: implement
		Ret = strlen(pState->szBuffer);
		break;
	case sf_convtype::charconv:
		if (bytestoconv == 0)
		{
			pState->szBuffer[0] = *(char*)&reg->byte;
			pState->szBuffer[1] = '\0';
			Ret = 1;
		}
		else
		{
			uint64_t zero = 0;
			memcpy(pState->szBuffer, &reg->qword, bytestoconv);
			memcpy(pState->szBuffer + bytestoconv, &zero, bytestoconv);
			Ret = bytestoconv;
		}
		break;
	case sf_convtype::string:
		break;
	case sf_convtype::pointer:
		pConvRet = llutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&Ret
		);
		break;
	case sf_convtype::n:
		*(int*)reg->qword = *wrote;
		break;
	case sf_convtype::noconv:
		pState->szBuffer[0] = '%';
		pState->szBuffer[1] = '\0';
		Ret = 1;
		break;
	}

	if (ConvType != sf_convtype::n)
	{
		if (ConvType != sf_convtype::string)
		{
			if (ConvType == sf_convtype::double_dec)
			{
				Ret = WritePaddedTextDoubleReal(
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
				Ret = WritePaddedTextNoDouble(
					s, n,
					wrote,
					pFlags,
					pConvRet,
					Ret
				);
			}
			else
			{
				Ret = WritePaddedTextNoDouble(
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

				strcpy(pState->szBuffer, "unimplemented mbstring");
				Ret = strlen(pState->szBuffer);
				CopyTextWithLimits(s, n, wrote, pState->szBuffer, Ret);
			}
			else
			{
				if (reg->qword)
				{
					// copy string
					Ret = strlen((char*)reg->qword);
					CopyTextWithLimits(s, n, wrote, (char*)reg->qword, Ret);
				}
				else
				{
					Ret = 6;
					if (bUpper)
						CopyTextWithLimits(s, n, wrote, "{NULL}", Ret);
					else
						CopyTextWithLimits(s, n, wrote, "{null}", Ret);
				}
			}
		}
	}
	return Ret;
}

int ProcessParameter_vfprintf(
	FILE* restrict stream, 
	size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState
)
{
	//TODO: finish string, doubles and conforming other stuff
	//TODO: add integration with wcrtomb for %ls
	int nRet = 0;
	size_t len;
	uint64_t bytestoconv;
	char* pConvRet = pState->szBuffer;
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
		pConvRet = llutoa(
			reg->qword,
			10,
			1,
			bUpper,
			true,
			pState->szBuffer,
			&len);

		break;
	}
	case sf_convtype::udecimal_oct:
	{
		pConvRet = llutoa(
			reg->qword,
			8,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&len
		);
		break;
	}
	case sf_convtype::udecimal_unsigned:
		pConvRet = llutoa(
			reg->qword,
			10,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&len
		);
		break;
	case sf_convtype::udecimal_hex:
		pConvRet = llutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&len
		);
		break;

	case sf_convtype::double_dec:
		dbltostr(reg->real8, &pFlags->nPrecision, bUpper, pState);
		len = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_exponent:
		strcpy(pState->szBuffer, "unimplemented double_exponent");
		//TODO: implement
		len = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_dec_or_exp:
		strcpy(pState->szBuffer, "unimplemented double_dec_or_exp");
		//TODO: implement
		len = strlen(pState->szBuffer);
		break;
	case sf_convtype::double_hex_exp:
		strcpy(pState->szBuffer, "unimplemented double_hex_exp");
		//TODO: implement
		len = strlen(pState->szBuffer);
		break;
	case sf_convtype::charconv:
		if (bytestoconv == 0)
		{
			pState->szBuffer[0] = *(char*)&reg->byte;
			pState->szBuffer[1] = '\0';
			len = 1;
		}
		else
		{
			uint64_t zero = 0;
			memcpy(pState->szBuffer, &reg->qword, bytestoconv);
			memcpy(pState->szBuffer + bytestoconv, &zero, bytestoconv);
			len = bytestoconv;
		}
		break;
	case sf_convtype::string:
		break;
	case sf_convtype::pointer:
		pConvRet = llutoa(
			reg->qword,
			16,
			1,
			bUpper,
			false,
			pState->szBuffer,
			&len
		);
		break;
	case sf_convtype::n:
		*(int*)reg->qword = *wrote;
		break;
	case sf_convtype::noconv:
		pState->szBuffer[0] = '%';
		pState->szBuffer[1] = '\0';
		len = 1;
		break;
	}

	if (ConvType != sf_convtype::n)
	{
		if (ConvType != sf_convtype::string)
		{
			if (ConvType == sf_convtype::double_dec)
			{
				nRet = WritePaddedTextDoubleReal_File(
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
				nRet = WritePaddedTextNoDouble_File(
					stream,
					wrote,
					pFlags,
					pConvRet,
					len
				);
			}
			else
			{
				nRet = WritePaddedTextNoDouble_File(
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
				//TODO: implement

				strcpy(pState->szBuffer, "unimplemented mbstring");
				len = strlen(pState->szBuffer);
				if(len)
					nRet = CopyText_File(stream, wrote, pState->szBuffer, len);
			}
			else
			{
				if (reg->qword)
				{
					// copy string
					len = strlen((char*)reg->qword);
					if(len)
						nRet = CopyText_File(stream, wrote, (char*)reg->qword, len);
				}
				else
				{
					len = 6;
					if (bUpper)
						nRet = CopyText_File(stream, wrote, "{NULL}", len);
					else
						nRet = CopyText_File(stream, wrote, "{null}", len);
				}
			}
		}
	}
	return nRet;
}

bool ReadVararg(va_list* pList, sf_convtype ConvType, sf_bitwidth BitWidth, x86_reg_struct* pReg)
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