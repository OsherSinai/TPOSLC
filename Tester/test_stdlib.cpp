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
#include <include/stdlib.h>
#include <include/string.h>
#include <include/time.h>
#include <include/wchar.h>
#include <include/math.h>
void test_atoi()
{
	CASE_CHECK_EQ(atoi("-1234"), -1234, "atoi correct");
	CASE_CHECK_EQ(atol("-1234"), -1234, "atol correct");
	CASE_CHECK_EQ(atoll("-1234"), -1234, "atoll correct");
	CASE_CHECK_EQ(atoi("0x1234"), 0, "atoi incorrect hex");
	CASE_CHECK_EQ(atol("0x1234"), 0, "atol incorrect hex");
	CASE_CHECK_EQ(atoll("0x1234"), 0, "atoll incorrect hex");
	CASE_CHECK_NE(atoi("x-1234"), -1234, "atoi incorrect");
	CASE_CHECK_NE(atol("x-1234"), -1234, "atol incorrect");
	CASE_CHECK_NE(atoll("x-1234"), -1234, "atoll incorrect");
}

void test_div()
{
	div_t dt;
	ldiv_t ldt;
	lldiv_t lldt;

	dt = div(49, 10);
	CASE_CHECK_EQ(dt.q, 4, "div, quote");
	CASE_CHECK_EQ(dt.rem, 9, "div, rem");
	ldt = ldiv(49, 10);
	CASE_CHECK_EQ(ldt.q, 4, "ldiv, quote");
	CASE_CHECK_EQ(ldt.rem, 9, "ldiv, rem");
	lldt = lldiv(49, 10);
	CASE_CHECK_EQ(lldt.q, 4, "lldiv, quote");
	CASE_CHECK_EQ(lldt.rem, 9, "lldiv, rem");
}

void test_abs()
{
	CASE_CHECK_EQ(abs(1), 1, "abs 1");
	CASE_CHECK_EQ(abs(-1), 1, "abs -1");
	CASE_CHECK_EQ(abs(0), 0, "abs 0");

	CASE_CHECK_EQ(labs(1), 1, "labs 1");
	CASE_CHECK_EQ(labs(-1), 1, "labs -1");
	CASE_CHECK_EQ(labs(0), 0, "labs 0");

	CASE_CHECK_EQ(llabs(1), 1, "llabs 1");
	CASE_CHECK_EQ(llabs(-1), 1, "llabs -1");
	CASE_CHECK_EQ(llabs(0), 0, "llabs 0");
}

static int _test_comp_bigger(const void* p1, const void* p2)
{
	int n1 = *(int*)p1;
	int n2 = *(int*)p2;
	return n2 - n1;
}
static int _test_comp_smaller(const void* p1, const void* p2)
{
	int n1 = *(int*)p1;
	int n2 = *(int*)p2;
	return n1 - n2;
}
void test_search()
{
	const int ctrl_array[10] = {
		0,//0
		1,//1
		2,//2
		3,//3
		4,//4
		4,//5
		5,//6
		6,//7
		7,//8
		8 //9
	};

	int org_array[10] = { 
		1,//0
		4,//1
		3,//2
		5,//3
		2,//4
		4,//5
		6,//6
		8,//7
		7,//8
		0 //9
	};
	int sorted[10] = {0};
	memcpy(sorted, org_array, sizeof(org_array));
	qsort(sorted, 10, 4, _test_comp_smaller);
	CASE_CHECK_EQ(sorted[0], ctrl_array[0], "sort, sorted[0]");
	CASE_CHECK_EQ(sorted[1], ctrl_array[1], "sort, sorted[1]");
	CASE_CHECK_EQ(sorted[2], ctrl_array[2], "sort, sorted[2]");
	CASE_CHECK_EQ(sorted[3], ctrl_array[3], "sort, sorted[3]");
	CASE_CHECK_EQ(sorted[4], ctrl_array[4], "sort, sorted[4]");
	CASE_CHECK_EQ(sorted[5], ctrl_array[5], "sort, sorted[5]");
	CASE_CHECK_EQ(sorted[6], ctrl_array[6], "sort, sorted[6]");
	CASE_CHECK_EQ(sorted[7], ctrl_array[7], "sort, sorted[7]");
	CASE_CHECK_EQ(sorted[8], ctrl_array[8], "sort, sorted[8]");
	CASE_CHECK_EQ(sorted[9], ctrl_array[9], "sort, sorted[9]");


	int* pSearchRet;
	int nKey = 0;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted, "search 0");
	nKey = 1;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted+1, "search 1");
	nKey = 2;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 2, "search 2");
	nKey = 3;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 3, "search 3");
	nKey = 4;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 4, "search 4");
	nKey = 5;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 6, "search 5");
	nKey = 6;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 7, "search 6");
	nKey = 7;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 8, "search 7");
	nKey = 8;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, sorted + 9, "search 8");
	nKey = 11;
	pSearchRet = (int*)bsearch(&nKey, sorted, 10, sizeof(int), _test_comp_bigger);
	CASE_CHECK_EQ(pSearchRet, NULL, "search non existant");
}

void test_rand()
{
	srand(100);
	CASE_CHECK_EQ(rand(), 0x3a0d8a51, "rand, 1");
	CASE_CHECK_EQ(rand(), 0x9b9b1735, "rand, 2");
	CASE_CHECK_EQ(rand(), 0xf8461395, "rand, 3");
	CASE_CHECK_EQ(rand(), 0x70a289f7, "rand, 4");
	srand(time(0));
	return;
}

extern "C" int _tos_CheckPtr(void* ptr);
void test_malloc()
{
	void* aa;
	void* bb;
	void* cc;
	aa = aligned_alloc(16, 48);
	CASE_CHECK_NE(aa, NULL, "aligned_alloc, allocation");
	CASE_CHECK_EQ(_tos_CheckPtr(aa), 0, "aligned_alloc, validity")
	CASE_CHECK_EQ((*(size_t*)&aa) & 0xF, 0, "aligned_alloc, alignment");
	free(aa);
	CASE_CHECK_NE(_tos_CheckPtr(aa), 0, "aligned_alloc, validity after free");

	aa = calloc(16, 48);
	CASE_CHECK_NE(aa, NULL, "calloc, allocation");
	CASE_CHECK_EQ(_tos_CheckPtr(aa), 0, "calloc, validity");
	free(aa);
	CASE_CHECK_NE(_tos_CheckPtr(aa), 0, "calloc, validity after free");

	aa = malloc(16);
	CASE_CHECK_NE(aa, NULL, "malloc, allocation");
	CASE_CHECK_EQ(_tos_CheckPtr(aa), 0, "malloc, validity");
	free(aa);
	CASE_CHECK_NE(_tos_CheckPtr(aa), 0, "malloc, validity after free");

	aa = realloc(0, 16);
	CASE_CHECK_NE(aa, NULL, "realloc, allocation");
	CASE_CHECK_EQ(_tos_CheckPtr(aa), 0, "realloc, validity");
	free(aa);
	CASE_CHECK_NE(_tos_CheckPtr(aa), 0, "realloc, validity after free");

	aa = malloc(16);
	bb = malloc(16);
	cc = realloc(aa, 24);
	CASE_CHECK_NE(cc, NULL, "realloc, allocation");
	CASE_CHECK_EQ(_tos_CheckPtr(cc), 0, "realloc, validity");
	CASE_CHECK_NE(_tos_CheckPtr(aa), 0, "realloc, validity after realloc");
	free(cc);
	CASE_CHECK_NE(_tos_CheckPtr(cc), 0, "realloc, validity after free");
	free(bb);
	CASE_CHECK_NE(_tos_CheckPtr(bb), 0, "realloc, validity after free");
}

void test_system()
{
	CASE_CHECK_EQ(system(0), 0, "system, has parser");
}

void test_getenv()
{
	char* env = getenv("Path");
	CASE_CHECK_NE(env, NULL, "getenv, return");
	CASE_MANUAL_CHECK_START();
	printf("path = [%s]\n", env);
	CASE_MANUAL_CHECK_END();
}


void test_mbstowcs()
{
	wchar_t tmpwc = 0;
	char tmpmb[8] = {0};
	wchar_t orgwcsstr[64] = L"おはよございます！";
	char8_t orgutfstr[128] = u8"おはよございます！";
	wchar_t outputwc[128] = {0};
	char outputc[128] = { 0 };
	char* pch = (char*)orgutfstr;
	CASE_CHECK_EQ(mblen(pch, 64), 3, "check first byte len");
	CASE_CHECK_EQ(mbtowc(&tmpwc, pch, 64), 3, "mbtowc ret");
	CASE_CHECK_EQ(tmpwc, L'お', "mbtowc output");
	CASE_CHECK_EQ(wctomb(tmpmb, tmpwc), 3, "wctomb ret");
	CASE_CHECK_EQ(memcmp(tmpmb, orgutfstr, 3), 0, "wctomb output");
	CASE_CHECK_EQ(mbstowcs(outputwc, pch, 128), 9, "mbstowcs ret");
	CASE_CHECK_EQ(memcmp(outputwc, orgwcsstr, sizeof(wchar_t) * 63), 0, "mbstowcs output");

	CASE_CHECK_EQ(wcstombs(outputc, outputwc, 127), 27, "wcstombs ret");
	CASE_CHECK_EQ(memcmp(outputc, orgutfstr, 128), 0, "wcstombs output");
	return;
}

void test_strtol()
{
	const char strbin[] = "1010p";
	const char stroct[] = "01234p";
	const char strdec[] = "1234p";
	const char strhex[] = "0x1234p";
	const char strb36[] = "junk";
	const char strnegbin[] = "-1010p";
	const char strnegdec[] = "-1234p";
	const char strneghex[] = "-0x1234p";
	const char strnegoct[] = "-01234p";
	const char strnegb36[] = "-junk";
	const char strhexoverflow[] = "0xFFFFFFFFFp";
	const char strhexunderflow[] = "-0xFFFFFFFFFp";
	char* endptr = 0;
	CASE_CHECK_EQ(strtol(strbin, &endptr, 2), 10, "strtol 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtol 2, bin endptr");
	CASE_CHECK_EQ(strtol(stroct, &endptr, 2), 1, "strtol 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtol 2, oct endptr");
	CASE_CHECK_EQ(strtol(strdec, &endptr, 2), 1, "strtol 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtol 2, dec endptr");
	CASE_CHECK_EQ(strtol(strhex, &endptr, 2), 0, "strtol 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtol 2, hex endptr");
	CASE_CHECK_EQ(strtol(strb36, &endptr, 2), 0, "strtol 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtol 2, b36 endptr");

	CASE_CHECK_EQ(strtol(strbin, &endptr, 8), 520, "strtol 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtol 8, bin endptr");
	CASE_CHECK_EQ(strtol(stroct, &endptr, 8), 668, "strtol 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtol 8, oct endptr");
	CASE_CHECK_EQ(strtol(strdec, &endptr, 8), 668, "strtol 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtol 8, dec endptr");
	CASE_CHECK_EQ(strtol(strhex, &endptr, 8), 0, "strtol 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtol 8, hex endptr");
	CASE_CHECK_EQ(strtol(strb36, &endptr, 8), 0, "strtol 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtol 8, b36 endptr");

	CASE_CHECK_EQ(strtol(strbin, &endptr, 10), 1010, "strtol 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtol 10, bin endptr");
	CASE_CHECK_EQ(strtol(stroct, &endptr, 10), 1234, "strtol 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtol 10, oct endptr");
	CASE_CHECK_EQ(strtol(strdec, &endptr, 10), 1234, "strtol 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtol 10, dec endptr");
	CASE_CHECK_EQ(strtol(strhex, &endptr, 10), 0, "strtol 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtol 10, hex endptr");
	CASE_CHECK_EQ(strtol(strb36, &endptr, 10), 0, "strtol 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtol 10, b36 endptr");

	CASE_CHECK_EQ(strtol(strbin, &endptr, 16), 0x1010, "strtol 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtol 16, bin endptr");
	CASE_CHECK_EQ(strtol(stroct, &endptr, 16), 0x1234, "strtol 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtol 16, oct endptr");
	CASE_CHECK_EQ(strtol(strdec, &endptr, 16), 0x1234, "strtol 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtol 16, dec endptr");
	CASE_CHECK_EQ(strtol(strhex, &endptr, 16), 0x1234, "strtol 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtol 16, hex endptr");
	CASE_CHECK_EQ(strtol(strb36, &endptr, 16), 0, "strtol 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtol 16, b36 endptr");


	CASE_CHECK_EQ(strtol(strnegbin, &endptr, 2), -10, "strtol 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtol 2, neg bin endptr");
	CASE_CHECK_EQ(strtol(strnegoct, &endptr, 2), -1, "strtol 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 3, "strtol 2, neg oct endptr");
	CASE_CHECK_EQ(strtol(strnegdec, &endptr, 2), -1, "strtol 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec + 2, "strtol 2, neg dec endptr");
	CASE_CHECK_EQ(strtol(strneghex, &endptr, 2), 0, "strtol 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtol 2, neg hex endptr");
	CASE_CHECK_EQ(strtol(strnegb36, &endptr, 2), 0, "strtol 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36+1, "strtol 2, neg b36 endptr");

	CASE_CHECK_EQ(strtol(strnegbin, &endptr, 8), -520, "strtol 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtol 8, neg bin endptr");
	CASE_CHECK_EQ(strtol(strnegoct, &endptr, 8), -668, "strtol 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtol 8, neg oct endptr");
	CASE_CHECK_EQ(strtol(strnegdec, &endptr, 8), -668, "strtol 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtol 8, neg dec endptr");
	CASE_CHECK_EQ(strtol(strneghex, &endptr, 8), 0, "strtol 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtol 8, neg hex endptr");
	CASE_CHECK_EQ(strtol(strnegb36, &endptr, 8), 0, "strtol 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtol 8, neg b36 endptr");

	CASE_CHECK_EQ(strtol(strnegbin, &endptr, 10), -1010, "strtol 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtol 10, neg bin endptr");
	CASE_CHECK_EQ(strtol(strnegoct, &endptr, 10), -1234, "strtol 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtol 10, neg oct endptr");
	CASE_CHECK_EQ(strtol(strnegdec, &endptr, 10), -1234, "strtol 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtol 10, neg dec endptr");
	CASE_CHECK_EQ(strtol(strneghex, &endptr, 10), 0, "strtol 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtol 10, neg hex endptr");
	CASE_CHECK_EQ(strtol(strnegb36, &endptr, 10), 0, "strtol 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtol 10, neg b36 endptr");

	CASE_CHECK_EQ(strtol(strnegbin, &endptr, 16), -0x1010, "strtol 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtol 16, neg bin endptr");
	CASE_CHECK_EQ(strtol(strnegoct, &endptr, 16), -0x1234, "strtol 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtol 16, neg oct endptr");
	CASE_CHECK_EQ(strtol(strnegdec, &endptr, 16), -0x1234, "strtol 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtol 16, neg dec endptr");
	CASE_CHECK_EQ(strtol(strneghex, &endptr, 16), -0x1234, "strtol 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 7, "strtol 16, neg hex endptr");
	CASE_CHECK_EQ(strtol(strnegb36, &endptr, 16), 0, "strtol 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtol 16, neg b36 endptr");

	CASE_CHECK_EQ(strtol(strhexoverflow, &endptr, 16), LONG_MAX, "strtol 16, overflow");
	CASE_CHECK_EQ(endptr, strhexoverflow + 11, "strtol 16, overflow endptr");
	CASE_CHECK_EQ(strtol(strhexunderflow, &endptr, 16), LONG_MIN, "strtol 16, underflow");
	CASE_CHECK_EQ(endptr, strhexunderflow + 12, "strtol 16, underflow endptr");
}

void test_strtoll()
{
	const char strbin[] = "1010p";
	const char stroct[] = "01234p";
	const char strdec[] = "1234p";
	const char strhex[] = "0x1234p";
	const char strb36[] = "junk";
	const char strnegbin[] = "-1010p";
	const char strnegdec[] = "-1234p";
	const char strneghex[] = "-0x1234p";
	const char strnegoct[] = "-01234p";
	const char strnegb36[] = "-junk";
	const char strhexoverflow[] = "0xFFFFFFFFFFFFFFFFp";
	const char strhexunderflow[] = "-0xFFFFFFFFFFFFFFFFp";
	char* endptr = 0;
	CASE_CHECK_EQ(strtoll(strbin, &endptr, 2), 10ll, "strtoll 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoll 2, bin endptr");
	CASE_CHECK_EQ(strtoll(stroct, &endptr, 2), 1ll, "strtoll 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtoll 2, oct endptr");
	CASE_CHECK_EQ(strtoll(strdec, &endptr, 2), 1ll, "strtoll 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtoll 2, dec endptr");
	CASE_CHECK_EQ(strtoll(strhex, &endptr, 2), 0ll, "strtoll 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoll 2, hex endptr");
	CASE_CHECK_EQ(strtoll(strb36, &endptr, 2), 0ll, "strtoll 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoll 2, b36 endptr");

	CASE_CHECK_EQ(strtoll(strbin, &endptr, 8), 520ll, "strtoll 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoll 8, bin endptr");
	CASE_CHECK_EQ(strtoll(stroct, &endptr, 8), 668ll, "strtoll 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoll 8, oct endptr");
	CASE_CHECK_EQ(strtoll(strdec, &endptr, 8), 668ll, "strtoll 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoll 8, dec endptr");
	CASE_CHECK_EQ(strtoll(strhex, &endptr, 8), 0ll, "strtoll 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoll 8, hex endptr");
	CASE_CHECK_EQ(strtoll(strb36, &endptr, 8), 0ll, "strtoll 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoll 8, b36 endptr");

	CASE_CHECK_EQ(strtoll(strbin, &endptr, 10), 1010ll, "strtoll 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoll 10, bin endptr");
	CASE_CHECK_EQ(strtoll(stroct, &endptr, 10), 1234ll, "strtoll 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoll 10, oct endptr");
	CASE_CHECK_EQ(strtoll(strdec, &endptr, 10), 1234ll, "strtoll 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoll 10, dec endptr");
	CASE_CHECK_EQ(strtoll(strhex, &endptr, 10), 0ll, "strtoll 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoll 10, hex endptr");
	CASE_CHECK_EQ(strtoll(strb36, &endptr, 10), 0ll, "strtoll 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoll 10, b36 endptr");

	CASE_CHECK_EQ(strtoll(strbin, &endptr, 16), 0x1010ll, "strtoll 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoll 16, bin endptr");
	CASE_CHECK_EQ(strtoll(stroct, &endptr, 16), 0x1234ll, "strtoll 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoll 16, oct endptr");
	CASE_CHECK_EQ(strtoll(strdec, &endptr, 16), 0x1234ll, "strtoll 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoll 16, dec endptr");
	CASE_CHECK_EQ(strtoll(strhex, &endptr, 16), 0x1234ll, "strtoll 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtoll 16, hex endptr");
	CASE_CHECK_EQ(strtoll(strb36, &endptr, 16), 0ll, "strtoll 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoll 16, b36 endptr");


	CASE_CHECK_EQ(strtoll(strnegbin, &endptr, 2), -10ll, "strtoll 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoll 2, neg bin endptr");
	CASE_CHECK_EQ(strtoll(strnegoct, &endptr, 2), -1ll, "strtoll 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 3, "strtoll 2, neg oct endptr");
	CASE_CHECK_EQ(strtoll(strnegdec, &endptr, 2), -1ll, "strtoll 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec + 2, "strtoll 2, neg dec endptr");
	CASE_CHECK_EQ(strtoll(strneghex, &endptr, 2), 0ll, "strtoll 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoll 2, neg hex endptr");
	CASE_CHECK_EQ(strtoll(strnegb36, &endptr, 2), 0ll, "strtoll 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoll 2, neg b36 endptr");

	CASE_CHECK_EQ(strtoll(strnegbin, &endptr, 8), -520ll, "strtoll 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoll 8, neg bin endptr");
	CASE_CHECK_EQ(strtoll(strnegoct, &endptr, 8), -668ll, "strtoll 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoll 8, neg oct endptr");
	CASE_CHECK_EQ(strtoll(strnegdec, &endptr, 8), -668ll, "strtoll 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoll 8, neg dec endptr");
	CASE_CHECK_EQ(strtoll(strneghex, &endptr, 8), 0ll, "strtoll 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoll 8, neg hex endptr");
	CASE_CHECK_EQ(strtoll(strnegb36, &endptr, 8), 0ll, "strtoll 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoll 8, neg b36 endptr");

	CASE_CHECK_EQ(strtoll(strnegbin, &endptr, 10), -1010ll, "strtoll 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoll 10, neg bin endptr");
	CASE_CHECK_EQ(strtoll(strnegoct, &endptr, 10), -1234ll, "strtoll 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoll 10, neg oct endptr");
	CASE_CHECK_EQ(strtoll(strnegdec, &endptr, 10), -1234ll, "strtoll 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoll 10, neg dec endptr");
	CASE_CHECK_EQ(strtoll(strneghex, &endptr, 10), 0ll, "strtoll 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoll 10, neg hex endptr");
	CASE_CHECK_EQ(strtoll(strnegb36, &endptr, 10), 0ll, "strtoll 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoll 10, neg b36 endptr");

	CASE_CHECK_EQ(strtoll(strnegbin, &endptr, 16), -0x1010ll, "strtoll 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoll 16, neg bin endptr");
	CASE_CHECK_EQ(strtoll(strnegoct, &endptr, 16), -0x1234ll, "strtoll 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoll 16, neg oct endptr");
	CASE_CHECK_EQ(strtoll(strnegdec, &endptr, 16), -0x1234ll, "strtoll 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoll 16, neg dec endptr");
	CASE_CHECK_EQ(strtoll(strneghex, &endptr, 16), -0x1234ll, "strtoll 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 7, "strtoll 16, neg hex endptr");
	CASE_CHECK_EQ(strtoll(strnegb36, &endptr, 16), 0ll, "strtoll 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoll 16, neg b36 endptr");

	CASE_CHECK_EQ(strtoll(strhexoverflow, &endptr, 16), LLONG_MAX, "strtoll 16, overflow");
	CASE_CHECK_EQ(endptr, strhexoverflow + 18, "strtoll 16, overflow endptr");
	CASE_CHECK_EQ(strtoll(strhexunderflow, &endptr, 16), LLONG_MIN, "strtoll 16, underflow");
	CASE_CHECK_EQ(endptr, strhexunderflow + 19, "strtoll 16, underflow endptr");
}

void test_strtoul()
{
	const char strbin[] = "1010p";
	const char stroct[] = "01234p";
	const char strdec[] = "1234p";
	const char strhex[] = "0x1234p";
	const char strb36[] = "junk";
	const char strnegbin[] = "-1010p";
	const char strnegdec[] = "-1234p";
	const char strneghex[] = "-0x1234p";
	const char strnegoct[] = "-01234p";
	const char strnegb36[] = "-junk";
	const char strhexoverflow[] = "0xFFFFFFFFFFFFFFFFp";
	char* endptr = 0;
	CASE_CHECK_EQ(strtoul(strbin, &endptr, 2), 10ll, "strtoul 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoul 2, bin endptr");
	CASE_CHECK_EQ(strtoul(stroct, &endptr, 2), 1ll, "strtoul 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtoul 2, oct endptr");
	CASE_CHECK_EQ(strtoul(strdec, &endptr, 2), 1ll, "strtoul 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtoul 2, dec endptr");
	CASE_CHECK_EQ(strtoul(strhex, &endptr, 2), 0ll, "strtoul 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoul 2, hex endptr");
	CASE_CHECK_EQ(strtoul(strb36, &endptr, 2), 0ll, "strtoul 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoul 2, b36 endptr");

	CASE_CHECK_EQ(strtoul(strbin, &endptr, 8), 520ll, "strtoul 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoul 8, bin endptr");
	CASE_CHECK_EQ(strtoul(stroct, &endptr, 8), 668ll, "strtoul 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoul 8, oct endptr");
	CASE_CHECK_EQ(strtoul(strdec, &endptr, 8), 668ll, "strtoul 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoul 8, dec endptr");
	CASE_CHECK_EQ(strtoul(strhex, &endptr, 8), 0ll, "strtoul 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoul 8, hex endptr");
	CASE_CHECK_EQ(strtoul(strb36, &endptr, 8), 0ll, "strtoul 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoul 8, b36 endptr");

	CASE_CHECK_EQ(strtoul(strbin, &endptr, 10), 1010ll, "strtoul 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoul 10, bin endptr");
	CASE_CHECK_EQ(strtoul(stroct, &endptr, 10), 1234ll, "strtoul 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoul 10, oct endptr");
	CASE_CHECK_EQ(strtoul(strdec, &endptr, 10), 1234ll, "strtoul 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoul 10, dec endptr");
	CASE_CHECK_EQ(strtoul(strhex, &endptr, 10), 0ll, "strtoul 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoul 10, hex endptr");
	CASE_CHECK_EQ(strtoul(strb36, &endptr, 10), 0ll, "strtoul 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoul 10, b36 endptr");

	CASE_CHECK_EQ(strtoul(strbin, &endptr, 16), 0x1010ll, "strtoul 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoul 16, bin endptr");
	CASE_CHECK_EQ(strtoul(stroct, &endptr, 16), 0x1234ll, "strtoul 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoul 16, oct endptr");
	CASE_CHECK_EQ(strtoul(strdec, &endptr, 16), 0x1234ll, "strtoul 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoul 16, dec endptr");
	CASE_CHECK_EQ(strtoul(strhex, &endptr, 16), 0x1234ll, "strtoul 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtoul 16, hex endptr");
	CASE_CHECK_EQ(strtoul(strb36, &endptr, 16), 0ll, "strtoul 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoul 16, b36 endptr");


	CASE_CHECK_EQ(strtoul(strnegbin, &endptr, 2), 0, "strtoul 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoul 2, neg bin endptr");
	CASE_CHECK_EQ(strtoul(strnegoct, &endptr, 2), 0, "strtoul 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoul 2, neg oct endptr");
	CASE_CHECK_EQ(strtoul(strnegdec, &endptr, 2), 0, "strtoul 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoul 2, neg dec endptr");
	CASE_CHECK_EQ(strtoul(strneghex, &endptr, 2), 0, "strtoul 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoul 2, neg hex endptr");
	CASE_CHECK_EQ(strtoul(strnegb36, &endptr, 2), 0, "strtoul 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoul 2, neg b36 endptr");

	CASE_CHECK_EQ(strtoul(strnegbin, &endptr, 8), 0, "strtoul 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoul 8, neg bin endptr");
	CASE_CHECK_EQ(strtoul(strnegoct, &endptr, 8), 0, "strtoul 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoul 8, neg oct endptr");
	CASE_CHECK_EQ(strtoul(strnegdec, &endptr, 8), 0, "strtoul 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoul 8, neg dec endptr");
	CASE_CHECK_EQ(strtoul(strneghex, &endptr, 8), 0ll, "strtoul 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoul 8, neg hex endptr");
	CASE_CHECK_EQ(strtoul(strnegb36, &endptr, 8), 0ll, "strtoul 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoul 8, neg b36 endptr");

	CASE_CHECK_EQ(strtoul(strnegbin, &endptr, 10), 0, "strtoul 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoul 10, neg bin endptr");
	CASE_CHECK_EQ(strtoul(strnegoct, &endptr, 10), 0, "strtoul 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoul 10, neg oct endptr");
	CASE_CHECK_EQ(strtoul(strnegdec, &endptr, 10), 0, "strtoul 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoul 10, neg dec endptr");
	CASE_CHECK_EQ(strtoul(strneghex, &endptr, 10), 0ll, "strtoul 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoul 10, neg hex endptr");
	CASE_CHECK_EQ(strtoul(strnegb36, &endptr, 10), 0ll, "strtoul 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoul 10, neg b36 endptr");

	CASE_CHECK_EQ(strtoul(strnegbin, &endptr, 16), 0, "strtoul 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoul 16, neg bin endptr");
	CASE_CHECK_EQ(strtoul(strnegoct, &endptr, 16), 0, "strtoul 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoul 16, neg oct endptr");
	CASE_CHECK_EQ(strtoul(strnegdec, &endptr, 16), 0, "strtoul 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoul 16, neg dec endptr");
	CASE_CHECK_EQ(strtoul(strneghex, &endptr, 16), 0, "strtoul 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoul 16, neg hex endptr");
	CASE_CHECK_EQ(strtoul(strnegb36, &endptr, 16), 0ll, "strtoul 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoul 16, neg b36 endptr");

	CASE_CHECK_EQ(strtoul(strhexoverflow, &endptr, 16), ULONG_MAX, "strtoul 16, overflow");
	CASE_CHECK_EQ(endptr, strhexoverflow + 18, "strtoul 16, overflow endptr");
}
void test_strtoull()
{
	const char strbin[] = "1010p";
	const char stroct[] = "01234p";
	const char strdec[] = "1234p";
	const char strhex[] = "0x1234p";
	const char strb36[] = "junk";
	const char strnegbin[] = "-1010p";
	const char strnegdec[] = "-1234p";
	const char strneghex[] = "-0x1234p";
	const char strnegoct[] = "-01234p";
	const char strnegb36[] = "-junk";
	const char strhexoverflow1[] = "0xFFFFFFFFFFFFFFFFFp";
	const char strhexoverflow2[] = "0xFFFFFFFFFFFFFFFF1p";
	char* endptr = 0;
	CASE_CHECK_EQ(strtoull(strbin, &endptr, 2), 10ll, "strtoull 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoull 2, bin endptr");
	CASE_CHECK_EQ(strtoull(stroct, &endptr, 2), 1ll, "strtoull 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtoull 2, oct endptr");
	CASE_CHECK_EQ(strtoull(strdec, &endptr, 2), 1ll, "strtoull 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtoull 2, dec endptr");
	CASE_CHECK_EQ(strtoull(strhex, &endptr, 2), 0ll, "strtoull 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoull 2, hex endptr");
	CASE_CHECK_EQ(strtoull(strb36, &endptr, 2), 0ll, "strtoull 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoull 2, b36 endptr");

	CASE_CHECK_EQ(strtoull(strbin, &endptr, 8), 520ll, "strtoull 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoull 8, bin endptr");
	CASE_CHECK_EQ(strtoull(stroct, &endptr, 8), 668ll, "strtoull 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoull 8, oct endptr");
	CASE_CHECK_EQ(strtoull(strdec, &endptr, 8), 668ll, "strtoull 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoull 8, dec endptr");
	CASE_CHECK_EQ(strtoull(strhex, &endptr, 8), 0ll, "strtoull 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoull 8, hex endptr");
	CASE_CHECK_EQ(strtoull(strb36, &endptr, 8), 0ll, "strtoull 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoull 8, b36 endptr");

	CASE_CHECK_EQ(strtoull(strbin, &endptr, 10), 1010ll, "strtoull 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoull 10, bin endptr");
	CASE_CHECK_EQ(strtoull(stroct, &endptr, 10), 1234ll, "strtoull 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoull 10, oct endptr");
	CASE_CHECK_EQ(strtoull(strdec, &endptr, 10), 1234ll, "strtoull 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoull 10, dec endptr");
	CASE_CHECK_EQ(strtoull(strhex, &endptr, 10), 0ll, "strtoull 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoull 10, hex endptr");
	CASE_CHECK_EQ(strtoull(strb36, &endptr, 10), 0ll, "strtoull 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoull 10, b36 endptr");

	CASE_CHECK_EQ(strtoull(strbin, &endptr, 16), 0x1010ll, "strtoull 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoull 16, bin endptr");
	CASE_CHECK_EQ(strtoull(stroct, &endptr, 16), 0x1234ll, "strtoull 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoull 16, oct endptr");
	CASE_CHECK_EQ(strtoull(strdec, &endptr, 16), 0x1234ll, "strtoull 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoull 16, dec endptr");
	CASE_CHECK_EQ(strtoull(strhex, &endptr, 16), 0x1234ll, "strtoull 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtoull 16, hex endptr");
	CASE_CHECK_EQ(strtoull(strb36, &endptr, 16), 0ll, "strtoull 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoull 16, b36 endptr");


	CASE_CHECK_EQ(strtoull(strnegbin, &endptr, 2), 0, "strtoull 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoull 2, neg bin endptr");
	CASE_CHECK_EQ(strtoull(strnegoct, &endptr, 2), 0, "strtoull 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoull 2, neg oct endptr");
	CASE_CHECK_EQ(strtoull(strnegdec, &endptr, 2), 0, "strtoull 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoull 2, neg dec endptr");
	CASE_CHECK_EQ(strtoull(strneghex, &endptr, 2), 0, "strtoull 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoull 2, neg hex endptr");
	CASE_CHECK_EQ(strtoull(strnegb36, &endptr, 2), 0, "strtoull 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoull 2, neg b36 endptr");

	CASE_CHECK_EQ(strtoull(strnegbin, &endptr, 8), 0, "strtoull 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoull 8, neg bin endptr");
	CASE_CHECK_EQ(strtoull(strnegoct, &endptr, 8), 0, "strtoull 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoull 8, neg oct endptr");
	CASE_CHECK_EQ(strtoull(strnegdec, &endptr, 8), 0, "strtoull 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoull 8, neg dec endptr");
	CASE_CHECK_EQ(strtoull(strneghex, &endptr, 8), 0ll, "strtoull 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoull 8, neg hex endptr");
	CASE_CHECK_EQ(strtoull(strnegb36, &endptr, 8), 0ll, "strtoull 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoull 8, neg b36 endptr");

	CASE_CHECK_EQ(strtoull(strnegbin, &endptr, 10), 0, "strtoull 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoull 10, neg bin endptr");
	CASE_CHECK_EQ(strtoull(strnegoct, &endptr, 10), 0, "strtoull 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoull 10, neg oct endptr");
	CASE_CHECK_EQ(strtoull(strnegdec, &endptr, 10), 0, "strtoull 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoull 10, neg dec endptr");
	CASE_CHECK_EQ(strtoull(strneghex, &endptr, 10), 0ll, "strtoull 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoull 10, neg hex endptr");
	CASE_CHECK_EQ(strtoull(strnegb36, &endptr, 10), 0ll, "strtoull 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoull 10, neg b36 endptr");

	CASE_CHECK_EQ(strtoull(strnegbin, &endptr, 16), 0, "strtoull 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoull 16, neg bin endptr");
	CASE_CHECK_EQ(strtoull(strnegoct, &endptr, 16), 0, "strtoull 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoull 16, neg oct endptr");
	CASE_CHECK_EQ(strtoull(strnegdec, &endptr, 16), 0, "strtoull 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoull 16, neg dec endptr");
	CASE_CHECK_EQ(strtoull(strneghex, &endptr, 16), 0, "strtoull 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoull 16, neg hex endptr");
	CASE_CHECK_EQ(strtoull(strnegb36, &endptr, 16), 0ll, "strtoull 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoull 16, neg b36 endptr");

	CASE_CHECK_EQ(strtoull(strhexoverflow1, &endptr, 16), ULLONG_MAX, "strtoull 16, overflow1");
	CASE_CHECK_EQ(endptr, strhexoverflow1 + 19, "strtoull 16, overflow1 endptr");
	CASE_CHECK_EQ(strtoull(strhexoverflow2, &endptr, 16), ULLONG_MAX, "strtoull 16, overflow2");
	CASE_CHECK_EQ(endptr, strhexoverflow2 + 19, "strtoull 16, overflow2 endptr");
}

void test_strtold()
{
	char* endptr;
	const char str1[] = "111.11";
	const char str2[] = "-2.22";
	const char str3[] = "Nan";
	const char str4[] = "nan(2)";
	const char str5[] = "iNf";
	const char str6[] = "0X1.BC70A3D70A3D7P+6";
	const char str7[] = "1.18973e+4932zzz";
	CASE_CHECK_EQ(strtold(str1, &endptr), 111.11l, "strtold 111.11");
	CASE_CHECK_EQ(endptr, str1 + 6, "strtold 111.11 endptr");
	CASE_CHECK_EQ(strtold(str2, &endptr), -2.22l, "strtold -2.22");
	CASE_CHECK_EQ(endptr, str2 + 5, "strtold -2.22 endptr");
	CASE_CHECK_NE(isnan(strtold(str3, &endptr)), 0, "strtold nan");
	CASE_CHECK_EQ(endptr, str3 + 3, "strtold nan endptr");
	CASE_CHECK_NE(isnan(strtold(str4, &endptr)), 0, "strtold nan(2)");
	CASE_CHECK_EQ(endptr, str4 + 6, "strtold nan(2) endptr");
	CASE_CHECK_EQ(strtold(str5, &endptr), INFINITY, "strtold inf");
	CASE_CHECK_EQ(endptr, str5 + 3, "strtold inf endptr");
	CASE_CHECK_EQ(strtold(str6, &endptr), 111.11l, "strtold 0X1.BC70A3D70A3D7P+6");
	CASE_CHECK_EQ(endptr, str6 + 20, "strtold 0X1.BC70A3D70A3D7P+6 endptr");
	CASE_CHECK_EQ(strtold(str7, &endptr), INFINITY, "strtold 1.18973e+4932zzz");
	CASE_CHECK_EQ(endptr, str7 + 13, "strtold 1.18973e+4932zzz endptr");

	CASE_CHECK_EQ(strtod(str1, &endptr), 111.11, "strtod 111.11");
	CASE_CHECK_EQ(endptr, str1 + 6, "strtod 111.11 endptr");
	CASE_CHECK_EQ(strtod(str2, &endptr), -2.22, "strtod -2.22");
	CASE_CHECK_EQ(endptr, str2 + 5, "strtod -2.22 endptr");
	CASE_CHECK_NE(isnan(strtod(str3, &endptr)), 0, "strtod nan");
	CASE_CHECK_EQ(endptr, str3 + 3, "strtod nan endptr");
	CASE_CHECK_NE(isnan(strtod(str4, &endptr)), 0, "strtod nan(2)");
	CASE_CHECK_EQ(endptr, str4 + 6, "strtod nan(2) endptr");
	CASE_CHECK_EQ(strtod(str5, &endptr), INFINITY, "strtod inf");
	CASE_CHECK_EQ(endptr, str5 + 3, "strtod inf endptr");
	CASE_CHECK_EQ(strtod(str6, &endptr), 111.11, "strtod 0X1.BC70A3D70A3D7P+6");
	CASE_CHECK_EQ(endptr, str6 + 20, "strtod 0X1.BC70A3D70A3D7P+6 endptr");
	CASE_CHECK_EQ(strtod(str7, &endptr), INFINITY, "strtod 1.18973e+4932zzz");
	CASE_CHECK_EQ(endptr, str7 + 13, "strtod 1.18973e+4932zzz endptr");


	CASE_CHECK_EQ(strtof(str1, &endptr), 111.11f, "strtof 111.11");
	CASE_CHECK_EQ(endptr, str1 + 6, "strtof 111.11 endptr");
	CASE_CHECK_EQ(strtof(str2, &endptr), -2.22f, "strtof -2.22");
	CASE_CHECK_EQ(endptr, str2 + 5, "strtof -2.22 endptr");
	CASE_CHECK_NE(isnan(strtof(str3, &endptr)), 0, "strtof nan");
	CASE_CHECK_EQ(endptr, str3 + 3, "strtof nan endptr");
	CASE_CHECK_NE(isnan(strtof(str4, &endptr)), 0, "strtof nan(2)");
	CASE_CHECK_EQ(endptr, str4 + 6, "strtof nan(2) endptr");
	CASE_CHECK_EQ(strtof(str5, &endptr), INFINITY, "strtof inf");
	CASE_CHECK_EQ(endptr, str5 + 3, "strtof inf endptr");
	CASE_CHECK_EQ(strtof(str6, &endptr), 111.11f, "strtof 0X1.BC70A3D70A3D7P+6");
	CASE_CHECK_EQ(endptr, str6 + 20, "strtof 0X1.BC70A3D70A3D7P+6 endptr");
	CASE_CHECK_EQ(strtof(str7, &endptr), INFINITY, "strtof 1.18973e+4932zzz");
	CASE_CHECK_EQ(endptr, str7 + 13, "strtof 1.18973e+4932zzz endptr");


	CASE_CHECK_EQ(atof(str1), 111.11, "atof 111.11");
	CASE_CHECK_EQ(atof(str2), -2.22, "atof -2.22");
	CASE_CHECK_NE(isnan(atof(str3)), 0, "atof nan");
	CASE_CHECK_NE(isnan(atof(str4)), 0, "atof nan(2)");
	CASE_CHECK_EQ(atof(str5), INFINITY, "atof inf");
	CASE_CHECK_EQ(atof(str6), 111.11, "atof 0X1.BC70A3D70A3D7P+6");
	CASE_CHECK_EQ(atof(str7), INFINITY, "atof 1.18973e+4932zzz");

	return;
}


void test_abort()
{
	CASE_MANUAL_CHECK_START();
	printf("Before abort\n");
	CASE_MANUAL_CHECK_END();
	abort();
	CASE_CHECK_EQ(true, false, "After abort");
}

static void func_at_aexit()
{
	CASE_CHECK_EQ(true, true, "atexit called\n");
}

void test_atexit()
{
	atexit(func_at_aexit);
	CASE_MANUAL_CHECK_START();
	printf("Before exit\n");
	CASE_MANUAL_CHECK_END();
	exit(4);
	CASE_CHECK_EQ(true, false, "After exit");
}

void test_quick_exit()
{
	at_quick_exit(func_at_aexit);
	CASE_MANUAL_CHECK_START();
	printf("Before exit\n");
	CASE_MANUAL_CHECK_END();
	quick_exit(4);
	CASE_CHECK_EQ(true, false, "After quick exit");
}


void test_stdlib()
{
	printf("\ntest suite stdlib:\n");
	test_atoi();
	test_div();
	test_abs();
	test_search();
	test_rand();
	test_malloc();
	test_getenv();
	test_mbstowcs();
	test_strtol();
	test_strtoll();
	test_strtoul();
	test_strtoull();
	test_strtold();
}