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
#include <include/stdint.h>

void test_stdint()
{
	printf("\ntest suite stdint:\n");

	CASE_CHECK_EQ(sizeof(int8_t),			1, "int8_t size check");
	CASE_CHECK_EQ(sizeof(int16_t),			2, "int16_t size check");
	CASE_CHECK_EQ(sizeof(int32_t),			4, "int32_t size check");
	CASE_CHECK_EQ(sizeof(int64_t),			8, "int64_t size check");
	CASE_CHECK_EQ(sizeof(uint8_t),			1, "uint8_t size check");
	CASE_CHECK_EQ(sizeof(uint16_t),			2, "uint16_t size check");
	CASE_CHECK_EQ(sizeof(uint32_t),			4, "uint32_t size check");
	CASE_CHECK_EQ(sizeof(uint64_t),			8, "uint64_t size check");
	CASE_CHECK_BE(sizeof(int_least8_t),		1, "int_least8_t size check");
	CASE_CHECK_BE(sizeof(int_least16_t),	2, "int_least16_t size check");
	CASE_CHECK_BE(sizeof(int_least32_t),	4, "int_least32_t size check");
	CASE_CHECK_BE(sizeof(int_least64_t),	8, "int_least64_t size check");
	CASE_CHECK_BE(sizeof(uint_least8_t),	1, "uint_least8_t size check");
	CASE_CHECK_BE(sizeof(uint_least16_t),	2, "uint_least16_t size check");
	CASE_CHECK_BE(sizeof(uint_least32_t),	4, "uint_least32_t size check");
	CASE_CHECK_BE(sizeof(uint_least64_t),	8, "uint_least64_t size check");
	CASE_CHECK_BE(sizeof(int_fast8_t),		1, "int_fast8_t size check");
	CASE_CHECK_BE(sizeof(int_fast16_t),		2, "int_fast16_t size check");
	CASE_CHECK_BE(sizeof(int_fast32_t),		4, "int_fast32_t size check");
	CASE_CHECK_BE(sizeof(int_fast64_t),		8, "int_fast64_t size check");
	CASE_CHECK_BE(sizeof(uint_fast8_t),		1, "uint_fast8_t size check");
	CASE_CHECK_BE(sizeof(uint_fast16_t),	2, "uint_fast16_t size check");
	CASE_CHECK_BE(sizeof(uint_fast32_t),	4, "uint_fast32_t size check");
	CASE_CHECK_BE(sizeof(uint_fast64_t),	8, "uint_fast64_t size check");
	CASE_CHECK_EQ(sizeof(intptr_t),			8, "intptr_t size check");
	CASE_CHECK_EQ(sizeof(uintptr_t),		8, "uintptr_t size check");
	CASE_CHECK_EQ(sizeof(intmax_t),			8, "intmax_t size check");
	CASE_CHECK_EQ(sizeof(uintmax_t),		8, "uintmax_t size check");

}