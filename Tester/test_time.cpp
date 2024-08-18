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
#include <include/time.h>
#include <include/threads.h>
#include <include/string.h>
//1721999493 = gmt 13:11:33 7/26/(1900 + 124) 5(fri) 207 1
static constexpr time_t c_TestTime = 1721999493llu;

void test_clock()
{
	timespec duration;
	timespec rem;
	duration.tv_sec = 1;
	duration.tv_nsec = 0;
	clock_t t2;
	clock_t t1 = clock();
	thrd_sleep(&duration, &rem);
	t2 = clock();
	uint64_t dur_ms = 1000 * (t2 - t1) / CLOCKS_PER_SEC;
	CASE_CHECK_BE(dur_ms, 1000, "clock, test 1, check 1sec");
	CASE_CHECK_SE(dur_ms, 1100, "clock, test 2, check 1.1sec");
}

void test_time_func()
{
	time_t tp = 0;
	time_t t = time(&tp);
	time_t t2 = time(0);
	CASE_CHECK_EQ(t, tp, "mktime, test 1, return equal to param");
	CASE_CHECK_NE(t, -1, "mktime, test 2, return equal to param");
	CASE_CHECK_NE(t2, -1, "mktime, test 3, return with param zero");
}

void test_mktime()
{
	time_t currtime = time(0);
	struct tm start = {0};
	struct tm* p = localtime(&currtime);
	if (p) start = *p;
	time_t curr = mktime(&start);
	CASE_CHECK_EQ(curr, currtime, "mktime, return equal to original time");
}

void test_gmtime()
{
	struct tm t = *gmtime(&c_TestTime);
	CASE_CHECK_EQ(t.tm_hour, 13, "gmt time, test 1, hour");
	CASE_CHECK_EQ(t.tm_min, 11, "gmt time, test 2, minute");
	CASE_CHECK_EQ(t.tm_sec, 33, "gmt time, test 3, seconds");
	CASE_CHECK_EQ(t.tm_mon, 6, "gmt time, test 4, month");
	CASE_CHECK_EQ(t.tm_mday, 26, "gmt time, test 5, mday");
	CASE_CHECK_EQ(t.tm_year, 124, "gmt time, test 6, year");
	CASE_CHECK_EQ(t.tm_wday, 5, "gmt time, test 7, week day");
	CASE_CHECK_EQ(t.tm_yday, 207, "gmt time, test 8, year day");
	CASE_CHECK_EQ(t.tm_isdst, 1, "gmt time, test 9, day saving time");
	return;
}
void test_localtime()
{
	time_t currtime = time(0);
	struct tm* p = localtime(&currtime);
	CASE_CHECK_NE(p, 0, "localtime, return non 0");
	if (p)
	{
		struct tm t = *p;
		CASE_MANUAL_CHECK_START();
		printf("manual check:"
			"\t%d:%d:%d %d/%d/%d %d %d daylight saving? %s\n",
			t.tm_hour, t.tm_min, t.tm_sec,
			t.tm_mon + 1, t.tm_mday, t.tm_year + 1900,
			t.tm_wday + 1, t.tm_yday + 1,
			(t.tm_isdst == 0) ? "false" : "true"
		);
		CASE_MANUAL_CHECK_END();
	}
	return;
}

void test_difftime()
{
	struct tm start;
	start.tm_hour = 13;
	start.tm_min = 11;
	start.tm_sec = 33;
	start.tm_mon = 6;
	start.tm_mday = 26;
	start.tm_year = 124;
	start.tm_wday = 5;
	start.tm_yday = 207;
	start.tm_isdst = 1;
	struct tm end;
	end.tm_hour = 15;
	end.tm_min = 14;
	end.tm_sec = 34;
	end.tm_mon = 6;
	end.tm_mday = 26;
	end.tm_year = 124;
	end.tm_wday = 5;
	end.tm_yday = 207;
	end.tm_isdst = 1;
	
	double seconds = difftime(mktime(&end), mktime(&start));
	CASE_CHECK_EQ(seconds, 7381., "difftime, return 7381");

}

void test_asctime()
{
	const char* chk = "Fri Jul 26 13:11:33 2024\n";
	struct tm start;
	start.tm_hour = 13;
	start.tm_min = 11;
	start.tm_sec = 33;
	start.tm_mon = 6;
	start.tm_mday = 26;
	start.tm_year = 124;
	start.tm_wday = 5;
	start.tm_yday = 207;
	start.tm_isdst = 1;
	char* ret = asctime(&start);
	CASE_CHECK_EQ(strcmp(ret, chk), 0, "asctime, return equal to check");

}

void test_ctime()
{
	time_t t = time(0);
	char* ret = ctime(&t);
	CASE_CHECK_NE(ret, 0, "ctime, return check");
	if (ret)
	{
		CASE_MANUAL_CHECK_START();
		printf("manual check:"
			"\t%s",
			ret
		);
		CASE_MANUAL_CHECK_END();
	}
}

void test_strftime()
{
	char StrBuf[4096];
	struct tm start;
	start.tm_hour = 13;
	start.tm_min = 11;
	start.tm_sec = 33;
	start.tm_mon = 6;
	start.tm_mday = 26;
	start.tm_year = 124;
	start.tm_wday = 5;
	start.tm_yday = 207;
	start.tm_isdst = 1;
	memset(StrBuf, 'a', sizeof(StrBuf));
	size_t Size; 

	Size = strftime(StrBuf, 4095, "%%%t%n", &start);
	CASE_CHECK_EQ(Size, 3, "strftime, test 1, return equal 3");
	CASE_CHECK_EQ(strcmp(StrBuf, "%\t\n"), 0, "strftime, test 2, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%Y%EY%y%Oy%Ey%C%EC%G%g", &start);
	CASE_CHECK_EQ(Size, 24, "strftime, test 3, return equal 24");
	CASE_CHECK_EQ(strcmp(StrBuf, "202420242424242020202424"), 0, "strftime, test 4, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%b%Ob%h%B%OB%m%Om", &start);
	CASE_CHECK_EQ(Size, 21, "strftime, test 5, return equal 21");
	CASE_CHECK_EQ(strcmp(StrBuf, "JulJulJulJulyJuly0707"), 0, "strftime, test 6, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%U%OU%W%OW%V%OV", &start);
	CASE_CHECK_EQ(Size, 12, "strftime, test 6, return equal 12");
	CASE_CHECK_EQ(strcmp(StrBuf, "292930303030"), 0, "strftime, test 7, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%j%d%Od%e%Oe", &start);
	CASE_CHECK_EQ(Size, 11, "strftime, test 8, return equal 11");
	CASE_CHECK_EQ(strcmp(StrBuf, "20826262626"), 0, "strftime, test 9, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%a%A%w%Ow%u%Ou", &start);
	CASE_CHECK_EQ(Size, 13, "strftime, test 9, return equal 13");
	CASE_CHECK_EQ(strcmp(StrBuf, "FriFriday5555"), 0, "strftime, test 10, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%H%OH%I%OI%M%OM%S%OS", &start);
	CASE_CHECK_EQ(Size, 16, "strftime, test 11, return equal 16");
	CASE_CHECK_EQ(strcmp(StrBuf, "1313010111113333"), 0, "strftime, test 12, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%c%Ec%x%Ex%X%EX%D%F%r%R%T%p", &start);
	CASE_CHECK_EQ(Size, 124, "strftime, test 11, return equal 129");
	int nStrcmp = strcmp(StrBuf, "Fri Jul 26 13:11:33 2024Fri Jul 26 13:11:33 202407/26/2407/26/2413:11:3313:11:3307/26/242024-07-2601:11:33 PM13:1113:11:33PM");
	CASE_CHECK_EQ(nStrcmp, 0, "strftime, test 12, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%z", &start);
	CASE_CHECK_EQ(Size, 5, "strftime, test 13, return equal 5");
	CASE_MANUAL_CHECK_START();
	printf("manual check: (utc offset) ");
	putc('%', stdout);
	printf("z = %s\n",
		StrBuf
	);
	CASE_MANUAL_CHECK_END();

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = strftime(StrBuf, 4095, "%Z", &start);
	CASE_CHECK_NE(Size, 0, "strftime, test 13, return not equal 0");
	CASE_MANUAL_CHECK_START();
	printf("manual check: (os timezone) ");
	putc('%', stdout);
	printf("Z = %s\n",
		StrBuf
	);
	CASE_MANUAL_CHECK_END();
	return;
}

void test_timespec_get()
{
	struct timespec ts = {0};
	char buff[100];
	int nRet = timespec_get(&ts, TIME_UTC);
	strftime(buff, sizeof(buff), "%D %T", gmtime(&ts.tv_sec));
	CASE_CHECK_EQ(nRet, TIME_UTC, "timespec_get, return equal TIME_UTC");
	CASE_MANUAL_CHECK_START();
	printf("manual check: (current date) = %s\n",
		buff
	);
	CASE_MANUAL_CHECK_END();
	
}

void test_time()
{
	printf("\ntest suite time:\n");
	test_clock();
	test_time_func();
	test_gmtime();
	test_localtime();
	test_difftime();
	test_mktime();
	test_asctime();
	test_ctime();
	test_strftime();
	test_timespec_get();
	return;
}