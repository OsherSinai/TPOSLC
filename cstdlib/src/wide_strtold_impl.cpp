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
#include <include\stdlib.h>
#include <include\string.h>
#include <include\wchar.h>
#include <include\wctype.h>
#include <include\math.h>
#include <include\float.h>
#include "VariableSizeMath.h"
#include "IEEE754Parsers.h"
#include "x87_float.h"

static void SetFPBit(size_t bit, uint64_t* p)
{
	uint64_t uval = 1;
	uint64_t shiftby = bit % 64;
	uint64_t idx = bit / 64;

	uval <<= shiftby;
	p[idx] |= uval;
}

static long double cstm_wcstold_construct_ldbl(int64_t exp, uint64_t fraq)
{
	if constexpr (sizeof(long double) == 10)
	{
		x87_long_double d;
		fraq = fraq >> 1;
		d.bitfield.sign = 0;
		d.bitfield.exponent = (exp)+16383;
		d.bitfield.fraction = fraq;
		d.bitfield.intpart = 0;
		return d.val;
	}
	else
	{
		x87_double d;
		fraq = fraq >> 12;
		d.bitfield.sign = 0;
		d.bitfield.exponent = (exp)+1023;
		d.bitfield.fraction = fraq;
		return d.val;
	}
}


static void cstm_wcstold_set_fraq_nibble(dbltofx_inner* pState, uint64_t nib, uint64_t val)
{
	//64bit = 16 nibbles so 0xF
	uint64_t shift = 60 - ((nib & 0xf) << 2);
	int64_t ndx = -1 - ((int64_t)(nib >> 4));

	pState->num[ndx] &= ~(0xFllu << shift);
	pState->num[ndx] |= (val << shift);
}

[[nodiscard("cstm_strtold_CreateNormalizedString")]] static  wchar_t* cstm_wcstold_CreateNormalizedString(const wchar_t* str, wchar_t** ppEnd)
{
	wchar_t* szRet = nullptr;
	const wchar_t* szInt = str;
	const wchar_t* szFraq = nullptr;
	//const wchar_t* szExp = nullptr;
	int64_t exponent = 0;
	int64_t IntLen = 0;
	int64_t FraqLen = 0;
	size_t TotalSize = 0;

	while (*str && iswdigit(*str) != 0)
		str++;
	IntLen = (size_t)(str - szInt);

	if (*str == L'.')
	{
		str++;
		szFraq = str;
		while (*str && iswdigit(*str) != 0)
			str++;
		FraqLen = (size_t)(str - szFraq);
	}

	if (*str == L'e' || *str == L'E')
	{
		bool mexp = false;
		str++;
		//szExp = str;
		if (*str == L'-')
		{
			mexp = true;
			str++;
		}
		else if (*str == L'+')
		{
			str++;
		}
		while (*str && iswdigit(*str) != 0)
		{
			exponent *= 10;
			exponent += *str - L'0';
			str++;
		}

		if (mexp)
			exponent = -exponent;
	}
	if (ppEnd)
		*ppEnd = (wchar_t*)str;
	TotalSize = IntLen + FraqLen;
	if (exponent > 0 && exponent > FraqLen)
		TotalSize = TotalSize + (exponent - FraqLen);
	else if (exponent < 0 && llabs(exponent) > IntLen)
		TotalSize = TotalSize + (llabs(exponent) - IntLen);

	szRet = (wchar_t*)malloc(TotalSize + 2);
	if (szRet)
	{
		int64_t qwDot = IntLen + exponent;
		int64_t it = 0;
		memset(szRet, 0, TotalSize + 2);

		if (qwDot < 0)
		{
			szRet[it] = '.';
			it++;
			int64_t ab = llabs(qwDot);
			for (size_t i = 0; i < ab; i++)
			{
				if (it == qwDot)
				{
					szRet[it] = L'.';
					it++;
				}
				szRet[it] = L'0';
				it++;
			}
		}

		for (int64_t i = 0; i < IntLen; i++)
		{
			if (it == qwDot)
			{
				szRet[it] = L'.';
				it++;
			}
			szRet[it] = szInt[i];
			it++;
		}
		for (int64_t i = 0; i < FraqLen; i++)
		{
			if (it == qwDot)
			{
				szRet[it] = L'.';
				it++;
			}
			szRet[it] = szFraq[i];
			it++;
		}

		for (; it < TotalSize + 1; it++)
		{
			if (it == qwDot)
			{
				szRet[it] = L'.';
			}
			else
				szRet[it] = L'0';
		}
	}

	return szRet;
}

static bool chk_overflow(dbltofx_inner* pNum)
{
	//constexpr size_t c_MaxSetBit = DBL_MAX_EXP;
	constexpr size_t c_LimitIdx = pNum->numlen / 2;
	//constexpr size_t c_Limit = pNum->numlen * 64;
	bool bRet = false;

	for (size_t i = c_LimitIdx; i < pNum->numlen && bRet == false; i++)
		bRet = pNum->num[i] != 0;

	return bRet;
}

static void cstm_wcstold_dec(const wchar_t* str, long double* pRet, wchar_t** endptr)
{
	//base 10
	/*
	decimal-floating-constant:
		fractional-constant exponent-partopt floating-suffixopt
		digit-sequence exponent-part floating-suffixopt

	fractional-constant:
		digit-sequenceopt . digit-sequence
		digit-sequence .

	exponent-part:
		e signopt digit-sequence
		E signopt digit-sequence

	digit-sequence:
		digit
		digit-sequence digit

	floating-suffix: one of
		f l F L
	*/

	// use a full range bigints for this so we wont overflow
	dbl_to_str_state* pfp = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	memset(pfp, 0, sizeof(*pfp));
	bool bOverflow = false;
	wchar_t* szNormalized = cstm_wcstold_CreateNormalizedString(str, endptr);
	if (szNormalized)
	{
		wchar_t* szDup = szNormalized;
		while (*szDup && iswdigit(*szDup) != 0)
		{
			VariSizeMult64(pfp->fixed_point.num, 10, pfp->fixed_point.numlen);
			pfp->fraction_buffer_adder[0] = *szDup - L'0';
			VariSizeAdd64(pfp->fixed_point.num, pfp->fraction_buffer_adder, pfp->fixed_point.numlen);
			if (chk_overflow(&pfp->fixed_point))
			{
				bOverflow = true;
				break;
			}
			szDup++;
		}

		if (*szDup == '.' && !bOverflow)
		{
			uint64_t qwDigitCount = 0;
			szDup++;
			while (*szDup && iswdigit(*szDup) != 0)
			{
				VariSizeMult64(pfp->fraction_buffer_acc, 10, pfp->fixed_point.numlen);
				pfp->fraction_buffer_adder[0] = *szDup - L'0';
				VariSizeAdd64(pfp->fraction_buffer_acc, pfp->fraction_buffer_adder, pfp->fixed_point.numlen);
				qwDigitCount++;
				szDup++;
			}

			memset(pfp->fraction_buffer_adder, 0, sizeof(pfp->fraction_buffer_adder));
			pfp->fraction_buffer_adder[0] = 1;
			for (uint64_t i = 0; i < qwDigitCount; i++)
				VariSizeMult64(pfp->fraction_buffer_adder, 10, pfp->fixed_point.numlen);

			constexpr size_t BitCount = pfp->fixed_point.numlen * sizeof(uint64_t) * 8;
			for (size_t i = 0; i < BitCount; i++)
			{
				VariSizeMult64(pfp->fraction_buffer_acc, 2, pfp->fixed_point.numlen);
				if (VariSizeBiggerEq(pfp->fraction_buffer_acc, pfp->fraction_buffer_adder, pfp->fixed_point.numlen))
				{
					VariSizeSub64(pfp->fraction_buffer_acc, pfp->fraction_buffer_adder, pfp->fixed_point.numlen);
					SetFPBit((BitCount - 1) - i, pfp->fixed_point.frac);
				}
			}

		}

		if (endptr)
		{
			wchar_t* pch = *endptr;
			if (*pch == L'l' || *pch == L'f' || *pch == L'F' || *pch == L'L')
				(*endptr)++;
		}

		//TODO: validate if zero or inf

		int64_t exponent = 0;
		uint64_t fraq = 0;
		if (!bOverflow) {

			dbl_extract_values(&pfp->fixed_point, &exponent, &fraq);
			if ((fraq & (~0xFFFFFFFFFFFFF000llu)) > 0x7FF)
				fraq += 0x1000;
			if (exponent > 1024)
				*pRet = HUGE_VALL;
			if (exponent < -1024)
				*pRet = 0.;
			else
				*pRet = cstm_wcstold_construct_ldbl(exponent, fraq);
		}
		else
			*pRet = HUGE_VALL;


		free(szNormalized);
	}
	free(pfp);
}
static void cstm_wcstold_hex(const wchar_t* str, long double* pRet, wchar_t** endptr)
{
	//base 2
	/*
	hexadecimal-floating-constant:
		hexadecimal-prefix hexadecimal-fractional-constant
			binary-exponent-part floating-suffixop
		hexadecimal-prefix hexadecimal-digit-sequence
			binary-exponent-part floating-suffixopt

	hexadecimal-fractional-constant:
		hexadecimal-digit-sequenceopt .
			hexadecimal-digit-sequence
		hexadecimal-digit-sequence .

	binary-exponent-part:
		p signopt digit-sequence
		P signopt digit-sequence

	hexadecimal-digit-sequence:
		hexadecimal-digit
		hexadecimal-digit-sequence hexadecimal-digit

	floating-suffix: one of
		f l F L
	*/
	int64_t exponent = 0;

	// use a full range bigints for this so we wont overflow
	dbl_to_str_state* pfp = (dbl_to_str_state*)malloc(sizeof(dbl_to_str_state));
	memset(pfp, 0, sizeof(*pfp));

	//#error remove the string as we dont really need it
	const wchar_t* szNormalized = str;// cstm_strtold_CreateNormalizedString(str, endptr);
	if (szNormalized)
	{
		const wchar_t* szDup = szNormalized;
		while (*szDup && iswxdigit(*szDup) != 0)
		{
			VariSizeMult64(pfp->fixed_point.num, 16, pfp->fixed_point.numlen);
			if (iswdigit(*szDup) != 0)
			{
				pfp->fraction_buffer_adder[0] = *szDup - L'0';
			}
			else
			{
				wchar_t ch = towlower(*szDup);
				pfp->fraction_buffer_adder[0] = ((ch - L'a') + 10);
			}
			VariSizeAdd64(pfp->fixed_point.num, pfp->fraction_buffer_adder, pfp->fixed_point.numlen);
			szDup++;
		}

		if (*szDup == L'.')
		{
			uint64_t qwDigitCount = 0;
			szDup++;
			while (*szDup && iswxdigit(*szDup) != 0)
			{
				uint64_t nib;
				if (iswdigit(*szDup) != 0)
				{
					nib = *szDup - L'0';
				}
				else
				{
					wchar_t ch = towlower(*szDup);
					nib = ((ch - L'a') + 10);
				}
				cstm_wcstold_set_fraq_nibble(&pfp->fixed_point, qwDigitCount, nib);
				qwDigitCount++;
				szDup++;
			}
		}



		if (*szDup == L'p' || *szDup == L'P')
		{
			bool mexp = false;
			szDup++;
			if (*szDup == L'-')
			{
				mexp = true;
				szDup++;
			}
			else if (*szDup == L'+')
			{
				szDup++;
			}
			while (*szDup && iswdigit(*szDup) != 0)
			{
				exponent *= 10;
				exponent += *szDup - L'0';
				szDup++;
			}

			if (mexp)
				exponent = -exponent;
		}

		if (exponent > 0)
		{
			for (uint64_t i = 0; i < exponent; i++)
				VariSizeMult64(pfp->fixed_point.arr, 2, pfp->fixed_point.numlen * 2);
		}
		else if (exponent < 0)
		{
			int64_t absexpo = llabs(exponent);
			for (uint64_t i = 0; i < absexpo; i++)
				VariSizeDiv64(pfp->fixed_point.arr, 2, pfp->fixed_point.numlen * 2);
		}

		if (endptr)
		{
			*endptr = (wchar_t*)szDup;
			wchar_t* pch = *endptr;
			if (*pch == L'l' || *pch == L'f' || *pch == L'F' || *pch == L'L')
				(*endptr)++;
		}


		uint64_t fraq = 0;
		dbl_extract_values(&pfp->fixed_point, &exponent, &fraq);
		if ((fraq & (~0xFFFFFFFFFFFFF000llu)) > 0x7FF)
			fraq += 0x1000;
		if (exponent > 1024)
			*pRet = INFINITY;
		if (exponent < -1024)
			*pRet = 0.;
		else
			*pRet = cstm_wcstold_construct_ldbl(exponent, fraq);


	}
	free(pfp);
}

static void cstm_wcstold_speical(const wchar_t* str, long double* pRet, wchar_t** endptr)
{
	//speicaltype
	/*
	check inf/infinity
	check nan/nan(char_sequence)

	n-wchar_t-sequence:
		digit
		nondigit
		n-wchar_t-sequence digit
		n-wchar_t-sequence nondigit

	*/
	if (endptr)
		*endptr = (wchar_t*)str;
	if (towlower(str[0]) == L'i')
	{
		if (towlower(str[1]) == L'n')
		{
			if (towlower(str[2]) == L'f')
			{
				*pRet = HUGE_VALL;
				wchar_t* pr = (wchar_t*)&str[3];
				if ((towlower(str[3]) == L'i') &&
					(towlower(str[4]) == L'n') &&
					(towlower(str[5]) == L'i') &&
					(towlower(str[6]) == L't') &&
					(towlower(str[7]) == L'y'))
				{
					pr = (wchar_t*)&str[8];
				}
				if (endptr)
					*endptr = pr;
			}
		}
	}
	else if (towlower(str[0]) == L'n')
	{
		if (towlower(str[1]) == L'a')
		{
			if (towlower(str[2]) == L'n')
			{
				uint64_t tmp = 0;
				if constexpr (sizeof(long double) == 10)
				{
					*(uint64_t*)pRet = 0x0;
					*(((uint16_t*)pRet) + 4) = 0x7F'FF;
				}
				else
				{
					*(uint64_t*)pRet = 0x7F'F0'00'00'00'00'00'00;
				}
				wchar_t* pr = (wchar_t*)&str[3];
				if (endptr)
					*endptr = pr;
				if (pr[0] == L'(')
				{
					pr++;
					wchar_t* endptr2 = NULL;
					wchar_t* endptr3 = NULL;
					tmp = wcstoull(pr, &endptr2, 10);
					if (endptr2 == NULL || *endptr2 != L')')
					{
						tmp = wcstoull(pr, &endptr3, 16);
						if constexpr (sizeof(long double) == 10)
							*(uint64_t*)pRet = tmp;
						else
							*(uint64_t*)pRet |= tmp & 0x000F'FFFF'FFFF'FFFFllu;
						if (endptr)
						{
							endptr3++;
							*endptr = endptr3;
						}
					}
					else
					{
						if constexpr (sizeof(long double) == 10)
							*(uint64_t*)pRet = tmp;
						else
							*(uint64_t*)pRet |= tmp & 0x000F'FFFF'FFFF'FFFFllu;
						if (endptr)
						{
							endptr2++;
							*endptr = endptr2;
						}
					}
				}
				else
				{
					*pRet = NAN;
				}
			}
		}
	}
}


enum class cstm_atof_dotype {
	dec,
	hex,
	special
};
long double wcstold(const wchar_t* restrict nptr,
	wchar_t** restrict endptr)
{
	long double dret = 0.;
	bool bMinus = false;
	cstm_atof_dotype calltype = cstm_atof_dotype::dec;
	if (nptr)
	{
		while (iswspace(*nptr))nptr++;

		if (*nptr == L'-')
		{
			bMinus = true;
			nptr++;
		}
		else if (*nptr == L'+')
		{
			nptr++;
		}


		if (*nptr == L'0')
		{
			nptr++;
			if (*nptr == L'x' || *nptr == L'X')
			{
				calltype = cstm_atof_dotype::hex;
				nptr++;
			}
		}
		else if (iswdigit(*nptr) == 0)
		{
			calltype = cstm_atof_dotype::special;
		}

		switch (calltype)
		{
		case cstm_atof_dotype::dec:
			cstm_wcstold_dec(nptr, &dret, endptr);
			break;
		case cstm_atof_dotype::hex:
			cstm_wcstold_hex(nptr, &dret, endptr);
			break;
		case cstm_atof_dotype::special:
			cstm_wcstold_speical(nptr, &dret, endptr);
			break;
		}
		if (bMinus)
		{
			dret = -dret;
		}
	}

	return dret;
}


double wcstod(const wchar_t* restrict nptr,
	wchar_t** restrict endptr)
{
	double ret;
	long double rldbl = wcstold(nptr, endptr);
	ret = rldbl;
	if (isnan(rldbl))
	{
		if constexpr (sizeof(long double) == 10)
		{
			x87_long_double* ldbl = (x87_long_double*)&rldbl;
			x87_double* dbl = (x87_double*)&ret;
			dbl->bitfield.fraction = ldbl->bitfield.fraction;
		}
		if ((isnan(ret)) == 0)
			ret = NAN;
	}
	return ret;
}
float wcstof(const wchar_t* restrict nptr,
	wchar_t** restrict endptr)
{
	float ret;
	long double rldbl = wcstold(nptr, endptr);
	ret = rldbl;
	if (isnan(rldbl))
	{
		if constexpr (sizeof(long double) == 10)
		{
			x87_long_double* ldbl = (x87_long_double*)&rldbl;
			x87_float* dbl = (x87_float*)&ret;
			dbl->bitfield.fraction = ldbl->bitfield.fraction;
		}
		else
		{
			x87_double* ldbl = (x87_double*)&rldbl;
			x87_float* flt = (x87_float*)&ret;
			flt->bitfield.fraction = ldbl->bitfield.fraction;
		}
		if ((isnan(ret)) == 0)
			ret = NAN;
	}
	return ret;
}
