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
#pragma once
#ifndef TOS_CPLX_H
#define TOS_CPLX_H

class cplx;
class cplx_polar {
public:
	long double mag;
	long double angle;
	cplx convert();
};
class cplx {
public:
	long double real;
	long double img;


	void load_float(const float _Complex c);
	void load_double(const double _Complex c);
	void load_long_double(const long double _Complex c);
	float _Complex store_float();
	double _Complex store_double();
	long double _Complex store_long_double();
	inline void tgload(const float _Complex c)
	{
		load_float(c);
	}
	inline void tgload(const double _Complex c)
	{
		load_double(c);
	}
	inline void tgload(const long double _Complex c)
	{
		load_long_double(c);
	}
	inline float _Complex tgstore(const float _Complex c)
	{
		return store_float();
	}
	inline double _Complex tgstore(const double _Complex c)
	{
		return store_double();
	}
	inline long double _Complex tgstore(const long double _Complex c)
	{
		return store_long_double();
	}

	cplx_polar convert();
	long double abs();
	cplx sqrt();
	long double carg();
	cplx pow(long double n);
	cplx cos();
	cplx sin();

	cplx cpow(cplx p);
	cplx cexp();
	cplx clog();

	cplx csinh();

	
	cplx ccosh();

	cplx ctan();
	cplx ctanh();

	cplx cacos();
	cplx casin();

	cplx catan();
	cplx catanh();
	cplx casinh();

	cplx cacosh();

	static cplx cis(long double y);
	void swap();
};


cplx operator+(const cplx& l, const cplx& r);
cplx operator-(const cplx& l, const cplx& r);
cplx operator/(const cplx& l, const cplx& r);
cplx operator*(const cplx& l, const cplx& r);
cplx operator*(const float& l, const cplx& r);
cplx operator*(const double& l, const cplx& r);
cplx operator*(const long double& l, const cplx& r);
#endif // !TOS_CPLX_H
