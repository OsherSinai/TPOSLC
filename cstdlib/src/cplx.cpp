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
#include "cplx.h"
#include <include\math.h>
#include <include\stdbool.h>

//TODO: recheck the sign constranits

cplx cplx_polar::convert()
{
	cplx ret;
	ret.real = mag * cosl(angle);
	ret.img = mag * sinl(angle);
	return ret;
}

cplx operator+(const cplx& l, const cplx& r)
{
	cplx ret;
	ret.real = l.real + r.real;
	ret.img = l.img + r.img;
	return ret;
}
cplx operator-(const cplx& l, const cplx& r)
{
	cplx ret;
	ret.real = l.real - r.real;
	ret.img = l.img - r.img;
	return ret;
}
cplx operator/(const cplx& l, const cplx& r)
{
	cplx ret;
	//double divisor = r.real * r.real + r.img * r.img;
	//ret.real = (l.real * r.real + l.img * r.img) / divisor;
	//ret.img = (l.img * r.real - l.real * r.img) / divisor;
	double a, b, c, d, logbw, denom, x, y;
	int ilogbw = 0;
	a = l.real;
	b = l.img;
	c = r.real; 
	d = r.img;
	logbw = logb(fmax(fabs(c), fabs(d)));
	if (isfinite(logbw)) {
		ilogbw = (int)logbw;
		c = scalbn(c, -ilogbw); d = scalbn(d, -ilogbw);
	}
	denom = c * c + d * d;
	x = scalbn((a * c + b * d) / denom, -ilogbw);
	y = scalbn((b * c - a * d) / denom, -ilogbw);
	/* Recover infinities and zeros that computed as NaN+iNaN; */
	/* the only cases are nonzero/zero, infinite/finite, and finite/infinite,
	... */
	if ((isnan(x)) && (isnan(y))) {
		if ((denom == 0.0) &&
			(!(isnan(a)) || !(isnan(b)))) {
			x = copysign(INFINITY, c) * a;
			y = copysign(INFINITY, c) * b;
		}
		else if ((isinf(a) || isinf(b)) &&
			isfinite(c) && isfinite(d)) {
			a = copysign(isinf(a) ? 1.0 : 0.0, a);
			b = copysign(isinf(b) ? 1.0 : 0.0, b);
			x = INFINITY * (a * c + b * d);
			y = INFINITY * (b * c - a * d);
		}
		else if ((logbw == INFINITY) &&
			isfinite(a) && isfinite(b)) {
			c = copysign(isinf(c) ? 1.0 : 0.0, c);
			d = copysign(isinf(d) ? 1.0 : 0.0, d);
			x = 0.0 * (a * c + b * d);
			y = 0.0 * (b * c - a * d);
		}
	}
	ret.real = x;
	ret.img =  y;
	return ret;
}

cplx operator*(const cplx& l, const cplx& r)
{
	cplx ret;
	//ret.real = l.real * r.real - l.img * r.img;
	//ret.img = l.real * r.img + l.img * r.real;
	double a, b, c, d, ac, bd, ad, bc, x, y;
	a = l.real;
	b = l.img;
	c = r.real;
	d = r.img;
	ac = a * c;
	bd = b * d;
	ad = a * d;
	bc = b * c;
	x = ac - bd;
	y = ad + bc;
	if ((isnan(x)) && (isnan(y))) {
		/* Recover infinities that computed as NaN+iNaN ... */
		int recalc = 0;
		if (isinf(a) || isinf(b)) { // z is infinite
			/* "Box" the infinity and change NaNs in the other factor to
			0 */
			a = copysign(isinf(a) ? 1.0 : 0.0, a);
			b = copysign(isinf(b) ? 1.0 : 0.0, b);
			if (isnan(c)) c = copysign(0.0, c);
			if (isnan(d)) d = copysign(0.0, d);
			recalc = 1;
		}
		if (isinf(c) || isinf(d)) { // w is infinite
			/* "Box" the infinity and change NaNs in the other factor to
			0 */
			c = copysign(isinf(c) ? 1.0 : 0.0, c);
			d = copysign(isinf(d) ? 1.0 : 0.0, d);
			if (isnan(a)) a = copysign(0.0, a);
			if (isnan(b)) b = copysign(0.0, b);
			recalc = 1;
		}
		if (!recalc && (isinf(ac) || isinf(bd) ||
			isinf(ad) || isinf(bc))) {
			/* Recover infinities from overflow by changing NaNs to 0
			... */
			if (isnan(a)) a = copysign(0.0, a);
			if (isnan(b)) b = copysign(0.0, b);
			if (isnan(c)) c = copysign(0.0, c);
			if (isnan(d)) d = copysign(0.0, d);
			recalc = 1;
		}
		if (recalc) {
			x = INFINITY * (a * c - b * d);
			y = INFINITY * (a * d + b * c);
		}
	}
	ret.real = x;
	ret.img = y;
	return ret;
}

cplx operator*(const float& l, const cplx& r)
{
	cplx ret;
	long double t = l;
	ret.real = t * r.real;
	ret.img = t * r.img;
	return ret;
}

cplx operator*(const double& l, const cplx& r)
{
	cplx ret;
	long double t = l;
	ret.real = t * r.real;
	ret.img = t * r.img;
	return ret;
}

cplx operator*(const long double& l, const cplx& r)
{
	cplx ret;
	ret.real = l * r.real;
	ret.img = l * r.img;
	return ret;
}


void cplx::load_float(const float _Complex c)
{
	float* p = (float*)&c;
	this->real = (long double)p[0];
	this->img = (long double)p[1];
}
void cplx::load_double(const double _Complex c)
{
	double* p = (double*)&c;
	this->real = (long double)p[0];
	this->img = (long double)p[1];
}
void cplx::load_long_double(const long double _Complex c)
{
	long double* p = (long double*)&c;
	this->real = p[0];
	this->img = p[1];
}
float _Complex cplx::store_float()
{
	return { (float)this->real, (float)this->img };
}
double _Complex cplx::store_double()
{
	return { (double)this->real, (double)this->img };
}
long double _Complex cplx::store_long_double()
{
	return { this->real, this->img };
}

cplx_polar cplx::convert()
{
	cplx_polar polar;
	polar.mag = this->abs();
	polar.angle = acosl(real / polar.mag);
	if (signbit(img))
		polar.angle = -polar.angle;
	return polar;
}
long double cplx::abs()
{
	return hypotl(this->real, this->img);//sqrtl(real * real + img * img);
}

cplx cplx::sqrt()
{
	// sqrt(z) = sqrt(r)*((z+r)/|z+r|), r = |z|
	cplx ret;
	if (isinf(this->img))
	{
		ret.real = INFINITY;
		ret.img = INFINITY;
	}
	else if (isinf(this->real))
	{
		long double sec = isnan(this->img) ? NAN : 0.l;
		if (signbitld(this->real))
		{
			ret.real = sec;
			ret.img = INFINITY;
		}
		else
		{
			ret.real = INFINITY;
			ret.img = sec;
		}
	}
	else if (isnan(this->real) || isnan(this->img))
	{
		ret.real = NAN;
		ret.img = NAN;
	}
	else
	{
		auto pol = this->convert();
		pol.mag = sqrtl(pol.mag);
		pol.angle /= 2.;
		ret = pol.convert();
	}
	return ret;
}

cplx cplx::pow(long double n)
{
	cplx_polar pol = convert();
	cplx ret;
	long double nmag = powl(pol.mag, n);
	ret.real = nmag * cosl(n * pol.angle);
	ret.img = nmag * sinl(n * pol.angle);
	return ret;
}

long double cplx::carg()
{
	/*
	cplx_polar pol;
	pol = this->convert();
	if (signbit(this->img))
		pol.angle = -pol.angle;
	return pol.angle;
	*/
	return atan2(this->img, this->real);
}

cplx cplx::cpow(cplx p)
{
	cplx ret;
	cplx_polar pol;
	long double absx = this->abs();
	long double cargx;
	if (absx != 0.l)
	{
		cargx = this->carg();
		pol.mag = powl(absx, p.real);
		pol.angle = p.real * cargx;
		if (p.img != 0.l)
		{
			pol.mag = pol.mag * expl(-p.img * cargx);
			pol.angle = pol.angle + p.img * logl(absx);
		}
		ret = pol.convert();
	}
	else
	{
		ret.real = 0.l;
		ret.img = 0.l;
	}
	return ret;
}

cplx cplx::cexp()
{
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l && this->img == 0.l)
	{
		ret.real = 1.l;
		ret.img = 0.l;
	}
	else if (isinf(this->real))
	{
		if (signbit(this->real) == 0)
		{
			//inf
			ret.real = INFINITY;
			if (this->real == 0.l)
			{
				ret.img = 0.l;
			}
			else if (isinf(this->img))
			{
				ret.img = NAN;
			}
			else if (isnan(this->img))
			{
				ret.img = NAN;
			}
			else if (isfinite(this->img))
			{
				cplx zero;
				zero.real = INFINITY;
				zero.img = 0.l;
				ret = zero * cplx::cis(this->img);
			}
			else
			{
				bNonspecial = true;
			}
		}
		else
		{
			//-inf
			ret.real = 0.l;
			if (isinf(this->img))
			{
				ret.img = 0.l;
			}
			else if (isnan(this->img))
			{
				ret.img = 0.l;
			}
			else if (isfinite(this->img) && this->img != 0.l)
			{
				cplx zero;
				zero.real = 0.l;
				zero.img = 0.l;
				ret = zero * cplx::cis(this->img);
			}
			else
			{
				bNonspecial = true;
			}
		}
	}
	else if(isnan(this->real))
	{
		ret.real = NAN;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else if (isfinite(this->img) && this->img == 0.l)
		{
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else
	{
		if (isfinite(this->real) && (isnan(this->img)))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else if(isfinite(this->real) && (isnan(this->img)))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}

	
	if(bNonspecial)
	{
		long double ex = expl(this->real);
		ret.real = cosl(this->img) * ex;
		ret.img = sinl(this->img) * ex;
	}
	return ret;
}

cplx cplx::clog()
{
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l)
	{
		if (this->img == 0.l)
		{
			ret.real = -INFINITY;
			ret.img = signbit(this->real) ? M_PI : 0.l;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isnan(this->real))
	{
		if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else if (isinf(this->img))
		{
			ret.real = INFINITY;
			ret.img = NAN;
		}
		else
		{
			ret.real = NAN;
			ret.img = NAN;
		}
	}
	else if (isinf(this->img))
	{
		if (isinf(this->real) == 0)
		{
			ret.real = INFINITY;
			ret.img = M_PI_2;
		}
		else if (signbit(this->real))
		{
			ret.real = INFINITY;
			ret.img = M_PI_4*3.l;
		}
		else
		{
			ret.real = INFINITY;
			ret.img = M_PI_4;
		}
	}
	else if (isinf(real))
	{
		if (isnan(this->img))
		{
			ret.real = INFINITY;
			ret.img = NAN;
		}
		else if (signbit(this->real))
		{
			ret.real = INFINITY;
			ret.img = M_PI;
		}
		else
		{
			ret.real = INFINITY;
			ret.img = 0.l;
		}
	}
	else if (isnan(this->img))
	{
		ret.real = NAN;
		ret.img = NAN;
	}
	else
	{
		bNonspecial = true;
	}
	
	if(bNonspecial)
	{
		ret.real = logl(sqrtl(this->real * this->real + this->img * this->img));
		ret.img  = atan2l(this->img, this->real);
	}

	return ret;
}

cplx cplx::csinh()
{
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l && this->img == 0.l)
	{
		ret.real = 0.l;
		ret.img = 0.l;
	}
	else if (isinf(this->img))
	{
		ret.img = NAN;
		if (this->real == 0.l)
		{
			ret.real = 0.l;
		}
		else if (isinf(this->real) && signbit(this->real) == 0)
		{
			ret.real = INFINITY;
		}
		else if (signbit(this->real) == 1)
		{
			bNonspecial = true;
		}
		else 
		{
			ret.real = NAN;
		}
	}
	else if (isnan(this->img))
	{
		ret.img = NAN;
		if (this->real == 0.l)
		{
			ret.real = 0.l;
		}
		else if (isinf(this->real) && signbit(this->real) == 0)
		{
			ret.real = INFINITY;
		}
		else if (signbit(this->real) == 1)
		{
			bNonspecial = true;
		}
		else
		{
			ret.real = NAN;
		}
	}
	else if (isinf(this->real))
	{
		ret.real = INFINITY;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else
		{
			ret.img = INFINITY;
		}
	}
	else if (isnan(this->real))
	{
		ret.real = NAN;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else
		{
			ret.img = NAN;
		}
	}
	else
	{
		bNonspecial = true;
	}

	if (bNonspecial)
	{
		ret.real = sinhl(this->real) * cosl(this->img);
		ret.img = coshl(this->real) * sinl(this->img);
	}
	return ret;
}

cplx cplx::catan()
{
	cplx c1;
	cplx ret;
	cplx i;
	i.real = 0.l;
	i.img = 1.l;
	c1.real = -this->img;
	c1.img = this->real;
	//c1 = i * (*this);
	c1 = c1.catanh();
	i.real = -0.l;
	i.img = -i.img;

	//ret.real = c1.img;
	//ret.img = -c1.real;
	ret = i * c1;
	ret.real = copysign(ret.real, this->real);

	//if (this->real == 0.l && signbit(this->real) == 0)
	//	ret.real = -ret.real;
	return ret;
}

cplx cplx::catanh()
{
	/*
	artanh(z) = 0.5*ln[(1+z) / (1-z)]
	*/
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l)
	{
		ret.real = 0.l;
		if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (this->real == 1.l && this->img == 0.l)
	{
		ret.real = INFINITY;
		ret.img = 0.l;
	}
	else if (isinf(this->real))
	{
		ret.real = 0.l;
		if (isinf(this->img))
		{
			ret.img = M_PI_2;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else if (isfinite(this->img))
		{
			ret.img = M_PI_2;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if(isnan(this->real))
	{
		if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else if (isinf(this->img))
		{
			ret.real = 0;
			ret.img = M_PI_2;
		}
		else if (isfinite(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else
	{
		if (signbit(this->real) == 0 && isinf(this->img))
		{
			ret.real = 0;
			ret.img = M_PI_2;
		}
		else if (this->real != 0.l && (isnan(this->img)))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}

	if (bNonspecial)
	{
		cplx c1;
		cplx cpl1;
		cplx cpl2;
		cplx cpx;
		c1.real = 1.l;
		c1.img = 0.l;
		cpl1 = c1 + *this;
		cpl2 = c1 - *this;
		cpx = cpl1 / cpl2;
		ret = cpx.clog();
		c1.real = 0.5l;
		ret = ret * c1;
		//if (this->img == 0.l && signbit(this->img) == 0)
		//	ret.img = -ret.img;

		ret.img = copysignl(ret.img, this->img);
	}
	return ret;
}

cplx cplx::casinh()
{
	/*
	asinh(z) = ln(z + sqrt(1 + z^2))
	*/
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l && this->img == 0.l)
	{
		ret.real = 0.l;
		ret.img = 0.l;
	}
	else if (isinf(this->real) && signbit(this->real) == 0)
	{
		ret.real = INFINITY;
		if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else if(isinf(this->img) && signbit(this->img) == 0)
		{
			ret.img = M_PI_4;
		}
		else if (isfinite(this->img) && signbit(this->img) == 0)
		{
			ret.img = 0.l;
		}
		else
		{ 
			bNonspecial = true;
		}
	}
	else if (isnan(this->real))
	{
		if (isinf(this->img) )
		{
			ret.real = INFINITY;
			ret.img = NAN;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else if (this->img == 0.l)
		{
			ret.real = NAN;
			ret.img = 0.l;
		}
		else if (isfinite(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isfinite(this->real))
	{
		if (isinf(this->img) && signbit(this->img) == 0 && signbit(this->real) == 0)
		{
			ret.real = INFINITY;
			ret.img = M_PI_2;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}

	if (bNonspecial)
	{
		/*
		asinh(z) = ln(z + sqrt(1 + z^2))
		*/
		cplx c1;
		cplx sqrtt;
		c1.real = 1.l;
		c1.img = 0.l;
		sqrtt = (*this * *this) + c1;
		sqrtt = sqrtt.sqrt() + *this;
		ret = sqrtt.clog();
		if (this->real == 0.l && signbit(this->real))
			ret.real = -ret.real;
	}
	return ret;
}

cplx cplx::cacosh()
{
	//cacosh(z) = ln(z + sqrt(z+1)*sqrt(z-1)
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l)
	{
		ret.img = M_PI_2;
		if (this->img == 0.l)
		{
			ret.real = 0.l;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isinf(this->real))
	{
		ret.real = INFINITY;
		if (signbit(this->real))
		{
			//-inf
			if (isinf(this->img))
			{
				ret.img = 3.l * M_PI_4;
			}
			else if (isnan(this->img))
			{
				ret.img = NAN;
			}
			else if (isfinite(this->img) && signbit(this->img) == 0)
			{
				ret.img = M_PI;
			}
			else
			{
				bNonspecial = true;
			}
		}
		else
		{
			//inf
			if (isinf(this->img))
			{
				ret.img = M_PI_4;
			}
			else if (isnan(this->img))
			{
				ret.img = NAN;
			}
			else if (isfinite(this->img) && signbit(this->img) == 0)
			{
				ret.img = 0.l;
			}
			else
			{
				bNonspecial = true;
			}
		}
	}
	else if (isnan(this->real))
	{
		ret.img = NAN;
		if (isnan(this->img))
		{
			ret.real = NAN;
		}
		else if (isinf(this->img))
		{
			ret.real = INFINITY;
		}
		else if (isfinite(this->img))
		{
			ret.real = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isfinite(this->real))
	{
		if (isinf(this->img))
		{
			ret.real = INFINITY;
			ret.img = M_PI_2;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else
	{
		bNonspecial = true;
	}



	if (bNonspecial)
	{
		cplx c1;
		cplx zm1;
		cplx zp1;
		c1.real = 1.l;
		c1.img = 0.l;
		zm1 = *this - c1;
		zm1 = zm1.sqrt();
		zp1 = *this + c1;
		zp1 = zp1.sqrt();
		ret = *this + zm1 * zp1;
		ret = ret.clog();
	}
	return ret;
}

cplx cplx::cis(long double y)
{
	cplx ret;
	ret.real = cosl(y);
	ret.img = sinl(y);
	return ret;
}

cplx cplx::cacos()
{
	//acos(z)=0.5pi + iln(iz + sqrt(1-z))^2?
	/*
	cplx ret = this->casin();
	ret.real = M_PI_2 - ret.real;
	ret.img = -ret.img;
	return ret;
	*/
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l)
	{
		ret.real = M_PI_2;
		if (this->img == 0.l)
		{
			ret.img = -0.l;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isinf(this->real))
	{
		ret.img = -INFINITY;
		if (isnan(this->img))
		{
			ret.real = NAN;
		}
		else if (signbit(this->real))
		{
			if (isinf(this->img))
			{
				ret.real = 3.l * M_PI_4;
			}
			else if (signbit(this->img) == 0)
			{
				ret.real = M_PI;
			}
			else
			{
				bNonspecial = true;
			}
		}
		else
		{
			if (isinf(this->img))
			{
				ret.real = M_PI_4;
			}
			else if(signbit(this->img) == 0)
			{
				ret.real = 0.l;
			}
			else
			{
				bNonspecial = true;
			}
		}
	}
	else if (isnan(this->real))
	{
		ret.real = NAN;
		if (isinf(this->img))
		{
			ret.img = -INFINITY;
		}
		else if (isfinite(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isfinite(this->real))
	{
		if (isinf(this->img))
		{
			ret.real = M_PI_2;
			ret.img = -INFINITY;
		}
		else if (this->real != 0.l && (isnan(this->img)))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else
	{
		bNonspecial = true;
	}

	if(bNonspecial)
	{
		cplx m1;
		cplx sqrtt;
		cplx isub;
		cplx pis2;
		m1.real = 1.l;
		m1.img = 0.l;
		sqrtt = m1 - (*this * *this);
		sqrtt = sqrtt.sqrt();
		isub.img = this->real;
		isub.real = -this->img;
		sqrtt = sqrtt + isub;
		sqrtt = sqrtt.clog();
		isub.real = -sqrtt.img;
		isub.img = sqrtt.real;
		pis2.real = M_PI_2;
		pis2.img = 0.l;
		ret = pis2 + isub;

		if (signbit(ret.img) == signbit(this->img))
			ret.img = -ret.img;
	}
	return ret;
}

cplx cplx::casin()
{
	/*
	inter.real = 1.l - (c.real - c.img) * (c.real * c.img);
	inter.img = -2.l * c.real * c.img;
	c.swap();
	c.real = -c.real;
	inter = c + inter.sqrt();
	inter = inter.clog();
	ret.real = inter.img;
	ret.img = -inter.real;
	*/

	cplx c;
	cplx ret;
	c.real = -this->img;
	c.img = this->real;
	c = c.casinh();
	ret.real = c.img;
	ret.img = c.real;
	//cplx InverseI(0.l, 1.l);
	//c = *this;
	//c = c * InverseI;
	//c = c.casinh();
	//InverseI.img = -InverseI.img;
	//ret = c * InverseI;
	//ret.img = -ret.img;
	return ret;
}

cplx cplx::ccosh()
{
	cplx ret;
	bool bNonspecial = false;
	if (this->real == 0.l)
	{
		ret.img = 0.l;
		if (this->img == 0.l)
		{
			ret.real = 1.l;
		}
		else if (isinf(this->img))
		{
			ret.real = NAN;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isinf(this->real) && signbit(this->real) == 0)
	{
		ret.real = INFINITY;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else if (isinf(this->img))
		{
			ret.img = NAN;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			ret.img = INFINITY;
		}
	}
	else if(isnan(this->real))
	{
		ret.real = NAN;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			ret.img = NAN;
		}
	}
	else if(isinf(this->img))
	{
		ret.real = NAN;
		ret.img = NAN;
	}
	else if (isnan(this->img))
	{
		ret.real = NAN;
		ret.img = NAN;
	}
	else
	{
		bNonspecial = true;
	}

	if (bNonspecial)
	{
		ret.real = coshl(this->real) * cosl(this->img);
		ret.img = sinhl(this->real) * sinl(this->img);
	}

	return ret;
}

cplx cplx::ctan()
{
	cplx c;
	cplx ret;
	c.real = -this->img;
	c.img = this->real;
	c = c.ctanh();
	ret.real = c.img;
	ret.img = -c.real;
	return ret;
}

cplx cplx::ctanh()
{
	cplx ret;
	bool bNonspecial = false;

	if (this->real == 0.l)
	{
		ret.real = 0.l;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else if (isinf(this->img))
		{
			ret.img = NAN;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isinf(this->real) && signbit(this->real) == 0)
	{
		ret.real = 1.l;
		if (isinf(this->img))
		{
			ret.img = 0.l;
		}
		else if (isnan(this->img))
		{
			ret.img = 0.l;
		}
		else if (isfinite(this->img))
		{
			ret.img = 0.l * sinl(2.l * this->img);
		}
		else
		{
			bNonspecial = true;
		}
	}
	else if (isnan(this->real))
	{
		ret.real = NAN;
		if (this->img == 0.l)
		{
			ret.img = 0.l;
		}
		else if (isnan(this->img))
		{
			ret.img = NAN;
		}
		else
		{
			ret.img = NAN;
		}
	}
	else
	{
		if (isinf(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else if (isnan(this->img))
		{
			ret.real = NAN;
			ret.img = NAN;
		}
		else
		{
			bNonspecial = true;
		}
	}

	if (bNonspecial)
	{
		cplx c;
		c = *this;
		c.real *= 2.l;
		c.img *= 2.l;
		long double divisor = coshl(c.real) + cosl(c.img);
		ret.real = sinhl(c.real) / divisor;
		ret.img = sinl(c.img) / divisor;
	}

	return ret;
}

void cplx::swap()
{
	long double tmp = real;
	real = img;
	img = tmp;
}


cplx cplx::cos()
{
	// changed function to comply with G6.7
	//trig substitution cos(z) = cos(a+bi) = cos(a)cos(bi)-sin(a)sin(bi)
	cplx ret;
	//ret.real = cosl(this->real)* coshl(this->img);
	//ret.img = -(sinl(this->real) * sinhl(this->img));
	ret.real = -this->img;
	ret.img = this->real;
	ret = ret.ccosh();
	return ret;
}

cplx cplx::sin()
{
	//trig substitute sin(z) = sin(a+bi) = sin(a)cos(bi)+cos(a)sin(bi) = sin(a)cosh(b)+cos(a)*sinh(b)i
	cplx ret;
	ret.real = sinl(this->real) * coshl(this->img);
	ret.img = cosl(this->real) * sinhl(this->img);
	return ret;
}