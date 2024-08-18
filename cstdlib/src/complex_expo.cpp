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

double complex cexp(double complex z)
{
	cplx c;
	c.load_double(z);
	c = c.cexp();
	return c.store_double();
}
float complex cexpf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.cexp();
	return c.store_float();
}
long double complex cexpl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.cexp();
	return c.store_long_double();
}

double complex clog(double complex z)
{
	cplx ret;
	ret.load_double(z);
	ret = ret.clog();
	//ret.real = log(cabs(z));
	//ret.img = carg(z);
	return ret.store_double();
}
float complex clogf(float complex z)
{
	cplx ret;
	ret.load_float(z);
	ret = ret.clog();
	//ret.real = logf(cabsf(z));
	//ret.img = cargf(z);
	return ret.store_float();
}
long double complex clogl(long double complex z)
{
	cplx ret;
	ret.load_long_double(z);
	ret = ret.clog();
	//ret.real = logl(cabsl(z));
	//ret.img = cargl(z);
	return ret.store_long_double();
}

double cabs(double complex z)
{
	cplx c;
	c.load_double(z);
	return (double)c.abs();
}
float cabsf(float complex z)
{
	cplx c;
	c.load_float(z);
	return (float)c.abs();
}
long double cabsl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	return c.abs();
}

double complex cpow(double complex x, double complex y)
{
	cplx c;
	cplx ret;
	cplx_polar pol;
	double absx = cabs(x);
	double cargx;
	if (absx != 0.)
	{
		c.load_double(y);
		cargx = carg(x);
		pol.mag = powl(absx, c.real);
		pol.angle = c.real * cargx;
		if (c.img != 0)
		{
			pol.mag = pol.mag * expl(-c.img * cargx);
			pol.angle = pol.angle + c.img * logl(absx);
		}
		ret = pol.convert();
	}
	else
	{
		ret.real = 0.f;
		ret.img = 0.f;
	}
	return ret.store_double();
}
float complex cpowf(float complex x, float complex y)
{
	cplx c;
	cplx ret;
	cplx_polar pol;
	float absx = cabsf(x);
	float cargx;
	if (absx != 0.f)
	{
		c.load_float(y);
		cargx = cargf(x);
		pol.mag = powl(absx, c.real);
		pol.angle = c.real * cargx;
		if (c.img != 0.l)
		{
			pol.mag = pol.mag * expl(-c.img * cargx);
			pol.angle = pol.angle + c.img * logl(absx);
		}
		ret = pol.convert();
	}
	else
	{
		ret.real = 0.f;
		ret.img = 0.f;
	}
	return ret.store_float();
}
long double complex cpowl(long double complex x,
	long double complex y)
{
	cplx c;
	cplx ret;
	cplx_polar pol;
	long double absx = cabsl(x);
	long double cargx;
	if (absx != 0.l)
	{
		c.load_long_double(y);
		cargx = cargl(x);
		pol.mag = powl(absx, c.real);
		pol.angle = c.real * cargx;
		if (c.img != 0.l)
		{
			pol.mag = pol.mag * expl(-c.img * cargx);
			pol.angle = pol.angle + c.img * logl(absx);
		}
		ret = pol.convert();
	}
	else
	{
		ret.real = 0.l;
		ret.img = 0.l;
	}
	return ret.store_long_double();
}

double complex csqrt(double complex z)
{
	cplx c;
	c.load_double(z);
	cplx r = c.sqrt();
	return r.store_double();
}
float complex csqrtf(float complex z)
{
	cplx c;
	c.load_float(z);
	cplx r = c.sqrt();
	return r.store_float();
}
long double complex csqrtl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	cplx r = c.sqrt();
	return r.store_long_double();
}