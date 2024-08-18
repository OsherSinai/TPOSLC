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
#include <include/time.h>
#include <include/string.h>
#include <include/stdlib.h>
#include <include/inttypes.h>

extern "C" void _tos_NormalizeTM(tm * pTM);

static constexpr const char* c_szWeekdays[7] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednsday",
	"Thursday",
	"Friday",
	"Saturday"
};

static constexpr const char* c_szMonthName[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

enum class TimeParamType {
	error,

	WeekDayAbriv,
	WeekDayFull,
	WeekDayDec,
	WeekDayISO8601,

	YearDay,

	MonthDay2Dig,
	MonthDaySpaced,

	MonthAbriv,
	MonthFull,
	MonthDec,

	YearDec,
	Year2DTrim,
	YearCentury,

	DateMDY,
	DateISO8601,

	YearIOS8601,
	Year2DISO8601,

	DateWeekOfYearISO8601,
	DateWeekOfYearSun,
	DateWeekOfYearMon,

	Seconds,

	Minutes,

	Hour24h,
	//equivalent to “%I:%M:%S %p”.
	Hour12h,
	//one of “AM” or “PM”.
	HourAMPM,

	TimeHourMinute,
	Time12h,
	TimeISO8601,

	//equivalent to “%a %b %e %T %Y”
	LocaleDateAndTime,
	//equivalent to “%m/%d/%y”.
	LocaleDate,
	//equivalent to %T.
	LocaleTime,

	UTCOffset,
	Timezone,

	Tab,
	Newline,
	Percent
};
/*
%a is replaced by the locale’s abbreviated weekday name. [tm_wday]
%A is replaced by the locale’s full weekday name. [tm_wday] is replaced by the locale’s abbreviated month name. [tm_mon]
%w is replaced by the weekday as a decimal number (0–6), where Sunday is 0. [tm_wday]
%u is replaced by the ISO 8601 weekday as a decimal number (1–7), where Monday is 1. [tm_wday]

%j is replaced by the day of the year as a decimal number (001–366). [tm_yday]

%d is replaced by the day of the month as a decimal number (01–31). [tm_mday]
%e is replaced by the day of the month as a decimal number (1–31); a single digit is preceded by a space. [tm_mday]


%B is replaced by the locale’s full month name. [tm_mon]
%h is equivalent to “%b”. [tm_mon]
%m is replaced by the month as a decimal number (01–12). [tm_mon]


%Y is replaced by the year as a decimal number (e.g., 1997). [tm_year]
%y is replaced by the last 2 digits of the year as a decimal number (00–99). [tm_year]
%C is replaced by the year divided by 100 and truncated to an integer, as a decimal number (00–99).[tm_year]


%D is equivalent to “%m/%d/%y”. [tm_mon, tm_mday, tm_year]
%F is equivalent to “%Y-%m-%d” (the ISO 8601 date format). [tm_year, tm_mon, tm_mday]

%G is replaced by the week-based year (see below) as a decimal number (e.g., 1997). [tm_year, tm_wday, tm_yday]
%g is replaced by the last 2 digits of the week-based year (see below) as a decimal number (00–99). [tm_year, tm_wday, tm_yday]

%V is replaced by the ISO 8601 week number (see below) as a decimal number (01–53). [tm_year, tm_wday, tm_yday]
%U is replaced by the week number of the year (the first Sunday as the first day of week 1) as a decimal number (00–53). [tm_year, tm_wday, tm_yday]
%W is replaced by the week number of the year (the first Monday as the first day of week 1) as a decimal number (00–53). [tm_year, tm_wday, tm_yday]

%S is replaced by the second as a decimal number (00–60). [tm_sec]

%M is replaced by the minute as a decimal number (00–59). [tm_min]

%H is replaced by the hour (24-hour clock) as a decimal number (00–23). [tm_hour]
%I is replaced by the hour (12-hour clock) as a decimal number (01–12). [tm_hour]
%p is replaced by the locale’s equivalent of the AM/PM designations associated with a 12-hour clock. [tm_hour]

%R is equivalent to “%H:%M”. [tm_hour, tm_min ]
%r is replaced by the locale’s 12-hour clock time. [tm_hour, tm_min, tm_sec]
%T is equivalent to “%H:%M:%S” (the ISO 8601 time format). [tm_hour, tm_min, tm_sec]

%c is replaced by the locale’s appropriate date and time representation. [all specified in 7.27.1]
%x is replaced by the locale’s appropriate date representation. [all specified in 7.27.1]
%X is replaced by the locale’s appropriate time representation. [all specified in 7.27.1]
%z is replaced by the offset from UTC in the ISO 8601 format “-0430” (meaning 4 hours 30 minutes behind UTC, west of Greenwich), or by no characters if no time zone is determinable. [tm_isdst]
%Z is replaced by the locale’s time zone name or abbreviation, or by no characters if no time zone is determinable. [tm_isdst]
%t is replaced by a horizontal-tab character.
%n is replaced by a new-line character.
%% is replaced by %.

As only the "C" locale is supported E and O modifiers are ignored:
%a the first three characters of %A.
%A one of “Sunday”, “Monday”, . . . , “Saturday”.
%b the first three characters of %B.
%B one of “January”, “February”, . . . , “December”.
%c equivalent to “%a %b %e %T %Y”.
%p one of “AM” or “PM”.
%r equivalent to “%I:%M:%S %p”.
%x equivalent to “%m/%d/%y”.
%X equivalent to %T.
%Z implementation-defined.
*/

static char* basic_zero_lltoa(int64_t i, char buffer[32])
{
	char* ret = &buffer[31];
	*ret = 0;
	memset(buffer, '0', sizeof(char) * 31);
	while (i)
	{
		int64_t mod = i % 10;
		i = i / 10;
		ret--;
		*ret = '0' + mod;
	}
	return ret;
}

static size_t HandleWeekDay(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 0;

	if (TimeParamType::WeekDayAbriv == type)
	{
		const char* szName = c_szWeekdays[timeptr->tm_wday];
		Ret = 3;
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szName, wr);
		}
	}
	else if (TimeParamType::WeekDayFull == type)
	{
		const char* szName = c_szWeekdays[timeptr->tm_wday];
		Ret = strlen(szName);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szName, wr);
		}
	}
	else if (TimeParamType::WeekDayDec == type)
	{
		Ret = 1;
		if (s && remsize)
			*s = timeptr->tm_wday + '0';
	}
	else
	{
		//TimeParamType::WeekDayISO8601 == type
		Ret = 1;
		int wday = timeptr->tm_wday;
		if (wday == 0)
			wday = 7;
		if (s && remsize)
			*s = wday + '0';
	}
	return Ret;
}
static size_t HandleYearDay(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 3;
	if (remsize && s)
	{
		char buffer[32];
		int yday = timeptr->tm_yday + 1;
		basic_zero_lltoa(yday, buffer);
		Ret = 3;
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[28], wr);
		}
	}
	return Ret;
}

static size_t HandleMonthDay(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 2;
	if (remsize && s)
	{
		char buffer[32];
		int yday = timeptr->tm_mday;
		basic_zero_lltoa(yday, buffer);
		if (s)
		{
			if (type == TimeParamType::MonthDaySpaced && buffer[29] == '0')
				buffer[29] = ' ';
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[29], wr);
		}
	}
	return Ret;
}

static size_t HandleMonth(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret;
	if (TimeParamType::MonthAbriv == type)
	{
		const char* szName = c_szMonthName[timeptr->tm_mon];
		Ret = 3;
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szName, wr);
		}
	}
	else if (TimeParamType::MonthFull == type)
	{
		const char* szName = c_szMonthName[timeptr->tm_mon];
		Ret = strlen(szName);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szName, wr);
		}
	}
	else
	{
		//TimeParamType::MonthDec == type
		Ret = 2;
		if (s && remsize)
		{
			char buffer[32];
			basic_zero_lltoa(timeptr->tm_mon+1, buffer);
			//*s = timeptr->tm_wday + '0';
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[29], wr);
		}
	}
	return Ret;
}

static size_t HandleYear(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret;
	char buffer[32];
	char* szYear;
	if (TimeParamType::YearDec == type)
	{
		szYear = basic_zero_lltoa(timeptr->tm_year + 1900, buffer);
		Ret = strlen(szYear);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szYear, wr);
		}
	}
	else if (TimeParamType::Year2DTrim == type)
	{
		basic_zero_lltoa(timeptr->tm_year + 1900, buffer);
		Ret = 2;
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[29], wr);
		}
	}
	else
	{
		//TimeParamType::YearCentury == Type
		szYear = basic_zero_lltoa((timeptr->tm_year + 1900) / 100, buffer);
		Ret = strlen(szYear);
		if (s && remsize)
		{
			
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szYear, wr);
		}
	}
	return Ret;
}

static size_t HandleSeconds(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 2;
	if (remsize && s)
	{
		char buffer[32];
		char* szSeconds = basic_zero_lltoa(timeptr->tm_sec, buffer);
		Ret = strlen(szSeconds);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szSeconds, wr);
		}
	}
	return Ret;
}
static size_t HandleMinutes(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 2;
	if (remsize && s)
	{
		char buffer[32];
		char* szMinutes = basic_zero_lltoa(timeptr->tm_min, buffer);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szMinutes, wr);
		}
	}
	return Ret;
}
static size_t HandleHours(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 2;
	if (remsize && s)
	{
		int hour = timeptr->tm_hour;
		char buffer[32];
		if (type == TimeParamType::Hour12h && hour > 12)
			hour -= 12;
		basic_zero_lltoa(hour, buffer);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[29], wr);
		}
	}
	return Ret;
}

static size_t HandleAMPM(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 2;
	if (remsize && s)
	{
		if (s)
		{
			const char* szAMPM = timeptr->tm_hour > 12 ? "PM" : "AM";
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szAMPM, wr);
		}
	}
	return Ret;
}


static inline size_t _CondSub(size_t remsize, size_t dec)
{
	return dec <= remsize ? remsize - dec : 0;
}
static inline char* _IncS(char* s, size_t inc)
{
	if (s)
	{
		s += inc;
	}
	return s;
}
static inline char* _AssignIncS(char* s, char c, size_t inc)
{
	if (s)
	{
		s += inc;
		*s = c;
		s++;
	}
	return s;
}

static size_t HandleDate(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
/*
%D is equivalent to “%m/%d/%y”. [tm_mon, tm_mday, tm_year]
%F is equivalent to “%Y-%m-%d” (the ISO 8601 date format). [tm_year, tm_mon, tm_mday]
*/
	size_t Ret = 0;
	size_t retsize;
	if (type == TimeParamType::DateMDY)
	{
		//“%m/%d/%y”
		//"MonthDec/MonthDay2Dig/Year2DTrim"
		retsize = HandleMonth(s, remsize, TimeParamType::MonthDec, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, '/', retsize);

		retsize = HandleMonthDay(s, remsize, TimeParamType::MonthDay2Dig, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, '/', retsize);

		retsize = HandleYear(s, remsize, TimeParamType::Year2DTrim, timeptr);
		Ret += retsize;
	}
	else 
	{
		//TimeParamType::DateISO8601
		//“%Y-%m-%d”
		//YearDec-MonthDec-MonthDay2Dig
		retsize = HandleYear(s, remsize, TimeParamType::YearDec, timeptr);
		Ret += retsize;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, '-', retsize);

		retsize = HandleMonth(s, remsize, TimeParamType::MonthDec, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, '-', retsize);

		retsize = HandleMonthDay(s, remsize, TimeParamType::MonthDay2Dig, timeptr);
		Ret += retsize + 1;

	}
	return Ret;
}


/*
	Subtract the weekday number from the ordinal day of the year.
	Add 10.
	Divide by 7, discard the remainder.
		If the week number thus obtained equals 0, 
		it means that the given date belongs to the preceding (week-based) year.
		If a week number of 53 is obtained, 
		one must check that the date is not actually in week 1 of the following year.
*/
static inline int CalculateISO8601WeekNumber(const struct tm* restrict timeptr)
{
	int nRet = timeptr->tm_yday - timeptr->tm_wday + 10;
	return nRet / 7;
}
static inline int CalculateISO8601Year(int* pnWeekNumber, const struct tm* restrict timeptr)
{
	int nRet = timeptr->tm_year + 1900;
	if (*pnWeekNumber == 0)
	{
		//week is in prev year
		nRet--;
		*pnWeekNumber = 53;
	}
	else if (*pnWeekNumber == 53)
	{
		struct tm test = *timeptr;
		test.tm_yday = 0;
		test.tm_mday = 1;
		test.tm_year++;
		_tos_NormalizeTM(&test);
		int nNewWeek = CalculateISO8601WeekNumber(&test);
		if (nNewWeek != 0)
		{
			// week is in next year
			nRet++;
			*pnWeekNumber = nNewWeek;
		}
	}
	return nRet;
}
static size_t HandleISO8601Year(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	/*
	%G is replaced by the week-based year (see below) as a decimal number (e.g., 1997). [tm_year, tm_wday, tm_yday]
	%g is replaced by the last 2 digits of the week-based year (see below) as a decimal number (00–99). [tm_year, tm_wday, tm_yday]
	*/
	size_t Ret = 0;
	char buffer[32];
	int weeknum = CalculateISO8601WeekNumber(timeptr);
	int year = CalculateISO8601Year(&weeknum, timeptr);
	if (type == TimeParamType::YearIOS8601)
	{
		char* szYear = basic_zero_lltoa(year, buffer);
		Ret = strlen(szYear);
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szYear, wr);
		}
	}
	else
	{
		//TimeParamType::Year2DISO8601
		basic_zero_lltoa(year, buffer);
		Ret = 2;
		if (s)
		{
			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, &buffer[29], wr);
		}

	}
	return Ret;
}

/*
static int CalculateWeekOfYear(const struct tm* restrict timeptr, int sun)
{
	int nRet;
	int nWeekdayp7 = timeptr->tm_wday + 7;
	if (sun == 0)
	{
		nWeekdayp7 -= 1;
		nWeekdayp7 = nWeekdayp7 % 7;
		nWeekdayp7 -= 7;
	}
	nRet = timeptr->tm_yday - nWeekdayp7;
	return nRet / 7;
}
*/

static size_t HandleWeekOfYear(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret;
	char buffer[32];
	char* szWeek;
	int year;
	if (TimeParamType::DateWeekOfYearSun == type)
	{
		//U
		//L_('Y') ((tp->tm_yday - tp->tm_wday + 7) / 7)
		year = ((timeptr->tm_yday - timeptr->tm_wday + 7) / 7);
		szWeek = basic_zero_lltoa(year, buffer);
	}
	else if (TimeParamType::DateWeekOfYearMon == type)
	{
		//W
		//L_('W') (tp->tm_yday - (tp->tm_wday - 1 + 7) % 7 + 7) / 7
		year = (timeptr->tm_yday - (timeptr->tm_wday - 1 + 7) % 7 + 7) / 7;
		szWeek = basic_zero_lltoa(year, buffer);
	}
	else
	{
		//TimeParamType::DateWeekOfYearISO8601 == type
		int weeknum = CalculateISO8601WeekNumber(timeptr);
		year = CalculateISO8601Year(&weeknum, timeptr);
		szWeek = basic_zero_lltoa(weeknum, buffer);
	}

	Ret = strlen(szWeek);
	if (s && remsize)
	{

		size_t wr = Ret > remsize ? remsize : Ret;
		memcpy(s, szWeek, wr);
	}
	return Ret;
}


static size_t HandleCompositeTime(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	/*
	%R is equivalent to “%H:%M”. [tm_hour, tm_min ]
	%r is replaced by the locale’s 12-hour clock time. [tm_hour, tm_min, tm_sec]
	%T is equivalent to “%H:%M:%S” (the ISO 8601 time format). [tm_hour, tm_min, tm_sec]
	*/
	size_t Ret = 0;
	size_t retsize;
	if (type == TimeParamType::TimeHourMinute)
	{
		//“%H:%M”
		//TimeParamType::Hour24h:TimeParamType::Minutes
		retsize = HandleHours(s, remsize, TimeParamType::Hour24h, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ':', retsize);

		retsize = HandleMinutes(s, remsize, TimeParamType::Minutes, timeptr);
		Ret += retsize;
	}
	else if(type == TimeParamType::Time12h)
	{
		//%r equivalent to “%I:%M:%S %p”.
		//
		retsize = HandleHours(s, remsize, TimeParamType::Hour12h, timeptr);
		Ret += retsize;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ':', retsize);

		retsize = HandleMinutes(s, remsize, TimeParamType::Minutes, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ':', retsize);

		retsize = HandleSeconds(s, remsize, TimeParamType::Seconds, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ' ', retsize);

		retsize = HandleAMPM(s, remsize, TimeParamType::HourAMPM, timeptr);
		Ret += retsize + 1;
	}
	else
	{
		//TimeISO8601
		//“%H:%M:%S”
		retsize = HandleHours(s, remsize, TimeParamType::Hour24h, timeptr);
		Ret += retsize;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ':', retsize);

		retsize = HandleMinutes(s, remsize, TimeParamType::Minutes, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ':', retsize);

		retsize = HandleSeconds(s, remsize, TimeParamType::Seconds, timeptr);
		Ret += retsize + 1;
	}
	return Ret;
}

extern "C" void _tos_GetUTCOffset(const struct tm* timeptr, int* pnhours, int* pnminutes);
extern "C" void _tos_GetUTCTimezoneName(const struct tm* timeptr, char szName[129]);
static size_t HandleLocaleSpecific(char* restrict s, size_t remsize, TimeParamType type, const struct tm* restrict timeptr)
{
	size_t Ret = 0;
	size_t retsize;
	if (type == TimeParamType::LocaleDateAndTime)
	{
		//equivalent to “%a %b %e %T %Y”
		//WeekDayAbriv MonthAbriv MonthDaySpaced TimeISO8601 YearDec
		//LocaleDateAndTime
		retsize = HandleWeekDay(s, remsize, TimeParamType::WeekDayAbriv, timeptr);
		Ret += retsize;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ' ', retsize);

		retsize = HandleMonth(s, remsize, TimeParamType::MonthAbriv, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ' ', retsize);

		retsize = HandleMonthDay(s, remsize, TimeParamType::MonthDaySpaced, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ' ', retsize);

		retsize = HandleCompositeTime(s, remsize, TimeParamType::TimeISO8601, timeptr);
		Ret += retsize + 1;
		remsize = _CondSub(remsize, retsize);
		s = _AssignIncS(s, ' ', retsize);

		retsize = HandleYear(s, remsize, TimeParamType::YearDec, timeptr);
		Ret += retsize + 1;
	}
	else if (type == TimeParamType::LocaleDate)
	{
		//equivalent to “%m/%d/%y”.
		//LocaleDate = DateMDY
		Ret = HandleDate(s, remsize, TimeParamType::DateMDY, timeptr);
	}
	else if(type == TimeParamType::LocaleTime)
	{
		//equivalent to %T.
		//LocaleTime = TimeISO8601
		Ret = HandleCompositeTime(s, remsize, TimeParamType::TimeISO8601, timeptr);
	}
	else if (type == TimeParamType::UTCOffset)
	{
		//%z is replaced by the offset from UTC in the ISO 8601 format “-0430” (meaning 4 hours 30 minutes behind UTC, west of Greenwich), or by no characters if no time zone is determinable. [tm_isdst]
		//UTCOffset
		char buffer[32];
		int nHour = 0;
		int nMinute = 0;
		Ret = 4;
		_tos_GetUTCOffset(timeptr, &nHour, &nMinute);
		remsize = _CondSub(remsize, 1);
		if (nHour <= 0)
			s = _AssignIncS(s, '+', 0);
		else
			s = _AssignIncS(s, '-', 0);
		nHour = abs(nHour);
		Ret++;
		basic_zero_lltoa(nHour, buffer);
		if (s && remsize)
		{

			size_t wr = 2 > remsize ? remsize : 2;
			memcpy(s, &buffer[29], wr);
			remsize = _CondSub(remsize, wr);
			s = _IncS(s, wr);
		}
		basic_zero_lltoa(nMinute, buffer);
		if (s && remsize)
		{

			size_t wr = 2 > remsize ? remsize : 2;
			memcpy(s, &buffer[29], wr);
			remsize = _CondSub(remsize, wr);
			s = _IncS(s, wr);
		}


	}
	else
	{
		//%Z is replaced by the locale’s time zone name or abbreviation, or by no characters if no time zone is determinable. [tm_isdst]
		//Timezone
		char szName[129];
		memset(szName, 0, sizeof(szName));
		_tos_GetUTCTimezoneName(timeptr, szName);
		Ret = strlen(szName);
		if (s && remsize)
		{

			size_t wr = Ret > remsize ? remsize : Ret;
			memcpy(s, szName, wr);
			remsize -= wr;
		}
	}

	return Ret;
}


static size_t HandleControls(char* restrict s, size_t remsize, TimeParamType type)
{
	if (remsize && s)
	{
		if (type == TimeParamType::Tab)
			*s = '\t';
		else if (type == TimeParamType::Newline)
			*s = '\n';
		else
		{
			//TimeParamType::Percent:
			*s = '%';
		}
	}
	return 1;
}

static bool CheckExtParse(const char* szFmt)
{
	bool bRet = false;
	if (szFmt[0] == 'E')
	{
		switch (szFmt[1])
		{
		case 'Y':
		case 'y':
		case 'C':
		case 'c':
		case 'x':
		case 'X':
			bRet = true;
			break;
		}
	}
	else
	{
		//'O'
		switch (szFmt[1])
		{
		case 'y':
		case 'b':
		case 'B':
		case 'm':
		case 'U':
		case 'W':
		case 'V':
		case 'd':
		case 'e':
		case 'w':
		case 'u':
		case 'H':
		case 'I':
		case 'M':
		case 'S':
			bRet = true;
			break;
		}
	}
	return bRet;
}

static TimeParamType ParseType(const char* szFmt, int* pFmtInc)
{
/*
%a is replaced by the locale’s abbreviated weekday name. [tm_wday]
%A is replaced by the locale’s full weekday name. [tm_wday] is replaced by the locale’s abbreviated month name. [tm_mon]
%w is replaced by the weekday as a decimal number (0–6), where Sunday is 0. [tm_wday]
%u is replaced by the ISO 8601 weekday as a decimal number (1–7), where Monday is 1. [tm_wday]
%j is replaced by the day of the year as a decimal number (001–366). [tm_yday]
%d is replaced by the day of the month as a decimal number (01–31). [tm_mday]
%e is replaced by the day of the month as a decimal number (1–31); a single digit is preceded by a space. [tm_mday]
%B is replaced by the locale’s full month name. [tm_mon]
%h is equivalent to “%b”. [tm_mon]
%m is replaced by the month as a decimal number (01–12). [tm_mon]
%Y is replaced by the year as a decimal number (e.g., 1997). [tm_year]
%y is replaced by the last 2 digits of the year as a decimal number (00–99). [tm_year]
%C is replaced by the year divided by 100 and truncated to an integer, as a decimal number (00–99).[tm_year]
%D is equivalent to “%m/%d/%y”. [tm_mon, tm_mday, tm_year]
%F is equivalent to “%Y-%m-%d” (the ISO 8601 date format). [tm_year, tm_mon, tm_mday]
%G is replaced by the week-based year (see below) as a decimal number (e.g., 1997). [tm_year, tm_wday, tm_yday]
%g is replaced by the last 2 digits of the week-based year (see below) as a decimal number (00–99). [tm_year, tm_wday, tm_yday]
%V is replaced by the ISO 8601 week number (see below) as a decimal number (01–53). [tm_year, tm_wday, tm_yday]
%U is replaced by the week number of the year (the first Sunday as the first day of week 1) as a decimal number (00–53). [tm_year, tm_wday, tm_yday]
%W is replaced by the week number of the year (the first Monday as the first day of week 1) as a decimal number (00–53). [tm_year, tm_wday, tm_yday]
%S is replaced by the second as a decimal number (00–60). [tm_sec]
%M is replaced by the minute as a decimal number (00–59). [tm_min]
%H is replaced by the hour (24-hour clock) as a decimal number (00–23). [tm_hour]
%I is replaced by the hour (12-hour clock) as a decimal number (01–12). [tm_hour]
%p is replaced by the locale’s equivalent of the AM/PM designations associated with a 12-hour clock. [tm_hour]
%R is equivalent to “%H:%M”. [tm_hour, tm_min ]
%r is replaced by the locale’s 12-hour clock time. [tm_hour, tm_min, tm_sec]
%T is equivalent to “%H:%M:%S” (the ISO 8601 time format). [tm_hour, tm_min, tm_sec]
%c is replaced by the locale’s appropriate date and time representation. [all specified in 7.27.1]
%x is replaced by the locale’s appropriate date representation. [all specified in 7.27.1]
%X is replaced by the locale’s appropriate time representation. [all specified in 7.27.1]
%z is replaced by the offset from UTC in the ISO 8601 format “-0430” (meaning 4 hours 30 minutes behind UTC, west of Greenwich), or by no characters if no time zone is determinable. [tm_isdst]
%Z is replaced by the locale’s time zone name or abbreviation, or by no characters if no time zone is determinable. [tm_isdst]
%t is replaced by a horizontal-tab character.
%n is replaced by a new-line character.
%% is replaced by %.
*/
	TimeParamType Ret = TimeParamType::error;
	*pFmtInc = 1;
	switch (*szFmt)
	{
	case 'a':
		Ret = TimeParamType::WeekDayAbriv;
		break;
	case 'A':
		Ret = TimeParamType::WeekDayFull;
		break;
	case 'w':
		Ret = TimeParamType::WeekDayDec;
		break;
	case 'u':
		Ret = TimeParamType::WeekDayISO8601;
		break;
	case 'j':
		Ret = TimeParamType::YearDay;
		break;
	case 'd':
		Ret = TimeParamType::MonthDay2Dig;
		break;
	case 'e':
		Ret = TimeParamType::MonthDaySpaced;
		break;
	case 'h':
	case 'b':
		Ret = TimeParamType::MonthAbriv;
		break;
	case 'B':
		Ret = TimeParamType::MonthFull;
		break;
	case 'm':
		Ret = TimeParamType::MonthDec;
		break;
	case 'Y':
		Ret = TimeParamType::YearDec;
		break;
	case 'y':
		Ret = TimeParamType::Year2DTrim;
		break;
	case 'C':
		Ret = TimeParamType::YearCentury;
		break;
	case 'D':
		Ret = TimeParamType::DateMDY;
		break;
	case 'F':
		Ret = TimeParamType::DateISO8601;
		break;
	case 'G':
		Ret = TimeParamType::YearIOS8601;
		break;
	case 'g':
		Ret = TimeParamType::Year2DISO8601;
		break;
	case 'V':
		Ret = TimeParamType::DateWeekOfYearISO8601;
		break;
	case 'U':
		Ret = TimeParamType::DateWeekOfYearSun;
		break;
	case 'W':
		Ret = TimeParamType::DateWeekOfYearMon;
		break;
	case 'S':
		Ret = TimeParamType::Seconds;
		break;
	case 'M':
		Ret = TimeParamType::Minutes;
		break;
	case 'H':
		Ret = TimeParamType::Hour24h;
		break;
	case 'I':
		Ret = TimeParamType::Hour12h;
		break;
	case 'p':
		Ret = TimeParamType::HourAMPM;
		break;
	case 'R':
		Ret = TimeParamType::TimeHourMinute;
		break;
	case 'r':
		Ret = TimeParamType::Time12h;
		break;
	case 'T':
		Ret = TimeParamType::TimeISO8601;
		break;
	case 'c':
		Ret = TimeParamType::LocaleDateAndTime;
		break;
	case 'x':
		Ret = TimeParamType::LocaleDate;
		break;
	case 'X':
		Ret = TimeParamType::LocaleTime;
		break;
	case 'z':
		Ret = TimeParamType::UTCOffset;
		break;
	case 'Z':
		Ret = TimeParamType::Timezone;
		break;
	case 't':
		Ret = TimeParamType::Tab;
		break;
	case 'n':
		Ret = TimeParamType::Newline;
		break;
	case '%':
		Ret = TimeParamType::Percent;
		break;

	case 'O':
	case 'E':
		if (CheckExtParse(szFmt))
		{
			int nInnerFmtInc = 0;
			Ret = ParseType(szFmt + 1, &nInnerFmtInc);
			(*pFmtInc) += nInnerFmtInc;
		}
		break;
	}
	return Ret;
}

static size_t DispatchHandlers(
	char* restrict s,
	size_t remsize,
	TimeParamType Type,
	const struct tm* restrict timeptr)
{
	size_t ret;
	switch (Type)
	{
	case TimeParamType::WeekDayAbriv:
	case TimeParamType::WeekDayFull:
	case TimeParamType::WeekDayDec:
	case TimeParamType::WeekDayISO8601:
		ret = HandleWeekDay(s, remsize, Type, timeptr);
		break;
	case TimeParamType::YearDay:
		ret = HandleYearDay(s, remsize, Type, timeptr);
		break;
	case TimeParamType::MonthDay2Dig:
	case TimeParamType::MonthDaySpaced:
		ret = HandleMonthDay(s, remsize, Type, timeptr);
		break;
	case TimeParamType::MonthAbriv:
	case TimeParamType::MonthFull:
	case TimeParamType::MonthDec:
		ret = HandleMonth(s, remsize, Type, timeptr);
		break;
	case TimeParamType::YearDec:
	case TimeParamType::Year2DTrim:
	case TimeParamType::YearCentury:
		ret = HandleYear(s, remsize, Type, timeptr);
		break;
	case TimeParamType::DateMDY:
	case TimeParamType::DateISO8601:
		ret = HandleDate(s, remsize, Type, timeptr);
		break;
	case TimeParamType::YearIOS8601:
	case TimeParamType::Year2DISO8601:
		ret = HandleISO8601Year(s, remsize, Type, timeptr);
		break;
	case TimeParamType::DateWeekOfYearISO8601:
	case TimeParamType::DateWeekOfYearSun:
	case TimeParamType::DateWeekOfYearMon:
		ret = HandleWeekOfYear(s, remsize, Type, timeptr);
		break;
	case TimeParamType::Seconds:
		ret = HandleSeconds(s, remsize, Type, timeptr);
		break;
	case TimeParamType::Minutes:
		ret = HandleMinutes(s, remsize, Type, timeptr);
		break;
	case TimeParamType::Hour24h:
	case TimeParamType::Hour12h:
		ret = HandleHours(s, remsize, Type, timeptr);
		break;
	case TimeParamType::HourAMPM:
		ret = HandleAMPM(s, remsize, Type, timeptr);
		break;
	case TimeParamType::TimeHourMinute:
	case TimeParamType::Time12h:
	case TimeParamType::TimeISO8601:
		ret = HandleCompositeTime(s, remsize, Type, timeptr);
		break;
	case TimeParamType::LocaleDateAndTime:
	case TimeParamType::LocaleDate:
	case TimeParamType::LocaleTime:
	case TimeParamType::UTCOffset:
	case TimeParamType::Timezone:
		ret = HandleLocaleSpecific(s, remsize, Type, timeptr);
		break;
	case TimeParamType::Tab:
	case TimeParamType::Newline:
	case TimeParamType::Percent:
		ret = HandleControls(s, remsize, Type);
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}

size_t strftime(char* restrict s,
	size_t maxsize,
	const char* restrict format,
	const struct tm* restrict timeptr)
{
	size_t Ret = 0;
	size_t RemainingSize = maxsize;
	bool bOOM = false;
	if (RemainingSize)
	{
		RemainingSize--;
		if (s)
			s[RemainingSize] = '\0';
	}
	while (*format)
	{
		if (*format != '%')
		{
			RemainingSize = _CondSub(RemainingSize, 1);
			s = _AssignIncS(s, *format, 0);
			format++;
			Ret += 1;
		}
		else
		{
			format++;
			int nFmtInc = 0;
			TimeParamType type = ParseType(format, &nFmtInc);
			if (type == TimeParamType::error)
			{
				RemainingSize = _CondSub(RemainingSize, 1);
				s = _AssignIncS(s, '%', 1);
				Ret += 1;
			}
			else
			{
				size_t R = DispatchHandlers(s, RemainingSize, type, timeptr);
				s = _IncS(s, R);
				Ret += R;
				RemainingSize = _CondSub(RemainingSize, R);
			}
			format += nFmtInc;
		}

		if (Ret >= maxsize)
		{
			Ret = 0;
			bOOM = true;
			break;
		}
	}
	if (!bOOM)
	{
		if(s)
			*s = '\0';
	}
	return Ret;
}