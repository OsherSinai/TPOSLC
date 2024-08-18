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
#include <include\wctype.h>
#include <include\string.h>
int iswalnum(wint_t wc)
{
	return iswalpha(wc) != 0 || iswdigit(wc) != 0;
}
int iswalpha(wint_t wc)
{
	return iswupper(wc) != 0 || iswlower(wc) != 0;
}
int iswblank(wint_t wc)
{
	return (wc == L' ') || (wc == L'\t');
}
int iswcntrl(wint_t wc)
{
	return wc < (wint_t)L' ' || wc == (wint_t)127;
}
int iswdigit(wint_t wc)
{
	return (wc >= L'0') && (wc <= L'9');
}
int iswgraph(wint_t wc)
{
	return  ((L' ' < wc) && (wc < 127));
}
int iswlower(wint_t wc)
{
	return wc >= L'a' && wc <= L'z';
}
int iswprint(wint_t wc)
{
	return ((L' ' <= wc) && (wc < 127));
}
int iswpunct(wint_t wc)
{
	return iswgraph(wc) != 0 && iswalnum(wc) == 0;
}
int iswspace(wint_t wc)
{
	return (wc == L' ') || (wc == L'\f') || (wc == L'\n') || (wc == L'\r') || (wc == L'\t') || (wc == L'\v');
}
int iswupper(wint_t wc)
{
	return wc >= L'A' && wc <= L'Z';
}
int iswxdigit(wint_t wc)
{
	return iswdigit(wc) != 0 || 
		(wc >= L'A' && wc <= L'F') ||
		(wc >= L'a' && wc <= L'f');
}

enum class wctype_val : wctype_t {
	zero,
	alnum,
	alpha,
	blank,
	cntrl,
	digit,
	graph,
	lower,
	print,
	punct,
	space,
	upper,
	xdigit,
	unknown
};

int iswctype(wint_t wc, wctype_t desc)
{
	int nRet;
	switch ((wctype_val)desc)
	{
	case wctype_val::zero:
		nRet = 0;
		break;
	case wctype_val::alnum:
		nRet = iswalnum(wc);
		break;
	case wctype_val::alpha:
		nRet = iswalpha(wc);
		break;
	case wctype_val::blank:
		nRet = iswblank(wc);
		break;
	case wctype_val::cntrl:
		nRet = iswcntrl(wc);
		break;
	case wctype_val::digit:
		nRet = iswdigit(wc);
		break;
	case wctype_val::graph:
		nRet = iswgraph(wc);
		break;
	case wctype_val::lower:
		nRet = iswlower(wc);
		break;
	case wctype_val::print:
		nRet = iswprint(wc);
		break;
	case wctype_val::punct:
		nRet = iswpunct(wc);
		break;
	case wctype_val::space:
		nRet = iswspace(wc);
		break;
	case wctype_val::upper:
		nRet = iswupper(wc);
		break;
	case wctype_val::xdigit:
		nRet = iswxdigit(wc);
		break;
	case wctype_val::unknown:
	default:
		nRet = 0;
		break;
	}
	return nRet;
}
wctype_t wctype(const char* property)
{
	wctype_val ret = wctype_val::unknown;
	if (strcmp(property, "alnum") == 0) ret = wctype_val::alnum;
	else if (strcmp(property, "alpha") == 0) ret = wctype_val::alpha;
	else if (strcmp(property, "blank") == 0) ret = wctype_val::blank;
	else if (strcmp(property, "cntrl") == 0) ret = wctype_val::cntrl;
	else if (strcmp(property, "digit") == 0) ret = wctype_val::digit;
	else if (strcmp(property, "graph") == 0) ret = wctype_val::graph;
	else if (strcmp(property, "lower") == 0) ret = wctype_val::lower;
	else if (strcmp(property, "print") == 0) ret = wctype_val::print;
	else if (strcmp(property, "punct") == 0) ret = wctype_val::punct;
	else if (strcmp(property, "space") == 0) ret = wctype_val::space;
	else if (strcmp(property, "upper") == 0) ret = wctype_val::upper;
	else if (strcmp(property, "xdigit") == 0) ret = wctype_val::xdigit;
	return (wctype_t)ret;
}

wint_t towlower(wint_t wc)
{
	if (iswupper(wc) != 0)
		wc += 0x20;
	return wc;
}
wint_t towupper(wint_t wc)
{
	if (iswlower(wc))
		wc -= 0x20;
	return wc;
}

enum class wctrans_val : wctype_t {
	tolower,
	toupper,
	zero,
	unknown
};
wint_t towctrans(wint_t wc, wctrans_t desc)
{
	wint_t nRet = wc;
	switch ((wctrans_val)desc)
	{
	case wctrans_val::tolower:
		nRet = towlower(wc);
		break;
	case wctrans_val::toupper:
		nRet = towupper(wc);
		break;
	case wctrans_val::zero:
	case wctrans_val::unknown:
	default:
		break;
	}
	return nRet;
}
wctrans_t wctrans(const char* property)
{
	wctrans_val ret = wctrans_val::unknown;
	if (strcmp(property, "tolower") == 0) ret = wctrans_val::tolower;
	else if (strcmp(property, "toupper") == 0) ret = wctrans_val::toupper;
	return (wctrans_t)ret;
}