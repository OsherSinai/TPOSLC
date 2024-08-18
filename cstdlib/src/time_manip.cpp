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
#include <include\time.h>
#include <include\stdlib.h>
#include <include\string.h>
#include <include\stdio.h>
#include <include\threads.h>
#include <include\wchar.h>
#include <include\uchar.h>
#include "TOSThreadEnvironmentBlock.h"
#ifdef _WIN32
#include "win32/win32_ntdll.h"
#include "win32/win32_tzres_dll.h"
#else
#error Unimplemented time_manip
#endif // _WIN32

//TODO: support for time before 1 jan 1970

#define UNIX_EPOCH 1970
#define TM_YEAR_BASE 1900

static time_t g_TimeProcessorStart;
static time_t g_TimeProcessorFrequency;
extern "C" uint32_t * g_time_HypervisorSharedPageInfo;
static uint32_t* g_time_HypervisorSharedPageInfo;

#ifdef _WIN32
//TODO: change it so it will be fetched every call
static  RTL_TIMEZONE_INFO g_time_Win32KernTimezone;

#endif // _WIN32


static constexpr size_t c_uchGregorianCalender[2][12] = 
{ 
    { 31, 28, 31, 30 ,31 ,30 ,31, 31, 30 ,31 ,30 ,31 },
    { 31, 29, 31, 30 ,31 ,30 ,31, 31, 30 ,31 ,30 ,31 },
};
static constexpr const char* c_szGregorianCalenderNames[12] = {
    "Jan", "Feb", "Mar", "Apr",
    "May", "Jun", "Jul", "Aug",
    "Sep", "Oct", "Nov", "Dec"
};
static constexpr const char* c_szWeekdays[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
static constexpr time_t c_UnixEpochFirstDay = 4ll;
static constexpr time_t c_UnixSecInMinute = 60ll;
static constexpr time_t c_UnixSecInHour = c_UnixSecInMinute * 60ll;
static constexpr time_t c_UnixSecInDay = c_UnixSecInHour * 24ll;
//static constexpr time_t c_UnixSecInYear = 31556926ll;
static constexpr time_t c_UnixEpochLeapDays = (1970ll / 4ll) - (1970ll / 100ll) + (1970ll / 400ll);
static constexpr time_t c_WinEpochLeapDays = (1601ll / 4ll) - (1601ll / 100ll) + (1601ll / 400ll);
static constexpr time_t c_WinToUnixEpochSec = (1970ll-1601ll)*365ll* c_UnixSecInDay + (c_UnixEpochLeapDays - c_WinEpochLeapDays) * c_UnixSecInDay;
static constexpr time_t c_WinToUnixEpochNanosec100 = c_WinToUnixEpochSec * 10000000;

extern "C" int _tos_initialize_time()
{
    int nRet = 0;
#ifdef _WIN32
    LARGE_INTEGER Frequency;
    LARGE_INTEGER Counter;
    NTSTATUS ntStat;

    ntStat = SyscallNtQuerySystemInformation(
        0xC5, //hypervisorSharedPageInfo pointer
        &g_time_HypervisorSharedPageInfo,
        sizeof(void*),
        0
    );
    if (ntStat != STATUS_SUCCESS)
    {
        nRet = -1;
        goto cleanup;
    }

    RtlQueryPerformanceFrequency(&Frequency);
    ntStat = RtlQueryPerformanceCounter(&Counter);
    if (ntStat == 1)
    {
        g_TimeProcessorStart = Counter.QWord;
        g_TimeProcessorFrequency = Frequency.QWord;
    }
    else
    {
        nRet = -1;
        goto cleanup;
    }

    ntStat = SyscallNtQuerySystemInformation(
        0x2C, // RTL_TIMEZONE_INFO
        &g_time_Win32KernTimezone,
        sizeof(g_time_Win32KernTimezone),
        0
    );
    if (ntStat != STATUS_SUCCESS)
    {
        nRet = -1;
        goto cleanup;
    }

#endif // _WIN32

cleanup:
    return nRet;
}

extern "C" void _tos_uninitialize_time()
{

}

clock_t clock()
{
    clock_t ret = ~0;
#ifdef _WIN32
    LARGE_INTEGER leCounter;
    LARGE_INTEGER leTmp;
    LARGE_INTEGER leRet;
    BOOL bOk = RtlQueryPerformanceCounter(&leCounter);
    if (bOk != FALSE)
    {
        // do we really need an overflow fail?
        leTmp.QWord = leCounter.QWord - g_TimeProcessorStart;
        leRet.QWord = (((leTmp.QWord % g_TimeProcessorFrequency) * CLOCKS_PER_SEC) / g_TimeProcessorFrequency) +
            ((leTmp.QWord / g_TimeProcessorFrequency) * CLOCKS_PER_SEC);
        if (leRet.QWord < 0x8000000)
            ret = leRet.QWord;
    }
#endif // _WIN32
    return ret;
}

double difftime(time_t time1, time_t time0)
{
    double ret = 0.;
    if (!time1 || !time0)
    {
        //TODO: error
    }
    else
    {
        ret = (double)(time1 - time0);
    }
    return ret;
}



static bool IsLeapYear(int64_t year)
{
    bool bIsYear = false;

    if ((year & 0x3) == 0)
    {
        if ((year % 100) == 0)
            bIsYear = (year % 400) == 0;
        else
            bIsYear = true;
    }


    return bIsYear;
}

extern "C" bool _tos_time_ValidateTM(const struct tm* timeptr)
{
    bool bRet = false;
    
    if (!timeptr)
        goto cleanup;

    if (timeptr->tm_year < 0)
        goto cleanup;

    if ((timeptr->tm_wday < 0) || (timeptr->tm_wday > 6))
        goto cleanup;


    if ((timeptr->tm_sec < 0) || (timeptr->tm_sec > 60))
        goto cleanup;

    if ((timeptr->tm_min < 0) || (timeptr->tm_min > 59))
        goto cleanup;

    if ((timeptr->tm_hour < 0) || (timeptr->tm_hour > 23))
        goto cleanup;



    if ((timeptr->tm_yday < 0) || (timeptr->tm_yday > 365))//TODO: validate with actual leap year
        goto cleanup;
    if ((timeptr->tm_mday < 0) || (timeptr->tm_mday > 31)) //TODO: validate with actual leap year
        goto cleanup;
    //TODO: check daylight saving
    if ((timeptr->tm_mon < 0) || (timeptr->tm_mon > 11))
        goto cleanup;

    bRet = true;
cleanup:
    return bRet;
}


static bool CheckInDaylightSavingRange(const struct tm* timeptr)
{
    bool bRet = false;

#ifdef _WIN32
    if (g_time_Win32KernTimezone.StandardStart.Month >
        g_time_Win32KernTimezone.DaylightStart.Month)
    {
        if (timeptr->tm_mon >= g_time_Win32KernTimezone.DaylightStart.Month
            && timeptr->tm_mon < g_time_Win32KernTimezone.StandardStart.Month)
        {
            WIN32_TIME_FIELDS* ptf;
            if (timeptr->tm_mon == g_time_Win32KernTimezone.DaylightStart.Month)
            {
                ptf = &g_time_Win32KernTimezone.DaylightStart;
                size_t dls_sec = ptf->Hour * c_UnixSecInHour + ptf->Minute * c_UnixSecInMinute + ptf->Second;
                size_t tm_sec = timeptr->tm_hour * c_UnixSecInHour + timeptr->tm_min * c_UnixSecInMinute + timeptr->tm_sec;
                if (timeptr->tm_mday > ptf->Day)
                {
                    bRet = true;
                }
                else if (timeptr->tm_mday == ptf->Day)
                {
                    bRet = tm_sec >= dls_sec;
                }
            }
            else if (timeptr->tm_mon == g_time_Win32KernTimezone.StandardStart.Month)
            {
                ptf = &g_time_Win32KernTimezone.StandardStart;
                size_t dls_sec = ptf->Hour * c_UnixSecInHour + ptf->Minute * c_UnixSecInMinute + ptf->Second;
                size_t tm_sec = timeptr->tm_hour * c_UnixSecInHour + timeptr->tm_min * c_UnixSecInMinute + timeptr->tm_sec;
                if (timeptr->tm_mday < ptf->Day)
                {
                    bRet = true;
                }
                else if (timeptr->tm_mday == ptf->Day)
                {
                    bRet = tm_sec < dls_sec;
                }
            }
            else
            {
                bRet = true;
            }
        }
    }
    else
    {
        if (timeptr->tm_mon >= g_time_Win32KernTimezone.DaylightStart.Month
            || timeptr->tm_mon < g_time_Win32KernTimezone.StandardStart.Month)
        {
            WIN32_TIME_FIELDS* ptf;
            if (timeptr->tm_mon == g_time_Win32KernTimezone.DaylightStart.Month)
            {
                ptf = &g_time_Win32KernTimezone.DaylightStart;
                size_t dls_sec = ptf->Hour * c_UnixSecInHour + ptf->Minute * c_UnixSecInMinute + ptf->Second;
                size_t tm_sec = timeptr->tm_hour * c_UnixSecInHour + timeptr->tm_min * c_UnixSecInMinute + timeptr->tm_sec;
                if (timeptr->tm_mday > ptf->Day)
                {
                    bRet = true;
                }
                else if (timeptr->tm_mday == ptf->Day)
                {
                    bRet = tm_sec >= dls_sec;
                }
            }
            else if (timeptr->tm_mon == g_time_Win32KernTimezone.StandardStart.Month)
            {
                ptf = &g_time_Win32KernTimezone.StandardStart;
                size_t dls_sec = ptf->Hour * c_UnixSecInHour + ptf->Minute * c_UnixSecInMinute + ptf->Second;
                size_t tm_sec = timeptr->tm_hour * c_UnixSecInHour + timeptr->tm_min * c_UnixSecInMinute + timeptr->tm_sec;
                if (timeptr->tm_mday < ptf->Day)
                {
                    bRet = true;
                }
                else if (timeptr->tm_mday == ptf->Day)
                {
                    bRet = tm_sec < dls_sec;
                }
            }
            else
            {
                bRet = true;
            }
        }
    }
#else

#error Unimplemented (time_manip.cpp)
#endif // _WIN32
    return bRet;
}


extern "C" void _tos_GetUTCOffset(const struct tm* timeptr, int* pnhours, int* pnminutes)
{
#ifdef _WIN32
    time_t Offset = g_time_Win32KernTimezone.Bias;
    if (CheckInDaylightSavingRange(timeptr))
        Offset += g_time_Win32KernTimezone.DaylightBias;
    else
        Offset += g_time_Win32KernTimezone.StandardBias;
    *pnhours = Offset / c_UnixSecInMinute;
    *pnminutes = Offset % c_UnixSecInMinute;
    *pnminutes = abs(*pnminutes);
#else
#error unimplemented _tos_GetUTCOffset (time_manip.cpp)
#endif
}
extern "C" void _tos_GetUTCTimezoneName(const struct tm* timeptr, char szName[129])
{
#ifdef _WIN32
    bool bNotCopied = true;
    char szTmpName[129] = { 0 };
    wchar_t* pwsz = (wchar_t*)g_time_Win32KernTimezone.StandardName;
    mbstate_t state = {0};
    wcsrtombs((char*)szTmpName, (const wchar_t**)&pwsz, 128, &state);
    if (szTmpName[0] == '@')
    {
        char* p = strchr(szTmpName, ',');
        if (p)
        {
            p++;
            long long idx = llabs(strtoll(p, 0, 10));
            idx--;
            if (sizeof(g_tzres) / sizeof(g_tzres[0]) > idx && idx >= 0)
            {
                const char* pTZRes = g_tzres[idx];
                strcpy(szName, pTZRes);
                bNotCopied = false;
            }
        }
    }
    if(bNotCopied)
    {
        strcpy(szName, szTmpName);
    }
#else
#error unimplemented _tos_GetUTCOffset (time_manip.cpp)
#endif
}

static int CheckDaylightSaving(struct tm* timeptr, time_t* pOffset)
{
    int nDaylight = 0;

#ifdef _WIN32
    time_t Offset = g_time_Win32KernTimezone.Bias;
    if (CheckInDaylightSavingRange(timeptr))
    {
        Offset += g_time_Win32KernTimezone.DaylightBias;
    }
    else
    {
        Offset += g_time_Win32KernTimezone.StandardBias;
    }
    if(pOffset)
        *pOffset = Offset * c_UnixSecInMinute;
#else
#error Unimplemented (time_manip.cpp)
#endif // _WIN32

    return nDaylight;
}
static void GetDaylightSavingOffset(int nDaylightSaving, time_t* pOffset)
{
#ifdef _WIN32
    time_t Offset = g_time_Win32KernTimezone.Bias;
    if (nDaylightSaving)
    {
        Offset += g_time_Win32KernTimezone.DaylightBias;
    }
    else
    {

        Offset += g_time_Win32KernTimezone.StandardBias;
    }
    *pOffset = Offset * c_UnixSecInMinute;
#else
#error Unimplemented (time_manip.cpp)
#endif // _WIN32

}

extern "C" void _tos_NormalizeTM(tm * pTM)
{
    if (pTM->tm_sec > 59)
    {
        while (pTM->tm_sec > 59)
        {
            pTM->tm_sec -= 60;
            pTM->tm_min++;
        }
    }
    else if (pTM->tm_sec < 0)
    {
        while (pTM->tm_sec < 0)
        {
            pTM->tm_sec += 60;
            pTM->tm_min--;
        }
    }

    if (pTM->tm_min > 59)
    {
        while (pTM->tm_min > 59)
        {
            pTM->tm_min -= 60;
            pTM->tm_hour++;
        }
    }
    else if (pTM->tm_min < 0)
    {
        while (pTM->tm_min < 0)
        {
            pTM->tm_min += 60;
            pTM->tm_hour--;
        }
    }

    if (pTM->tm_hour > 23)
    {
        while (pTM->tm_hour > 23)
        {
            pTM->tm_hour -= 24;
            pTM->tm_yday++;
            pTM->tm_wday++;
        }
    }
    else if (pTM->tm_hour < 0)
    {
        while (pTM->tm_hour < 0)
        {
            pTM->tm_hour += 24;
            pTM->tm_yday--;
            pTM->tm_wday--;
        }
    }

    if (pTM->tm_wday > 6)
    {
        while (pTM->tm_wday > 6)
            pTM->tm_wday -= 7;
    }
    else if (pTM->tm_wday < 0)
    {
        while (pTM->tm_wday < 0)
            pTM->tm_wday += 7;
    }

    // check 

    int nLeapYear = IsLeapYear(pTM->tm_year) ? 1 : 0;
    if (pTM->tm_yday > (364 + nLeapYear))
    {
        while (pTM->tm_yday > (364 + nLeapYear))
        {
            pTM->tm_yday -= (365 + nLeapYear);
            pTM->tm_year++;
            nLeapYear = IsLeapYear(pTM->tm_year);
        }
    }
    else if (pTM->tm_yday < 0)
    {
        while (pTM->tm_yday < 0)
        {
            pTM->tm_yday += (365 + nLeapYear);
            pTM->tm_year--;
            nLeapYear = IsLeapYear(pTM->tm_year);
        }
    }


    int i = 0;
    int DayAcc = pTM->tm_yday;
    for (i = 0; i < 12; i++)
    {
        if (c_uchGregorianCalender[nLeapYear][i] > DayAcc)
            break;
        DayAcc -= c_uchGregorianCalender[nLeapYear][i];
    }
    pTM->tm_mday = DayAcc + 1; // day of the month-- [1, 31]
    pTM->tm_mon = i; // months since January-- [0, 11]

    pTM->tm_isdst = CheckInDaylightSavingRange(pTM);
}

time_t mktime(struct tm* timeptr)
{
    //time from 1 jan 1970
    time_t sec;
    time_t min;
    time_t hour;
    time_t year;
    time_t yday;

    struct tm normalized = *timeptr;
    time_t time = 0;
    if (!_tos_time_ValidateTM(timeptr))
    {
        errno = EINVAL;
        goto cleanup;
    }
    _tos_NormalizeTM(&normalized);
    if (!_tos_time_ValidateTM(&normalized))
    {
        errno = EINVAL;
        goto cleanup;
    }
    sec = normalized.tm_sec;
    min = normalized.tm_min;
    hour = normalized.tm_hour;
    year = normalized.tm_year + 1900;
    yday = normalized.tm_yday;

    //dtt = ydhms_diff(year, yday, hour, min, sec,
    //    UNIX_EPOCH - TM_YEAR_BASE, 0, 0, 0, 0
    //);

    if (normalized.tm_year >= 70)
    {
        // were on unix epoch 
        //year -= 70;
        time += sec;
        time += min * c_UnixSecInMinute;
        time += hour * c_UnixSecInHour;
        time += yday * c_UnixSecInDay;
        time_t offset = 0;

        time_t total_leap_days = ((year / 4) - (year / 100) + (year / 400)) - c_UnixEpochLeapDays;
        if(IsLeapYear(year))
            total_leap_days--; // yday already account for current year's leap day

        time += ((normalized.tm_year - 70) * (365 * c_UnixSecInDay)) + total_leap_days*c_UnixSecInDay;

        if (normalized.tm_isdst < 0)
        {
            //call calc daytime
            CheckDaylightSaving(&normalized, &offset);
        }
        else
        {
            GetDaylightSavingOffset(normalized.tm_isdst, &offset);
        }
        time += offset;
    }
    else
    {

    }

    errno = 0;
cleanup:
    return time;
}

union win32_times {
    struct {
        uint32_t low;
        uint32_t high;
    };
    int64_t time;
};

time_t time(time_t* timer)
{
    time_t ret = ~0;
#ifdef _WIN32
    FILETIME winpoc;
    GetSystemTimeAsFileTime(&winpoc);
    time_t comb = (time_t)(((uint64_t)winpoc.dwHighDateTime) << 32) | ((uint64_t)winpoc.dwLowDateTime);
    ret = (comb - c_WinToUnixEpochNanosec100) / 10000000;
#endif // _WIN32
    if (timer)
        *timer = ret;
    return ret;
}

int timespec_get(struct timespec* ts, int base)
{
#ifdef _WIN32
    FILETIME winpoc;
    time_t comb;
#endif // _WIN32
    if (!ts || (base > TIME_UTC) || (base < 0))
    {
        base = 0;
        goto cleanup;
    }
#ifdef _WIN32
    GetSystemTimeAsFileTime(&winpoc);
    comb = (time_t)(((uint64_t)winpoc.dwHighDateTime) << 32) | ((uint64_t)winpoc.dwLowDateTime);
    ts->tv_sec = (comb - c_WinToUnixEpochNanosec100) / 10000000;
    ts->tv_nsec = ((comb - c_WinToUnixEpochNanosec100) * 100) - (ts->tv_sec * 1000000000);
#endif // _WIN32
cleanup:
    return base;
}


char* asctime(const struct tm* timeptr)
{
    static thread_local char result[32];
    memset(result, 0, sizeof(result));
    if (!_tos_time_ValidateTM(timeptr))
        goto cleanup;

    sprintf(result, "%.3s %.3s %.3d %.2d:%.2d:%.2d %d\n",
        c_szWeekdays[timeptr->tm_wday],
        c_szGregorianCalenderNames[timeptr->tm_mon],
        timeptr->tm_mday, timeptr->tm_hour,
        timeptr->tm_min, timeptr->tm_sec,
        1900 + timeptr->tm_year);

cleanup:
    return result;
}

static void CalculateGMTimeInternal(tm* pTM, const time_t* timer)
{
    //timers are always in utc time
    size_t i;
    time_t DayAcc;
    time_t WeekDay;
    int nLeapYear;
    //TODO: add check for negative timer, verify this
    memset(pTM, 0, sizeof(struct tm));
    // we've got the time in seconds
    time_t ttbuffer = *timer;
    pTM->tm_sec = ttbuffer % 60;
    ttbuffer /= 60;

    //time is now in minutes
    pTM->tm_min = ttbuffer % 60;
    ttbuffer /= 60;

    //time is now hours
    pTM->tm_hour = ttbuffer % 24;
    ttbuffer /= 24;

    WeekDay = (ttbuffer + c_UnixEpochFirstDay) % 7;

    //time is now in days (including leap days)
    time_t approx_years = ttbuffer / 365 + 1970 - 1;
    time_t total_leap_days_m1 = ((approx_years / 4) - (approx_years / 100) + (approx_years / 400)) - c_UnixEpochLeapDays;
    ttbuffer -= total_leap_days_m1;
    pTM->tm_year = ttbuffer / 365 + 70;
    pTM->tm_yday = ttbuffer % 365; // days since January 1-- [0, 365]
    DayAcc = pTM->tm_yday;
    nLeapYear = IsLeapYear(pTM->tm_year + 1900) ? 1 : 0;
    for (i = 0; i < 12; i++)
    {
        if (c_uchGregorianCalender[nLeapYear][i] > DayAcc)
            break;
        DayAcc -= c_uchGregorianCalender[nLeapYear][i];
    }

    pTM->tm_mday = DayAcc + 1; // day of the month-- [1, 31]
    pTM->tm_mon = i; // months since January-- [0, 11]

    pTM->tm_wday = WeekDay; // days since Sunday-- [0, 6]
    pTM->tm_isdst = CheckInDaylightSavingRange(pTM); // Daylight Saving Time flag

}

struct tm* gmtime(const time_t* timer)
{
    CalculateGMTimeInternal(&tos_teb.UTCTime, timer);
    return &tos_teb.UTCTime;
}


struct tm* localtime(const time_t* timer)
{
    //timers are always in utc time
    time_t offset;
    CalculateGMTimeInternal(&tos_teb.LocalTime, timer);
    GetDaylightSavingOffset(tos_teb.LocalTime.tm_isdst, &offset);

    tos_teb.LocalTime.tm_sec -= offset;

    _tos_NormalizeTM(&tos_teb.LocalTime);

    

    return &tos_teb.LocalTime;
}

char* ctime(const time_t* timer)
{
    return asctime(localtime(timer));
}