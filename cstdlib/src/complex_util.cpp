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
#include <include\complex.h>
#include <include\math.h>
#include "cplx.h"

double carg(double complex z)
{
	cplx c;
	cplx_polar pol;
	c.load_double(z);
	pol = c.convert();
	//if (signbit(c.img))
	//	pol.angle = -pol.angle;
	return pol.angle;
}
float cargf(float complex z)
{
	cplx c;
	cplx_polar pol;
	c.load_float(z);
	pol = c.convert();
	//if (signbit(c.img))
	//	pol.angle = -pol.angle;
	return pol.angle;
}
long double cargl(long double complex z)
{
	cplx c;
	cplx_polar pol;
	c.load_long_double(z);
	pol = c.convert();
	//if (signbit(c.img))
	//	pol.angle = -pol.angle;
	return pol.angle;
}

double cimag(double complex z)
{
	cplx c;
	c.load_double(z);
	return c.img;
}
float cimagf(float complex z)
{
	cplx c;
	c.load_float(z);
	return c.img;
}
long double cimagl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	return c.img;
}

#undef CMPLX
double complex CMPLX(double x, double y)
{
	double complex r = {x, y};
	return r;
}
float complex CMPLXF(float x, float y)
{
	float complex r = { x, y };
	return r;
}
long double complex CMPLXL(long double x, long double y)
{
	long double complex r = { x, y };
	return r;
}

double complex conj(double complex z)
{
	cplx c;
	c.load_double(z);
	c.img = -c.img;
	return c.store_double();
}
float complex conjf(float complex z)
{
	cplx c;
	c.load_float(z);
	c.img = -c.img;
	return c.store_float();
}
long double complex conjl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c.img = -c.img;
	return c.store_long_double();
}

double complex cproj(double complex z)
{
	cplx c;
	c.load_double(z);
	if (c.real == HUGE_VAL ||
		c.real == -HUGE_VAL ||
		c.real == NAN ||
		c.img == HUGE_VAL ||
		c.img == -HUGE_VAL ||
		c.img == NAN)
	{
		c.real = HUGE_VAL;
		c.img = copysign(0., c.img);
	}
	return c.store_double();
}
float complex cprojf(float complex z)
{
	cplx c;
	c.load_float(z);
	if (c.real == HUGE_VALF ||
		c.real == -HUGE_VALF ||
		c.real == NAN ||
		c.img == HUGE_VALF ||
		c.img == -HUGE_VALF ||
		c.img == NAN)
	{
		c.real = HUGE_VALF;
		c.img = copysignf(0., c.img);
	}
	return c.store_float();
}
long double complex cprojl(long double complex z)
{

	cplx c;
	c.load_long_double(z);
	if (c.real == HUGE_VALL ||
		c.real == -HUGE_VALL ||
		c.real == NAN ||
		c.img == HUGE_VALL ||
		c.img == -HUGE_VALL ||
		c.img == NAN)
	{
		c.real = HUGE_VALL;
		c.img = copysignl(0., c.img);
	}
	return c.store_long_double();
}

double creal(double complex z)
{
	cplx c;
	c.load_double(z);
	return c.real;
}
float crealf(float complex z)
{
	cplx c;
	c.load_float(z);
	return c.real;
}
long double creall(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	return c.real;
}