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
#include <include/stddef.h>
#include <include/string.h>
#include <include/stdlib.h>
#include <include/stdio.h>
#include <include/ctype.h>
#include <include/errno.h>
void testf_printf()
{
	remove("testing_files/printf_test.txt");
	FILE* pFile = fopen("testing_files/printf_test.txt", "w");
	if (pFile)
	{
		const char c_validation[] = "17872111442017451144201745-861330324592032919917872111442017451144201745-86133032459203291992121021104146210211041462102110416731452504146210211787211144201745114420174598334408277892224171122114433221144332211887766554433221111221144332211443322118877665544332211a aFFEEDDCCBBAA9988%abcdefgh";
		char* sz = (char*)malloc(0x10000);
		if (sz)
		{
			void* ptr = (void*)0xFFEEDDCCBBAA9988LLU;
			char str[] = "abcdefgh";
			int cc = *(int*)str;
			memset(sz, 0, 0x10000);
			uint64_t u64 = 0x8877665544332211LLU;
			int nRet = fprintf(pFile,
				"%hhd%hd%d%ld%lld"
				"%hhi%hi%i%li%lli"
				"%hho%ho%o%lo%llo"
				"%hhu%hu%u%lu%llu"
				"%hhx%hx%x%lx%llx"
				"%hhX%hX%X%lX%llX"
				"%c%2c"
				"%p"
				"%%"
				"%s"
				,
				(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
				(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				cc, cc,
				ptr,
				str
			);
			CASE_CHECK_EQ(nRet, 0x124, "fprintf/vfprintf/printf  ret check");
			fclose(pFile);
			pFile = fopen("testing_files/printf_test.txt", "r");
			if (pFile)
			{
				fread(sz, 1, 0xFFFF, pFile);
				const char* p1 = c_validation;
				const char* p2 = sz;
				while (tolower(*p1) == tolower(*p2))
				{
					if (*p1 == 0)
						break;
					if (*p2 == 0)
						break;
					p1++;
					p2++;
				}
				CASE_CHECK_EQ(*p1, *p2, "fprintf/vfprintf/printf check");
				CASE_MANUAL_CHECK_START();
				printf("NOTICE: the this implementation doesn't yet implement floating point conversion and doesn't check it\n");
				CASE_MANUAL_CHECK_END();
			}
			remove("testing_files/printf_test.txt");
			free(sz);
		}
		fclose(pFile);
	}
}
void test_sprintf()
{
	char* sz = (char*)malloc(0x10000);
	if (sz)
	{
		const char c_validation[] = "17872111442017451144201745-861330324592032919917872111442017451144201745-86133032459203291992121021104146210211041462102110416731452504146210211787211144201745114420174598334408277892224171122114433221144332211887766554433221111221144332211443322118877665544332211a aFFEEDDCCBBAA9988%abcdefgh";
		void* ptr = (void*)0xFFEEDDCCBBAA9988LLU;
		char str[] = "abcdefgh";
		int cc = *(int*)str;
		memset(sz, 0, 0x10000);
		uint64_t u64 = 0x8877665544332211LLU;
		int nRet = snprintf(sz, 0xFFFF,
			"%hhd%hd%d%ld%lld"
			"%hhi%hi%i%li%lli"
			"%hho%ho%o%lo%llo"
			"%hhu%hu%u%lu%llu"
			"%hhx%hx%x%lx%llx"
			"%hhX%hX%X%lX%llX"
			"%c%2c"
			"%p"
			"%%"
			"%s"
			,
			(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
			(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			cc, cc,
			ptr,
			str
		);
		const char* p1 = c_validation;
		const char* p2 = sz;
		while (tolower(*p1) == tolower(*p2))
		{
			if (*p1 == 0)
				break;
			if (*p2 == 0)
				break;
			p1++;
			p2++;
		}
		CASE_CHECK_EQ(nRet, 0x124, "sprintf/snprintf/vprintf/vsprintf/vsnprintf ret check");

		CASE_CHECK_EQ(*p1, *p2, "sprintf/snprintf/vprintf/vsprintf/vsnprintf check");
		CASE_MANUAL_CHECK_START();
		printf("NOTICE: the this implementation doesn't yet implement floating point conversion and doesn't check it\n");
		CASE_MANUAL_CHECK_END();
		free(sz);
	}
}
void test_fscanf()
{
	constexpr uint8_t c_validation_8[6] = { 0x7f, 0x7f, 0x57, 0x7f, 0x27, 0x27 };
	constexpr uint16_t c_validation_16[6] = { 0x0190, 0x0190, 0x0100, 0x0190, 0x0400, 0x0400 };
	constexpr uint32_t c_validation_32_1[6] = { 0x000001f4, 0x000001f4, 0x00000140, 0x000001f4, 0x00000500, 0x00000500 };
	constexpr uint32_t c_validation_32_2[6] = { 0x00000294, 0x00000294, 0x000001b0, 0x00000294, 0x00000660, 0x00000660 };
	constexpr uint64_t c_validation_64[6] = { 0xffffffffffffe19f, 0xffffffffffffe19f, 0xfffffffffffff001, 0x000000000000270f, 0x0000000000009999, 0x0000000000009999 };
	int c_validation_cc1 = 0x20;
	int c_validation_cc2 = 0x62622061;
	void* c_validation_p = (void*)0x0000000000001234llu;
	char c_validation_ch[512] = "abcdefg";
	size_t c_validation_ret = 0x0000000000000023;
	int c_validation_n = 0x000000AE;

	FILE* pFile = fopen("testing_files/scanf_test.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "loading scanf_test.txt");
	if (pFile)
	{
		uint8_t u8[6] = { 0 };
		uint16_t u16[6] = { 0 };
		uint32_t u32_1[6] = { 0 };
		uint32_t u32_2[6] = { 0 };
		uint64_t u64[6] = { 0 };
		int cc1 = 0, cc2 = 0;
		void* p = 0;
		char ch[512] = { 0 };
		int n = 0;
		size_t srt = fscanf(pFile,
			"%hhd %hd %d %ld %lld "
			"%hhi %hi %i %li %lli "
			"%hho %ho %o %lo %llo "
			"%hhu %hu %u %lu %llu "
			"%hhx %hx %x %lx %llx "
			"%hhX %hX %X %lX %llX"
			"%c%4c "
			"%p"
			"%% "
			"%s%n",
			u8 + 0, u16 + 0, u32_1 + 0, (long*)u32_2 + 0, u64 + 0,
			u8 + 1, u16 + 1, u32_1 + 1, (long*)u32_2 + 1, u64 + 1,
			u8 + 2, u16 + 2, u32_1 + 2, (unsigned long*)u32_2 + 2, u64 + 2,
			u8 + 3, u16 + 3, u32_1 + 3, (unsigned long*)u32_2 + 3, u64 + 3,
			u8 + 4, u16 + 4, u32_1 + 4, (unsigned long*)u32_2 + 4, u64 + 4,
			u8 + 5, u16 + 5, u32_1 + 5, (unsigned long*)u32_2 + 5, u64 + 5,
			(char*)&cc1, (char*)&cc2,
			&p,
			ch,
			&n
		);
		CASE_CHECK_EQ(srt, c_validation_ret, "fscanf, ret");

		CASE_CHECK_EQ(u8[0], c_validation_8[0], "fscanf, u8[0]");
		CASE_CHECK_EQ(u8[1], c_validation_8[1], "fscanf, u8[1]");
		CASE_CHECK_EQ(u8[2], c_validation_8[2], "fscanf, u8[2]");
		CASE_CHECK_EQ(u8[3], c_validation_8[3], "fscanf, u8[3]");
		CASE_CHECK_EQ(u8[4], c_validation_8[4], "fscanf, u8[4]");
		CASE_CHECK_EQ(u8[5], c_validation_8[5], "fscanf, u8[5]");

		CASE_CHECK_EQ(u16[0], c_validation_16[0], "fscanf, u16[0]");
		CASE_CHECK_EQ(u16[1], c_validation_16[1], "fscanf, u16[1]");
		CASE_CHECK_EQ(u16[2], c_validation_16[2], "fscanf, u16[2]");
		CASE_CHECK_EQ(u16[3], c_validation_16[3], "fscanf, u16[3]");
		CASE_CHECK_EQ(u16[4], c_validation_16[4], "fscanf, u16[4]");
		CASE_CHECK_EQ(u16[5], c_validation_16[5], "fscanf, u16[5]");

		CASE_CHECK_EQ(u32_1[0], c_validation_32_1[0], "fscanf, u32_1[0]");
		CASE_CHECK_EQ(u32_1[1], c_validation_32_1[1], "fscanf, u32_1[1]");
		CASE_CHECK_EQ(u32_1[2], c_validation_32_1[2], "fscanf, u32_1[2]");
		CASE_CHECK_EQ(u32_1[3], c_validation_32_1[3], "fscanf, u32_1[3]");
		CASE_CHECK_EQ(u32_1[4], c_validation_32_1[4], "fscanf, u32_1[4]");
		CASE_CHECK_EQ(u32_1[5], c_validation_32_1[5], "fscanf, u32_1[5]");

		CASE_CHECK_EQ(u32_2[0], c_validation_32_2[0], "fscanf, u32_2[0]");
		CASE_CHECK_EQ(u32_2[1], c_validation_32_2[1], "fscanf, u32_2[1]");
		CASE_CHECK_EQ(u32_2[2], c_validation_32_2[2], "fscanf, u32_2[2]");
		CASE_CHECK_EQ(u32_2[3], c_validation_32_2[3], "fscanf, u32_2[3]");
		CASE_CHECK_EQ(u32_2[4], c_validation_32_2[4], "fscanf, u32_2[4]");
		CASE_CHECK_EQ(u32_2[5], c_validation_32_2[5], "fscanf, u32_2[5]");

		CASE_CHECK_EQ(u64[0], c_validation_64[0], "fscanf, u64[0]");
		CASE_CHECK_EQ(u64[1], c_validation_64[1], "fscanf, u64[1]");
		CASE_CHECK_EQ(u64[2], c_validation_64[2], "fscanf, u64[2]");
		CASE_CHECK_EQ(u64[3], c_validation_64[3], "fscanf, u64[3]");
		CASE_CHECK_EQ(u64[4], c_validation_64[4], "fscanf, u64[4]");
		CASE_CHECK_EQ(u64[5], c_validation_64[5], "fscanf, u64[5]");

		CASE_CHECK_EQ(cc1, c_validation_cc1, "fscanf, cc1");
		CASE_CHECK_EQ(cc2, c_validation_cc2, "fscanf, cc2");

		CASE_CHECK_EQ(p, c_validation_p, "fscanf, ptr");

		CASE_CHECK_EQ(strcmp(ch, c_validation_ch), 0, "fscanf, string");
		CASE_CHECK_EQ(n, c_validation_n, "fscanf, n");
		fclose(pFile);
	}
}
void test_sscanf()
{
	constexpr uint8_t c_validation_8[6] = { 0x7f, 0x7f, 0x57, 0x7f, 0x27, 0x27 };
	constexpr uint16_t c_validation_16[6] = { 0x0190, 0x0190, 0x0100, 0x0190, 0x0400, 0x0400 };
	constexpr uint32_t c_validation_32_1[6] = { 0x000001f4, 0x000001f4, 0x00000140, 0x000001f4, 0x00000500, 0x00000500 };
	constexpr uint32_t c_validation_32_2[6] = { 0x00000294, 0x00000294, 0x000001b0, 0x00000294, 0x00000660, 0x00000660 };
	constexpr uint64_t c_validation_64[6] = { 0xffffffffffffe19f, 0xffffffffffffe19f, 0xfffffffffffff001, 0x000000000000270f, 0x0000000000009999, 0x0000000000009999 };
	int c_validation_cc1 = 0x20;
	int c_validation_cc2 = 0x62622061;
	void* c_validation_p = (void*)0x0000000000001234llu;
	char c_validation_ch[512] = "abcdefg";
	size_t c_validation_ret = 0x0000000000000023;
	int c_validation_n = 0x000000AE;

	uint8_t u8[6] = { 0 };
	uint16_t u16[6] = { 0 };
	uint32_t u32_1[6] = { 0 };
	uint32_t u32_2[6] = { 0 };
	uint64_t u64[6] = { 0 };
	int cc1 = 0, cc2 = 0;
	void* p = 0;
	char ch[512] = { 0 };
	int n = 0;
	const char c_validation[] =
		"127 400 500 660 -7777 "
		"127 400 500 660 -7777 "
		"127 400 500 660 -7777 "
		"0127 0400 0500 0660 09999 "
		"0x127 0x400 0x500 0x660 0x9999 "
		"0x127 0x400 0x500 0x660 0x9999 "
		"a bb "
		"0x1234 "
		"%abcdefg ";
	size_t srt = sscanf(c_validation,
		"%hhd %hd %d %ld %lld "
		"%hhi %hi %i %li %lli "
		"%hho %ho %o %lo %llo "
		"%hhu %hu %u %lu %llu "
		"%hhx %hx %x %lx %llx "
		"%hhX %hX %X %lX %llX"
		"%c%4c "
		"%p"
		"%% "
		"%s%n",
		u8 + 0, u16 + 0, u32_1 + 0, (long*)u32_2 + 0, u64 + 0,
		u8 + 1, u16 + 1, u32_1 + 1, (long*)u32_2 + 1, u64 + 1,
		u8 + 2, u16 + 2, u32_1 + 2, (unsigned long*)u32_2 + 2, u64 + 2,
		u8 + 3, u16 + 3, u32_1 + 3, (unsigned long*)u32_2 + 3, u64 + 3,
		u8 + 4, u16 + 4, u32_1 + 4, (unsigned long*)u32_2 + 4, u64 + 4,
		u8 + 5, u16 + 5, u32_1 + 5, (unsigned long*)u32_2 + 5, u64 + 5,
		(char*)&cc1, (char*)&cc2,
		&p,
		ch,
		&n
	);
	CASE_CHECK_EQ(srt, c_validation_ret, "sscanf, ret");

	CASE_CHECK_EQ(u8[0], c_validation_8[0], "sscanf, u8[0]");
	CASE_CHECK_EQ(u8[1], c_validation_8[1], "sscanf, u8[1]");
	CASE_CHECK_EQ(u8[2], c_validation_8[2], "sscanf, u8[2]");
	CASE_CHECK_EQ(u8[3], c_validation_8[3], "sscanf, u8[3]");
	CASE_CHECK_EQ(u8[4], c_validation_8[4], "sscanf, u8[4]");
	CASE_CHECK_EQ(u8[5], c_validation_8[5], "sscanf, u8[5]");

	CASE_CHECK_EQ(u16[0], c_validation_16[0], "sscanf, u16[0]");
	CASE_CHECK_EQ(u16[1], c_validation_16[1], "sscanf, u16[1]");
	CASE_CHECK_EQ(u16[2], c_validation_16[2], "sscanf, u16[2]");
	CASE_CHECK_EQ(u16[3], c_validation_16[3], "sscanf, u16[3]");
	CASE_CHECK_EQ(u16[4], c_validation_16[4], "sscanf, u16[4]");
	CASE_CHECK_EQ(u16[5], c_validation_16[5], "sscanf, u16[5]");

	CASE_CHECK_EQ(u32_1[0], c_validation_32_1[0], "sscanf, u32_1[0]");
	CASE_CHECK_EQ(u32_1[1], c_validation_32_1[1], "sscanf, u32_1[1]");
	CASE_CHECK_EQ(u32_1[2], c_validation_32_1[2], "sscanf, u32_1[2]");
	CASE_CHECK_EQ(u32_1[3], c_validation_32_1[3], "sscanf, u32_1[3]");
	CASE_CHECK_EQ(u32_1[4], c_validation_32_1[4], "sscanf, u32_1[4]");
	CASE_CHECK_EQ(u32_1[5], c_validation_32_1[5], "sscanf, u32_1[5]");

	CASE_CHECK_EQ(u32_2[0], c_validation_32_2[0], "sscanf, u32_2[0]");
	CASE_CHECK_EQ(u32_2[1], c_validation_32_2[1], "sscanf, u32_2[1]");
	CASE_CHECK_EQ(u32_2[2], c_validation_32_2[2], "sscanf, u32_2[2]");
	CASE_CHECK_EQ(u32_2[3], c_validation_32_2[3], "sscanf, u32_2[3]");
	CASE_CHECK_EQ(u32_2[4], c_validation_32_2[4], "sscanf, u32_2[4]");
	CASE_CHECK_EQ(u32_2[5], c_validation_32_2[5], "sscanf, u32_2[5]");

	CASE_CHECK_EQ(u64[0], c_validation_64[0], "sscanf, u64[0]");
	CASE_CHECK_EQ(u64[1], c_validation_64[1], "sscanf, u64[1]");
	CASE_CHECK_EQ(u64[2], c_validation_64[2], "sscanf, u64[2]");
	CASE_CHECK_EQ(u64[3], c_validation_64[3], "sscanf, u64[3]");
	CASE_CHECK_EQ(u64[4], c_validation_64[4], "sscanf, u64[4]");
	CASE_CHECK_EQ(u64[5], c_validation_64[5], "sscanf, u64[5]");

	CASE_CHECK_EQ(cc1, c_validation_cc1, "sscanf, cc1");
	CASE_CHECK_EQ(cc2, c_validation_cc2, "sscanf, cc2");

	CASE_CHECK_EQ(p, c_validation_p, "sscanf, ptr");

	CASE_CHECK_EQ(strcmp(ch, c_validation_ch), 0, "sscanf, string");
	CASE_CHECK_EQ(n, c_validation_n, "sscanf, n");
}

void test_fopen_fclose()
{
	FILE* pFile2;
	FILE* pFile = fopen("testing_files/r.txt", "r");
	CASE_CHECK_EQ(pFile, NULL, "fopen(r), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files\\dummy.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(r), opening dummy file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/w.txt", "w");
	CASE_CHECK_NE(pFile, NULL, "fopen(w), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wx.txt", "wx");
	pFile2 = fopen("testing_files/wx.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(wx), opening nonexistant file");
	CASE_CHECK_EQ(pFile2, NULL, "fopen(wx), opening exclusive file");
	if (pFile)
		fclose(pFile);
	if (pFile2)
		fclose(pFile2);
	pFile = fopen("testing_files/a.txt", "a");
	CASE_CHECK_NE(pFile, NULL, "fopen(a), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/rb.txt", "rb");
	CASE_CHECK_EQ(pFile, NULL, "fopen(rb), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/dummy.txt", "rb");
	CASE_CHECK_NE(pFile, NULL, "fopen(rb), opening dummy file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wb.txt", "wb");
	CASE_CHECK_NE(pFile, NULL, "fopen(wb), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wbx.txt", "wbx");
	pFile2 = fopen("testing_files/wbx.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(wbx), opening nonexistant file");
	CASE_CHECK_EQ(pFile2, NULL, "fopen(wbx), opening exclusive file");
	if (pFile)
		fclose(pFile);
	if (pFile2)
		fclose(pFile2);
	pFile = fopen("testing_files/rp.txt", "r+");
	CASE_CHECK_EQ(pFile, NULL, "fopen(r+), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/dummy.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(r+), opening dummy file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wp.txt", "w+");
	CASE_CHECK_NE(pFile, NULL, "fopen(w+), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wpx.txt", "w+x");
	pFile2 = fopen("testing_files/wpx.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(w+x), opening nonexistant file");
	CASE_CHECK_EQ(pFile2, NULL, "fopen(w+x), opening exclusive file");
	if (pFile)
		fclose(pFile);
	if (pFile2)
		fclose(pFile2);
	pFile = fopen("testing_files/ap.txt", "a+");
	CASE_CHECK_NE(pFile, NULL, "fopen(a+), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/rpb.txt", "r+b");
	CASE_CHECK_EQ(pFile, NULL, "fopen(r+b), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/dummy.txt", "r+b");
	CASE_CHECK_NE(pFile, NULL, "fopen(r+b), opening dummy file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/rbp.txt", "rb+");
	CASE_CHECK_EQ(pFile, NULL, "fopen(rb+), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/dummy.txt", "r+b");
	CASE_CHECK_NE(pFile, NULL, "fopen(r+b), opening dummy file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wpb.txt", "w+b");
	CASE_CHECK_NE(pFile, NULL, "fopen(w+b), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wbp.txt", "wb+");
	CASE_CHECK_NE(pFile, NULL, "fopen(wb+), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/wpbx.txt", "w+bx");
	pFile2 = fopen("testing_files/wpbx.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(w+bx), opening nonexistant file");
	CASE_CHECK_EQ(pFile2, NULL, "fopen(w+bx), opening exclusive file");
	if (pFile)
		fclose(pFile);
	if (pFile2)
		fclose(pFile2);
	pFile = fopen("testing_files/wbpx.txt", "wb+x");
	pFile2 = fopen("testing_files/wbpx.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "fopen(wb+x), opening nonexistant file");
	CASE_CHECK_EQ(pFile2, NULL, "fopen(wb+x), opening exclusive file");
	if (pFile)
		fclose(pFile);
	if (pFile2)
		fclose(pFile2);
	pFile = fopen("testing_files/apb.txt", "a+b");
	CASE_CHECK_NE(pFile, NULL, "fopen(a+b), opening nonexistant file");
	if (pFile)
		fclose(pFile);
	pFile = fopen("testing_files/abp.txt", "ab+");
	CASE_CHECK_NE(pFile, NULL, "fopen(ab+), opening nonexistant file");
	if (pFile)
		fclose(pFile);

}

static void call_remove()
{
	remove("testing_files/r.txt");
	remove("testing_files/w.txt");
	remove("testing_files/wx.txt");
	remove("testing_files/a.txt");
	remove("testing_files/rb.txt");
	remove("testing_files/wb.txt");
	remove("testing_files/wbx.txt");
	remove("testing_files/rp.txt");
	remove("testing_files/wp.txt");
	remove("testing_files/wpx.txt");
	remove("testing_files/ap.txt");
	remove("testing_files/rpb.txt");
	remove("testing_files/rbp.txt");
	remove("testing_files/wpb.txt");
	remove("testing_files/wbp.txt");
	remove("testing_files/wpbx.txt");
	remove("testing_files/wbpx.txt");
	remove("testing_files/apb.txt");
	remove("testing_files/abp.txt");
}
static void test_remove()
{
	int nRet;
	nRet = remove("testing_files/r.txt");
	CASE_CHECK_NE(nRet, 0, "remove r.txt (doesn't exist)");
	nRet = remove("testing_files/w.txt");
	CASE_CHECK_EQ(nRet, 0, "remove w.txt");
	nRet = remove("testing_files/wx.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wx.txt");
	nRet = remove("testing_files/a.txt");
	CASE_CHECK_EQ(nRet, 0, "remove a.txt");
	nRet = remove("testing_files/rb.txt");
	CASE_CHECK_NE(nRet, 0, "remove rb.txt (doesn't exist)");
	nRet = remove("testing_files/wb.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wb.txt");
	nRet = remove("testing_files/wbx.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wbx.txt");
	nRet = remove("testing_files/rp.txt");
	CASE_CHECK_NE(nRet, 0, "remove (doesn't exist)");
	nRet = remove("testing_files/wp.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wp.txt");
	nRet = remove("testing_files/wpx.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wpx.txt");
	nRet = remove("testing_files/ap.txt");
	CASE_CHECK_EQ(nRet, 0, "remove ap.txt");
	nRet = remove("testing_files/rpb.txt");
	CASE_CHECK_NE(nRet, 0, "remove (doesn't exist)");
	nRet = remove("testing_files/rbp.txt");
	CASE_CHECK_NE(nRet, 0, "remove (doesn't exist)");
	nRet = remove("testing_files/wpb.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wpb.txt");
	nRet = remove("testing_files/wbp.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wbp.txt");
	nRet = remove("testing_files/wpbx.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wpbx.txt");
	nRet = remove("testing_files/wbpx.txt");
	CASE_CHECK_EQ(nRet, 0, "remove wbpx.txt");
	nRet = remove("testing_files/apb.txt");
	CASE_CHECK_EQ(nRet, 0, "remove apb.txt");
	nRet = remove("testing_files/abp.txt");
	CASE_CHECK_EQ(nRet, 0, "remove abp.txt");
}
void test_rename()
{
	FILE* pFile = fopen("testing_files/dummy.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "rename dummy.txt exist");
	if (pFile)
		fclose(pFile);
	int nRet = rename("testing_files/dummy.txt", "testing_files/dummy2.txt");
	CASE_CHECK_EQ(nRet, 0, "rename dummy.txt->dummy2.txt");
	pFile = fopen("testing_files/dummy.txt", "r");
	CASE_CHECK_EQ(pFile, NULL, "rename dummy.txt doesnt exist");
	if (pFile)
		fclose(pFile);
	nRet = rename("testing_files/dummy.txt", "testing_files/dummy3.txt");
	CASE_CHECK_NE(nRet, 0, "rename dummy.txt->dummy3.txt");
	nRet = rename("testing_files/dummy2.txt", "testing_files/dummy.txt");
	CASE_CHECK_EQ(nRet, 0, "rename dummy2.txt->dummy.txt");
	pFile = fopen("testing_files/dummy.txt", "r");
	CASE_CHECK_NE(pFile, NULL, "rename dummy.txt exist");
	if (pFile)
		fclose(pFile);
}

void test_tmpnam()
{
	char temp1[L_tmpnam] = { 0 };
	char temp2[L_tmpnam] = { 0 };
	char* p1 = NULL;
	char* p2 = NULL;
	p1 = tmpnam(temp1);
	p2 = tmpnam(temp2);
	CASE_CHECK_NE(strcmp(temp1, temp2), 0, "tmpnam 1, two calls different");
	CASE_CHECK_NE(p1, NULL, "tmpnam 1, return");
	CASE_CHECK_NE(p1, p2, "tmpnam 1, returns");
	p1 = tmpnam(0);
	p2 = tmpnam(0);
	CASE_CHECK_EQ(strcmp(p1, p2), 0, "tmpnam 2, two calls different");
	CASE_CHECK_NE(p1, NULL, "tmpnam 2, return");
	CASE_CHECK_EQ(p1, p2, "tmpnam 2, returns");
}

void test_tmpfile_fflush_rewind_fread_fwrite()
{
	uint8_t b1[7] = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77 };

	FILE* pFile = tmpfile();
	CASE_CHECK_NE(pFile, 0, "tmpfile created");
	if (pFile)
	{
		size_t wrote = fwrite(b1, 1, sizeof(b1), pFile);
		CASE_CHECK_EQ(wrote, 7, "fwrite, 7");
		int nRet = fflush(pFile);
		CASE_CHECK_EQ(nRet, 0, "fflush, 0");
		rewind(pFile);
		uint16_t tmp1 = 0;
		uint8_t tmp2 = 0;
		wrote = fread(&tmp1, 1, 2, pFile);
		CASE_CHECK_EQ(wrote, 2, "fread ret 1, 2");
		CASE_CHECK_EQ(tmp1, 0x2211, "fread val 1, 0x2211");
		wrote = fread(&tmp1, 1, 2, pFile);
		CASE_CHECK_EQ(wrote, 2, "fread ret 2, 2");
		CASE_CHECK_EQ(tmp1, 0x4433, "fread val 2, 0x4433");
		wrote = fread(&tmp1, 1, 2, pFile);
		CASE_CHECK_EQ(wrote, 2, "fread ret 3, 2");
		CASE_CHECK_EQ(tmp1, 0x6655, "fread val 3, 0x6655");
		wrote = fread(&tmp2, 1, 1, pFile);
		CASE_CHECK_EQ(wrote, 1, "fread ret 4, 1");
		CASE_CHECK_EQ(tmp2, 0x77, "fread val 4, 0x77");

		fclose(pFile);
	}
}

void test_fgetc_fputc_feof_ferror()
{
	FILE* pFile = tmpfile();
	CASE_CHECK_NE(pFile, 0, "tmpfile created");
	if (pFile)
	{
		int nRet = fputc(0x11, pFile);
		CASE_CHECK_EQ(nRet, 0x11, "fputc, ret");
		nRet = fflush(pFile);
		CASE_CHECK_EQ(nRet, 0, "fflush, 0");
		rewind(pFile);
		CASE_CHECK_EQ(feof(pFile), 0, "feof, not eof");
		nRet = fgetc(pFile);
		CASE_CHECK_EQ(nRet, 0x11, "fgetc ret, 0x11");
		nRet = fgetc(pFile);
		CASE_CHECK_EQ(nRet, -1, "fgetc eof");
		CASE_CHECK_NE(feof(pFile), 0, "feof, eof");
		fclose(pFile);
	}
}

void test_fgets_fputs()
{
	char chc[27] = "abcdefghijklmnopqrstuvwxyz";
	char buf[32] = {0};
	char* p = NULL;
	FILE* pFile = tmpfile();
	CASE_CHECK_NE(pFile, 0, "tmpfile created");
	if (pFile)
	{
		int nRet = fputs(chc, pFile);
		CASE_CHECK_BE(nRet, 0, "fputs, ret");
		nRet = fflush(pFile);
		CASE_CHECK_EQ(nRet, 0, "fflush, 0");
		rewind(pFile);
		p = fgets(buf, 31, pFile);
		CASE_CHECK_NE(p, NULL, "fgets ret");
		CASE_CHECK_EQ(strcmp(buf, chc), 0, "fgets buf");
		p = fgets(buf, 31, pFile);
		CASE_CHECK_EQ(p, 0, "fgets eof");

		fclose(pFile);
	}
}

void test_fseek_fsetpos_ftell_fgetpos_ungetc()
{
	constexpr const char c_validation[] = "abcdefghijklmnopqrstuvwxyz";
	constexpr size_t c_validation_len = sizeof(c_validation) - 1;
	char buff[c_validation_len + 1] = { 0 };
	FILE* pFile = fopen("testing_files/abc.txt", "rb");
	if (pFile)
	{
		int ch;
		long pos;
		fpos_t fp;
		for (int i = c_validation_len - 1; i >= 0; i--)
		{
			fseek(pFile, -i - 1, SEEK_END);
			ch = fgetc(pFile);
			buff[c_validation_len - i - 1] = ch;
		}

		CASE_CHECK_EQ(strcmp(buff, c_validation), 0, "fseek");
		for (int i = c_validation_len - 1; i >= 0; i--)
		{
			fp = i;
			fsetpos(pFile, &fp);
			ch = fgetc(pFile);
			buff[i] = ch;
		}

		CASE_CHECK_EQ(strcmp(buff, c_validation), 0, "fsetpos");

		fseek(pFile, 8, SEEK_SET);
		pos = ftell(pFile);
		fgetpos(pFile, &fp);
		ch = fgetc(pFile);
		CASE_CHECK_EQ(fp, 8, "fgetpos, pos");
		CASE_CHECK_EQ(pos, 8, "ftell, pos");
		CASE_CHECK_EQ(ch, c_validation[8], "ftell, val");
		ungetc('!', pFile);
		ch = fgetc(pFile);
		CASE_CHECK_EQ(ch, '!', "ungetc, pushed val");
		ch = fgetc(pFile);
		CASE_CHECK_EQ(ch, c_validation[9], "ungetc, next normal");
		ungetc('!', pFile);
		fseek(pFile, 0, SEEK_CUR);
		ch = fgetc(pFile);
		CASE_CHECK_EQ(ch, c_validation[10], "ungetc, removed unget");


		fclose(pFile);
	}
}

//FILE* freopen(const char* restrict filename, const char* restrict mode, FILE* restrict stream);
//void setbuf(FILE* restrict stream, char* restrict buf);
//int setvbuf(FILE* restrict stream, char* restrict buf, int mode, size_t size);

void test_stdio_errors()
{
	FILE* pFile = fopen("testing_files/dummy.txt", "r");
	CASE_CHECK_NE(pFile, 0, "Dummy file opened");
	if (pFile)
	{
		char ch[2];
		CASE_CHECK_EQ(ferror(pFile), 0, "Error clear");
		putc('1', pFile);
		CASE_CHECK_NE(ferror(pFile), 0, "Error set");
		CASE_CHECK_EQ(feof(pFile), 0, "EOF clear");
		fread(ch, 1, 2, pFile);
		CASE_CHECK_NE(feof(pFile), 0, "EOF set");
		clearerr(pFile);
		CASE_CHECK_EQ(ferror(pFile), 0, "Error cleared");
		CASE_CHECK_EQ(feof(pFile), 0, "EOF cleared");
		fclose(pFile);
	}
}

void test_perror()
{
	//output of perror should be on stderr
	//"test: No message of desired type."
	errno = ENOMSG;

	CASE_MANUAL_CHECK_START();
	printf("void test_perror(): manual check, validate that the square brackets contains \"test: No message of desired type.\"\n[");
	perror("test");
	printf("]\n");
	CASE_MANUAL_CHECK_END();
	errno = 0;
	return;
}

void test_stdio()
{
	printf("\ntest suite stdio:\n");
	call_remove();
	test_fopen_fclose();
	test_remove();
	test_rename();
	test_tmpnam();
	test_tmpfile_fflush_rewind_fread_fwrite();
	test_fgetc_fputc_feof_ferror();
	test_fgets_fputs();
	test_sprintf();
	testf_printf();
	test_sscanf();
	test_fscanf();
	test_fseek_fsetpos_ftell_fgetpos_ungetc();
	test_stdio_errors();
	test_perror();
}