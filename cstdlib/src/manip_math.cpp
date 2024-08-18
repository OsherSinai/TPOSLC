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
#include <include\stddef.h>
#include <include\math.h>
#include <include\stdlib.h>
#include "x87_float.h"
double copysign(double x, double y)
{
	constexpr uint64_t mask = (1ull << 63);
	decltype(mask) ysign = (decltype(mask))y & mask;
	return (double)((decltype(mask))x ^ ysign);
}
float copysignf(float x, float y)
{
	constexpr uint32_t mask = (1ull << 31);
	decltype(mask) ysign = (decltype(mask))y & mask;
	return (double)((decltype(mask))x ^ ysign);
}

long double copysignl(long double x, long double y)
{
	uint8_t mask = 0x80;
	decltype(mask) ysign = ((uint8_t*)&y)[9] & mask;
	((uint8_t*)&x)[9] = ((uint8_t*)&x)[9] ^ ysign;
	return x;
}


double nan(const char* tagp)
{
	return strtod(tagp, NULL);
}
float nanf(const char* tagp)
{
	return strtof(tagp, NULL);
}
long double nanl(const char* tagp)
{
	return strtold(tagp, NULL);
}

double nextafter(double x, double y)
{
	double ret;
	x87_double* p = (x87_double*)&x;
	if (isinf(x) != 0 || isinf(y) != 0)
	{
		if (isinf(x) != 0)
			ret = copysignf(x, y);
		else
			ret = y;
	}
	else if ((isnan(x) != 0) || (isnan(y) != 0))
	{
		if ((isnan(x)) != 0)
			ret = copysignf(x, y);
		else
			ret = y;
	}
	else
	{
		if (x > y)
		{
			p->bitfield.fraction--;
			if (p->bitfield.fraction == ~0)
				p->bitfield.exponent++;
			ret = p->val;
		}
		else if (x < y)
		{
			p->bitfield.fraction++;
			if (p->bitfield.fraction == 0)
				p->bitfield.exponent++;
			ret = p->val;
		}
		else
		{
			ret = y;
		}
	}
	return ret;
}
float nextafterf(float x, float y)
{
	float ret;
	x87_float* p = (x87_float*)&x;
	if (isinf(x) != 0 || isinf(y) != 0)
	{
		if (isinf(x) != 0)
			ret = copysignf(x, y);
		else
			ret = y;
	}
	else if ((isnan(x)) != 0 || (isnan(y) != 0))
	{
		if ((isnan(x)) != 0)
			ret = copysignf(x, y);
		else
			ret = y;
	}
	else
	{
		if (x > y)
		{
			p->bitfield.fraction--;
			if (p->bitfield.fraction == ~0)
				p->bitfield.exponent++;
			ret = p->val;
		}
		else if (x < y)
		{
			p->bitfield.fraction++;
			if (p->bitfield.fraction == 0)
				p->bitfield.exponent++;
			ret = p->val;
		}
		else
		{
			ret = y;
		}
	}
	return ret;
}
long double nextafterl(long double x, long double y)
{
	long double ret;
	if (isinf(x) != 0 || isinf(y) != 0)
	{
		if (isinf(x) != 0)
			ret = copysignl(x, y);
		else
			ret = y;
	}
	else if ((isnan(x)) != 0 || (isnan(y) != 0))
	{
		if ((isnan(x)) != 0)
			ret = copysignl(x, y);
		else
			ret = y;
	}
	else
	{
		if (x > y)
		{
			if constexpr (sizeof(long double) == 10)
			{
				x87_long_double* p = (x87_long_double*)&x;
				p->bitfield.fraction--;
				if (p->bitfield.fraction == ~0)
					p->bitfield.exponent++;
				ret = p->val;
			}
			else
			{
				x87_double* p = (x87_double*)&x;
				p->bitfield.fraction--;
				if (p->bitfield.fraction == ~0)
					p->bitfield.exponent--;
				ret = p->val;
			}
		}
		else if (x < y)
		{
			if constexpr (sizeof(long double) == 10)
			{
				x87_long_double* p = (x87_long_double*)&x;
				p->bitfield.fraction++;
				if (p->bitfield.fraction == 0)
					p->bitfield.exponent++;
				ret = p->val;
			}
			else
			{
				x87_double* p = (x87_double*)&x;
				p->bitfield.fraction++;
				if (p->bitfield.fraction == 0)
					p->bitfield.exponent++;
				ret = p->val;
			}
		}
		else
		{
			ret = y;
		}
	}
	return ret;
}


double nexttoward(double x, long double y)
{
	return nexttowardl(x, y);
}
float nexttowardf(float x, long double y)
{
	return nexttowardl(x, y);
}
long double nexttowardl(long double x, long double y)
{
	long double ret;
	if (isinf(x) != 0 || isinf(y) != 0)
	{
		if (isinf(x) != 0)
			ret = copysignl(x, y);
		else
			ret = y;
	}
	else if ((isnan(x)) != 0 || (isnan(y)) != 0)
	{
		if ((isnan(x)) != 0)
			ret = copysignl(x, y);
		else
			ret = y;
	}
	else
	{
		if (x > y)
		{
			if constexpr (sizeof(long double) == 10)
			{
				x87_long_double* p = (x87_long_double*)&x;
				p->bitfield.fraction--;
				if (p->bitfield.fraction == ~0)
					p->bitfield.exponent++;
				ret = p->val;
			}
			else
			{
				x87_double* p = (x87_double*)&x;
				p->bitfield.fraction--;
				if (p->bitfield.fraction == ~0)
					p->bitfield.exponent--;
				ret = p->val;
			}
		}
		else if (x < y)
		{
			if constexpr (sizeof(long double) == 10)
			{
				x87_long_double* p = (x87_long_double*)&x;
				p->bitfield.fraction++;
				if (p->bitfield.fraction == 0)
					p->bitfield.exponent++;
				ret = p->val;
			}
			else
			{
				x87_double* p = (x87_double*)&x;
				p->bitfield.fraction++;
				if (p->bitfield.fraction == 0)
					p->bitfield.exponent++;
				ret = p->val;
			}
		}
		else
		{
			ret = y;
		}
	}
	return ret;
}