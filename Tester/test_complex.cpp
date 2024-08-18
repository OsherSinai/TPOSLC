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
#include <include\complex.h>
#include <include\math.h>
#include <include\float.h>

void test_cplx()
{
	float complex cplxf = CMPLX(1., 2.);
	double complex cplxd = CMPLX(3., 4.);
	long double complex cplxld = CMPLX(5., 6.);
	
	CASE_CHECK_EQ(crealf(cplxf), 1.f, "creal float");
	CASE_CHECK_EQ(creal(cplxd), 3.f, "creal double");
	CASE_CHECK_EQ(creall(cplxld), 5.f, "creal long double");
	CASE_CHECK_EQ(cimagf(cplxf), 2.f, "cimag float");
	CASE_CHECK_EQ(cimag(cplxd), 4.f, "cimag double");
	CASE_CHECK_EQ(cimagl(cplxld), 6.f, "cimag long double");
}
void test_complex_trigonometry()
{
	auto sinrf  = csinf(1);
	auto sinr   = csin(1);
	auto sinrl  = csinl(1);
	auto sinrfi = csinf(I);
	auto sinri  = csin(I);
	auto sinrli = csinl(I);
	auto cosrf  = ccosf(1);
	auto cosr   = ccos(1);
	auto cosrl  = ccosl(1);
	auto cosrfi = ccosf(I);
	auto cosri  = ccos(I);
	auto cosrli = ccosl(I);
	auto tanrf  = ctanf(1);
	auto tanr   = ctan(1);
	auto tanrl  = ctanl(1);
	auto tanrfi = ctanf(I);
	auto tanri  = ctan(I);
	auto tanrli = ctanl(I);
	CASE_CHECK_BALLPARK(crealf(sinrf), 0.841471f, 0.0001f, "csin float, real, 1");
	CASE_CHECK_BALLPARK(cimagf(sinrf), 0.000000f, 0.0001f, "csin float, imag, 1");
	CASE_CHECK_BALLPARK(creal(sinr),   0.841471,  0.0001, "csin double, real, 1");
	CASE_CHECK_BALLPARK(cimag(sinr),   0.000000,  0.0001, "csin double, imag, 1");
	CASE_CHECK_BALLPARK(creall(sinrl), 0.841471l, 0.0001l, "csin long double, real, 1");
	CASE_CHECK_BALLPARK(cimagl(sinrl), 0.000000l, 0.0001l, "csin long double, imag, 1");

	CASE_CHECK_BALLPARK(crealf(sinrfi), 0.000000f, 0.0001f, "csin float, real, I");
	CASE_CHECK_BALLPARK(cimagf(sinrfi), 1.175201f, 0.0001f, "csin float, imag, I");
	CASE_CHECK_BALLPARK(creal(sinri),   0.000000,  0.0001, "csin double, real, I");
	CASE_CHECK_BALLPARK(cimag(sinri),   1.175201,  0.0001, "csin double, imag, I");
	CASE_CHECK_BALLPARK(creall(sinrli), 0.000000l, 0.0001l, "csin long double, real, I");
	CASE_CHECK_BALLPARK(cimagl(sinrli), 1.175201l, 0.0001l, "csin long double, imag, I");
	

	CASE_CHECK_BALLPARK(crealf(cosrf), 0.540302f, 0.0001f, "ccos float, real, 1");
	CASE_CHECK_BALLPARK(cimagf(cosrf), 0.000000f, 0.0001f, "ccos float, imag, 1");
	CASE_CHECK_BALLPARK(creal(cosr),   0.540302,  0.0001, "ccos double, real, 1");
	CASE_CHECK_BALLPARK(cimag(cosr),   0.000000,  0.0001, "ccos double, imag, 1");
	CASE_CHECK_BALLPARK(creall(cosrl), 0.540302l, 0.0001l, "ccos long double, real, 1");
	CASE_CHECK_BALLPARK(cimagl(cosrl), 0.000000l, 0.0001l, "ccos long double, imag, 1");

	CASE_CHECK_BALLPARK(crealf(cosrfi), 1.543081f, 0.0001f, "ccos float, real, I");
	CASE_CHECK_BALLPARK(cimagf(cosrfi), 0.000000f, 0.0001f, "ccos float, imag, I");
	CASE_CHECK_BALLPARK(creal(cosri),   1.543081,  0.0001, "ccos double, real, I");
	CASE_CHECK_BALLPARK(cimag(cosri),   0.000000,  0.0001, "ccos double, imag, I");
	CASE_CHECK_BALLPARK(creall(cosrli), 1.543081l, 0.0001l, "ccos long double, real, I");
	CASE_CHECK_BALLPARK(cimagl(cosrli), 0.000000l, 0.0001l, "ccos long double, imag, I");


	CASE_CHECK_BALLPARK(crealf(tanrf), 1.557408f, 0.0001f, "ctan float, real, 1");
	CASE_CHECK_BALLPARK(cimagf(tanrf), 0.000000f, 0.0001f, "ctan float, imag, 1");
	CASE_CHECK_BALLPARK(creal(tanr), 1.557408, 0.0001, "ctan double, real, 1");
	CASE_CHECK_BALLPARK(cimag(tanr),   0.000000,  0.0001, "ctan double, imag, 1");
	CASE_CHECK_BALLPARK(creall(tanrl), 1.557408l, 0.0001l, "ctan long double, real, 1");
	CASE_CHECK_BALLPARK(cimagl(tanrl), 0.000000l, 0.0001l, "ctan long double, imag, 1");

	CASE_CHECK_BALLPARK(crealf(tanrfi), 0.000000f, 0.0001f, "ctan float, real, I");
	CASE_CHECK_BALLPARK(cimagf(tanrfi), 0.761594f, 0.0001f, "ctan float, imag, I");
	CASE_CHECK_BALLPARK(creal(tanri), 0.000000, 0.0001, "ctan double, real, I");
	CASE_CHECK_BALLPARK(cimag(tanri),   0.761594,  0.0001, "ctan double, imag, I");
	CASE_CHECK_BALLPARK(creall(tanrli), 0.000000l, 0.0001l, "ctan long double, real, I");
	CASE_CHECK_BALLPARK(cimagl(tanrli), 0.761594l, 0.0001l, "ctan long double, imag, I");

}
void test_carg()
{
	float complex f1 = 1.0 + 0.0 * I;
	float complex f2 = 0.0 + 1.0 * I;
	float complex f3 = -1.0 + 0.0 * I;
	float complex f4 = CMPLX(-1, -0.0);

	double complex d1 = 1.0 + 0.0 * I;
	double complex d2 = 0.0 + 1.0 * I;
	double complex d3 = -1.0 + 0.0 * I;
	double complex d4 = CMPLX(-1, -0.0);

	long double complex ld1 = 1.0 + 0.0 * I;
	long double complex ld2 = 0.0 + 1.0 * I;
	long double complex ld3 = -1.0 + 0.0 * I;
	long double complex ld4 = CMPLX(-1, -0.0);

	CASE_CHECK_BALLPARK(cargf(f1), 0.000000f, 0.0001f, "carg float, 1");
	CASE_CHECK_BALLPARK(cargf(f2), 1.570796f, 0.0001f, "carg float, 2");
	CASE_CHECK_BALLPARK(cargf(f3), 3.141593f, 0.0001f, "carg float, 3");
	CASE_CHECK_BALLPARK(cargf(f4), -3.141593f, 0.0001f, "carg float, 4");

	CASE_CHECK_BALLPARK(carg(d1), 0.000000, 0.0001, "carg double, 1");
	CASE_CHECK_BALLPARK(carg(d2), 1.570796, 0.0001, "carg double, 2");
	CASE_CHECK_BALLPARK(carg(d3), 3.141593, 0.0001, "carg double, 3");
	CASE_CHECK_BALLPARK(carg(d4), -3.141593, 0.0001, "carg double, 4");

	CASE_CHECK_BALLPARK(cargl(ld1), 0.000000l, 0.0001l, "carg long double, 1");
	CASE_CHECK_BALLPARK(cargl(ld2), 1.570796l, 0.0001l, "carg long double, 2");
	CASE_CHECK_BALLPARK(cargl(ld3), 3.141593l, 0.0001l, "carg long double, 3");
	CASE_CHECK_BALLPARK(cargl(ld4), -3.141593l, 0.0001l, "carg long double, 4");

}

void test_conj()
{
	float complex f1 = 0.0 + 1.0 * I;
	double complex d1 = 0.0 + 1.0 * I;
	long double complex ld1 = 0.0 + 1.0 * I;

	float complex f2 = conjf(f1);
	double complex d2 = conj(d1);
	long double complex ld2 = conjl(ld1);
	CASE_CHECK_EQ(crealf(f1), crealf(f2), "conj float, real");
	CASE_CHECK_EQ(-cimagf(f1), cimagf(f2), "conj float, imag");
	CASE_CHECK_EQ(creal(d1), creal(d2), "conj double, real");
	CASE_CHECK_EQ(-cimag(d1), cimag(d2), "conj double, imag");
	CASE_CHECK_EQ(crealf(ld1), crealf(ld2), "conj long double, real");
	CASE_CHECK_EQ(-cimagf(ld1), cimagf(ld2), "conj long double, imag");
}

void test_csqrt()
{
	float complex f1 = csqrtf(-4.f);
	double complex d1 = csqrt(-4.);
	long double complex ld1 = csqrtl(-4.l);

	float complex f2 = csqrtf(conjf(-4.f));
	double complex d2 = csqrt(conj(-4.));
	long double complex ld2 = csqrtl(conjl(-4.l));

	CASE_CHECK_BALLPARK(crealf(f1), 0.f, 0.0001f, "csqrtf float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 2.f, 0.0001f, "csqrtf float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 0., 0.0001, "csqrtf double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 2., 0.0001, "csqrtf double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 0.l, 0.0001l, "csqrtf long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 2.l, 0.0001l, "csqrtf long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 0.f, 0.0001f, "csqrtf float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), -2.f, 0.0001f, "csqrtf float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 0., 0.0001, "csqrtf double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), -2., 0.0001, "csqrtf double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.l, 0.0001l, "csqrtf long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), -2.l, 0.0001l,"csqrtf long double, imag 3");

	auto csf = csqrtf(conjf(1.f + 1.f * I));
	auto scf = conjf(csqrtf(1.f + 1.f * I));
	auto csd = csqrt(conj(1. + 1. * I));
	auto scd = conj(csqrt(1. + 1. * I));
	auto csl = csqrtl(conjl(1.l + 1.l * I));
	auto scl = conjl(csqrtl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "csqrt(conj) == conj(csqrt) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "csqrt(conj) == conj(csqrt) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "csqrt(conj) == conj(csqrt) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "csqrt(conj) == conj(csqrt) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "csqrt(conj) == conj(csqrt) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "csqrt(conj) == conj(csqrt) long double, imag");
	
	auto  rzerof = 0.f + 0.f * I;
	auto  rzerod = 0. + 0. * I;
	auto  rzerol = 0.l + 0.l * I;
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "csqrt(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "csqrt(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "csqrt(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "csqrt(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "csqrt(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "csqrt(0) long double, imag");

	auto x1yinff = csqrtf(CMPLX(1.f,INFINITY));
	auto x1yinfd = csqrt(CMPLX(1., INFINITY));
	auto x1yinfl = csqrtl(CMPLX(1.l, INFINITY));
	auto xnanyinff = csqrtf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = csqrt(CMPLX(NAN, INFINITY));
	auto xnanyinfl = csqrtl(CMPLX(NAN, INFINITY));

	CASE_CHECK_NE(isinf(crealf(x1yinff)) , 0, "csqrtf float, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimagf(x1yinff)) , 0, "csqrtf float, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creal(x1yinfd))  , 0, "csqrtf double, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimag(x1yinfd))  , 0, "csqrtf double, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creall(x1yinfl)), 0, "csqrtf long double, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimagl(x1yinfl)), 0, "csqrtf long double, imag 1+inf*i");
	CASE_CHECK_NE(isinf(crealf(xnanyinff)) , 0, "csqrtf float, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimagf(xnanyinff)) , 0, "csqrtf float, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creal(xnanyinfd))  , 0, "csqrtf double, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimag(xnanyinfd))  , 0, "csqrtf double, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creall(xnanyinfl)), 0, "csqrtf long double, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimagl(xnanyinfl)), 0, "csqrtf long double, imag nan+inf*i");

	auto xynanf = csqrtf(CMPLX(1.f ,NAN));
	auto xynand = csqrt(CMPLX(1., NAN));
	auto xynanl = csqrtl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "csqrtf float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "csqrtf float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "csqrtf double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "csqrtf double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "csqrtf long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "csqrtf long double, imag nan+1*i");

	auto xminfy1f = csqrtf(CMPLX(-INFINITY, 1.f));
	auto xminfy1d = csqrt(CMPLX(-INFINITY, 1.));
	auto xminfy1l = csqrtl(CMPLX(-INFINITY, 1.l));
	CASE_CHECK_EQ(crealf(xminfy1f), 0.f, "csqrtf float, real -inf+1*i");
	CASE_CHECK_NE(isinf(cimagf(xminfy1f)), 0, "csqrtf float, imag -inf+1*i");
	CASE_CHECK_EQ(creal(xminfy1d), 0., "csqrtf double, real -inf+1*i");
	CASE_CHECK_NE(isinf(cimag(xminfy1d)), 0, "csqrtf double, imag -inf+1*i");
	CASE_CHECK_EQ(creall(xminfy1l), 0.l, "csqrtf long double, real -inf+1*i");
	CASE_CHECK_NE(isinf(cimagl(xminfy1l)), 0, "csqrtf long double, imag -inf+1*i");

	auto xinffy1f = csqrtf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = csqrt(CMPLX(INFINITY, 1.));
	auto xinffy1l = csqrtl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "csqrtf float, real inf+1*i");
	CASE_CHECK_EQ(cimagf(xinffy1f), 0.f, "csqrtf float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "csqrtf double, real inf+1*i");
	CASE_CHECK_EQ(cimag(xinffy1d), 0., "csqrtf double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "csqrtf long double, real inf+1*i");
	CASE_CHECK_EQ(cimagl(xinffy1l), 0.l, "csqrtf long double, imag inf+1*i");

	auto xminfynanf = csqrtf(CMPLX(-INFINITY, NAN));
	auto xminfynand = csqrt(CMPLX(-INFINITY, NAN));
	auto xminfynanl = csqrtl(CMPLX(-INFINITY, NAN));
	auto xinffynanf = csqrtf(CMPLX(INFINITY, NAN));
	auto xinffynand = csqrt(CMPLX(INFINITY, NAN));
	auto xinffynanl = csqrtl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isnan(crealf(xminfynanf)), 0, "csqrtf float, real -inf+nan*i");
	CASE_CHECK_NE(isinf(cimagf(xminfynanf)), 0, "csqrtf float, imag -inf+nan*i");
	CASE_CHECK_NE(isnan(creal(xminfynand)), 0, "csqrtf double, real -inf+nan*i");
	CASE_CHECK_NE(isinf(cimag(xminfynand)), 0, "csqrtf double, imag -inf+nan*i");
	CASE_CHECK_NE(isnan(creall(xminfynanl)), 0, "csqrtf long double, real -inf+nan*i");
	CASE_CHECK_NE(isinf(cimagl(xminfynanl)), 0, "csqrtf long double, imag -inf+nan*i");
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "csqrtf float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "csqrtf float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "csqrtf double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "csqrtf double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "csqrtf long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "csqrtf long double, imag inf+nan*i");

	auto xnany1f = csqrtf(CMPLX(NAN, 1));
	auto xnany1d = csqrt(CMPLX(NAN, 1));
	auto xnany1l = csqrtl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "csqrtf float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "csqrtf float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "csqrtf double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "csqrtf double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "csqrtf long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "csqrtf long double, imag nan+1*i");

	auto xnanynanf = csqrtf(CMPLX(NAN, NAN));
	auto xnanynand = csqrt(CMPLX(NAN, NAN));
	auto xnanynanl = csqrtl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "csqrtf float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "csqrtf float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "csqrtf double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "csqrtf double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "csqrtf long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "csqrtf long double, imag nan+nan*i");

}

void test_cabs()
{
	float complex f1 = 1.0f + 1.0f * I;
	double complex d1 = 1.0 + 1.0 * I;
	long double complex ld1 = 1.0l + 1.0l * I;
	CASE_CHECK_BALLPARK(cabsf(f1), 1.414214f, 0.0001f, "cabs float");
	CASE_CHECK_BALLPARK(cabs(d1), 1.414214, 0.0001, "cabs double");
	CASE_CHECK_BALLPARK(cabsl(ld1), 1.414214l, 0.0001l, "cabs long double");

}

void test_cproj()
{
	float complex f1 = cprojf(1. + 2. * I);
	float complex f2 = cprojf(INFINITY + 2.0 * I);
	float complex f3 = cprojf(INFINITY - 2.0 * I);
	float complex d1 = cproj(1. + 2. * I);
	float complex d2 = cproj(INFINITY + 2.0 * I);
	float complex d3 = cproj(INFINITY - 2.0 * I);
	float complex ld1 = cprojl(1. + 2. * I);
	float complex ld2 = cprojl(INFINITY + 2.0 * I);
	float complex ld3 = cprojl(INFINITY - 2.0 * I);
	CASE_CHECK_BALLPARK(crealf(f1)    , 1.f, 0.0001f, "cproj float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1)    , 2.f, 0.0001f, "cproj float, imag 1");
	CASE_CHECK_NE(isinf(crealf(f2))   , 0  ,          "cproj float, real 2");
	CASE_CHECK_EQ(signbitf(cimagf(f2)), 0  ,          "cproj float, imag signbit 2");
	CASE_CHECK_BALLPARK(cimagf(f2)    , 0.f, 0.0001f, "cproj float, imag 2");
	CASE_CHECK_NE(isinf(crealf(f3))   , 0  ,          "cproj float, real 3");
	CASE_CHECK_NE(signbitf(cimagf(f3)), 0  ,          "cproj float, imag signbit 3");
	CASE_CHECK_BALLPARK(cimagf(f3)    , 0.f, 0.0001f, "cproj float, imag 3");
	
	CASE_CHECK_BALLPARK(crealf(d1)    , 1.f, 0.0001f, "cproj double, real 1");
	CASE_CHECK_BALLPARK(cimagf(d1)    , 2.f, 0.0001f, "cproj double, imag 1");
	CASE_CHECK_NE(isinf(crealf(d2))   , 0  ,          "cproj double, real 2");
	CASE_CHECK_EQ(signbitf(cimagf(d2)), 0  ,          "cproj double, imag signbit 2");
	CASE_CHECK_BALLPARK(cimagf(d2)    , 0.f, 0.0001f, "cproj double, imag 2");
	CASE_CHECK_NE(isinf(crealf(d3))   , 0  ,          "cproj double, real 3");
	CASE_CHECK_NE(signbitf(cimagf(d3)), 0  ,          "cproj double, imag signbit 3");
	CASE_CHECK_BALLPARK(cimagf(d3)    , 0.f, 0.0001f, "cproj double, imag 3");
	
	CASE_CHECK_BALLPARK(crealf(ld1)    , 1.f, 0.0001f, "cproj long double, real 1");
	CASE_CHECK_BALLPARK(cimagf(ld1)    , 2.f, 0.0001f, "cproj long double, imag 1");
	CASE_CHECK_NE(isinf(crealf(ld2))   , 0  ,          "cproj long double, real 2");
	CASE_CHECK_EQ(signbitf(cimagf(ld2)), 0  ,          "cproj long double, imag signbit 2");
	CASE_CHECK_BALLPARK(cimagf(ld2)    , 0.f, 0.0001f, "cproj long double, imag 2");
	CASE_CHECK_NE(isinf(crealf(ld3))   , 0  ,          "cproj long double, real 3");
	CASE_CHECK_NE(signbitf(cimagf(ld3)), 0  ,          "cproj long double, imag signbit 3");
	CASE_CHECK_BALLPARK(cimagf(ld3)    , 0.f, 0.0001f, "cproj long double, imag 3");
}

void test_cpow()
{
	float complex f1 = cpow(1.0 + 2.0 * I, 2);
	float complex f2 = cpow(-1., 0.5);
	float complex f3 = cpow(conj(-1.), 0.5);
	float complex f4 = cpow(I, I);
	double complex d1 = cpow(1.0 + 2.0 * I, 2);
	double complex d2 = cpow(-1., 0.5);
	double complex d3 = cpow(conj(-1.), 0.5);
	double complex d4 = cpow(I, I);
	long double complex ld1 = cpow(1.0 + 2.0 * I, 2);
	long double complex ld2 = cpow(-1., 0.5);
	long double complex ld3 = cpow(conj(-1.), 0.5);
	long double complex ld4 = cpow(I, I);

	CASE_CHECK_BALLPARK(crealf(f1),      -3.f, 0.0001f, "cproj float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1),       4.f, 0.0001f, "cproj float, imag 1");
	CASE_CHECK_BALLPARK(crealf(f2),       0.f, 0.0001f, "cproj float, real 2");
	CASE_CHECK_BALLPARK(cimagf(f2),       1.f, 0.0001f, "cproj float, imag 2");
	CASE_CHECK_BALLPARK(crealf(f3),       0.f, 0.0001f, "cproj float, real 3");
	CASE_CHECK_BALLPARK(cimagf(f3),      -1.f, 0.0001f, "cproj float, imag 3");
	CASE_CHECK_BALLPARK(crealf(f4), 0.207880f, 0.0001f, "cproj float, real 4");
	CASE_CHECK_BALLPARK(cimagf(f4), 0.000000f, 0.0001f, "cproj float, imag 4");

	CASE_CHECK_BALLPARK(creal(d1),      -3., 0.0001, "cproj double, real 1");
	CASE_CHECK_BALLPARK(cimag(d1),       4., 0.0001, "cproj double, imag 1");
	CASE_CHECK_BALLPARK(creal(d2),       0., 0.0001, "cproj double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2),       1., 0.0001, "cproj double, imag 2");
	CASE_CHECK_BALLPARK(creal(d3),       0., 0.0001, "cproj double, real 3");
	CASE_CHECK_BALLPARK(cimag(d3),      -1., 0.0001, "cproj double, imag 3");
	CASE_CHECK_BALLPARK(creal(d4), 0.207880, 0.0001, "cproj double, real 4");
	CASE_CHECK_BALLPARK(cimag(d4), 0.000000, 0.0001, "cproj double, imag 4");

	CASE_CHECK_BALLPARK(creall(ld1),      -3.l, 0.0001l, "cproj long double, real 1");
	CASE_CHECK_BALLPARK(cimagl(ld1),       4.l, 0.0001l, "cproj long double, imag 1");
	CASE_CHECK_BALLPARK(creall(ld2),       0.l, 0.0001l, "cproj long double, real 2");
	CASE_CHECK_BALLPARK(cimagl(ld2),       1.l, 0.0001l, "cproj long double, imag 2");
	CASE_CHECK_BALLPARK(creall(ld3),       0.l, 0.0001l, "cproj long double, real 3");
	CASE_CHECK_BALLPARK(cimagl(ld3),      -1.l, 0.0001l, "cproj long double, imag 3");
	CASE_CHECK_BALLPARK(creall(ld4), 0.207880l, 0.0001l, "cproj long double, real 4");
	CASE_CHECK_BALLPARK(cimagl(ld4), 0.000000l, 0.0001l, "cproj long double, imag 4");

}

void test_cexp()
{
	float complex f1 = cexpf(acosf(-1.f) * I);
	double complex d1 = cexp(acos(-1.) * I);
	long double complex ld1 = cexpl(acosl(-1.l) * I);

	CASE_CHECK_BALLPARK(crealf(f1), -1.f, 0.0001f, "cexp float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 0.f, 0.0001f, "cexp float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), -1., 0.0001, "cexp double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 0., 0.0001, "cexp double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), -1.l, 0.0001l, "cexp long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 0.l, 0.0001l, "cexp long double, imag 3");

	auto csf = cexpf(conjf(1.f + 1.f * I));
	auto scf = conjf(cexpf(1.f + 1.f * I));
	auto csd = cexp(conj(1. + 1. * I));
	auto scd = conj(cexp(1. + 1. * I));
	auto csl = cexpl(conjl(1.l + 1.l * I));
	auto scl = conjl(cexpl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "cexp(conj) == conj(cexp) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "cexp(conj) == conj(cexp) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "cexp(conj) == conj(cexp) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "cexp(conj) == conj(cexp) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "cexp(conj) == conj(cexp) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "cexp(conj) == conj(cexp) long double, imag");

	auto  rzerof = cexpf(0.f + 0.f * I);
	auto  rzerod = cexp(0. + 0. * I);
	auto  rzerol = cexpl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 1.f, 0.0001f, "cexp(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "cexp(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 1., 0.0001, "cexp(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "cexp(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 1.l, 0.0001l, "cexp(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "cexp(0) long double, imag");

	auto x1yinff = cexpf(CMPLX(1.f, INFINITY));
	auto x1yinfd = cexp(CMPLX(1., INFINITY));
	auto x1yinfl = cexpl(CMPLX(1.l, INFINITY));
	auto xnanyinff = cexpf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = cexp(CMPLX(NAN, INFINITY));
	auto xnanyinfl = cexpl(CMPLX(NAN, INFINITY));

	CASE_CHECK_NE(isnan(crealf(x1yinff)), 0, "cexp float, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagf(x1yinff)), 0, "cexp float, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creal(x1yinfd)), 0, "cexp double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimag(x1yinfd)), 0, "cexp double, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creall(x1yinfl)), 0, "cexp long double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagl(x1yinfl)), 0, "cexp long double, imag 1+inf*i");
	CASE_CHECK_NE(isnan(crealf(xnanyinff)), 0, "cexp float, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xnanyinff)), 0, "cexp float, imag nan+inf*i");
	CASE_CHECK_NE(isnan(creal(xnanyinfd)), 0, "cexp double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimag(xnanyinfd)), 0, "cexp double, imag nan+inf*i");
	CASE_CHECK_NE(isnan(creall(xnanyinfl)), 0, "cexp long double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xnanyinfl)), 0, "cexp long double, imag nan+inf*i");

	auto xynanf = cexpf(CMPLX(1.f, NAN));
	auto xynand = cexp(CMPLX(1., NAN));
	auto xynanl = cexpl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "cexp float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "cexp float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "cexp double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "cexp double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "cexp long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "cexp long double, imag nan+1*i");

	auto xminfy1f = cexpf(CMPLX(-INFINITY, 1.f));
	auto xminfy1d = cexp(CMPLX(-INFINITY, 1.));
	auto xminfy1l = cexpl(CMPLX(-INFINITY, 1.l));
	CASE_CHECK_EQ(crealf(xminfy1f), 0.f, "cexp float, real -inf+1*i");
	CASE_CHECK_EQ(cimagf(xminfy1f), 0.f, "cexp float, imag -inf+1*i");
	CASE_CHECK_EQ(creal(xminfy1d), 0., "cexp double, real -inf+1*i");
	CASE_CHECK_EQ(cimag(xminfy1d), 0., "cexp double, imag -inf+1*i");
	CASE_CHECK_EQ(creall(xminfy1l), 0.l, "cexp long double, real -inf+1*i");
	CASE_CHECK_EQ(cimagl(xminfy1l), 0.l, "cexp long double, imag -inf+1*i");
	
	auto xinffy1f = cexpf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = cexp(CMPLX(INFINITY, 1.));
	auto xinffy1l = cexpl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "cexp float, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagf(xinffy1f)), 0, "cexp float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "cexp double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimag(xinffy1d)), 0., "cexp double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "cexp long double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagl(xinffy1l)), 0, "cexp long double, imag inf+1*i");

	auto xminfyinff = cexpf(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfd = cexp(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfl = cexpl(CMPLX(-INFINITY, INFINITY));
	auto xinffyinff = cexpf(CMPLX(INFINITY, INFINITY));
	auto xinffyinfd = cexp(CMPLX(INFINITY, INFINITY));
	auto xinffyinfl = cexpl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xminfyinff), 0.f, 0.0001f, "cexp float, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xminfyinff), 0.f, 0.0001f, "cexp float, imag -inf+inf*i");
	CASE_CHECK_BALLPARK(creal(xminfyinfd), 0., 0.0001, "cexp double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xminfyinfd), 0, 0.0001, "cexp double, imag -inf+inf*i");
	CASE_CHECK_BALLPARK(creall(xminfyinfl), 0.l, 0.0001l, "cexp long double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xminfyinfl), 0.l, 0.0001l, "cexp long double, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(crealf(xinffyinff)), 0, "cexp float, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xinffyinff)), 0, "cexp float, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xinffyinfd)), 0, "cexp double, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimag(xinffyinfd)), 0, "cexp double, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xinffyinfl)), 0, "cexp long double, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xinffyinfl)), 0, "cexp long double, imag inf+inf*i");

	auto xminfynanf = cexpf(CMPLX(-INFINITY, NAN));
	auto xminfynand = cexp(CMPLX(-INFINITY, NAN));
	auto xminfynanl = cexpl(CMPLX(-INFINITY, NAN));
	auto xinffynanf = cexpf(CMPLX(INFINITY, NAN));
	auto xinffynand = cexp(CMPLX(INFINITY, NAN));
	auto xinffynanl = cexpl(CMPLX(INFINITY, NAN));
	CASE_CHECK_BALLPARK(crealf(xminfynanf), 0.f, 0.0001f, "cexp float, real -inf+nan*i");
	CASE_CHECK_BALLPARK(cimagf(xminfynanf), 0.f, 0.0001f, "cexp float, imag -inf+nan*i");
	CASE_CHECK_BALLPARK(creal(xminfynand), 0., 0.0001, "cexp double, real -inf+nan*i");
	CASE_CHECK_BALLPARK(cimag(xminfynand), 0., 0.0001, "cexp double, imag -inf+nan*i");
	CASE_CHECK_BALLPARK(creall(xminfynanl), 0.l, 0.0001l, "cexp long double, real -inf+nan*i");
	CASE_CHECK_BALLPARK(cimagl(xminfynanl), 0.l, 0.0001l, "cexp long double, imag -inf+nan*i");
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "cexp float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "cexp float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "cexp double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "cexp double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "cexp long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "cexp long double, imag inf+nan*i");

	auto xnany0f = cexpf(CMPLX(NAN, 0));
	auto xnany0d = cexp(CMPLX(NAN, 0));
	auto xnany0l = cexpl(CMPLX(NAN, 0));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "cexp float, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagf(xnany0f), 0.f, 0.0001, "cexp float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "cexp double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimag(xnany0d), 0., 0.0001, "cexp double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "cexp long double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagl(xnany0l), 0.l, 0.0001l, "cexp long double, imag nan+0*i");

	auto xnany1f = cexpf(CMPLX(NAN, 1));
	auto xnany1d = cexp(CMPLX(NAN, 1));
	auto xnany1l = cexpl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "cexp float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "cexp float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "cexp double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "cexp double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "cexp long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "cexp long double, imag nan+1*i");

	auto xnanynanf = cexpf(CMPLX(NAN, NAN));
	auto xnanynand = cexp(CMPLX(NAN, NAN));
	auto xnanynanl = cexpl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "cexp float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "cexp float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "cexp double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "cexp double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "cexp long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "cexp long double, imag nan+nan*i");
}

void test_clog()
{
	float fsqrd2 = sqrtf(2.f) / 2.f;
	double dsqrd2 = sqrtf(2.) / 2.;
	long double ldsqrd2 = sqrtl(2.l) / 2.l;
	float complex f1 = clogf(fsqrd2 + fsqrd2 *I);
	double complex d1 = clog(dsqrd2 + dsqrd2 * I);
	long double complex ld1 = clogl(ldsqrd2 + ldsqrd2 * I);
	
	CASE_CHECK_BALLPARK(crealf(f1), 0.f, 0.0001f, "clog float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), M_PI_4, 0.0001f, "clog float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 0., 0.0001, "clog double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), M_PI_4, 0.0001, "clog double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 0.l, 0.0001l, "clog long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), M_PI_4, 0.0001l, "clog long double, imag 3");

	auto csf = clogf(conjf(1.f + 1.f * I));
	auto scf = conjf(clogf(1.f + 1.f * I));
	auto csd = clog(conj(1. + 1. * I));
	auto scd = conj(clog(1. + 1. * I));
	auto csl = clogl(conjl(1.l + 1.l * I));
	auto scl = conjl(clogl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "clog(conj) == conj(clog) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "clog(conj) == conj(clog) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "clog(conj) == conj(clog) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "clog(conj) == conj(clog) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "clog(conj) == conj(clog) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "clog(conj) == conj(clog) long double, imag");

	auto  rzerof = clogf(0.f + 0.f * I);
	auto  rzerod = clog(0. + 0. * I);
	auto  rzerol = clogl(0.l + 0.l * I);
	CASE_CHECK_NE(isinf(crealf(rzerof)), 0, "clog(0) float, real");
	CASE_CHECK_NE(signbit(crealf(rzerof)), 0, "clog(0) float, sign real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "clog(0) float, imag");
	CASE_CHECK_NE(isinf(creal(rzerod)), 0, "clog(0) double, real");
	CASE_CHECK_NE(signbit(creal(rzerod)), 0, "clog(0) double, sign real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "clog(0) double, imag");
	CASE_CHECK_NE(isinf(creall(rzerol)), 0, "clog(0) long double, real");
	CASE_CHECK_NE(signbit(creall(rzerol)), 0, "clog(0) long double, sign real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "clog(0) long double, imag");

	auto  rmzerof = clogf(CMPLX(-0.f, 0.f));
	auto  rmzerod = clog(CMPLX(-0., 0.));
	auto  rmzerol = clogl(CMPLX(-0.l, 0.l));
	CASE_CHECK_NE(isinf(crealf(rmzerof)), 0, "clog(-0) float, real");
	CASE_CHECK_NE(signbit(crealf(rmzerof)), 0, "clog(-0) float, sign real");
	CASE_CHECK_BALLPARK(cimagf(rmzerof), M_PI, 0.0001f, "clog(-0) float, imag");
	CASE_CHECK_NE(isinf(creal(rmzerod)), 0, "clog(-0) double, real");
	CASE_CHECK_NE(signbit(creal(rmzerod)), 0, "clog(-0) double, sign real");
	CASE_CHECK_BALLPARK(cimag(rmzerod), M_PI, 0.0001, "clog(-0) double, imag");
	CASE_CHECK_NE(isinf(creall(rmzerol)), 0, "clog(-0) long double, real");
	CASE_CHECK_NE(signbit(creall(rmzerol)), 0, "clog(-0) long double, sign real");
	CASE_CHECK_BALLPARK(cimagl(rmzerol), M_PI, 0.0001l, "clog(-0) long double, imag");

	auto x1yinff = clogf(CMPLX(1.f, INFINITY));
	auto x1yinfd = clog(CMPLX(1., INFINITY));
	auto x1yinfl = clogl(CMPLX(1.l, INFINITY));
	auto xnanyinff = clogf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = clog(CMPLX(NAN, INFINITY));
	auto xnanyinfl = clogl(CMPLX(NAN, INFINITY));

	CASE_CHECK_NE(isinf(crealf(x1yinff)), 0, "clog float, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimagf(x1yinff), M_PI_2, 0.0001f, "clog float, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creal(x1yinfd)), 0, "clog double, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimag(x1yinfd), M_PI_2, 0.0001, "clog double, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creall(x1yinfl)), 0, "clog long double, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimagl(x1yinfl), M_PI_2, 0.0001l, "clog long double, imag 1+inf*i");

	CASE_CHECK_NE(isinf(crealf(xnanyinff)), 0, "clog float, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xnanyinff)), 0, "clog float, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creal(xnanyinfd)), 0, "clog double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimag(xnanyinfd)), 0, "clog double, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creall(xnanyinfl)), 0, "clog long double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xnanyinfl)), 0, "clog long double, imag nan+inf*i");

	auto xynanf = clogf(CMPLX(1.f, NAN));
	auto xynand = clog(CMPLX(1., NAN));
	auto xynanl = clogl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "clog float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "clog float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "clog double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "clog double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "clog long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "clog long double, imag nan+1*i");

	auto xminfy1f = clogf(CMPLX(-INFINITY, 1.f));
	auto xminfy1d = clog(CMPLX(-INFINITY, 1.));
	auto xminfy1l = clogl(CMPLX(-INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xminfy1f)), 0, "clog float, real -inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xminfy1f), M_PI, 0.0001f, "clog float, imag -inf+1*i");
	CASE_CHECK_NE(isinf(creal(xminfy1d)), 0, "clog double, real -inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xminfy1d), M_PI, 0.0001, "clog double, imag -inf+1*i");
	CASE_CHECK_NE(isinf(creall(xminfy1l)), 0, "clog long double, real -inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xminfy1l), M_PI, 0.0001l, "clog long double, imag -inf+1*i");

	auto xinffy1f = clogf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = clog(CMPLX(INFINITY, 1.));
	auto xinffy1l = clogl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "clog float, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xinffy1f), 0, 0.0001f, "clog float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "clog double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xinffy1d), 0., 0.0001, "clog double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "clog long double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xinffy1l), 0., 0.0001l, "clog long double, imag inf+1*i");

	auto xminfyinff = clogf(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfd = clog(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfl = clogl(CMPLX(-INFINITY, INFINITY));
	auto xinffyinff = clogf(CMPLX(INFINITY, INFINITY));
	auto xinffyinfd = clog(CMPLX(INFINITY, INFINITY));
	auto xinffyinfl = clogl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xminfyinff)), 0, "clog float, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xminfyinff), M_PI_4 * 3.f, 0.0001f, "clog float, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xminfyinfd)), 0, "clog double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xminfyinfd), M_PI_4 * 3., 0.0001, "clog double, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xminfyinfl)), 0, "clog long double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xminfyinfl), M_PI_4 * 3.l, 0.0001l, "clog long double, imag -inf+inf*i");

	CASE_CHECK_NE(isinf(crealf(xinffyinff)), 0, "clog float, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xinffyinff), M_PI_4, 0.0001f, "clog float, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xinffyinfd)), 0, "clog double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xinffyinfd), M_PI_4, 0.0001, "clog double, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xinffyinfl)), 0, "clog long double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xinffyinfl), M_PI_4, 0.0001l, "clog long double, imag inf+inf*i");

	auto xminfynanf = clogf(CMPLX(-INFINITY, NAN));
	auto xminfynand = clog(CMPLX(-INFINITY, NAN));
	auto xminfynanl = clogl(CMPLX(-INFINITY, NAN));
	auto xinffynanf = clogf(CMPLX(INFINITY, NAN));
	auto xinffynand = clog(CMPLX(INFINITY, NAN));
	auto xinffynanl = clogl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isinf(crealf(xminfynanf)), 0, "clog float, real -inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xminfynanf)), 0, "clog float, imag -inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xminfynand)), 0, "clog double, real -inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xminfynand)), 0, "clog double, imag -inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xminfynanl)), 0,"clog long double, real -inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xminfynanl)), 0,"clog long double, imag -inf+nan*i");
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "clog float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "clog float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "clog double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "clog double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "clog long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "clog long double, imag inf+nan*i");

	auto xnany0f = clogf(CMPLX(NAN, 0));
	auto xnany0d = clog(CMPLX(NAN, 0));
	auto xnany0l = clogl(CMPLX(NAN, 0));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "clog float, real nan+0*i");
	CASE_CHECK_NE(isnan(cimagf(xnany0f)), 0, "clog float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "clog double, real nan+0*i");
	CASE_CHECK_NE(isnan(cimag(xnany0d)), 0, "clog double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "clog long double, real nan+0*i");
	CASE_CHECK_NE(isnan(cimagl(xnany0l)), 0, "clog long double, imag nan+0*i");

	auto xnanynanf = clogf(CMPLX(NAN, NAN));
	auto xnanynand = clog(CMPLX(NAN, NAN));
	auto xnanynanl = clogl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "clog float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "clog float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "clog double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "clog double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "clog long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "clog long double, imag nan+nan*i");
}

void test_csinh()
{
	float complex f1 = csinhf(1.f);
	double complex d1 = csinh(1.);
	long double complex ld1 = csinhl(1.l);
	float complex f2 = csinhf(0.f+1.f * I);
	double complex d2 = csinh(0. + 1. * I);
	long double complex ld2 = csinhl(0.l + 1.l*I);

	CASE_CHECK_BALLPARK(crealf(f1), 1.17520f, 0.0001f, "csinh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 0.f, 0.0001f, "csinh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 1.17520, 0.0001, "csinh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 0., 0.0001, "csinh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 1.17520l, 0.0001l, "csinh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 0.l, 0.0001l, "csinh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 0.f, 0.0001f, "csinh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), 0.841471f, 0.0001f, "csinh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 0., 0.0001, "csinh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 0.841471, 0.0001, "csinh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.l, 0.0001l, "csinh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), 0.841471l, 0.0001l, "csinh long double, imag 3");

	auto csf = csinhf(conjf(1.f + 1.f * I));
	auto scf = conjf(csinhf(1.f + 1.f * I));
	auto csd = csinh(conj(1. + 1. * I));
	auto scd = conj(csinh(1. + 1. * I));
	auto csl = csinhl(conjl(1.l + 1.l * I));
	auto scl = conjl(csinhl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "csinh(conj) == conj(csinh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "csinh(conj) == conj(csinh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "csinh(conj) == conj(csinh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "csinh(conj) == conj(csinh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "csinh(conj) == conj(csinh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "csinh(conj) == conj(csinh) long double, imag");

	csf = csinh(CMPLX(1.f, 1.f));
	scf = csinh(CMPLX(-1.f, -1.f));
	csd = csinh(CMPLX(1., 1.));
	scd = csinh(CMPLX(-1., -1.));
	csl = csinh(CMPLX(1.l, 1.l));
	scl = csinh(CMPLX(-1.l, -1.l));
	CASE_CHECK_BALLPARK(crealf(csf), -crealf(scf), 0.0001f, "csinh(z) == -csinh(-z) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), -cimagf(scf), 0.0001f, "csinh(z) == -csinh(-z) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), -creal(scd), 0.0001, "csinh(z) == -csinh(-z) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), -cimag(scd), 0.0001, "csinh(z) == -csinh(-z) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), -creall(scl), 0.0001l, "csinh(z) == -csinh(-z) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), -cimagl(scl), 0.0001l, "csinh(z) == -csinh(-z) long double, imag");

	auto  rzerof = csinhf(0.f + 0.f * I);
	auto  rzerod = csinh(0. + 0. * I);
	auto  rzerol = csinhl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "csinh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "csinh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "csinh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "csinh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "csinh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "csinh(0) long double, imag");

	auto  rmzerof = csinhf(CMPLX(0.f, INFINITY));
	auto  rmzerod = csinh(CMPLX(0., INFINITY));
	auto  rmzerol = csinhl(CMPLX(0.l, INFINITY));
	CASE_CHECK_BALLPARK(crealf(rmzerof), 0.f, 0.0001f, "csinh(0,inf) float, real");
	CASE_CHECK_NE(isnan(cimagf(rmzerof)), 0, "csinh(0,inf) float, imag");
	CASE_CHECK_BALLPARK(creal(rmzerod), 0., 0.0001, "csinh(0,inf) double, real");
	CASE_CHECK_NE(isnan(cimag(rmzerod)), 0, "csinh(0,inf) double, imag");
	CASE_CHECK_BALLPARK(creall(rmzerol), 0.l, 0.0001l, "csinh(0,inf) long double, real");
	CASE_CHECK_NE(isnan(cimagl(rmzerol)), 0, "csinh(0,inf) long double, imag");

	rmzerof = csinhf(CMPLX(0.f, NAN));
	rmzerod = csinh(CMPLX(0., NAN));
	rmzerol = csinhl(CMPLX(0.l, NAN));
	CASE_CHECK_BALLPARK(crealf(rmzerof), 0.f, 0.0001f, "csinh(0,nan) float, real");
	CASE_CHECK_NE(isnan(cimagf(rmzerof)), 0, "csinh(0,nan) float, imag");
	CASE_CHECK_BALLPARK(creal(rmzerod), 0., 0.0001, "csinh(0,nan) double, real");
	CASE_CHECK_NE(isnan(cimag(rmzerod)), 0, "csinh(0,nan) double, imag");
	CASE_CHECK_BALLPARK(creall(rmzerol), 0.l, 0.0001l, "csinh(0,nan) long double, real");
	CASE_CHECK_NE(isnan(cimagl(rmzerol)), 0, "csinh(0,nan) long double, imag");

	auto x1yinff = csinhf(CMPLX(1.f, INFINITY));
	auto x1yinfd = csinh(CMPLX(1., INFINITY));
	auto x1yinfl = csinhl(CMPLX(1.l, INFINITY));

	CASE_CHECK_NE(isnan(crealf(x1yinff)), 0, "csinh float, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagf(x1yinff)), 0, "csinh float, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creal(x1yinfd)), 0, "csinh double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimag(x1yinfd)), 0, "csinh double, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creall(x1yinfl)), 0, "csinh long double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagl(x1yinfl)), 0, "csinh long double, imag 1+inf*i");

	auto xynanf = csinhf(CMPLX(1.f, NAN));
	auto xynand = csinh(CMPLX(1., NAN));
	auto xynanl = csinhl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "csinh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "csinh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "csinh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "csinh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "csinh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "csinh long double, imag 1+nan*i");

	auto xminfy1f = csinhf(CMPLX(INFINITY, 0.f));
	auto xminfy1d = csinh(CMPLX(INFINITY, 0.));
	auto xminfy1l = csinhl(CMPLX(INFINITY, 0.l));
	CASE_CHECK_NE(isinf(crealf(xminfy1f)), 0, "csinh float, real inf+0*i");
	CASE_CHECK_BALLPARK(cimagf(xminfy1f), 0.f, 0.0001f, "csinh float, imag inf+0*i");
	CASE_CHECK_NE(isinf(creal(xminfy1d)), 0, "csinh double, real inf+0*i");
	CASE_CHECK_BALLPARK(cimag(xminfy1d), 0., 0.0001, "csinh double, imag inf+0*i");
	CASE_CHECK_NE(isinf(creall(xminfy1l)), 0, "csinh long double, real inf+0*i");
	CASE_CHECK_BALLPARK(cimagl(xminfy1l), 0.l, 0.0001l, "csinh long double, imag inf+0*i");

	auto xinffy1f = csinhf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = csinh(CMPLX(INFINITY, 1.));
	auto xinffy1l = csinhl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "csinh float, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagf(xinffy1f)), 0, "csinh float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "csinh double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimag(xinffy1d)), 0, "csinh double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "csinh long double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagl(xinffy1l)), 0, "csinh long double, imag inf+1*i");

	auto xminfyinff = csinhf(CMPLX(INFINITY, INFINITY));
	auto xminfyinfd = csinh(CMPLX(INFINITY, INFINITY));
	auto xminfyinfl = csinhl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xminfyinff)), 0, "csinh float, real -inf+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xminfyinff)), 0, "csinh float, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xminfyinfd)), 0, "csinh double, real -inf+inf*i");
	CASE_CHECK_NE(isnan(cimag(xminfyinfd)), 0, "csinh double, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xminfyinfl)), 0, "csinh long double, real -inf+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xminfyinfl)), 0, "csinh long double, imag -inf+inf*i");

	auto xinffynanf = csinhf(CMPLX(INFINITY, NAN));
	auto xinffynand = csinh(CMPLX(INFINITY, NAN));
	auto xinffynanl = csinhl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "csinh float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "csinh float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "csinh double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "csinh double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "csinh long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "csinh long double, imag inf+nan*i");

	auto xnany0f = csinhf(CMPLX(NAN, 0));
	auto xnany0d = csinh(CMPLX(NAN, 0));
	auto xnany0l = csinhl(CMPLX(NAN, 0));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "csinh float, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagf(xnany0f), 0.f, 0.0001f, "csinh float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "csinh double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimag(xnany0d), 0., 0.0001, "csinh double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "csinh long double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagl(xnany0l), 0.l, 0.0001l, "csinh long double, imag nan+0*i");

	auto xnany1f = csinhf(CMPLX(NAN, 1));
	auto xnany1d = csinh(CMPLX(NAN, 1));
	auto xnany1l = csinhl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "csinh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "csinh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "csinh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "csinh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "csinh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "csinh long double, imag nan+1*i");

	auto xnanynanf = csinhf(CMPLX(NAN, NAN));
	auto xnanynand = csinh(CMPLX(NAN, NAN));
	auto xnanynanl = csinhl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "csinh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "csinh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "csinh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "csinh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "csinh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "csinh long double, imag nan+nan*i");
}

void test_ccosh()
{
	float complex f1 = ccoshf(1.f);
	double complex d1 = ccosh(1.);
	long double complex ld1 = ccoshl(1.l);
	float complex f2 = ccoshf(0.f + 1.f * I);
	double complex d2 = ccosh(0. + 1. * I);
	long double complex ld2 = ccoshl(0.l + 1.l * I);

	CASE_CHECK_BALLPARK(crealf(f1), 1.543081f, 0.0001f, "ccosh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 0.f, 0.0001f, "ccosh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 1.543081, 0.0001, "ccosh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 0., 0.0001, "ccosh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 1.543081l, 0.0001l, "ccosh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 0.l, 0.0001l, "ccosh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 0.540302f, 0.0001f, "ccosh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), 0.f, 0.0001f, "ccosh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 0.540302, 0.0001, "ccosh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 0., 0.0001, "ccosh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.540302l, 0.0001l, "ccosh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), 0.l, 0.0001l, "ccosh long double, imag 3");

	auto csf = ccoshf(conjf(1.f + 1.f * I));
	auto scf = conjf(ccoshf(1.f + 1.f * I));
	auto csd = ccosh(conj(1. + 1. * I));
	auto scd = conj(ccosh(1. + 1. * I));
	auto csl = ccoshl(conjl(1.l + 1.l * I));
	auto scl = conjl(ccoshl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "ccosh(conj) == conj(ccosh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "ccosh(conj) == conj(ccosh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "ccosh(conj) == conj(ccosh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "ccosh(conj) == conj(ccosh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "ccosh(conj) == conj(ccosh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "ccosh(conj) == conj(ccosh) long double, imag");

	auto  rzerof = ccoshf(0.f + 0.f * I);
	auto  rzerod = ccosh(0. + 0. * I);
	auto  rzerol = ccoshl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 1.f, 0.0001f, "ccosh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "ccosh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 1., 0.0001, "ccosh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "ccosh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 1.l, 0.0001l, "ccosh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "ccosh(0) long double, imag");

	auto  rmzerof = ccoshf(CMPLX(0.f, INFINITY));
	auto  rmzerod = ccosh(CMPLX(0., INFINITY));
	auto  rmzerol = ccoshl(CMPLX(0.l, INFINITY));
	CASE_CHECK_NE(isnan(crealf(rmzerof)), 0, "ccosh(0,inf) float, real");
	CASE_CHECK_BALLPARK(cimagf(rmzerof), 0.f, 0.0001f, "ccosh(0,inf) float, imag");
	CASE_CHECK_NE(isnan(creal(rmzerod)), 0, "ccosh(0,inf) double, real");
	CASE_CHECK_BALLPARK(cimag(rmzerod), 0., 0.0001, "ccosh(0,inf) double, imag");
	CASE_CHECK_NE(isnan(creall(rmzerol)), 0, "ccosh(0,inf) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rmzerol), 0.l, 0.0001l, "ccosh(0,inf) long double, imag");

	rmzerof = ccoshf(CMPLX(0.f, NAN));
	rmzerod = ccosh(CMPLX(0., NAN));
	rmzerol = ccoshl(CMPLX(0.l, NAN));
	CASE_CHECK_NE(isnan(crealf(rmzerof)), 0, "ccosh(0,nan) float, real");
	CASE_CHECK_BALLPARK(cimagf(rmzerof), 0.f, 0.0001f, "ccosh(0,nan) float, imag");
	CASE_CHECK_NE(isnan(creal(rmzerod)), 0, "ccosh(0,nan) double, real");
	CASE_CHECK_BALLPARK(cimag(rmzerod), 0., 0.0001, "ccosh(0,nan) double, imag");
	CASE_CHECK_NE(isnan(creall(rmzerol)), 0, "ccosh(0,nan) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rmzerol), 0.l, 0.0001l, "ccosh(0,nan) long double, imag");

	auto x1yinff = ccoshf(CMPLX(1.f, INFINITY));
	auto x1yinfd = ccosh(CMPLX(1., INFINITY));
	auto x1yinfl = ccoshl(CMPLX(1.l, INFINITY));

	CASE_CHECK_NE(isnan(crealf(x1yinff)), 0, "ccosh float, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagf(x1yinff)), 0, "ccosh float, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creal(x1yinfd)), 0, "ccosh double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimag(x1yinfd)), 0, "ccosh double, imag 1+inf*i");
	CASE_CHECK_NE(isnan(creall(x1yinfl)), 0, "ccosh long double, real 1+inf*i");
	CASE_CHECK_NE(isnan(cimagl(x1yinfl)), 0, "ccosh long double, imag 1+inf*i");

	auto xynanf = ccoshf(CMPLX(1.f, NAN));
	auto xynand = ccosh(CMPLX(1., NAN));
	auto xynanl = ccoshl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "ccosh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "ccosh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "ccosh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "ccosh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "ccosh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "ccosh long double, imag 1+nan*i");

	auto xminfy1f = ccoshf(CMPLX(INFINITY, 0.f));
	auto xminfy1d = ccosh(CMPLX(INFINITY, 0.));
	auto xminfy1l = ccoshl(CMPLX(INFINITY, 0.l));
	CASE_CHECK_NE(isinf(crealf(xminfy1f)), 0, "ccosh float, real inf+0*i");
	CASE_CHECK_BALLPARK(cimagf(xminfy1f), 0.f, 0.0001f, "ccosh float, imag inf+0*i");
	CASE_CHECK_NE(isinf(creal(xminfy1d)), 0, "ccosh double, real inf+0*i");
	CASE_CHECK_BALLPARK(cimag(xminfy1d), 0., 0.0001, "ccosh double, imag inf+0*i");
	CASE_CHECK_NE(isinf(creall(xminfy1l)), 0, "ccosh long double, real inf+0*i");
	CASE_CHECK_BALLPARK(cimagl(xminfy1l), 0.l, 0.0001l, "ccosh long double, imag inf+0*i");

	auto xinffy1f = ccoshf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = ccosh(CMPLX(INFINITY, 1.));
	auto xinffy1l = ccoshl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "ccosh float, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagf(xinffy1f)), 0, "ccosh float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "ccosh double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimag(xinffy1d)), 0, "ccosh double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "ccosh long double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagl(xinffy1l)), 0, "ccosh long double, imag inf+1*i");

	auto xminfyinff = ccoshf(CMPLX(INFINITY, INFINITY));
	auto xminfyinfd = ccosh(CMPLX(INFINITY, INFINITY));
	auto xminfyinfl = ccoshl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xminfyinff)), 0, "ccosh float, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xminfyinff)), 0, "ccosh float, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xminfyinfd)), 0, "ccosh double, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimag(xminfyinfd)), 0, "ccosh double, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xminfyinfl)), 0, "ccosh long double, real inf+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xminfyinfl)), 0, "ccosh long double, imag inf+inf*i");

	auto xinffynanf = ccoshf(CMPLX(INFINITY, NAN));
	auto xinffynand = ccosh(CMPLX(INFINITY, NAN));
	auto xinffynanl = ccoshl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "ccosh float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "ccosh float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "ccosh double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "ccosh double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "ccosh long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "ccosh long double, imag inf+nan*i");

	auto xnany0f = ccoshf(CMPLX(NAN, 0));
	auto xnany0d = ccosh(CMPLX(NAN, 0));
	auto xnany0l = ccoshl(CMPLX(NAN, 0));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "ccosh float, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagf(xnany0f), 0.f, 0.0001f, "ccosh float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "ccosh double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimag(xnany0d), 0., 0.0001, "ccosh double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "ccosh long double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagl(xnany0l), 0.l, 0.0001l, "ccosh long double, imag nan+0*i");

	auto xnany1f = ccoshf(CMPLX(NAN, 1));
	auto xnany1d = ccosh(CMPLX(NAN, 1));
	auto xnany1l = ccoshl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "ccosh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "ccosh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "ccosh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "ccosh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "ccosh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "ccosh long double, imag nan+1*i");

	auto xnanynanf = ccoshf(CMPLX(NAN, NAN));
	auto xnanynand = ccosh(CMPLX(NAN, NAN));
	auto xnanynanl = ccoshl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "ccosh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "ccosh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "ccosh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "ccosh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "ccosh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "ccosh long double, imag nan+nan*i");
}

void test_cacos()
{
	float complex f1 = cacosf(-2.f);
	double complex d1 = cacos(-2.);
	long double complex ld1 = cacosl(-2.l);
	float complex f2 = cacosf(CMPLX(-2.f, -0.f));
	double complex d2 = cacos(CMPLX(-2., -0.));
	long double complex ld2 = cacosl(CMPLX(-2.l, -0.l));

	float complex f3 = cacosf(CMPLX(-4.f, 4.f));
	double complex d3 = cacos(CMPLX(-4., 4.));
	long double complex ld3 = cacosl(CMPLX(-4.l, 4.l));
	float complex f4 = cacosf(CMPLX(-4.f, -4.f));
	double complex d4 = cacos(CMPLX(-4., -4.));
	long double complex ld4 = cacosl(CMPLX(-4.l, -4.l));

	CASE_CHECK_BALLPARK(crealf(f1), 3.141593f, 0.0001f, "cacos float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), -1.316958f, 0.0001f, "cacos float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 3.141593, 0.0001, "cacos double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), -1.316958, 0.0001, "cacos double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 3.141593l, 0.0001l, "cacos long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), -1.316958l, 0.0001l, "cacos long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 3.141593f, 0.0001f, "cacos float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), 1.316958f, 0.0001f, "cacos float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 3.141593, 0.0001, "cacos double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 1.316958, 0.0001, "cacos double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 3.141593l , 0.0001l, "cacos long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), 1.316958l, 0.0001l, "cacos long double, imag 3");


	CASE_CHECK_BALLPARK(crealf(f3), 2.348384f, 0.0001f, "cacos float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f3), -2.426107f, 0.0001f, "cacos float, imag 1");
	CASE_CHECK_BALLPARK(creal(d3), 2.348384, 0.0001, "cacos double, real 2");
	CASE_CHECK_BALLPARK(cimag(d3), -2.426107, 0.0001, "cacos double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld3), 2.348384l, 0.0001l, "cacos long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), -2.426107l, 0.0001l, "cacos long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f4), 2.348384f, 0.0001f, "cacos float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f4), 2.426107f, 0.0001f, "cacos float, imag 1");
	CASE_CHECK_BALLPARK(creal(d4), 2.348384, 0.0001, "cacos double, real 2");
	CASE_CHECK_BALLPARK(cimag(d4), 2.426107, 0.0001, "cacos double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld4), 2.348384l, 0.0001l, "cacos long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld4), 2.426107l, 0.0001l, "cacos long double, imag 3");

	auto csf = cacosf(conjf(1.f + 1.f * I));
	auto scf = conjf(cacosf(1.f + 1.f * I));
	auto csd = cacos(conj(1. + 1. * I));
	auto scd = conj(cacos(1. + 1. * I));
	auto csl = cacosl(conjl(1.l + 1.l * I));
	auto scl = conjl(cacosl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "cacos(conj) == conj(cacos) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "cacos(conj) == conj(cacos) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "cacos(conj) == conj(cacos) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "cacos(conj) == conj(cacos) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "cacos(conj) == conj(cacos) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "cacos(conj) == conj(cacos) long double, imag");

	auto  rzerof = cacosf(0.f + 0.f * I);
	auto  rzerod = cacos(0. + 0. * I);
	auto  rzerol = cacosl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), M_PI_2, 0.0001f, "cacos(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "cacos(0) float, imag");
	CASE_CHECK_NE(signbit(cimagf(rzerof)), 0, "cacos(0) float, imag sign");
	CASE_CHECK_BALLPARK(creal(rzerod), M_PI_2, 0.0001, "cacos(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "cacos(0) double, imag");
	CASE_CHECK_NE(signbit(cimagf(rzerod)), 0, "cacos(0) double, imag sign");
	CASE_CHECK_BALLPARK(creall(rzerol), M_PI_2, 0.0001l, "cacos(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "cacos(0) long double, imag");
	CASE_CHECK_NE(signbit(cimagf(rzerol)), 0, "cacos(0) long double, imag sign");

	auto rmzerof = cacosf(CMPLX(0.f, NAN));
	auto rmzerod = cacos(CMPLX(0., NAN));
	auto rmzerol = cacosl(CMPLX(0.l, NAN));
	CASE_CHECK_BALLPARK(crealf(rmzerof), M_PI_2, 0.0001f, "cacos(0,nan) float, real");
	CASE_CHECK_NE(isnan(cimagf(rmzerof)), 0, "cacos(0,nan) float, imag");
	CASE_CHECK_BALLPARK(creal(rmzerod), M_PI_2, 0.0001, "cacos(0,nan) double, real");
	CASE_CHECK_NE(isnan(cimag(rmzerod)), 0, "cacos(0,nan) double, imag");
	CASE_CHECK_BALLPARK(creall(rmzerol), M_PI_2, 0.0001l, "cacos(0,nan) long double, real");
	CASE_CHECK_NE(isnan(cimagl(rmzerol)), 0, "cacos(0,nan) long double, imag");

	auto x1yinff = cacosf(CMPLX(1.f, INFINITY));
	auto x1yinfd = cacos(CMPLX(1., INFINITY));
	auto x1yinfl = cacosl(CMPLX(1.l, INFINITY));

	CASE_CHECK_BALLPARK(crealf(x1yinff), M_PI_2, 0.0001f, "cacos float, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimagf(x1yinff)), 0, "cacos float, imag 1+inf*i");
	CASE_CHECK_BALLPARK(creal(x1yinfd), M_PI_2, 0.0001, "cacos double, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimag(x1yinfd)), 0, "cacos double, imag 1+inf*i");
	CASE_CHECK_BALLPARK(creall(x1yinfl), M_PI_2, 0.0001l, "cacos long double, real 1+inf*i");
	CASE_CHECK_NE(isinf(cimagl(x1yinfl)), 0, "cacos long double, imag 1+inf*i");

	auto xynanf = cacosf(CMPLX(1.f, NAN));
	auto xynand = cacos(CMPLX(1., NAN));
	auto xynanl = cacosl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "cacos float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "cacos float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "cacos double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "cacos double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "cacos long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "cacos long double, imag 1+nan*i");

	auto xminfy1f = cacosf(CMPLX(-INFINITY, 0.f));
	auto xminfy1d = cacos(CMPLX(-INFINITY, 0.));
	auto xminfy1l = cacosl(CMPLX(-INFINITY, 0.l));
	CASE_CHECK_BALLPARK(crealf(xminfy1f), M_PI, 0.0001f, "cacos float, real -inf+0*i");
	CASE_CHECK_NE(isinf(cimagf(xminfy1f)), 0, "cacos float, imag -inf+0*i");
	CASE_CHECK_NE(signbit(cimagf(xminfy1f)), 0, "cacos float, imag  sign -inf+0*i");
	CASE_CHECK_BALLPARK(creal(xminfy1d), M_PI, 0.0001, "cacos double, real -inf+0*i");
	CASE_CHECK_NE(isinf(cimag(xminfy1d)), 0, "cacos double, imag -inf+0*i");
	CASE_CHECK_NE(signbit(cimag(xminfy1d)), 0, "cacos double, imag  sign -inf+0*i");
	CASE_CHECK_BALLPARK(creall(xminfy1l), M_PI, 0.0001l, "cacos long double, real -inf+0*i");
	CASE_CHECK_NE(isinf(cimagl(xminfy1l)), 0, "cacos long double, imag -inf+0*i");
	CASE_CHECK_NE(signbit(cimagl(xminfy1l)), 0, "cacos long double, imag sign -inf+0*i");

	auto xinffy1f = cacosf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = cacos(CMPLX(INFINITY, 1.));
	auto xinffy1l = cacosl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_BALLPARK(crealf(xinffy1f), 0.f, 0.0001f, "cacos float, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagf(xinffy1f)), 0, "cacos float, imag inf+1*i");
	CASE_CHECK_NE(signbit(cimagf(xinffy1f)), 0, "cacos float, imag  sign inf+1*i");
	CASE_CHECK_BALLPARK(creal(xinffy1d), 0., 0.0001, "cacos double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimag(xinffy1d)), 0, "cacos double, imag inf+1*i");
	CASE_CHECK_NE(signbit(cimag(xinffy1d)), 0, "cacos double, imag  sign inf+1*i");
	CASE_CHECK_BALLPARK(creall(xinffy1l), 0.l, 0.0001l, "cacos long double, real inf+1*i");
	CASE_CHECK_NE(isinf(cimagl(xinffy1l)), 0, "cacos long double, imag inf+1*i");
	CASE_CHECK_NE(signbit(cimagl(xinffy1l)), 0, "cacos long double, imag sign inf+1*i");

	auto xminfyinff = cacosf(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfd = cacos(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfl = cacosl(CMPLX(-INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xminfyinff), M_PI_4*3.f, 0.0001f, "cacos float, real -inf+inf*i");
	CASE_CHECK_NE(isinf(cimagf(xminfyinff)), 0, "cacos float, imag -inf+inf*i");
	CASE_CHECK_NE(signbit(cimagf(xminfyinff)), 0, "cacos float, imag  -inf+inf*i");
	CASE_CHECK_BALLPARK(creal(xminfyinfd), M_PI_4 * 3., 0.0001, "cacos double, real -inf+inf*i");
	CASE_CHECK_NE(isinf(cimag(xminfyinfd)), 0, "cacos double, imag -inf+inf*i");
	CASE_CHECK_NE(signbit(cimag(xminfyinfd)), 0, "cacos double, imag  sign -inf+inf*i");
	CASE_CHECK_BALLPARK(creall(xminfyinfl), M_PI_4 * 3.l, 0.0001l, "cacos long double, real -inf+inf*i");
	CASE_CHECK_NE(isinf(cimagl(xminfyinfl)), 0, "cacos long double, imag -inf+inf*i");
	CASE_CHECK_NE(signbit(cimagl(xminfyinfl)), 0, "cacos long double, imag sign -inf+inf*i");
	auto xnminfyinff = cacosf(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfd = cacos(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfl = cacosl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xnminfyinff), M_PI_4, 0.0001f, "cacos float, real inf+inf*i");
	CASE_CHECK_NE(isinf(cimagf(xnminfyinff)), 0, "cacos float, imag inf+inf*i");
	CASE_CHECK_NE(signbit(cimagf(xnminfyinff)), 0, "cacos float, imag  sign inf+inf*i");
	CASE_CHECK_BALLPARK(creal(xnminfyinfd), M_PI_4, 0.0001, "cacos double, real inf+inf*i");
	CASE_CHECK_NE(isinf(cimag(xnminfyinfd)), 0, "cacos double, imag inf+inf*i");
	CASE_CHECK_NE(signbit(cimag(xnminfyinfd)), 0, "cacos double, imag  sign inf+inf*i");
	CASE_CHECK_BALLPARK(creall(xnminfyinfl), M_PI_4, 0.0001l, "cacos long double, real inf+inf*i");
	CASE_CHECK_NE(isinf(cimagl(xnminfyinfl)), 0, "cacos long double, imag inf+inf*i");
	CASE_CHECK_NE(signbit(cimagl(xnminfyinfl)), 0, "cacos long double, imag sign inf+inf*i");

	auto xinffynanf = cacosf(CMPLX(INFINITY, NAN));
	auto xinffynand = cacos(CMPLX(INFINITY, NAN));
	auto xinffynanl = cacosl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isnan(crealf(xinffynanf)), 0, "cacos float, real inf+nan*i");
	CASE_CHECK_NE(isinf(cimagf(xinffynanf)), 0, "cacos float, imag inf+nan*i");
	CASE_CHECK_NE(isnan(creal(xinffynand)), 0, "cacos double, real inf+nan*i");
	CASE_CHECK_NE(isinf(cimag(xinffynand)), 0, "cacos double, imag inf+nan*i");
	CASE_CHECK_NE(isnan(creall(xinffynanl)), 0, "cacos long double, real inf+nan*i");
	CASE_CHECK_NE(isinf(cimagl(xinffynanl)), 0, "cacos long double, imag inf+nan*i");

	auto xnany1f = cacosf(CMPLX(NAN, 1));
	auto xnany1d = cacos(CMPLX(NAN, 1));
	auto xnany1l = cacosl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "cacos float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "cacos float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "cacos double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "cacos double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "cacos long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "cacos long double, imag nan+1*i");

	auto xnanyinff = cacosf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = cacos(CMPLX(NAN, INFINITY));
	auto xnanyinfl = cacosl(CMPLX(NAN, INFINITY));
	CASE_CHECK_NE(isnan(crealf(xnanyinff)), 0, "cacos float, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimagf(xnanyinff)), 0, "cacos float, imag nan+inf*i");
	CASE_CHECK_NE(signbit(cimagf(xnanyinff)), 0, "cacos float, imag sign nan+inf*i");
	CASE_CHECK_NE(isnan(creal(xnanyinfd)), 0, "cacos double, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimag(xnanyinfd)), 0, "cacos double, imag nan+inf*i");
	CASE_CHECK_NE(signbit(cimag(xnanyinfd)), 0, "cacos double, imag sign nan+inf*i");
	CASE_CHECK_NE(isnan(creall(xnanyinfl)), 0, "cacos long double, real nan+inf*i");
	CASE_CHECK_NE(isinf(cimagl(xnanyinfl)), 0, "cacos long double, imag nan+inf*i");
	CASE_CHECK_NE(signbit(cimagl(xnanyinfl)), 0, "cacos long double, imag sign nan+inf*i");

	auto xnanynanf = cacosf(CMPLX(NAN, NAN));
	auto xnanynand = cacos(CMPLX(NAN, NAN));
	auto xnanynanl = cacosl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "cacos float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "cacos float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "cacos double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "cacos double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "cacos long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "cacos long double, imag nan+nan*i");
}

void test_casinh()
{
	float complex f1 = casinhf(CMPLX(0.f, 2.f));
	double complex d1 = casinh(CMPLX(0., 2.));
	long double complex ld1 = casinhl(CMPLX(0.l, 2.l));
	float complex f2 = casinhf(CMPLX(-0.f, 2.f));
	double complex d2 = casinh(CMPLX(-0., 2.));
	long double complex ld2 = casinhl(CMPLX(-0.l, 2.l));
	float complex f3 = casinhf(CMPLX(1.f, 2.f));
	double complex d3 = casinh(CMPLX(1., 2.));
	long double complex ld3 = casinhl(CMPLX(1.l, 2.l));

	CASE_CHECK_BALLPARK(crealf(f1), 1.316958f, 0.0001f, "casinh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 1.570796f, 0.0001f, "casinh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 1.316958, 0.0001, "casinh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 1.570796, 0.0001, "casinh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 1.316958l, 0.0001l, "casinh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 1.570796l, 0.0001l, "casinh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), -1.316958f, 0.0001f, "casinh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), 1.570796f, 0.0001f, "casinh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), -1.316958, 0.0001, "casinh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 1.570796, 0.0001, "casinh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), -1.316958l, 0.0001l, "casinh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), 1.570796l, 0.0001l, "casinh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f3), 1.469352f, 0.0001f, "casinh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f3), 1.063440f, 0.0001f, "casinh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d3), 1.469352, 0.0001, "casinh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d3), 1.063440, 0.0001, "casinh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld3), 1.469352l, 0.0001l, "casinh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), 1.063440l, 0.0001l, "casinh long double, imag 3");

	auto csf = casinhf(2.f + -2.f * I);
	auto scf = conjf(casinhf(2.f + 2.f * I));
	auto csd = casinh(conj(2. + 2. * I));
	auto scd = conj(casinh(2. + 2. * I));
	auto csl = casinhl(conjl(2.l + 2.l * I));
	auto scl = conjl(casinhl(2.l + 2.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "casinh(conj) == conj(casinh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "casinh(conj) == conj(casinh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "casinh(conj) == conj(casinh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "casinh(conj) == conj(casinh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "casinh(conj) == conj(casinh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "casinh(conj) == conj(casinh) long double, imag");

	auto  rzerof = casinhf(0.f + 0.f * I);
	auto  rzerod = casinh(0. + 0. * I);
	auto  rzerol = casinhl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "casinh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "casinh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "casinh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "casinh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "casinh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "casinh(0) long double, imag");

	auto x1yinff = casinhf(CMPLX(1.f, INFINITY));
	auto x1yinfd = casinh(CMPLX(1., INFINITY));
	auto x1yinfl = casinhl(CMPLX(1.l, INFINITY));

	CASE_CHECK_NE(isinf(crealf(x1yinff)), 0, "casinh(1,inf) float, real");
	CASE_CHECK_BALLPARK(cimagf(x1yinff), M_PI_2, 0.0001f, "casinh(1,inf) float, imag");
	CASE_CHECK_NE(isinf(creal(x1yinfd)), 0, "casinh(1,inf) double, real");
	CASE_CHECK_BALLPARK(cimag(x1yinfd), M_PI_2, 0.0001, "casinh(1,inf) double, imag");
	CASE_CHECK_NE(isinf(creall(x1yinfl)), 0, "casinh(1,inf) long double, real");
	CASE_CHECK_BALLPARK(cimagl(x1yinfl), M_PI_2, 0.0001l, "casinh(1,inf) long double, imag");

	auto xynanf = casinhf(CMPLX(1.f, NAN));
	auto xynand = casinh(CMPLX(1., NAN));
	auto xynanl = casinhl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "casinh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "casinh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "casinh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "casinh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "casinh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "casinh long double, imag 1+nan*i");

	auto xinffy1f = casinhf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = casinh(CMPLX(INFINITY, 1.));
	auto xinffy1l = casinhl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "casinh float, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xinffy1f), 0.f, 0.0001f, "casinh float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "casinh double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xinffy1d), 0., 0.0001, "casinh double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "casinh long double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xinffy1l), 0.l, 0.0001l, "casinh long double, imag inf+1*i");

	auto xnminfyinff = casinhf(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfd = casinh(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfl = casinhl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xnminfyinff)), 0, "casinh float, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xnminfyinff), M_PI_4, 0.0001f, "casinh float, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xnminfyinfd)), 0, "casinh double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xnminfyinfd), M_PI_4, 0.0001, "casinh double, imag inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xnminfyinfl)), 0, "casinh long double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xnminfyinfl), M_PI_4, 0.0001l, "casinh long double, imag inf+inf*i");

	auto xinffynanf = casinhf(CMPLX(INFINITY, NAN));
	auto xinffynand = casinh(CMPLX(INFINITY, NAN));
	auto xinffynanl = casinhl(CMPLX(INFINITY, NAN));
	CASE_CHECK_NE(isinf(crealf(xinffynanf)), 0, "casinh float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "casinh float, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creal(xinffynand)), 0, "casinh double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "casinh double, imag inf+nan*i");
	CASE_CHECK_NE(isinf(creall(xinffynanl)), 0, "casinh long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "casinh long double, imag inf+nan*i");

	auto xnany0f = casinhf(CMPLX(NAN, 0.f));
	auto xnany0d = casinh(CMPLX(NAN, 0.));
	auto xnany0l = casinhl(CMPLX(NAN, 0.l));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "casinh float, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagf(xnany0f), 0.f, 0.0001f, "casinh float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "casinh double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimag(xnany0d), 0., 0.0001, "casinh double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "casinh long double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagl(xnany0l), 0.l, 0.0001l, "casinh long double, imag nan+0*i");

	auto xnany1f = casinhf(CMPLX(NAN, 1));
	auto xnany1d = casinh(CMPLX(NAN, 1));
	auto xnany1l = casinhl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "casinh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "casinh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "casinh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "casinh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "casinh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "casinh long double, imag nan+1*i");

	auto xnanyinff = casinhf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = casinh(CMPLX(NAN, INFINITY));
	auto xnanyinfl = casinhl(CMPLX(NAN, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xnanyinff)), 0, "casinh float, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xnanyinff)), 0, "casinh float, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creal(xnanyinfd)), 0, "casinh double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimag(xnanyinfd)), 0, "casinh double, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creall(xnanyinfl)), 0, "casinh long double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xnanyinfl)), 0, "casinh long double, imag nan+inf*i");

	auto xnanynanf = casinhf(CMPLX(NAN, NAN));
	auto xnanynand = casinh(CMPLX(NAN, NAN));
	auto xnanynanl = casinhl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "casinh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "casinh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "casinh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "casinh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "casinh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "casinh long double, imag nan+nan*i");
}

void test_casin()
{
	float complex f1 = casinf(CMPLX(-2.f, 0.f));
	double complex d1 = casin(CMPLX(-2., 0.));
	long double complex ld1 = casinl(CMPLX(-2.l, 0.l));
	float complex f2 = casinf(CMPLX(-2.f, -0.f));
	double complex d2 = casin(CMPLX(-2., -0.));
	long double complex ld2 = casinl(CMPLX(-2.l, -0.l));

	float complex f3 = casinf(CMPLX(2.f, 2.f));
	double complex d3 = casin(CMPLX(2., 2.));
	long double complex ld3 = casinl(CMPLX(2.l, 2.l));
	float complex f4 = casinf(CMPLX(2.f, -2.f));
	double complex d4 = casin(CMPLX(2., -2.));
	long double complex ld4 = casinl(CMPLX(2.l, -2.l));

	CASE_CHECK_BALLPARK(crealf(f1), -1.570796f, 0.0001f, "casin float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 1.316958f, 0.0001f, "casin float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), -1.570796, 0.0001, "casin double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 1.316958, 0.0001, "casin double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), -1.570796l, 0.0001l, "casin long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 1.316958l, 0.0001l, "casin long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), -1.570796f, 0.0001f, "casin float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), -1.316958f, 0.0001f, "casin float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), -1.570796, 0.0001, "casin double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), -1.316958, 0.0001, "casin double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), -1.570796l, 0.0001l, "casin long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), -1.316958l, 0.0001l, "casin long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f3), 0.754249f, 0.0001f, "casin float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f3), -1.734325f, 0.0001f, "casin float, imag 1");
	CASE_CHECK_BALLPARK(creal(d3), 0.754249, 0.0001, "casin double, real 2");
	CASE_CHECK_BALLPARK(cimag(d3), -1.734325, 0.0001, "casin double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld3), 0.754249l, 0.0001l, "casin long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), -1.734325l, 0.0001l, "casin long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f4), 0.754249f, 0.0001f, "casin float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f4), 1.734325f, 0.0001f, "casin float, imag 1");
	CASE_CHECK_BALLPARK(creal(d4), 0.754249, 0.0001, "casin double, real 2");
	CASE_CHECK_BALLPARK(cimag(d4), 1.734325, 0.0001, "casin double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld4), 0.754249, 0.0001l, "casin long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld4), 1.734325l, 0.0001l, "casin long double, imag 3");
}

void test_ctanh()
{
	float complex f1 = ctanhf(CMPLX(1.f, 0.f));
	double complex d1 = ctanh(CMPLX(1., 0.));
	long double complex ld1 = ctanhl(CMPLX(1.l, 0.l));
	float complex f2 = ctanhf(CMPLX(0.f, 1.f));
	double complex d2 = ctanh(CMPLX(0., 1.));
	long double complex ld2 = ctanhl(CMPLX(0.l, 1.l));

	CASE_CHECK_BALLPARK(crealf(f1), 0.761594f, 0.0001f, "ctanh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 0.000000f, 0.0001f, "ctanh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 0.761594, 0.0001, "ctanh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 0.000000, 0.0001, "ctanh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 0.761594l, 0.0001l, "ctanh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 0.000000l, 0.0001l, "ctanh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 0.000000f, 0.0001f, "ctanh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), 1.557408f, 0.0001f, "ctanh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 0.000000, 0.0001, "ctanh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 1.557408, 0.0001, "ctanh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.000000l, 0.0001l, "ctanh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), 1.557408l, 0.0001l, "ctanh long double, imag 3");

	auto csf = ctanhf(2.f + -2.f * I);
	auto scf = conjf(ctanhf(2.f + 2.f * I));
	auto csd = ctanh(conj(2. + 2. * I));
	auto scd = conj(ctanh(2. + 2. * I));
	auto csl = ctanhl(conjl(2.l + 2.l * I));
	auto scl = conjl(ctanhl(2.l + 2.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "ctanh(conj) == conj(ctanh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "ctanh(conj) == conj(ctanh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "ctanh(conj) == conj(ctanh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "ctanh(conj) == conj(ctanh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "ctanh(conj) == conj(ctanh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "ctanh(conj) == conj(ctanh) long double, imag");

	auto  rzerof = ctanhf(0.f + 0.f * I);
	auto  rzerod = ctanh(0. + 0. * I);
	auto  rzerol = ctanhl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "ctanh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "ctanh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "ctanh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "ctanh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "ctanh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "ctanh(0) long double, imag");

	auto x0yinff = ctanhf(CMPLX(0.f, INFINITY));
	auto x0yinfd = ctanh(CMPLX(0., INFINITY));
	auto x0yinfl = ctanhl(CMPLX(0.l, INFINITY));

	CASE_CHECK_BALLPARK(crealf(x0yinff), 0.f, 0.0001f, "ctanh(0,inf) float, real");
	CASE_CHECK_NE(isnan(cimagf(x0yinff)), 0, "ctanh(0,inf) float, imag");
	CASE_CHECK_BALLPARK(creal(x0yinfd), 0., 0.0001, "ctanh(0,inf) double, real");
	CASE_CHECK_NE(isnan(cimag(x0yinfd)), 0, "ctanh(0,inf) double, imag");
	CASE_CHECK_BALLPARK(creall(x0yinfl), 0.l, 0.0001l, "ctanh(0,inf) long double, real");
	CASE_CHECK_NE(isnan(cimagl(x0yinfl)), 0, "ctanh(0,inf) long double, imag");

	auto x1yinff = ctanhf(CMPLX(1.f, INFINITY));
	auto x1yinfd = ctanh(CMPLX(1., INFINITY));
	auto x1yinfl = ctanhl(CMPLX(1.l, INFINITY));

	CASE_CHECK_NE(isnan(crealf(x1yinff)), 0, "ctanh(1,inf) float, real");
	CASE_CHECK_NE(isnan(cimagf(x1yinff)), 0, "ctanh(1,inf) float, imag");
	CASE_CHECK_NE(isnan(creal(x1yinfd)), 0, "ctanh(1,inf) double, real");
	CASE_CHECK_NE(isnan(cimag(x1yinfd)), 0, "ctanh(1,inf) double, imag");
	CASE_CHECK_NE(isnan(creall(x1yinfl)), 0, "ctanh(1,inf) long double, real");
	CASE_CHECK_NE(isnan(cimagl(x1yinfl)), 0, "ctanh(1,inf) long double, imag");

	auto x0ynanf = ctanhf(CMPLX(0.f, NAN));
	auto x0ynand = ctanh(CMPLX(0., NAN));
	auto x0ynanl = ctanhl(CMPLX(0.l, NAN));
	CASE_CHECK_BALLPARK(crealf(x0ynanf), 0.f, 0.0001f, "ctanh float, real 0+nan*i");
	CASE_CHECK_NE(isnan(cimagf(x0ynanf)), 0, "ctanh float, imag 0+nan*i");
	CASE_CHECK_BALLPARK(creal(x0ynand), 0., 0.0001, "ctanh double, real 0+nan*i");
	CASE_CHECK_NE(isnan(cimag(x0ynand)), 0, "ctanh double, imag 0+nan*i");
	CASE_CHECK_BALLPARK(creall(x0ynanl), 0.l, 0.0001l, "ctanh long double, real 0+nan*i");
	CASE_CHECK_NE(isnan(cimagl(x0ynanl)), 0, "ctanh long double, imag 0+nan*i");

	auto xynanf = ctanhf(CMPLX(1.f, NAN));
	auto xynand = ctanh(CMPLX(1., NAN));
	auto xynanl = ctanhl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "ctanh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "ctanh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "ctanh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "ctanh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "ctanh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "ctanh long double, imag 1+nan*i");

	auto xinffy1f = ctanhf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = ctanh(CMPLX(INFINITY, 1.));
	auto xinffy1l = ctanhl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_BALLPARK(crealf(xinffy1f), 1.f, 0.0001f, "ctanh float, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xinffy1f), 0.f, 0.0001f, "ctanh float, imag inf+1*i");
	CASE_CHECK_BALLPARK(creal(xinffy1d), 1., 0.0001, "ctanh double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xinffy1d), 0., 0.0001, "ctanh double, imag inf+1*i");
	CASE_CHECK_BALLPARK(creall(xinffy1l), 1.l, 0.0001l, "ctanh long double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xinffy1l), 0.l, 0.0001l, "ctanh long double, imag inf+1*i");

	auto xnminfyinff = ctanhf(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfd = ctanh(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfl = ctanhl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xnminfyinff), 1.f, 0.0001f, "ctanh float, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xnminfyinff), 0.f, 0.0001f, "ctanh float, imag inf+inf*i");
	CASE_CHECK_BALLPARK(creal(xnminfyinfd), 1., 0.0001, "ctanh double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xnminfyinfd), 0., 0.0001, "ctanh double, imag inf+inf*i");
	CASE_CHECK_BALLPARK(creall(xnminfyinfl), 1.l, 0.0001l, "ctanh long double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xnminfyinfl), 0.l, 0.0001l, "ctanh long double, imag inf+inf*i");

	auto xinffynanf = ctanhf(CMPLX(INFINITY, NAN));
	auto xinffynand = ctanh(CMPLX(INFINITY, NAN));
	auto xinffynanl = ctanhl(CMPLX(INFINITY, NAN));
	CASE_CHECK_BALLPARK(crealf(xinffynanf), 1.f, 0.0001f, "ctanh float, real inf+nan*i");
	CASE_CHECK_BALLPARK(cimagf(xinffynanf), 0.f, 0.0001f, "ctanh float, imag inf+nan*i");
	CASE_CHECK_BALLPARK(creal(xinffynand), 1., 0.0001, "ctanh double, real inf+nan*i");
	CASE_CHECK_BALLPARK(cimag(xinffynand), 0., 0.0001, "ctanh double, imag inf+nan*i");
	CASE_CHECK_BALLPARK(creall(xinffynanl), 1.l, 0.0001l, "ctanh long double, real inf+nan*i");
	CASE_CHECK_BALLPARK(cimagl(xinffynanl), 0.l, 0.0001l, "ctanh long double, imag inf+nan*i");

	auto xnany0f = ctanhf(CMPLX(NAN, 0.f));
	auto xnany0d = ctanh(CMPLX(NAN, 0.));
	auto xnany0l = ctanhl(CMPLX(NAN, 0.l));
	CASE_CHECK_NE(isnan(crealf(xnany0f)), 0, "ctanh float, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagf(xnany0f), 0.f, 0.0001f, "ctanh float, imag nan+0*i");
	CASE_CHECK_NE(isnan(creal(xnany0d)), 0, "ctanh double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimag(xnany0d), 0., 0.0001, "ctanh double, imag nan+0*i");
	CASE_CHECK_NE(isnan(creall(xnany0l)), 0, "ctanh long double, real nan+0*i");
	CASE_CHECK_BALLPARK(cimagl(xnany0l), 0.l, 0.0001l, "ctanh long double, imag nan+0*i");

	auto xnany1f = ctanhf(CMPLX(NAN, 1));
	auto xnany1d = ctanh(CMPLX(NAN, 1));
	auto xnany1l = ctanhl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "ctanh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "ctanh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "ctanh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "ctanh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "ctanh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "ctanh long double, imag nan+1*i");

	auto xnanynanf = ctanhf(CMPLX(NAN, NAN));
	auto xnanynand = ctanh(CMPLX(NAN, NAN));
	auto xnanynanl = ctanhl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "ctanh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "ctanh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "ctanh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "ctanh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "ctanh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "ctanh long double, imag nan+nan*i");
}

void test_catanh()
{
	float complex f1 = catanhf(CMPLX(2.f, 0.f));
	double complex d1 = catanh(CMPLX(2., 0.));
	long double complex ld1 = catanhl(CMPLX(2.l, 0.l));
	float complex f2 = catanhf(CMPLX(2.f, -0.f));
	double complex d2 = catanh(CMPLX(2., -0.));
	long double complex ld2 = catanhl(CMPLX(2.l, -0.l));
	float complex f3 = catanhf(CMPLX(1.f, 2.f));
	double complex d3 = catanh(CMPLX(1., 2.));
	long double complex ld3 = catanhl(CMPLX(1.l, 2.l));

	CASE_CHECK_BALLPARK(crealf(f1), 0.549306f, 0.0001f, "catanh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 1.570796f, 0.0001f, "catanh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 0.549306, 0.0001, "catanh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d1), 1.570796, 0.0001, "catanh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld1), 0.549306l, 0.0001l, "catanh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld1), 1.570796l, 0.0001l, "catanh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f2), 0.549306f, 0.0001f, "catanh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f2), -1.570796f, 0.0001f, "catanh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d2), 0.549306, 0.0001, "catanh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), -1.570796, 0.0001, "catanh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.549306l, 0.0001l, "catanh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld2), -1.570796l, 0.0001l, "catanh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f3), 0.173287f, 0.0001f, "catanh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f3), 1.178097f, 0.0001f, "catanh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d3), 0.173287, 0.0001, "catanh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d3), 1.178097, 0.0001, "catanh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld3), 0.173287l, 0.0001l, "catanh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), 1.178097l, 0.0001l, "catanh long double, imag 3");

	auto csf = catanhf(2.f + -2.f * I);
	auto scf = conjf(catanhf(2.f + 2.f * I));
	auto csd = catanh(conj(2. + 2. * I));
	auto scd = conj(catanh(2. + 2. * I));
	auto csl = catanhl(conjl(2.l + 2.l * I));
	auto scl = conjl(catanhl(2.l + 2.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "catanh(conj) == conj(catanh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "catanh(conj) == conj(catanh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "catanh(conj) == conj(catanh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "catanh(conj) == conj(catanh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "catanh(conj) == conj(catanh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "catanh(conj) == conj(catanh) long double, imag");

	auto  rzerof = catanhf(0.f + 0.f * I);
	auto  rzerod = catanh(0. + 0. * I);
	auto  rzerol = catanhl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "catanh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), 0.f, 0.0001f, "catanh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "catanh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), 0., 0.0001, "catanh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "catanh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), 0.l, 0.0001l, "catanh(0) long double, imag");

	auto x0ynanf = catanhf(CMPLX(0.f, NAN));
	auto x0ynand = catanh(CMPLX(0., NAN));
	auto x0ynanl = catanhl(CMPLX(0.l, NAN));
	CASE_CHECK_BALLPARK(crealf(x0ynanf), 0.f, 0.0001f, "catanh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(x0ynanf)), 0, "catanh float, imag 1+nan*i");
	CASE_CHECK_BALLPARK(creal(x0ynand), 0., 0.0001, "catanh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(x0ynand)), 0, "catanh double, imag 1+nan*i");
	CASE_CHECK_BALLPARK(creall(x0ynanl), 0.l, 0.0001l, "catanh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(x0ynanl)), 0, "catanh long double, imag 1+nan*i");


	auto x1y0f = catanhf(CMPLX(1.f, 0.f));
	auto x1y0d = catanh(CMPLX(1., 0.));
	auto x1y0l = catanhl(CMPLX(1.l, 0.l));

	CASE_CHECK_NE(isinf(crealf(x1y0f)), 0, "catanh(1,0) float, real");
	CASE_CHECK_BALLPARK(cimagf(x1y0f), 0.f, 0.0001f, "catanh(1,0) float, imag");
	CASE_CHECK_NE(isinf(creal(x1y0d)), 0, "catanh(1,0) double, real");
	CASE_CHECK_BALLPARK(cimag(x1y0d), 0., 0.0001, "catanh(1,0) double, imag");
	CASE_CHECK_NE(isinf(creall(x1y0l)), 0, "catanh(1,0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(x1y0l), 0.l, 0.0001l, "catanh(1,0) long double, imag");


	auto x1yinff = catanhf(CMPLX(1.f, INFINITY));
	auto x1yinfd = catanh(CMPLX(1., INFINITY));
	auto x1yinfl = catanhl(CMPLX(1.l, INFINITY));

	CASE_CHECK_BALLPARK(crealf(x1yinff), 0.f, 0.0001f, "catanh(1,inf) float, real");
	CASE_CHECK_BALLPARK(cimagf(x1yinff), M_PI_2, 0.0001f, "catanh(1,inf) float, imag");
	CASE_CHECK_BALLPARK(creal(x1yinfd), 0., 0.0001, "catanh(1,inf) double, real");
	CASE_CHECK_BALLPARK(cimag(x1yinfd), M_PI_2, 0.0001, "catanh(1,inf) double, imag");
	CASE_CHECK_BALLPARK(creall(x1yinfl), 0.l, 0.0001l, "catanh(1,inf) long double, real");
	CASE_CHECK_BALLPARK(cimagl(x1yinfl), M_PI_2, 0.0001l, "catanh(1,inf) long double, imag");

	auto xynanf = catanhf(CMPLX(1.f, NAN));
	auto xynand = catanh(CMPLX(1., NAN));
	auto xynanl = catanhl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "catanh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "catanh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "catanh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "catanh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "catanh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "catanh long double, imag 1+nan*i");

	auto xinffy1f = catanhf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = catanh(CMPLX(INFINITY, 1.));
	auto xinffy1l = catanhl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_BALLPARK(crealf(xinffy1f), 0.f, 0.0001f, "catanh float, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xinffy1f), M_PI_2, 0.0001f, "catanh float, imag inf+1*i");
	CASE_CHECK_BALLPARK(creal(xinffy1d), 0., 0.0001, "catanh double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xinffy1d), M_PI_2, 0.0001, "catanh double, imag inf+1*i");
	CASE_CHECK_BALLPARK(creall(xinffy1l), 0.l, 0.0001l, "catanh long double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xinffy1l), M_PI_2, 0.0001l, "catanh long double, imag inf+1*i");

	auto xnminfyinff = catanhf(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfd = catanh(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfl = catanhl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xnminfyinff), 0.f, 0.0001f, "catanh float, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xnminfyinff), M_PI_2, 0.0001f, "catanh float, imag inf+inf*i");
	CASE_CHECK_BALLPARK(creal(xnminfyinfd), 0., 0.0001, "catanh double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xnminfyinfd), M_PI_2, 0.0001, "catanh double, imag inf+inf*i");
	CASE_CHECK_BALLPARK(creall(xnminfyinfl), 0.l, 0.0001l, "catanh long double, real inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xnminfyinfl), M_PI_2, 0.0001l, "catanh long double, imag inf+inf*i");

	auto xinffynanf = catanhf(CMPLX(INFINITY, NAN));
	auto xinffynand = catanh(CMPLX(INFINITY, NAN));
	auto xinffynanl = catanhl(CMPLX(INFINITY, NAN));
	CASE_CHECK_BALLPARK(crealf(xinffynanf), 0.f, 0.0001f, "catanh float, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xinffynanf)), 0, "catanh float, imag inf+nan*i");
	CASE_CHECK_BALLPARK(creal(xinffynand), 0., 0.0001, "catanh double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimag(xinffynand)), 0, "catanh double, imag inf+nan*i");
	CASE_CHECK_BALLPARK(creall(xinffynanl), 0.l, 0.0001l, "catanh long double, real inf+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xinffynanl)), 0, "catanh long double, imag inf+nan*i");

	auto xnany1f = catanhf(CMPLX(NAN, 1));
	auto xnany1d = catanh(CMPLX(NAN, 1));
	auto xnany1l = catanhl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "catanh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "catanh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "catanh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "catanh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "catanh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "catanh long double, imag nan+1*i");

	auto xnanyinff = catanhf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = catanh(CMPLX(NAN, INFINITY));
	auto xnanyinfl = catanhl(CMPLX(NAN, INFINITY));
	CASE_CHECK_BALLPARK(crealf(xnanyinff), 0.f, 0.0001f, "catanh float, real nan+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xnanyinff), M_PI_2, 0.0001f, "catanh float, imag nan+inf*i");
	CASE_CHECK_BALLPARK(creal(xnanyinfd), 0., 0.0001, "catanh double, real nan+inf*i");
	CASE_CHECK_BALLPARK(cimag(xnanyinfd), M_PI_2, 0.0001, "catanh double, imag nan+inf*i");
	CASE_CHECK_BALLPARK(creall(xnanyinfl), 0.l, 0.0001l, "catanh long double, real nan+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xnanyinfl), M_PI_2, 0.0001l, "catanh long double, imag nan+inf*i");

	auto xnanynanf = catanhf(CMPLX(NAN, NAN));
	auto xnanynand = catanh(CMPLX(NAN, NAN));
	auto xnanynanl = catanhl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "catanh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "catanh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "catanh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "catanh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "catanh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "catanh long double, imag nan+nan*i");
}

void test_catan()
{
	auto f1 = catanf(CMPLX(0.f, 2.f));
	auto d1 = catan(CMPLX(0., 2.));
	auto ld1 = catanl(CMPLX(0.l, 2.l));

	CASE_CHECK_BALLPARK(crealf(f1), 1.570796f, 0.0001f, "catan float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 0.549306f, 0.0001f, "catan float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 1.570796, 0.0001, "catan double, real 1");
	CASE_CHECK_BALLPARK(cimag(d1), 0.549306, 0.0001, "catan double, imag 1");
	CASE_CHECK_BALLPARK(crealf(ld1), 1.570796l, 0.0001l, "catan long double, real 1");
	CASE_CHECK_BALLPARK(cimagf(ld1), 0.549306l, 0.0001l, "catan long double, imag 1");

	auto f2 = catanf(CMPLX(-0.f, 2.f));
	auto d2 = catan(CMPLX(-0., 2.));
	auto ld2 = catanl(CMPLX(-0.l, 2.l));

	CASE_CHECK_BALLPARK(crealf(f2), -1.570796f, 0.0001f, "catan float, real 2");
	CASE_CHECK_BALLPARK(cimagf(f2), 0.549306f, 0.0001f, "catan float, imag 2");
	CASE_CHECK_BALLPARK(creal(d2), -1.570796, 0.0001, "catan double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), 0.549306, 0.0001, "catan double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), -1.570796l, 0.0001l, "catan long double, real 2");
	CASE_CHECK_BALLPARK(cimagf(ld2), 0.549306l, 0.0001l, "catan long double, imag 2");

	auto f3 = catanf(CMPLX(-22.f, 6.f));
	auto d3 = catan(CMPLX(-22., 6.));
	auto ld3 = catanl(CMPLX(-22.l, 6.l));

	CASE_CHECK_BALLPARK(crealf(f3), -1.528508f, 0.0001f, "catan float, real 3");
	CASE_CHECK_BALLPARK(cimagf(f3), 0.011518f, 0.0001f, "catan float, imag 3");
	CASE_CHECK_BALLPARK(creal(d3), -1.528508, 0.0001, "catan double, real 3");
	CASE_CHECK_BALLPARK(cimag(d3), 0.011518, 0.0001, "catan double, imag 3");
	CASE_CHECK_BALLPARK(crealf(ld3), -1.528508l, 0.0001l, "catan long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), 0.011518l, 0.0001l, "catan long double, imag 3");

	auto f4 = catanf(CMPLX(22.f, 6.f));
	auto d4 = catan(CMPLX(22., 6.));
	auto ld4 = catanl(CMPLX(22.l, 6.l));

	CASE_CHECK_BALLPARK(crealf(f4), 1.528508f, 0.0001f, "catan float, real 4");
	CASE_CHECK_BALLPARK(cimagf(f4), 0.011518f, 0.0001f, "catan float, imag 4");
	CASE_CHECK_BALLPARK(creal(d4), 1.528508, 0.0001, "catan double, real 4");
	CASE_CHECK_BALLPARK(cimag(d4), 0.011518, 0.0001, "catan double, imag 4");
	CASE_CHECK_BALLPARK(crealf(ld4), 1.528508l, 0.0001l, "catan long double, real 4");
	CASE_CHECK_BALLPARK(cimagf(ld4), 0.011518l, 0.0001l, "catan long double, imag 4");

	auto f5 = catanf(CMPLX(11.f, 9.f));
	auto d5 = catan(CMPLX(11., 9.));
	auto ld5 = catanl(CMPLX(11.l, 9.l));

	CASE_CHECK_BALLPARK(crealf(f5), 1.516287f, 0.0001f, "catan float, real 5");
	CASE_CHECK_BALLPARK(cimagf(f5), 0.044452f, 0.0001f, "catan float, imag 5");
	CASE_CHECK_BALLPARK(creal(d5), 1.516287, 0.0001, "catan double, real 5");
	CASE_CHECK_BALLPARK(cimag(d5), 0.044452, 0.0001, "catan double, imag 5");
	CASE_CHECK_BALLPARK(crealf(ld5), 1.516287l, 0.0001l, "catan long double, real 5");
	CASE_CHECK_BALLPARK(cimagf(ld5), 0.044452l, 0.0001l, "catan long double, imag 5");

	auto f6 = catanf(CMPLX(0.5f, 0.5f));
	auto d6 = catan(CMPLX(0.5, 0.5));
	auto ld6 = catanl(CMPLX(0.5l, 0.5l));

	CASE_CHECK_BALLPARK(crealf(f6), 0.553574f, 0.0001f, "catan float, real 6");
	CASE_CHECK_BALLPARK(cimagf(f6), 0.402359f, 0.0001f, "catan float, imag 6");
	CASE_CHECK_BALLPARK(creal(d6), 0.553574, 0.0001, "catan double, real 6");
	CASE_CHECK_BALLPARK(cimag(d6), 0.402359, 0.0001, "catan double, imag 6");
	CASE_CHECK_BALLPARK(crealf(ld6), 0.553574l, 0.0001l, "catan long double, real 6");
	CASE_CHECK_BALLPARK(cimagf(ld6), 0.402359l, 0.0001l, "catan long double, imag 6");

	auto f7 = catanf(CMPLX(0.f, INFINITY));
	auto d7 = catan(CMPLX(0., INFINITY));
	auto ld7 = catanl(CMPLX(0.l, INFINITY));

	CASE_CHECK_BALLPARK(crealf(f7), M_PI_2, 0.0001f, "catan float, real 7");
	CASE_CHECK_BALLPARK(cimagf(f7), 0.0f, 0.0001f, "catan float, imag 7");
	CASE_CHECK_BALLPARK(creal(d7), M_PI_2, 0.0001, "catan double, real 7");
	CASE_CHECK_BALLPARK(cimag(d7), 0., 0.0001, "catan double, imag 7");
	CASE_CHECK_BALLPARK(crealf(ld7), M_PI_2, 0.0001l, "catan long double, real 7");
	CASE_CHECK_BALLPARK(cimagf(ld7), 0.l, 0.0001l, "catan long double, imag 7");
}

//double complex cacosh(double complex z);
//float complex cacoshf(float complex z);
//long double complex cacoshl(long double complex z);
void test_cacosh()
{
	auto f1 = cacosh(CMPLX(0.5f, 0.f));
	auto d1 = cacosh(CMPLX(0.5, 0.));
	auto ld1 = cacosh(CMPLX(0.5l, 0.l));

	auto f2 = cacosh(CMPLX(0.5f, -0.f));
	auto d2 = cacosh(CMPLX(0.5, -0.));
	auto ld2 = cacosh(CMPLX(0.5l, -0.l));

	auto f3 = cacosh(CMPLX(1.f, 1.f));
	auto d3 = cacosh(CMPLX(1., 1.));
	auto ld3 = cacosh(CMPLX(1.l, 1.l));

	auto f4 = cacosh(CMPLX(-4.f, 4.f));
	auto d4 = cacosh(CMPLX(-4., 4.));
	auto ld4 = cacosh(CMPLX(-4.l, 4.l));

	auto f5 = cacosh(CMPLX(-4.f, -4.f));
	auto d5 = cacosh(CMPLX(-4., -4.));
	auto ld5 = cacosh(CMPLX(-4.l, -4.l));

	CASE_CHECK_BALLPARK(crealf(f1), 0.000000f, 0.0001f, "cacosh float, real 1");
	CASE_CHECK_BALLPARK(cimagf(f1), 1.047198f, 0.0001f, "cacosh float, imag 1");
	CASE_CHECK_BALLPARK(creal(d1), 0.000000, 0.0001, "cacosh double, real 1");
	CASE_CHECK_BALLPARK(cimag(d1), 1.047198, 0.0001, "cacosh double, imag 1");
	CASE_CHECK_BALLPARK(crealf(ld1), 0.000000l, 0.0001l, "cacosh long double, real 1");
	CASE_CHECK_BALLPARK(cimagf(ld1), 1.047198l, 0.0001l, "cacosh long double, imag 1");

	CASE_CHECK_BALLPARK(crealf(f2), 0.000000f, 0.0001f, "cacosh float, real 2");
	CASE_CHECK_BALLPARK(cimagf(f2), -1.047198f, 0.0001f, "cacosh float, imag 2");
	CASE_CHECK_BALLPARK(creal(d2), 0.000000, 0.0001, "cacosh double, real 2");
	CASE_CHECK_BALLPARK(cimag(d2), -1.047198, 0.0001, "cacosh double, imag 2");
	CASE_CHECK_BALLPARK(crealf(ld2), 0.000000l, 0.0001l, "cacosh long double, real 2");
	CASE_CHECK_BALLPARK(cimagf(ld2), -1.047198l, 0.0001l, "cacosh long double, imag 2");

	CASE_CHECK_BALLPARK(crealf(f3), 1.061275f, 0.0001f, "cacosh float, real 3");
	CASE_CHECK_BALLPARK(cimagf(f3), 0.904557f, 0.0001f, "cacosh float, imag 3");
	CASE_CHECK_BALLPARK(creal(d3), 1.061275, 0.0001, "cacosh double, real 3");
	CASE_CHECK_BALLPARK(cimag(d3), 0.904557, 0.0001, "cacosh double, imag 3");
	CASE_CHECK_BALLPARK(crealf(ld3), 1.061275l, 0.0001l, "cacosh long double, real 3");
	CASE_CHECK_BALLPARK(cimagf(ld3), 0.904557l, 0.0001l, "cacosh long double, imag 3");

	CASE_CHECK_BALLPARK(crealf(f4), 2.426107f, 0.0001f, "cacosh float, real 4");
	CASE_CHECK_BALLPARK(cimagf(f4), 2.348384f, 0.0001f, "cacosh float, imag 4");
	CASE_CHECK_BALLPARK(creal(d4), 2.426107, 0.0001, "cacosh double, real 4");
	CASE_CHECK_BALLPARK(cimag(d4), 2.348384, 0.0001, "cacosh double, imag 4");
	CASE_CHECK_BALLPARK(crealf(ld4), 2.426107l, 0.0001l, "cacosh long double, real 4");
	CASE_CHECK_BALLPARK(cimagf(ld4), 2.348384l, 0.0001l, "cacosh long double, imag 4");

	CASE_CHECK_BALLPARK(crealf(f5), 2.426107f, 0.0001f, "cacosh float, real 4");
	CASE_CHECK_BALLPARK(cimagf(f5), -2.348384f, 0.0001f, "cacosh float, imag 4");
	CASE_CHECK_BALLPARK(creal(d5), 2.426107, 0.0001, "cacosh double, real 4");
	CASE_CHECK_BALLPARK(cimag(d5), -2.348384, 0.0001, "cacosh double, imag 4");
	CASE_CHECK_BALLPARK(crealf(ld5), 2.426107l, 0.0001l, "cacosh long double, real 4");
	CASE_CHECK_BALLPARK(cimagf(ld5), -2.348384l, 0.0001l, "cacosh long double, imag 4");

	auto csf = cacoshf(conjf(1.f + 1.f * I));
	auto scf = conjf(cacoshf(1.f + 1.f * I));
	auto csd = cacosh(conj(1. + 1. * I));
	auto scd = conj(cacosh(1. + 1. * I));
	auto csl = cacoshl(conjl(1.l + 1.l * I));
	auto scl = conjl(cacoshl(1.l + 1.l * I));
	CASE_CHECK_BALLPARK(crealf(csf), crealf(scf), 0.0001f, "cacosh(conj) == conj(cacosh) float, real");
	CASE_CHECK_BALLPARK(cimagf(csf), cimagf(scf), 0.0001f, "cacosh(conj) == conj(cacosh) float, imag");
	CASE_CHECK_BALLPARK(creal(csd), creal(scd), 0.0001, "cacosh(conj) == conj(cacosh) double, real");
	CASE_CHECK_BALLPARK(cimag(csd), cimag(scd), 0.0001, "cacosh(conj) == conj(cacosh) double, imag");
	CASE_CHECK_BALLPARK(creall(csl), creall(scl), 0.0001l, "cacosh(conj) == conj(cacosh) long double, real");
	CASE_CHECK_BALLPARK(cimagl(csl), cimagl(scl), 0.0001l, "cacosh(conj) == conj(cacosh) long double, imag");


	auto  rzerof = cacoshf(0.f + 0.f * I);
	auto  rzerod = cacosh(0. + 0. * I);
	auto  rzerol = cacoshl(0.l + 0.l * I);
	CASE_CHECK_BALLPARK(crealf(rzerof), 0.f, 0.0001f, "cacosh(0) float, real");
	CASE_CHECK_BALLPARK(cimagf(rzerof), M_PI_2, 0.0001f, "cacosh(0) float, imag");
	CASE_CHECK_BALLPARK(creal(rzerod), 0., 0.0001, "cacosh(0) double, real");
	CASE_CHECK_BALLPARK(cimag(rzerod), M_PI_2, 0.0001, "cacosh(0) double, imag");
	CASE_CHECK_BALLPARK(creall(rzerol), 0.l, 0.0001l, "cacosh(0) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rzerol), M_PI_2, 0.0001l, "cacosh(0) long double, imag");

	auto x1yinff = cacoshf(CMPLX(1.f, INFINITY));
	auto x1yinfd = cacosh(CMPLX(1., INFINITY));
	auto x1yinfl = cacoshl(CMPLX(1.l, INFINITY));

	CASE_CHECK_NE(isinf(crealf(x1yinff)), 0, "cacosh float, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimagf(x1yinff), M_PI_2, 0.0001f, "cacosh float, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creal(x1yinfd)), 0, "cacosh double, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimag(x1yinfd), M_PI_2, 0.0001, "cacosh double, imag 1+inf*i");
	CASE_CHECK_NE(isinf(creall(x1yinfl)), 0, "cacosh long double, real 1+inf*i");
	CASE_CHECK_BALLPARK(cimagl(x1yinfl), M_PI_2, 0.0001l, "cacosh long double, imag 1+inf*i");

	auto rmzerof = cacoshf(CMPLX(0.f, NAN));
	auto rmzerod = cacosh(CMPLX(0., NAN));
	auto rmzerol = cacoshl(CMPLX(0.l, NAN));
	CASE_CHECK_NE(isnan(crealf(rmzerof)), 0, "cacosh(0,nan) float, real");
	CASE_CHECK_BALLPARK(cimagf(rmzerof), M_PI_2, 0.0001f, "cacosh(0,nan) float, imag");
	CASE_CHECK_NE(isnan(creal(rmzerod)), 0, "cacosh(0,nan) double, real");
	CASE_CHECK_BALLPARK(cimag(rmzerod), M_PI_2, 0.0001, "cacosh(0,nan) double, imag");
	CASE_CHECK_NE(isnan(creall(rmzerol)), 0, "cacosh(0,nan) long double, real");
	CASE_CHECK_BALLPARK(cimagl(rmzerol), M_PI_2, 0.0001l, "cacosh(0,nan) long double, imag");

	auto xynanf = cacoshf(CMPLX(1.f, NAN));
	auto xynand = cacosh(CMPLX(1., NAN));
	auto xynanl = cacoshl(CMPLX(1.l, NAN));
	CASE_CHECK_NE(isnan(crealf(xynanf)), 0, "cacosh float, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xynanf)), 0, "cacosh float, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creal(xynand)), 0, "cacosh double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimag(xynand)), 0, "cacosh double, imag 1+nan*i");
	CASE_CHECK_NE(isnan(creall(xynanl)), 0, "cacosh long double, real 1+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xynanl)), 0, "cacosh long double, imag 1+nan*i");

	auto xminfy1f = cacoshf(CMPLX(-INFINITY, 0.f));
	auto xminfy1d = cacosh(CMPLX(-INFINITY, 0.));
	auto xminfy1l = cacoshl(CMPLX(-INFINITY, 0.l));
	CASE_CHECK_NE(isinf(crealf(xminfy1f)), 0, "cacosh float, real -inf+0*i");
	CASE_CHECK_BALLPARK(cimagf(xminfy1f), M_PI, 0.0001f, "cacosh float, imag -inf+0*i");
	CASE_CHECK_NE(isinf(creal(xminfy1d)), 0, "cacosh double, real -inf+0*i");
	CASE_CHECK_BALLPARK(cimag(xminfy1d), M_PI, 0.0001, "cacosh double, imag -inf+0*i");
	CASE_CHECK_NE(isinf(creall(xminfy1l)), 0, "cacosh long double, real -inf+0*i");
	CASE_CHECK_BALLPARK(cimagl(xminfy1l), M_PI, 0.0001l, "cacosh long double, imag -inf+0*i");

	auto xinffy1f = cacoshf(CMPLX(INFINITY, 1.f));
	auto xinffy1d = cacosh(CMPLX(INFINITY, 1.));
	auto xinffy1l = cacoshl(CMPLX(INFINITY, 1.l));
	CASE_CHECK_NE(isinf(crealf(xinffy1f)), 0, "cacosh float, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagf(xinffy1f), 0.f, 0.0001f, "cacosh float, imag inf+1*i");
	CASE_CHECK_NE(isinf(creal(xinffy1d)), 0, "cacosh double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimag(xinffy1d), 0., 0.0001, "cacosh double, imag inf+1*i");
	CASE_CHECK_NE(isinf(creall(xinffy1l)), 0, "cacosh long double, real inf+1*i");
	CASE_CHECK_BALLPARK(cimagl(xinffy1l), 0.l, 0.0001l, "cacosh long double, imag inf+1*i");


	auto xminfyinff = cacoshf(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfd = cacosh(CMPLX(-INFINITY, INFINITY));
	auto xminfyinfl = cacoshl(CMPLX(-INFINITY, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xminfyinff)), 0, "cacosh float, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagf(xminfyinff), M_PI_4 * 3.f, 0.0001f, "cacosh float, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xminfyinfd)), 0, "cacosh double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xminfyinfd), M_PI_4 * 3., 0.0001, "cacosh double, imag -inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xminfyinfl)), 0, "cacosh long double, real -inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xminfyinfl), M_PI_4 * 3.l, 0.0001l, "cacosh long double, imag -inf+inf*i");

	auto xnminfyinff = cacoshf(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfd = cacosh(CMPLX(INFINITY, INFINITY));
	auto xnminfyinfl = cacoshl(CMPLX(INFINITY, INFINITY));
	CASE_CHECK_BALLPARK(cimagf(xnminfyinff), M_PI_4, 0.0001f, "cacosh float, real inf+inf*i");
	CASE_CHECK_NE(isinf(crealf(xnminfyinff)), 0, "cacosh float, imag inf+inf*i");
	CASE_CHECK_BALLPARK(cimag(xnminfyinfd), M_PI_4, 0.0001, "cacosh double, real inf+inf*i");
	CASE_CHECK_NE(isinf(creal(xnminfyinfd)), 0, "cacosh double, imag inf+inf*i");
	CASE_CHECK_BALLPARK(cimagl(xnminfyinfl), M_PI_4, 0.0001l, "cacosh long double, real inf+inf*i");
	CASE_CHECK_NE(isinf(creall(xnminfyinfl)), 0, "cacosh long double, imag inf+inf*i");


	auto xnany1f = cacoshf(CMPLX(NAN, 1));
	auto xnany1d = cacosh(CMPLX(NAN, 1));
	auto xnany1l = cacoshl(CMPLX(NAN, 1));
	CASE_CHECK_NE(isnan(crealf(xnany1f)), 0, "cacosh float, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagf(xnany1f)), 0, "cacosh float, imag nan+1*i");
	CASE_CHECK_NE(isnan(creal(xnany1d)), 0, "cacosh double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimag(xnany1d)), 0, "cacosh double, imag nan+1*i");
	CASE_CHECK_NE(isnan(creall(xnany1l)), 0, "cacosh long double, real nan+1*i");
	CASE_CHECK_NE(isnan(cimagl(xnany1l)), 0, "cacosh long double, imag nan+1*i");

	auto xnanyinff = cacoshf(CMPLX(NAN, INFINITY));
	auto xnanyinfd = cacosh(CMPLX(NAN, INFINITY));
	auto xnanyinfl = cacoshl(CMPLX(NAN, INFINITY));
	CASE_CHECK_NE(isinf(crealf(xnanyinff)), 0, "cacosh float, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagf(xnanyinff)), 0, "cacosh float, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creal(xnanyinfd)), 0, "cacosh double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimag(xnanyinfd)), 0, "cacosh double, imag nan+inf*i");
	CASE_CHECK_NE(isinf(creall(xnanyinfl)), 0, "cacosh long double, real nan+inf*i");
	CASE_CHECK_NE(isnan(cimagl(xnanyinfl)), 0, "cacosh long double, imag nan+inf*i");

	auto xnanynanf = cacoshf(CMPLX(NAN, NAN));
	auto xnanynand = cacosh(CMPLX(NAN, NAN));
	auto xnanynanl = cacoshl(CMPLX(NAN, NAN));
	CASE_CHECK_NE(isnan(crealf(xnanynanf)), 0, "cacosh float, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagf(xnanynanf)), 0, "cacosh float, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creal(xnanynand)), 0, "cacosh double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimag(xnanynand)), 0, "cacosh double, imag nan+nan*i");
	CASE_CHECK_NE(isnan(creall(xnanynanl)), 0, "cacosh long double, real nan+nan*i");
	CASE_CHECK_NE(isnan(cimagl(xnanynanl)), 0, "cacosh long double, imag nan+nan*i");
}


void test_complex()
{
	printf("\ntest suite complex:\n");
	test_cplx();
	test_complex_trigonometry();
	test_carg();
	test_conj();
	test_csqrt();
	test_cabs();
	test_cproj();
	test_cpow();
	test_cexp();
	test_clog();
	test_csinh();
	test_ccosh();
	test_cacos();
	test_casinh();
	test_casin();
	test_ctanh();
	test_catanh();
	test_catan();
	test_cacosh();
}