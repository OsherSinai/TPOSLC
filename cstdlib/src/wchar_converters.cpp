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
#include <include\wchar.h>
#include <include\uchar.h>
#include <include\string.h>

wint_t btowc(int c)
{
	wint_t ret = 0;
	if (c != EOF && (uint8_t)c < 0x80)
		ret = (wint_t)c;
	else
		ret = WEOF;
	return ret;
}
int wctob(wint_t c)
{
	int ret = 0;
	if (c != WEOF && c < 0x80)
		ret = (uint8_t)c;
	else
		ret = EOF;
	return ret;
}

int mbsinit(const mbstate_t* ps)
{
	int nRet = 0;
	if (ps == NULL)
		nRet = -1;
	else if (ps->utf32 != 0 || ps->Pending != 0)
		nRet = -1;
	return nRet;
}
size_t mbrlen(const char* restrict s, size_t n,
	mbstate_t* restrict ps)
{
	mbstate_t mbs = { 0 };
	return mbrtowc(NULL, s, n, ps != NULL ? ps : &mbs);
}

size_t mbrtowc(wchar_t* restrict pwc,
	const char* restrict s, size_t n,
	mbstate_t* restrict ps)
{
	size_t nRet = 0;
	if (s)
	{
		size_t rt = 1;
		if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
			rt = mbrtoc16((char16_t*)pwc, s, n, ps);
		else
			rt = mbrtoc32((char32_t*)pwc, s, n, ps);

		if (rt == ((size_t)-1))
		{
			//encoding error
			if(pwc)
				*pwc = L'\0';
			nRet = -1;
		}
		else if (rt == ((size_t)-2))
		{
			//incomplete
			if (pwc)
				*pwc = L'\0';
			nRet = -2;
		}
		else if (rt == ((size_t)-3))
		{
			//result from previous call
			if (pwc)
				pwc++;

		}
		else
		{
			if (pwc)
				pwc++;
			nRet += rt;
		}
	}
	else
	{
		memset(ps, 0, sizeof(mbstate_t));
	}

	return nRet;
}


size_t wcrtomb(char* restrict s, wchar_t wc,
	mbstate_t* restrict ps)
{
	size_t nRet = 0;
	if (s)
	{
		size_t rt = 1;
		if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
			rt = c16rtomb(s, wc, ps);
		else
			rt = c32rtomb(s, wc, ps);
		nRet = (size_t)rt;

		if (wc == L'\0')
		{
			*s = '\0';
			nRet = 1;
		}
		else if (rt == ((size_t)-1))
		{
			//encoding error
			*s = '\0';
		}
		else if (rt == ((size_t)-2))
		{
			//incomplete
			*s = '\0';
		}
		else if (rt == ((size_t)-3))
		{
			//result from previous call
			s++;
		}
	}
	else
	{
		memset(ps, 0, sizeof(mbstate_t));
	}

	return nRet;
}

size_t mbsrtowcs(wchar_t* restrict dst,
	const char** restrict src, size_t len,
	mbstate_t* restrict ps)
{
	size_t nRet = 0;
	uint8_t throwaway[MB_LEN_MAX*2] = { 0 };
	bool bUseThrowaway = dst == NULL;
	if (bUseThrowaway)
		dst = (wchar_t*)throwaway;
	if (src)
	{
		if (*src != '\0')
		{
			size_t bytelen = strlen(*src);
			size_t rt = 1;
			while (rt >= 0 && len > nRet)
			{
				if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
					rt = mbrtoc16((char16_t*)dst, *src, bytelen, ps);
				else
					rt = mbrtoc32((char32_t*)dst, *src, bytelen, ps);

				if (rt == ((size_t)-1))
				{
					//encoding error
					*dst = L'\0';
					nRet = -1;
					break;
				}
				else if (rt == ((size_t)-2))
				{
					//incomplete
					*dst = L'\0';
					nRet = -2;
					break;
				}
				else if (rt == ((size_t)-3))
				{
					//result from previous call
					if (!bUseThrowaway)
						dst++;
					nRet++;

				}
				else
				{
					wchar_t lastwc = *dst;
					if (!bUseThrowaway)
						dst++;
					(*src) += rt;
					bytelen -= rt;
					nRet++;
					if (lastwc == L'\0')
					{
						nRet--;
						break;
					}
				}
			}
		}
		else
		{
			*dst = L'\0';
			nRet = 1;
		}
	}

	if (bUseThrowaway)
	{
		memset(ps, 0, sizeof(mbstate_t));
	}

	return nRet;
}


size_t wcsrtombs(char* restrict dst,
	const wchar_t** restrict src, size_t len,
	mbstate_t* restrict ps)
{
	size_t nRet = 0;
	char throwaway[MB_LEN_MAX * 2] = { 0 };
	bool bUseThrowaway = dst == NULL;
	if (src && *src != L'\0')
	{
		size_t rt = 1;
		while (rt >= 0 && len > nRet)
		{
			memset(throwaway, 0, sizeof(throwaway));
			if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
				rt = c16rtomb(throwaway, *((char16_t*)*src), ps);
			else
				rt = c32rtomb(throwaway, *((char32_t*)*src), ps);

			/*
			if (rt >= 0)
			{
				rt *= sizeof(wchar_t);
			}
			*/

			if (rt == ((size_t)-1))
			{
				//encoding error
				if(!bUseThrowaway)
					*dst = '\0';
				nRet = -1;
				break;
			}
			else if (rt == ((size_t)-2))
			{
				//incomplete
				if (!bUseThrowaway)
					*dst = '\0';
				nRet = -2;
				break;
			}
			else if (rt == ((size_t)-3))
			{
				//result from previous call
				if (!bUseThrowaway)
					dst++;

			}
			else if (rt + nRet > len)
			{
				//cannot save the translated character but character is valid
				break;
			}
			else
			{
				char lastc;
				if (dst)
				{
					memcpy(dst, throwaway, rt);
					lastc = *dst;
				}
				else
				{
					lastc = throwaway[0];
				}
				if(!bUseThrowaway)
					dst += rt;
				wchar_t lastsrc = *(*src);
				if (lastsrc == L'\0')
					break;

				(*src)++;
				nRet += rt;
				if (rt != 0 && lastc == '\0')
				{
					break;
				}

			}
		}
		if (rt == 0)
		{
			if (!bUseThrowaway)
				*dst = '\0';
			(*src) = NULL;
		}
	}
	if (bUseThrowaway)
	{
		memset(ps, 0, sizeof(mbstate_t));
	}

	return nRet;
}