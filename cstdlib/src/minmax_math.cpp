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
double fdim(double x, double y)
{
	auto ret = x - y;
	ret = (ret < 0.) ? +0. : ret;
	return ret;
}
float fdimf(float x, float y)
{
	auto ret = x - y;
	ret = (ret < 0.f) ? +0.f : ret;
	return ret;
}
long double fdiml(long double x, long double y)
{
	auto ret = x - y;
	ret = (ret < 0.L) ? +0.L : ret;
	return ret;
}

double fmax(double x, double y)
{
	return x > y ? x : y;
}
float fmaxf(float x, float y)
{
	return x > y ? x : y;
}
long double fmaxl(long double x, long double y)
{
	return x > y ? x : y;
}

double fmin(double x, double y)
{
	return x < y ? x : y;
}
float fminf(float x, float y)
{
	return x < y ? x : y;
}
long double fminl(long double x, long double y)
{
	return x < y ? x : y;
}