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
#include <include\wchar.h>
#include <include\wctype.h>
#include <include\errno.h>
#include <include\limits.h>

extern "C"
{

inline static int CharToNum(wchar_t c)
{
	int nRet;
	if (iswdigit(c) == true)
		nRet = c - L'0';
	else if (iswupper(c) == true)
		nRet = c - L'A' + 10;
	else if (iswlower(c) == true)
		nRet = c - L'a' + 10;
	else
		nRet = -1;
	return nRet;
}
static bool IsPartOfBase(int n, int base)
{
	return (n >= 0) && ((n) < base);
}
/*
static bool FlowDetect(long int n1, long int nprev)
{
	// n1 ^ nprev will have different signs on overflow/underflow
	long int sign = (n1 ^ nprev) & (1 << 31);
	return sign != 0;

}
*/
//269
long int wcstol(
	const wchar_t* restrict nptr,
	wchar_t** restrict endptr,
	int base)
{
	long int nRet;
	long long int llnRet = wcstoll(nptr, endptr, base);
	if (llnRet < LONG_MIN)
		nRet = LONG_MIN;
	else if (llnRet > LONG_MAX)
		nRet = LONG_MAX;
	else
		nRet = llnRet;
	return nRet;
}
long long int wcstoll(
	const wchar_t* restrict nptr,
	wchar_t** restrict endptr,
	int base)
{
	errno = 0;
	long long int qwRet = 0;
	bool bFlow = false;
	int nTmp;
	bool bNeg = false;
	while (iswspace(*nptr))
		nptr++;
	if (*nptr) {
		bNeg = *nptr == L'-';
		if (bNeg || *nptr == L'+')
			nptr++;

		if (base == 16)
		{
			if (*nptr == L'0' && (nptr[1] == L'x' || nptr[1] == L'X'))
			{
				nptr += 2;
				base = 16;
			}
		}
		else if (base == 0)
		{
			if (*nptr == L'0' && (nptr[1] == L'x' || nptr[1] == L'X'))
			{
				nptr += 2;
				base = 16;
			}
			else if (*nptr == L'0')
				base = 8;
			else
				base = 10;
		}

		nTmp = CharToNum(*nptr++);
		while (IsPartOfBase(nTmp, base) == true)
		{
			qwRet = (qwRet * base) + nTmp;
			if (qwRet & (1ll << (sizeof(long long int) * 8 - 1)))
				bFlow = true;
			nTmp = CharToNum(*nptr++);
		}
		if (endptr)
			*endptr = (wchar_t*)(nptr - 1);
		if (bNeg)
			qwRet = -qwRet;


		if (bFlow)
		{
			if (bNeg)
				qwRet = LLONG_MIN;
			else
				qwRet = LLONG_MAX;
			errno = ERANGE;
		}
	}
	else
		errno = EINVAL;
	return qwRet;
}
unsigned long int wcstoul(
	const wchar_t* restrict nptr,
	wchar_t** restrict endptr,
	int base)
{
	unsigned long int nRet;
	unsigned long long int lluRet = wcstoull(nptr, endptr, base);
	if (lluRet > ULONG_MAX)
		nRet = ULONG_MAX;
	else
		nRet = lluRet;
	return nRet;
}
unsigned long long int wcstoull(
	const wchar_t* restrict nptr,
	wchar_t** restrict endptr,
	int base)
{
	errno = 0;
	unsigned long long int qwRet = 0;
	unsigned long long int qwPrevRet = 0;
	bool bFlow = false;
	int nTmp;
	while (iswspace(*nptr))
		nptr++;
	if (*nptr) {
		if (*nptr == L'+')
			nptr++;

		if (base == 16)
		{
			if (*nptr == L'0' && (nptr[1] == L'x' || nptr[1] == L'X'))
			{
				nptr += 2;
				base = 16;
			}
		}
		else if (base == 0)
		{
			if (*nptr == L'0' && (nptr[1] == L'x' || nptr[1] == L'X'))
			{
				nptr += 2;
				base = 16;
			}
			else if (*nptr == L'0')
				base = 8;
			else
				base = 10;
		}

		nTmp = CharToNum(*nptr++);
		while (IsPartOfBase(nTmp, base) == true)
		{
			qwRet = (qwRet * base) + nTmp;
			if (qwRet < qwPrevRet)
				bFlow = true;
			qwPrevRet = qwRet;
			nTmp = CharToNum(*nptr++);
		}
		if (endptr)
			*endptr = (wchar_t*)(nptr - 1);

		if (bFlow)
		{
			qwRet = ULLONG_MAX;
			errno = ERANGE;
		}
	}
	else
		errno = EINVAL;
	return qwRet;
}

}