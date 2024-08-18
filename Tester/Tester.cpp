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

#include <include\stdio.h>
#include "TestCaseUtils.h"

#include "TestSuites.h"

size_t g_TotalSuccessfulTests = 0;
size_t g_TotalFailedTests = 0;
//NOTICE, DO NOT USE RELEASE BUILD IN VISUAL STUDIO
//It will use its own builtin functions for some of libc, which will break the functionality of this library
extern "C" int main(int argc, char* argv[])
{
	printf("TOS libc comprehensive test\n");
	test_stdint();
	test_ctype();
	test_errno();
	test_string();
	test_fenv();
	test_setjmp();
	test_stdarg();
	test_signal();
	test_time();
	test_math();
	test_stdlib();
	test_inttypes();
	test_complex();
	test_threads();
	test_uchar();
	test_wctype();
	test_stdio();
	test_wstring();

	printf("\n\ntotal tests: [%zu]\n\tSuccessful tests: [", g_TotalSuccessfulTests + g_TotalFailedTests);
	CASE_SET_GREEN;
	printf("%zu", g_TotalSuccessfulTests);
	CASE_SET_WHITE;
	printf("]\n\tFailed tests: [");
	CASE_SET_RED;
	printf("%zu", g_TotalFailedTests);
	CASE_SET_WHITE;
	printf("]\n");
	return 0;
}
