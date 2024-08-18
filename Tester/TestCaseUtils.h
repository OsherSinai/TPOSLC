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
#ifndef TEST_CASE_UTILS_H
#define TEST_CASE_UTILS_H

#include <include\stdio.h>

extern size_t g_TotalSuccessfulTests;
extern size_t g_TotalFailedTests;

#define CASE_SET_RED printf("\033[31;1m")
#define CASE_SET_GREEN printf("\033[32;1m")
#define CASE_SET_YELLOW printf("\033[93;1m")
#define CASE_SET_WHITE printf("\033[0m")

#define CASE_MANUAL_CHECK_START() CASE_SET_YELLOW
#define CASE_MANUAL_CHECK_END() CASE_SET_WHITE


#define CASE_ASSERT_GENERIC(a, b, op, text)\
	if((a) op (b))\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_GREEN;\
		printf("success");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalSuccessfulTests++;\
	}\
	else\
	{\
		printf( __PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_RED;\
		printf("failed");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalFailedTests++;\
		return;\
	}

#define CASE_CHECK_GENERIC(a, b, op, text)\
	if((a) op (b))\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_GREEN;\
		printf("success");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalSuccessfulTests++;\
	}\
	else\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_RED;\
		printf("failed");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalFailedTests++;\
	}

#define CASE_CHECK_BALLPARK(a, b, c, text)\
	if(((a) > ((b) - (c))) &&  ((a) < ((b) + (c))))\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_GREEN;\
		printf("success");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalSuccessfulTests++;\
	}\
	else\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_RED;\
		printf("failed");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalFailedTests++;\
	}
#define CASE_CHECK_NOT_IN_BALLPARK(a, b, c, text)\
	if(((a) <= ((b) - (c))) || ((a) >= ((b) + (c))))\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_GREEN;\
		printf("success");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalSuccessfulTests++;\
	}\
	else\
	{\
		printf(__PRETTY_FUNCTION__);\
		printf( ":" text ":\t[");\
		CASE_SET_RED;\
		printf("failed");\
		CASE_SET_WHITE;\
		printf("]\n");\
		g_TotalFailedTests++;\
	}

#define CASE_ASSERT_EQ(a, b, text) CASE_ASSERT_GENERIC(a, b, ==, text)
#define CASE_ASSERT_NE(a, b, text) CASE_ASSERT_GENERIC(a, b, !=, text)
#define CASE_ASSERT_BT(a, b, text) CASE_ASSERT_GENERIC(a, b, >, text)
#define CASE_ASSERT_ST(a, b, text) CASE_ASSERT_GENERIC(a, b, <, text)
#define CASE_ASSERT_BE(a, b, text) CASE_ASSERT_GENERIC(a, b, >=, text)
#define CASE_ASSERT_SE(a, b, text) CASE_ASSERT_GENERIC(a, b, <=, text)

#define CASE_CHECK_EQ(a, b, text) CASE_CHECK_GENERIC(a, b, ==, text)
#define CASE_CHECK_NE(a, b, text) CASE_CHECK_GENERIC(a, b, !=, text)
#define CASE_CHECK_BT(a, b, text) CASE_CHECK_GENERIC(a, b, >, text)
#define CASE_CHECK_ST(a, b, text) CASE_CHECK_GENERIC(a, b, <, text)
#define CASE_CHECK_BE(a, b, text) CASE_CHECK_GENERIC(a, b, >=, text)
#define CASE_CHECK_SE(a, b, text) CASE_CHECK_GENERIC(a, b, <=, text)

#endif // !TEST_CASE_UTILS_H
