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
#include <include\math.h>
#include <include\stdint.h>

int fpclassifyf(float x)
{
	int nRet = FP_SUBNORMAL;
	if ((isnan(x)))
		nRet = FP_NAN;
	else if (isinf(x))
		nRet = FP_INFINITE;
	else if((*(uint32_t*)&x & 0x7FFFFFFF) == 0)
		nRet = FP_ZERO;
	else if (isnormal(x))
		nRet = FP_NORMAL;
	return nRet;
}
int fpclassifyd(double x)
{
	int nRet = FP_SUBNORMAL;
	if ((isnan(x)))
		nRet = FP_NAN;
	else if (isinf(x))
		nRet = FP_INFINITE;
	else if ((*(uint64_t*)&x & 0x7FFFFFFFFFFFFFFFLLU) == 0)
		nRet = FP_ZERO;
	else if (isnormal(x))
		nRet = FP_NORMAL;
	return nRet;
}
int fpclassifyld(long double x)
{
	int nRet = FP_SUBNORMAL;
	if ((isnan(x)))
		nRet = FP_NAN;
	else if (isinf(x))
		nRet = FP_INFINITE;
	else
	{
		if (x == 0.l)
			nRet = FP_ZERO;
		else if (isnormal(x))
			nRet = FP_NORMAL;
	}
	return nRet;
}


int isfinitef(float x)
{
	return !(isnan(x)) && !isinf(x);
}
int isfinited(double x)
{
	return !(isnan(x)) && !isinf(x);
}
int isfiniteld(long double x)
{
	return !(isnan(x)) && !isinf(x);
}


int isinff(float x)
{
	constexpr uint32_t Mask = 0x7FFFFFFF;
	constexpr uint32_t Expected = 0x7F800000;
	return ((*(uint32_t*)&x) & Mask) == Expected;
}
int isinfd(double x)
{
	constexpr uint64_t Mask = 0x7FFFFFFFFFFFFFFFLLU;
	constexpr uint64_t Expected = 0x7FF0000000000000LLU;
	return ((*(uint64_t*)&x) & Mask) == Expected;
}
int isinfld(long double x)
{
	int isi = 0;
	if constexpr (sizeof(x) == 10)
	{
		uint64_t* frac = (uint64_t*)&x;
		uint16_t* exp = (uint16_t*)(frac + 1);
		if (*exp & 0x7FFF)
			isi = (*frac & 0x7FFFFFFFFFFFFFFFLLU) == 0;
	}
	else
	{
		isi = isinfd(x);
	}
	return isi;
}


int isnanf(float x)
{
	constexpr uint32_t Mask = 0x7FFFFFFF;
	constexpr uint32_t Mask2 = 0x7F800000;
	constexpr uint32_t Mask3 = ~0xFF800000;
	int isn = 0;
	uint32_t v = *(uint32_t*)&x;
	v &= Mask;// remove sign
	if ((v & Mask2) == Mask2) // is special
	{
		isn = (v & Mask3) != 0; // fraction is not zero
	}
	return isn;
}
int isnand(double x)
{

	constexpr uint64_t Mask = 0x7FFFFFFFFFFFFFFFLLU;
	constexpr uint64_t Mask2 = 0x7FF0000000000000LLU;
	constexpr uint64_t Mask3 = ~0xFFF0000000000000LLU;
	int isn = 0;
	uint64_t v = *(uint64_t*)&x;
	v &= Mask;
	if ((v & Mask2) == Mask2)
		isn = (v & Mask3) != 0;
	return isn;
}
int isnanld(long double x)
{
	int isi = 0;
	if constexpr (sizeof(x) == 10)
	{
		uint64_t* frac = (uint64_t*)&x;
		uint16_t* exp = (uint16_t*)(frac + 1);
		if (*exp & 0x7FFF)
		{
			isi = (*frac & 0x3FFFFFFFFFFFFFFFLLU) != 0;
			if (isi == 0)
			{
				uint64_t v = *frac >> 62;
				isi = v != 0x1;
			}

		}
	}
	else
	{
		isi = isnand(x);
	}

	return isi;
}


int isnormalf(float x)
{
	int isn = 0;
	if ((isnan(x)) == 0)
	{
		isn = isfinite(x);
		if (isn != 0)
		{
			isn = (*(uint32_t*)&x & 0x7FFFFFFF) != 0;
		}
	}
	return isn;
}
int isnormald(double x)
{
	int isn = 0;
	if ((isnan(x)) == 0)
	{
		isn = isfinite(x);
		if (isn != 0)
		{
			isn = (*(uint64_t*)&x & 0x7FFFFFFFFFFFFFFFLLU) != 0;
		}
	}
	return isn;
}
int isnormalld(long double x)
{
	int isn; 
	if constexpr (sizeof(x) == 10)
	{
		isn = 0;
		if ((isnan(x)) == 0)
		{
			isn = isfinite(x);
			if (isn == 0)
			{
				uint64_t* frac = (uint64_t*)&x;
				uint16_t* exp = (uint16_t*)(frac + 1);
				isn = (*exp & 0x7FFF) != 0;
			}
		}
	}
	else
	{
		isn = isnormald(x);
	}
	return isn;
}


int signbitf(float x)
{
	constexpr uint32_t Mask = 0x80000000;
	return (*(uint32_t*)&x & Mask) != 0;
}
int signbitd(double x)
{
	constexpr uint64_t Mask = 0x8000000000000000LLU;
	return (*(uint64_t*)&x & Mask) != 0;
}
int signbitld(long double x)
{
	if constexpr (sizeof(x) == 10)
	{
		uint64_t* frac = (uint64_t*)&x;
		uint16_t* exp = (uint16_t*)(frac + 1);
		return (*exp & 0x8000) != 0;
	}
	else
	{
		return signbitd(x);
	}
}
