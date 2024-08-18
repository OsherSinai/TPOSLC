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
#include "TestSuites.h"
#include "TestCaseUtils.h"
#include <include/errno.h>

void test_errno()
{
	printf("\ntest suite errno:\n");

	errno = 0;
	CASE_CHECK_EQ(errno, 0, "errno test 1, equal 0");
	errno = 1;
	CASE_CHECK_EQ(errno, 1, "errno test 2, equal 1");
	errno = 2;
	CASE_CHECK_EQ(errno, 2, "errno test 3, equal 2");
	errno = 3;
	CASE_CHECK_EQ(errno, 3, "errno test 4, equal 3");
	errno = 0;
	CASE_CHECK_EQ(errno, 0, "errno test 5, equal 0");
}