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
#ifndef TOS_TIME_H
#define TOS_TIME_H
#include "stddef.h"

typedef size_t clock_t;
typedef ptrdiff_t time_t;

// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
#define TIME_UTC 1

struct timespec {
	time_t tv_sec; // whole seconds - >= 0
	long tv_nsec; // nanoseconds - [0, 999999999]
};

struct tm {
	int tm_sec; // seconds after the minute-- [0, 60]
	int tm_min; // minutes after the hour-- [0, 59]
	int tm_hour; // hours since midnight-- [0, 23]
	int tm_mday; // day of the month-- [1, 31]
	int tm_mon; // months since January-- [0, 11]
	int tm_year; // years since 1900

	int tm_wday; // days since Sunday-- [0, 6]
	int tm_yday; // days since January 1-- [0, 365]
	int tm_isdst; // Daylight Saving Time flag
};

LIBC_DEF_BEGIN

// time_manip.cpp
clock_t clock();
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm* timeptr);
time_t time(time_t* timer);
int timespec_get(struct timespec* ts, int base);


// time_conv.cpp
char* asctime(const struct tm* timeptr);
char* ctime(const time_t* timer);
struct tm* gmtime(const time_t* timer);
struct tm* localtime(const time_t* timer);
size_t strftime(char* restrict s,
	size_t maxsize,
	const char* restrict format,
	const struct tm* restrict timeptr);



LIBC_DEF_END
#endif // !TOS_TIME_H
