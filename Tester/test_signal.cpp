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
#include <include/signal.h>
#include <include/except.h>


void SigsegvHandler(int type)
{
	_tos_exception te = {0};
	te.pValue = (void*)999;
	TOS_THROW(te);
}

void test_signal()
{
	printf("\ntest suite signal:\n");

	auto orghandler = signal(SIGSEGV, SigsegvHandler);
	CASE_CHECK_NE(orghandler, 0, "signal, signal called")

	TOS_TRY
		//If you're seeing this and got an exception it is intended.
		//Just continue the run, the exception should be caught.
		int* p = 0;
		*p = 1;
	TOS_EXCEPT((void*)999)
		CASE_CHECK_EQ(0, 0, "signal, caught signal")
	TOS_EXCEPT_UNIVERSAL
		CASE_CHECK_NE(0, 0, "signal, incorrect signal called")
	TOS_TRY_FINISH

	signal(SIGSEGV, orghandler);
}