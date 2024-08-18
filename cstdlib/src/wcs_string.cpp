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
#include <include\string.h>
#include <include\wctype.h>
#include "TOSThreadEnvironmentBlock.h"
wchar_t* wcscpy(wchar_t* restrict s1,
	const wchar_t* restrict s2)
{
	wchar_t* pRet = s1;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = *s2;
	return pRet;
}
wchar_t* wcsncpy(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n)
{
	wchar_t* pRet = s1;
	while (n && *s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	while (n)
	{
		*s1 = 0;
		s1++;
		n--;
	}
	return pRet;
}
wchar_t* wmemcpy(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n)
{
	return (wchar_t*)memcpy(s1, s2, n*sizeof(wchar_t));
}
wchar_t* wmemmove(wchar_t* s1, const wchar_t* s2,
	size_t n)
{
	return(wchar_t*)memmove(s1, s2, n * sizeof(wchar_t));
}
wchar_t* wcscat(wchar_t* restrict s1,
	const wchar_t* restrict s2)
{
	wchar_t* pRet = s1;

	while (*s1 != 0)
		s1++;

	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = 0;

	return pRet;
}
wchar_t* wcsncat(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n)
{
	wchar_t* pRet = s1;

	while (*s1 != 0 && n)
	{
		s1++;
	}

	while (*s2 && n)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	while (n)
	{
		*s1 = 0;
		s1++;
		n--;
	}
	return pRet;
}
int wcscmp(const wchar_t* s1, const wchar_t* s2)
{
	int nRet = 0;

	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	nRet = *s1 - *s2;

	return nRet;
}
int wcscoll(const wchar_t* s1, const wchar_t* s2)
{
	int nRet = 0;
	
	while (towlower(*s1) == towlower(*s2))
	{
		nRet = *s1 - *s2;
		if (nRet != 0 || *s1 == 0)
			break;
		s1++;
		s2++;
	}
	if (*s1 != 0 || *s2 != 0)
	{
		nRet = *s1 - *s2;
	}
	return nRet;
}
int wcsncmp(const wchar_t* s1, const wchar_t* s2,
	size_t n)
{
	int nRet = 0;

	while (*s1 && *s2 && n)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		n--;
	}
	if (n)
		nRet = *s1 - *s2;

	return nRet;
}


int wmemcmp(const wchar_t* s1, const wchar_t* s2,
	size_t n)
{
	int nRet = 0;

	while (n)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		n--;
	}
	if (n)
		nRet = *s1 - *s2;

	return nRet;
}


wchar_t* wcschr(const wchar_t* s, wchar_t c)
{
	wchar_t* pRet = NULL;
	while (*s && (*s != c))
		s++;
	if (*s == c)
		pRet = (wchar_t*)s;

	return pRet;
}


static bool IsPresent(const wchar_t* s, wchar_t c)
{
	bool bRet = false;
	while (*s)
	{
		if (*s == c)
		{
			bRet = true;
			break;
		}
		s++;
	}
	return bRet;
}
size_t wcscspn(const wchar_t* s1, const wchar_t* s2)
{
	size_t Ret = 0;

	while (*s1)
	{
		if (IsPresent(s2, *s1) == true)
			break;
		Ret++;
		s1++;
	}

	return Ret;
}
wchar_t* wcspbrk(const wchar_t* s1, const wchar_t* s2)
{
	wchar_t* pRet = NULL;

	while (*s1)
	{
		if (IsPresent(s2, *s1) == true)
		{
			pRet = (wchar_t*)s1;
			break;
		}
		s1++;
	}
	return pRet;
}
wchar_t* wcsrchr(const wchar_t* s, wchar_t c)
{
	wchar_t* pRet = NULL;

	while (*s)
	{
		if (*s == c)
			pRet = (wchar_t*)s;
		s++;
	}

	if (*s == c)
		pRet = (wchar_t*)s;

	return pRet;
}
size_t wcsspn(const wchar_t* s1, const wchar_t* s2)
{
	size_t Ret = 0;

	while (*s1)
	{
		if (IsPresent(s2, *s1) == false)
			break;
		Ret++;
		s1++;
	}

	return Ret;
}

inline static bool ContainSubstr(const wchar_t* s1, const wchar_t* s2)
{
	bool bRet = false;

	while (*s1 && *s2 && *s1 == *s2) {
		s1++;
		s2++;
	}
	bRet = *s2 == 0;

	return bRet;
}
wchar_t* wcsstr(const wchar_t* s1, const wchar_t* s2)
{
	wchar_t* pRet = NULL;

	while (*s1)
	{
		if (ContainSubstr(s1, s2) == true)
		{
			pRet = (wchar_t*)s1;
			break;
		}
		s1++;
	}
	return pRet;
}
wchar_t* wmemchr(const wchar_t* s, wchar_t c, size_t n)
{
	wchar_t* pRet = NULL;
	while (n && (*s != c))
	{
		s = s + 1;
		n--;
	}
	if (*s == c)
		pRet = (wchar_t*)s;

	return pRet;
}
size_t wcslen(const wchar_t* s)
{
	size_t len = 0;
	while (*s)
	{
		s++;
		len++;
	}

	return len;
}
wchar_t* wmemset(wchar_t* s, wchar_t c, size_t n)
{
	wchar_t* pRet = s;
	while (n)
	{
		*s = c;
		s++;
		n--;
	}
	return pRet;
}

size_t wcsxfrm(wchar_t* restrict s1,
	const wchar_t* restrict s2, size_t n)
{
	size_t Ret = 0;
	if (s1 && s2 && n)
		wcsncpy(s1, s2, n);
	if(s2)
		Ret = wcslen(s2);
	return Ret;
}

wchar_t* wcstok(wchar_t* restrict s1,
	const wchar_t* restrict s2,
	wchar_t** restrict ptr)
{
	wchar_t* pRet = NULL;
	wchar_t* pTmp = NULL;
	wchar_t* throwaway = NULL;
	if (ptr == NULL)
		ptr = &throwaway;
	if (s1)
	{
		*ptr = s1;
		pRet = *ptr;
	}
	if (*ptr)
	{
		do
		{
			if (*ptr == pTmp)
				(*ptr)++;
			pTmp = wcspbrk(*ptr, s2);
		} while (*ptr == pTmp);

		if (pTmp)
		{
			pRet = *ptr;
			*pTmp = 0;
			*ptr = pTmp + 1;
		}
		else
		{
			if (**ptr == L'\0')
				pRet = NULL;
			else
				pRet = *ptr;
			*ptr = NULL;
		}
	}
	return pRet;
}