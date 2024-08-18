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
#ifndef TOS_STDDEF_H
#define TOS_STDDEF_H
#include "stdint.h"

typedef uint64_t size_t;
typedef int64_t ptrdiff_t;
typedef size_t max_align_t;

#ifndef __cplusplus
#ifdef _WIN32
typedef int16_t wchar_t;
#else
typedef int32_t wchar_t;
#endif // _WIN32
#endif // !__cplusplus

#define NULL 0

#define offsetof(t, d) __builtin_offsetof(t, d)

#ifdef __cplusplus
#ifndef restrict
#define restrict
#endif // !restrict
#define LIBC_DEF_BEGIN extern "C" {
#define LIBC_DEF_END };
#else
#define LIBC_DEF_BEGIN
#define LIBC_DEF_END
#endif // __cplusplus


#endif // !TOS_STDDEF_H
