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
#include <include\fenv.h>

double ceil(double x)
{
	int rnd = fegetround();
	fesetround(FE_UPWARD);
	x = rint(x);
	fesetround(rnd);
	return x;
}
float ceilf(float x)
{
	int rnd = fegetround();
	fesetround(FE_UPWARD);
	x = rintf(x);
	fesetround(rnd);
	return x;
}
long double ceill(long double x)
{
	int rnd = fegetround();
	fesetround(FE_UPWARD);
	x = rintl(x);
	fesetround(rnd);
	return x;
}

double floor(double x)
{
	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rint(x);
	fesetround(rnd);
	return x;
}
float floorf(float x)
{
	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rintf(x);
	fesetround(rnd);
	return x;
}
long double floorl(long double x)
{
	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rintl(x);
	fesetround(rnd);
	return x;
}

double round(double x)
{
	int rnd = fegetround();
	fesetround(FE_TONEAREST);
	x = rint(x);
	fesetround(rnd);
	return x;
}
float roundf(float x)
{
	int rnd = fegetround();
	fesetround(FE_TONEAREST);
	x = rintf(x);
	fesetround(rnd);
	return x;
}
long double roundl(long double x)
{
	int rnd = fegetround();
	fesetround(FE_TONEAREST);
	x = rintl(x);
	fesetround(rnd);
	return x;
}

double rint(double x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
	}
	return x;
}
float rintf(float x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
	}
	return x;
}
long double rintl(long double x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
	}
	return x;
}


long int lrint(double x)
{
	return (long int)rint(x);
}
long int lrintf(float x)
{
	return (long int)rintf(x);
}
long int lrintl(long double x)
{
	
	return (long int)rintl(x);
}
long long int llrint(double x)
{
	return (long long int)rint(x);
}
long long int llrintf(float x)
{
	return (long long int)rintf(x);
}
long long int llrintl(long double x)
{
	return (long long int)rintl(x);
}


double nearbyint(double x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
		fclex
	}
	return x;
}
float nearbyintf(float x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
		fclex
	}
	return x;
}
long double nearbyintl(long double x)
{
	__asm {
		fld [x]
		frndint
		fstp [x]
		fclex
	}
	return x;
}

long int lround(double x)
{
	//TODO: add bound check
	return (long int)round(x);
}
long int lroundf(float x)
{
	//TODO: add bound check
	return (long int)roundf(x);
}
long int lroundl(long double x)
{
	//TODO: add bound check
	return (long int)roundl(x);
}

long long int llround(double x)
{
	//TODO: add bound check
	return (long long int)round(x);
}
long long int llroundf(float x)
{
	//TODO: add bound check
	return (long long int)roundf(x);
}
long long int llroundl(long double x)
{
	//TODO: add bound check
	return (long long int)roundl(x);
}


double trunc(double x)
{

	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rint(x);
	fesetround(rnd);
	return x;
}
float truncf(float x)
{

	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rintf(x);
	fesetround(rnd);
	return x;
}
long double truncl(long double x)
{
	int rnd = fegetround();
	fesetround(FE_TOWARDZERO);
	x = rintl(x);
	fesetround(rnd);
	return x;
}