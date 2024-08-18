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
#include <include\ctype.h>
#include <include\errno.h>
#include <include\limits.h>

extern "C" 
{
int atoi(const char* nptr)
{
	int nRet = 0;
	bool bNeg = false;
	while (isspace(*nptr))
		nptr++;
	if (*nptr) {
		bNeg = *nptr == '-';
		if (bNeg || *nptr == '+')
			nptr++;

		while (isdigit(*nptr))
		{
			nRet = (nRet * 10) + (*nptr++ - '0');
		}
		if (bNeg)
			nRet = 0 - nRet;
	}
	return nRet;
}

long int atol(const char* nptr)
{
	long int nRet = 0;
	bool bNeg = false;
	while (isspace(*nptr))
		nptr++;
	if (*nptr) {
		bNeg = *nptr == '-';
		if (bNeg || *nptr == '+')
			nptr++;

		while (isdigit(*nptr))
		{
			nRet = (nRet * 10) + (*nptr++ - '0');
		}
		if (bNeg)
			nRet = 0 - nRet;
	}
	return nRet;
}
long long int atoll(const char* nptr)
{

	long long int nRet = 0;
	bool bNeg = false;
	while (isspace(*nptr))
		nptr++;
	if (*nptr) {
		bNeg = *nptr == '-';
		if (bNeg || *nptr == '+')
			nptr++;

		while (isdigit(*nptr))
		{
			nRet = (nRet * 10) + (*nptr++ - '0');
		}
		if (bNeg)
			nRet = 0 - nRet;
	}
	return nRet;
}
/*
extern "C" double atof(const char* nptr)
{

}
*/
inline static int CharToNum(char c)
{
	int nRet;
	if (isdigit(c) == true)
		nRet = c - '0';
	else if (isupper(c) == true)
		nRet = c - 'A' + 10;
	else if (islower(c) == true)
		nRet = c - 'a' + 10;
	else
		nRet = -1;
	return nRet;
}
static bool IsPartOfBase(int n, int base)
{
	return (n >= 0) && (n < base);
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
long int strtol(
	const char* restrict nptr,
	char** restrict endptr,
	int base)
{
	long int nRet;
	long long int llnRet = strtoll(nptr, endptr, base);
	if (llnRet < LONG_MIN)
		nRet = LONG_MIN;
	else if (llnRet > LONG_MAX)
		nRet = LONG_MAX;
	else
		nRet = llnRet;
	return nRet;
}
long long int strtoll(
	const char* restrict nptr,
	char** restrict endptr,
	int base)
{
	long long int qwRet = 0;
	bool bFlow = false;
	int nTmp;
	bool bNeg = false;
	while (isspace(*nptr))
		nptr++;
	if (*nptr) {
		errno = 0;
		bNeg = *nptr == '-';
		if (bNeg || *nptr == '+')
			nptr++;

		if (base == 16)
		{
			if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			{
				nptr += 2;
				base = 16;
			}
		}
		else if (base == 0)
		{
			if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			{
				nptr += 2;
				base = 16;
			}
			else if (*nptr == '0')
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
			*endptr = (char*)(nptr - 1);
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
unsigned long int strtoul(
	const char* restrict nptr,
	char** restrict endptr,
	int base)
{
	unsigned long int nRet;
	unsigned long long int lluRet = strtoull(nptr, endptr, base);
	if (lluRet > ULONG_MAX)
		nRet = ULONG_MAX;
	else
		nRet = lluRet;
	return nRet;
}
unsigned long long int strtoull(
	const char* restrict nptr,
	char** restrict endptr,
	int base)
{
	unsigned long long int qwRet = 0;
	unsigned long long int qwPrevRet = 0;
	bool bFlow = false;
	int nTmp;
	while (isspace(*nptr))
		nptr++;
	if (*nptr) {
		if (*nptr == '+')
			nptr++;

		if (base == 16)
		{
			if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			{
				nptr += 2;
				base = 16;
			}
		}
		else if (base == 0)
		{
			if (*nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
			{
				nptr += 2;
				base = 16;
			}
			else if (*nptr == '0')
				base = 8;
			else
				base = 10;
		}

		nTmp = CharToNum(*(nptr++));
		while (IsPartOfBase(nTmp, base) == true)
		{
			qwRet = (qwRet * base) + nTmp;
			if (qwRet < qwPrevRet || ((qwRet == qwPrevRet) && (qwRet != 0)) )
				bFlow = true;
			qwPrevRet = qwRet;
			nTmp = CharToNum(*(nptr++));
		}
		if (endptr)
			*endptr = (char*)(nptr - 1);

		errno = 0;
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