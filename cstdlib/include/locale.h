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
#ifndef TOS_LOCALE_H
#define TOS_LOCALE_H
#include "stddef.h"

struct lconv {
	char* decimal_point; //"."
	char* thousands_sep; //""
	char* grouping; //""
	char* mon_decimal_point; //""
	char* mon_thousands_sep; //""
	char* mon_grouping; //""
	char* positive_sign; //""
	char* negative_sign; //""
	char* currency_symbol; //""
	char frac_digits; //CHAR_MAX
	char p_cs_precedes; //CHAR_MAX
	char n_cs_precedes; //CHAR_MAX
	char p_sep_by_space; //CHAR_MAX
	char n_sep_by_space; //CHAR_MAX
	char p_sign_posn; //CHAR_MAX
	char n_sign_posn; //CHAR_MAX
	char* int_curr_symbol; //""
	char int_frac_digits; //CHAR_MAX
	char int_p_cs_precedes; //CHAR_MAX
	char int_n_cs_precedes; //CHAR_MAX
	char int_p_sep_by_space; //CHAR_MAX
	char int_n_sep_by_space; //CHAR_MAX
	char int_p_sign_posn; //CHAR_MAX
	char int_n_sign_posn; //CHAR_MAX
};

#define LC_ALL 0
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 3
#define LC_NUMERIC 4
#define LC_TIME 5

LIBC_DEF_BEGIN
char* setlocale(int category, const char* locale);
struct lconv* localeconv(void);
LIBC_DEF_END
#endif