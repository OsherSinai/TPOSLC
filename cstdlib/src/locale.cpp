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
#include <include\locale.h>
#include <include\limits.h>

//not gonna implement this, this feature is mostly useless

struct lconv g_ProgramLocale;
//extern "C" struct lconv g_ProgramLocale;
extern "C" void _tos_initialize_locale()
{
	g_ProgramLocale.decimal_point = (char*)"."; //"."
	g_ProgramLocale.thousands_sep = (char*)""; //""
	g_ProgramLocale.grouping = (char*)""; //""
	g_ProgramLocale.mon_decimal_point = (char*)""; //""
	g_ProgramLocale.mon_thousands_sep = (char*)""; //""
	g_ProgramLocale.mon_grouping = (char*)""; //""
	g_ProgramLocale.positive_sign = (char*)""; //""
	g_ProgramLocale.negative_sign = (char*)""; //""
	g_ProgramLocale.currency_symbol = (char*)""; //""
	g_ProgramLocale.frac_digits = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.p_cs_precedes = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.n_cs_precedes = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.p_sep_by_space = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.n_sep_by_space = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.p_sign_posn = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.n_sign_posn = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_curr_symbol = (char*)""; //""
	g_ProgramLocale.int_frac_digits = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_p_cs_precedes = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_n_cs_precedes = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_p_sep_by_space = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_n_sep_by_space = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_p_sign_posn = CHAR_MAX; //CHAR_MAX
	g_ProgramLocale.int_n_sign_posn = CHAR_MAX; //CHAR_MAX
}


char* setlocale(int category, const char* locale)
{
	char* szRet = 0;
	if (*locale == 'C')
	{
		/*
		switch (category)
		{
		case LC_ALL:
			break;
		case LC_COLLATE:
			break;
		case LC_CTYPE:
			break;
		case LC_MONETARY:
			break;
		case LC_NUMERIC:
			break;
		case LC_TIME:
			break;
		default:
			break;
		}
		*/
	}
	return szRet;
}
struct lconv* localeconv(void)
{
	return &g_ProgramLocale;
}