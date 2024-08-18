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
#pragma once
#ifndef TOS_MATH_H
#define TOS_MATH_H

#include "stddef.h"
LIBC_DEF_BEGIN

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

#define TOS_DEG_TO_RAD(x) (x*(M_PI/180.))
#define TOS_RAD_TO_DEG_LD(x) (x*(180. * M_1_PI))

#if (FLT_EVAL_METHOD == 0)
typedef float float_t;
typedef double double_t;
#elif (FLT_EVAL_METHOD == 1)
typedef double float_t;
typedef double double_t;
#elif (FLT_EVAL_METHOD == 2)
typedef long double float_t;
typedef long double double_t;
#else
typedef float float_t;
typedef double double_t;
#endif

#define INFINITY ((float)(+1e300 * +1e300))
#define NAN (-(INFINITY * 0.0f))

#define HUGE_VAL ((double)INFINITY)
#define HUGE_VALF INFINITY
#define HUGE_VALL ((long double)INFINITY)

//support
#define FP_FAST_FMA 1
#define FP_FAST_FMAF 1
#define FP_FAST_FMAL 1
#define FP_ILOGB0 0
#define FP_ILOGBNAN (~1)

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2

#define FP_ZERO 0
#define FP_INFINITE 1
#define FP_NAN 2
#define FP_NORMAL 3
#define FP_SUBNORMAL 4

#define math_errhandling MATH_ERRNO
/*classify_math.cpp*/
int fpclassifyf(float x);
int fpclassifyd(double x);
int fpclassifyld(long double x);
#define fpclassify(x) _Generic((x),\
	float:		 fpclassifyf,\
	double:		 fpclassifyd,\
	long double: fpclassifld\
)(x)

int isfinitef(float x);
int isfinited(double x);
int isfiniteld(long double x);
#define isfinite(x) _Generic((x),\
	float:		 isfinitef,\
	double:		 isfinited,\
	long double: isfiniteld\
)(x)

int isinff(float x);
int isinfd(double x);
int isinfld(long double x);
#define isinf(x) _Generic((x),\
	float:		 isinff,\
	double:		 isinfd,\
	long double: isinfld\
)(x)

int isnanf(float x);
int isnand(double x);
int isnanld(long double x);
#define isnan(x) _Generic((x),\
	float:		 isnanf,\
	double:		 isnand,\
	long double: isnanld\
)(x)

int isnormalf(float x);
int isnormald(double x);
int isnormalld(long double x);
#define isnormal(x) _Generic((x),\
	float:		 isnormalf,\
	double:		 isnormald,\
	long double: isnormalld\
)(x)

int signbitf(float x);
int signbitd(double x);
int signbitld(long double x);
#define signbit(x) _Generic((x),\
	float:		 signbitf,\
	double:		 signbitd,\
	long double: signbitld\
)(x)

/*trigo_math.cpp*/
double acos(double x);
float acosf(float x);
long double acosl(long double x);

double asin(double x);
float asinf(float x);
long double asinl(long double x);

double atan(double x);
float atanf(float x);
long double atanl(long double x);

double atan2(double y, double x);
float atan2f(float y, float x);
long double atan2l(long double y, long double x);

double cos(double x);
float cosf(float x);
long double cosl(long double x);

double sin(double x);
float sinf(float x);
long double sinl(long double x);

double tan(double x);
float tanf(float x);
long double tanl(long double x);


/*hyper_math.cpp*/
double acosh(double x);
float acoshf(float x);
long double acoshl(long double x);

double asinh(double x);
float asinhf(float x);
long double asinhl(long double x);

double atanh(double x);
float atanhf(float x);
long double atanhl(long double x);

double cosh(double x);
float coshf(float x);
long double coshl(long double x);

double sinh(double x);
float sinhf(float x);
long double sinhl(long double x);

double tanh(double x);
float tanhf(float x);
long double tanhl(long double x);

/*expo.cpp*/
double exp(double x);
float expf(float x);
long double expl(long double x);

double exp2(double x);
float exp2f(float x);
long double exp2l(long double x);

double expm1(double x);
float expm1f(float x);
long double expm1l(long double x);

double frexp(double value, int* exp);
float frexpf(float value, int* exp);
long double frexpl(long double value, int* exp);

int ilogb(double x);
int ilogbf(float x);
int ilogbl(long double x);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);
long double ldexpl(long double x, int exp);

double log(double x);
float logf(float x);
long double logl(long double x);

double log10(double x);
float log10f(float x);
long double log10l(long double x);

double log1p(double x);
float log1pf(float x);
long double log1pl(long double x);

double log2(double x);
float log2f(float x);
long double log2l(long double x);

double logb(double x);
float logbf(float x);
long double logbl(long double x);

double modf(double value, double* iptr);
float modff(float value, float* iptr);
long double modfl(long double value, long double* iptr);

double scalbn(double x, int n);
float scalbnf(float x, int n);
long double scalbnl(long double x, int n);
double scalbln(double x, long int n);
float scalblnf(float x, long int n);
long double scalblnl(long double x, long int n);

double cbrt(double x);
float cbrtf(float x);
long double cbrtl(long double x);

double fabs(double x);
float fabsf(float x);
long double fabsl(long double x);

double hypot(double x, double y);
float hypotf(float x, float y);
long double hypotl(long double x, long double y);

double pow(double x, double y);
float powf(float x, float y);
long double powl(long double x, long double y);

double sqrt(double x);
float sqrtf(float x);
long double sqrtl(long double x);
//error_gamma.cpp
double erf(double x);
float erff(float x);
long double erfl(long double x);

double erfc(double x);
float erfcf(float x);
long double erfcl(long double x);

double lgamma(double x);
float lgammaf(float x);
long double lgammal(long double x);

double tgamma(double x);
float tgammaf(float x);
long double tgammal(long double x);

// round,cpp
double ceil(double x);
float ceilf(float x);
long double ceill(long double x);

double floor(double x);
float floorf(float x);
long double floorl(long double x);

double nearbyint(double x);
float nearbyintf(float x);
long double nearbyintl(long double x);

double rint(double x);
float rintf(float x);
long double rintl(long double x);

long int lrint(double x);
long int lrintf(float x);
long int lrintl(long double x);
long long int llrint(double x);
long long int llrintf(float x);
long long int llrintl(long double x);

double round(double x);
float roundf(float x);
long double roundl(long double x);

long int lround(double x);
long int lroundf(float x);
long int lroundl(long double x);

long long int llround(double x);
long long int llroundf(float x);
long long int llroundl(long double x);

double trunc(double x);
float truncf(float x);
long double truncl(long double x);

/*math_rem.cpp*/
double fmod(double x, double y);
float fmodf(float x, float y);
long double fmodl(long double x, long double y);

double remainder(double x, double y);
float remainderf(float x, float y);
long double remainderl(long double x, long double y);

double remquo(double x, double y, int* quo);
float remquof(float x, float y, int* quo);
long double remquol(long double x, long double y,
	int* quo);

/*manip_math.cpp*/
double copysign(double x, double y);
float copysignf(float x, float y);
long double copysignl(long double x, long double y);

double nan(const char* tagp);
float nanf(const char* tagp);
long double nanl(const char* tagp);

double nextafter(double x, double y);
float nextafterf(float x, float y);
long double nextafterl(long double x, long double y);

double nexttoward(double x, long double y);
float nexttowardf(float x, long double y);
long double nexttowardl(long double x, long double y);

/*minmax_math.h*/
double fdim(double x, double y);
float fdimf(float x, float y);
long double fdiml(long double x, long double y);

double fmax(double x, double y);
float fmaxf(float x, float y);
long double fmaxl(long double x, long double y);

double fmin(double x, double y);
float fminf(float x, float y);
long double fminl(long double x, long double y);

/*fma_math.cpp*/
double fma(double x, double y, double z);
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y,
	long double z);

/*comp_math.cpp*/
//int isgreater(real - floating x, real - floating y);
//int isgreaterequal(real - floating x, real - floating y);
//int isless(real - floating x, real - floating y);
//int islessequal(real - floating x, real - floating y);
//int islessgreater(real - floating x, real - floating y);
//int isunordered(real - floating x, real - floating y);

LIBC_DEF_END
#endif // !TOS_MATH_H
