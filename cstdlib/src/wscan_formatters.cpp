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
#include <include\stdlib.h>
#include <include\string.h>
#include <include\wchar.h>
#include <include\stddef.h>
#include <include\stdint.h>
#include <include\wctype.h>
#include <include\stdarg.h>

enum class sf_bitwidth {
	byte,
	word,
	dword,
	qword,
	imax,
	size,
	ptrdiff,
	longd,
	unknown
};

enum class sf_convtype {
	decimal, //
	udecimal_oct, //
	udecimal_unsigned, //
	udecimal_hex, //
	double_dec,
	double_exponent,
	double_dec_or_exp,
	double_hex_exp,
	charconv,
	string,
	pointer,
	n,
	noconv,
	percent,
	set,
	error,
	unknown
};

union ScannerReturnNative
{
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;
};

struct scanners_scope_check_ctx {
	bool bSign;
	bool bPoint;
	bool bExponent;
	bool bExpSign;
	bool bPrefix1;
	bool bPrefix2;
	bool bNotHex;
	wchar_t chFirstTwo[2];
	uint8_t FirstTwoCount;
};

typedef bool (*procscopechk)(int n, scanners_scope_check_ctx* pctx);

static bool ScopeCheckDec(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n == L'+' || n == L'-')
	{
		if (pctx->bSign)
			bRet = false;
		pctx->bSign = true;
	}
	else if (iswdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckHex(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n == '+' || n == '-')
	{
		if (pctx->bSign)
			bRet = false;
		pctx->bSign = true;
	}
	else if (n != L'0' && !pctx->bPrefix1)
		bRet = false;
	else if (n == L'0' && !pctx->bPrefix1)
		pctx->bPrefix1 = true;
	else if (towlower(n) != L'x' && !pctx->bPrefix2)
		bRet = false;
	else if (towlower(n) == L'x' && !pctx->bPrefix2)
		pctx->bPrefix2 = true;
	else if (iswxdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckOct(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n == L'+' || n == L'-')
	{
		if (pctx->bSign)
			bRet = false;
		pctx->bSign = true;
	}
	else if (iswdigit(n) == 0 || towlower(n) >= L'g')
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatDec(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	//nan
	//inf, infinity
	if (n == L'+' || n == L'-')
	{
		if (pctx->bExponent)
		{
			if (pctx->bExpSign)
				bRet = false;
			pctx->bExpSign = true;
		}
		else if (pctx->bSign)
		{
			bRet = false;
		}
		pctx->bSign = true;
	}
	else if (n == L'.')
	{
		if (pctx->bPoint)
			bRet = false;
		pctx->bPoint = true;
	}
	else if (towlower(n) == (L'e'))
	{
		if (pctx->bExponent)
			bRet = false;
		pctx->bExponent = true;
	}
	else if (iswdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatHex(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	//nan
	//inf, infinity
	if (n == L'+' || n == L'-')
	{
		if (pctx->bExponent)
		{
			if (pctx->bExpSign)
				bRet = false;
			pctx->bExpSign = true;
		}
		else if (pctx->bSign)
		{
			bRet = false;
		}
		pctx->bSign = true;
	}
	else if (n != L'0' && !pctx->bPrefix1)
		bRet = false;
	else if (n == L'0' && !pctx->bPrefix1)
		pctx->bPrefix1 = true;
	else if (towlower(n) != L'x' && !pctx->bPrefix2)
		bRet = false;
	else if (towlower(n) == L'x' && !pctx->bPrefix2)
		pctx->bPrefix2 = true;
	else if (n == L'.')
	{
		if (pctx->bPoint)
			bRet = false;
		pctx->bPoint = true;
	}
	else if (towlower(n) == (L'p'))
	{
		if (pctx->bExponent)
			bRet = false;
		pctx->bExponent = true;
	}
	else if (iswxdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatCombined(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n != L'-' && n != L'+')
	{
		if (pctx->FirstTwoCount == 0)
		{
			if ((wchar_t)n != L'0')
			{
				pctx->bNotHex = true;
				pctx->FirstTwoCount++;
			}
			pctx->FirstTwoCount++;
		}
		else if (pctx->FirstTwoCount == 1)
		{
			if ((wchar_t)towlower(n) != L'x')
				pctx->bNotHex = true;
			pctx->FirstTwoCount++;
		}
	}

	if (pctx->bNotHex)
		bRet = ScopeCheckFloatDec(n, pctx);
	else
		bRet = ScopeCheckFloatHex(n, pctx);

	return bRet;
}


static bool ScopeCheckString(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	//if (isalnum(n) == 0)
	//	bRet = false;
	return bRet;
}

static bool ScannerStrGeneric(
	FILE* stream,
	procscopechk fScopeCheck,
	uint64_t qwCharLimit,
	wchar_t* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar;
	scanners_scope_check_ctx ctx = { 0 };
	do
	{
		nChar = getwc(stream);
		if (!iswspace(nChar))
		{
			if (fScopeCheck(nChar, &ctx))
			{
				*pOutBuff = nChar;
				pOutBuff++;
				CharCount++;
				bRet = true;
			}
		}
		else
		{
			ungetwc(nChar, stream);
			break;
		}

	} while (nChar != EOF && CharCount < qwCharLimit);
	*pOutBuff = L'\0';
	*pnReadCount = CharCount;
	return bRet;
}

static bool ScannerStrGenericAbsolute(
	FILE* stream,
	uint64_t qwCharLimit,
	wchar_t* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar;
	do
	{
		nChar = getwc(stream);
		if (nChar != EOF)
		{
			*pOutBuff = nChar;
			pOutBuff++;
			CharCount++;
			bRet = true;
		}

	} while (nChar != EOF && CharCount < qwCharLimit);
	*pOutBuff = L'\0';
	*pnReadCount = CharCount;
	return bRet;
}

static void WhitespaceDirective(FILE* stream, int* pnCount)
{
	int nChar;
	int nCount = -1;
	do
	{
		nChar = getwc(stream);
		nCount++;
	} while (iswspace(nChar) != 0);
	ungetwc(nChar, stream);
	*pnCount = nCount;
}

static sf_bitwidth ParseWidth(const wchar_t* szFormat, uint64_t* pLength)
{
	sf_bitwidth ret = sf_bitwidth::unknown;
	*pLength = 1;
	switch (szFormat[0])
	{
	case L'h':
		if (szFormat[1] == L'h')
		{
			ret = sf_bitwidth::byte;
			*pLength = 2;
		}
		else
			ret = sf_bitwidth::word;
		break;
	case L'l':
		if (szFormat[1] == L'l')
		{
			ret = sf_bitwidth::qword;
			*pLength = 2;
		}
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
	default:
		*pLength = 0;
		break;
	}
	return ret;
}

static sf_convtype ParseType(
	const wchar_t* szFormat, uint64_t* pLength,
	bool pbSet[256])
{
	sf_convtype ret = sf_convtype::unknown;
	size_t SetCount = 0;
	size_t SetItr = 1;
	bool bSetVal = true;
	*pLength = 1;
	switch (szFormat[0])
	{
	case L'%':
		ret = sf_convtype::percent;
		break;
	case L'c':
		ret = sf_convtype::charconv;
		break;
	case L's':
		ret = sf_convtype::string;
		break;
	case L'd':
		ret = sf_convtype::decimal;
		break;
	case L'i':
		ret = sf_convtype::decimal;
		break;
	case L'u':
		ret = sf_convtype::udecimal_unsigned;
		break;
	case L'o':
		ret = sf_convtype::udecimal_oct;
		break;
	case L'x':
		ret = sf_convtype::udecimal_hex;
		break;
	case L'X':
		ret = sf_convtype::udecimal_hex;
		break;
	case L'n':
		ret = sf_convtype::n;
		break;
	case L'a':
	case L'A':
	case L'e':
	case L'E':
	case L'f':
	case L'F':
	case L'g':
	case L'G':
		ret = sf_convtype::double_dec_or_exp;
		break;
	case L'p':
		ret = sf_convtype::pointer;
		break;
	case L'[':
		ret = sf_convtype::set;
		if (szFormat[SetItr] == L'^')
		{
			bSetVal = false;
			SetItr++;
		}
		memset(pbSet, !bSetVal, sizeof(bool) * 256);
		//TODO: finish implementing this in a conformant way
		//TODO: Add a way to support this on non ascii characters
		while (szFormat[SetItr] != L']' && szFormat[SetItr] != L'\0')
		{
			for (size_t i = 0; i < SetCount; i++)
				pbSet[(uint8_t)szFormat[SetItr]] = bSetVal;
			SetItr++;
		}
		if (szFormat[SetItr] == L'\0')
			ret = sf_convtype::error;
		*pLength = SetItr;
		break;
	default:
		*pLength = 0;
		break;
	}

	return ret;
}

static bool IsSuppressed(const wchar_t* szFormat, uint64_t* pLength)
{
	bool bRet = szFormat[0] == L'*';
	*pLength = bRet ? 1 : 0;
	return bRet;
}
static bool HasFieldWidth(const wchar_t* szFormat, uint64_t* pLength, uint64_t* pWidth)
{
	bool bRet = false;
	size_t itr = 0;
	*pWidth = 4095;
	if (iswdigit(szFormat[itr]) != 0)
	{
		uint64_t width = 0;
		do
		{
			width = (width * 10) + (uint64_t)(szFormat[itr] - L'0');
			itr++;
		} while (iswdigit(szFormat[itr]) != 0);
		*pWidth = width;
		bRet = true;
	}
	*pLength = itr;
	return bRet;
}

static bool ScanByParams(
	FILE* stream,
	bool bSuppressed,
	uint64_t* pqwWidth,
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	wchar_t* pOutBuffer,
	int* pnReadCount
)
{
	bool bRet = false;
	*pnReadCount = 0;
	switch (convtype)
	{
	case sf_convtype::decimal:
		bRet = ScannerStrGeneric(stream, ScopeCheckDec, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_oct:
		bRet = ScannerStrGeneric(stream, ScopeCheckOct, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_unsigned:
		bRet = ScannerStrGeneric(stream, ScopeCheckDec, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_hex:
		bRet = ScannerStrGeneric(stream, ScopeCheckHex, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
		bRet = ScannerStrGeneric(stream, ScopeCheckFloatCombined, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::charconv:
		if (*pqwWidth == 4095)
			*pqwWidth = 1;
		bRet = ScannerStrGenericAbsolute(stream, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::string:
		bRet = ScannerStrGeneric(stream, ScopeCheckString, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::pointer:
		bRet = ScannerStrGeneric(stream, ScopeCheckHex, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::n:
		bRet = true;
		break;
	case sf_convtype::percent:
		pOutBuffer[0] = L'%';
		pOutBuffer[1] = L'\n';
		break;
	case sf_convtype::set:
		//TODO: finish this
		break;
	case sf_convtype::noconv:
	case sf_convtype::error:
	case sf_convtype::unknown:
	default:
		break;
	}
	return bRet;
}

struct ParamConversionCtx
{
	union
	{
		wchar_t* szStr;
		uint64_t u64;
		int64_t i64;
		long double ldbl;
	};
	size_t size;

};

ParamConversionCtx ConvertParam(
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	wchar_t* pBuffer)
{
	ParamConversionCtx ret;
	switch (convtype)
	{
	case sf_convtype::decimal:
		ret.i64 = wcstoll(pBuffer, 0, 10);
		break;
	case sf_convtype::udecimal_oct:
		ret.i64 = wcstoll(pBuffer, 0, 8);
		break;
	case sf_convtype::udecimal_unsigned:
		ret.u64 = wcstoull(pBuffer, 0, 10);
		break;
	case sf_convtype::udecimal_hex:
	case sf_convtype::pointer:
		ret.u64 = wcstoull(pBuffer, 0, 16);
		break;
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
		ret.ldbl = wcstold(pBuffer, 0);
		break;
	case sf_convtype::charconv:
	case sf_convtype::string:
	case sf_convtype::percent:
		ret.szStr = pBuffer;
		break;
	case sf_convtype::noconv:
		//TODO: finish this
		break;
	case sf_convtype::set:
		//TODO: finish this
		break;
	default:
		break;
	}
	return ret;
}

static void SaveParam(
	void* pDst,
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	ParamConversionCtx ctx
)
{
	uint64_t bytesize = 4;
	switch (bitwidth)
	{
	case sf_bitwidth::byte:
		bytesize = 1;
		break;
	case sf_bitwidth::word:
		bytesize = 2;
		break;
	case sf_bitwidth::dword:
		bytesize = 4;
		break;
	case sf_bitwidth::qword:
	case sf_bitwidth::imax:
	case sf_bitwidth::size:
	case sf_bitwidth::ptrdiff:
		bytesize = 8;
		break;
	case sf_bitwidth::longd:
#ifndef _WIN32
		bytesize = 10;
#else
		bytesize = 8;
#endif // !_WIN32

		break;
	default:
		break;
	}

	switch (convtype)
	{
	case sf_convtype::decimal:
		if (bytesize == 1)
			*(int8_t*)pDst = ctx.i64;
		else if (bytesize == 2)
			*(int16_t*)pDst = ctx.i64;
		else if (bytesize == 4)
			*(int32_t*)pDst = ctx.i64;
		else
			*(int64_t*)pDst = ctx.i64;
		break;
	case sf_convtype::udecimal_oct:
	case sf_convtype::udecimal_unsigned:
	case sf_convtype::udecimal_hex:
		memcpy(pDst, &ctx.u64, bytesize);
		break;
	case sf_convtype::pointer:
		memcpy(pDst, &ctx.u64, 8);
		break;
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
		if (bytesize == 10)
			*((long double*)pDst) = ctx.ldbl;
		else if (bytesize == 8)
			*((double*)pDst) = ctx.ldbl;
		else
			*((float*)pDst) = ctx.ldbl;
		break;
	case sf_convtype::charconv:
	{
		wmemcpy((wchar_t*)pDst, ctx.szStr, ctx.size);
		break;
	}
	case sf_convtype::string:
	case sf_convtype::percent:
	{
		wchar_t* chh = (wchar_t*)pDst;
		wcscpy(chh, ctx.szStr);
		break;
	}
	case sf_convtype::set:
		//TODO: scanf, set, finish this
		break;
	default:
		break;
	}

}

int vfwscanf(FILE* restrict stream,
	const wchar_t* restrict format,
	va_list arg)
{
	va_list lstdup;
	va_copy(lstdup, arg);
	int nRet = 0;
	const wchar_t* fmt = format;

	size_t count = 0;
	bool bSet[256];
	wchar_t innerbuffer[4096];

	while (*fmt)
	{
		if (*fmt == L' ')
		{
			int nReadCount = 0;
			WhitespaceDirective(stream, &nReadCount);
			count += nReadCount;
			fmt++;
		}
		else if (*fmt == L'%')
		{
			void* ptr;
			fmt++;
			uint64_t qwTmp = 0;
			uint64_t qwWidth = 0;
			int nReadCount = 0;
			bool bSuppressed = IsSuppressed(fmt, &qwTmp);
			fmt += qwTmp;
			HasFieldWidth(fmt, &qwTmp, &qwWidth);
			fmt += qwTmp;
			sf_bitwidth bitwidth = ParseWidth(fmt, &qwTmp);
			fmt += qwTmp;
			sf_convtype convtype = ParseType(fmt, &qwTmp, bSet);
			if (convtype != sf_convtype::percent)
			{
				memset(innerbuffer, 0, sizeof(innerbuffer));
				if (!ScanByParams(stream, bSuppressed, &qwWidth, bitwidth, convtype, innerbuffer, &nReadCount))
				{
					nRet = EOF;
					break;
				}

				count += nReadCount;

				if (convtype == sf_convtype::n)
				{
					int* p = va_arg(lstdup, int*);
					*p = count;
					nRet++;
				}
				else
				{
					if (!bSuppressed)
					{
						ptr = va_arg(lstdup, void*);
						ParamConversionCtx pcctx = ConvertParam(bitwidth, convtype, innerbuffer);
						pcctx.size = qwWidth;
						SaveParam(ptr, bitwidth, convtype, pcctx);
						nRet++;
					}
				}
			}
			else
			{
				nReadCount = 0;
				int nPrecent;
				nPrecent = getwc(stream);
				nReadCount++;
				while (nPrecent != EOF && nPrecent != L'%')
				{
					nReadCount++;
					nPrecent = getwc(stream);
				}
				count += nReadCount;
			}
			fmt++;
			//printf("nRet = [%d], vfscanf n=[%zu]\n", nRet, count);
		}
		else
		{
			nRet = EOF;
			break;
		}
	}

	va_end(lstdup);
	return nRet;
}

int fwscanf(FILE* restrict stream,
	const wchar_t* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vfwscanf(stream, format, valist);
	va_end(valist);
	return nRet;
}

int wscanf(const wchar_t* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vfwscanf(stdin, format, valist);
	va_end(valist);
	return nRet;
}

int vwscanf(const wchar_t* restrict format,
	va_list arg)
{
	return vfwscanf(stdin, format, arg);
}


static bool ScannerStrGenericString(
	const wchar_t* s,
	procscopechk fScopeCheck,
	uint64_t qwCharLimit,
	wchar_t* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar = *s;
	scanners_scope_check_ctx ctx = { 0 };
	while (nChar != EOF && CharCount < qwCharLimit)
	{
		nChar = *s;
		if (!iswspace(nChar))
		{
			if (fScopeCheck(nChar, &ctx))
			{
				*pOutBuff = nChar;
				pOutBuff++;
				CharCount++;
				bRet = true;
			}
		}
		else
		{
			break;
		}
		s++;

	}
	*pOutBuff = L'\0';
	*pnReadCount = CharCount;
	return bRet;
}
static bool ScannerStrGenericStringAbsolute(
	const wchar_t* s,
	uint64_t qwCharLimit,
	wchar_t* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar = *s;
	while (nChar != EOF && CharCount < qwCharLimit)
	{
		nChar = *s;
		*pOutBuff = nChar;
		pOutBuff++;
		CharCount++;
		bRet = true;
		s++;

	}
	*pOutBuff = L'\0';
	*pnReadCount = CharCount;
	return bRet;
}

static bool ScanByParamsString(
	const wchar_t* s,
	bool bSuppressed,
	uint64_t* pqwWidth,
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	wchar_t* pOutBuffer,
	int* pnReadCount
)
{
	bool bRet = false;
	*pnReadCount = 0;
	switch (convtype)
	{
	case sf_convtype::decimal:
		bRet = ScannerStrGenericString(s, ScopeCheckDec, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_oct:
		bRet = ScannerStrGenericString(s, ScopeCheckOct, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_unsigned:
		bRet = ScannerStrGenericString(s, ScopeCheckDec, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::udecimal_hex:
		bRet = ScannerStrGenericString(s, ScopeCheckHex, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
		bRet = ScannerStrGenericString(s, ScopeCheckFloatCombined, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::charconv:
		if (*pqwWidth == 4095)
			*pqwWidth = 1;
		bRet = ScannerStrGenericStringAbsolute(s, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::string:
		bRet = ScannerStrGenericString(s, ScopeCheckString, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::pointer:
		bRet = ScannerStrGenericString(s, ScopeCheckHex, *pqwWidth, pOutBuffer, pnReadCount);
		break;
	case sf_convtype::n:
		bRet = true;
		break;
	case sf_convtype::percent:
		pOutBuffer[0] = L'%';
		pOutBuffer[1] = L'\n';
		bRet = true;
		break;
	case sf_convtype::set:
		//TODO: wscanf, set,  finish this
		break;
	case sf_convtype::noconv:
	case sf_convtype::error:
	case sf_convtype::unknown:
	default:
		break;
	}
	return bRet;
}

static void WhitespaceDirectiveString(const wchar_t* s, int* pnCount)
{
	int nChar = *s;
	int nCount = 0;
	while (iswspace(nChar) != 0)
	{
		s++;
		nChar = *s;
		nCount++;
	}
	*pnCount = nCount;
}

int vswscanf(const wchar_t* restrict s,
	const wchar_t* restrict format,
	va_list arg)
{
	va_list lstdup;
	va_copy(lstdup, arg);
	int nRet = 0;
	const wchar_t* fmt = format;

	size_t count = 0;
	bool bSet[256];
	wchar_t innerbuffer[4096];


	while (*fmt)
	{
		if (*fmt == L' ')
		{
			int nReadCount = 0;
			WhitespaceDirectiveString(s, &nReadCount);
			count += nReadCount;
			fmt++;
			s += nReadCount;
		}
		else if (*fmt == L'%')
		{
			void* ptr;
			fmt++;
			uint64_t qwTmp = 0;
			uint64_t qwWidth = 0;
			int nReadCount = 0;
			bool bSuppressed = IsSuppressed(fmt, &qwTmp);
			fmt += qwTmp;
			HasFieldWidth(fmt, &qwTmp, &qwWidth);
			fmt += qwTmp;
			sf_bitwidth bitwidth = ParseWidth(fmt, &qwTmp);
			fmt += qwTmp;
			sf_convtype convtype = ParseType(fmt, &qwTmp, bSet);
			if (convtype != sf_convtype::percent)
			{
				memset(innerbuffer, 0, sizeof(innerbuffer));
				if (!ScanByParamsString(s, bSuppressed, &qwWidth, bitwidth, convtype, innerbuffer, &nReadCount))
				{
					nRet = EOF;
					break;
				}
				s += nReadCount;

				count += nReadCount;

				if (convtype == sf_convtype::n)
				{
					int* p = va_arg(lstdup, int*);
					*p = count;
					nRet++;
				}
				else
				{
					if (!bSuppressed)
					{
						ptr = va_arg(lstdup, void*);
						ParamConversionCtx pcctx = ConvertParam(bitwidth, convtype, innerbuffer);
						pcctx.size = qwWidth;
						SaveParam(ptr, bitwidth, convtype, pcctx);
						nRet++;
					}
				}
			}
			else
			{
				nReadCount = 0;
				wchar_t* pPrecent = wcschr(s, L'%');
				if (pPrecent)
				{
					nReadCount = pPrecent - s + 1;

				}
				s += nReadCount;
				count += nReadCount;
			}
			fmt++;
			//printf("nRet = [%d], vsscanf n=[%zu]\n", nRet, count);
		}
		else
		{
			nRet = EOF;
			break;
		}
	}

	va_end(lstdup);
	return nRet;
}
int swscanf(const wchar_t* restrict s,
	const wchar_t* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vswscanf(s, format, valist);
	va_end(valist);
	return nRet;
}