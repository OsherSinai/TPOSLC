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

//constexpr long double ldpie = 3.1415926535897932384626433832795028841971693993751058209749445923l;
//constexpr long double recipocal_2divsqrtpi = 1.12837916709551257389615890312154517168810125865799771368817144342128493688298682897348732040421472688605669581272341470337986298965232573273097904003553798658567527411919687952070492870043594514242316049154564044110901705434643324441692661622279902552690897l;
double erf(double x)
{
	return (double)erfl((long double)x);
}
float erff(float x)
{
	return (float)erfl((long double)x);
}
long double erfl(long double x)
{
	// erf(x) = 2/sqrt(pi) * int(x,0){e^(-t^2)}
	//return recipocal_2divsqrtpi * (powl(M_E, -(x * x)) - 1.l);

	long double fa;
	if ((isinf(x)) == 0 && (isnan(x) == 0))
	{
		long double a = (8.l * (M_PI - 3.l)) / ((3.l * M_PI) * (4 - M_PI));

		long double axx = a * (x * x);

		long double lu = (4.l / M_PI) + axx;
		long double ll = 1.l + axx;

		long double rexp = expl((-(x * x)) * ((lu) / (ll)));

		fa = sqrtl(1.l - rexp);
	}
	else
	{
		if ((isinf(x)) != 0)
			fa = 1.;
		else
			fa = x;
	}

	return copysignl(fa, x);
}

double erfc(double x)
{
	return (double)erfcl((long double)x);
}
float erfcf(float x)
{
	return (float)erfcl((long double)x);
}
long double erfcl(long double x)
{
	return 1.l - erfl(x);
}

double lgamma(double x)
{
	double ret;
	if (isnan(x))
		ret = NAN;
	else if (x == INFINITY || x == -INFINITY || x <= 0.l)
		ret = INFINITY;
	else if (x <= 2.l)
		ret = 0.l;
	else
		ret = log(fabs(tgamma(x)));
	return ret;
}
float lgammaf(float x)
{
	float ret;
	if (isnan(x))
		ret = NAN;
	else if (x == INFINITY || x == -INFINITY || x <= 0.l)
		ret = INFINITY;
	else if (x <= 2.l)
		ret = 0.l;
	else
		ret = logf(fabsf(tgammaf(x)));
	return ret;
}
long double lgammal(long double x)
{
	long double ret;
	if (isnan(x))
		ret = NAN;
	else if (x == INFINITY || x == -INFINITY || x <= 0.l)
		ret = INFINITY;
	else if (x <= 2.l)
		ret = 0.l;
	else
		ret = logl(fabsl(tgammal(x)));
	return ret;
}

double tgamma(double x)
{
	return (double)tgammal((long double)x);
}
float tgammaf(float x)
{
	return (float)tgammal((long double)x);
}


static constexpr long double c_StirlingCoeffnumerators[17] = {
	1.l,
	1.l,
	1.l,
	-139.l,
	-571.l,
	163879.l,
	5246819.l,
	-534703531.l,
	-4483131259.l,
	432261921612371.l,
	6232523202521089.l,
	-25834629665134204969.l,
	-1579029138854919086429.l,
	746590869962651602203151.l,
	1511513601028097903631961.l,
	-8849272268392873147705987190261.l,
	-142801712490607530608130701097701.l
};
static constexpr long double c_StirlingCoeffDenumerators[17] = {
		1.l,
		12.l,
		288.l,
		51840.l,
		2488320.l,
		209018880.l,
		75246796800.l,
		902961561600.l,
		86684309913600.l,
		514904800886784000.l,
		86504006548979712000.l,
		13494625021640835072000.l,
		9716130015581401251840000.l,
		116593560186976815022080000.l,
		2798245444487443560529920000.l,
		299692087104605205332754432000000.l,
		57540880724084199423888850944000000.l
};
static long double StirlingCoeff(long double n)
{
	long double ret = 0.;
	for (size_t i = 0; i < 12; i++)
		ret += (
			c_StirlingCoeffnumerators[i] / 
			(c_StirlingCoeffDenumerators[i] * powl(n, i))
			);
	return ret;
}

long double tgammal(long double x)
{
	// Stirling's approximation
	long double ret = 0.l;
	if (x == -INFINITY || x < 0.l || (isnan(x) != 0))
		ret = NAN;
	else if (x == 0.l)
		ret = copysignl(INFINITY, x);
	else if (x == INFINITY)
		ret = INFINITY;
	else if (x <= 2.l)
		ret = 1.l;
	else
	{
		//An explicit formula for the coefficients in this series was given by G. Nemes
		//On the Coefficients of the Asymptotic Expansion of n!
		x -= 1.l;
		long double Stirling = sqrt(2.l * M_PI * x) * powl(x / M_E, x);

		long double coeff = StirlingCoeff(x);
		ret = coeff * Stirling;
	}

	return ret;
}