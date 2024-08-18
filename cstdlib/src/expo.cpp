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
#include <include\float.h>
#include <include\limits.h>
#include <include\fenv.h>
#include <include\errno.h>

double modf(double value, double* iptr)
{
	*iptr = floor(value);
	return copysign(isinf(value) ? 0.0 : value - (*iptr), value);
}
float modff(float value, float* iptr)
{
	*iptr = floorf(value);
	float fret;
	if (isinf(value) != 0)
		fret = 0.0;
	else
		fret = value - (*iptr);

	return copysignf(fret, value);
}
long double modfl(long double value, long double* iptr)
{
	*iptr = floorl(value);
	return copysignl(isinf(value) ? 0.0 : value - (*iptr), value);
}

double cbrt(double x)
{
	double ret = sqrt(x);
	if (x != 0.)
	{
		for (size_t i = 0; i < 10; i++)
		{
			double powprev = ret * ret;
			double upper = powprev * ret - x;
			double lower = 3 * powprev;
			ret = ret - (upper / lower);
		}
	}
	return ret;
}
float cbrtf(float x)
{
	float ret = sqrtf(x);
	if (x != 0.f)
	{
		for (size_t i = 0; i < 10; i++)
		{
			float powprev = ret * ret;
			float upper = powprev * ret - x;
			float lower = 3 * powprev;
			ret = ret - (upper / lower);
		}
	}
	return ret;
}
long double cbrtl(long double x)
{
	long double ret = sqrtl(x);
	if (x != 0.l)
	{
		for (size_t i = 0; i < 10; i++)
		{
			long double powprev = ret * ret;
			long double upper = powprev * ret - x;
			long double lower = 3 * powprev;
			ret = ret - (upper / lower);
		}
	}
	return ret;
}

double fabs(double x)
{
	__asm {
		fld [x]
		fabs
		fstp [x]
	}
	return x;
}
float fabsf(float x)
{
	__asm {
		fld [x]
		fabs
		fstp [x]
	}
	return x;
}
long double fabsl(long double x)
{
	__asm {
		fld [x]
		fabs
		fstp [x]
	}
	return x;
}


double hypot(double x, double y)
{
	if (isinf(x) != 0 || isinf(y) != 0)
		x = INFINITY;
	else
	{
		__asm {
			fld [x]
			fmul st
			fld [y]
			fmul st
			faddp
			fsqrt
			fstp [x]
		}
	}
	return x;
}
float hypotf(float x, float y)
{
	if (isinf(x) != 0 || isinf(y) != 0)
		x = INFINITY;
	else
	{
		__asm {
			fld [x]
			fmul st
			fld [y]
			fmul st
			faddp
			fsqrt
			fstp [x]
		}
	}
	return x;
}
long double hypotl(long double x, long double y)
{
	if (isinf(x) != 0 || isinf(y) != 0)
		x = INFINITY;
	else
	{
		__asm {
			fld [x]
			fmul st
			fld [y]
			fmul st
			faddp
			fsqrt
			fstp [x]
		}
	}
	return x;
}

double pow(double base, double power)
{
	__asm {
		fld [power]	; power
		fld [base]	; base, power
		fyl2x		; log
		fld st		; log, log
		frndint		; floor, log
		fxch		; log, floor
		fld	st(1)	; floor, log, floor
		fsub		; norm, floor
		f2xm1		; pown, floor
		fld1		; 1, pown, floor
		faddp		; powns, floor
		fscale		; pow, floor
		fstp [base] ; floor
		fstp st
	}
	return base;
}
float powf(float base, float power)
{
	__asm {
		fld [power]	; power
		fld [base]	; base, power
		fyl2x		; log
		fld st		; log, log
		frndint		; floor, log
		fxch		; log, floor
		fld	st(1)	; floor, log, floor
		fsub		; norm, floor
		f2xm1		; pown, floor
		fld1		; 1, pown, floor
		faddp		; powns, floor
		fscale		; pow, floor
		fstp [base] ; floor
		fstp st
	}
	return base;
}
long double powl(long double base, long double power)
{
	__asm {
		fld [power]	; power
		fld [base]	; base, power
		fyl2x		; log
		fld st		; log, log
		frndint		; floor, log
		fxch		; log, floor
		fld	st(1)	; floor, log, floor
		fsub		; norm, floor
		f2xm1		; pown, floor
		fld1		; 1, pown, floor
		faddp		; powns, floor
		fscale		; pow, floor
		fstp [base] ; floor
		fstp st
	}
	return base;
}

double sqrt(double x)
{
	__asm {
		fld [x]
		fsqrt 
		fstp [x]
	}
	return x;
}
float sqrtf(float x)
{
	__asm {
		fld [x]
		fsqrt 
		fstp [x]
	}
	return x;
}
long double sqrtl(long double x)
{
	__asm {
		fld [x]
		fsqrt 
		fstp [x]
	}
	return x;
}


static constexpr double log2e_recipocal = 0.69314718055994529;
static constexpr double log210_recipocal = 0.30102999566398120;
static long double InternalLog(long double iresip, long double x)
{
	__asm {
		fld [iresip] ; 1 / log_2(e)
		fld [x]; x, 1 / log_2(e)
		fyl2x; log_e(x)
		fstp [iresip]
	}
	return iresip;
}

double log(double x)
{
	return (double)logl(x);
}
float logf(float x)
{
	return (float)logl(x);
}
long double logl(long double x)
{
	return InternalLog(log2e_recipocal, x);
}

double log10(double x)
{
	return (double)log10l(x);
}
float log10f(float x)
{
	return (float)log10l(x);
}
long double log10l(long double x)
{
	return InternalLog(log210_recipocal, x);
}

double log2(double x)
{
	return (double)InternalLog(1.l, x);
}
float log2f(float x)
{
	return (float)InternalLog(1.l, x);
}
long double log2l(long double x)
{
	return InternalLog(1.l, x);
}

double log1p(double x)
{
	return log(x + 1.);
}
float log1pf(float x)
{
	return logf(x + 1.f);

}
long double log1pl(long double x)
{
	return logl(x + 1.l);
}


double exp(double x)
{
	double fret;
	if (fabs(x) == 0.)
		fret = 1.;
	else if (x == -HUGE_VAL)
		fret = 0.;
	else if (x == HUGE_VAL)
		fret = HUGE_VAL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = pow(M_E, x);
	return fret;
}
float expf(float x)
{
	float fret;
	if (fabsf(x) == 0.f)
		fret = 1.f;
	else if (x == -HUGE_VALF)
		fret = 0.f;
	else if (x == HUGE_VALF)
		fret = HUGE_VALF;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powf(M_E, x);
	return fret;
}
long double expl(long double x)
{
	long double fret;
	if (fabsl(x) == 0.l)
		fret = 1.;
	else if (x == -HUGE_VALL)
		fret = 0.l;
	else if (x == HUGE_VALL)
		fret = HUGE_VALL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powl(M_E, x);
	return fret;
}

double exp2(double x)
{
	double fret;
	if (fabs(x) == 0.)
		fret = 1.;
	else if (x == -HUGE_VAL)
		fret = 0.;
	else if (x == HUGE_VAL)
		fret = HUGE_VAL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = pow(2., x);
	return fret;
}
float exp2f(float x)
{
	float fret;
	if (fabsf(x) == 0.f)
		fret = 1.f;
	else if (x == -HUGE_VALF)
		fret = 0.f;
	else if (x == HUGE_VALF)
		fret = HUGE_VALF;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powf(2.f, x);
	return fret;
}
long double exp2l(long double x)
{
	long double fret;
	if (fabsl(x) == 0.l)
		fret = 1.;
	else if (x == -HUGE_VALL)
		fret = 0.l;
	else if (x == HUGE_VALL)
		fret = HUGE_VALL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powl(2.l, x);
	return fret;
}

double expm1(double x)
{
	double fret;
	if (fabs(x) == 0.l)
		fret = x;
	else if (x == -HUGE_VAL)
		fret = -1.f;
	else if (x == HUGE_VAL)
		fret = HUGE_VAL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = pow(M_E, x) - 1.f;
	return fret;
}
float expm1f(float x)
{
	float fret;
	if (fabsf(x) == 0.l)
		fret = x;
	else if (x == -HUGE_VALF)
		fret = -1.f;
	else if (x == HUGE_VALF)
		fret = HUGE_VALF;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powf(M_E, x) - 1.f;
	return fret;
}
long double expm1l(long double x)
{
	long double fret;
	if (fabsl(x) == 0.l)
		fret = x;
	else if (x == -HUGE_VALL)
		fret = -1.l;
	else if (x == HUGE_VALL)
		fret = HUGE_VALL;
	else if ((isnan(x)) != 0)
		fret = NAN;
	else
		fret = powl(M_E, x) - 1.l;
	return fret;
}


double frexp(double value, int* exp)
{
	if (value == 0.)
		*exp = FP_ILOGB0;
	else if (isnan(value))
		*exp = FP_ILOGBNAN;
	else
		*exp = ilogb(value);

	if (value == 0.f)
		*exp = FP_ILOGB0;
	else if (isnan(value))
		*exp = FP_ILOGBNAN;
	else if (value == HUGE_VALF)
		*exp = 1;
	else
	{
		*exp = ilogb(value);
		uint64_t* pUW = ((uint64_t*)&value);
		*pUW &= 0x800F'FFFF'FFFF'FFFFllu;
		*pUW |= 0x3FF0'0000'0000'0000llu;
	}
	return value;
}
float frexpf(float value, int* exp)
{
	if (value == 0.f)
		*exp = FP_ILOGB0;
	else if (isnan(value))
		*exp = FP_ILOGBNAN;
	else if (value == HUGE_VALF)
		*exp = 1;
	else
	{
		*exp = ilogbf(value);
		uint32_t* pUW = ((uint32_t*)&value);
		*pUW &= 0x807FFFFF;
		*pUW |= 0x3f800000;
	}
	return value;
}

long double frexpl(long double value, int* exp) 
{
	if constexpr (sizeof(value) == 10)
	{

		if (value == 0.f)
			*exp = FP_ILOGB0;
		else if (isnan(value))
			*exp = FP_ILOGBNAN;
		else if (value == HUGE_VALF)
			*exp = 1;
		else
		{
			*exp = ilogbl(value);
			uint16_t* pW = (((uint16_t*)&value) + 4);
			*pW &= 0x8000;
			*pW |= 0x3fFF;
		}
	}
	else
	{
		value = frexp(value, exp);
	}
	return value;
}


int ilogb(double x)
{
	//11 bit - 1
	int expo;
	if (x == 0.f)
		expo = FP_ILOGB0;
	else if (isnan(x))
		expo = FP_ILOGBNAN;
	else if (x == HUGE_VAL)
		expo = INT_MAX;
	else
		expo = (int)(((*(uint64_t*)&x) >> 52) & 0x7FF) - 1023;
	return expo;
}
int ilogbf(float x)
{
	// 8 bit - 1
	int expo;
	if (x == 0.f)
		expo = FP_ILOGB0;
	else if (isnan(x))
		expo = FP_ILOGBNAN;
	else if (x == HUGE_VALF)
		expo = INT_MAX;
	else
		expo = (int)(((*(uint32_t*)&x) >> 23) & 0xFF) - 127;
	return expo;
}
int ilogbl(long double x)
{
	int nRet;
	if constexpr (sizeof(long double) == 8)
		nRet = ilogb(x);
	else
	{
		// 15 bit - 1
		if (x == 0.f)
			nRet = FP_ILOGB0;
		else if (isnan(x))
			nRet = FP_ILOGBNAN;
		else if (x == HUGE_VALL)
			nRet = INT_MAX;
		else
		nRet = (int)((*(((uint64_t*)&x + 1))) & 0x7FFF) - 16383;
	}
	return nRet;
}


double ldexp(double x, int exp)
{
	errno = 0;
	if (exp > 1023 || exp < -1022)
	{
		errno = EDOM;
	}
	exp += 1023;
	uint64_t uint_expo = ((*(uint64_t*)&exp & 0x7FFF) << 52);
	double expo = *(double*)&uint_expo;
	return expo * x;
	

}
float ldexpf(float x, int exp)
{
	errno = 0;
	if (exp > 127 || exp < -126)
	{
		errno = EDOM;
	}
	exp += 127;
	uint32_t uint_expo = ((*(uint32_t*)&exp & 0xFF) << 23);
	float expo = *(float*)&uint_expo;
	return expo * x;
}
long double ldexpl(long double x, int exp)
{
	long double ldRet;
	errno = 0;
	if constexpr (sizeof(long double) == 8)
		ldRet = ldexp(x, exp);
	else
	{
		if (exp > 16383 || exp < -16382)
		{
			errno = EDOM;
		}
		exp += 16383;
		uint8_t uint_expo[10] = { 0 };
		uint16_t* pWU = (uint16_t*)&uint_expo[8];
		*pWU = exp & 0x7FFF;
		ldRet = x * *(long double*)uint_expo;
	}
	return ldRet;
}

double logb(double x)
{
	return (double)logbl((long double)x);
}
float logbf(float x)
{
	return (float)logbl((long double)x);
}
long double logbl(long double x)
{
	__asm {
		fld1; 1
		fld [x]; x, 1
		fyl2x; log_e(x)
		fstp [x]
	}
	return x;
}


double scalbn(double x, int n)
{
	return ldexp(x, n);
}
float scalbnf(float x, int n)
{
	return ldexpf(x, n);
}
long double scalbnl(long double x, int n)
{
	return ldexpl(x, n);
}
double scalbln(double x, long int n)
{
	return ldexp(x, (int)n);
}
float scalblnf(float x, long int n)
{
	return ldexpf(x, (int)n);
}
long double scalblnl(long double x, long int n)
{
	return ldexpl(x, (int)n);
}