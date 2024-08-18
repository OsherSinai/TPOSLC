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
// cstdlib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// TOS - Training Operating System
/*
#include "include/setjmp.h"

#include "include/stdarg.h"

#include "include/stdlib.h"
#include "include/limits.h"
#include "include/stddef.h"
#include "include/stdatomic.h"
#include "include/signal.h"



#include "src/win32_memory.h"
#include "src/win32_ntdll.h"
#include "include/stdlib.h"
#include "include/string.h"

#include "src/win32_file.h"
#include "src/win32_ntdll.h"
#include "include/stdio.h"
#include "src/win32_except.h"

#include "src/lock.h"

#include "src/LinkedList.h"

#include "include/time.h"

extern "C" int _tos_initialize_time();
extern "C" void _tos_initialize_peb_signal_handler();

#include "src/TOSThreadEnvironmentBlock.h"
#include "include/errno.h"

//thread_local int testlk = 0;
//TODO: split win32_ntdll.h to multiple smaller hfiles
#include "src/utf_conv.h"


#include "include/locale.h"

#include "include/except.h"
void test_exception_layer1_nullptr()
{
	int* p0 = 0;
	TOS_TRY
		* p0 = 1;
	TOS_EXCEPT((void*)0)
		printf("test_exception_layer1_nullptr: 0\n");
	TOS_EXCEPT_UNIVERSAL
		printf("test_exception_layer1_nullptr: universal\n");
	TOS_TRY_FINISH
		return;
}
void test_exception_layer2_throw1()
{
	_tos_exception excpt = { 0 };
	excpt.pValue = (void*)2;
	TOS_TRY
		TOS_THROW(excpt);
	TOS_EXCEPT((void*)1)
		printf("test_exception_layer1_nullptr: 1\n");
	TOS_EXCEPT((void*)2)
		printf("test_exception_layer1_nullptr: 2\n");
	TOS_EXCEPT_UNIVERSAL
		printf("test_exception_layer1_nullptr: universal\n");
	TOS_TRY_FINISH
		return;
}
void test_exception_layer1_throw1()
{
	TOS_TRY
		test_exception_layer2_throw1();
	TOS_EXCEPT((void*)1)
		printf("test_exception_layer1_nullptr: 1\n");
	TOS_EXCEPT((void*)2)
		printf("test_exception_layer1_nullptr: 2\n");
	TOS_EXCEPT_UNIVERSAL
		printf("test_exception_layer1_nullptr: universal\n");
	TOS_TRY_FINISH
		return;
}

void test_exception_layer2_throw2()
{
	_tos_exception excpt = { 0 };
	excpt.pValue = (void*)3;
	TOS_TRY
		TOS_THROW(excpt);
	TOS_EXCEPT((void*)1)
		printf("test_exception_layer1_nullptr: 1\n");
	TOS_EXCEPT((void*)2)
		printf("test_exception_layer1_nullptr: 2\n");
	TOS_TRY_FINISH
		return;
}
void test_exception_layer1_throw2()
{
	TOS_TRY
		test_exception_layer2_throw2();
	TOS_EXCEPT((void*)1)
		printf("test_exception_layer1_nullptr: 1\n");
	TOS_EXCEPT((void*)2)
		printf("test_exception_layer1_nullptr: 2\n");
	TOS_EXCEPT_UNIVERSAL
		printf("test_exception_layer1_nullptr: universal\n");
	TOS_TRY_FINISH
		return;
}

void test_exception()
{
	test_exception_layer1_nullptr();
	test_exception_layer1_throw1();
	test_exception_layer1_throw2();
}

extern "C" int main(int argc, char** argv)
{
	test_exception();
	//test_ungetchar();
	//test_environment();
	return 0;
}

*/