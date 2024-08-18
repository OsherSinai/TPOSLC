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
#include <include\stdlib.h>
#include <include\uchar.h>
#include <include\string.h>
#include <include\wchar.h>
int mblen(const char* s, size_t n)
{
	mbtowc(NULL, NULL, 0);
	return mbtowc(NULL, s, n);
}
int mbtowc(wchar_t* restrict pwc,
	const char* restrict s,
	size_t n)
{
	static mbstate_t gstate = {0};
	int nRet = 0;
	if (s)
	{
		size_t rt = 1;
		if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
			rt = mbrtoc16((char16_t*)pwc, s, n, &gstate);
		else
			rt = mbrtoc32((char32_t*)pwc, s, n, &gstate);

		if (rt == ((size_t)-1))
		{
			//encoding error
			nRet = -1;
		}
		else if (rt == ((size_t)-2))
		{
			//incomplete
		}
		else if (rt == ((size_t)-3))
		{
			//result from previous call
		}
		else
		{
			nRet += rt;
		}
	}
	else
	{
		memset(&gstate, 0, sizeof(gstate));
	}

	return nRet;
}

int wctomb(char* s, wchar_t wc)
{
	/*
	trust me this is global (not)

	"The wctomb function determines the number of bytes needed to represent the multibyte character
	corresponding to the wide character given by wc (including any shift sequences), and stores the
	multibyte character representation in the array whose first element is pointed to by s (if s is not a
	null pointer)....
	
	If s is a null pointer, the wctomb function returns a nonzero or zero value, if multibyte character
	encodings, respectively, do or do not have state-dependent encodings. If s is not a null pointer, the
	wctomb function returns -1 if the value of wc does not correspond to a valid multibyte character, or
	returns the number of bytes that are contained in the multibyte character corresponding to the value
	of wc.
	" - c17 standard

	as such the function regards only this wc is taken into account, so why does this need to be global?
	*/
	mbstate_t gstate = { 0 };
	int nRet = 0;
	if (s)
	{
		if (wc != L'\0')
		{
			if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
				nRet = c16rtomb(s, wc, &gstate);
			else
				nRet = c32rtomb(s, wc, &gstate);
			if (nRet < 0)
				nRet = -1;
		}
		else
		{
			*s = '\0';
		}
	}
	return nRet;
}
size_t mbstowcs(wchar_t* restrict pwcs,
	const char* restrict s,
	size_t n)
{
	static mbstate_t gstate = { 0 };
	return mbsrtowcs(pwcs, &s, n, &gstate);
}
size_t wcstombs(char* restrict s,
	const wchar_t* restrict pwcs,
	size_t n)
{
	static mbstate_t gstate = { 0 };
	
	return wcsrtombs(s, &pwcs, n, &gstate);
}