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

//TODO: review G6 in the spec

//https://www.youtube.com/watch?v=M7m65MeWubU
/*
thanks euler

cos(i*x) = cosh(x)
sin(i*x) = i*sinh(x)

cosh(i*x) = cos(x)
sinh(i*x) = i*sin(x)

*/

double complex cacos(double complex z)
{
	cplx c;
	c.load_double(z);
	c = c.cacos();
	return c.store_double();
}
float complex cacosf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.cacos();
	return c.store_float();
}
long double complex cacosl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.cacos();
	return c.store_long_double();
}

double complex casin(double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.casin();
	return c.store_long_double();
}
float complex casinf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.casin();
	return c.store_float();
}
long double complex casinl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.casin();
	return c.store_long_double();
}

//atan(x) = asin(x/sqrt(1+x^2))
double complex catan(double complex z)
{
	cplx c;
	c.load_double(z);
	c = c.catan();
	return c.tgstore(z);
}
float complex catanf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.catan();
	return c.tgstore(z);
}
long double complex catanl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.catan();
	return c.tgstore(z);
}

double complex ccos(double complex z)
{
	cplx c;
	c.load_double(z);
	c = c.cos();
	return c.store_double();
}
float complex ccosf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.cos();
	return c.store_float();
}
long double complex ccosl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.cos();
	return c.store_long_double();
}

double complex csin(double complex z)
{
	cplx c;
	c.load_double(z);
	c.swap();
	c.real = -c.real;
	c = c.csinh();
	c.swap();
	c.img = -c.img;
	return c.store_double();
}
float complex csinf(float complex z)
{
	cplx c;
	c.load_float(z);
	c.swap();
	c.real = -c.real;
	c = c.csinh();
	c.swap();
	c.img = -c.img;
	return c.store_float();
}
long double complex csinl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c.swap();
	c.real = -c.real;
	c = c.csinh();
	c.swap();
	c.img = -c.img;
	return c.store_long_double();
}

double complex ctan(double complex z)
{
	cplx c;
	c.load_double(z);
	c = c.ctan();
	//c = c.sin() / c.cos();
	return c.store_double();
}
float complex ctanf(float complex z)
{
	cplx c;
	c.load_float(z);
	c = c.ctan();
	//c = c.sin() / c.cos();
	return c.store_float();
}
long double complex ctanl(long double complex z)
{
	cplx c;
	c.load_long_double(z);
	c = c.ctan();
	//c = c.sin() / c.cos();
	return c.store_long_double();
}

double complex cacosh(double complex z)
{
	/*
	arccosh = (sqrt(z-1)/sqrt(1-z))*arcos(z)
	*/
	cplx ret;
	ret.tgload(z);
	ret = ret.cacosh();
	return ret.tgstore(z);
}
float complex cacoshf(float complex z)
{
	/*
	arccosh = (sqrt(z-1)/sqrt(1-z))*arcos(z)
	*/
	cplx ret;
	ret.tgload(z);
	ret = ret.cacosh();
	return ret.tgstore(z);
}
long double complex cacoshl(long double complex z)
{
	/*
	arccosh = (sqrt(z-1)/sqrt(1-z))*arcos(z)
	*/
	cplx ret;
	ret.tgload(z);
	ret = ret.cacosh();
	return ret.tgstore(z);
}

double complex casinh(double complex z)
{
	/*
	asinh(z) = ln(z + sqrt(1 + z^2))
	*/
	/*
	cplx x;
	cplx sqrtx;
	cplx s2;
	s2.real = 2.l;
	s2.img = 0.l;
	x.tgload(z);
	sqrtx = x.cpow(s2);
	sqrtx.real += 1.l;
	sqrtx = sqrtx.sqrt();
	x = x + sqrtx;
	x.tgload(clogl(x.store_long_double()));
	return x.tgstore(z);
	*/
	cplx x;
	x.tgload(z);
	x = x.casinh();
	return x.tgstore(z);
}
float complex casinhf(float complex z)
{
	/*
	asinh(z) = ln(z + sqrt(1 + z^2))
	*/
	/*
	cplx x;
	cplx sqrtx;
	cplx s2;
	s2.real = 2.l;
	s2.img = 0.l;
	x.tgload(z);
	sqrtx = x.cpow(s2);
	sqrtx.real += 1.l;
	sqrtx = sqrtx.sqrt();
	x = x + sqrtx;
	x.tgload(clogl(x.store_long_double()));
	return x.tgstore(z);
	*/
	cplx x;
	x.tgload(z);
	x = x.casinh();
	return x.tgstore(z);
}
long double complex casinhl(long double complex z)
{
	cplx x;
	x.tgload(z);
	x = x.casinh();
	return x.tgstore(z);
}

double complex catanh(double complex z)
{
	cplx x;
	x.tgload(z);
	x = x.catanh();
	return x.tgstore(z);
}
float complex catanhf(float complex z)
{
	cplx x;
	x.tgload(z);
	x = x.catanh();
	return x.tgstore(z);
}
long double complex catanhl(long double complex z)
{
	/*
	artanh(z) = 0.5*[ln(1+z) - ln(1-z)]
	*/
	cplx x;
	//cplx half;
	//cplx c1;
	//cplx c2;
	x.tgload(z);
	//half.real = 0.5l;
	//half.img = 0.l;
	//c1.real = 1.l;
	//c1.img = 0.l;
	//c2 = c1 - x;
	//c1 = c1 + x;
	//c1.tgload(clogl(c1.store_long_double()));
	//c2.tgload(clogl(c2.store_long_double()));
	//x = c1 - c2;
	//x = x * half;
	x = x.catanh();
	return x.tgstore(z);
}

double complex ccosh(double complex z)
{
	/*

	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	cosh(x+yi) = cosh(x)cosh(yi)+sinh(x)sinh(yi) =
				 cosh(x)cos(y)+sinh(x)sin(y)i
	*/
	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = coshl(c.real) * cosl(c.img);
	//ret.img = sinhl(c.real) * sinl(c.img);
	ret = c.ccosh();
	return ret.tgstore(z);
}
float complex ccoshf(float complex z)
{
	/*

	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	cosh(x+yi) = cosh(x)cosh(yi)+sinh(x)sinh(yi) =
				 cosh(x)cos(y)+sinh(x)sin(y)i
	*/
	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = coshl(c.real) * cosl(c.img);
	//ret.img = sinhl(c.real) * sinl(c.img);
	ret = c.ccosh();
	return ret.tgstore(z);
}
long double complex ccoshl(long double complex z)
{
	/*

	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	cosh(x+yi) = cosh(x)cosh(yi)+sinh(x)sinh(yi) =
				 cosh(x)cos(y)+sinh(x)sin(y)i
	*/
	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = coshl(c.real) * cosl(c.img);
	//ret.img = sinhl(c.real) * sinl(c.img);
	ret = c.ccosh();
	return ret.tgstore(z);
}

double complex csinh(double complex z)
{
	/*

	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	sinh(x+yi) = sinh(x)cosh(yi) + cosh(x)sinh(yi) =
				 sinh(x)cos(y) + cosh(x)sin(y)i
	*/

	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = sinhl(c.real) * cosl(c.img);
	//ret.img = coshl(c.real) * sinl(c.img);
	ret = c.csinh();
	return ret.tgstore(z);
}

float complex csinhf(float complex z)
{
	/*

	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	sinh(x+yi) = sinh(x)cosh(yi) + cosh(x)sinh(yi) =
				 sinh(x)cos(y) + cosh(x)sin(y)i
	*/

	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = sinhl(c.real) * cosl(c.img);
	//ret.img = coshl(c.real) * sinl(c.img);
	ret = c.csinh();
	return ret.tgstore(z);
}

long double complex csinhl(long double complex z)
{
	/*
	
	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	sinh(x+yi) = sinh(x)cosh(yi) + cosh(x)sinh(yi) =
				 sinh(x)cos(y) + cosh(x)sin(y)i
	*/

	cplx c;
	cplx ret;
	c.tgload(z);
	//ret.real = sinhl(c.real) * cosl(c.img);
	//ret.img = coshl(c.real) * sinl(c.img);
	ret = c.csinh();
	return ret.tgstore(z);
}

double complex ctanh(double complex z)
{
	/*
	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	tanh(ix) = i*tan(x)
	tanh(x) = -i*tan(ix)

				 sinh(2a) + i*sin(2b)
	tanh(x+yi) = --------------------
				 cosh(2a) + cos(2b)
	*/
	cplx c;
	cplx ret;
	c.tgload(z);
	ret = c.ctanh();
	//c.real *= 2.l;
	//c.img *= 2.l;
	//long double divisor = coshl(c.real) + cosl(c.img);
	//ret.real = sinhl(c.real) / divisor;
	//ret.img = sin(c.img) / divisor;
	return ret.tgstore(z);
}
float complex ctanhf(float complex z)
{
	/*
	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	tanh(ix) = i*tan(x)
	tanh(x) = -i*tan(ix)

				 sinh(2a) + i*sin(2b)
	tanh(x+yi) = --------------------
				 cosh(2a) + cos(2b)
	*/

	cplx c;
	cplx ret;
	c.tgload(z);
	ret = c.ctanh();
	//c.real *= 2.l;
	//c.img *= 2.l;
	//long double divisor = coshl(c.real) + cosl(c.img);
	//ret.real = sinhl(c.real) / divisor;
	//ret.img = sin(c.img) / divisor;
	return ret.tgstore(z);
}
long double complex ctanhl(long double complex z)
{
	/*
	cos(i*x) = cosh(x)
	sin(i*x) = i*sinh(x)

	cosh(i*x) = cos(x)
	sinh(i*x) = i*sin(x)

	tanh(ix) = i*tan(x)
	tanh(x) = -i*tan(ix)

				 sinh(2a) + i*sin(2b)
	tanh(x+yi) = --------------------
				 cosh(2a) + cos(2b)
	*/
	
	cplx c;
	cplx ret;
	c.tgload(z);
	ret = c.ctanh();
	//c.real *= 2.l;
	//c.img *= 2.l;
	//long double divisor = coshl(c.real) + cosl(c.img);
	//ret.real = sinhl(c.real) / divisor;
	//ret.img = sin(c.img) / divisor;
	return ret.tgstore(z);
}