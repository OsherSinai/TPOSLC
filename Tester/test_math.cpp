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
#include "TestCaseUtils.h"
#include "TestSuites.h"
#include <include/math.h>
#include <include/string.h>
#include <include/limits.h>
#include <include/float.h>
#include <include/fenv.h>
void test_fpclassify()
{
	CASE_CHECK_EQ(isfinitef(HUGE_VALF), 0,				"isfinite float, infinity");
	CASE_CHECK_EQ(isfinitef(-HUGE_VALF), 0,				"isfinite float, -infinity");
	CASE_CHECK_EQ(isfinitef(1.f), 1,					"isfinite float, one");
	CASE_CHECK_EQ(isfinitef(0.f), 1,					"isfinite float, zero");
	CASE_CHECK_EQ(isfinited(HUGE_VAL), 0,				"isfinite double, infinity");
	CASE_CHECK_EQ(isfinited(-HUGE_VAL), 0,				"isfinite double, -infinity");
	CASE_CHECK_EQ(isfinited(1.), 1,						"isfinite double, one");
	CASE_CHECK_EQ(isfinited(0.), 1,						"isfinite double, zero");
	CASE_CHECK_EQ(isfiniteld(HUGE_VALL), 0,				"isfinite long double, infinity");
	CASE_CHECK_EQ(isfiniteld(-HUGE_VALL), 0,			"isfinite long double, -infinity");
	CASE_CHECK_EQ(isfiniteld(1.l), 1,					"isfinite long double, one");
	CASE_CHECK_EQ(isfiniteld(0.l), 1,					"isfinite long double, zero");
	
	CASE_CHECK_EQ(isinff(HUGE_VALF), 1,					"isinf float, infinity");
	CASE_CHECK_EQ(isinff(-HUGE_VALF), 1,				"isinf float, -infinity");
	CASE_CHECK_EQ(isinff(1.f), 0,						"isinf float, one");
	CASE_CHECK_EQ(isinff(0.f), 0,						"isinf float, zero");
	CASE_CHECK_EQ(isinfd(HUGE_VAL), 1,					"isinf double, infinity");
	CASE_CHECK_EQ(isinfd(-HUGE_VAL), 1,					"isinf double, -infinity");
	CASE_CHECK_EQ(isinfd(1.), 0,						"isinf double, one");
	CASE_CHECK_EQ(isinfd(0.), 0,						"isinf double, zero");
	CASE_CHECK_EQ(isinfld(HUGE_VALL), 1,				"isinf long double, infinity");
	CASE_CHECK_EQ(isinfld(-HUGE_VALL), 1,				"isinf long double, -infinity");
	CASE_CHECK_EQ(isinfld(1.l), 0,						"isinf long double, one");
	CASE_CHECK_EQ(isinfld(0.l), 0,						"isinf long double, zero");
	
	CASE_CHECK_EQ(isnormalf(HUGE_VALF), 0,				"isnormal float, infinity");
	CASE_CHECK_EQ(isnormalf(-HUGE_VALF), 0,				"isnormal float, -infinity");
	CASE_CHECK_EQ(isnormalf(NAN), 0,					"isnormal float, nan");
	CASE_CHECK_EQ(isnormalf(-NAN), 0,					"isnormal float, -nan");
	CASE_CHECK_EQ(isnormalf(1.f), 1,					"isnormal float, one");
	CASE_CHECK_EQ(isnormalf(0.f), 0,					"isnormal float, zero");
	CASE_CHECK_EQ(isnormald(HUGE_VAL), 0,				"isnormal double, infinity");
	CASE_CHECK_EQ(isnormald(-HUGE_VAL), 0,				"isnormal double, -infinity");
	CASE_CHECK_EQ(isnormald(NAN), 0,					"isnormal float, nan");
	CASE_CHECK_EQ(isnormald(-NAN), 0,					"isnormal float, -nan");
	CASE_CHECK_EQ(isnormald(1.), 1,						"isnormal double, one");
	CASE_CHECK_EQ(isnormald(0.), 0,						"isnormal double, zero");
	CASE_CHECK_EQ(isnormalld(HUGE_VALL), 0,				"isnormal long double, infinity");
	CASE_CHECK_EQ(isnormalld(-HUGE_VALL), 0,			"isnormal long double, -infinity");
	CASE_CHECK_EQ(isnormalld(NAN), 0,					"isnormal float, nan");
	CASE_CHECK_EQ(isnormalld(-NAN), 0,					"isnormal float, -nan");
	CASE_CHECK_EQ(isnormalld(1.l), 1,					"isnormal long double, one");
	CASE_CHECK_EQ(isnormalld(0.l), 0,					"isnormal long double, zero");
	
	CASE_CHECK_EQ(isnanf(HUGE_VALF), 0,					"isnan float, infinity");
	CASE_CHECK_EQ(isnanf(-HUGE_VALF), 0,				"isnan float, -infinity");
	CASE_CHECK_EQ(isnanf(NAN), 1,						"isnan float, nan");
	CASE_CHECK_EQ(isnanf(-NAN), 1,						"isnan float, -nan");
	CASE_CHECK_EQ(isnanf(1.f), 0,						"isnan float, one");
	CASE_CHECK_EQ(isnanf(0.f), 0,						"isnan float, zero");
	CASE_CHECK_EQ(isnand(HUGE_VAL), 0,					"isnan double, infinity");
	CASE_CHECK_EQ(isnand(-HUGE_VAL), 0,					"isnan double, -infinity");
	CASE_CHECK_EQ(isnand(NAN), 1,						"isnan float, nan");
	CASE_CHECK_EQ(isnand(-NAN), 1,						"isnan float, -nan");
	CASE_CHECK_EQ(isnand(1.), 0,						"isnan double, one");
	CASE_CHECK_EQ(isnand(0.), 0,						"isnan double, zero");
	CASE_CHECK_EQ(isnanld(HUGE_VALL), 0,				"isnan long double, infinity");
	CASE_CHECK_EQ(isnanld(-HUGE_VALL), 0,				"isnan long double, -infinity");
	CASE_CHECK_EQ(isnanld(NAN), 1,						"isnan float, nan");
	CASE_CHECK_EQ(isnanld(-NAN), 1,						"isnan float, -nan");
	CASE_CHECK_EQ(isnanld(1.l), 0,						"isnan long double, one");
	CASE_CHECK_EQ(isnanld(0.l), 0,						"isnan long double, zero");
	
	CASE_CHECK_EQ(signbitf(HUGE_VALF), 0,				"signbit float, infinity");
	CASE_CHECK_EQ(signbitf(-HUGE_VALF), 1,				"signbit float, -infinity");
	CASE_CHECK_EQ(signbitf(NAN), 1,						"signbit float, nan");
	CASE_CHECK_EQ(signbitf(-NAN), 0,					"signbit float, -nan");
	CASE_CHECK_EQ(signbitf(1.f), 0,						"signbit float, one");
	CASE_CHECK_EQ(signbitf(0.f), 0,						"signbit float, zero");
	CASE_CHECK_EQ(signbitf(-1.f), 1,					"signbit float, -one");
	CASE_CHECK_EQ(signbitf(-0.f), 1,					"signbit float, -zero");
	CASE_CHECK_EQ(signbitd(HUGE_VAL), 0,				"signbit double, infinity");
	CASE_CHECK_EQ(signbitd(-HUGE_VAL), 1,				"signbit double, -infinity");
	CASE_CHECK_EQ(signbitd(NAN), 1,						"signbit float, nan");
	CASE_CHECK_EQ(signbitd(-NAN), 0,					"signbit float, -nan");
	CASE_CHECK_EQ(signbitd(1.), 0,						"signbit double, one");
	CASE_CHECK_EQ(signbitd(0.), 0,						"signbit double, zero");
	CASE_CHECK_EQ(signbitd(-1.), 1,						"signbit double, -one");
	CASE_CHECK_EQ(signbitd(-0.), 1,						"signbit double, -zero");
	CASE_CHECK_EQ(signbitld(HUGE_VALL), 0,				"signbit long double, infinity");
	CASE_CHECK_EQ(signbitld(-HUGE_VALL), 1,				"signbit long double, -infinity");
	CASE_CHECK_EQ(signbitld(NAN), 1,					"signbit float, nan");
	CASE_CHECK_EQ(signbitld(-NAN), 0,					"signbit float, -nan");
	CASE_CHECK_EQ(signbitld(1.l), 0,					"signbit long double, one");
	CASE_CHECK_EQ(signbitld(0.l), 0,					"signbit long double, zero");
	CASE_CHECK_EQ(signbitld(-1.l), 1,					"signbit long double, -one");
	CASE_CHECK_EQ(signbitld(-0.l), 1,					"signbit long double, -zero");

	CASE_CHECK_EQ(fpclassifyf(HUGE_VALF), FP_INFINITE,	"fpclassify float, infinity");
	CASE_CHECK_EQ(fpclassifyf(NAN), FP_NAN,				"fpclassify float, nan");
	CASE_CHECK_EQ(fpclassifyf(1.f), FP_NORMAL,			"fpclassify float, normal");
	CASE_CHECK_EQ(fpclassifyf(0.f), FP_ZERO,			"fpclassify float, zero");
	CASE_CHECK_EQ(fpclassifyd(HUGE_VAL), FP_INFINITE,	"fpclassify double, infinity");
	CASE_CHECK_EQ(fpclassifyd(NAN), FP_NAN,				"fpclassify double, nan");
	CASE_CHECK_EQ(fpclassifyd(1.), FP_NORMAL,			"fpclassify double, normal");
	CASE_CHECK_EQ(fpclassifyd(0.), FP_ZERO,				"fpclassify double, zero");
	CASE_CHECK_EQ(fpclassifyld(HUGE_VALL), FP_INFINITE,	"fpclassify long double, infinity");
	CASE_CHECK_EQ(fpclassifyld(NAN), FP_NAN,			"fpclassify long double, nan");
	CASE_CHECK_EQ(fpclassifyld(1.l), FP_NORMAL,			"fpclassify long double, normal");
	CASE_CHECK_EQ(fpclassifyld(0.l), FP_ZERO,			"fpclassify long double, zero");

}

void test_trigonometry_sine()
{
	CASE_CHECK_BALLPARK(sinf(0), 0.f, 0.0001f, "sin float, 0");
	CASE_CHECK_BALLPARK(sinf(M_PI / 6.f), 0.5f, 0.0001f, "sin float, pi/6");
	CASE_CHECK_BALLPARK(sinf(M_PI / 4.f), 0.707106781187f, 0.0001f, "sin float, pi/4");
	CASE_CHECK_BALLPARK(sinf(M_PI / 3.f), 0.866025403784f, 0.0001f, "sin float, pi/3");
	CASE_CHECK_BALLPARK(sinf(M_PI_2), 1.f, 0.0001f, "sin float, pi/2");
	CASE_CHECK_BALLPARK(sinf(2.f * (M_PI / 3.f)), 0.866025403784f, 0.0001f, "sin float, 2pi/3");
	CASE_CHECK_BALLPARK(sinf(3.f * (M_PI / 4.f)), 0.707106781187f, 0.0001f, "sin float, 3pi/4");
	CASE_CHECK_BALLPARK(sinf(5.f * (M_PI / 6.f)), 0.5f, 0.0001f, "sin float, 5pi/6");
	CASE_CHECK_BALLPARK(sinf(M_PI), 0.f, 0.0001f, "sin float, pi");

	CASE_CHECK_BALLPARK(sin(0), 0., 0.0001, "sin double, 0");
	CASE_CHECK_BALLPARK(sin(M_PI / 6.), 0.5, 0.0001, "sin double, pi/6");
	CASE_CHECK_BALLPARK(sin(M_PI / 4.), 0.707106781187, 0.0001, "sin double, pi/4");
	CASE_CHECK_BALLPARK(sin(M_PI / 3.), 0.866025403784, 0.0001, "sin double, pi/3");
	CASE_CHECK_BALLPARK(sin(M_PI_2), 1., 0.0001, "sin double, pi/2");
	CASE_CHECK_BALLPARK(sin(2. * (M_PI / 3.)), 0.866025403784, 0.0001, "sin double, 2pi/3");
	CASE_CHECK_BALLPARK(sin(3. * (M_PI / 4.)), 0.707106781187, 0.0001, "sin double, 3pi/4");
	CASE_CHECK_BALLPARK(sin(5. * (M_PI / 6.)), 0.5, 0.0001, "sin double, 5pi/6");

	CASE_CHECK_BALLPARK(sinl(M_PI), 0.l, 0.0001l, "sin long double, pi");
	CASE_CHECK_BALLPARK(sinl(M_PI / 6.l), 0.5l, 0.0001l, "sin long double, pi/6");
	CASE_CHECK_BALLPARK(sinl(M_PI / 4.l), 0.707106781187l, 0.0001l, "sin long double, pi/4");
	CASE_CHECK_BALLPARK(sinl(M_PI / 3.l), 0.866025403784l, 0.0001l, "sin long double, pi/3");
	CASE_CHECK_BALLPARK(sinl(M_PI_2), 1.l, 0.0001l, "sin long double, pi/2");
	CASE_CHECK_BALLPARK(sinl(2.l * (M_PI / 3.l)), 0.866025403784l, 0.0001l, "sin long double, 2pi/3");
	CASE_CHECK_BALLPARK(sinl(3.l * (M_PI / 4.l)), 0.707106781187l, 0.0001l, "sin long double, 3pi/4");
	CASE_CHECK_BALLPARK(sinl(5.l * (M_PI / 6.l)), 0.5l, 0.0001l, "sin long double, 5pi/6");
	CASE_CHECK_BALLPARK(sinl(M_PI), 0.l, 0.0001l, "sin long double, pi");
}
void test_trigonometry_cos()
{
	CASE_CHECK_BALLPARK(cosf(0), 1.f, 0.0001f, "cos float, 0");
	CASE_CHECK_BALLPARK(cosf(M_PI / 6.f), 0.866025403784f, 0.0001f, "cos float, pi/6");
	CASE_CHECK_BALLPARK(cosf(M_PI / 4.f), 0.707106781187f, 0.0001f, "cos float, pi/4");
	CASE_CHECK_BALLPARK(cosf(M_PI / 3.f),0.5f, 0.0001f, "cos float, pi/3");
	CASE_CHECK_BALLPARK(cosf(M_PI_2), 0.f, 0.0001f, "cos float, pi/2");
	CASE_CHECK_BALLPARK(cosf(2.f * (M_PI / 3.f)), -0.5f, 0.0001f, "cos float, 2pi/3");
	CASE_CHECK_BALLPARK(cosf(3.f * (M_PI / 4.f)), -0.707106781187f, 0.0001f, "cos float, 3pi/4");
	CASE_CHECK_BALLPARK(cosf(5.f * (M_PI / 6.f)), -0.866025403784f, 0.0001f, "cos float, 5pi/6");
	CASE_CHECK_BALLPARK(cosf(M_PI), -1.f, 0.0001f, "cos float, pi");

	CASE_CHECK_BALLPARK(cos(0), 1., 0.0001, "cos double, 0");
	CASE_CHECK_BALLPARK(cos(M_PI / 6.), 0.866025403784, 0.0001, "cos double, pi/6");
	CASE_CHECK_BALLPARK(cos(M_PI / 4.), 0.707106781187, 0.0001, "cos double, pi/4");
	CASE_CHECK_BALLPARK(cos(M_PI / 3.), 0.5, 0.0001, "cos double, pi/3");
	CASE_CHECK_BALLPARK(cos(M_PI_2), 0., 0.0001, "cos double, pi/2");
	CASE_CHECK_BALLPARK(cos(2. * (M_PI / 3.)), -0.5, 0.0001, "cos double, 2pi/3");
	CASE_CHECK_BALLPARK(cos(3. * (M_PI / 4.)), -0.707106781187, 0.0001, "cos double, 3pi/4");
	CASE_CHECK_BALLPARK(cos(5. * (M_PI / 6.)), -0.866025403784, 0.0001, "cos double, 5pi/6");
	CASE_CHECK_BALLPARK(cos(M_PI), -1., 0.0001, "cos double, pi");

	CASE_CHECK_BALLPARK(cosl(0), 1.l, 0.0001l, "cos long double, 0");
	CASE_CHECK_BALLPARK(cosl(M_PI / 6.l), 0.866025403784l, 0.0001l, "cos long double, pi/6");
	CASE_CHECK_BALLPARK(cosl(M_PI / 4.l), 0.707106781187l, 0.0001l, "cos long double, pi/4");
	CASE_CHECK_BALLPARK(cosl(M_PI / 3.l), 0.5l, 0.0001l, "cos long double, pi/3");
	CASE_CHECK_BALLPARK(cosl(M_PI_2), 0.l, 0.0001l, "cos long double, pi/2");
	CASE_CHECK_BALLPARK(cosl(2.l * (M_PI / 3.l)), -0.5l, 0.0001l, "cos long double, 2pi/3");
	CASE_CHECK_BALLPARK(cosl(3.l * (M_PI / 4.l)), -0.707106781187l, 0.0001l, "cos long double, 3pi/4");
	CASE_CHECK_BALLPARK(cosl(5.l * (M_PI / 6.l)), -0.866025403784l, 0.0001l, "cos long double, 5pi/6");
	CASE_CHECK_BALLPARK(cosl(M_PI), -1.l, 0.0001l, "cos long double, pi");
}
void test_trigonometry_tan()
{
	CASE_CHECK_BALLPARK(tanf(0), 0.f, 0.0001f, "tan float, 0");
	CASE_CHECK_BALLPARK(tanf(M_PI / 6.f), 0.57735026919f, 0.0001f, "tan float, pi/6");
	CASE_CHECK_BALLPARK(tanf(M_PI / 4.f), 1.f, 0.0001f, "tan float, pi/4");
	CASE_CHECK_BALLPARK(tanf(M_PI / 3.f), 1.73205080757f, 0.0001f, "tan float, pi/3");
	CASE_CHECK_BALLPARK(tanf(2.f * (M_PI / 3.f)), -1.73205080757f, 0.0001f, "tan float, 2pi/3");
	CASE_CHECK_BALLPARK(tanf(3.f * (M_PI / 4.f)), -1.f, 0.0001f, "tan float, 3pi/4");
	CASE_CHECK_BALLPARK(tanf(5.f * (M_PI / 6.f)), -0.57735026919f, 0.0001f, "tan float, 5pi/6");
	CASE_CHECK_BALLPARK(tanf(M_PI), -0.f, 0.0001f, "tan float, pi");

	CASE_CHECK_BALLPARK(tan(0), 0., 0.0001, "tan double, 0");
	CASE_CHECK_BALLPARK(tan(M_PI / 6.), 0.57735026919, 0.0001, "tan double, pi/6");
	CASE_CHECK_BALLPARK(tan(M_PI / 4.), 1., 0.0001, "tan double, pi/4");
	CASE_CHECK_BALLPARK(tan(M_PI / 3.), 1.73205080757, 0.0001, "tan double, pi/3");
	CASE_CHECK_BALLPARK(tan(2. * (M_PI / 3.)), -1.73205080757, 0.0001, "tan double, 2pi/3");
	CASE_CHECK_BALLPARK(tan(3. * (M_PI / 4.)), -1., 0.0001, "tan double, 3pi/4");
	CASE_CHECK_BALLPARK(tan(5. * (M_PI / 6.)), -0.57735026919, 0.0001, "tan double, 5pi/6");
	CASE_CHECK_BALLPARK(tan(M_PI), -0., 0.0001, "tan double, pi");

	CASE_CHECK_BALLPARK(tanl(0), 0.l, 0.0001l, "tan long double, 0");
	CASE_CHECK_BALLPARK(tanl(M_PI / 6.l), 0.57735026919l, 0.0001l, "tan long double, pi/6");
	CASE_CHECK_BALLPARK(tanl(M_PI / 4.l), 1.l, 0.0001l, "tan long double, pi/4");
	CASE_CHECK_BALLPARK(tanl(M_PI / 3.l), 1.73205080757l, 0.0001l, "tan long double, pi/3");
	CASE_CHECK_BALLPARK(tanl(2.l * (M_PI / 3.l)), -1.73205080757l, 0.0001l, "tan long double, 2pi/3");
	CASE_CHECK_BALLPARK(tanl(3.l * (M_PI / 4.l)), -1.l, 0.0001l, "tan long double, 3pi/4");
	CASE_CHECK_BALLPARK(tanl(5.l * (M_PI / 6.l)), -0.57735026919l, 0.0001l, "tan long double, 5pi/6");
	CASE_CHECK_BALLPARK(tanl(M_PI), -0.l, 0.0001l, "tan long double, pi");
}

void test_trigonometry_arc_sine()
{
	CASE_CHECK_BALLPARK(asinf(sinf(-1.f)), -1.f, 0.0001f, "arch sin float, -1");
	CASE_CHECK_BALLPARK(asinf(sinf(-0.866025403784f)), -0.866025403784f, 0.0001f, "arch sin float, -sqrt(3)/2");
	CASE_CHECK_BALLPARK(asinf(sinf(-M_SQRT1_2)), -M_SQRT1_2, 0.0001f, "arch sin float, -sqrt(2)/2");
	CASE_CHECK_BALLPARK(asinf(sinf(-0.5f)), -0.5f, 0.0001f, "arch sin float, -0.5");
	CASE_CHECK_BALLPARK(asinf(sinf(0)), 0.f, 0.0001f, "arch sin float, 0");
	CASE_CHECK_BALLPARK(asinf(sinf(0.5f)), 0.5f, 0.0001f, "arch sin float, 0.5");
	CASE_CHECK_BALLPARK(asinf(sinf(M_SQRT1_2)), M_SQRT1_2, 0.0001f, "arch sin float, sqrt(2)/2");
	CASE_CHECK_BALLPARK(asinf(sinf(0.866025403784f)), 0.866025403784f, 0.0001f, "arch sin float, sqrt(3)/2");
	CASE_CHECK_BALLPARK(asinf(sinf(1.f)), 1.f, 0.0001f, "arch sin float, 2pi/3");

	CASE_CHECK_BALLPARK(asin(sin(-1.)), -1., 0.0001, "arch sin double, -1");
	CASE_CHECK_BALLPARK(asin(sin(-0.866025403784)), -0.866025403784, 0.0001, "arch sin double, -sqrt(3)/2");
	CASE_CHECK_BALLPARK(asin(sin(-M_SQRT1_2)), -M_SQRT1_2, 0.0001, "arch sin double, -sqrt(2)/2");
	CASE_CHECK_BALLPARK(asin(sin(-0.5)), -0.5, 0.0001, "arch sin double, -0.5");
	CASE_CHECK_BALLPARK(asin(sin(0)), 0., 0.0001, "arch sin double, 0");
	CASE_CHECK_BALLPARK(asin(sin(0.5)), 0.5, 0.0001, "arch sin double, 0.5");
	CASE_CHECK_BALLPARK(asin(sin(M_SQRT1_2)), M_SQRT1_2, 0.0001, "arch sin double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(asin(sin(0.866025403784)), 0.866025403784, 0.0001, "arch sin double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(asin(sin(1.)), 1., 0.0001, "arch sin double, 1");

	CASE_CHECK_BALLPARK(asinl(sinl(-1.l)), -1.l, 0.0001l, "arch sin long double, -1");
	CASE_CHECK_BALLPARK(asinl(sinl(-0.866025403784l)), -0.866025403784l, 0.0001l, "arch sin long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(asinl(sinl(-M_SQRT1_2)), -M_SQRT1_2, 0.0001l, "arch sin long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(asinl(sinl(-0.5l)), -0.5l, 0.0001l, "arch sin long double, -0.5");
	CASE_CHECK_BALLPARK(asinl(sinl(0)), 0.l, 0.0001l, "arch sin long double, 0");
	CASE_CHECK_BALLPARK(asinl(sinl(0.5l)), 0.5l, 0.0001l, "arch sin long double, 0.5");
	CASE_CHECK_BALLPARK(asinl(sinl(M_SQRT1_2)), M_SQRT1_2, 0.0001l, "arch sin long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(asinl(sinl(0.866025403784l)), 0.866025403784l, 0.0001l, "arch sin long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(asinl(sinl(1.l)), 1.l, 0.0001l, "arch sin long double, 1");
}
void test_trigonometry_arc_cos()
{
	CASE_CHECK_BALLPARK(acosf(cosf(-1.f)), 1.f, 0.0001f, "arch cos float, -1");
	CASE_CHECK_BALLPARK(acosf(cosf(-0.866025403784f)), 0.866025403784f, 0.0001f, "arch cos float, -sqrt(3)/2");
	CASE_CHECK_BALLPARK(acosf(cosf(-M_SQRT1_2)), M_SQRT1_2, 0.0001f, "arch cos float, -sqrt(2)/2");
	CASE_CHECK_BALLPARK(acosf(cosf(-0.5f)), 0.5f, 0.0001f, "arch cos float, -0.5");
	CASE_CHECK_BALLPARK(acosf(cosf(0)), 0.f, 0.0001f, "arch cos float, 0");
	CASE_CHECK_BALLPARK(acosf(cosf(0.5f)), 0.5f, 0.0001f, "arch cos float, 0.5");
	CASE_CHECK_BALLPARK(acosf(cosf(M_SQRT1_2)), M_SQRT1_2, 0.0001f, "arch cos float, sqrt(2)/2");
	CASE_CHECK_BALLPARK(acosf(cosf(0.866025403784f)), 0.866025403784f, 0.0001f, "arch cos float, sqrt(3)/2");
	CASE_CHECK_BALLPARK(acosf(cosf(1.f)), 1.f, 0.0001f, "arch cos float, 2pi/3");

	CASE_CHECK_BALLPARK(acos(cos(-1.)), 1., 0.0001, "arch cos double, -1");
	CASE_CHECK_BALLPARK(acos(cos(-0.866025403784)), 0.866025403784, 0.0001, "arch cos double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(acos(cos(-M_SQRT1_2)), M_SQRT1_2, 0.0001, "arch cos double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(acos(cos(-0.5)), 0.5, 0.0001, "arch cos double, -0.5");
	CASE_CHECK_BALLPARK(acos(cos(0)), 0., 0.0001, "arch cos double, 0");
	CASE_CHECK_BALLPARK(acos(cos(0.5)), 0.5, 0.0001, "arch cos double, 0.5");
	CASE_CHECK_BALLPARK(acos(cos(M_SQRT1_2)), M_SQRT1_2, 0.0001, "arch cos double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(acos(cos(0.866025403784)), 0.866025403784, 0.0001, "arch cos double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(acos(cos(1.)), 1., 0.0001, "arch cos double, 1");

	CASE_CHECK_BALLPARK(acosl(cosl(-1.l)), 1.l, 0.0001l, "arch cos long double, -1");
	CASE_CHECK_BALLPARK(acosl(cosl(-0.866025403784l)), 0.866025403784l, 0.0001l, "arch cos long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(acosl(cosl(-M_SQRT1_2)), M_SQRT1_2, 0.0001l, "arch cos long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(acosl(cosl(-0.5l)), 0.5l, 0.0001l, "arch cos long double, -0.5");
	CASE_CHECK_BALLPARK(acosl(cosl(0)), 0.l, 0.0001l, "arch cos long double, 0");
	CASE_CHECK_BALLPARK(acosl(cosl(0.5l)), 0.5l, 0.0001l, "arch cos long double, 0.5");
	CASE_CHECK_BALLPARK(acosl(cosl(M_SQRT1_2)), M_SQRT1_2, 0.0001l, "arch cos long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(acosl(cosl(0.866025403784l)), 0.866025403784l, 0.0001l, "arch cos long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(acosl(cosl(1.l)), 1.l, 0.0001l, "arch cos long double, 1");
}
void test_trigonometry_arc_tan()
{
	CASE_CHECK_BALLPARK(atanf(tanf(-1.f)), -1.f, 0.0001f, "arch tan float, -1");
	CASE_CHECK_BALLPARK(atanf(tanf(-0.866025403784f)), -0.866025403784f, 0.0001f, "arch tan float, -sqrt(3)/2");
	CASE_CHECK_BALLPARK(atanf(tanf(-M_SQRT1_2)), -M_SQRT1_2, 0.0001f, "arch tan float, -sqrt(2)/2");
	CASE_CHECK_BALLPARK(atanf(tanf(-0.5f)), -0.5f, 0.0001f, "arch tan float, -0.5");
	CASE_CHECK_BALLPARK(atanf(tanf(0)), 0.f, 0.0001f, "arch tan float, 0");
	CASE_CHECK_BALLPARK(atanf(tanf(0.5f)), 0.5f, 0.0001f, "arch tan float, 0.5");
	CASE_CHECK_BALLPARK(atanf(tanf(M_SQRT1_2)), M_SQRT1_2, 0.0001f, "arch tan float, sqrt(2)/2");
	CASE_CHECK_BALLPARK(atanf(tanf(0.866025403784f)), 0.866025403784f, 0.0001f, "arch tan float, sqrt(3)/2");
	CASE_CHECK_BALLPARK(atanf(tanf(1.f)), 1.f, 0.0001f, "arch tan float, 2pi/3");

	CASE_CHECK_BALLPARK(atan(tan(-1.)), -1., 0.0001, "arch tan double, -1");
	CASE_CHECK_BALLPARK(atan(tan(-0.866025403784)), -0.866025403784, 0.0001, "arch tan double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(atan(tan(-M_SQRT1_2)), -M_SQRT1_2, 0.0001, "arch tan double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(atan(tan(-0.5)), -0.5, 0.0001, "arch tan double, -0.5");
	CASE_CHECK_BALLPARK(atan(tan(0)), 0., 0.0001, "arch tan double, 0");
	CASE_CHECK_BALLPARK(atan(tan(0.5)), 0.5, 0.0001, "arch tan double, 0.5");
	CASE_CHECK_BALLPARK(atan(tan(M_SQRT1_2)), M_SQRT1_2, 0.0001, "arch tan double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(atan(tan(0.866025403784)), 0.866025403784, 0.0001, "arch tan double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(atan(tan(1.)), 1., 0.0001, "arch tan double, 1");

	CASE_CHECK_BALLPARK(atanl(tanl(-1.l)), -1.l, 0.0001l, "arch tan long double, -1");
	CASE_CHECK_BALLPARK(atanl(tanl(-0.866025403784l)), -0.866025403784l, 0.0001l, "arch tan long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(atanl(tanl(-M_SQRT1_2)), -M_SQRT1_2, 0.0001l, "arch tan long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(atanl(tanl(-0.5l)), -0.5l, 0.0001l, "arch tan long double, -0.5");
	CASE_CHECK_BALLPARK(atanl(tanl(0)), 0.l, 0.0001l, "arch tan long double, 0");
	CASE_CHECK_BALLPARK(atanl(tanl(0.5l)), 0.5l, 0.0001l, "arch tan long double, 0.5");
	CASE_CHECK_BALLPARK(atanl(tanl(M_SQRT1_2)), M_SQRT1_2, 0.0001l, "arch tan long double, sqrt(2)/2");
	CASE_CHECK_BALLPARK(atanl(tanl(0.866025403784l)), 0.866025403784l, 0.0001l, "arch tan long double, sqrt(3)/2");
	CASE_CHECK_BALLPARK(atanl(tanl(1.l)), 1.l, 0.0001l, "arch tan long double, 1");
}

void test_base_exponents()
{
	CASE_CHECK_BALLPARK(expf(1), 2.718282f, 0.0001f, "exp float, 1");
	CASE_CHECK_BALLPARK(100.f * expf(0.03f), 103.045453f, 0.0001f, "exp float, 0.03");
	CASE_CHECK_BALLPARK(expf(0.f), 1.f, 0.0001f, "exp float, 0");
	CASE_CHECK_BALLPARK(expf(-0.f), 1.f, 0.0001f, "exp float, -0");
	CASE_CHECK_BALLPARK(expf(-HUGE_VALF), 0.f, 0.0001f, "exp float, -inf");
	CASE_CHECK_EQ(expf(HUGE_VALF), HUGE_VALF, "exp float, inf");
	CASE_CHECK_NE(isnan(expf(NAN)), 0, "exp float, nan");
	CASE_CHECK_EQ(expf(800.f), HUGE_VALF, "exp float, 800.f");

	CASE_CHECK_BALLPARK(exp(1), 2.718282, 0.0001, "exp doube, 1");
	CASE_CHECK_BALLPARK(100. * exp(0.03), 103.045453, 0.0001, "exp double, 0.03");
	CASE_CHECK_BALLPARK(exp(0.), 1., 0.0001, "exp double, 0");
	CASE_CHECK_BALLPARK(exp(-0.), 1., 0.0001, "exp double, -0");
	CASE_CHECK_BALLPARK(exp(-HUGE_VAL), 0., 0.0001, "exp double, -inf");
	CASE_CHECK_EQ(exp(HUGE_VAL), HUGE_VAL, "exp double, inf");
	CASE_CHECK_NE(isnan(exp(NAN)), 0, "exp double, nan");
	CASE_CHECK_EQ(exp(800.), HUGE_VAL, "exp double, 800.f");

	CASE_CHECK_BALLPARK(expl(1), 2.718282l, 0.0001l, "exp long doube, 1");
	CASE_CHECK_BALLPARK(100.l * expl(0.03l), 103.045453l, 0.0001l, "exp double, 0.03");
	CASE_CHECK_BALLPARK(expl(0.l), 1.l, 0.0001l, "exp long double, 0");
	CASE_CHECK_BALLPARK(expl(-0.l), 1.l, 0.0001l, "exp long double, -0");
	CASE_CHECK_BALLPARK(expl(-HUGE_VALL), 0.l, 0.0001l, "exp long double, -inf");
	CASE_CHECK_EQ(expl(HUGE_VALL), HUGE_VALL, "exp double, inf");
	CASE_CHECK_NE(isnan(expl(NAN)), 0, "exp double, nan");
	CASE_CHECK_EQ(expl(800.), HUGE_VALL, "exp long double, 800.f");


	CASE_CHECK_BALLPARK(exp2f(1), 2.f, 0.0001f, "exp2 float, 1");
	CASE_CHECK_BALLPARK(exp2f(0.03f), 1.02101212571f, 0.0001f, "exp2 float, 0.03");
	CASE_CHECK_BALLPARK(exp2f(0.f), 1.f, 0.0001f, "exp2 float, 0");
	CASE_CHECK_BALLPARK(exp2f(-0.f), 1.f, 0.0001f, "exp2 float, -0");
	CASE_CHECK_BALLPARK(exp2f(-HUGE_VALF), 0.f, 0.0001f, "exp2 float, -inf");
	CASE_CHECK_EQ(exp2f(HUGE_VALF), HUGE_VALF, "exp2 float, inf");
	CASE_CHECK_NE(isnan(exp2f(NAN)), 0, "exp2 float, nan");
	CASE_CHECK_EQ(exp2f(7100.f), HUGE_VALF, "exp2 float, 7100");

	CASE_CHECK_BALLPARK(exp2(1), 2., 0.0001, "exp2 doube, 1");
	CASE_CHECK_BALLPARK(exp2(0.03), 1.02101212571, 0.0001, "exp2 double, 0.03");
	CASE_CHECK_BALLPARK(exp2(0.), 1., 0.0001, "exp2 double, 0");
	CASE_CHECK_BALLPARK(exp2(-0.), 1., 0.0001, "exp2 double, -0");
	CASE_CHECK_BALLPARK(exp2(-HUGE_VAL), 0., 0.0001, "exp2 double, -inf");
	CASE_CHECK_EQ(exp2(HUGE_VAL), HUGE_VAL, "exp2 double, inf");
	CASE_CHECK_NE(isnan(exp2(NAN)), 0, "exp2 double, nan");
	CASE_CHECK_EQ(exp2(7100.), HUGE_VAL, "exp2 double, 7100");

	CASE_CHECK_BALLPARK(exp2l(1), 2.l, 0.0001l, "exp2 long doube, 1");
	CASE_CHECK_BALLPARK(exp2l(0.03l), 1.02101212571, 0.0001l, "exp2 double, 0.03");
	CASE_CHECK_BALLPARK(exp2l(0.l), 1.l, 0.0001l, "exp2 long double, 0");
	CASE_CHECK_BALLPARK(exp2l(-0.l), 1.l, 0.0001l, "exp2 long double, -0");
	CASE_CHECK_BALLPARK(exp2l(-HUGE_VALL), 0.l, 0.0001l, "exp2 long double, -inf");
	CASE_CHECK_EQ(exp2l(HUGE_VALL), HUGE_VALL, "exp2 double, inf");
	CASE_CHECK_NE(isnan(exp2l(NAN)), 0, "exp2 double, nan");
	CASE_CHECK_EQ(exp2l(7100.), HUGE_VALL, "exp2 long double, 7100");

	CASE_CHECK_BALLPARK(expm1f(1), 1.718282f, 0.0001f, "expm1 float, 1");
	CASE_CHECK_BALLPARK(100.f * expm1f(0.03f), 3.0454533953516938f, 0.0001f, "expm1 float, 0.03");
	CASE_CHECK_BALLPARK(expm1f(0.f), 0.f, 0.0001f, "expm1 float, 0");
	CASE_CHECK_BALLPARK(expm1f(-0.f), 0.f, 0.0001f, "expm1 float, -0");
	CASE_CHECK_BALLPARK(expm1f(-HUGE_VALF), -1.f, 0.0001f, "expm1 float, -inf");
	CASE_CHECK_EQ(expm1f(HUGE_VALF), HUGE_VALF, "expm1 float, inf");
	CASE_CHECK_NE(isnan(expm1f(NAN)), 0, "expm1 float, nan");
	CASE_CHECK_EQ(expm1f(800.f), HUGE_VALF, "expm1 float, 800.f");

	CASE_CHECK_BALLPARK(expm1(1), 1.718282, 0.0001, "expm1 doube, 1");
	CASE_CHECK_BALLPARK(100. * expm1(0.03), 3.0454533953516938, 0.0001, "expm1 double, 0.03");
	CASE_CHECK_BALLPARK(expm1(0.), 0., 0.0001, "expm1 double, 0");
	CASE_CHECK_BALLPARK(expm1(-0.), 0., 0.0001, "expm1 double, -0");
	CASE_CHECK_BALLPARK(expm1(-HUGE_VAL), -1., 0.0001, "expm1 double, -inf");
	CASE_CHECK_EQ(expm1(HUGE_VAL), HUGE_VAL, "expm1 double, inf");
	CASE_CHECK_NE(isnan(expm1(NAN)), 0, "expm1 double, nan");
	CASE_CHECK_EQ(expm1(800.), HUGE_VAL, "expm1 double, 800.f");
	
	CASE_CHECK_BALLPARK(expm1l(1), 1.718282l, 0.0001l, "expm1 long doube, 1");
	CASE_CHECK_BALLPARK(100.l * expm1l(0.03l), 3.0454533953516938l, 0.0001l, "expm1 double, 0.03");
	CASE_CHECK_BALLPARK(expm1l(0.l), 0.l, 0.0001l, "expm1 long double, 0");
	CASE_CHECK_BALLPARK(expm1l(-0.l), 0.l, 0.0001l, "expm1 long double, -0");
	CASE_CHECK_BALLPARK(expm1l(-HUGE_VALL), -1.l, 0.0001l, "expm1 long double, -inf");
	CASE_CHECK_EQ(expm1l(HUGE_VALL), HUGE_VALL, "expm1 double, inf");
	CASE_CHECK_NE(isnan(expm1l(NAN)), 0, "expm1 double, nan");
	CASE_CHECK_EQ(expm1l(800.), HUGE_VALL, "expm1 long double, 800.f");
	
}

void test_pow()
{
	CASE_CHECK_BALLPARK(powf(2.f, 4.f), 16.f, 0.0001f, "pow float 2^4=16");
	CASE_CHECK_BALLPARK(powf(444.f, 2.6f), 7641796.5267531928f, 1.f, "pow float 444^2.6=7641796.5267531928");
	CASE_CHECK_BALLPARK(powf(8.f, 0.f), 1.f, 0.0001f, "pow float 8^0=1");
	CASE_CHECK_BALLPARK(powf(4.f, -1.f), 0.25f, 0.0001f, "pow float 4^-1=0.25");
	CASE_CHECK_EQ(powf(256.f, 512.f), HUGE_VALF, "pow float 256^512=inf");

	CASE_CHECK_BALLPARK(pow(2., 4.), 16., 0.0001, "pow double 2^4=16");
	CASE_CHECK_BALLPARK(pow(444., 2.6f), 7641796.5267531928, 1., "pow double 444^2.6=7641796.5267531928");
	CASE_CHECK_BALLPARK(pow(8., 0.), 1., 0.0001, "pow double 8^0=1");
	CASE_CHECK_BALLPARK(pow(4., -1.), 0.25, 0.0001, "pow double 4^-1=0.25");
	CASE_CHECK_EQ(pow(256., 512.), HUGE_VAL, "pow double 256^512=inf");

	CASE_CHECK_BALLPARK(powl(2.l, 4.l), 16.l, 0.0001l, "pow long double 2^4=16");
	CASE_CHECK_BALLPARK(powl(444.l, 2.6f), 7641796.5267531928l, 1.l , "pow long double 444^2.6=7641796.5267531928");
	CASE_CHECK_BALLPARK(powl(8.l, 0.l), 1.l, 0.0001l, "pow long double 8^0=1");
	CASE_CHECK_BALLPARK(powl(4.l, -1.l), 0.25l, 0.0001l, "pow long double 4^-1=0.25");
	CASE_CHECK_EQ(powl(256.l, 512.l), HUGE_VALL, "pow long double 256^512=inf");
}

void test_exponent_deconstruction()
{
	//ldexp
	int fexponent = 0;
	float ft = frexpf(3.f, &fexponent);
	CASE_CHECK_BALLPARK(ft, 1.5f, 0.0001f, "frexp float, 1.5");
	CASE_CHECK_EQ(fexponent, 1, "frexp float exponent 1");
	CASE_CHECK_EQ(ldexpf(ft, fexponent), 3.f, "ldexp float exponent");
	fexponent = 0;
	ft = frexpf(0.03f, &fexponent);
	CASE_CHECK_BALLPARK(ft, 1.9199996, 0.0001f, "frexp float, 0.03");
	CASE_CHECK_EQ(fexponent, -6, "frexp float exponent 0.03");
	CASE_CHECK_BALLPARK(ldexpf(ft, fexponent), 0.03, 0.0001f, "ldexp float exponent");
	fexponent = 0;
	ft = frexpf(4.f, &fexponent);
	CASE_CHECK_BALLPARK(ft, 1., 0.0001f, "frexp float, 4");
	CASE_CHECK_EQ(fexponent, 2, "frexp float exponent 4");
	CASE_CHECK_EQ(ldexpf(ft, fexponent), 4.f, "ldexp float exponent");
	fexponent = 0;
	ft = frexpf(0.f, &fexponent);
	CASE_CHECK_BALLPARK(ft, 0.f, 0.0001f, "frexp float, 0");
	CASE_CHECK_EQ(fexponent, 0, "frexp float exponent 0");
	CASE_CHECK_EQ(ldexpf(ft, fexponent), 0.f, "ldexp float exponent");
	fexponent = 0;
	ft = frexpf(800.f, &fexponent);
	CASE_CHECK_EQ(ft, 1.5625, "frexp float, 800");
	CASE_CHECK_EQ(fexponent, 9, "frexp float exponent 800");
	CASE_CHECK_EQ(ldexpf(ft, fexponent), 800.f, "ldexp float exponent");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexpf(-0.f, &fexponent), 0.f, 0.0001f, "frexp float, -0");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexpf(-HUGE_VALF, &fexponent), -1.f, 0.0001f, "frexp float, -inf");
	fexponent = 0;
	CASE_CHECK_EQ(frexpf(HUGE_VALF, &fexponent), HUGE_VALF, "frexp float, inf");
	fexponent = 0;
	CASE_CHECK_NE(isnan(frexpf(NAN, &fexponent)), 0, "frexp float, nan");

	fexponent = 0;
	double dbl = frexp(3., &fexponent);
	CASE_CHECK_BALLPARK(dbl, 1.5, 0.0001, "frexp double, 1.5");
	CASE_CHECK_EQ(fexponent, 1, "frexp double exponent 1");
	CASE_CHECK_EQ(ldexp(dbl, fexponent), 3., "ldexp double exponent");
	fexponent = 0;
	dbl = frexp(0.03, &fexponent);
	CASE_CHECK_BALLPARK(dbl, 1.9199996, 0.0001, "frexp double, 0.03");
	CASE_CHECK_EQ(fexponent, -6, "frexp double exponent 0.03");
	CASE_CHECK_EQ(ldexp(dbl, fexponent), 0.03, "ldexp double exponent");
	fexponent = 0;
	dbl = frexp(4., &fexponent);
	CASE_CHECK_BALLPARK(dbl, 1., 0.0001, "frexp double, 4");
	CASE_CHECK_EQ(fexponent, 2, "frexp double exponent 4");
	CASE_CHECK_EQ(ldexp(dbl, fexponent), 4., "ldexp double exponent");
	fexponent = 0;
	dbl = frexp(0., &fexponent);
	CASE_CHECK_BALLPARK(dbl, 0., 0.0001, "frexp double, 0");
	CASE_CHECK_EQ(fexponent, 0, "frexp double exponent 0");
	CASE_CHECK_EQ(ldexp(dbl, fexponent), 0., "ldexp double exponent");
	fexponent = 0;
	dbl = frexp(800., &fexponent);
	CASE_CHECK_EQ(dbl, 1.5625, "frexp double, 800");
	CASE_CHECK_EQ(fexponent, 9, "frexp double exponent 800");
	CASE_CHECK_EQ(ldexp(dbl, fexponent), 800., "ldexp double exponent");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexp(-0., &fexponent), 0., 0.0001, "frexp double, -0");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexp(-HUGE_VAL, &fexponent), -1., 0.0001, "frexp double, -inf");
	fexponent = 0;
	CASE_CHECK_EQ(frexp(HUGE_VAL, &fexponent), HUGE_VAL, "frexp double, inf");
	fexponent = 0;
	CASE_CHECK_NE(isnan(frexp(NAN, &fexponent)), 0, "frexp double, nan");

	fexponent = 0;
	long double ldbl = frexpl(3.l, &fexponent);
	CASE_CHECK_BALLPARK(ldbl, 1.5l, 0.0001l, "frexpl long double, 1.5");
	CASE_CHECK_EQ(fexponent, 1, "frexpl long double exponent 1");
	CASE_CHECK_EQ(ldexpl(ldbl, fexponent), 3.l, "ldexp long double exponent");
	fexponent = 0;
	ldbl = frexpl(0.03, &fexponent);
	CASE_CHECK_BALLPARK(ldbl, 1.9199996l, 0.0001l, "frexpl long double, 0.03");
	CASE_CHECK_EQ(fexponent, -6, "frexpl long double exponent 0.03");
	CASE_CHECK_EQ(ldexpl(ldbl, fexponent), 0.03l, "ldexp long double exponent");
	fexponent = 0;
	ldbl = frexpl(4., &fexponent);
	CASE_CHECK_BALLPARK(ldbl, 1.l, 0.0001l, "frexpl long double, 4");
	CASE_CHECK_EQ(fexponent, 2, "frexpl long double exponent 4");
	CASE_CHECK_EQ(ldexpl(ldbl, fexponent), 4.l, "ldexp long double exponent");
	fexponent = 0;
	ldbl = frexpl(0., &fexponent);
	CASE_CHECK_BALLPARK(ldbl, 0.l, 0.0001l, "frexpl long double, 0");
	CASE_CHECK_EQ(fexponent, 0, "frexpl long double exponent 0");
	CASE_CHECK_EQ(ldexpl(ldbl, fexponent), 0., "ldexp long double exponent");
	fexponent = 0;
	ldbl = frexpl(800., &fexponent);
	CASE_CHECK_EQ(ldbl, 1.5625l, "frexpl long double, 800");
	CASE_CHECK_EQ(fexponent, 9, "frexpl long double exponent 800");
	CASE_CHECK_EQ(ldexpl(ldbl, fexponent), 800., "ldexp long double exponent");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexpl(-0., &fexponent), 0.l, 0.0001l, "frexpl long double, -0");
	fexponent = 0;
	CASE_CHECK_BALLPARK(frexpl(-HUGE_VALL, &fexponent), -1.l, 0.0001l, "frexpl long double, -inf");
	fexponent = 0;
	CASE_CHECK_EQ(frexpl(HUGE_VALL, &fexponent), HUGE_VALL, "frexpl long double, inf");
	fexponent = 0;
	CASE_CHECK_NE(isnan(frexpl(NAN, &fexponent)), 0, "frexpl long double, nan");

}

void test_root()
{
	CASE_CHECK_NE(isnan(sqrtf(-1.f)), 0, "sqrt float, -1");
	CASE_CHECK_EQ(sqrtf(0.f), 0.f, "sqrt float, 0");
	CASE_CHECK_BALLPARK(sqrtf(483331.25f), 695.220288829f, 0.0001f, "sqrt float, sqrt(483331.25) = 695.220288829");

	CASE_CHECK_NE(isnan(sqrt(-1.)), 0, "sqrt double, -1");
	CASE_CHECK_EQ(sqrt(0.), 0., "sqrt double, 0");
	CASE_CHECK_BALLPARK(sqrt(483331.25), 695.220288829, 0.0001f, "sqrt double, sqrt(483331.25) = 695.220288829");

	CASE_CHECK_NE(isnan(sqrtl(-1.l)), 0, "sqrt long double, -1");
	CASE_CHECK_EQ(sqrtl(0.l), 0.l, "sqrt long double, 0");
	CASE_CHECK_BALLPARK(sqrtl(483331.25l), 695.220288829l, 0.0001f, "sqrt long double, sqrt(483331.25) = 695.220288829");

	CASE_CHECK_NE(isnan(cbrtf(-1.f)), 0, "cbrt float, -1");
	CASE_CHECK_NE(cbrtf(1.f), 0, "cbrt float, 1");
	CASE_CHECK_EQ(cbrtf(0.f), 0.f, "cbrt float, 0");
	CASE_CHECK_BALLPARK(cbrtf(483331.25f), 78.4780660047f, 0.0001f, "cbrt float, cbrtf(483331.25) = 78.4780660047");

	CASE_CHECK_NE(isnan(cbrt(-1.)), 0, "cbrt double, -1");
	CASE_CHECK_NE(cbrt(1.), 0, "cbrt double, 1");
	CASE_CHECK_EQ(cbrt(0.), 0., "cbrt double, 0");
	CASE_CHECK_BALLPARK(cbrt(483331.25), 78.4780660047, 0.0001f, "cbrt double, cbrtf(483331.25) = 78.4780660047");

	CASE_CHECK_NE(isnan(cbrtl(-1.l)), 0, "cbrt long double, -1");
	CASE_CHECK_NE(cbrtl (1.), 0, "cbrt long double, 1");
	CASE_CHECK_EQ(cbrtl(0.l), 0.l, "cbrt long double, 0");
	CASE_CHECK_BALLPARK(cbrtl(483331.25l), 78.4780660047l, 0.0001f, "cbrt long double, cbrtf(483331.25) = 78.4780660047");
}

template<typename _Ty>
static bool BinaryComp(_Ty a, _Ty b)
{
	return memcmp(&a, &b, sizeof(_Ty)) == 0;
}

void test_fabs()
{
	CASE_CHECK_EQ(fabsf(8.f), 8.f, "abs float, 8");
	CASE_CHECK_EQ(fabsf(-8.f), 8.f, "abs float, -8");
	CASE_CHECK_EQ(fabsf(HUGE_VALF), HUGE_VALF, "abs float, inf");
	CASE_CHECK_EQ(fabsf(-HUGE_VALF), HUGE_VALF, "abs float, -inf");
	CASE_CHECK_EQ(BinaryComp<float>(fabsf(NAN), -NAN), true, "abs float, NAN");
	CASE_CHECK_EQ(BinaryComp<float>(fabsf(-NAN), -NAN), true, "abs float, -NAN");

	CASE_CHECK_EQ(fabs(8.f), 8.f, "abs double, 8");
	CASE_CHECK_EQ(fabs(-8.f), 8.f, "abs double, -8");
	CASE_CHECK_EQ(fabs(HUGE_VAL), HUGE_VAL, "abs double, inf");
	CASE_CHECK_EQ(fabs(-HUGE_VAL), HUGE_VAL, "abs double, -inf");
	CASE_CHECK_EQ(BinaryComp<double>(fabs(NAN), -NAN), true, "abs double, NAN");
	CASE_CHECK_EQ(BinaryComp<double>(fabs(-NAN), -NAN), true, "abs double, -NAN");

	CASE_CHECK_EQ(fabsl(8.f), 8.f, "abs long double, 8");
	CASE_CHECK_EQ(fabsl(-8.f), 8.f, "abs long double, -8");
	CASE_CHECK_EQ(fabsl(HUGE_VALL), HUGE_VALL, "abs long double, inf");
	CASE_CHECK_EQ(fabsl(-HUGE_VALL), HUGE_VALL, "abs long double, -inf");
	CASE_CHECK_EQ(BinaryComp<long double>(fabsl(NAN), -NAN), true, "abs long double, NAN");
	CASE_CHECK_EQ(BinaryComp<long double>(fabsl(-NAN), -NAN), true, "abs long double, -NAN");

}

void test_log()
{
	CASE_CHECK_EQ(ilogbf(0), FP_ILOGB0, "ilog float, 0");
	CASE_CHECK_EQ(ilogbf(HUGE_VALF), INT_MAX, "ilog float, INT_MAX");
	CASE_CHECK_EQ(ilogbf(NAN), FP_ILOGBNAN, "ilog float, nan");
	CASE_CHECK_EQ(ilogbf(8.f), 3, "ilog float, 8");
	CASE_CHECK_EQ(ilogbf(0.25f), -2, "ilog float, 0.25");

	CASE_CHECK_EQ(ilogb(0), FP_ILOGB0, "ilog double, 0");
	CASE_CHECK_EQ(ilogb(HUGE_VAL), INT_MAX, "ilog double, INT_MAX");
	CASE_CHECK_EQ(ilogb(NAN), FP_ILOGBNAN, "ilog double, nan");
	CASE_CHECK_EQ(ilogb(8.), 3, "ilog double, 8");
	CASE_CHECK_EQ(ilogb(0.25), -2, "ilog double, 0.25");

	CASE_CHECK_EQ(ilogbl(0), FP_ILOGB0, "ilog long double, 0");
	CASE_CHECK_EQ(ilogbl(HUGE_VALL), INT_MAX, "ilog long double, INT_MAX");
	CASE_CHECK_EQ(ilogbl(NAN), FP_ILOGBNAN, "ilog long double, nan");
	CASE_CHECK_EQ(ilogbl(8.f), 3, "ilog long double, 8");
	CASE_CHECK_EQ(ilogbl(0.25f), -2, "ilog long double, 0.25");

	CASE_CHECK_EQ(logf(1.f), 0.f, "log float, 1");
	CASE_CHECK_EQ(logf(HUGE_VALF), HUGE_VALF, "log float, inf");
	CASE_CHECK_EQ(logf(0), -HUGE_VALF, "log float, -inf");
	CASE_CHECK_BALLPARK(logf(powf(M_E, 2.f)), 2.f, 0.001f, "log float, e^2");
	CASE_CHECK_BALLPARK(logf(powf(M_E, 8.8f)), 8.8f, 0.001f, "log float, e^8.8");
	CASE_CHECK_BALLPARK(logf(powf(M_E, -4.f)), -4.f, 0.001f, "log float, e^-4");

	CASE_CHECK_EQ(log(1.), 0., "log double, 1");
	CASE_CHECK_EQ(log(HUGE_VALF), HUGE_VALF, "log double, inf");
	CASE_CHECK_EQ(log(0), -HUGE_VALF, "log double, -inf");
	CASE_CHECK_BALLPARK(log(pow(M_E, 2)), 2., 0.001, "log double, e^2");
	CASE_CHECK_BALLPARK(log(pow(M_E, 8.8)), 8.8, 0.001, "log double, e^8.8");
	CASE_CHECK_BALLPARK(log(pow(M_E, -4.)), -4., 0.001, "log double, e^-4");

	CASE_CHECK_EQ(logl(1.l), 0.l, "log float, 1");
	CASE_CHECK_EQ(logl(HUGE_VALF), HUGE_VALF, "log float, inf");
	CASE_CHECK_EQ(logl(0), -HUGE_VALF, "log float, -inf");
	CASE_CHECK_BALLPARK(logl(powl(M_E, 2.l)), 2.l, 0.001l, "log float, e^2");
	CASE_CHECK_BALLPARK(logl(powl(M_E, 8.8l)), 8.8l, 0.001l, "log float, e^8.8");
	CASE_CHECK_BALLPARK(logl(powl(M_E, -4.l)), -4.l, 0.001l, "log float, e^-4");



	CASE_CHECK_EQ(log10f(1.f), 0.f, "log10 float, 1");
	CASE_CHECK_EQ(log10f(HUGE_VALF), HUGE_VALF, "log10 float, inf");
	CASE_CHECK_EQ(log10f(0), -HUGE_VALF, "log10 float, -inf");
	CASE_CHECK_BALLPARK(log10f(powf(10.f, 2.f)), 2.f, 0.001f, "log10 float, 10^2");
	CASE_CHECK_BALLPARK(log10f(powf(10.f, 8.8f)), 8.8f, 0.001f, "log10 float, 10^8.8");
	CASE_CHECK_BALLPARK(log10f(powf(10.f, -4.f)), -4.f, 0.001f, "log10 float, 10^-4");

	CASE_CHECK_EQ(log10(1.), 0., "log10 double, 1");
	CASE_CHECK_EQ(log10(HUGE_VALF), HUGE_VALF, "log10 double, inf");
	CASE_CHECK_EQ(log10(0), -HUGE_VALF, "log10 double, -inf");
	CASE_CHECK_BALLPARK(log10(pow(10., 2)), 2., 0.001, "log10 double, 10^2");
	CASE_CHECK_BALLPARK(log10(pow(10., 8.8)), 8.8, 0.001, "log10 double, 10^8.8");
	CASE_CHECK_BALLPARK(log10(pow(10., -4.)), -4., 0.001, "log10 double, 10^-4");

	CASE_CHECK_EQ(log10l(1.l), 0.l, "log10 float, 1");
	CASE_CHECK_EQ(log10l(HUGE_VALF), HUGE_VALF, "log10 float, inf");
	CASE_CHECK_EQ(log10l(0), -HUGE_VALF, "log10 float, -inf");
	CASE_CHECK_BALLPARK(log10l(powl(10.l, 2.l)), 2.l, 0.001l, "log10 float, 10^2");
	CASE_CHECK_BALLPARK(log10f(powl(10.l, 8.8l)), 8.8l, 0.001l, "log10 float, 10^8.8");
	CASE_CHECK_BALLPARK(log10f(powl(10.l, -4.l)), -4.l, 0.001l, "log10 float, 10^-4");


	CASE_CHECK_EQ(log1pf(0.f), 0.f, "log1p float, 1");
	CASE_CHECK_EQ(log1pf(HUGE_VALF), HUGE_VALF, "log1p float, inf");
	CASE_CHECK_EQ(log1pf(-1.f), -HUGE_VALF, "log1p float, -inf");
	CASE_CHECK_BALLPARK(log1pf(powf(M_E, 2.f) - 1.f), 2.f, 0.001f, "log1p float, e^2");
	CASE_CHECK_BALLPARK(log1pf(powf(M_E, 8.8f) - 1.f), 8.8f, 0.001f, "log1p float, e^8.8");
	CASE_CHECK_BALLPARK(log1pf(powf(M_E, -4.f) - 1.f), -4.f, 0.001f, "log1p float, e^-4");

	CASE_CHECK_EQ(log1p(0.), 0., "log1p double, 1");
	CASE_CHECK_EQ(log1p(HUGE_VALF), HUGE_VALF, "log1p double, inf");
	CASE_CHECK_EQ(log1p(-1.), -HUGE_VALF, "log1p double, -inf");
	CASE_CHECK_BALLPARK(log1p(pow(M_E, 2) - 1.), 2., 0.001, "log1p double, e^2");
	CASE_CHECK_BALLPARK(log1p(pow(M_E, 8.8) - 1.), 8.8, 0.001, "log1p double, e^8.8");
	CASE_CHECK_BALLPARK(log1p(pow(M_E, -4.) - 1.), -4., 0.001, "log1p double, e^-4");

	CASE_CHECK_EQ(log1pl(0.l), 0.l, "log1p float, 1");
	CASE_CHECK_EQ(log1pl(HUGE_VALF), HUGE_VALF, "log1p float, inf");
	CASE_CHECK_EQ(log1pl(-1.), -HUGE_VALF, "log1p float, -inf");
	CASE_CHECK_BALLPARK(log1pl(powl(M_E, 2.l) - 1.l), 2.l, 0.001l, "log1p float, e^2");
	CASE_CHECK_BALLPARK(log1pl(powl(M_E, 8.8l) - 1.l), 8.8l, 0.001l, "log1p float, e^8.8");
	CASE_CHECK_BALLPARK(log1pl(powl(M_E, -4.l) - 1.l), -4.l, 0.001l, "log1p float, e^-4");

	CASE_CHECK_EQ(log2f(1.f), 0.f, "log2 float, 1");
	CASE_CHECK_EQ(log2f(HUGE_VALF), HUGE_VALF, "log2 float, inf");
	CASE_CHECK_EQ(log2f(0), -HUGE_VALF, "log2 float, -inf");
	CASE_CHECK_BALLPARK(log2f(powf(2.f, 2.f)), 2.f, 0.001f, "log2 float, 2^2");
	CASE_CHECK_BALLPARK(log2f(powf(2.f, 8.8f)), 8.8f, 0.001f, "log2 float, 2^8.8");
	CASE_CHECK_BALLPARK(log2f(powf(2.f, -4.f)), -4.f, 0.001f, "log2 float, 2^-4");

	CASE_CHECK_EQ(log2(1.), 0., "log2 double, 1");
	CASE_CHECK_EQ(log2(HUGE_VALF), HUGE_VALF, "log2 double, inf");
	CASE_CHECK_EQ(log2(0), -HUGE_VALF, "log2 double, -inf");
	CASE_CHECK_BALLPARK(log2(pow(2., 2)), 2., 0.001, "log2 double, 2^2");
	CASE_CHECK_BALLPARK(log2(pow(2., 8.8)), 8.8, 0.001, "log2 double, 2^8.8");
	CASE_CHECK_BALLPARK(log2(pow(2., -4.)), -4., 0.001, "log2 double, 2^-4");

	CASE_CHECK_EQ(log2l(1.l), 0.l, "log2 float, 1");
	CASE_CHECK_EQ(log2l(HUGE_VALF), HUGE_VALF, "log2 float, inf");
	CASE_CHECK_EQ(log2l(0), -HUGE_VALF, "log2 float, -inf");
	CASE_CHECK_BALLPARK(log2l(powl(2.l, 2.l)), 2.l, 0.001l, "log2 float, 2^2");
	CASE_CHECK_BALLPARK(log2f(powl(2.l, 8.8l)), 8.8l, 0.001l, "log2 float, 2^8.8");
	CASE_CHECK_BALLPARK(log2f(powl(2.l, -4.l)), -4.l, 0.001l, "log2 float, 2^-4");

	CASE_CHECK_EQ(logbf(0), -HUGE_VALF, "logb float, 0");
	CASE_CHECK_EQ(logbf(HUGE_VALF), HUGE_VALF, "logb float, INT_MAX");
	CASE_CHECK_NE(isnan(logbf(NAN)), 0, "logb float, nan");
	CASE_CHECK_EQ(logbf(8.f), 3, "logb float, 8");
	CASE_CHECK_EQ(logbf(0.25f), -2, "logb float, 0.25");

	CASE_CHECK_EQ(logb(0), -HUGE_VAL, "logb double, 0");
	CASE_CHECK_EQ(logb(HUGE_VAL), HUGE_VAL, "logb double, INT_MAX");
	CASE_CHECK_NE(isnan(logb(NAN)), 0, "logb double, nan");
	CASE_CHECK_EQ(logb(8.), 3., "logb double, 8");
	CASE_CHECK_EQ(logb(0.25), -2., "logb double, 0.25");

	CASE_CHECK_EQ(logbl(0), -HUGE_VALL, "logb long double, 0");
	CASE_CHECK_EQ(logbl(HUGE_VALL), HUGE_VALL, "logb long double, INT_MAX");
	CASE_CHECK_NE(isnan(logbl(NAN)), 0, "logb long double, nan");
	CASE_CHECK_EQ(logbl(8.f), 3.l, "logb long double, 8");
	CASE_CHECK_EQ(logbl(0.25f), -2.l , "logb long double, 0.25");
}

void test_rounding()
{
	CASE_CHECK_EQ(ceilf(0.f), 0.f, "ceil float, test 0");
	CASE_CHECK_EQ(ceilf(0.5f), 1.f, "ceil float, test 0.5");
	CASE_CHECK_EQ(ceil(0.), 0., "ceil double, test 0");
	CASE_CHECK_EQ(ceil(0.5), 1., "ceil double, test 0.5");
	CASE_CHECK_EQ(ceill(0.l), 0.l, "ceil long double, test 0");
	CASE_CHECK_EQ(ceill(0.5l), 1.l, "ceil long double, test 0.5");
	CASE_CHECK_EQ(floorf(0.f), 0.f, "floor float, test 0");
	CASE_CHECK_EQ(floorf(0.5f), 0.f, "floor float, test 0.5");
	CASE_CHECK_EQ(floor(0.), 0., "floor double, test 0");
	CASE_CHECK_EQ(floor(0.5), 0., "floor double, test 0.5");
	CASE_CHECK_EQ(floorl(0.l), 0.l, "floor long double, test 0");
	CASE_CHECK_EQ(floorl(0.5l), 0.l, "floor long double, test 0.5");
	CASE_CHECK_EQ(roundf(0.6f), 1.f, "round float, test 0.6");
	CASE_CHECK_EQ(roundf(0.5f), 0.f, "round float, test 0.5");
	CASE_CHECK_EQ(round(0.6), 1., "round double, test 0.6");
	CASE_CHECK_EQ(round(0.5), 0., "round double, test 0.5");
	CASE_CHECK_EQ(roundl(0.6l), 1.l, "round long double, test 0.6");
	CASE_CHECK_EQ(roundl(0.5l), 0.l, "round long double, test 0.5");
	CASE_CHECK_EQ(lroundf(0.6f), 1, "lround float, test 0.6");
	CASE_CHECK_EQ(lroundf(0.5f), 0, "lround float, test 0.5");
	CASE_CHECK_EQ(lround(0.6), 1, "lround double, test 0.6");
	CASE_CHECK_EQ(lround(0.5), 0, "lround double, test 0.5");
	CASE_CHECK_EQ(lroundl(0.6l), 1, "lround long double, test 0.6");
	CASE_CHECK_EQ(lroundl(0.5l), 0, "lround long double, test 0.5");
	CASE_CHECK_EQ(llroundf(0.6f), 1, "llround float, test 0.6");
	CASE_CHECK_EQ(llroundf(0.5f), 0, "llround float, test 0.5");
	CASE_CHECK_EQ(llround(0.6), 1, "llround double, test 0.6");
	CASE_CHECK_EQ(llround(0.5), 0, "llround double, test 0.5");
	CASE_CHECK_EQ(llroundl(0.6l), 1, "llround long double, test 0.6");
	CASE_CHECK_EQ(llroundl(0.5l), 0, "llround long double, test 0.5");
	CASE_CHECK_EQ(truncf(1.f), 1, "trunc float, test 1");
	CASE_CHECK_EQ(truncf(0.4f), 0, "trunc float, test 0.4");
	CASE_CHECK_EQ(truncf(0.f), 0, "trunc float, test 0");
	CASE_CHECK_EQ(trunc(1.), 1, "trunc double, test 1");
	CASE_CHECK_EQ(trunc(0.4), 0, "trunc double, test 0.4");
	CASE_CHECK_EQ(trunc(0.), 0, "trunc double, test 0");
	CASE_CHECK_EQ(truncl(1.l), 1, "trunc long double, test 1");
	CASE_CHECK_EQ(truncl(0.4l), 0, "trunc long double, test 0.4");
	CASE_CHECK_EQ(truncl(0.l), 0, "trunc long double, test 0");

	int nOrgRound = fegetround();

	fesetround(FE_DOWNWARD);
	CASE_CHECK_EQ(nearbyintf(0.5f), 0.f, "FE_DOWNWARD, nearbyint float, test 0.5");
	CASE_CHECK_EQ(nearbyintf(0.4f), 0.f, "FE_DOWNWARD, nearbyint float, test 0.4");
	CASE_CHECK_EQ(nearbyint(0.5), 0., "FE_DOWNWARD, nearbyint double, test 0.5");
	CASE_CHECK_EQ(nearbyint(0.4), 0., "FE_DOWNWARD, nearbyint double, test 0.4");
	CASE_CHECK_EQ(nearbyintl(0.5l), 0.l, "FE_DOWNWARD, nearbyint long double, test 0.5");
	CASE_CHECK_EQ(nearbyintl(0.4l), 0.l, "FE_DOWNWARD, nearbyint long double, test 0.4");
	CASE_CHECK_EQ(rintf(0.5f), 0.f, "FE_DOWNWARD, rint float, test 0.5");
	CASE_CHECK_EQ(rintf(0.4f), 0.f, "FE_DOWNWARD, rint float, test 0.4");
	CASE_CHECK_EQ(rint(0.5), 0., "FE_DOWNWARD, rint double, test 0.5");
	CASE_CHECK_EQ(rint(0.4), 0., "FE_DOWNWARD, rint double, test 0.4");
	CASE_CHECK_EQ(rintl(0.5l), 0.l, "FE_DOWNWARD, rint long double, test 0.5");
	CASE_CHECK_EQ(rintl(0.4l), 0.l, "FE_DOWNWARD, rint long double, test 0.4");
	CASE_CHECK_EQ(lrintf(0.5f), 0, "FE_DOWNWARD, lrint float, test 0.5");
	CASE_CHECK_EQ(lrintf(0.4f), 0, "FE_DOWNWARD, lrint float, test 0.4");
	CASE_CHECK_EQ(lrint(0.5), 0, "FE_DOWNWARD, lrint double, test 0.5");
	CASE_CHECK_EQ(lrint(0.4), 0, "FE_DOWNWARD, lrint double, test 0.4");
	CASE_CHECK_EQ(lrintl(0.5l), 0, "FE_DOWNWARD, lrint long double, test 0.5");
	CASE_CHECK_EQ(lrintl(0.4l), 0, "FE_DOWNWARD, lrint long double, test 0.4");
	CASE_CHECK_EQ(llrintf(0.5f), 0, "FE_DOWNWARD, llrint float, test 0.5");
	CASE_CHECK_EQ(llrintf(0.4f), 0, "FE_DOWNWARD, llrint float, test 0.4");
	CASE_CHECK_EQ(llrint(0.5), 0, "FE_DOWNWARD, llrint double, test 0.5");
	CASE_CHECK_EQ(llrint(0.4), 0, "FE_DOWNWARD, llrint double, test 0.4");
	CASE_CHECK_EQ(llrintl(0.5l), 0, "FE_DOWNWARD, llrint long double, test 0.5");
	CASE_CHECK_EQ(llrintl(0.4l), 0, "FE_DOWNWARD, llrint long double, test 0.4");

	fesetround(FE_TONEAREST);
	CASE_CHECK_EQ(nearbyintf(0.6f), 1.f, "FE_TONEAREST, nearbyint float, test 0.6");
	CASE_CHECK_EQ(nearbyintf(0.5f), 0.f, "FE_TONEAREST, nearbyint float, test 0.5");
	CASE_CHECK_EQ(nearbyint(0.6), 1., "FE_TONEAREST, nearbyint double, test 0.6");
	CASE_CHECK_EQ(nearbyint(0.5), 0., "FE_TONEAREST, nearbyint double, test 0.5");
	CASE_CHECK_EQ(nearbyintl(0.6l), 1.l, "FE_TONEAREST, nearbyint long double, test 0.6");
	CASE_CHECK_EQ(nearbyintl(0.5l), 0.l, "FE_TONEAREST, nearbyint long double, test 0.5");
	CASE_CHECK_EQ(rintf(0.6f), 1.f, "FE_TONEAREST, rint float, test 0.6");
	CASE_CHECK_EQ(rintf(0.5f), 0.f, "FE_TONEAREST, rint float, test 0.5");
	CASE_CHECK_EQ(rint(0.6), 1., "FE_TONEAREST, rint double, test 0.6");
	CASE_CHECK_EQ(rint(0.5), 0., "FE_TONEAREST, rint double, test 0.5");
	CASE_CHECK_EQ(rintl(0.6l), 1.l, "FE_TONEAREST, rint long double, test 0.6");
	CASE_CHECK_EQ(rintl(0.5l), 0.l, "FE_TONEAREST, rint long double, test 0.5");
	CASE_CHECK_EQ(lrintf(0.6f), 1, "FE_TONEAREST, lrint float, test 0.6");
	CASE_CHECK_EQ(lrintf(0.5f), 0, "FE_TONEAREST, lrint float, test 0.5");
	CASE_CHECK_EQ(lrint(0.6), 1, "FE_TONEAREST, lrint double, test 0.6");
	CASE_CHECK_EQ(lrint(0.5), 0, "FE_TONEAREST, lrint double, test 0.5");
	CASE_CHECK_EQ(lrintl(0.6l), 1, "FE_TONEAREST, lrint long double, test 0.6");
	CASE_CHECK_EQ(lrintl(0.5l), 0, "FE_TONEAREST, lrint long double, test 0.5");
	CASE_CHECK_EQ(llrintf(0.6f), 1, "FE_TONEAREST, llrint float, test 0.6");
	CASE_CHECK_EQ(llrintf(0.5f), 0, "FE_TONEAREST, llrint float, test 0.5");
	CASE_CHECK_EQ(llrint(0.6), 1, "FE_TONEAREST, llrint double, test 0.6");
	CASE_CHECK_EQ(llrint(0.5), 0, "FE_TONEAREST, llrint double, test 0.5");
	CASE_CHECK_EQ(llrintl(0.6l), 1, "FE_TONEAREST, llrint long double, test 0.6");
	CASE_CHECK_EQ(llrintl(0.5l), 0, "FE_TONEAREST, llrint long double, test 0.5");

	fesetround(FE_TOWARDZERO);
	CASE_CHECK_EQ(nearbyintf(0.5f), 0.f, "FE_TOWARDZERO, nearbyint float, test 0.5");
	CASE_CHECK_EQ(nearbyintf(0.4f), 0.f, "FE_TOWARDZERO, nearbyint float, test 0.4");
	CASE_CHECK_EQ(nearbyint(0.5), 0., "FE_TOWARDZERO, nearbyint double, test 0.5");
	CASE_CHECK_EQ(nearbyint(0.4), 0., "FE_TOWARDZERO, nearbyint double, test 0.4");
	CASE_CHECK_EQ(nearbyintl(0.5l), 0.l, "FE_TOWARDZERO, nearbyint long double, test 0.5");
	CASE_CHECK_EQ(nearbyintl(0.4l), 0.l, "FE_TOWARDZERO, nearbyint long double, test 0.4");
	CASE_CHECK_EQ(rintf(0.5f), 0.f, "FE_TOWARDZERO, rint float, test 0.5");
	CASE_CHECK_EQ(rintf(0.4f), 0.f, "FE_TOWARDZERO, rint float, test 0.4");
	CASE_CHECK_EQ(rint(0.5), 0., "FE_TOWARDZERO, rint double, test 0.5");
	CASE_CHECK_EQ(rint(0.4), 0., "FE_TOWARDZERO, rint double, test 0.4");
	CASE_CHECK_EQ(rintl(0.5l), 0.l, "FE_TOWARDZERO, rint long double, test 0.5");
	CASE_CHECK_EQ(rintl(0.4l), 0.l, "FE_TOWARDZERO, rint long double, test 0.4");
	CASE_CHECK_EQ(lrintf(0.5f), 0, "FE_TOWARDZERO, lrint float, test 0.5");
	CASE_CHECK_EQ(lrintf(0.4f), 0, "FE_TOWARDZERO, lrint float, test 0.4");
	CASE_CHECK_EQ(lrint(0.5), 0, "FE_TOWARDZERO, lrint double, test 0.5");
	CASE_CHECK_EQ(lrint(0.4), 0, "FE_TOWARDZERO, lrint double, test 0.4");
	CASE_CHECK_EQ(lrintl(0.5l), 0, "FE_TOWARDZERO, lrint long double, test 0.5");
	CASE_CHECK_EQ(lrintl(0.4l), 0, "FE_TOWARDZERO, lrint long double, test 0.4");
	CASE_CHECK_EQ(llrintf(0.5f), 0, "FE_TOWARDZERO, llrint float, test 0.5");
	CASE_CHECK_EQ(llrintf(0.4f), 0, "FE_TOWARDZERO, llrint float, test 0.4");
	CASE_CHECK_EQ(llrint(0.5), 0, "FE_TOWARDZERO, llrint double, test 0.5");
	CASE_CHECK_EQ(llrint(0.4), 0, "FE_TOWARDZERO, llrint double, test 0.4");
	CASE_CHECK_EQ(llrintl(0.5l), 0, "FE_TOWARDZERO, llrint long double, test 0.5");
	CASE_CHECK_EQ(llrintl(0.4l), 0, "FE_TOWARDZERO, llrint long double, test 0.4");

	fesetround(FE_UPWARD);
	CASE_CHECK_EQ(nearbyintf(0.5f), 1.f, "FE_UPWARD, nearbyint float, test 0.5");
	CASE_CHECK_EQ(nearbyintf(0.4f), 1.f, "FE_UPWARD, nearbyint float, test 0.4");
	CASE_CHECK_EQ(nearbyint(0.5), 1., "FE_UPWARD, nearbyint double, test 0.5");
	CASE_CHECK_EQ(nearbyint(0.4), 1., "FE_UPWARD, nearbyint double, test 0.4");
	CASE_CHECK_EQ(nearbyintl(0.5l), 1.l, "FE_UPWARD, nearbyint long double, test 0.5");
	CASE_CHECK_EQ(nearbyintl(0.4l), 1.l, "FE_UPWARD, nearbyint long double, test 0.4");
	CASE_CHECK_EQ(rintf(0.5f), 1.f, "FE_UPWARD, rint float, test 0.5");
	CASE_CHECK_EQ(rintf(0.4f), 1.f, "FE_UPWARD, rint float, test 0.4");
	CASE_CHECK_EQ(rint(0.5), 1., "FE_UPWARD, rint double, test 0.5");
	CASE_CHECK_EQ(rint(0.4), 1., "FE_UPWARD, rint double, test 0.4");
	CASE_CHECK_EQ(rintl(0.5l), 1.l, "FE_UPWARD, rint long double, test 0.5");
	CASE_CHECK_EQ(rintl(0.4l), 1.l, "FE_UPWARD, rint long double, test 0.4");
	CASE_CHECK_EQ(lrintf(0.5f), 1, "FE_UPWARD, lrint float, test 0.5");
	CASE_CHECK_EQ(lrintf(0.4f), 1, "FE_UPWARD, lrint float, test 0.4");
	CASE_CHECK_EQ(lrint(0.5), 1, "FE_UPWARD, lrint double, test 0.5");
	CASE_CHECK_EQ(lrint(0.4), 1, "FE_UPWARD, lrint double, test 0.4");
	CASE_CHECK_EQ(lrintl(0.5l), 1, "FE_UPWARD, lrint long double, test 0.5");
	CASE_CHECK_EQ(lrintl(0.4l), 1, "FE_UPWARD, lrint long double, test 0.4");
	CASE_CHECK_EQ(llrintf(0.5f), 1, "FE_UPWARD, llrint float, test 0.5");
	CASE_CHECK_EQ(llrintf(0.4f), 1, "FE_UPWARD, llrint float, test 0.4");
	CASE_CHECK_EQ(llrint(0.5), 1, "FE_UPWARD, llrint double, test 0.5");
	CASE_CHECK_EQ(llrint(0.4), 1, "FE_UPWARD, llrint double, test 0.4");
	CASE_CHECK_EQ(llrintl(0.5l), 1, "FE_UPWARD, llrint long double, test 0.5");
	CASE_CHECK_EQ(llrintl(0.4l), 1, "FE_UPWARD, llrint long double, test 0.4");
	fesetround(nOrgRound);
}

void test_modf()
{
	float fltwhole;
	double dblwhole;
	long double ldblwhole;
	CASE_CHECK_BALLPARK(modff(123.45, &fltwhole), 0.45f, 0.001f, "modf float, ret, 123.45");
	CASE_CHECK_EQ(fltwhole, 123.f, "modf float, ptr, 123.45");
	CASE_CHECK_EQ(modff(-0.f, &fltwhole), -0.f, "modf float, ret, -0.");
	CASE_CHECK_EQ(fltwhole, -0.f, "modf float, ptr, -0.");
	CASE_CHECK_EQ(modff(-HUGE_VALF, &fltwhole), -0.f, "modf float, ret, -inf");
	CASE_CHECK_EQ(fltwhole, -HUGE_VALF, "modf float, ptr, -inf");

	CASE_CHECK_BALLPARK(modf(123.45, &dblwhole), 0.45, 0.001, "modf double, ret, 123.45");
	CASE_CHECK_EQ(dblwhole, 123., "modf double, ptr, 123.45");
	CASE_CHECK_EQ(modf(-0., &dblwhole), -0., "modf double, ret, -0.");
	CASE_CHECK_EQ(dblwhole, -0., "modf double, ptr, -0.");
	CASE_CHECK_EQ(modf(-HUGE_VAL, &dblwhole), -0., "modf double, ret, -inf");
	CASE_CHECK_EQ(dblwhole, -HUGE_VAL, "modf double, ptr, -inf");

	CASE_CHECK_BALLPARK(modfl(123.45l, &ldblwhole), 0.45l, 0.001l,"modf long double, ret, 123.45");
	CASE_CHECK_EQ(ldblwhole, 123.l, "modf long double, ptr, 123.45");
	CASE_CHECK_EQ(modfl(-0., &ldblwhole), -0.l, "modf long double, ret, -0.");
	CASE_CHECK_EQ(ldblwhole, -0.l, "modf long double, ptr, -0.");
	CASE_CHECK_EQ(modfl(-HUGE_VALL, &ldblwhole), -0.l, "modf long double, ret, -inf");
	CASE_CHECK_EQ(ldblwhole, -HUGE_VALL, "modf long double, ptr, -inf");
}

void test_copysign()
{
	CASE_CHECK_EQ(copysignf(122.f, 1.f), 122.f, "copysign float, 122 with sign of 1");
	CASE_CHECK_EQ(copysignf(122.f, -1.f), -122.f, "copysign float, 122 with sign of -1");
	CASE_CHECK_EQ(copysignf(0.f, -1.f), -0.f, "copysign float, 0 with sign of -1");
	CASE_CHECK_EQ(copysignf(HUGE_VALF, -1.f), -HUGE_VALF, "copysign float, inf with sign of -1");

	CASE_CHECK_EQ(copysign(122., 1.), 122., "copysign double, 122 with sign of 1");
	CASE_CHECK_EQ(copysign(122., -1.), -122., "copysign double, 122 with sign of -1");
	CASE_CHECK_EQ(copysign(0., -1.), -0., "copysign double, 0 with sign of -1");
	CASE_CHECK_EQ(copysign(HUGE_VAL, -1.), -HUGE_VAL, "copysign double, inf with sign of -1");

	CASE_CHECK_EQ(copysignl(122.l, 1.l), 122.l, "copysign long double, 122 with sign of 1");
	CASE_CHECK_EQ(copysignl(122.l, -1.l), -122.l, "copysign long double, 122 with sign of -1");
	CASE_CHECK_EQ(copysignl(0.l, -1.l), -0.l, "copysign long double, 0 with sign of -1");
	CASE_CHECK_EQ(copysignl(HUGE_VALL, -1.l), -HUGE_VALL, "copysign long double, inf with sign of -1");
}

void test_remquo()
{
	int rq;
	CASE_CHECK_EQ(remquof(4888.f, 488.f, &rq), 8.f, "remquo float, ret, 4888/488");
	CASE_CHECK_EQ(rq, 10, "remquo float, ptr, 4888/488");
	CASE_CHECK_NE(isnan(remquof(4888.f, 0.f, &rq)), 0, "remquo float, ret, 4888/0");
	CASE_CHECK_EQ(rq, 0, "remquo float, ptr, 4888/0");

	CASE_CHECK_EQ(remquo(4888., 488., &rq), 8., "remquo double, ret, 4888/488");
	CASE_CHECK_EQ(rq, 10, "remquo double, ptr, 4888/488");
	CASE_CHECK_NE(isnan(remquo(4888., 0., &rq)), 0., "remquo double, ret, 4888/0");
	CASE_CHECK_EQ(rq, 0, "remquo double, ptr, 4888/0");

	CASE_CHECK_EQ(remquol(4888.l, 488.l, &rq), 8.l, "remquo long double, ret, 4888/488");
	CASE_CHECK_EQ(rq, 10, "remquo long double, ptr, 4888/488");
	CASE_CHECK_NE(isnan(remquol(4888.l, 0.l, &rq)), 0.l, "remquo long double, ret, 4888/0");
	CASE_CHECK_EQ(rq, 0, "remquo long double, ptr, 4888/0");

	CASE_CHECK_BALLPARK(remainderf(4888.f, 488.f), 8.f, 0.001f, "remainder float, ret, 4888/488");
	CASE_CHECK_BALLPARK(remainderf(4888.f, -488.f), -8.f, 0.001f, "remainder float, ret, 4888/-488");
	CASE_CHECK_BALLPARK(remainderf(-4888.f, 488.f), -8.f, 0.001f, "remainder float, ret, -4888/488");
	CASE_CHECK_BALLPARK(remainderf(-4888.f, -488.f), 8.f, 0.001f, "remainder float, ret, -4888/-488");
	CASE_CHECK_BALLPARK(remainderf(48.f, HUGE_VALF), 48.f, 0.001f, "remainder float, ret, -4888/inf");
	CASE_CHECK_NE(isnan(remainderf(4888.f, 0.f)), 0, "remainder float, ret, 4888/0");
	CASE_CHECK_BALLPARK(remainder(4888., 488.), 8., 0.001, "remainder double, ret, 4888/488");
	CASE_CHECK_BALLPARK(remainder(4888., -488.), -8., 0.001, "remainder double, ret, 4888/-488");
	CASE_CHECK_BALLPARK(remainder(-4888., 488.), -8., 0.001, "remainder double, ret, -4888/488");
	CASE_CHECK_BALLPARK(remainder(-4888., -488.), 8., 0.001, "remainder double, ret, -4888/-488");
	CASE_CHECK_BALLPARK(remainder(48., HUGE_VAL), 48., 0.001, "remainder double, ret, -4888/inf");
	CASE_CHECK_NE(isnan(remainder(4888., 0.)), 0., "remainder double, ret, 4888/0");
	CASE_CHECK_BALLPARK(remainderl(4888.l, 488.l), 8.l, 0.001l, "remainder long double, ret, 4888/488");
	CASE_CHECK_BALLPARK(remainderl(4888.l, -488.l), -8.l, 0.001l, "remainder long double, ret, 4888/-488");
	CASE_CHECK_BALLPARK(remainderl(-4888.l, 488.l), -8.l, 0.001l, "remainder long double, ret, -4888/488");
	CASE_CHECK_BALLPARK(remainderl(-4888.l, -488.l), 8.l, 0.001l, "remainder long double, ret, -4888/-488");
	CASE_CHECK_BALLPARK(remainderl(48.l, HUGE_VAL), 48., 0.001l, "remainder long double, ret, -4888/inf");
	CASE_CHECK_NE(isnan(remainderl(4888.l, 0.l)), 0.l, "remainder long double, ret, 4888/0");

	CASE_CHECK_BALLPARK(fmodf(4888.f, 488.f), 8.f, 0.001f, "fmod float, ret, 4888/488");
	CASE_CHECK_BALLPARK(fmodf(4888.f, -488.f), -8.f, 0.001f, "fmod float, ret, 4888/-488");
	CASE_CHECK_BALLPARK(fmodf(-4888.f, 488.f), -8.f, 0.001f, "fmod float, ret, -4888/488");
	CASE_CHECK_BALLPARK(fmodf(-4888.f, -488.f), 8.f, 0.001f, "fmod float, ret, -4888/-488");
	CASE_CHECK_BALLPARK(fmodf(48.f, HUGE_VALF), 48.f, 0.001f, "fmod float, ret, -4888/inf");
	CASE_CHECK_NE(isnan(fmodf(4888.f, 0.f)), 0, "fmod float, ret, 4888/0");
	CASE_CHECK_BALLPARK(fmod(4888., 488.), 8., 0.001, "fmod double, ret, 4888/488");
	CASE_CHECK_BALLPARK(fmod(4888., -488.), -8., 0.001, "fmod double, ret, 4888/-488");
	CASE_CHECK_BALLPARK(fmod(-4888., 488.), -8., 0.001, "fmod double, ret, -4888/488");
	CASE_CHECK_BALLPARK(fmod(-4888., -488.), 8., 0.001, "fmod double, ret, -4888/-488");
	CASE_CHECK_BALLPARK(fmod(48., HUGE_VAL), 48., 0.001, "fmod double, ret, -4888/inf");
	CASE_CHECK_NE(isnan(fmod(4888., 0.)), 0., "fmod double, ret, 4888/0");
	CASE_CHECK_BALLPARK(fmodl(4888.l, 488.l), 8.l, 0.001l, "fmod long double, ret, 4888/488");
	CASE_CHECK_BALLPARK(fmodl(4888.l, -488.l), -8.l, 0.001l, "fmod long double, ret, 4888/-488");
	CASE_CHECK_BALLPARK(fmodl(-4888.l, 488.l), -8.l, 0.001l, "fmod long double, ret, -4888/488");
	CASE_CHECK_BALLPARK(fmodl(-4888.l, -488.l), 8.l, 0.001l, "fmod long double, ret, -4888/-488");
	CASE_CHECK_BALLPARK(fmodl(48.l, HUGE_VAL), 48., 0.001l, "fmod long double, ret, -4888/inf");
	CASE_CHECK_NE(isnan(fmodl(4888.l, 0.l)), 0.l, "fmod long double, ret, 4888/0");
}

void test_minmax()
{
	CASE_CHECK_BALLPARK(fmaxf(8.f, 4.f), 8.f, 0.001f, "fmax float, fmax(8,4)");
	CASE_CHECK_BALLPARK(fmaxf(4.f, 8.f), 8.f, 0.001f, "fmax float, fmax(4,8)");
	CASE_CHECK_BALLPARK(fmaxf(8.f, NAN), 8.f, 0.001f, "fmax float, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fmaxf(NAN, 8.f), 8.f, 0.001f, "fmax float, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fmaxf(NAN, NAN)), 0, "fmax float, fmax(nan,nan)");

	CASE_CHECK_BALLPARK(fmax(8., 4.), 8., 0.001, "fmax double, fmax(8,4)");
	CASE_CHECK_BALLPARK(fmax(4., 8.), 8., 0.001, "fmax double, fmax(4,8)");
	CASE_CHECK_BALLPARK(fmax(8., NAN), 8., 0.001, "fmax double, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fmax(NAN, 8.), 8., 0.001, "fmax double, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fmax(NAN, NAN)), 0, "fmax double, fmax(nan,nan)");

	CASE_CHECK_BALLPARK(fmaxl(8.l, 4.l), 8.l, 0.001l, "fmax long double, fmax(8,4)");
	CASE_CHECK_BALLPARK(fmaxl(4.l, 8.l), 8.l, 0.001l, "fmax long double, fmax(4,8)");
	CASE_CHECK_BALLPARK(fmaxl(8.l, NAN), 8.l, 0.001l, "fmax long double, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fmaxl(NAN, 8.l), 8.l, 0.001l, "fmax long double, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fmaxl(NAN, NAN)), 0, "fmax long double, fmax(nan,nan)");

	CASE_CHECK_BALLPARK(fminf(8.f, 4.f), 4.f, 0.001f, "fmax float, fmax(8,4)");
	CASE_CHECK_BALLPARK(fminf(4.f, 8.f), 4.f, 0.001f, "fmax float, fmax(4,8)");
	CASE_CHECK_BALLPARK(fminf(8.f, NAN), 8.f, 0.001f, "fmax float, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fminf(NAN, 8.f), 8.f, 0.001f, "fmax float, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fminf(NAN, NAN)), 0, "fmax float, fmax(nan,nan)");

	CASE_CHECK_BALLPARK(fmin(8., 4.), 4., 0.001, "fmax double, fmax(8,4)");
	CASE_CHECK_BALLPARK(fmin(4., 8.), 4., 0.001, "fmax double, fmax(4,8)");
	CASE_CHECK_BALLPARK(fmin(8., NAN), 8., 0.001, "fmax double, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fmin(NAN, 8.), 8., 0.001, "fmax double, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fmin(NAN, NAN)), 0, "fmax double, fmax(nan,nan)");

	CASE_CHECK_BALLPARK(fminl(8.l, 4.l), 4.l, 0.001l, "fmax long double, fmax(8,4)");
	CASE_CHECK_BALLPARK(fminl(4.l, 8.l), 4.l, 0.001l, "fmax long double, fmax(4,8)");
	CASE_CHECK_BALLPARK(fminl(8.l, NAN), 8.l, 0.001l, "fmax long double, fmax(8,nan)");
	CASE_CHECK_BALLPARK(fminl(NAN, 8.l), 8.l, 0.001l, "fmax long double, fmax(nan,8)");
	CASE_CHECK_NE(isnan(fminl(NAN, NAN)), 0, "fmax long double, fmax(nan,nan)");
}

void test_fdim()
{
	CASE_CHECK_BALLPARK(fdimf(5.f, 2.f), 3.f, 0.001f, "fdim float, fdim(5,2)");
	CASE_CHECK_BALLPARK(fdimf(7.f, 1.f), 6.f, 0.001f, "fdim float, fdim(7,1)");
	CASE_CHECK_BALLPARK(fdimf(5.f, 5.f), 0.f, 0.001f, "fdim float, fdim(5,5)");
	CASE_CHECK_BALLPARK(fdimf(2.f, 5.f), 0.f, 0.001f, "fdim float, fdim(2,5)");
	CASE_CHECK_NE(isnan(fdimf(5.f, NAN)), 0, "fdim float, fdim(5,nan)");
	CASE_CHECK_NE(isnan(fdimf(NAN, 2.f)), 0, "fdim float, fdim(nan,2)");

	CASE_CHECK_BALLPARK(fdim(5., 2.), 3., 0.001, "fdim double, fdim(5,2)");
	CASE_CHECK_BALLPARK(fdim(7., 1.), 6., 0.001, "fdim double, fdim(7,1)");
	CASE_CHECK_BALLPARK(fdim(5., 5.), 0., 0.001, "fdim double, fdim(5,5)");
	CASE_CHECK_BALLPARK(fdim(2., 5.), 0., 0.001, "fdim double, fdim(2,5)");
	CASE_CHECK_NE(isnan(fdim(5., NAN)), 0, "fdim double, fdim(5,nan)");
	CASE_CHECK_NE(isnan(fdim(NAN, 2.)), 0, "fdim double, fdim(nan,2)");

	CASE_CHECK_BALLPARK(fdiml(5.l, 2.l), 3.l, 0.001l, "fdim long double, fdim(5,2)");
	CASE_CHECK_BALLPARK(fdiml(7.l, 1.l), 6.l, 0.001l, "fdim long double, fdim(7,1)");
	CASE_CHECK_BALLPARK(fdiml(5.l, 5.l), 0.l, 0.001l, "fdim long double, fdim(5,5)");
	CASE_CHECK_BALLPARK(fdiml(2.l, 5.l), 0.l, 0.001l, "fdim long double, fdim(2,5)");
	CASE_CHECK_NE(isnan(fdiml(5.l, NAN)), 0, "fdim long double, fdim(5,nan)");
	CASE_CHECK_NE(isnan(fdiml(NAN, 2.l)), 0, "fdim long double, fdim(nan,2)");
}

void test_fma()
{
	CASE_CHECK_EQ(fmaf(7.f, 8.f, 11.f), (7.f * 8.f) + 11.f, "fma float, 7*8+11");
	CASE_CHECK_EQ(fmaf(7.f, 0.f, 11.f), (7.f * 0.f) + 11.f, "fma float, 7*0+11");
	CASE_CHECK_EQ(fmaf(0.f, 8.f, 11.f), (0.f * 8.f) + 11.f, "fma float, 0*8+11");
	CASE_CHECK_EQ(fmaf(7.f, 8.f, 0.f), (7.f * 8.f) + 0.f, "fma float, 7*8+0");
	CASE_CHECK_NE(isnan(fmaf(7.f, 8.f, NAN)), 0, "fma float, 7*8+nan");

	CASE_CHECK_EQ(fma(7., 8., 11.), (7. * 8.) + 11., "fma double, 7*8+11");
	CASE_CHECK_EQ(fma(7., 0., 11.), (7. * 0.) + 11., "fma double, 7*0+11");
	CASE_CHECK_EQ(fma(0., 8., 11.), (0. * 8.) + 11., "fma double, 0*8+11");
	CASE_CHECK_EQ(fma(7., 8., 0.), (7. * 8.) + 0., "fma double, 7*8+0");
	CASE_CHECK_NE(isnan(fmaf(7., 8., NAN)), 0, "fma double, 7*8+nan");

	CASE_CHECK_EQ(fmal(7.l, 8.l, 11.l), (7.l * 8.l) + 11.l, "fma long double, 7*8+11");
	CASE_CHECK_EQ(fmal(7.l, 0.l, 11.l), (7.l * 0.l) + 11.l, "fma long double, 7*0+11");
	CASE_CHECK_EQ(fmal(0.l, 8.l, 11.l), (0.l * 8.l) + 11.l, "fma long double, 0*8+11");
	CASE_CHECK_EQ(fmal(7.l, 8.l, 0.l), (7.l * 8.l) + 0.l, "fma long double, 7*8+0");
	CASE_CHECK_NE(isnan(fmaf(7.l, 8.l, NAN)), 0, "fma long double, 7*8+nan");

}

void test_hypot()
{
	CASE_CHECK_BALLPARK(hypotf(1.f, 1.f), M_SQRT2, 0.001f, "hypot float, sqrt(1^2 + 1^2)");
	CASE_CHECK_BALLPARK(hypotf(2.f, 2.f), M_SQRT2*2.f, 0.001f, "hypot float, sqrt(2^2 + 2^2)");
	CASE_CHECK_EQ(hypotf(NAN, HUGE_VALF), HUGE_VALF, "hypot float, sqrt(NAN^2 + inf^2)");

	CASE_CHECK_BALLPARK(hypot(1., 1.), M_SQRT2, 0.001, "hypot double, sqrt(1^2 + 1^2)");
	CASE_CHECK_BALLPARK(hypot(2., 2.), M_SQRT2*2., 0.001, "hypot double, sqrt(2^2 + 2^2)");
	CASE_CHECK_EQ(hypot(NAN, HUGE_VAL), HUGE_VAL, "hypot double, sqrt(NAN^2 + inf^2)");

	CASE_CHECK_BALLPARK(hypotl(1.l, 1.l), M_SQRT2, 0.001l, "hypot long double, sqrt(1^2 + 1^2)");
	CASE_CHECK_BALLPARK(hypotl(2.l, 2.l), M_SQRT2*2.l, 0.001l, "hypot long double, sqrt(2^2 + 2^2)");
	CASE_CHECK_EQ(hypotl(NAN, HUGE_VALL), HUGE_VALL, "hypot long double, sqrt(NAN^2 + inf^2)");
}

void test_erf()
{
	CASE_CHECK_BALLPARK(erff(0.02f), 0.022564575f, 0.001f, "erf float, 0.02");
	CASE_CHECK_BALLPARK(erff(0.04f), 0.045111106f, 0.001f, "erf float, 0.04");
	CASE_CHECK_BALLPARK(erff(0.06f), 0.067621594f, 0.001f, "erf float, 0.06");
	CASE_CHECK_BALLPARK(erff(0.08f), 0.090078126f, 0.001f, "erf float, 0.08");
	CASE_CHECK_BALLPARK(erff(0.1f), 0.112462916f, 0.001f, "erf float, 0.1");
	CASE_CHECK_BALLPARK(erff(0.2f), 0.222702589f, 0.001f, "erf float, 0.2");
	CASE_CHECK_BALLPARK(erff(0.3f), 0.328626759f, 0.001f, "erf float, 0.3");
	CASE_CHECK_BALLPARK(erff(0.4f), 0.428392355f, 0.001f, "erf float, 0.4");
	CASE_CHECK_BALLPARK(erff(0.5f), 0.520499878f, 0.001f, "erf float, 0.5");
	CASE_CHECK_BALLPARK(erff(0.6f), 0.603856091f, 0.001f, "erf float, 0.6");
	CASE_CHECK_BALLPARK(erff(0.7f), 0.677801194f, 0.001f, "erf float, 0.7");
	CASE_CHECK_BALLPARK(erff(0.8f), 0.742100965f, 0.001f, "erf float, 0.8");
	CASE_CHECK_BALLPARK(erff(0.9f), 0.796908212f, 0.001f, "erf float, 0.9");
	CASE_CHECK_BALLPARK(erff(1.0f), 0.842700793f, 0.001f, "erf float, 1.0");
	CASE_CHECK_BALLPARK(erff(1.1f), 0.880205070f, 0.001f, "erf float, 1.1");
	CASE_CHECK_BALLPARK(erff(1.2f), 0.910313978f, 0.001f, "erf float, 1.2");
	CASE_CHECK_BALLPARK(erff(1.3f), 0.934007945f, 0.001f, "erf float, 1.3");
	CASE_CHECK_BALLPARK(erff(1.4f), 0.952285120f, 0.001f, "erf float, 1.4");
	CASE_CHECK_BALLPARK(erff(1.5f), 0.966105146f, 0.001f, "erf float, 1.5");
	CASE_CHECK_BALLPARK(erff(1.6f), 0.976348383f, 0.001f, "erf float, 1.6");
	CASE_CHECK_BALLPARK(erff(1.7f), 0.983790459f, 0.001f, "erf float, 1.7");
	CASE_CHECK_BALLPARK(erff(1.8f), 0.989090502f, 0.001f, "erf float, 1.8");
	CASE_CHECK_BALLPARK(erff(1.9f), 0.992790429f, 0.001f, "erf float, 1.9");
	CASE_CHECK_BALLPARK(erff(2.0f), 0.995322265f, 0.001f, "erf float, 2.0");
	CASE_CHECK_BALLPARK(erff(2.1f), 0.997020533f, 0.001f, "erf float, 2.1");
	CASE_CHECK_BALLPARK(erff(2.2f), 0.998137154f, 0.001f, "erf float, 2.2");
	CASE_CHECK_BALLPARK(erff(2.3f), 0.998856823f, 0.001f, "erf float, 2.3");
	CASE_CHECK_BALLPARK(erff(2.4f), 0.999311486f, 0.001f, "erf float, 2.4");
	CASE_CHECK_BALLPARK(erff(2.5f), 0.999593048f, 0.001f, "erf float, 2.5");
	CASE_CHECK_BALLPARK(erff(3.0f), 0.999977910f, 0.001f, "erf float, 3.0");
	CASE_CHECK_BALLPARK(erff(3.5f), 0.999999257f, 0.001f, "erf float, 3.5");
	CASE_CHECK_EQ(erff(0.f), 0.f, "erf float, 0");
	CASE_CHECK_EQ(erff(-0.f), -0.f, "erf float, -0");
	CASE_CHECK_EQ(erff(INFINITY), 1.f, "erf float, inf");
	CASE_CHECK_EQ(erff(-INFINITY), -1.f, "erf float, -inf");
	CASE_CHECK_NE(isnan(erff(NAN)), 0, "erf float, nan");

	CASE_CHECK_BALLPARK(erf(0.02), 0.022564575, 0.001, "erf double, 0.02");
	CASE_CHECK_BALLPARK(erf(0.04), 0.045111106, 0.001, "erf double, 0.04");
	CASE_CHECK_BALLPARK(erf(0.06), 0.067621594, 0.001, "erf double, 0.06");
	CASE_CHECK_BALLPARK(erf(0.08), 0.090078126, 0.001, "erf double, 0.08");
	CASE_CHECK_BALLPARK(erf(0.1), 0.112462916, 0.001, "erf double, 0.1");
	CASE_CHECK_BALLPARK(erf(0.2), 0.222702589, 0.001, "erf double, 0.2");
	CASE_CHECK_BALLPARK(erf(0.3), 0.328626759, 0.001, "erf double, 0.3");
	CASE_CHECK_BALLPARK(erf(0.4), 0.428392355, 0.001, "erf double, 0.4");
	CASE_CHECK_BALLPARK(erf(0.5), 0.520499878, 0.001, "erf double, 0.5");
	CASE_CHECK_BALLPARK(erf(0.6), 0.603856091, 0.001, "erf double, 0.6");
	CASE_CHECK_BALLPARK(erf(0.7), 0.677801194, 0.001, "erf double, 0.7");
	CASE_CHECK_BALLPARK(erf(0.8), 0.742100965, 0.001, "erf double, 0.8");
	CASE_CHECK_BALLPARK(erf(0.9), 0.796908212, 0.001, "erf double, 0.9");
	CASE_CHECK_BALLPARK(erf(1.0), 0.842700793, 0.001, "erf double, 1.0");
	CASE_CHECK_BALLPARK(erf(1.1), 0.880205070, 0.001, "erf double, 1.1");
	CASE_CHECK_BALLPARK(erf(1.2), 0.910313978, 0.001, "erf double, 1.2");
	CASE_CHECK_BALLPARK(erf(1.3), 0.934007945, 0.001, "erf double, 1.3");
	CASE_CHECK_BALLPARK(erf(1.4), 0.952285120, 0.001, "erf double, 1.4");
	CASE_CHECK_BALLPARK(erf(1.5), 0.966105146, 0.001, "erf double, 1.5");
	CASE_CHECK_BALLPARK(erf(1.6), 0.976348383, 0.001, "erf double, 1.6");
	CASE_CHECK_BALLPARK(erf(1.7), 0.983790459, 0.001, "erf double, 1.7");
	CASE_CHECK_BALLPARK(erf(1.8), 0.989090502, 0.001, "erf double, 1.8");
	CASE_CHECK_BALLPARK(erf(1.9), 0.992790429, 0.001, "erf double, 1.9");
	CASE_CHECK_BALLPARK(erf(2.0), 0.995322265, 0.001, "erf double, 2.0");
	CASE_CHECK_BALLPARK(erf(2.1), 0.997020533, 0.001, "erf double, 2.1");
	CASE_CHECK_BALLPARK(erf(2.2), 0.998137154, 0.001, "erf double, 2.2");
	CASE_CHECK_BALLPARK(erf(2.3), 0.998856823, 0.001, "erf double, 2.3");
	CASE_CHECK_BALLPARK(erf(2.4), 0.999311486, 0.001, "erf double, 2.4");
	CASE_CHECK_BALLPARK(erf(2.5), 0.999593048, 0.001, "erf double, 2.5");
	CASE_CHECK_BALLPARK(erf(3.0), 0.999977910, 0.001, "erf double, 3.0");
	CASE_CHECK_BALLPARK(erf(3.5), 0.999999257, 0.001, "erf double, 3.5");
	CASE_CHECK_EQ(erf(0.), 0., "erf double, 0");
	CASE_CHECK_EQ(erf(-0.), -0., "erf double, -0");
	CASE_CHECK_EQ(erf(INFINITY), 1., "erf double, inf");
	CASE_CHECK_EQ(erf(-INFINITY), -1., "erf double, -inf");
	CASE_CHECK_NE(isnan(erf(NAN)), 0, "erf double, nan");

	CASE_CHECK_BALLPARK(erfl(0.02l), 0.022564575l, 0.001l, "erf long double, 0.02");
	CASE_CHECK_BALLPARK(erfl(0.04l), 0.045111106l, 0.001l, "erf long double, 0.04");
	CASE_CHECK_BALLPARK(erfl(0.06l), 0.067621594l, 0.001l, "erf long double, 0.06");
	CASE_CHECK_BALLPARK(erfl(0.08l), 0.090078126l, 0.001l, "erf long double, 0.08");
	CASE_CHECK_BALLPARK(erfl(0.1l), 0.112462916l, 0.001l, "erf long double, 0.1");
	CASE_CHECK_BALLPARK(erfl(0.2l), 0.222702589l, 0.001l, "erf long double, 0.2");
	CASE_CHECK_BALLPARK(erfl(0.3l), 0.328626759l, 0.001l, "erf long double, 0.3");
	CASE_CHECK_BALLPARK(erfl(0.4l), 0.428392355l, 0.001l, "erf long double, 0.4");
	CASE_CHECK_BALLPARK(erfl(0.5l), 0.520499878l, 0.001l, "erf long double, 0.5");
	CASE_CHECK_BALLPARK(erfl(0.6l), 0.603856091l, 0.001l, "erf long double, 0.6");
	CASE_CHECK_BALLPARK(erfl(0.7l), 0.677801194l, 0.001l, "erf long double, 0.7");
	CASE_CHECK_BALLPARK(erfl(0.8l), 0.742100965l, 0.001l, "erf long double, 0.8");
	CASE_CHECK_BALLPARK(erfl(0.9l), 0.796908212l, 0.001l, "erf long double, 0.9");
	CASE_CHECK_BALLPARK(erfl(1.0l), 0.842700793l, 0.001l, "erf long double, 1.0");
	CASE_CHECK_BALLPARK(erfl(1.1l), 0.880205070l, 0.001l, "erf long double, 1.1");
	CASE_CHECK_BALLPARK(erfl(1.2l), 0.910313978l, 0.001l, "erf long double, 1.2");
	CASE_CHECK_BALLPARK(erfl(1.3l), 0.934007945l, 0.001l, "erf long double, 1.3");
	CASE_CHECK_BALLPARK(erfl(1.4l), 0.952285120l, 0.001l, "erf long double, 1.4");
	CASE_CHECK_BALLPARK(erfl(1.5l), 0.966105146l, 0.001l, "erf long double, 1.5");
	CASE_CHECK_BALLPARK(erfl(1.6l), 0.976348383l, 0.001l, "erf long double, 1.6");
	CASE_CHECK_BALLPARK(erfl(1.7l), 0.983790459l, 0.001l, "erf long double, 1.7");
	CASE_CHECK_BALLPARK(erfl(1.8l), 0.989090502l, 0.001l, "erf long double, 1.8");
	CASE_CHECK_BALLPARK(erfl(1.9l), 0.992790429l, 0.001l, "erf long double, 1.9");
	CASE_CHECK_BALLPARK(erfl(2.0l), 0.995322265l, 0.001l, "erf long double, 2.0");
	CASE_CHECK_BALLPARK(erfl(2.1l), 0.997020533l, 0.001l, "erf long double, 2.1");
	CASE_CHECK_BALLPARK(erfl(2.2l), 0.998137154l, 0.001l, "erf long double, 2.2");
	CASE_CHECK_BALLPARK(erfl(2.3l), 0.998856823l, 0.001l, "erf long double, 2.3");
	CASE_CHECK_BALLPARK(erfl(2.4l), 0.999311486l, 0.001l, "erf long double, 2.4");
	CASE_CHECK_BALLPARK(erfl(2.5l), 0.999593048l, 0.001l, "erf long double, 2.5");
	CASE_CHECK_BALLPARK(erfl(3.0l), 0.999977910l, 0.001l, "erf long double, 3.0");
	CASE_CHECK_BALLPARK(erfl(3.5l), 0.999999257l, 0.001l, "erf long double, 3.5");
	CASE_CHECK_EQ(erfl(0.l), 0.l, "erf long double, 0");
	CASE_CHECK_EQ(erfl(-0.l), -0.l, "erf long double, -0");
	CASE_CHECK_EQ(erfl(INFINITY), 1.l, "erf long double, inf");
	CASE_CHECK_EQ(erfl(-INFINITY), -1.l, "erf long double, -inf");
	CASE_CHECK_NE(isnan(erfl(NAN)), 0, "erf long double, nan");



	CASE_CHECK_BALLPARK(erfcf(0.02f), 1.f - 0.022564575f, 0.001f, "erfc float, 0.02");
	CASE_CHECK_BALLPARK(erfcf(0.04f), 1.f - 0.045111106f, 0.001f, "erfc float, 0.04");
	CASE_CHECK_BALLPARK(erfcf(0.06f), 1.f - 0.067621594f, 0.001f, "erfc float, 0.06");
	CASE_CHECK_BALLPARK(erfcf(0.08f), 1.f - 0.090078126f, 0.001f, "erfc float, 0.08");
	CASE_CHECK_BALLPARK(erfcf(0.1f), 1.f - 0.112462916f, 0.001f, "erfc float, 0.1");
	CASE_CHECK_BALLPARK(erfcf(0.2f), 1.f - 0.222702589f, 0.001f, "erfc float, 0.2");
	CASE_CHECK_BALLPARK(erfcf(0.3f), 1.f - 0.328626759f, 0.001f, "erfc float, 0.3");
	CASE_CHECK_BALLPARK(erfcf(0.4f), 1.f - 0.428392355f, 0.001f, "erfc float, 0.4");
	CASE_CHECK_BALLPARK(erfcf(0.5f), 1.f - 0.520499878f, 0.001f, "erfc float, 0.5");
	CASE_CHECK_BALLPARK(erfcf(0.6f), 1.f - 0.603856091f, 0.001f, "erfc float, 0.6");
	CASE_CHECK_BALLPARK(erfcf(0.7f), 1.f - 0.677801194f, 0.001f, "erfc float, 0.7");
	CASE_CHECK_BALLPARK(erfcf(0.8f), 1.f - 0.742100965f, 0.001f, "erfc float, 0.8");
	CASE_CHECK_BALLPARK(erfcf(0.9f), 1.f - 0.796908212f, 0.001f, "erfc float, 0.9");
	CASE_CHECK_BALLPARK(erfcf(1.0f), 1.f - 0.842700793f, 0.001f, "erfc float, 1.0");
	CASE_CHECK_BALLPARK(erfcf(1.1f), 1.f - 0.880205070f, 0.001f, "erfc float, 1.1");
	CASE_CHECK_BALLPARK(erfcf(1.2f), 1.f - 0.910313978f, 0.001f, "erfc float, 1.2");
	CASE_CHECK_BALLPARK(erfcf(1.3f), 1.f - 0.934007945f, 0.001f, "erfc float, 1.3");
	CASE_CHECK_BALLPARK(erfcf(1.4f), 1.f - 0.952285120f, 0.001f, "erfc float, 1.4");
	CASE_CHECK_BALLPARK(erfcf(1.5f), 1.f - 0.966105146f, 0.001f, "erfc float, 1.5");
	CASE_CHECK_BALLPARK(erfcf(1.6f), 1.f - 0.976348383f, 0.001f, "erfc float, 1.6");
	CASE_CHECK_BALLPARK(erfcf(1.7f), 1.f - 0.983790459f, 0.001f, "erfc float, 1.7");
	CASE_CHECK_BALLPARK(erfcf(1.8f), 1.f - 0.989090502f, 0.001f, "erfc float, 1.8");
	CASE_CHECK_BALLPARK(erfcf(1.9f), 1.f - 0.992790429f, 0.001f, "erfc float, 1.9");
	CASE_CHECK_BALLPARK(erfcf(2.0f), 1.f - 0.995322265f, 0.001f, "erfc float, 2.0");
	CASE_CHECK_BALLPARK(erfcf(2.1f), 1.f - 0.997020533f, 0.001f, "erfc float, 2.1");
	CASE_CHECK_BALLPARK(erfcf(2.2f), 1.f - 0.998137154f, 0.001f, "erfc float, 2.2");
	CASE_CHECK_BALLPARK(erfcf(2.3f), 1.f - 0.998856823f, 0.001f, "erfc float, 2.3");
	CASE_CHECK_BALLPARK(erfcf(2.4f), 1.f - 0.999311486f, 0.001f, "erfc float, 2.4");
	CASE_CHECK_BALLPARK(erfcf(2.5f), 1.f - 0.999593048f, 0.001f, "erfc float, 2.5");
	CASE_CHECK_BALLPARK(erfcf(3.0f), 1.f - 0.999977910f, 0.001f, "erfc float, 3.0");
	CASE_CHECK_BALLPARK(erfcf(3.5f), 1.f - 0.999999257f, 0.001f, "erfc float, 3.5");
	CASE_CHECK_EQ(erfcf(0.f), 1.f, "erfc float, 0");
	CASE_CHECK_EQ(erfcf(-0.f), 1.f, "erfc float, -0");
	CASE_CHECK_EQ(erfcf(INFINITY), 0.f, "erfc float, inf");
	CASE_CHECK_EQ(erfcf(-INFINITY), 2.f, "erfc float, -inf");
	CASE_CHECK_NE(isnan(erfcf(NAN)), 0, "erfc float, nan");

	CASE_CHECK_BALLPARK(erfc(0.02), 1. - 0.022564575, 0.001, "erfc double, 0.02");
	CASE_CHECK_BALLPARK(erfc(0.04), 1. - 0.045111106, 0.001, "erfc double, 0.04");
	CASE_CHECK_BALLPARK(erfc(0.06), 1. - 0.067621594, 0.001, "erfc double, 0.06");
	CASE_CHECK_BALLPARK(erfc(0.08), 1. - 0.090078126, 0.001, "erfc double, 0.08");
	CASE_CHECK_BALLPARK(erfc(0.1), 1. - 0.112462916, 0.001, "erfc double, 0.1");
	CASE_CHECK_BALLPARK(erfc(0.2), 1. - 0.222702589, 0.001, "erfc double, 0.2");
	CASE_CHECK_BALLPARK(erfc(0.3), 1. - 0.328626759, 0.001, "erfc double, 0.3");
	CASE_CHECK_BALLPARK(erfc(0.4), 1. - 0.428392355, 0.001, "erfc double, 0.4");
	CASE_CHECK_BALLPARK(erfc(0.5), 1. - 0.520499878, 0.001, "erfc double, 0.5");
	CASE_CHECK_BALLPARK(erfc(0.6), 1. - 0.603856091, 0.001, "erfc double, 0.6");
	CASE_CHECK_BALLPARK(erfc(0.7), 1. - 0.677801194, 0.001, "erfc double, 0.7");
	CASE_CHECK_BALLPARK(erfc(0.8), 1. - 0.742100965, 0.001, "erfc double, 0.8");
	CASE_CHECK_BALLPARK(erfc(0.9), 1. - 0.796908212, 0.001, "erfc double, 0.9");
	CASE_CHECK_BALLPARK(erfc(1.0), 1. - 0.842700793, 0.001, "erfc double, 1.0");
	CASE_CHECK_BALLPARK(erfc(1.1), 1. - 0.880205070, 0.001, "erfc double, 1.1");
	CASE_CHECK_BALLPARK(erfc(1.2), 1. - 0.910313978, 0.001, "erfc double, 1.2");
	CASE_CHECK_BALLPARK(erfc(1.3), 1. - 0.934007945, 0.001, "erfc double, 1.3");
	CASE_CHECK_BALLPARK(erfc(1.4), 1. - 0.952285120, 0.001, "erfc double, 1.4");
	CASE_CHECK_BALLPARK(erfc(1.5), 1. - 0.966105146, 0.001, "erfc double, 1.5");
	CASE_CHECK_BALLPARK(erfc(1.6), 1. - 0.976348383, 0.001, "erfc double, 1.6");
	CASE_CHECK_BALLPARK(erfc(1.7), 1. - 0.983790459, 0.001, "erfc double, 1.7");
	CASE_CHECK_BALLPARK(erfc(1.8), 1. - 0.989090502, 0.001, "erfc double, 1.8");
	CASE_CHECK_BALLPARK(erfc(1.9), 1. - 0.992790429, 0.001, "erfc double, 1.9");
	CASE_CHECK_BALLPARK(erfc(2.0), 1. - 0.995322265, 0.001, "erfc double, 2.0");
	CASE_CHECK_BALLPARK(erfc(2.1), 1. - 0.997020533, 0.001, "erfc double, 2.1");
	CASE_CHECK_BALLPARK(erfc(2.2), 1. - 0.998137154, 0.001, "erfc double, 2.2");
	CASE_CHECK_BALLPARK(erfc(2.3), 1. - 0.998856823, 0.001, "erfc double, 2.3");
	CASE_CHECK_BALLPARK(erfc(2.4), 1. - 0.999311486, 0.001, "erfc double, 2.4");
	CASE_CHECK_BALLPARK(erfc(2.5), 1. - 0.999593048, 0.001, "erfc double, 2.5");
	CASE_CHECK_BALLPARK(erfc(3.0), 1. - 0.999977910, 0.001, "erfc double, 3.0");
	CASE_CHECK_BALLPARK(erfc(3.5), 1. - 0.999999257, 0.001, "erfc double, 3.5");
	CASE_CHECK_EQ(erfc(0.), 1., "erfc double, 0");
	CASE_CHECK_EQ(erfc(-0.), 1., "erfc double, -0");
	CASE_CHECK_EQ(erfc(INFINITY), 0., "erfc double, inf");
	CASE_CHECK_EQ(erfc(-INFINITY), 2., "erfc double, -inf");
	CASE_CHECK_NE(isnan(erfc(NAN)), 0., "erfc double, nan");

	CASE_CHECK_BALLPARK(erfcl(0.02l), 1.l - 0.022564575l, 0.001l, "erfc long double, 0.02");
	CASE_CHECK_BALLPARK(erfcl(0.04l), 1.l - 0.045111106l, 0.001l, "erfc long double, 0.04");
	CASE_CHECK_BALLPARK(erfcl(0.06l), 1.l - 0.067621594l, 0.001l, "erfc long double, 0.06");
	CASE_CHECK_BALLPARK(erfcl(0.08l), 1.l - 0.090078126l, 0.001l, "erfc long double, 0.08");
	CASE_CHECK_BALLPARK(erfcl(0.1l), 1.l - 0.112462916l, 0.001l, "erfc long double, 0.1");
	CASE_CHECK_BALLPARK(erfcl(0.2l), 1.l - 0.222702589l, 0.001l, "erfc long double, 0.2");
	CASE_CHECK_BALLPARK(erfcl(0.3l), 1.l - 0.328626759l, 0.001l, "erfc long double, 0.3");
	CASE_CHECK_BALLPARK(erfcl(0.4l), 1.l - 0.428392355l, 0.001l, "erfc long double, 0.4");
	CASE_CHECK_BALLPARK(erfcl(0.5l), 1.l - 0.520499878l, 0.001l, "erfc long double, 0.5");
	CASE_CHECK_BALLPARK(erfcl(0.6l), 1.l - 0.603856091l, 0.001l, "erfc long double, 0.6");
	CASE_CHECK_BALLPARK(erfcl(0.7l), 1.l - 0.677801194l, 0.001l, "erfc long double, 0.7");
	CASE_CHECK_BALLPARK(erfcl(0.8l), 1.l - 0.742100965l, 0.001l, "erfc long double, 0.8");
	CASE_CHECK_BALLPARK(erfcl(0.9l), 1.l - 0.796908212l, 0.001l, "erfc long double, 0.9");
	CASE_CHECK_BALLPARK(erfcl(1.0l), 1.l - 0.842700793l, 0.001l, "erfc long double, 1.0");
	CASE_CHECK_BALLPARK(erfcl(1.1l), 1.l - 0.880205070l, 0.001l, "erfc long double, 1.1");
	CASE_CHECK_BALLPARK(erfcl(1.2l), 1.l - 0.910313978l, 0.001l, "erfc long double, 1.2");
	CASE_CHECK_BALLPARK(erfcl(1.3l), 1.l - 0.934007945l, 0.001l, "erfc long double, 1.3");
	CASE_CHECK_BALLPARK(erfcl(1.4l), 1.l - 0.952285120l, 0.001l, "erfc long double, 1.4");
	CASE_CHECK_BALLPARK(erfcl(1.5l), 1.l - 0.966105146l, 0.001l, "erfc long double, 1.5");
	CASE_CHECK_BALLPARK(erfcl(1.6l), 1.l - 0.976348383l, 0.001l, "erfc long double, 1.6");
	CASE_CHECK_BALLPARK(erfcl(1.7l), 1.l - 0.983790459l, 0.001l, "erfc long double, 1.7");
	CASE_CHECK_BALLPARK(erfcl(1.8l), 1.l - 0.989090502l, 0.001l, "erfc long double, 1.8");
	CASE_CHECK_BALLPARK(erfcl(1.9l), 1.l - 0.992790429l, 0.001l, "erfc long double, 1.9");
	CASE_CHECK_BALLPARK(erfcl(2.0l), 1.l - 0.995322265l, 0.001l, "erfc long double, 2.0");
	CASE_CHECK_BALLPARK(erfcl(2.1l), 1.l - 0.997020533l, 0.001l, "erfc long double, 2.1");
	CASE_CHECK_BALLPARK(erfcl(2.2l), 1.l - 0.998137154l, 0.001l, "erfc long double, 2.2");
	CASE_CHECK_BALLPARK(erfcl(2.3l), 1.l - 0.998856823l, 0.001l, "erfc long double, 2.3");
	CASE_CHECK_BALLPARK(erfcl(2.4l), 1.l - 0.999311486l, 0.001l, "erfc long double, 2.4");
	CASE_CHECK_BALLPARK(erfcl(2.5l), 1.l - 0.999593048l, 0.001l, "erfc long double, 2.5");
	CASE_CHECK_BALLPARK(erfcl(3.0l), 1.l - 0.999977910l, 0.001l, "erfc long double, 3.0");
	CASE_CHECK_BALLPARK(erfcl(3.5l), 1.l - 0.999999257l, 0.001l, "erfc long double, 3.5");
	CASE_CHECK_EQ(erfcl(0.l), 1.l, "erfc long double, 0");
	CASE_CHECK_EQ(erfcl(-0.l), 1.l, "erfc long double, -0");
	CASE_CHECK_EQ(erfcl(INFINITY), 0.l, "erfc long double, inf");
	CASE_CHECK_EQ(erfcl(-INFINITY), 2.l, "erfc long double, -inf");
	CASE_CHECK_NE(isnan(erfcl(NAN)), 0, "erfc long double, nan");
}

void test_tgamma()
{
	CASE_CHECK_NE(isnan(tgammaf(NAN)), 0, "tgamma float, nan");
	CASE_CHECK_EQ(tgammaf(INFINITY), INFINITY, "tgamma float, inf");
	CASE_CHECK_NE(isnan(tgammaf(-INFINITY)), 0, "tgamma float, -inf");
	CASE_CHECK_NE(isnan(tgammaf(-1.f)), 0, "tgamma float, negative");
	CASE_CHECK_EQ(tgammaf(+0.f), INFINITY, "tgamma float, +0");
	CASE_CHECK_EQ(tgammaf(-0.f), -INFINITY, "tgamma float, -0");
	CASE_CHECK_BALLPARK(tgammaf(1.f), 1.f, 0.1000f, "tgamma 1");
	CASE_CHECK_BALLPARK(tgammaf(2.f), 1.f, 0.0100f, "tgamma 2");
	CASE_CHECK_BALLPARK(tgammaf(4.f), 6.f, 0.0100f, "tgamma float, 4");
	CASE_CHECK_BALLPARK(tgammaf(6.4555f), 265.852814l, 0.0001f, "tgamma float, 6.4555");

	CASE_CHECK_NE(isnan(tgamma(NAN)), 0, "tgamma double, nan");
	CASE_CHECK_EQ(tgamma(INFINITY), INFINITY, "tgamma double, inf");
	CASE_CHECK_NE(isnan(tgamma(-INFINITY)), 0, "tgamma double, -inf");
	CASE_CHECK_NE(isnan(tgamma(-1.)), 0, "tgamma double, negative");
	CASE_CHECK_EQ(tgamma(+0.), INFINITY, "tgamma double, +0");
	CASE_CHECK_EQ(tgamma(-0.), -INFINITY, "tgamma double, -0");
	CASE_CHECK_BALLPARK(tgamma(1.), 1., 0.1000, "tgamma double, 1");
	CASE_CHECK_BALLPARK(tgamma(2.), 1., 0.0100, "tgamma double, 2");
	CASE_CHECK_BALLPARK(tgamma(4.), 6., 0.0100, "tgamma double, 4");
	CASE_CHECK_BALLPARK(tgamma(6.4555), 265.852814, 0.0001, "tgamma double, 6.4555");

	CASE_CHECK_NE(isnan(tgammal(NAN)), 0, "tgamma long double, nan");
	CASE_CHECK_EQ(tgammal(INFINITY), INFINITY, "tgamma long double, inf");
	CASE_CHECK_NE(isnan(tgammal(-INFINITY)), 0, "tgamma long double, -inf");
	CASE_CHECK_NE(isnan(tgammal(-1.l)), 0, "tgamma long double, negative");
	CASE_CHECK_EQ(tgammal(+0.l), INFINITY, "tgamma long double, +0");
	CASE_CHECK_EQ(tgammal(-0.l), -INFINITY, "tgamma long double, -0");
	CASE_CHECK_BALLPARK(tgammal(1.l), 1.l, 0.1000l, "tgamma long double, 1");
	CASE_CHECK_BALLPARK(tgammal(2.l), 1.l, 0.0100l, "tgamma long double, 2");
	CASE_CHECK_BALLPARK(tgammal(4.l), 6.l, 0.0100l, "tgamma long double, 4");
	CASE_CHECK_BALLPARK(tgammal(6.4555l), 265.852814l, 0.0001l, "tgamma long double, 6.4555");
}

void test_lgamma()
{
	CASE_CHECK_NE(isnan(lgammaf(NAN)), 0, "lgamma float, nan");
	CASE_CHECK_EQ(lgammaf(INFINITY), INFINITY, "lgamma float, inf");
	CASE_CHECK_EQ(lgammaf(-INFINITY), INFINITY, "lgamma float, -inf");
	CASE_CHECK_EQ(lgammaf(-1.f), INFINITY, "lgamma float, negative");
	CASE_CHECK_EQ(lgammaf(+0.f), INFINITY, "lgamma float, +0");
	CASE_CHECK_EQ(lgammaf(-0.f), INFINITY, "lgamma float, -0");
	CASE_CHECK_BALLPARK(lgammaf(1.f), 0.f, 0.0001f, "lgamma float, 1");
	CASE_CHECK_BALLPARK(lgammaf(2.f), 0.f, 0.0001f, "lgamma float, 2");
	CASE_CHECK_BALLPARK(lgammaf(4.f), 1.79175949f, 0.0001f, "lgamma float, 4");
	CASE_CHECK_BALLPARK(lgammaf(30.4f), 72.613513653956673f, 0.0001f, "lgamma float, 30.4");

	CASE_CHECK_NE(isnan(lgamma(NAN)), 0, "lgamma double, nan");
	CASE_CHECK_EQ(lgamma(INFINITY), INFINITY, "lgamma double, inf");
	CASE_CHECK_EQ(lgamma(-INFINITY), INFINITY, "lgamma double, -inf");
	CASE_CHECK_EQ(lgamma(-1.), INFINITY, "lgamma double, negative");
	CASE_CHECK_EQ(lgamma(+0.), INFINITY, "lgamma double, +0");
	CASE_CHECK_EQ(lgamma(-0.), INFINITY, "lgamma double, -0");
	CASE_CHECK_BALLPARK(lgamma(1.), 0., 0.0001, "lgamma double, 1");
	CASE_CHECK_BALLPARK(lgamma(2.), 0., 0.0001, "lgamma double, 2");
	CASE_CHECK_BALLPARK(lgamma(4.), 1.79175949, 0.0001, "lgamma double, 4");
	CASE_CHECK_BALLPARK(lgamma(39.4), 104.43054380123993, 0.0001, "lgamma double, 39.4");

	CASE_CHECK_NE(isnan(lgammal(NAN)), 0, "lgamma long double, nan");
	CASE_CHECK_EQ(lgammal(INFINITY), INFINITY, "lgamma long double, inf");
	CASE_CHECK_EQ(lgammal(-INFINITY), INFINITY, "lgamma long double, -inf");
	CASE_CHECK_EQ(lgammal(-1.l), INFINITY, "lgamma long double, negative");
	CASE_CHECK_EQ(lgammal(+0.l), INFINITY, "lgamma long double, +0");
	CASE_CHECK_EQ(lgammal(-0.l), INFINITY, "lgamma long double, -0");
	CASE_CHECK_BALLPARK(lgammal(1.l), 0.l, 0.0001l, "lgamma long double, 1");
	CASE_CHECK_BALLPARK(lgammal(2.l), 0.l, 0.0001l, "lgamma long double, 2");
	CASE_CHECK_BALLPARK(lgammal(4.l), 1.79175949l, 0.0001l, "lgamma long double, 4");
	CASE_CHECK_BALLPARK(lgammal(39.4l), 104.43054380123993l, 0.0001l, "lgamma long double, 39.4");
}

void test_nan()
{
	float fnan1234 = nanf("NAN(1234)");
	double dblnan1234 = nan("NAN(1234)");
	long double ldblnan1234 = nanl("NAN(1234)");

	uint32_t u32nan1234 = *(uint32_t*)&fnan1234;
	uint64_t u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x7F8004D2, "nan float, NAN(1234)");
	CASE_CHECK_EQ(u64nan1234, 0x7FF00000000004D2llu, "nan double, NAN(1234)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x00000000000004D2llu, "nan long double u64, NAN(1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x7FFFllu, "nan long double u16, NAN(1234)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x7FF00000000004D2llu, "nan long double, NAN(1234)");
	}

	fnan1234 = nanf("NAN(0x1234)");
	dblnan1234 = nan("NAN(0x1234)");
	ldblnan1234 = nanl("NAN(0x1234)");
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x7F801234, "nan float, NAN(0x1234)");
	CASE_CHECK_EQ(u64nan1234, 0x7FF0000000001234llu, "nan double, NAN(0x1234)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000001234llu, "nan long double u64, NAN(0x1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x7FFFllu, "nan long double u16, NAN(0x1234)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x7FF0000000001234llu, "nan long double, NAN(0x1234)");
	}

	fnan1234 = nanf("NAN(0x7FFFFF)");
	dblnan1234 = nan("NAN(0xFFFFFFFFFFFFF)");
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x7FFFFFFF, "nan float, NAN(0x7FFFFF)");
	CASE_CHECK_EQ(u64nan1234, 0x7FFFFFFFFFFFFFFFllu, "nan double, NAN(0xFFFFFFFFFFFFF)");
	if constexpr (sizeof(long double) == 10)
	{
		ldblnan1234 = nanl("NAN(0x7FFFFFFFFFFFFFFF)");
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x7FFFFFFFFFFFFFFFllu, "nan long double u64, NAN(0x1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x7FFFllu, "nan long double u16, NAN(0x1234)");
	}
	else
	{
		ldblnan1234 = nanl("NAN(0xFFFFFFFFFFFFF)");
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x7FFFFFFFFFFFFFFFllu, "nan long double, NAN(0xFFFFFFFFFFFFF)");
	}

	fnan1234 = nanf("-NAN(1234)");
	dblnan1234 = nan("-NAN(1234)");
	ldblnan1234 = nanl("-NAN(1234)");

	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0xFF8004D2, "nan float, -NAN(1234)");
	CASE_CHECK_EQ(u64nan1234, 0xFFF00000000004D2llu, "nan double, -NAN(1234)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x00000000000004D2llu, "nan long double u64, -NAN(1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0xFFFFllu, "nan long double u16, -NAN(1234)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0xFFF00000000004D2llu, "nan long double, NAN(1234)");
	}

	fnan1234 = nanf("-NAN(0x1234)");
	dblnan1234 = nan("-NAN(0x1234)");
	ldblnan1234 = nanl("-NAN(0x1234)");
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0xFF801234, "nan float, -NAN(0x1234)");
	CASE_CHECK_EQ(u64nan1234, 0xFFF0000000001234llu, "nan double, -NAN(0x1234)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000001234llu, "nan long double u64, -NAN(0x1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0xFFFFllu, "nan long double u16, -NAN(0x1234)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0xFFF0000000001234llu, "nan long double, NAN(0x1234)");
	}

	fnan1234 = nanf("-NAN(0x7FFFFF)");
	dblnan1234 = nan("-NAN(0xFFFFFFFFFFFFF)");
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0xFFFFFFFF, "nan float, NAN(0x7FFFFF)");
	CASE_CHECK_EQ(u64nan1234, 0xFFFFFFFFFFFFFFFFllu, "nan double, NAN(0xFFFFFFFFFFFFF)");
	if constexpr (sizeof(long double) == 10)
	{
		ldblnan1234 = nanl("-NAN(0x7FFFFFFFFFFFFFFF)");
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x7FFFFFFFFFFFFFFFllu, "nan long double u64, NAN(0x1234)");
		CASE_CHECK_EQ(u80nan1234_p2, 0xFFFFllu, "nan long double u16, NAN(0x1234)");
	}
	else
	{
		ldblnan1234 = nanl("-NAN(0xFFFFFFFFFFFFF)");
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0xFFFFFFFFFFFFFFFFllu, "nan long double, NAN(0xFFFFFFFFFFFFF)");
	}
}

void test_nextafter()
{
	float fnan1234 = nextafterf(0.f, 1.f);
	double dblnan1234 = nextafter(0., 1.);
	long double ldblnan1234 = nextafterl(0.l, 1.l);
	uint32_t u32nan1234 = *(uint32_t*)&fnan1234;
	uint64_t u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x00000001, "nextafter float, nextafter(0, 1)");
	CASE_CHECK_EQ(u64nan1234, 0x0000000000000001llu, "nextafter double, nextafter(0, 1)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nextafter long double u64, nextafter(0, 1)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x0000llu, "nextafter long double u16, nextafter(0, 1)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x0000000000000001llu, "nextafter long double, nextafter(0, 1)");
	}

	fnan1234 = nextafterf(1.f, 2.f);
	dblnan1234 = nextafter(1., 2.);
	ldblnan1234 = nextafterl(1.l, 2.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800001, "nextafter float, nextafter(1, 2)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000001llu, "nextafter double, nextafter(1, 2)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nextafter long double u64, nextafter(1, 2)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nextafter long double u16, nextafter(1, 2)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000001llu, "nextafter long double, nextafter(1, 2)");
	}

	fnan1234 = nextafterf(1.f, 1.f);
	dblnan1234 = nextafter(1., 1.);
	ldblnan1234 = nextafterl(1.l, 1.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800000, "nextafter float, nextafter(1, 1)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000000llu, "nextafter double, nextafter(1, 1)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000000llu, "nextafter long double u64, nextafter(1, 1)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nextafter long double u16, nextafter(1, 1)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000000llu, "nextafter long double, nextafter(1, 1)");
	}

	fnan1234 = nextafterf(1.f, 2.f);
	dblnan1234 = nextafter(1., 2.);
	ldblnan1234 = nextafterl(1.l, 2.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800001, "nextafter float, nextafter(1, 2)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000001llu, "nextafter double, nextafter(1, 2)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nextafter long double u64, nextafter(1, 2)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nextafter long double u16, nextafter(1, 2)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000001llu, "nextafter long double, nextafter(1, 2)");
	}

	fnan1234 = nextafterf(1.f, NAN);
	dblnan1234 = nextafter(1., NAN);
	ldblnan1234 = nextafterl(1.l, NAN);
	CASE_CHECK_NE(isnan(fnan1234), 0, "nextafter float, nextafter(1, nan)");
	CASE_CHECK_NE(isnan(dblnan1234), 0, "nextafter double, nextafter(1, nan)");
	CASE_CHECK_NE(isnan(ldblnan1234), 0, "nextafter double, nextafter(1, nan)");

	fnan1234 = nextafterf(NAN, 1.f);
	dblnan1234 = nextafter(NAN, 1.);
	ldblnan1234 = nextafterl(NAN, 1.l);
	CASE_CHECK_NE(isnan(fnan1234), 0, "nextafter float, nextafter(nan, 1)");
	CASE_CHECK_NE(isnan(dblnan1234), 0, "nextafter double, nextafter(nan, 1)");
	CASE_CHECK_NE(isnan(ldblnan1234), 0, "nextafter double, nextafter(nan, 1)");

	fnan1234 = nextafterf(1.f, INFINITY);
	dblnan1234 = nextafter(1., INFINITY);
	ldblnan1234 = nextafterl(1.l, INFINITY);
	CASE_CHECK_NE(isinf(fnan1234), 0, "nextafter float, nextafter(1, inf)");
	CASE_CHECK_NE(isinf(dblnan1234), 0, "nextafter double, nextafter(1, inf)");
	CASE_CHECK_NE(isinf(ldblnan1234), 0, "nextafter double, nextafter(1, inf)");

	fnan1234 = nextafterf(INFINITY, 1.f);
	dblnan1234 = nextafter(INFINITY, 1.);
	ldblnan1234 = nextafterl(INFINITY, 1.l);
	CASE_CHECK_NE(isinf(fnan1234), 0, "nextafter float, nextafter(inf, 1)");
	CASE_CHECK_NE(isinf(dblnan1234), 0, "nextafter double, nextafter(inf, 1)");
	CASE_CHECK_NE(isinf(ldblnan1234), 0, "nextafter double, nextafter(inf, 1)");
}

void test_nexttoward()
{
	float fnan1234 = nexttowardf(0.f, 1.f);
	double dblnan1234 = nexttoward(0., 1.);
	long double ldblnan1234 = nexttowardl(0.l, 1.l);
	uint32_t u32nan1234 = *(uint32_t*)&fnan1234;
	uint64_t u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x00000000, "nexttoward float, nexttoward(0, 1)");
	CASE_CHECK_EQ(u64nan1234, 0x0000000000000001llu, "nexttoward double, nexttoward(0, 1)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nexttoward long double u64, nexttoward(0, 1)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x0000llu, "nexttoward long double u16, nexttoward(0, 1)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x0000000000000001llu, "nexttoward long double, nexttoward(0, 1)");
	}

	fnan1234 = nexttowardf(1.f, 2.f);
	dblnan1234 = nexttoward(1., 2.);
	ldblnan1234 = nexttowardl(1.l, 2.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800000, "nexttoward float, nexttoward(1, 2)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000001llu, "nexttoward double, nexttoward(1, 2)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nexttoward long double u64, nexttoward(1, 2)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nexttoward long double u16, nexttoward(1, 2)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000001llu, "nexttoward long double, nexttoward(1, 2)");
	}

	fnan1234 = nexttowardf(1.f, 1.f);
	dblnan1234 = nexttoward(1., 1.);
	ldblnan1234 = nexttowardl(1.l, 1.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800000, "nexttoward float, nexttoward(1, 1)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000000llu, "nexttoward double, nexttoward(1, 1)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000000llu, "nexttoward long double u64, nexttoward(1, 1)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nexttoward long double u16, nexttoward(1, 1)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000000llu, "nexttoward long double, nexttoward(1, 1)");
	}

	fnan1234 = nexttowardf(1.f, 2.f);
	dblnan1234 = nexttoward(1., 2.);
	ldblnan1234 = nexttowardl(1.l, 2.l);
	u32nan1234 = *(uint32_t*)&fnan1234;
	u64nan1234 = *(uint64_t*)&dblnan1234;
	CASE_CHECK_EQ(u32nan1234, 0x3F800000, "nexttoward float, nexttoward(1, 2)");
	CASE_CHECK_EQ(u64nan1234, 0x3FF0000000000001llu, "nexttoward double, nexttoward(1, 2)");
	if constexpr (sizeof(long double) == 10)
	{
		uint64_t u80nan1234_p1 = *(uint64_t*)&ldblnan1234;
		uint16_t u80nan1234_p2 = *(((uint16_t*)&ldblnan1234) + 4);
		CASE_CHECK_EQ(u80nan1234_p1, 0x0000000000000001llu, "nexttoward long double u64, nexttoward(1, 2)");
		CASE_CHECK_EQ(u80nan1234_p2, 0x3FFFllu, "nexttoward long double u16, nexttoward(1, 2)");
	}
	else
	{
		uint64_t u80nan1234 = *(uint64_t*)&ldblnan1234;
		CASE_CHECK_EQ(u80nan1234, 0x3FF0000000000001llu, "nexttoward long double, nexttoward(1, 2)");
	}

	fnan1234 = nexttowardf(1.f, NAN);
	dblnan1234 = nexttoward(1., NAN);
	ldblnan1234 = nexttowardl(1.l, NAN);
	CASE_CHECK_NE(isnan(fnan1234), 0, "nexttoward float, nexttoward(1, nan)");
	CASE_CHECK_NE(isnan(dblnan1234), 0, "nexttoward double, nexttoward(1, nan)");
	CASE_CHECK_NE(isnan(ldblnan1234), 0, "nexttoward double, nexttoward(1, nan)");

	fnan1234 = nexttowardf(NAN, 1.f);
	dblnan1234 = nexttoward(NAN, 1.);
	ldblnan1234 = nexttowardl(NAN, 1.l);
	CASE_CHECK_NE(isnan(fnan1234), 0, "nexttoward float, nexttoward(nan, 1)");
	CASE_CHECK_NE(isnan(dblnan1234), 0, "nexttoward double, nexttoward(nan, 1)");
	CASE_CHECK_NE(isnan(ldblnan1234), 0, "nexttoward double, nexttoward(nan, 1)");

	fnan1234 = nexttowardf(1.f, INFINITY);
	dblnan1234 = nexttoward(1., INFINITY);
	ldblnan1234 = nexttowardl(1.l, INFINITY);
	CASE_CHECK_NE(isinf(fnan1234), 0, "nexttoward float, nexttoward(1, inf)");
	CASE_CHECK_NE(isinf(dblnan1234), 0, "nexttoward double, nexttoward(1, inf)");
	CASE_CHECK_NE(isinf(ldblnan1234), 0, "nexttoward double, nexttoward(1, inf)");

	fnan1234 = nexttowardf(INFINITY, 1.f);
	dblnan1234 = nexttoward(INFINITY, 1.);
	ldblnan1234 = nexttowardl(INFINITY, 1.l);
	CASE_CHECK_NE(isinf(fnan1234), 0, "nexttoward float, nexttoward(inf, 1)");
	CASE_CHECK_NE(isinf(dblnan1234), 0, "nexttoward double, nexttoward(inf, 1)");
	CASE_CHECK_NE(isinf(ldblnan1234), 0, "nexttoward double, nexttoward(inf, 1)");
}
/*
static uint64_t Factorial(uint64_t n)
{
	uint64_t rt = 0;
	if (n == 0)
	{
		rt = 1;
	}
	else
	{
		for (uint64_t i = 1; i < n; i++)
			rt *= i;
	}
	return rt;
}
static long double TaylorSeriesSinh(long double x)
{
	long double rt = 0.l;
	for (uint64_t i = 1; i < 12; i += 2)
		rt += powl(x, i) / Factorial(i);

	return rt;
}
static long double TaylorSeriesCosh(long double x)
{
	long double rt = 0.l;
	for (uint64_t i = 0; i < 11; i += 2)
		rt += powl(x, i) / Factorial(i);
	return rt;
}
static long double TaylorSeriesTanh(long double x)
{
	constexpr long double BernouliiNumber[] = {
		1.000000000l,
		0.500000000l,
		0.166666666l,
		0.000000000l,
		-0.033333333l,
		0.000000000l,
		0.023809523l,
		0.000000000l,
		-0.033333333l,
		0.000000000l,
		0.075757575l,
		0.000000000l,
		-0.253113553l,
		0.000000000l,
		1.166666666l,
		0.000000000l,
		-7.092156862l,
		0.000000000l,
		54.97117794l,
		0.000000000l,
		-529.1242424l
	};

	long double rt = 0.l;
	for (uint64_t i = 0; i < 6; i++)
	{
		long double numerator =
			powl(2.l, 2.l * i) *
			(powl(2.l, 2.l * i) - 1) *
			BernouliiNumber[2 * i] *
			powl(x, 2 * i - 1);
		long double denumerator =
			Factorial(2 * i);

		rt = numerator / denumerator;
	}
	return rt;
}
*/

void test_hyperbole_trigonometry()
{
	CASE_CHECK_BALLPARK(sinhf(1.f), 1.175201f, 0.001f, "sinh float, 1");
	CASE_CHECK_BALLPARK(sinhf(-1.f), -1.175201f, 0.001f, "sinh float, -1");
	CASE_CHECK_BALLPARK(sinhf(+0.f), +0.f, 0.001f, "sinh float, +0.f");
	CASE_CHECK_BALLPARK(sinhf(-0.f), -0.f, 0.001f, "sinh float, -0.f");
	CASE_CHECK_NE(isinf(sinhf(710.5f)), 0, "sinh float, 710.5");

	CASE_CHECK_BALLPARK(sinh(1.), 1.175201, 0.001, "sinh double, 1");
	CASE_CHECK_BALLPARK(sinh(-1.), -1.175201, 0.001, "sinh double, -1");
	CASE_CHECK_BALLPARK(sinh(+0.), +0., 0.001, "sinh double, +0.f");
	CASE_CHECK_BALLPARK(sinh(-0.), -0., 0.001, "sinh double, -0.f");
	CASE_CHECK_NE(isinf(sinh(710.5)), 0, "sinh double, 710.5");

	CASE_CHECK_BALLPARK(sinhl(1.l), 1.175201l, 0.001l, "sinh long double, 1");
	CASE_CHECK_BALLPARK(sinhl(-1.l), -1.175201l, 0.001l, "sinh long double, -1");
	CASE_CHECK_BALLPARK(sinhl(+0.l), +0.l, 0.001l, "sinh long double, +0.f");
	CASE_CHECK_BALLPARK(sinhl(-0.l), -0.l, 0.001l, "sinh long double, -0.f");
	CASE_CHECK_NE(isinf(sinhl(710.5l)), 0, "sinh long double, 710.5");


	CASE_CHECK_BALLPARK(coshf(1.f), 1.543081f, 0.001f, "cosh float, 1");
	CASE_CHECK_BALLPARK(coshf(-1.f), 1.543081f, 0.001f, "cosh float, -1");
	CASE_CHECK_BALLPARK(coshf(+0.f), 1.f, 0.001f, "cosh float, +0.f");
	CASE_CHECK_BALLPARK(coshf(-0.f), 1.f, 0.001f, "cosh float, -0.f");
	CASE_CHECK_NE(isinf(coshf(710.5f)), 0, "cosh float, 710.5");

	CASE_CHECK_BALLPARK(cosh(1.), 1.543081, 0.001, "cosh double, 1");
	CASE_CHECK_BALLPARK(cosh(-1.), 1.543081, 0.001, "cosh double, -1");
	CASE_CHECK_BALLPARK(cosh(+0.), 1., 0.001, "cosh double, +0.f");
	CASE_CHECK_BALLPARK(cosh(-0.), 1., 0.001, "cosh double, -0.f");
	CASE_CHECK_NE(isinf(cosh(710.5)), 0, "cosh double, 710.5");

	CASE_CHECK_BALLPARK(coshl(1.l), 1.543081l, 0.001l, "cosh long double, 1");
	CASE_CHECK_BALLPARK(coshl(-1.l), 1.543081l, 0.001l, "cosh long double, -1");
	CASE_CHECK_BALLPARK(coshl(+0.l), 1.l, 0.001l, "cosh long double, +0.f");
	CASE_CHECK_BALLPARK(coshl(-0.l), 1.l, 0.001l, "cosh long double, -0.f");
	CASE_CHECK_NE(isinf(coshl(710.5l)), 0, "cosh long double, 710.5");


	CASE_CHECK_BALLPARK(tanhf(1.f), 0.761594f, 0.001f, "tanh float, 1");
	CASE_CHECK_BALLPARK(tanhf(-1.f), -0.761594f, 0.001f, "tanh float, -1");
	CASE_CHECK_BALLPARK(tanhf(+0.f), +0.f, 0.001f, "tanh float, +0.f");
	CASE_CHECK_BALLPARK(tanhf(-0.f), -0.f, 0.001f, "tanh float, -0.f");

	CASE_CHECK_BALLPARK(tanh(1.), 0.761594, 0.001, "tanh double, 1");
	CASE_CHECK_BALLPARK(tanh(-1.), -0.761594, 0.001, "tanh double, -1");
	CASE_CHECK_BALLPARK(tanh(+0.), +0., 0.001, "tanh double, +0.f");
	CASE_CHECK_BALLPARK(tanh(-0.), -0., 0.001, "tanh double, -0.f");

	CASE_CHECK_BALLPARK(tanhl(1.l), 0.761594l, 0.001l, "tanh long double, 1");
	CASE_CHECK_BALLPARK(tanhl(-1.l), -0.761594l, 0.001l, "tanh long double, -1");
	CASE_CHECK_BALLPARK(tanhl(+0.l), +0.l, 0.001l, "tanh long double, +0.f");
	CASE_CHECK_BALLPARK(tanhl(-0.l), -0.l, 0.001l, "tanh long double, -0.f");


	CASE_CHECK_BALLPARK(asinhf(1.f), 0.881374f, 0.001f, "asinh float, 1");
	CASE_CHECK_BALLPARK(asinhf(-1.f), -0.881374f, 0.001f, "asinh float, -1");
	CASE_CHECK_BALLPARK(asinhf(+0.f), +0.f, 0.001f, "asinh float, +0.f");
	CASE_CHECK_BALLPARK(asinhf(-0.f), -0.f, 0.001f, "asinh float, -0.f");

	CASE_CHECK_BALLPARK(asinh(1.), 0.881374, 0.001, "asinh double, 1");
	CASE_CHECK_BALLPARK(asinh(-1.), -0.881374, 0.001, "asinh double, -1");
	CASE_CHECK_BALLPARK(asinh(+0.), +0., 0.001, "asinh double, +0.f");
	CASE_CHECK_BALLPARK(asinh(-0.), -0., 0.001, "asinh double, -0.f");

	CASE_CHECK_BALLPARK(asinhl(1.l), 0.881374l, 0.001l, "asinh long double, 1");
	CASE_CHECK_BALLPARK(asinhl(-1.l), -0.881374l, 0.001l, "asinh long double, -1");
	CASE_CHECK_BALLPARK(asinhl(+0.l), +0.l, 0.001l, "asinh long double, +0.f");
	CASE_CHECK_BALLPARK(asinhl(-0.l), -0.l, 0.001l, "asinh long double, -0.f");

	CASE_CHECK_BALLPARK(acoshf(1.f), 0.f, 0.001f, "acosh float, 1");
	CASE_CHECK_BALLPARK(acoshf(10.f), 2.993223f, 0.001f, "acosh float, 10");
	CASE_CHECK_EQ(acoshf(FLT_MAX), INFINITY, "acosh float, FLT_MAX");
	CASE_CHECK_EQ(acoshf(INFINITY), INFINITY, "acosh float, INFINITY");
	CASE_CHECK_NE(isnan(acoshf(-0.5)), 0, "acosh float, -nan");

	CASE_CHECK_BALLPARK(acosh(1.), 0., 0.001, "acosh double, 1");
	CASE_CHECK_BALLPARK(acosh(10.), 2.993223, 0.001, "acosh double, 10");
	CASE_CHECK_EQ(acosh(DBL_MAX), INFINITY, "acosh double, DBL_MAX");
	CASE_CHECK_EQ(acosh(INFINITY), INFINITY, "acosh double, INFINITY");
	CASE_CHECK_NE(isnan(acosh(-0.5)), 0, "acosh double, -nan");

	CASE_CHECK_BALLPARK(acoshl(1.l), 0.l, 0.001l, "acosh long double, 1");
	CASE_CHECK_BALLPARK(acoshl(10.l), 2.993223l, 0.001l, "acosh long double, 10");
	if constexpr (sizeof(long double) == 10)
	{
		CASE_CHECK_EQ(acoshl(LDBL_MAX), INFINITY, "acosh long double, LDBL_MAX");
	}
	else
	{
		CASE_CHECK_EQ(acoshl(LDBL_MAX), INFINITY, "acosh long double, LDBL_MAX");
	}
	CASE_CHECK_EQ(acoshl(INFINITY), INFINITY, "acosh long double, INFINITY");
	CASE_CHECK_NE(isnan(acoshl(-0.5l)), 0, "acosh long double, -nan");


	CASE_CHECK_BALLPARK(atanhf(0.f), 0.0f, 0.001f, "asinh float, 0");
	CASE_CHECK_BALLPARK(atanhf(-0.f), -0.0f, 0.001f, "asinh float, -0");
	CASE_CHECK_BALLPARK(atanhf(0.9f), +1.472219f, 0.001f, "asinh float, +0.9");
	CASE_CHECK_EQ(atanhf(-1.f), -INFINITY, "asinh float, -1");

	CASE_CHECK_BALLPARK(atanh(0.), 0.0, 0.001, "asinh double, 0");
	CASE_CHECK_BALLPARK(atanh(-0.), -0.0, 0.001, "asinh double, -0");
	CASE_CHECK_BALLPARK(atanh(0.9), +1.472219, 0.001, "asinh double, +0.9");
	CASE_CHECK_EQ(atanh(-1.), -INFINITY, "asinh double, -1");

	CASE_CHECK_BALLPARK(atanhl(0.l), 0.0l, 0.001l, "asinh long double, 0");
	CASE_CHECK_BALLPARK(atanhl(-0.l), -0.0l, 0.001l, "asinh long double, -0");
	CASE_CHECK_BALLPARK(atanhl(0.9l), +1.472219l, 0.001l, "asinh long double, +0.9");
	CASE_CHECK_EQ(atanhl(-1.l), -INFINITY, "asinh long double, -1");
	

	CASE_CHECK_BALLPARK(atan2f(1.f, 1.f)  ,  0.785398f, 0.001f, "atan2 float, atan2(1., 1.)");
	CASE_CHECK_BALLPARK(atan2f(1.f, -1.f) ,  2.356194f, 0.001f, "atan2 float, atan2(1., -1.)");
	CASE_CHECK_BALLPARK(atan2f(-1.f, 1.f) , -0.785398f, 0.001f, "atan2 float, atan2(-1., 1.)");
	CASE_CHECK_BALLPARK(atan2f(-1.f, -1.f), -2.356194f, 0.001f, "atan2 float, atan2(-1., -1.)");
	CASE_CHECK_BALLPARK(atan2f(0.f, 0.f)  ,        0.f, 0.001f, "atan2 float, atan2(0., 0.)");
	CASE_CHECK_BALLPARK(atan2f(0.f, -0.f) ,  3.141593f, 0.001f, "atan2 float, atan2(0., -0.)");
	CASE_CHECK_BALLPARK(atan2f(7.f, 0.f)  ,  1.570796f, 0.001f, "atan2 float, atan2(7., 0.)");
	CASE_CHECK_BALLPARK(atan2f(7.f, -0.f) ,  1.570796f, 0.001f, "atan2 float, atan2(7., -0.)");

	CASE_CHECK_BALLPARK(atan2(1., 1.)  ,  0.785398, 0.001, "atan2 double, atan2(1., 1.)");
	CASE_CHECK_BALLPARK(atan2(1., -1.) ,  2.356194, 0.001, "atan2 double, atan2(1., -1.)");
	CASE_CHECK_BALLPARK(atan2(-1., 1.) , -0.785398, 0.001, "atan2 double, atan2(-1., 1.)");
	CASE_CHECK_BALLPARK(atan2(-1., -1.), -2.356194, 0.001, "atan2 double, atan2(-1., -1.)");
	CASE_CHECK_BALLPARK(atan2(0., 0.)  ,        0., 0.001, "atan2 double, atan2(0., 0.)");
	CASE_CHECK_BALLPARK(atan2(0., -0.) ,  3.141593, 0.001, "atan2 double, atan2(0., -0.)");
	CASE_CHECK_BALLPARK(atan2(7., 0.)  ,  1.570796, 0.001, "atan2 double, atan2(7., 0.)");
	CASE_CHECK_BALLPARK(atan2(7., -0.) ,  1.570796, 0.001, "atan2 double, atan2(7., -0.)");

	CASE_CHECK_BALLPARK(atan2l(1.l , 1.l)  , 0.785398l, 0.001l, "atan2 long double, atan2(1., 1.)");
	CASE_CHECK_BALLPARK(atan2l(1.l, -1.l) ,  2.356194l, 0.001l, "atan2 long double, atan2(1., -1.)");
	CASE_CHECK_BALLPARK(atan2l(-1.l, 1.l) , -0.785398l, 0.001l, "atan2 long double, atan2(-1., 1.)");
	CASE_CHECK_BALLPARK(atan2l(-1.l, -1.l), -2.356194l, 0.001l, "atan2 long double, atan2(-1., -1.)");
	CASE_CHECK_BALLPARK(atan2l(0.l, 0.l)  ,        0.l, 0.001l, "atan2 long double, atan2(0., 0.)");
	CASE_CHECK_BALLPARK(atan2l(0.l, -0.l) ,  3.141593l, 0.001l, "atan2 long double, atan2(0., -0.)");
	CASE_CHECK_BALLPARK(atan2l(7.l, 0.l)  ,  1.570796l, 0.001l, "atan2 long double, atan2(7., 0.)");
	CASE_CHECK_BALLPARK(atan2l(7.l, -0.l) ,  1.570796l, 0.001l, "atan2 long double, atan2(7., -0.)");

}



void test_math()
{
	printf("\ntest suite math:\n");
	test_fpclassify();
	test_trigonometry_sine();
	test_trigonometry_cos();
	test_trigonometry_tan();
	test_trigonometry_arc_sine();
	test_trigonometry_arc_cos();
	test_trigonometry_arc_tan();
	test_base_exponents();
	test_pow();
	test_root();
	test_fabs();
	test_log();
	test_exponent_deconstruction();
	test_rounding();
	test_modf();
	test_copysign();
	test_remquo();
	test_minmax();
	test_fdim();
	test_fma();
	test_hypot();
	test_erf();
	test_tgamma();
	test_lgamma();
	test_nan();
	test_nextafter();
	test_nexttoward();
	test_hyperbole_trigonometry();
}