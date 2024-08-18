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
#ifndef TOS_LIMITS_H
#define TOS_LIMITS_H

#ifndef MB_LEN_MAX
#define MB_LEN_MAX 4
#endif // !MB_LEN_MAX

#define CHAR_BIT 8

#define SCHAR_MIN (-__SCHAR_MAX__-1)
#define SCHAR_MAX __SCHAR_MAX__
#define UCHAR_MAX (__SCHAR_MAX__*2  +1)

#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX

#define SHRT_MIN (-__SHRT_MAX__ -1)
#define SHRT_MAX __SHRT_MAX__
#define USHRT_MAX (__SHRT_MAX__ * 2U + 1U)
#define INT_MIN (-__INT_MAX__  -1)
#define INT_MAX __INT_MAX__
#define UINT_MAX (__INT_MAX__  *2U +1U)
#define LONG_MIN  (-__LONG_MAX__ -1L)
#define LONG_MAX __LONG_MAX__
#define ULONG_MAX (__LONG_MAX__ *2UL+1UL)
#define LLONG_MIN (-__LONG_LONG_MAX__-1LL)
#define LLONG_MAX __LONG_LONG_MAX__
#define ULLONG_MAX (__LONG_LONG_MAX__*2ULL+1ULL)


#endif // !TOS_LIMITS_H
