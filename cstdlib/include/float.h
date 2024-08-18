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
#ifndef TOS_FLOAT_H
#define TOS_FLOAT_H
#ifndef __cplusplus
#endif // !__cplusplus
#define FLT_ROUNDS (__builtin_flt_rounds());
#define FLT_EVAL_METHOD 0

#define FLT_HAS_SUBNORM 1
#define DBL_HAS_SUBNORM 1
#define LDBL_HAS_SUBNORM 1

#define FLT_RADIX 2

#define FLT_MANT_DIG 24
#define DBL_MANT_DIG 53


#define FLT_DECIMAL_DIG 9
#define DBL_DECIMAL_DIG 17

#define DECIMAL_DIG 17

#define FLT_DIG 6
#define DBL_DIG 15

#define FLT_MIN_EXP (-125)
#define DBL_MIN_EXP (-1021)

#define FLT_MIN_10_EXP (-37)
#define DBL_MIN_10_EXP (-307)

#define FLT_MAX_EXP (128)
#define DBL_MAX_EXP (1024)

#define FLT_MAX_10_EXP (+37)
#define DBL_MAX_10_EXP (+37)

#define FLT_MAX 3.40282347e+38F
#define DBL_MAX 1.7976931348623157e+308

#define FLT_EPSILON 1.19209290e-7F
#define DBL_EPSILON 2.2204460492503131e-16

#define FLT_MIN 1.17549435e-38F
#define DBL_MIN 2.2250738585072014e-308

#define FLT_TRUE_MIN 1.40129846e-45F
#define DBL_TRUE_MIN 4.9406564584124654e-324

#ifdef _WIN32
#define LDBL_MANT_DIG DBL_MANT_DIG
#define LDBL_DECIMAL_DIG DBL_DECIMAL_DIG
#define LDBL_MAX_EXP DBL_MAX_EXP
#define LDBL_DIG DBL_DIG
#define LDBL_MIN_EXP DBL_MIN_EXP
#define LDBL_MIN_10_EXP DBL_MIN_10_EXP
#define LDBL_MAX_10_EXP DBL_MAX_10_EXP
#define LDBL_MAX DBL_MAX
#define LDBL_EPSILON DBL_EPSILON
#define LDBL_MIN DBL_MIN
#define LDBL_TRUE_MIN DBL_TRUE_MIN
#else
#define LDBL_MANT_DIG 63
#endif // _WIN32
#endif // !TOS_FLOAT_H
