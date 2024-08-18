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

double fmod(double x, double y)
{
	return (double)fmodl((long double)x, (long double)y);
}
float fmodf(float x, float y)
{
	return (float)fmodl((long double)x, (long double)y);
}
long double fmodl(long double x, long double y)
{
	//TODO: check for negatives
	long double ret;
	long double flr;
	if (isinf(y))
	{
		ret = x;
	}
	else
	{
		ret = x / y;
		flr = floorl(ret);
		ret = ret - flr;
		ret *= fabsl(y);
	}
	return ret;
}

double remainder(double x, double y)
{
	return fmod(x, y);
}
float remainderf(float x, float y)
{
	return fmodf(x, y);
}
long double remainderl(long double x, long double y)
{
	return fmodl(x, y);
}

double remquo(double x, double y, int* quo)
{
	double flr = floor(x / y);
	if (isnan(flr))
		*quo = 0;
	else if (isinf(flr))
		*quo = 0;
	else
		*quo = (int)flr;
	return x - (flr * y);
}
float remquof(float x, float y, int* quo)
{
	float flr = floorf(x / y);
	if(isnan(flr))
		*quo = 0;
	else if(isinf(flr))
		*quo = 0;
	else
		*quo = (int)flr;
	return x - (flr * y);
}
long double remquol(long double x, long double y,
	int* quo)
{
	long double flr = floorl(x / y);
	if (isnan(flr))
		*quo = 0;
	else if (isinf(flr))
		*quo = 0;
	else
		*quo = (int)flr;
	return x - (flr * y);
}