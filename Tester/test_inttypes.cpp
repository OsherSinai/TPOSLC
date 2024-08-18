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
#include <include/inttypes.h>
#include <include/stdlib.h>
#include <include/string.h>
#include <include/time.h>
#include <include/wchar.h>
#include <include/math.h>

void test_imaxdiv()
{
	imaxdiv_t dt;
	dt = imaxdiv(49, 10);
	CASE_CHECK_EQ(dt.quot, 4ll, "imaxdiv, quote");
	CASE_CHECK_EQ(dt.rem, 9ll, "imaxdiv, rem");
}

void test_imaxabs()
{
	CASE_CHECK_EQ(imaxabs(1ll), 1ll, "imaxabs 1");
	CASE_CHECK_EQ(imaxabs(-1ll), 1ll, "imaxabs -1");
	CASE_CHECK_EQ(imaxabs(0ll), 0ll, "imaxabs 0");
}

void test_strtoimax()
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
	CASE_CHECK_EQ(strtoimax(strbin, &endptr, 2), 10ll, "strtoimax 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoimax 2, bin endptr");
	CASE_CHECK_EQ(strtoimax(stroct, &endptr, 2), 1ll, "strtoimax 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtoimax 2, oct endptr");
	CASE_CHECK_EQ(strtoimax(strdec, &endptr, 2), 1ll, "strtoimax 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtoimax 2, dec endptr");
	CASE_CHECK_EQ(strtoimax(strhex, &endptr, 2), 0ll, "strtoimax 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoimax 2, hex endptr");
	CASE_CHECK_EQ(strtoimax(strb36, &endptr, 2), 0ll, "strtoimax 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoimax 2, b36 endptr");
	CASE_CHECK_EQ(strtoimax(strbin, &endptr, 8), 520ll, "strtoimax 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoimax 8, bin endptr");
	CASE_CHECK_EQ(strtoimax(stroct, &endptr, 8), 668ll, "strtoimax 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoimax 8, oct endptr");
	CASE_CHECK_EQ(strtoimax(strdec, &endptr, 8), 668ll, "strtoimax 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoimax 8, dec endptr");
	CASE_CHECK_EQ(strtoimax(strhex, &endptr, 8), 0ll, "strtoimax 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoimax 8, hex endptr");
	CASE_CHECK_EQ(strtoimax(strb36, &endptr, 8), 0ll, "strtoimax 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoimax 8, b36 endptr");
	CASE_CHECK_EQ(strtoimax(strbin, &endptr, 10), 1010ll, "strtoimax 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoimax 10, bin endptr");
	CASE_CHECK_EQ(strtoimax(stroct, &endptr, 10), 1234ll, "strtoimax 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoimax 10, oct endptr");
	CASE_CHECK_EQ(strtoimax(strdec, &endptr, 10), 1234ll, "strtoimax 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoimax 10, dec endptr");
	CASE_CHECK_EQ(strtoimax(strhex, &endptr, 10), 0ll, "strtoimax 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoimax 10, hex endptr");
	CASE_CHECK_EQ(strtoimax(strb36, &endptr, 10), 0ll, "strtoimax 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoimax 10, b36 endptr");
	CASE_CHECK_EQ(strtoimax(strbin, &endptr, 16), 0x1010ll, "strtoimax 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoimax 16, bin endptr");
	CASE_CHECK_EQ(strtoimax(stroct, &endptr, 16), 0x1234ll, "strtoimax 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoimax 16, oct endptr");
	CASE_CHECK_EQ(strtoimax(strdec, &endptr, 16), 0x1234ll, "strtoimax 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoimax 16, dec endptr");
	CASE_CHECK_EQ(strtoimax(strhex, &endptr, 16), 0x1234ll, "strtoimax 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtoimax 16, hex endptr");
	CASE_CHECK_EQ(strtoimax(strb36, &endptr, 16), 0ll, "strtoimax 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoimax 16, b36 endptr");
	CASE_CHECK_EQ(strtoimax(strnegbin, &endptr, 2), -10ll, "strtoimax 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoimax 2, neg bin endptr");
	CASE_CHECK_EQ(strtoimax(strnegoct, &endptr, 2), -1ll, "strtoimax 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 3, "strtoimax 2, neg oct endptr");
	CASE_CHECK_EQ(strtoimax(strnegdec, &endptr, 2), -1ll, "strtoimax 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec + 2, "strtoimax 2, neg dec endptr");
	CASE_CHECK_EQ(strtoimax(strneghex, &endptr, 2), 0ll, "strtoimax 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoimax 2, neg hex endptr");
	CASE_CHECK_EQ(strtoimax(strnegb36, &endptr, 2), 0ll, "strtoimax 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoimax 2, neg b36 endptr");
	CASE_CHECK_EQ(strtoimax(strnegbin, &endptr, 8), -520ll, "strtoimax 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoimax 8, neg bin endptr");
	CASE_CHECK_EQ(strtoimax(strnegoct, &endptr, 8), -668ll, "strtoimax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoimax 8, neg oct endptr");
	CASE_CHECK_EQ(strtoimax(strnegdec, &endptr, 8), -668ll, "strtoimax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoimax 8, neg dec endptr");
	CASE_CHECK_EQ(strtoimax(strneghex, &endptr, 8), 0ll, "strtoimax 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoimax 8, neg hex endptr");
	CASE_CHECK_EQ(strtoimax(strnegb36, &endptr, 8), 0ll, "strtoimax 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoimax 8, neg b36 endptr");
	CASE_CHECK_EQ(strtoimax(strnegbin, &endptr, 10), -1010ll, "strtoimax 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoimax 10, neg bin endptr");
	CASE_CHECK_EQ(strtoimax(strnegoct, &endptr, 10), -1234ll, "strtoimax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoimax 10, neg oct endptr");
	CASE_CHECK_EQ(strtoimax(strnegdec, &endptr, 10), -1234ll, "strtoimax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoimax 10, neg dec endptr");
	CASE_CHECK_EQ(strtoimax(strneghex, &endptr, 10), 0ll, "strtoimax 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "strtoimax 10, neg hex endptr");
	CASE_CHECK_EQ(strtoimax(strnegb36, &endptr, 10), 0ll, "strtoimax 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoimax 10, neg b36 endptr");
	CASE_CHECK_EQ(strtoimax(strnegbin, &endptr, 16), -0x1010ll, "strtoimax 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "strtoimax 16, neg bin endptr");
	CASE_CHECK_EQ(strtoimax(strnegoct, &endptr, 16), -0x1234ll, "strtoimax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "strtoimax 16, neg oct endptr");
	CASE_CHECK_EQ(strtoimax(strnegdec, &endptr, 16), -0x1234ll, "strtoimax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "strtoimax 16, neg dec endptr");
	CASE_CHECK_EQ(strtoimax(strneghex, &endptr, 16), -0x1234ll, "strtoimax 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 7, "strtoimax 16, neg hex endptr");
	CASE_CHECK_EQ(strtoimax(strnegb36, &endptr, 16), 0ll, "strtoimax 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "strtoimax 16, neg b36 endptr");
	CASE_CHECK_EQ(strtoimax(strhexoverflow, &endptr, 16), LLONG_MAX, "strtoimax 16, overflow");
	CASE_CHECK_EQ(endptr, strhexoverflow + 18, "strtoimax 16, overflow endptr");
	CASE_CHECK_EQ(strtoimax(strhexunderflow, &endptr, 16), LLONG_MIN, "strtoimax 16, underflow");
	CASE_CHECK_EQ(endptr, strhexunderflow + 19, "strtoimax 16, underflow endptr");
}

void test_wcstoimax()
{
	const wchar_t strbin[] = L"1010p";
	const wchar_t stroct[] = L"01234p";
	const wchar_t strdec[] = L"1234p";
	const wchar_t strhex[] = L"0x1234p";
	const wchar_t strb36[] = L"junk";
	const wchar_t strnegbin[] = L"-1010p";
	const wchar_t strnegdec[] = L"-1234p";
	const wchar_t strneghex[] = L"-0x1234p";
	const wchar_t strnegoct[] = L"-01234p";
	const wchar_t strnegb36[] = L"-junk";
	const wchar_t strhexoverflow[] = L"0xFFFFFFFFFFFFFFFFp";
	const wchar_t strhexunderflow[] = L"-0xFFFFFFFFFFFFFFFFp";
	wchar_t* endptr = 0;
	CASE_CHECK_EQ(wcstoimax(strbin, &endptr, 2), 10ll, "wcstoimax 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoimax 2, bin endptr");
	CASE_CHECK_EQ(wcstoimax(stroct, &endptr, 2), 1ll, "wcstoimax 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "wcstoimax 2, oct endptr");
	CASE_CHECK_EQ(wcstoimax(strdec, &endptr, 2), 1ll, "wcstoimax 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "wcstoimax 2, dec endptr");
	CASE_CHECK_EQ(wcstoimax(strhex, &endptr, 2), 0ll, "wcstoimax 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoimax 2, hex endptr");
	CASE_CHECK_EQ(wcstoimax(strb36, &endptr, 2), 0ll, "wcstoimax 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoimax 2, b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strbin, &endptr, 8), 520ll, "wcstoimax 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoimax 8, bin endptr");
	CASE_CHECK_EQ(wcstoimax(stroct, &endptr, 8), 668ll, "wcstoimax 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoimax 8, oct endptr");
	CASE_CHECK_EQ(wcstoimax(strdec, &endptr, 8), 668ll, "wcstoimax 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoimax 8, dec endptr");
	CASE_CHECK_EQ(wcstoimax(strhex, &endptr, 8), 0ll, "wcstoimax 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoimax 8, hex endptr");
	CASE_CHECK_EQ(wcstoimax(strb36, &endptr, 8), 0ll, "wcstoimax 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoimax 8, b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strbin, &endptr, 10), 1010ll, "wcstoimax 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoimax 10, bin endptr");
	CASE_CHECK_EQ(wcstoimax(stroct, &endptr, 10), 1234ll, "wcstoimax 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoimax 10, oct endptr");
	CASE_CHECK_EQ(wcstoimax(strdec, &endptr, 10), 1234ll, "wcstoimax 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoimax 10, dec endptr");
	CASE_CHECK_EQ(wcstoimax(strhex, &endptr, 10), 0ll, "wcstoimax 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoimax 10, hex endptr");
	CASE_CHECK_EQ(wcstoimax(strb36, &endptr, 10), 0ll, "wcstoimax 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoimax 10, b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strbin, &endptr, 16), 0x1010ll, "wcstoimax 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoimax 16, bin endptr");
	CASE_CHECK_EQ(wcstoimax(stroct, &endptr, 16), 0x1234ll, "wcstoimax 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoimax 16, oct endptr");
	CASE_CHECK_EQ(wcstoimax(strdec, &endptr, 16), 0x1234ll, "wcstoimax 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoimax 16, dec endptr");
	CASE_CHECK_EQ(wcstoimax(strhex, &endptr, 16), 0x1234ll, "wcstoimax 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "wcstoimax 16, hex endptr");
	CASE_CHECK_EQ(wcstoimax(strb36, &endptr, 16), 0ll, "wcstoimax 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoimax 16, b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strnegbin, &endptr, 2), -10ll, "wcstoimax 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "wcstoimax 2, neg bin endptr");
	CASE_CHECK_EQ(wcstoimax(strnegoct, &endptr, 2), -1ll, "wcstoimax 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 3, "wcstoimax 2, neg oct endptr");
	CASE_CHECK_EQ(wcstoimax(strnegdec, &endptr, 2), -1ll, "wcstoimax 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec + 2, "wcstoimax 2, neg dec endptr");
	CASE_CHECK_EQ(wcstoimax(strneghex, &endptr, 2), 0ll, "wcstoimax 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "wcstoimax 2, neg hex endptr");
	CASE_CHECK_EQ(wcstoimax(strnegb36, &endptr, 2), 0ll, "wcstoimax 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "wcstoimax 2, neg b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strnegbin, &endptr, 8), -520ll, "wcstoimax 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "wcstoimax 8, neg bin endptr");
	CASE_CHECK_EQ(wcstoimax(strnegoct, &endptr, 8), -668ll, "wcstoimax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "wcstoimax 8, neg oct endptr");
	CASE_CHECK_EQ(wcstoimax(strnegdec, &endptr, 8), -668ll, "wcstoimax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "wcstoimax 8, neg dec endptr");
	CASE_CHECK_EQ(wcstoimax(strneghex, &endptr, 8), 0ll, "wcstoimax 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "wcstoimax 8, neg hex endptr");
	CASE_CHECK_EQ(wcstoimax(strnegb36, &endptr, 8), 0ll, "wcstoimax 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "wcstoimax 8, neg b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strnegbin, &endptr, 10), -1010ll, "wcstoimax 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "wcstoimax 10, neg bin endptr");
	CASE_CHECK_EQ(wcstoimax(strnegoct, &endptr, 10), -1234ll, "wcstoimax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "wcstoimax 10, neg oct endptr");
	CASE_CHECK_EQ(wcstoimax(strnegdec, &endptr, 10), -1234ll, "wcstoimax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "wcstoimax 10, neg dec endptr");
	CASE_CHECK_EQ(wcstoimax(strneghex, &endptr, 10), 0ll, "wcstoimax 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 2, "wcstoimax 10, neg hex endptr");
	CASE_CHECK_EQ(wcstoimax(strnegb36, &endptr, 10), 0ll, "wcstoimax 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "wcstoimax 10, neg b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strnegbin, &endptr, 16), -0x1010ll, "wcstoimax 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin + 5, "wcstoimax 16, neg bin endptr");
	CASE_CHECK_EQ(wcstoimax(strnegoct, &endptr, 16), -0x1234ll, "wcstoimax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct + 6, "wcstoimax 16, neg oct endptr");
	CASE_CHECK_EQ(wcstoimax(strnegdec, &endptr, 16), -0x1234ll, "wcstoimax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec + 5, "wcstoimax 16, neg dec endptr");
	CASE_CHECK_EQ(wcstoimax(strneghex, &endptr, 16), -0x1234ll, "wcstoimax 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex + 7, "wcstoimax 16, neg hex endptr");
	CASE_CHECK_EQ(wcstoimax(strnegb36, &endptr, 16), 0ll, "wcstoimax 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36 + 1, "wcstoimax 16, neg b36 endptr");
	CASE_CHECK_EQ(wcstoimax(strhexoverflow, &endptr, 16), LLONG_MAX, "wcstoimax 16, overflow");
	CASE_CHECK_EQ(endptr, strhexoverflow + 18, "wcstoimax 16, overflow endptr");
	CASE_CHECK_EQ(wcstoimax(strhexunderflow, &endptr, 16), LLONG_MIN, "wcstoimax 16, underflow");
	CASE_CHECK_EQ(endptr, strhexunderflow + 19, "wcstoimax 16, underflow endptr");
}

void test_strtoumax()
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
	CASE_CHECK_EQ(strtoumax(strbin, &endptr, 2), 10ll, "strtoumax 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoumax 2, bin endptr");
	CASE_CHECK_EQ(strtoumax(stroct, &endptr, 2), 1ll, "strtoumax 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "strtoumax 2, oct endptr");
	CASE_CHECK_EQ(strtoumax(strdec, &endptr, 2), 1ll, "strtoumax 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "strtoumax 2, dec endptr");
	CASE_CHECK_EQ(strtoumax(strhex, &endptr, 2), 0ll, "strtoumax 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoumax 2, hex endptr");
	CASE_CHECK_EQ(strtoumax(strb36, &endptr, 2), 0ll, "strtoumax 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoumax 2, b36 endptr");
	CASE_CHECK_EQ(strtoumax(strbin, &endptr, 8), 520ll, "strtoumax 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoumax 8, bin endptr");
	CASE_CHECK_EQ(strtoumax(stroct, &endptr, 8), 668ll, "strtoumax 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoumax 8, oct endptr");
	CASE_CHECK_EQ(strtoumax(strdec, &endptr, 8), 668ll, "strtoumax 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoumax 8, dec endptr");
	CASE_CHECK_EQ(strtoumax(strhex, &endptr, 8), 0ll, "strtoumax 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoumax 8, hex endptr");
	CASE_CHECK_EQ(strtoumax(strb36, &endptr, 8), 0ll, "strtoumax 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoumax 8, b36 endptr");
	CASE_CHECK_EQ(strtoumax(strbin, &endptr, 10), 1010ll, "strtoumax 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoumax 10, bin endptr");
	CASE_CHECK_EQ(strtoumax(stroct, &endptr, 10), 1234ll, "strtoumax 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoumax 10, oct endptr");
	CASE_CHECK_EQ(strtoumax(strdec, &endptr, 10), 1234ll, "strtoumax 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoumax 10, dec endptr");
	CASE_CHECK_EQ(strtoumax(strhex, &endptr, 10), 0ll, "strtoumax 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "strtoumax 10, hex endptr");
	CASE_CHECK_EQ(strtoumax(strb36, &endptr, 10), 0ll, "strtoumax 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoumax 10, b36 endptr");
	CASE_CHECK_EQ(strtoumax(strbin, &endptr, 16), 0x1010ll, "strtoumax 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "strtoumax 16, bin endptr");
	CASE_CHECK_EQ(strtoumax(stroct, &endptr, 16), 0x1234ll, "strtoumax 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "strtoumax 16, oct endptr");
	CASE_CHECK_EQ(strtoumax(strdec, &endptr, 16), 0x1234ll, "strtoumax 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "strtoumax 16, dec endptr");
	CASE_CHECK_EQ(strtoumax(strhex, &endptr, 16), 0x1234ll, "strtoumax 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "strtoumax 16, hex endptr");
	CASE_CHECK_EQ(strtoumax(strb36, &endptr, 16), 0ll, "strtoumax 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "strtoumax 16, b36 endptr");
	CASE_CHECK_EQ(strtoumax(strnegbin, &endptr, 2), 0, "strtoumax 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoumax 2, neg bin endptr");
	CASE_CHECK_EQ(strtoumax(strnegoct, &endptr, 2), 0, "strtoumax 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoumax 2, neg oct endptr");
	CASE_CHECK_EQ(strtoumax(strnegdec, &endptr, 2), 0, "strtoumax 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoumax 2, neg dec endptr");
	CASE_CHECK_EQ(strtoumax(strneghex, &endptr, 2), 0, "strtoumax 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoumax 2, neg hex endptr");
	CASE_CHECK_EQ(strtoumax(strnegb36, &endptr, 2), 0, "strtoumax 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoumax 2, neg b36 endptr");
	CASE_CHECK_EQ(strtoumax(strnegbin, &endptr, 8), 0, "strtoumax 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoumax 8, neg bin endptr");
	CASE_CHECK_EQ(strtoumax(strnegoct, &endptr, 8), 0, "strtoumax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoumax 8, neg oct endptr");
	CASE_CHECK_EQ(strtoumax(strnegdec, &endptr, 8), 0, "strtoumax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoumax 8, neg dec endptr");
	CASE_CHECK_EQ(strtoumax(strneghex, &endptr, 8), 0ll, "strtoumax 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoumax 8, neg hex endptr");
	CASE_CHECK_EQ(strtoumax(strnegb36, &endptr, 8), 0ll, "strtoumax 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoumax 8, neg b36 endptr");
	CASE_CHECK_EQ(strtoumax(strnegbin, &endptr, 10), 0, "strtoumax 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoumax 10, neg bin endptr");
	CASE_CHECK_EQ(strtoumax(strnegoct, &endptr, 10), 0, "strtoumax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoumax 10, neg oct endptr");
	CASE_CHECK_EQ(strtoumax(strnegdec, &endptr, 10), 0, "strtoumax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoumax 10, neg dec endptr");
	CASE_CHECK_EQ(strtoumax(strneghex, &endptr, 10), 0ll, "strtoumax 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoumax 10, neg hex endptr");
	CASE_CHECK_EQ(strtoumax(strnegb36, &endptr, 10), 0ll, "strtoumax 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoumax 10, neg b36 endptr");
	CASE_CHECK_EQ(strtoumax(strnegbin, &endptr, 16), 0, "strtoumax 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "strtoumax 16, neg bin endptr");
	CASE_CHECK_EQ(strtoumax(strnegoct, &endptr, 16), 0, "strtoumax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "strtoumax 16, neg oct endptr");
	CASE_CHECK_EQ(strtoumax(strnegdec, &endptr, 16), 0, "strtoumax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "strtoumax 16, neg dec endptr");
	CASE_CHECK_EQ(strtoumax(strneghex, &endptr, 16), 0, "strtoumax 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "strtoumax 16, neg hex endptr");
	CASE_CHECK_EQ(strtoumax(strnegb36, &endptr, 16), 0ll, "strtoumax 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "strtoumax 16, neg b36 endptr");
	CASE_CHECK_EQ(strtoumax(strhexoverflow1, &endptr, 16), ULLONG_MAX, "strtoumax 16, overflow1");
	CASE_CHECK_EQ(endptr, strhexoverflow1 + 19, "strtoumax 16, overflow1 endptr");
	CASE_CHECK_EQ(strtoumax(strhexoverflow2, &endptr, 16), ULLONG_MAX, "strtoumax 16, overflow2");
	CASE_CHECK_EQ(endptr, strhexoverflow2 + 19, "strtoumax 16, overflow2 endptr");
}
void test_wcstoumax()
{
	const wchar_t strbin[] = L"1010p";
	const wchar_t stroct[] = L"01234p";
	const wchar_t strdec[] = L"1234p";
	const wchar_t strhex[] = L"0x1234p";
	const wchar_t strb36[] = L"junk";
	const wchar_t strnegbin[] = L"-1010p";
	const wchar_t strnegdec[] = L"-1234p";
	const wchar_t strneghex[] = L"-0x1234p";
	const wchar_t strnegoct[] = L"-01234p";
	const wchar_t strnegb36[] = L"-junk";
	const wchar_t strhexoverflow1[] = L"0xFFFFFFFFFFFFFFFFFp";
	const wchar_t strhexoverflow2[] = L"0xFFFFFFFFFFFFFFFF1p";
	wchar_t* endptr = 0;
	CASE_CHECK_EQ(wcstoumax(strbin, &endptr, 2), 10ll, "wcstoumax 2, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoumax 2, bin endptr");
	CASE_CHECK_EQ(wcstoumax(stroct, &endptr, 2), 1ll, "wcstoumax 2, oct");
	CASE_CHECK_EQ(endptr, stroct + 2, "wcstoumax 2, oct endptr");
	CASE_CHECK_EQ(wcstoumax(strdec, &endptr, 2), 1ll, "wcstoumax 2, dec");
	CASE_CHECK_EQ(endptr, strdec + 1, "wcstoumax 2, dec endptr");
	CASE_CHECK_EQ(wcstoumax(strhex, &endptr, 2), 0ll, "wcstoumax 2, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoumax 2, hex endptr");
	CASE_CHECK_EQ(wcstoumax(strb36, &endptr, 2), 0ll, "wcstoumax 2, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoumax 2, b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strbin, &endptr, 8), 520ll, "wcstoumax 8, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoumax 8, bin endptr");
	CASE_CHECK_EQ(wcstoumax(stroct, &endptr, 8), 668ll, "wcstoumax 8, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoumax 8, oct endptr");
	CASE_CHECK_EQ(wcstoumax(strdec, &endptr, 8), 668ll, "wcstoumax 8, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoumax 8, dec endptr");
	CASE_CHECK_EQ(wcstoumax(strhex, &endptr, 8), 0ll, "wcstoumax 8, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoumax 8, hex endptr");
	CASE_CHECK_EQ(wcstoumax(strb36, &endptr, 8), 0ll, "wcstoumax 8, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoumax 8, b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strbin, &endptr, 10), 1010ll, "wcstoumax 10, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoumax 10, bin endptr");
	CASE_CHECK_EQ(wcstoumax(stroct, &endptr, 10), 1234ll, "wcstoumax 10, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoumax 10, oct endptr");
	CASE_CHECK_EQ(wcstoumax(strdec, &endptr, 10), 1234ll, "wcstoumax 10, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoumax 10, dec endptr");
	CASE_CHECK_EQ(wcstoumax(strhex, &endptr, 10), 0ll, "wcstoumax 10, hex");
	CASE_CHECK_EQ(endptr, strhex + 1, "wcstoumax 10, hex endptr");
	CASE_CHECK_EQ(wcstoumax(strb36, &endptr, 10), 0ll, "wcstoumax 10, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoumax 10, b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strbin, &endptr, 16), 0x1010ll, "wcstoumax 16, bin");
	CASE_CHECK_EQ(endptr, strbin + 4, "wcstoumax 16, bin endptr");
	CASE_CHECK_EQ(wcstoumax(stroct, &endptr, 16), 0x1234ll, "wcstoumax 16, oct");
	CASE_CHECK_EQ(endptr, stroct + 5, "wcstoumax 16, oct endptr");
	CASE_CHECK_EQ(wcstoumax(strdec, &endptr, 16), 0x1234ll, "wcstoumax 16, oct");
	CASE_CHECK_EQ(endptr, strdec + 4, "wcstoumax 16, dec endptr");
	CASE_CHECK_EQ(wcstoumax(strhex, &endptr, 16), 0x1234ll, "wcstoumax 16, hex");
	CASE_CHECK_EQ(endptr, strhex + 6, "wcstoumax 16, hex endptr");
	CASE_CHECK_EQ(wcstoumax(strb36, &endptr, 16), 0ll, "wcstoumax 16, b36");
	CASE_CHECK_EQ(endptr, strb36, "wcstoumax 16, b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strnegbin, &endptr, 2), 0, "wcstoumax 2, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "wcstoumax 2, neg bin endptr");
	CASE_CHECK_EQ(wcstoumax(strnegoct, &endptr, 2), 0, "wcstoumax 2, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "wcstoumax 2, neg oct endptr");
	CASE_CHECK_EQ(wcstoumax(strnegdec, &endptr, 2), 0, "wcstoumax 2, neg dec");
	CASE_CHECK_EQ(endptr, strnegdec, "wcstoumax 2, neg dec endptr");
	CASE_CHECK_EQ(wcstoumax(strneghex, &endptr, 2), 0, "wcstoumax 2, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "wcstoumax 2, neg hex endptr");
	CASE_CHECK_EQ(wcstoumax(strnegb36, &endptr, 2), 0, "wcstoumax 2, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "wcstoumax 2, neg b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strnegbin, &endptr, 8), 0, "wcstoumax 8, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "wcstoumax 8, neg bin endptr");
	CASE_CHECK_EQ(wcstoumax(strnegoct, &endptr, 8), 0, "wcstoumax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "wcstoumax 8, neg oct endptr");
	CASE_CHECK_EQ(wcstoumax(strnegdec, &endptr, 8), 0, "wcstoumax 8, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "wcstoumax 8, neg dec endptr");
	CASE_CHECK_EQ(wcstoumax(strneghex, &endptr, 8), 0ll, "wcstoumax 8, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "wcstoumax 8, neg hex endptr");
	CASE_CHECK_EQ(wcstoumax(strnegb36, &endptr, 8), 0ll, "wcstoumax 8, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "wcstoumax 8, neg b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strnegbin, &endptr, 10), 0, "wcstoumax 10, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "wcstoumax 10, neg bin endptr");
	CASE_CHECK_EQ(wcstoumax(strnegoct, &endptr, 10), 0, "wcstoumax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "wcstoumax 10, neg oct endptr");
	CASE_CHECK_EQ(wcstoumax(strnegdec, &endptr, 10), 0, "wcstoumax 10, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "wcstoumax 10, neg dec endptr");
	CASE_CHECK_EQ(wcstoumax(strneghex, &endptr, 10), 0ll, "wcstoumax 10, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "wcstoumax 10, neg hex endptr");
	CASE_CHECK_EQ(wcstoumax(strnegb36, &endptr, 10), 0ll, "wcstoumax 10, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "wcstoumax 10, neg b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strnegbin, &endptr, 16), 0, "wcstoumax 16, neg bin");
	CASE_CHECK_EQ(endptr, strnegbin, "wcstoumax 16, neg bin endptr");
	CASE_CHECK_EQ(wcstoumax(strnegoct, &endptr, 16), 0, "wcstoumax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegoct, "wcstoumax 16, neg oct endptr");
	CASE_CHECK_EQ(wcstoumax(strnegdec, &endptr, 16), 0, "wcstoumax 16, neg oct");
	CASE_CHECK_EQ(endptr, strnegdec, "wcstoumax 16, neg dec endptr");
	CASE_CHECK_EQ(wcstoumax(strneghex, &endptr, 16), 0, "wcstoumax 16, neg hex");
	CASE_CHECK_EQ(endptr, strneghex, "wcstoumax 16, neg hex endptr");
	CASE_CHECK_EQ(wcstoumax(strnegb36, &endptr, 16), 0ll, "wcstoumax 16, neg b36");
	CASE_CHECK_EQ(endptr, strnegb36, "wcstoumax 16, neg b36 endptr");
	CASE_CHECK_EQ(wcstoumax(strhexoverflow1, &endptr, 16), ULLONG_MAX, "wcstoumax 16, overflow1");
	CASE_CHECK_EQ(endptr, strhexoverflow1 + 19, "wcstoumax 16, overflow1 endptr");
	CASE_CHECK_EQ(wcstoumax(strhexoverflow2, &endptr, 16), ULLONG_MAX, "wcstoumax 16, overflow2");
	CASE_CHECK_EQ(endptr, strhexoverflow2 + 19, "wcstoumax 16, overflow2 endptr");
}

void test_inttypes()
{
	printf("\ntest suite inttypes:\n");
	test_imaxabs();
	test_imaxdiv();
	test_strtoimax();
	test_strtoumax();
	test_wcstoimax();
	test_wcstoumax();
}