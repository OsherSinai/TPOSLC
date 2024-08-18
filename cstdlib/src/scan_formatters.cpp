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
#include <include\stddef.h>
#include <include\stdint.h>
#include <include\ctype.h>
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
	char chFirstTwo[2];
	uint8_t FirstTwoCount;
};

typedef bool (*procscopechk)(int n, scanners_scope_check_ctx* pctx);

static bool ScopeCheckDec(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n == '+' || n == '-')
	{
		if (pctx->bSign)
			bRet = false;
		pctx->bSign = true;
	}
	else if (isdigit(n) == 0)
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
	else if (n != '0' && !pctx->bPrefix1)
		bRet = false;
	else if (n == '0' && !pctx->bPrefix1)
		pctx->bPrefix1 = true;
	else if (tolower(n) != 'x' && !pctx->bPrefix2)
		bRet = false;
	else if (tolower(n) == 'x' && !pctx->bPrefix2)
		pctx->bPrefix2 = true;
	else if (isxdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckOct(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n == '+' || n == '-')
	{
		if (pctx->bSign)
			bRet = false;
		pctx->bSign = true;
	}
	else if (isdigit(n) == 0 || tolower(n) >= 'g')
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatDec(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	//nan
	//inf, infinity
	if (n == '+' || n == '-')
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
	else if (n == '.')
	{
		if (pctx->bPoint)
			bRet = false;
		pctx->bPoint = true;
	}
	else if (tolower(n) == ('e'))
	{
		if (pctx->bExponent)
			bRet = false;
		pctx->bExponent = true;
	}
	else if (isdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatHex(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	//nan
	//inf, infinity
	if (n == '+' || n == '-')
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
	else if (n != '0' && !pctx->bPrefix1)
		bRet = false;
	else if (n == '0' && !pctx->bPrefix1)
		pctx->bPrefix1 = true;
	else if (tolower(n) != 'x' && !pctx->bPrefix2)
		bRet = false;
	else if (tolower(n) == 'x' && !pctx->bPrefix2)
		pctx->bPrefix2 = true;
	else if (n == '.')
	{
		if (pctx->bPoint)
			bRet = false;
		pctx->bPoint = true;
	}
	else if (tolower(n) == ('p'))
	{
		if (pctx->bExponent)
			bRet = false;
		pctx->bExponent = true;
	}
	else if (isxdigit(n) == 0)
		bRet = false;
	return bRet;
}
static bool ScopeCheckFloatCombined(int n, scanners_scope_check_ctx* pctx)
{
	bool bRet = true;
	if (n != '-' && n != '+')
	{
		if (pctx->FirstTwoCount == 0)
		{
			if ((char)n != '0')
			{
				pctx->bNotHex = true;
				pctx->FirstTwoCount++;
			}
			pctx->FirstTwoCount++;
		}
		else if (pctx->FirstTwoCount == 1)
		{
			if ((char)tolower(n) != 'x')
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
	char* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar;
	scanners_scope_check_ctx ctx = { 0 };
	do
	{
		nChar = getc(stream);
		if (!isspace(nChar))
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
			ungetc(nChar, stream);
			break;
		}

	} while (nChar != EOF && CharCount < qwCharLimit);
	*pOutBuff = '\0';
	*pnReadCount = CharCount;
	return bRet;
}

static bool ScannerStrGenericAbsolute(
	FILE* stream,
	uint64_t qwCharLimit,
	char* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar;
	do
	{
		nChar = getc(stream);
		if (nChar != EOF)
		{
			*pOutBuff = nChar;
			pOutBuff++;
			CharCount++;
			bRet = true;
		}

	} while (nChar != EOF && CharCount < qwCharLimit);
	*pOutBuff = '\0';
	*pnReadCount = CharCount;
	return bRet;
}

static void WhitespaceDirective(FILE* stream, int* pnCount)
{
	int nChar;
	int nCount = -1;
	do
	{
		nChar = getc(stream);
		nCount++;
	} while (isspace(nChar) != 0);
	ungetc(nChar, stream);
	*pnCount = nCount;
}

static sf_bitwidth ParseWidth(const char* szFormat, uint64_t* pLength)
{
	sf_bitwidth ret = sf_bitwidth::unknown;
	*pLength = 1;
	switch (szFormat[0])
	{
	case 'h':
		if (szFormat[1] == 'h')
		{
			ret = sf_bitwidth::byte;
			*pLength = 2;
		}
		else
			ret = sf_bitwidth::word;
		break;
	case 'l':
		if (szFormat[1] == 'l')
		{
			ret = sf_bitwidth::qword;
			*pLength = 2;
		}
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
	default:
		*pLength = 0;
		break;
	}
	return ret;
}

static sf_convtype ParseType(
	const char* szFormat, uint64_t* pLength,
	bool pbSet[256])
{
	sf_convtype ret = sf_convtype::unknown;
	size_t SetCount = 0;
	size_t SetItr = 1;
	bool bSetVal = true;
	*pLength = 1;
	switch (szFormat[0])
	{
	case '%':
		ret = sf_convtype::percent;
		break;
	case 'c':
		ret = sf_convtype::charconv;
		break;
	case 's':
		ret = sf_convtype::string;
		break;
	case 'd':
		ret = sf_convtype::decimal;
		break;
	case 'i':
		ret = sf_convtype::decimal;
		break;
	case 'u':
		ret = sf_convtype::udecimal_unsigned;
		break;
	case 'o':
		ret = sf_convtype::udecimal_oct;
		break;
	case 'x':
		ret = sf_convtype::udecimal_hex;
		break;
	case 'X':
		ret = sf_convtype::udecimal_hex;
		break;
	case 'n':
		ret = sf_convtype::n;
		break;
	case 'a':
	case 'A':
	case 'e':
	case 'E':
	case 'f':
	case 'F':
	case 'g':
	case 'G':
		ret = sf_convtype::double_dec_or_exp;
		break;
	case 'p':
		ret = sf_convtype::pointer;
		break;
	case '[':
		ret = sf_convtype::set;
		if (szFormat[SetItr] == '^')
		{
			bSetVal = false;
			SetItr++;
		}
		memset(pbSet, !bSetVal, sizeof(bool) * 256);
		//TODO: finish implementing this in a conformant way
		while (szFormat[SetItr] != ']' && szFormat[SetItr] != '\0')
		{
			for (size_t i = 0; i < SetCount; i++)
				pbSet[(uint8_t)szFormat[SetItr]] = bSetVal;
			SetItr++;
		}
		if (szFormat[SetItr] == '\0')
			ret = sf_convtype::error;
		*pLength = SetItr;
		break;
	default:
		*pLength = 0;
		break;
	}

	return ret;
}

static bool IsSuppressed(const char* szFormat, uint64_t* pLength)
{
	bool bRet = szFormat[0] == '*';
	*pLength = bRet ? 1 : 0;
	return bRet;
}
static bool HasFieldWidth(const char* szFormat, uint64_t* pLength, uint64_t* pWidth)
{
	bool bRet = false;
	size_t itr = 0;
	*pWidth = 4095;
	if (isdigit(szFormat[itr]) != 0)
	{
		uint64_t width = 0;
		do
		{
			width = (width * 10) + (uint64_t)(szFormat[itr] - '0');
			itr++;
		} while (isdigit(szFormat[itr]) != 0);
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
	char* pOutBuffer,
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
		pOutBuffer[0] = '%';
		pOutBuffer[1] = '\n';
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
		char* szStr;
		uint64_t u64;
		int64_t i64;
		long double ldbl;
	};
	size_t size;

};

ParamConversionCtx ConvertParam(
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	char* pBuffer)
{
	ParamConversionCtx ret;
	switch (convtype)
	{
	case sf_convtype::decimal:
		ret.i64 = strtoll(pBuffer, 0, 10);
		break;
	case sf_convtype::udecimal_oct:
		ret.i64 = strtoll(pBuffer, 0, 8);
		break;
	case sf_convtype::udecimal_unsigned:
		ret.u64 = strtoull(pBuffer, 0, 10);
		break;
	case sf_convtype::udecimal_hex:
	case sf_convtype::pointer:
		ret.u64 = strtoull(pBuffer, 0, 16);
		break;
	case sf_convtype::double_dec:
	case sf_convtype::double_exponent:
	case sf_convtype::double_dec_or_exp:
	case sf_convtype::double_hex_exp:
		ret.ldbl = strtold(pBuffer, 0);
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
		memcpy(pDst, ctx.szStr, ctx.size);
		break;
	}
	case sf_convtype::string:
	case sf_convtype::percent:
	{
		char* chh = (char*)pDst;
		strcpy(chh, ctx.szStr);
		break;
	}
	case sf_convtype::set:
		//TODO: finish this
		break;
	default:
		break;
	}

}

int vfscanf(FILE* restrict stream,
	const char* restrict format,
	va_list arg)
{
	va_list lstdup;
	va_copy(lstdup, arg);
	int nRet = 0;
	const char* fmt = format;

	size_t count = 0;
	bool bSet[256];
	char innerbuffer[4096];

	//TODO: copy the other to here
	while (*fmt)
	{
		if (*fmt == ' ')
		{
			int nReadCount = 0;
			WhitespaceDirective(stream, &nReadCount);
			count += nReadCount;
			fmt++;
		}
		else if (*fmt == '%')
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
				nPrecent = getc(stream);
				nReadCount++;
				while(nPrecent != EOF && nPrecent != '%')
				{
					nReadCount++;
					nPrecent = getc(stream);
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

int fscanf(FILE* restrict stream,
	const char* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vfscanf(stream, format, valist);
	va_end(valist);
	return nRet;
}

int scanf(const char* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vfscanf(stdin, format, valist);
	va_end(valist);
	return nRet;
}

int vscanf(const char* restrict format,
	va_list arg)
{
	return vfscanf(stdin, format, arg);
}


static bool ScannerStrGenericString(
	const char* s,
	procscopechk fScopeCheck,
	uint64_t qwCharLimit,
	char* pOutBuff,
	int* pnReadCount)
{
	bool bRet = false;
	uint64_t CharCount = 0;
	int nChar = *s;
	scanners_scope_check_ctx ctx = { 0 };
	while (nChar != EOF && CharCount < qwCharLimit)
	{
		nChar = *s;
		if (!isspace(nChar))
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
	*pOutBuff = '\0';
	*pnReadCount = CharCount;
	return bRet;
}
static bool ScannerStrGenericStringAbsolute(
	const char* s,
	uint64_t qwCharLimit,
	char* pOutBuff,
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
	*pOutBuff = '\0';
	*pnReadCount = CharCount;
	return bRet;
}

static bool ScanByParamsString(
	const char* s,
	bool bSuppressed,
	uint64_t* pqwWidth,
	sf_bitwidth bitwidth,
	sf_convtype convtype,
	char* pOutBuffer,
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
		pOutBuffer[0] = '%';
		pOutBuffer[1] = '\n';
		bRet = true;
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

static void WhitespaceDirectiveString(const char* s, int* pnCount)
{
	int nChar = *s;
	int nCount = 0;
	while (isspace(nChar) != 0)
	{
		s++;
		nChar = *s;
		nCount++;
	}
	*pnCount = nCount;
}

int vsscanf(const char* restrict s,
	const char* restrict format,
	va_list arg)
{
	va_list lstdup;
	va_copy(lstdup, arg);
	int nRet = 0;
	const char* fmt = format;

	size_t count = 0;
	bool bSet[256];
	char innerbuffer[4096];


	while (*fmt)
	{
		if (*fmt == ' ')
		{
			int nReadCount = 0;
			WhitespaceDirectiveString(s, &nReadCount);
			count += nReadCount;
			fmt++;
			s += nReadCount;
		}
		else if (*fmt == '%')
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
				char* pPrecent = strchr(s, '%');
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
int sscanf(const char* restrict s,
	const char* restrict format, ...)
{
	int nRet;
	va_list valist;
	va_start(valist, format);
	nRet = vsscanf(s, format, valist);
	va_end(valist);
	return nRet;
}