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
#include <include/setjmp.h>


void test_setjmp()
{
	printf("\ntest suite setjmp:\n");
	int nCtr = 0;
	jmp_buf buf;
	int nJmpRet = setjmp(buf);


	if (nJmpRet == 0)
	{
		CASE_CHECK_EQ(nCtr, 0, "setjmp, Initial setjmp");
		nCtr++;
		longjmp(buf, 1);
	}
	else if (nJmpRet == 1)
	{
		CASE_CHECK_EQ(nCtr, 1, "setjmp, jump successful");
	}
	else
	{
		CASE_CHECK_NE(0, 0, "setjmp, Failed with incorrect return");
	}
}