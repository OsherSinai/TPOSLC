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
#ifdef __cplusplus
extern "C" {
#endif

double acos(double x)
{
	__asm {
		fld1		; 1
		fld [x]		; 1, x
		fmul st(0)	; 1, x^2,
		fsubp		; 1-x^2 
		fsqrt		; sqrt(1-x^2)
		fld [x]		; x, sqrt(1 - x ^ 2)
		fpatan;
		fstp [x]
	}
	return x;
}
float acosf(float x)
{
	__asm {
		fld1		; 1
		fld [x]		; 1, x
		fmul st(0)	; 1, x^2,
		fsubp		; 1-x^2 
		fsqrt		; sqrt(1-x^2)
		fld [x]		; x, sqrt(1 - x ^ 2)
		fpatan;
		fstp [x]
	}
	return x;
}
long double acosl(long double x)
{
	__asm {
		fld1		; 1
		fld [x]		; 1, x
		fmul st(0)	; 1, x^2,
		fsubp		; 1-x^2 
		fsqrt		; sqrt(1-x^2)
		fld [x]		; x, sqrt(1 - x ^ 2)
		fpatan;
		fstp [x]
	}
	return x;
}

double asin(double x)
{
	__asm {
		fld [x]
		fld1
		fld st(1)
		fld st(0)
		fmulp
		fsubp
		fsqrt
		fpatan
		fstp [x]
	}
	return x;
}
float asinf(float x)
{
	__asm {
		fld [x]
		fld1
		fld st(1)
		fld st(0)
		fmulp
		fsubp
		fsqrt
		fpatan
		fstp [x]
	}
	return x;
}
long double asinl(long double x)
{
	__asm {
		fld [x]
		fld1
		fld st(1)
		fld st(0)
		fmulp
		fsubp
		fsqrt
		fpatan
		fstp [x]
	}
	return x;
}

double atan(double x)
{
	__asm {
		fld [x]
		fld1
		fpatan
		fstp [x]
	}
	return x;
}
float atanf(float x)
{
	__asm {
		fld [x]
		fld1
		fpatan
		fstp [x]
	}
	return x;
}
long double atanl(long double x)
{
	__asm {
		fld [x]
		fld1
		fpatan
		fstp [x]
	}
	return x;
}

double atan2(double y, double x)
{
	__asm {
		fld [y]
		fld [x]
		fpatan
		fstp [x]
	}
	return x;
}
float atan2f(float y, float x)
{
	__asm {
		fld [y]
		fld [x]
		fpatan
		fstp [x]
	}
	return x;
}
long double atan2l(long double y, long double x)
{
	__asm {
		fld [y]
		fld [x]
		fpatan
		fstp [x]
	}
	return x;
}

double cos(double x)
{
	__asm {
		fld qword ptr[x]
		fcos
		fstp qword ptr[x]
	}
	return x;
}
float cosf(float x)
{
	__asm {
		fld dword ptr[x]
		fcos
		fstp dword ptr[x]
	}
	return x;
}
long double cosl(long double x)
{
	__asm {
		fld [x]
		fcos
		fstp [x]
	}
	return x;
}

double sin(double x)
{
	__asm {
		fld qword ptr[x]
		fsin
		fstp qword ptr[x]
	}
	return x;
}
float sinf(float x)
{
	__asm {
		fld dword ptr[x]
		fsin
		fstp dword ptr[x]
	}
	return x;
}
long double sinl(long double x)
{
	__asm {
		fld [x]
		fsin
		fstp [x]
	}
	return x;
}

double tan(double x)
{
	double sinu;
	double co;
	__asm {
		fld [x]
		fsincos
		fstp [co]
		fstp [sinu]
	}
	if (co != 0.f)
		x = sinu / co;
	else
		x = INFINITY;
	return x;
}
float tanf(float x)
{
	float sinu;
	float co;
	__asm {
		fld [x]
		fsincos
		fstp [co]
		fstp [sinu]
	}
	if (co != 0.)
		x = sinu / co;
	else
		x = INFINITY;
	return x;
}
long double tanl(long double x)
{
	long double sinu;
	long double co;
	__asm {
		fld [x]
		fsincos
		fstp [co]
		fstp [sinu]
	}
	if (co != 0.L)
		x = sinu / co;
	else
		x = INFINITY;
	return x;
}

#ifdef __cplusplus
}
#endif