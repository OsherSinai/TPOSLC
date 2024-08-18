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
#include <include/fenv.h>
#include <include/math.h>
#include <include/string.h>

//feclearexcept;
void test_feclearexcept()
{
	CASE_CHECK_EQ(feclearexcept(0), 0, "feclearexcept test 1, except argument 0");
	CASE_CHECK_EQ(feclearexcept(FE_ALL_EXCEPT), 0, "feclearexcept test 1, except argument 0");
}
//fegetexceptflag;
void test_fegetexceptflag()
{
	int nRet = 0;
	fexcept_t ex;
	feclearexcept(FE_ALL_EXCEPT);
	nRet = fegetexceptflag(&ex, FE_ALL_EXCEPT);
	CASE_CHECK_EQ(nRet, 0, "fegetexceptflag test 1, return");
	CASE_CHECK_EQ(ex, 0, "fegetexceptflag test 2, get exceptions");
	ex = ~0;
	fesetexceptflag(&ex, FE_ALL_EXCEPT);
	nRet = fegetexceptflag(&ex, FE_ALL_EXCEPT);
	CASE_CHECK_EQ(nRet, 0, "fegetexceptflag test 3, return");
	CASE_CHECK_EQ(ex, FE_ALL_EXCEPT, "fegetexceptflag test 4, get exceptions");
	feclearexcept(FE_ALL_EXCEPT);
}
//feraiseexcept;
void test_feraiseexcept()
{
	int nRet = 0;
	fexcept_t ex;
	feclearexcept(FE_ALL_EXCEPT);
	ex = ~0;
	nRet = feraiseexcept(FE_ALL_EXCEPT);
	ex = 0;
	fegetexceptflag(&ex, FE_ALL_EXCEPT);
	CASE_CHECK_EQ(nRet, 0, "feraiseexcept test 1, return");
	CASE_CHECK_EQ(ex, FE_ALL_EXCEPT, "feraiseexcept test 2, set exceptions");
	feclearexcept(FE_ALL_EXCEPT);
}

void test_fesetexceptflag()
{
	int nRet = 0;
	fexcept_t ex;
	feclearexcept(FE_ALL_EXCEPT);
	ex = ~0;
	nRet = fesetexceptflag(&ex, FE_ALL_EXCEPT);
	ex = 0;
	fegetexceptflag(&ex, FE_ALL_EXCEPT);
	CASE_CHECK_EQ(nRet, 0, "fesetexceptflag test 1, return");
	CASE_CHECK_EQ(ex, FE_ALL_EXCEPT, "fesetexceptflag test 2, set exceptions");
	feclearexcept(FE_ALL_EXCEPT);
}

//fetestexcept;
void test_fesetround()
{
	int nRet; 
	double RoundE;
	int nRoundMode;
	nRet = fesetround(FE_DOWNWARD);
	nRoundMode = fegetround();
	feclearexcept(FE_ALL_EXCEPT);
	RoundE = rint(0.5);//0.0
	CASE_CHECK_EQ(nRoundMode, FE_DOWNWARD, "fesetround test 1, downward, mode");
	CASE_CHECK_EQ(nRet, 0, "fesetround test 2, downward, return");
	CASE_CHECK_EQ(RoundE, 0.0, "fesetround test 3, downward, Round");
	nRet = fesetround(FE_UPWARD);
	nRoundMode = fegetround();
	feclearexcept(FE_ALL_EXCEPT);
	RoundE = rint(0.5);//1.0
	CASE_CHECK_EQ(nRoundMode, FE_UPWARD, "fesetround test 4, upward, mode");
	CASE_CHECK_EQ(nRet, 0, "fesetround test 5, upward, return");
	CASE_CHECK_EQ(RoundE, 1.0, "fesetround test 6, upward, Round");
	nRoundMode = fegetround();
	feclearexcept(FE_ALL_EXCEPT);
	RoundE = rint(0.5);//1.0
	CASE_CHECK_EQ(nRoundMode, FE_UPWARD, "fesetround test 7, upward, mode");
	CASE_CHECK_EQ(nRet, 0, "fesetround test 8, upward, return");
	CASE_CHECK_EQ(RoundE, 1.0, "fesetround test 9, upward, Round");
	nRet = fesetround(FE_TOWARDZERO);
	nRoundMode = fegetround();
	feclearexcept(FE_ALL_EXCEPT);
	RoundE = rint(0.5);//0.0
	CASE_CHECK_EQ(nRoundMode, FE_TOWARDZERO, "fesetround test 10, to zero, mode");
	CASE_CHECK_EQ(nRet, 0, "fesetround test 11, to zero, return");
	CASE_CHECK_EQ(RoundE, 0.0, "fesetround test 12, to zero, Round");
	nRet = fesetround(FE_TONEAREST);
	nRoundMode = fegetround();
	feclearexcept(FE_ALL_EXCEPT);
	RoundE = rint(0.5);// 0.0
	CASE_CHECK_EQ(nRoundMode, FE_TONEAREST, "fesetround test 13, nearest, mode");
	CASE_CHECK_EQ(nRet, 0, "fesetround test 14, to nearest, return");
	CASE_CHECK_EQ(RoundE, 0.0, "fesetround test 15, to nearest, Round");
}
void test_fegetround()
{
	int nRoundMode = fegetround();
	CASE_CHECK_BE(nRoundMode, FE_TONEAREST, "fegetround test 1, lower bound");
	CASE_CHECK_SE(nRoundMode, FE_TOWARDZERO, "fegetround test 2, upper bound");
}
extern "C" int _tos_fenv_TestEnvEqual(const fenv_t* a, const fenv_t* b);
//fegetenv;
void test_fegetenv()
{
	fenv_t defenv = FE_DEF_ENV;
	fenv_t env;
	feclearexcept(FE_ALL_EXCEPT);
	fesetenv(&defenv);
	int nRet = fegetenv(0);
	CASE_CHECK_NE(nRet, 0, "fegetenv test 1, param zero");
	nRet = fegetenv(&env);
	CASE_CHECK_EQ(nRet, 0, "fegetenv test 2, param proper");
	nRet = _tos_fenv_TestEnvEqual(&env, &defenv);
	CASE_CHECK_EQ(nRet, 0, "fegetenv test 3, got default env");
	env[1] = 0x3f;
	fesetenv(&env);
	nRet = fegetenv(&env);
	CASE_CHECK_EQ(nRet, 0, "fegetenv test 3, param after env change");
	nRet = _tos_fenv_TestEnvEqual(&env, &defenv);
	CASE_CHECK_NE(nRet, 0, "fegetenv test 4, got different env");
	fesetenv(&defenv);
}
//fesetenv;
void test_fesetenv()
{
	fenv_t defenv = FE_DEF_ENV;
	fenv_t env;
	feclearexcept(FE_ALL_EXCEPT);
	int nRet = fesetenv(0);
	CASE_CHECK_NE(nRet, 0, "fesetenv test 1, param zero");
	nRet = fesetenv(&defenv);
	CASE_CHECK_EQ(nRet, 0, "fesetenv test 2, param proper");
	fegetenv(&env);
	nRet = _tos_fenv_TestEnvEqual(&env, &defenv);
	CASE_CHECK_EQ(nRet, 0, "fesetenv test 3, got default env");
	env[1] = 0x3f;
	nRet = fesetenv(&env);
	CASE_CHECK_EQ(nRet, 0, "fesetenv test 3, param after env change");
	fegetenv(&env);
	nRet = _tos_fenv_TestEnvEqual(&env, &defenv);
	CASE_CHECK_NE(nRet, 0, "fesetenv test 4, got different env");
	fesetenv(&defenv);
}
//feholdexcept;
void test_feholdexcept()
{
	fenv_t defenv = FE_DEF_ENV;
	fenv_t env;
	feclearexcept(FE_ALL_EXCEPT);
	fesetenv(&defenv);
	int nRet = feholdexcept(0);
	CASE_CHECK_NE(nRet, 0, "feholdexcept test 1, param zero");
	nRet = feholdexcept(&env);
	CASE_CHECK_EQ(nRet, 0, "feholdexcept test 2, param proper");
	nRet = _tos_fenv_TestEnvEqual(&env, &defenv);
	CASE_CHECK_EQ(nRet, 0, "feholdexcept test 3, same env");

	fesetenv(&defenv);
}
//feupdateenv;
void test_feupdateenv()
{
	int nRet;
	fenv_t curr_excepts;
	feclearexcept(FE_ALL_EXCEPT);
	feraiseexcept(FE_INVALID);
	feholdexcept(&curr_excepts);
	feraiseexcept(FE_INEXACT);
	feclearexcept(FE_INEXACT);
	feraiseexcept(FE_OVERFLOW);

	nRet = feupdateenv(0);
	CASE_CHECK_NE(nRet, 0, "feholdexcept test 1, param zero");
	nRet = feupdateenv(&curr_excepts);
	CASE_CHECK_EQ(nRet, 0, "feholdexcept test 2, param proper");
	CASE_CHECK_NE(fetestexcept(FE_INVALID), 0, "feholdexcept test 3, test invalid");
	CASE_CHECK_NE(fetestexcept(FE_OVERFLOW), 0, "feholdexcept test 4, test merge (invalid & overflow)");
	feclearexcept(FE_ALL_EXCEPT);
}
void test_fenv()
{
	printf("\ntest suite fenv:\n");
	test_feclearexcept();
	test_fegetexceptflag();
	test_feraiseexcept();
	test_fesetexceptflag();
	test_fegetround();
	test_fesetround();
	test_fegetenv();
	test_fesetenv();
	test_feholdexcept();
	test_feupdateenv();
}