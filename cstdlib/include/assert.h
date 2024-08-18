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
#ifndef TOS_ASSERT_H
#define TOS_ASSERT_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif // !__cplusplus

#ifdef NDEBUG
#define assert(x) ((void*)0)
#else
void _tos_assert_impl(int res, const char* szFunc, const char* szFile, unsigned long long int line);
#define assert(x) _tos_assert_impl(x, __func__, __FILE__, __LINE__)
#endif // NDEBUG


#endif // !TOS_ASSERT_H
