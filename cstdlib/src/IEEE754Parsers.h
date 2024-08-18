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
#ifndef TOS_IEEE754_PARSERS_H
#define TOS_IEEE754_PARSERS_H
#include <include\stddef.h>

union dbltofx_inner {
	static constexpr size_t numlen = 32;
	struct {
		uint64_t frac[numlen];
		uint64_t num[numlen];
	};
	uint64_t arr[2 * numlen];
};

struct dbl_to_str_state {

	dbltofx_inner fixed_point;
	uint64_t fraction_buffer_adder[dbltofx_inner::numlen];
	uint64_t fraction_buffer_acc[dbltofx_inner::numlen];
	char szBuffer[4096];
};


extern "C" void dbltostr(double d, int* frac_limit, bool bUppercase, dbl_to_str_state * state);
extern "C"  void dbl_extract_values(dbltofx_inner * pState, int64_t * pExponent, uint64_t * pFraq);
#endif // !TOS_IEEE754_PARSERS_H
