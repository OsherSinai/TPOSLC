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
#include <include/stdarg.h>
#include <include/stddef.h>
#include <include/string.h>

void test_list(int count, va_list lst)
{
	va_list copy;
	va_copy(copy, lst);
	void* p = va_arg(copy, void*);
	char* str = va_arg(copy, char*);
	uint8_t u8 = (uint8_t)va_arg(copy, uint32_t);
	uint8_t u16 = (uint16_t)va_arg(copy, uint32_t);
	uint8_t u32 = va_arg(copy, uint32_t);
	uint8_t u64 = va_arg(copy, uint64_t);
	int8_t i8 = (int8_t)va_arg(copy, int32_t);
	int8_t i16 = (int16_t)va_arg(copy, int32_t);
	int8_t i32 = va_arg(copy, int32_t);
	int8_t i64 = va_arg(copy, int64_t);
	CASE_CHECK_EQ(p, (void*)0x8877665544332211llu, "copy list, ptr eq");
	CASE_CHECK_EQ(strcmp(str, "test string"), 0, "copy list, ptr eq");
	CASE_CHECK_EQ(u8,  1, "copy list, u8 eq");
	CASE_CHECK_EQ(u16, 2, "copy list, u16 eq");
	CASE_CHECK_EQ(u32, 3, "copy list, u32 eq");
	CASE_CHECK_EQ(u64, 4, "copy list, u64 eq");
	CASE_CHECK_EQ(i8,  5, "copy list, i8 eq");
	CASE_CHECK_EQ(i16, 6, "copy list, i16 eq");
	CASE_CHECK_EQ(i32, 7, "copy list, i32 eq");
	CASE_CHECK_EQ(i64, 8, "copy list, i64 eq");
	va_end(copy);
}

void test_directarg(int count...)
{
	va_list lst;
	va_start(lst, count);
	test_list(count, lst);
	void* p = va_arg(lst, void*);
	char* str = va_arg(lst, char*);
	uint8_t u8 = (uint8_t)va_arg(lst, uint32_t);
	uint8_t u16 = (uint16_t)va_arg(lst, uint32_t);
	uint8_t u32 = va_arg(lst, uint32_t);
	uint8_t u64 = va_arg(lst, uint64_t);
	int8_t i8 = (int8_t)va_arg(lst, int32_t);
	int8_t i16 = (int16_t)va_arg(lst, int32_t);
	int8_t i32 = va_arg(lst, int32_t);
	int8_t i64 = va_arg(lst, int64_t);
	CASE_CHECK_EQ(p, (void*)0x8877665544332211llu, "direct list, ptr eq");
	CASE_CHECK_EQ(strcmp(str, "test string"), 0, "direct list, ptr eq");
	CASE_CHECK_EQ(u8, 1, "direct list, u8 eq");
	CASE_CHECK_EQ(u16, 2, "direct list, u16 eq");
	CASE_CHECK_EQ(u32, 3, "direct list, u32 eq");
	CASE_CHECK_EQ(u64, 4, "direct list, u64 eq");
	CASE_CHECK_EQ(i8, 5, "direct list, i8 eq");
	CASE_CHECK_EQ(i16, 6, "direct list, i16 eq");
	CASE_CHECK_EQ(i32, 7, "direct list, i32 eq");
	CASE_CHECK_EQ(i64, 8, "direct list, i64 eq");

	va_end(lst);
}

void test_stdarg()
{
	printf("\ntest suite stdarg:\n");
	const char* str = "test string";
	int8_t i64 = 8;
	int8_t i32 = 7;
	int8_t i16 = 6;
	int8_t i8 = 5;
	uint8_t u64 = 4;
	uint8_t u32 = 3;
	uint8_t u16 = 2;
	uint8_t u8 = 1;
	void* p = (void*)0x8877665544332211llu;
	test_directarg(10, p, str, u8, u16, u32, u64, i8, i16, i32, i64);
}