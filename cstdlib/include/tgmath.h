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
#ifndef TOS_TGMATH_H
#define TOS_TGMATH_H

#include "stddef.h"
#include "math.h"
#include "complex.h"

LIBC_DEF_BEGIN
#define acos(x) _Generic((x),\
	float complex: cacosf,\
	double complex: cacos,\
	long double complex: cacosl,\
	float: acosf,\
	long double: acosl,\
	default: acos\
)(x)

#define asin(x) _Generic((x),\
	float complex: casinf,\
	double complex: casin,\
	long double complex: casinl,\
	float: asinf,\
	long double: asinl,\
	default: asin\
)(x)

#define atan(x) _Generic((x),\
	float complex: catanf,\
	double complex: catan,\
	long double complex: catanl,\
	float: atanf,\
	long double: atanl,\
	default: atan\
)(x)

#define acosh(x) _Generic((x),\
	float complex: cacoshf,\
	double complex: cacosh,\
	long double complex: cacoshl,\
	float: acoshf,\
	long double: acoshl,\
	default: acosh\
)(x)

#define asinh(x) _Generic((x),\
	float complex: casinhf,\
	double complex: casinh,\
	long double complex: casinhl,\
	float: asinhf,\
	long double: asinhl,\
	default: asinh\
)(x)

#define atanh(x) _Generic((x),\
	float complex: catanhf,\
	double complex: catanh,\
	long double complex: catanhl,\
	float: atanhf,\
	long double: atanhl,\
	default: atanh\
)(x)

#define cos(x) _Generic((x),\
	float complex: ccosf,\
	double complex: ccos,\
	long double complex: ccosl,\
	float: cosf,\
	long double: cosl,\
	default: cos\
)(x)

#define sin(x) _Generic((x),\
	float complex: csinf,\
	double complex: csin,\
	long double complex: csinl,\
	float: sinf,\
	long double: sinl,\
	default: sin\
)(x)

#define tan(x) _Generic((x),\
	float complex: ctanf,\
	double complex: ctan,\
	long double complex: ctanl,\
	float: tanf,\
	long double: tanl,\
	default: tan\
)(x)

#define cosh(x) _Generic((x),\
	float complex: ccoshf,\
	double complex: ccosh,\
	long double complex: ccoshl,\
	float: coshf,\
	long double: coshl,\
	default: cosh\
)(x)

#define sinh(x) _Generic((x),\
	float complex: csinhf,\
	double complex: csinh,\
	long double complex: csinhl,\
	float: sinhf,\
	long double: sinhl,\
	default: sinh\
)(x)

#define tanh(x) _Generic((x),\
	float complex: ctanhf,\
	double complex: ctanh,\
	long double complex: ctanhl,\
	float: tanhf,\
	long double: tanhl,\
	default: tanh\
)(x)

#define exp(x) _Generic((x),\
	float complex: cexpf,\
	double complex: cexp,\
	long double complex: cexpl,\
	float: expf,\
	long double: expl,\
	default: exp\
)(x)

#define log(x) _Generic((x),\
	float complex: clogf,\
	double complex: clog,\
	long double complex: clogl,\
	float: logf,\
	long double: logl,\
	default: log\
)(x)

#define pow(x, y) _Generic((x),\
	float complex: cpowf,\
	double complex: cpow,\
	long double complex: cpowl,\
	float: powf,\
	long double: powl,\
	default: pow\
)(x, y)

#define sqrt(x) _Generic((x),\
	float complex: csqrtf,\
	double complex: csqrt,\
	long double complex: csqrtl,\
	float: sqrtf,\
	long double: sqrtl,\
	default: sqrt\
)(x)

#define fabs(x) _Generic((x),\
	float complex: cabsf,\
	double complex: cabs,\
	long double complex: cabsl,\
	float: fabsf,\
	long double: fabsl,\
	default: fabs\
)(x)
LIBC_DEF_END
#endif // !TOS_TGMATH_H
