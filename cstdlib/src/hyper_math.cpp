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

double acosh(double x)
{
	return log(x + sqrt((x * x) - 1.l));
}
float acoshf(float x)
{
	return logf(x + sqrtf((x * x) - 1.l));
}
long double acoshl(long double x)
{
	return logl(x + sqrtl((x * x) - 1.l));
}

double asinh(double x)
{
	return log(x + sqrt((x * x) + 1.l));
}
float asinhf(float x)
{
	return logf(x + sqrtf((x * x) + 1.l));
}
long double asinhl(long double x)
{
	return logl(x + sqrtl((x * x) + 1.l));
}

double atanh(double x)
{
	return (double)atanhl((double)x);
}
float atanhf(float x)
{
	return (float)atanhl((float)x);
}
long double atanhl(long double x)
{
	return 0.5l * logl((1.l + x) / (1.l - x));
}

double cosh(double x)
{
	return (double)coshl((double)x);
}
float coshf(float x)
{
	return (float)coshl((float)x);
}
long double coshl(long double x)
{
	return (powl(M_E, x) + powl(M_E, -x)) / 2.l;
}

double sinh(double x)
{
	return (double)sinhl((double)x);
}
float sinhf(float x)
{
	return (float)sinhl((float)x);
}
long double sinhl(long double x)
{
	return (powl(M_E, x) - powl(M_E, -x)) / 2.l;
}

double tanh(double x)
{
	return (double)tanhl((double)x);
}
float tanhf(float x)
{
	return (float)tanhl((float)x);
}
long double tanhl(long double x)
{
	//long double e2x = powl(M_E, 2.l * x);
	x = powl(M_E, 2.l * x);
	return (x - 1.l) / (x + 1.l);
}