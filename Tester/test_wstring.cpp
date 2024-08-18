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
#include "TestCaseUtils.h"
#include "TestSuites.h"
#include <include/time.h>
#include <include/wchar.h>
#include <include/string.h>
#include <include/stdlib.h>
#include <include/stdio.h>
#include <include/wctype.h>

void test_wmemcpy()
{
	const size_t c_len = 16;
	wchar_t BufferDst1[c_len] = { 0 };
	wchar_t BufferDst2[c_len] = { 0 };
	wchar_t BufferDst3[c_len] = { 0 };
	wchar_t BufferSrc[c_len] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	bool bEq;
	void* Ret = wmemcpy(BufferDst1, BufferSrc, c_len);
	CASE_CHECK_EQ(Ret, BufferDst1, "wmemcpy test 1, Return value");
	bEq = true;
	for (int i = 0; i < c_len; i++)
	{
		if (BufferSrc[i] != BufferDst1[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemcpy test 1, Equality");
	Ret = wmemcpy(BufferDst2, BufferSrc, c_len / 2);
	CASE_CHECK_EQ(Ret, BufferDst2, "wmemcpy test 2, Return value");
	bEq = true;
	for (int i = 0; i < c_len / 2; i++)
	{
		if (BufferSrc[i] != BufferDst2[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemcpy test 2, Equality");
	Ret = wmemcpy(BufferDst3, BufferSrc, 0);
	CASE_CHECK_EQ(Ret, BufferDst3, "wmemcpy test 3, Return value");
	bEq = true;
	for (int i = 0; i < c_len / 2; i++)
	{
		if (0 != BufferDst3[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemcpy test 3, Equality");
}
void test_wmemmove()
{
	const size_t c_len = 16;
	wchar_t ControlResult1[c_len] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	wchar_t ControlResult2[c_len] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15 };
	wchar_t ControlResult3[c_len] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 12, 13, 14, 15, 13, 14, 15 };

	wchar_t BufferDst[c_len] = { 0 };
	wchar_t BufferSrc[c_len] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	bool bEq;
	void* Ret = wmemmove(BufferDst, BufferSrc, c_len);
	CASE_CHECK_EQ(Ret, BufferDst, "wmemmove test 1, Return value");
	bEq = true;
	for (int i = 0; i < c_len; i++)
	{
		if (ControlResult1[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemmove test 1, Equality\t");
	Ret = wmemmove(BufferDst + 4, BufferDst, 8);
	CASE_CHECK_EQ(Ret, BufferDst + 4, "wmemmove test 2, Return value");
	bEq = true;
	for (int i = 0; i < c_len; i++)
	{
		if (ControlResult2[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemmove test 2, Equality\t");
	Ret = wmemmove(BufferDst + 9, BufferDst + 12, 4);
	CASE_CHECK_EQ(Ret, BufferDst + 9, "wmemmove test 3, Return value");
	bEq = true;
	for (int i = 0; i < c_len; i++)
	{
		if (ControlResult3[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "wmemmove test 3, Equality\t");
}

void test_wmemcmp()
{
	wchar_t ControlResult1[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	wchar_t ControlResult2[16] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15 };

	int nRet;
	nRet = wmemcmp(ControlResult1, ControlResult1, 16);
	CASE_CHECK_EQ(nRet, 0, "wmemcmp test 1, Equality");
	nRet = wmemcmp(ControlResult1, ControlResult2, 16);
	CASE_CHECK_BT(nRet, 0, "wmemcmp test 2, Equality");
	nRet = wmemcmp(ControlResult2, ControlResult1, 16);
	CASE_CHECK_ST(nRet, 0, "wmemcmp test 3, Equality");
	nRet = wmemcmp(ControlResult2, ControlResult2, 4);
	CASE_CHECK_EQ(nRet, 0, "wmemcmp test 4, Equality");

}
void test_wcscmp()
{
	CASE_CHECK_EQ(wcscmp(L"abcd", L"abcd"), 0, "wcscmp test 1, equal");
	CASE_CHECK_ST(wcscmp(L"abcd", L"abcdc"), 0, "wcscmp test 2, s2 bigger");
	CASE_CHECK_BT(wcscmp(L"abcdc", L"abcd"), 0, "wcscmp test 3, s1 bigger");
	CASE_CHECK_ST(wcscmp(L"abcc", L"abcd"), 0, "wcscmp test 4, s1 smaller");
	CASE_CHECK_BT(wcscmp(L"abcd", L"abcc"), 0, "wcscmp test 5, s2 smaller");
}
void test_wcslen()
{
	CASE_CHECK_EQ(wcslen(L"abcd"), 4, "wcslen test 1, \"abcd\" == 4");
	CASE_CHECK_EQ(wcslen(L""), 0, "wcslen test 2, \"\" == 0");
	CASE_CHECK_EQ(wcslen(L"145\0\\4444"), 3, "wcslen test 3, \"145\\0\\4444\" == 3");
}
void test_wcscpy()
{
	wchar_t Buffer[8] = { 0 };
	wchar_t Src[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	wchar_t ControlResult1[4] = { 'a', 'b', 'c', 0 };
	wchar_t ControlResult2[8] = { 'a', 'b', 'c', 0, 'e', 'f', 'g', 0 };
	wchar_t* ret;
	ret = wcscpy(Buffer, Src);
	CASE_CHECK_EQ(Buffer, ret, "wcscpy test 1 (return)");
	CASE_CHECK_EQ(wmemcmp(Buffer, Src, 8), 0, "wcscpy test 2 (memory cmp)");
	ret = wcscpy(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "wcscpy test 3 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 3, "wcscpy test 4 (strlen == 3)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult2, 8), 0, "wcscpy test 5 (memory cmp)");
}
void test_wcsncpy()
{
	wchar_t Buffer[8] = { 0 };
	wchar_t Src[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	wchar_t ControlResult1[4] = { 'a', 'b', 'c', 0 };
	wchar_t ControlResult2[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	wchar_t ControlResult3[8] = { 'a', 'b', 'c', 0, 0, 0, 'g', 0 };
	wchar_t* ret;
	ret = wcsncpy(Buffer, Src, 8);
	CASE_CHECK_EQ(Buffer, ret, "wcsncpy test 1 (return)");
	CASE_CHECK_EQ(wmemcmp(Buffer, Src, 8), 0, "wcsncpy test 2 (memory cmp)");
	ret = wcsncpy(Buffer, ControlResult1, 3);
	CASE_CHECK_EQ(Buffer, ret, "wcsncpy test 3 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 7, "wcsncpy test 4 (strlen == 7)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult2, 8), 0, "wcsncpy test 5 (memory cmp)");
	ret = wcsncpy(Buffer, ControlResult1, 6);
	CASE_CHECK_EQ(Buffer, ret, "wcsncpy test 6 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 3, "wcsncpy test 7 (strlen == 3)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult3, 8), 0, "wcsncpy test 8 (memory cmp)");
}
void test_wcscat()
{
	wchar_t Buffer[8] = { 0 };
	wchar_t ControlResult1[8] = { 'a', 'b', 'c', 0, 0, 0, 0, 0 };
	wchar_t ControlResult2[8] = { 'a', 'b', 'c', 'a', 'b', 'c', 0, 0 };
	wchar_t* ret;
	ret = wcscat(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "strcat test 1 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 3, "strcat test 2 (strlen = 3)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult1, 8), 0, "strcat test 3 (memory cmp)");

	ret = wcscat(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "strcat test 4 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 6, "strcat test 5 (strlen = 6)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult2, 8), 0, "strcat test 6 (memory cmp)");

}
void test_wcsncat()
{
	wchar_t Buffer[8] = { 0 };
	wchar_t ControlResult1[8] = { 'a', 'b', 'c', 0, 0, 0, 0, 0 };
	wchar_t ControlResult2[8] = { 'a', 'b', 'c', 'a', 'b', 0, 0, 0 };
	wchar_t* ret;
	ret = wcsncat(Buffer, ControlResult1, 5);
	CASE_CHECK_EQ(Buffer, ret, "wcsncat test 1 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 3, "wcsncat test 2 (strlen = 3)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult1, 8), 0, "wcsncat test 3 (memory cmp)");

	ret = wcsncat(Buffer, ControlResult1, 2);
	CASE_CHECK_EQ(Buffer, ret, "wcsncat test 4 (return)");
	CASE_CHECK_EQ(wcslen(Buffer), 5, "wcsncat test 5 (strlen = 5)");
	CASE_CHECK_EQ(wmemcmp(Buffer, ControlResult2, 8), 0, "wcsncat test 6 (memory cmp)");

}

void test_wcsncmp()
{
	wchar_t ControlResult1[8] = { L'a', L'b', L'c', 0, 0, 0, 0, 0 };
	wchar_t ControlResult2[8] = { L'a', L'b', L'c', L'a', L'b', 0, 0, 0 };
	wchar_t ControlResult3[8] = { L'a', L'b', L'd', 0, 0, 0, 0, 0 };
	CASE_CHECK_EQ(wcsncmp(ControlResult1, ControlResult1, 3), 0, "wcsncmp test 1, equal");
	CASE_CHECK_EQ(wcsncmp(ControlResult1, ControlResult2, 3), 0, "wcsncmp test 2, equal");
	CASE_CHECK_EQ(wcsncmp(ControlResult2, ControlResult1, 3), 0, "wcsncmp test 3, s1 bigger");
	CASE_CHECK_ST(wcsncmp(ControlResult1, ControlResult2, 4), 0, "wcsncmp test 4, s1 smaller");
	CASE_CHECK_BT(wcsncmp(ControlResult2, ControlResult1, 4), 0, "wcsncmp test 5, s2 smaller");
	CASE_CHECK_ST(wcsncmp(ControlResult1, ControlResult3, 4), 0, "wcsncmp test 6, s1 smaller");
	CASE_CHECK_BT(wcsncmp(ControlResult3, ControlResult1, 4), 0, "wcsncmp test 7, s2 smaller");
}
void test_wmemchr()
{
	constexpr size_t c_len = 255;
	wchar_t  uch[c_len];
	for (int i = 0; i < c_len; i++)
		uch[i] = i;
	bool bSuccess = true;
	for (int i = 0; i < c_len; i++)
	{
		wchar_t* p = wmemchr(uch, i, c_len);
		if (p != (uch + i))
		{
			bSuccess = false;
			break;
		}
	}
	if (bSuccess)
	{
		wchar_t* p = wmemchr(uch, c_len, c_len);
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "wmemchr test, uint8 range check");
}
void test_wcschr()
{
	constexpr size_t c_len = 255;
	wchar_t uch[c_len];
	for (int i = 1; i < c_len; i++)
		uch[i - 1] = i;
	uch[c_len-1] = 0;
	bool bSuccess = true;
	for (int i = 1; i < c_len; i++)
	{
		wchar_t* p = wcschr(uch, i);
		if (p != (uch + (i - 1)))
		{
			bSuccess = false;
			break;
		}
	}
	if (bSuccess)
	{
		wchar_t* p = wcschr(uch, 255);
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "wcschr test, uint8 range check");
}
void test_wcscspn()
{
	CASE_CHECK_EQ(wcscspn(L"", L"abcdefg"), 0, "wcscspn test 1, len = 0");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"hij"), 23, "wcscspn test 2, len = 23");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"g"), 17, "wcscspn test 3, len = 17");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"fg"), 14, "wcscspn test 4, len = 14");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"efg"), 10, "wcscspn test 5, len = 10");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"defg"), 6, "wcscspn test 6, len = 6");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"cdefg"), 5, "wcscspn test 7, len = 5");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"bcdefg"), 3, "wcscspn test 8, len = 3");
	CASE_CHECK_EQ(wcscspn(L"aaabbcddddeeeefffgggggg", L"abcdefg"), 0, "wcscspn test 9, len = 0");
}
void test_wcspbrk()
{
	wchar_t str[2];
	wchar_t span[2];
	str[1] = 0;
	span[1] = 0;
	bool bSuccess = true;
	for (int i = 1; i < 255; i++)
	{
		str[0] = i;
		span[0] = i;
		wchar_t* p = wcspbrk(str, span);
		if (p != str)
		{
			bSuccess = false;
			break;
		}
	}
	if (bSuccess)
	{
		str[0] = 1;
		span[0] = 2;
		wchar_t* p = wcspbrk(str, span);
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "strchr test, uint8 range check");
}
void test_wcsrchr()
{
	wchar_t ControlResult1[8] = L"aaa";
	wchar_t ControlResult2[8] = L"bbaaa";
	CASE_CHECK_EQ(wcsrchr(ControlResult1, L'\0'), ControlResult1 + 3, "wcsrchr test 1, null terminator");
	CASE_CHECK_EQ(wcsrchr(ControlResult1, L'a'), ControlResult1 + 2, "wcsrchr test 2, last");
	CASE_CHECK_EQ(wcsrchr(ControlResult1, L'b'), 0, "wcsrchr test 3, not found");
	CASE_CHECK_EQ(wcsrchr(ControlResult2, L'b'), ControlResult2 + 1, "wcsrchr test 4, last of sequence 1");
	CASE_CHECK_EQ(wcsrchr(ControlResult2, L'a'), ControlResult2 + 4, "wcsrchr test 5, last of sequence 2");

}
void test_wcsspn()
{
	CASE_CHECK_EQ(wcsspn(L"", L"abcdefg"), 0, "wcsspn test 1, len = 0");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"abcdefg"), 23, "wcsspn test 2, len = 23");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"abcdef"), 17, "wcsspn test 3, len = 17");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"abcde"), 14, "wcsspn test 4, len = 14");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"abcd"), 10, "wcsspn test 5, len = 10");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"abc"), 6, "wcsspn test 6, len = 6");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"ab"), 5, "wcsspn test 7, len = 5");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"a"), 3, "wcsspn test 8, len = 3");
	CASE_CHECK_EQ(wcsspn(L"aaabbcddddeeeefffgggggg", L"hijk"), 0, "wcsspn test 9, len = 0");
}
void test_wcsstr()
{
	wchar_t ControlResult1[8] = L"aabbaaa";
	wchar_t ControlResult2[8] = L"aaa";
	wchar_t ControlResult3[8] = L"aa";
	wchar_t ControlResult4[8] = L"bb";
	wchar_t ControlResult5[8] = L"cc";
	CASE_CHECK_EQ(wcsstr(ControlResult1, ControlResult5), 0, "wcsstr test 1");
	CASE_CHECK_EQ(wcsstr(ControlResult1, ControlResult2), ControlResult1 + 4, "wcsstr test 2");
	CASE_CHECK_EQ(wcsstr(ControlResult1, ControlResult3), ControlResult1, "wcsstr test 3");
	CASE_CHECK_EQ(wcsstr(ControlResult1, ControlResult4), ControlResult1 + 2, "wcsstr test 4");
}
void test_wmemset()
{
	constexpr size_t c_len = 256;
	wchar_t ch[c_len];
	void* pRet;
	bool bSuccess = true;

	pRet = wmemset(ch, 0, c_len);
	for (int i = 0; i < c_len; i++)
	{
		if (ch[i] != 0)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_CHECK_EQ(pRet, ch, "wmemset test 1, return");
	CASE_CHECK_EQ(bSuccess, true, "wmemset test 2, set to 0x00");

	bSuccess = true;
	pRet = wmemset(ch, 0xF0, c_len);
	for (int i = 0; i < c_len; i++)
	{
		if (ch[i] != 0xF0)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_CHECK_EQ(pRet, ch, "wmemset test 3, return");
	CASE_CHECK_EQ(bSuccess, true, "wmemset test 4, set to 0xF0");
}
void test_wcstok()
{
	// example taken from c17 proposal
	wchar_t str[] = L"?a???b,,,#c";
	wchar_t* t;
	wchar_t* ptr = NULL;
	t = wcstok(str, L"?", &ptr); // t points to the token "a"
	CASE_CHECK_EQ(wcscmp(t, L"a"), 0, "wcstok test 1, part 1");
	t = wcstok(NULL, L",", &ptr); // t points to the token "??b"
	CASE_CHECK_EQ(wcscmp(t, L"??b"), 0, "wcstok test 2, part 2");
	t = wcstok(NULL, L"#,", &ptr); // t points to the token "c"
	CASE_CHECK_EQ(wcscmp(t, L"c"), 0, "wcstok test 3, part 3");
	t = wcstok(NULL, L"?", &ptr); // t is a null pointer
	CASE_CHECK_EQ(t, 0, "wcstok test 4, end");
}
void test_wcsxfrm()
{
	wchar_t Dst[16] = { 0 };
	wchar_t Src[16] = L"abcdef";
	size_t NeededSize = wcsxfrm(0, Src, 0);
	CASE_CHECK_EQ(NeededSize, 6, "wcsxfrm test 1, needed size");
	NeededSize = wcsxfrm(Dst, Src, NeededSize);
	CASE_CHECK_EQ(NeededSize, 6, "wcsxfrm test 2, needed size");
	CASE_CHECK_EQ(wcscmp(Dst, Src), 0, "wcsxfrm test 3, string cmp");
}
void test_wcscoll()
{
	CASE_CHECK_EQ(wcscoll(L"abcd", L"abcd"), 0, "wcscoll test 1, equal");
	CASE_CHECK_ST(wcscoll(L"abcd", L"abcdc"), 0, "wcscoll test 2, s2 bigger");
	CASE_CHECK_BT(wcscoll(L"abcdc", L"abcd"), 0, "wcscoll test 3, s1 bigger");
	CASE_CHECK_ST(wcscoll(L"abcc", L"abcd"), 0, "wcscoll test 4, s1 smaller");
	CASE_CHECK_BT(wcscoll(L"abcd", L"abcc"), 0, "wcscoll test 5, s2 smaller");
}



void test_wcsftime()
{
	wchar_t StrBuf[4096];
	struct tm start;
	start.tm_hour = 13;
	start.tm_min = 11;
	start.tm_sec = 33;
	start.tm_mon = 6;
	start.tm_mday = 26;
	start.tm_year = 124;
	start.tm_wday = 5;
	start.tm_yday = 207;
	start.tm_isdst = 1;
	memset(StrBuf, 'a', sizeof(StrBuf));
	size_t Size;

	Size = wcsftime(StrBuf, 4095, L"%%%t%n", &start);
	CASE_CHECK_EQ(Size, 3, "strftime, test 1, return equal 3");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"%\t\n"), 0, "strftime, test 2, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%Y%EY%y%Oy%Ey%C%EC%G%g", &start);
	CASE_CHECK_EQ(Size, 24, "strftime, test 3, return equal 24");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"202420242424242020202424"), 0, "strftime, test 4, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%b%Ob%h%B%OB%m%Om", &start);
	CASE_CHECK_EQ(Size, 21, "strftime, test 5, return equal 21");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"JulJulJulJulyJuly0707"), 0, "strftime, test 6, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%U%OU%W%OW%V%OV", &start);
	CASE_CHECK_EQ(Size, 12, "strftime, test 6, return equal 12");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"292930303030"), 0, "strftime, test 7, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%j%d%Od%e%Oe", &start);
	CASE_CHECK_EQ(Size, 11, "strftime, test 8, return equal 11");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"20826262626"), 0, "strftime, test 9, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%a%A%w%Ow%u%Ou", &start);
	CASE_CHECK_EQ(Size, 13, "strftime, test 9, return equal 13");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"FriFriday5555"), 0, "strftime, test 10, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%H%OH%I%OI%M%OM%S%OS", &start);
	CASE_CHECK_EQ(Size, 16, "strftime, test 11, return equal 16");
	CASE_CHECK_EQ(wcscmp(StrBuf, L"1313010111113333"), 0, "strftime, test 12, string ret");

	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%c%Ec%x%Ex%X%EX%D%F%r%R%T%p", &start);
	CASE_CHECK_EQ(Size, 124, "strftime, test 11, return equal 129");
	int nStrcmp = wcscmp(StrBuf, L"Fri Jul 26 13:11:33 2024Fri Jul 26 13:11:33 202407/26/2407/26/2413:11:3313:11:3307/26/242024-07-2601:11:33 PM13:1113:11:33PM");
	CASE_CHECK_EQ(nStrcmp, 0, "strftime, test 12, string ret");

	/*
	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%z", &start);
	CASE_CHECK_EQ(Size, 5, "strftime, test 13, return equal 5");
	
	CASE_MANUAL_CHECK_START();
	printf("manual check: (utc offset) ");
	putc('%', stdout);
	printf("z = %s\n",
		StrBuf
	);
	CASE_MANUAL_CHECK_END();
	memset(StrBuf, 0, sizeof(StrBuf));
	Size = wcsftime(StrBuf, 4095, L"%Z", &start);
	CASE_CHECK_NE(Size, 0, "strftime, test 13, return not equal 0");
	CASE_MANUAL_CHECK_START();
	printf("manual check: (os timezone) ");
	putc('%', stdout);
	printf("Z = %s\n",
		StrBuf
	);
	CASE_MANUAL_CHECK_END();
	*/
	return;
}

void test_btowc_wctob()
{
	char8_t uch[] = u8"あ";
	wint_t wret = 0;
	int n = 'a';
	wret = btowc(n);
	n = *(int*)uch;
	CASE_CHECK_EQ(wret, L'a', "btowc, valid conversion");
	wret = btowc(n);
	CASE_CHECK_EQ(wret, WEOF, "btowc, invalid conversion");
	n = wctob(L'a');
	CASE_CHECK_EQ(n, 'a', "wctob, valid conversion");
	n = wctob(L'あ');
	CASE_CHECK_EQ(n, EOF, "wctob, invalid conversion");

}
void test_mbsinit()
{
	char8_t uch[] = u8"🍌";
	char16_t wc;
	mbstate_t state = { 0 };
	int nRet = mbsinit(&state);
	CASE_CHECK_EQ(nRet, 0, "mbsinit, check 1");
	mbrtoc16(&wc, (char*)uch, 4, &state);
	nRet = mbsinit(&state);
	CASE_CHECK_NE(nRet, 0, "mbsinit, check 2");
	mbrtoc16(&wc, (char*)uch, 4, &state);
	nRet = mbsinit(&state);
	CASE_CHECK_EQ(nRet, 0, "mbsinit, check 3");
}
void test_mbrlen()
{
	char8_t uchinv[4] = u8"\xc3\x28";
	char8_t uch[] = u8"🍌";
	mbstate_t state = { 0 };
	size_t ret = mbrlen((char*)uch, 4, &state);
	CASE_CHECK_BE(ret, 0, "mbrlen, check 1");
	state = { 0 };
	ret = mbrlen((char*)uch, 2, &state);
	CASE_CHECK_EQ(ret, (size_t)-2, "mbrlen, check 2");
	state = { 0 };
	ret = mbrlen((char*)uchinv, 2, &state);
	CASE_CHECK_EQ(ret, (size_t)-1, "mbrlen, check 3");
}

void test_mbrtowc()
{
	//constexpr const wchar_t c_validation[6] = { 0x7a, 0xdf, 0x6c34, 0xd83c, 0xdf4c, 0 };
	constexpr const wchar_t c_validation[] = L"zß水🍌";
	const char8_t str8[11] = u8"zß水🍌";
	wchar_t wsz[11] = {0};
	mbstate_t state = {0};
	size_t ret;
	char* p = (char*)str8;
	char* pEnd = p + sizeof(str8);
	wchar_t* pwc = wsz;
	size_t sz = sizeof(str8);
	while (p != pEnd)
	{
		ret = mbrtowc(pwc, p, sz, &state);
		if (ret < 0 || *pwc == L'\0')
			break;
		sz -= ret;
		p += ret;
		pwc++;
	}
	size_t len = (sizeof(c_validation) / sizeof(c_validation[0]));
	CASE_CHECK_EQ(ret, 0, "mbrtowc, ret");
	sz = wcslen(wsz);
	CASE_CHECK_EQ(sz, len - 1, "mbrtowc, len");
	CASE_CHECK_EQ(wmemcmp(c_validation, wsz, sz), 0, "mbrtowc, content");
}
void test_mbsrtowcs()
{
	//constexpr const wchar_t c_validation[6] = { 0x7a, 0xdf, 0x6c34, 0xd83c, 0xdf4c, 0 };
	constexpr const wchar_t c_validation[] = L"zß水🍌";
	const char8_t str8[11] = u8"zß水🍌";
	wchar_t wsz[11] = { 0 };
	mbstate_t state = { 0 };
	size_t ret;
	char* p = (char*)str8;
	size_t sz = sizeof(str8);
	size_t len = (sizeof(c_validation)/sizeof(c_validation[0]));
	ret = mbsrtowcs(wsz, (const char**)&p, 11, &state);
	CASE_CHECK_EQ(ret, len - 1, "mbsrtowcs, ret");
	sz = wcslen(wsz);
	CASE_CHECK_EQ(sz, len - 1, "mbsrtowcs, len");
	CASE_CHECK_EQ(wmemcmp(c_validation, wsz, sz), 0, "mbsrtowcs, content");
}

void test_wcrtomb()
{
	constexpr const char8_t c_validation[] = u8"zß水🍌";
	const wchar_t wsz[6] = L"zß水🍌";
	char8_t str8[6*4] = { 0 };
	mbstate_t state = { 0 };
	size_t ret;
	char* p = (char*)str8;
	const wchar_t* pwc = wsz;
	size_t sz = 0;
	while (1)
	{
		ret = wcrtomb(p, *pwc,  &state);
		if (ret < 0 || *pwc == L'\0')
			break;
		sz -= ret;
		p += ret;
		pwc++;
	}
	CASE_CHECK_EQ(ret, 1, "mbrtowc, ret");
	sz = strlen((char*)str8);
	CASE_CHECK_EQ(sz, 10, "mbrtowc, len");
	CASE_CHECK_EQ(memcmp(c_validation, str8, sz), 0, "mbrtowc, content");
}
void test_wcsrtombs()
{
	constexpr const wchar_t c_org[8] = L"zß水🍌";
	constexpr const char8_t c_validation[11] = u8"zß水🍌";
	char sz[6*4] = { 0 };
	mbstate_t state = { 0 };
	size_t ret;
	wchar_t* p = (wchar_t*)c_org;
	size_t szsize = sizeof(c_org);
	ret = wcsrtombs(sz, (const wchar_t**)&p, 6*4, &state);
	CASE_CHECK_EQ(ret, 10, "wcsrtombs, ret");
	szsize = strlen(sz);
	CASE_CHECK_EQ(szsize, 10, "wcsrtombs, len");
	CASE_CHECK_EQ(memcmp(c_validation, sz, szsize), 0, "wcsrtombs, content");
}


void testf_wprintf()
{
	remove("testing_files/wprintf_test.txt");
	FILE* pFile = fopen("testing_files/wprintf_test.txt", "w");
	if (pFile)
	{
		const wchar_t c_validation[] = L"17872111442017451144201745-861330324592032919917872111442017451144201745-86133032459203291992121021104146210211041462102110416731452504146210211787211144201745114420174598334408277892224171122114433221144332211887766554433221111221144332211443322118877665544332211a aFFEEDDCCBBAA9988%abcdefgh";
		wchar_t* wsz = (wchar_t*)malloc(0x10000 * sizeof(wchar_t));
		if (wsz)
		{
			void* ptr = (void*)0xFFEEDDCCBBAA9988LLU;
			wchar_t str[] = L"abcdefgh";
			int cc = *(int*)str;
			wmemset(wsz, 0, 0x10000);
			uint64_t u64 = 0x8877665544332211LLU;
			int nRet = fwprintf(pFile,
				L"%hhd%hd%d%ld%lld"
				L"%hhi%hi%i%li%lli"
				L"%hho%ho%o%lo%llo"
				L"%hhu%hu%u%lu%llu"
				L"%hhx%hx%x%lx%llx"
				L"%hhX%hX%X%lX%llX"
				L"%c%2c"
				L"%p"
				L"%%"
				L"%s"
				,
				(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
				(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
				cc, cc,
				ptr,
				str
			);
			CASE_CHECK_EQ(nRet, 0x124, "fwprintf/vfwprintf/wprintf  ret check");
			fclose(pFile);
			pFile = fopen("testing_files/wprintf_test.txt", "r");
			if (pFile)
			{
				fread(wsz, 1, 0xFFFF*2, pFile);
				const wchar_t* p1 = c_validation;
				const wchar_t* p2 = wsz;
				while (towlower(*p1) == towlower(*p2))
				{
					if (*p1 == 0)
						break;
					if (*p2 == 0)
						break;
					p1++;
					p2++;
				}
				CASE_CHECK_EQ(*p1, *p2, "fwprintf/vfwprintf/wprintf check");
				CASE_MANUAL_CHECK_START();
				printf("NOTICE: the this implementation doesn't yet implement floating point conversion and doesn't check it\n");
				CASE_MANUAL_CHECK_END();
			}
			remove("testing_files/wprintf_test.txt");
			free(wsz);
		}
		fclose(pFile);
	}
}

void test_swprintf()
{
	wchar_t* wsz = (wchar_t*)malloc(0x10000 * sizeof(wchar_t));
	if (wsz)
	{
		const wchar_t c_validation[] = L"17872111442017451144201745-861330324592032919917872111442017451144201745-86133032459203291992121021104146210211041462102110416731452504146210211787211144201745114420174598334408277892224171122114433221144332211887766554433221111221144332211443322118877665544332211a aFFEEDDCCBBAA9988%abcdefgh";
		void* ptr = (void*)0xFFEEDDCCBBAA9988LLU;
		wchar_t str[] = L"abcdefgh";
		int cc = *(int*)str;
		wmemset(wsz, 0, 0x10000);
		uint64_t u64 = 0x8877665544332211LLU;
		int nRet = swprintf(wsz, 0xFFFF,
			L"%hhd%hd%d%ld%lld"
			L"%hhi%hi%i%li%lli"
			L"%hho%ho%o%lo%llo"
			L"%hhu%hu%u%lu%llu"
			L"%hhx%hx%x%lx%llx"
			L"%hhX%hX%X%lX%llX"
			L"%c%2c"
			L"%p"
			L"%%"
			L"%s"
			,
			(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
			(int8_t)u64, (int16_t)u64, (int32_t)u64, (long)u64, (int64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			(uint8_t)u64, (uint16_t)u64, (uint32_t)u64, (unsigned long)u64, (uint64_t)u64,
			cc, cc,
			ptr,
			str
		);
		const wchar_t* p1 = c_validation;
		const wchar_t* p2 = wsz;
		while (towlower(*p1) == towlower(*p2))
		{
			if (*p1 == 0)
				break;
			if (*p2 == 0)
				break;
			p1++;
			p2++;
		}
		CASE_CHECK_EQ(nRet, 0x124, "swprintf/vswprintf ret check");

		CASE_CHECK_EQ(*p1, *p2, "swprintf/vswprintf check");
		CASE_MANUAL_CHECK_START();
		printf("NOTICE: the this implementation doesn't yet implement floating point conversion and doesn't check it\n");
		CASE_MANUAL_CHECK_END();
		free(wsz);
	}
}

void test_fwscanf()
{
	constexpr const char szUTF16File[] = "testing_files/scanf_test-16.txt";
	constexpr const char szUTF32File[] = "testing_files/scanf_test-32.txt";
	const char* pFileName;
	if constexpr (sizeof(wchar_t) == sizeof(uint16_t))
		pFileName = szUTF16File;
	else
		pFileName = szUTF32File;
	constexpr uint8_t c_validation_8[6] = { 0x7f, 0x7f, 0x57, 0x7f, 0x27, 0x27 };
	constexpr uint16_t c_validation_16[6] = { 0x0190, 0x0190, 0x0100, 0x0190, 0x0400, 0x0400 };
	constexpr uint32_t c_validation_32_1[6] = { 0x000001f4, 0x000001f4, 0x00000140, 0x000001f4, 0x00000500, 0x00000500 };
	constexpr uint32_t c_validation_32_2[6] = { 0x00000294, 0x00000294, 0x000001b0, 0x00000294, 0x00000660, 0x00000660 };
	constexpr uint64_t c_validation_64[6] = { 0xffffffffffffe19f, 0xffffffffffffe19f, 0xfffffffffffff001, 0x000000000000270f, 0x0000000000009999, 0x0000000000009999 };
	int c_validation_cc1 = 0x20;
	wchar_t c_validation_cc2[] = L"a bb";
	void* c_validation_p = (void*)0x0000000000001234llu;
	wchar_t c_validation_ch[512] = L"abcdefg";
	size_t c_validation_ret = 0x0000000000000023;
	int c_validation_n = 0x000000AE;

	FILE* pFile = fopen(pFileName, "r");
	CASE_CHECK_NE(pFile, NULL, "loading scanf_test.txt");
	if (pFile)
	{
		fwide(pFile, 1);
		//we've got BOM in the file, read it and skip it
		wchar_t BOM = 0;
		fread(&BOM, 1,sizeof(wchar_t), pFile);

		uint8_t u8[6] = { 0 };
		uint16_t u16[6] = { 0 };
		uint32_t u32_1[6] = { 0 };
		uint32_t u32_2[6] = { 0 };
		uint64_t u64[6] = { 0 };
		int cc1 = 0;
		wchar_t cc2[5] = {0};
		void* p = 0;
		wchar_t ch[512] = { 0 };
		int n = 0;
		size_t srt = fwscanf(pFile,
			L"%hhd %hd %d %ld %lld "
			L"%hhi %hi %i %li %lli "
			L"%hho %ho %o %lo %llo "
			L"%hhu %hu %u %lu %llu "
			L"%hhx %hx %x %lx %llx "
			L"%hhX %hX %X %lX %llX"
			L"%c%4c "
			L"%p"
			L"%% "
			L"%s%n",
			u8 + 0, u16 + 0, u32_1 + 0, (long*)u32_2 + 0, u64 + 0,
			u8 + 1, u16 + 1, u32_1 + 1, (long*)u32_2 + 1, u64 + 1,
			u8 + 2, u16 + 2, u32_1 + 2, (unsigned long*)u32_2 + 2, u64 + 2,
			u8 + 3, u16 + 3, u32_1 + 3, (unsigned long*)u32_2 + 3, u64 + 3,
			u8 + 4, u16 + 4, u32_1 + 4, (unsigned long*)u32_2 + 4, u64 + 4,
			u8 + 5, u16 + 5, u32_1 + 5, (unsigned long*)u32_2 + 5, u64 + 5,
			(wchar_t*)&cc1, cc2,
			&p,
			ch,
			&n
		);
		CASE_CHECK_EQ(srt, c_validation_ret, "fwscanf, ret");

		CASE_CHECK_EQ(u8[0], c_validation_8[0], "fwscanf, u8[0]");
		CASE_CHECK_EQ(u8[1], c_validation_8[1], "fwscanf, u8[1]");
		CASE_CHECK_EQ(u8[2], c_validation_8[2], "fwscanf, u8[2]");
		CASE_CHECK_EQ(u8[3], c_validation_8[3], "fwscanf, u8[3]");
		CASE_CHECK_EQ(u8[4], c_validation_8[4], "fwscanf, u8[4]");
		CASE_CHECK_EQ(u8[5], c_validation_8[5], "fwscanf, u8[5]");

		CASE_CHECK_EQ(u16[0], c_validation_16[0], "fwscanf, u16[0]");
		CASE_CHECK_EQ(u16[1], c_validation_16[1], "fwscanf, u16[1]");
		CASE_CHECK_EQ(u16[2], c_validation_16[2], "fwscanf, u16[2]");
		CASE_CHECK_EQ(u16[3], c_validation_16[3], "fwscanf, u16[3]");
		CASE_CHECK_EQ(u16[4], c_validation_16[4], "fwscanf, u16[4]");
		CASE_CHECK_EQ(u16[5], c_validation_16[5], "fwscanf, u16[5]");

		CASE_CHECK_EQ(u32_1[0], c_validation_32_1[0], "fwscanf, u32_1[0]");
		CASE_CHECK_EQ(u32_1[1], c_validation_32_1[1], "fwscanf, u32_1[1]");
		CASE_CHECK_EQ(u32_1[2], c_validation_32_1[2], "fwscanf, u32_1[2]");
		CASE_CHECK_EQ(u32_1[3], c_validation_32_1[3], "fwscanf, u32_1[3]");
		CASE_CHECK_EQ(u32_1[4], c_validation_32_1[4], "fwscanf, u32_1[4]");
		CASE_CHECK_EQ(u32_1[5], c_validation_32_1[5], "fwscanf, u32_1[5]");

		CASE_CHECK_EQ(u32_2[0], c_validation_32_2[0], "fwscanf, u32_2[0]");
		CASE_CHECK_EQ(u32_2[1], c_validation_32_2[1], "fwscanf, u32_2[1]");
		CASE_CHECK_EQ(u32_2[2], c_validation_32_2[2], "fwscanf, u32_2[2]");
		CASE_CHECK_EQ(u32_2[3], c_validation_32_2[3], "fwscanf, u32_2[3]");
		CASE_CHECK_EQ(u32_2[4], c_validation_32_2[4], "fwscanf, u32_2[4]");
		CASE_CHECK_EQ(u32_2[5], c_validation_32_2[5], "fwscanf, u32_2[5]");

		CASE_CHECK_EQ(u64[0], c_validation_64[0], "fwscanf, u64[0]");
		CASE_CHECK_EQ(u64[1], c_validation_64[1], "fwscanf, u64[1]");
		CASE_CHECK_EQ(u64[2], c_validation_64[2], "fwscanf, u64[2]");
		CASE_CHECK_EQ(u64[3], c_validation_64[3], "fwscanf, u64[3]");
		CASE_CHECK_EQ(u64[4], c_validation_64[4], "fwscanf, u64[4]");
		CASE_CHECK_EQ(u64[5], c_validation_64[5], "fwscanf, u64[5]");

		CASE_CHECK_EQ(cc1, c_validation_cc1, "fwscanf, cc1");
		CASE_CHECK_EQ(wcscmp(cc2, c_validation_cc2) , 0, "fwscanf, cc2");

		CASE_CHECK_EQ(p, c_validation_p, "fwscanf, ptr");

		CASE_CHECK_EQ(wcslen(ch), wcslen(c_validation_ch), "fwscanf, string len");
		CASE_CHECK_EQ(wcscmp(ch, c_validation_ch), 0, "fwscanf, string");
		CASE_CHECK_EQ(n, c_validation_n, "fwscanf, n");
		fclose(pFile);
	}
}
void test_swscanf()
{
	constexpr uint8_t c_validation_8[6] = { 0x7f, 0x7f, 0x57, 0x7f, 0x27, 0x27 };
	constexpr uint16_t c_validation_16[6] = { 0x0190, 0x0190, 0x0100, 0x0190, 0x0400, 0x0400 };
	constexpr uint32_t c_validation_32_1[6] = { 0x000001f4, 0x000001f4, 0x00000140, 0x000001f4, 0x00000500, 0x00000500 };
	constexpr uint32_t c_validation_32_2[6] = { 0x00000294, 0x00000294, 0x000001b0, 0x00000294, 0x00000660, 0x00000660 };
	constexpr uint64_t c_validation_64[6] = { 0xffffffffffffe19f, 0xffffffffffffe19f, 0xfffffffffffff001, 0x000000000000270f, 0x0000000000009999, 0x0000000000009999 };
	wchar_t c_validation_cc1 = L' ';
	wchar_t c_validation_cc2[] = L"a bb";
	void* c_validation_p = (void*)0x0000000000001234llu;
	wchar_t c_validation_ch[512] = L"abcdefg";
	size_t c_validation_ret = 0x0000000000000023;
	int c_validation_n = 0x000000AE;

	uint8_t u8[6] = { 0 };
	uint16_t u16[6] = { 0 };
	uint32_t u32_1[6] = { 0 };
	uint32_t u32_2[6] = { 0 };
	uint64_t u64[6] = { 0 };
	int cc1 = 0;
	wchar_t cc2[5] = L"a bb";
	void* p = 0;
	wchar_t ch[512] = { 0 };
	int n = 0;
	const wchar_t c_validation[] =
		L"127 400 500 660 -7777 "
		L"127 400 500 660 -7777 "
		L"127 400 500 660 -7777 "
		L"0127 0400 0500 0660 09999 "
		L"0x127 0x400 0x500 0x660 0x9999 "
		L"0x127 0x400 0x500 0x660 0x9999 "
		L"a bb "
		L"0x1234 "
		L"%abcdefg ";
	size_t srt = swscanf(c_validation,
		L"%hhd %hd %d %ld %lld "
		L"%hhi %hi %i %li %lli "
		L"%hho %ho %o %lo %llo "
		L"%hhu %hu %u %lu %llu "
		L"%hhx %hx %x %lx %llx "
		L"%hhX %hX %X %lX %llX"
		L"%c%4c "
		L"%p"
		L"%% "
		L"%s%n",
		u8 + 0, u16 + 0, u32_1 + 0, (long*)u32_2 + 0, u64 + 0,
		u8 + 1, u16 + 1, u32_1 + 1, (long*)u32_2 + 1, u64 + 1,
		u8 + 2, u16 + 2, u32_1 + 2, (unsigned long*)u32_2 + 2, u64 + 2,
		u8 + 3, u16 + 3, u32_1 + 3, (unsigned long*)u32_2 + 3, u64 + 3,
		u8 + 4, u16 + 4, u32_1 + 4, (unsigned long*)u32_2 + 4, u64 + 4,
		u8 + 5, u16 + 5, u32_1 + 5, (unsigned long*)u32_2 + 5, u64 + 5,
		(char*)&cc1, (char*)&cc2,
		&p,
		ch,
		&n
	);
	CASE_CHECK_EQ(srt, c_validation_ret, "swscanf, ret");

	CASE_CHECK_EQ(u8[0], c_validation_8[0], "swscanf, u8[0]");
	CASE_CHECK_EQ(u8[1], c_validation_8[1], "swscanf, u8[1]");
	CASE_CHECK_EQ(u8[2], c_validation_8[2], "swscanf, u8[2]");
	CASE_CHECK_EQ(u8[3], c_validation_8[3], "swscanf, u8[3]");
	CASE_CHECK_EQ(u8[4], c_validation_8[4], "swscanf, u8[4]");
	CASE_CHECK_EQ(u8[5], c_validation_8[5], "swscanf, u8[5]");

	CASE_CHECK_EQ(u16[0], c_validation_16[0], "swscanf, u16[0]");
	CASE_CHECK_EQ(u16[1], c_validation_16[1], "swscanf, u16[1]");
	CASE_CHECK_EQ(u16[2], c_validation_16[2], "swscanf, u16[2]");
	CASE_CHECK_EQ(u16[3], c_validation_16[3], "swscanf, u16[3]");
	CASE_CHECK_EQ(u16[4], c_validation_16[4], "swscanf, u16[4]");
	CASE_CHECK_EQ(u16[5], c_validation_16[5], "swscanf, u16[5]");

	CASE_CHECK_EQ(u32_1[0], c_validation_32_1[0], "swscanf, u32_1[0]");
	CASE_CHECK_EQ(u32_1[1], c_validation_32_1[1], "swscanf, u32_1[1]");
	CASE_CHECK_EQ(u32_1[2], c_validation_32_1[2], "swscanf, u32_1[2]");
	CASE_CHECK_EQ(u32_1[3], c_validation_32_1[3], "swscanf, u32_1[3]");
	CASE_CHECK_EQ(u32_1[4], c_validation_32_1[4], "swscanf, u32_1[4]");
	CASE_CHECK_EQ(u32_1[5], c_validation_32_1[5], "swscanf, u32_1[5]");

	CASE_CHECK_EQ(u32_2[0], c_validation_32_2[0], "swscanf, u32_2[0]");
	CASE_CHECK_EQ(u32_2[1], c_validation_32_2[1], "swscanf, u32_2[1]");
	CASE_CHECK_EQ(u32_2[2], c_validation_32_2[2], "swscanf, u32_2[2]");
	CASE_CHECK_EQ(u32_2[3], c_validation_32_2[3], "swscanf, u32_2[3]");
	CASE_CHECK_EQ(u32_2[4], c_validation_32_2[4], "swscanf, u32_2[4]");
	CASE_CHECK_EQ(u32_2[5], c_validation_32_2[5], "swscanf, u32_2[5]");

	CASE_CHECK_EQ(u64[0], c_validation_64[0], "swscanf, u64[0]");
	CASE_CHECK_EQ(u64[1], c_validation_64[1], "swscanf, u64[1]");
	CASE_CHECK_EQ(u64[2], c_validation_64[2], "swscanf, u64[2]");
	CASE_CHECK_EQ(u64[3], c_validation_64[3], "swscanf, u64[3]");
	CASE_CHECK_EQ(u64[4], c_validation_64[4], "swscanf, u64[4]");
	CASE_CHECK_EQ(u64[5], c_validation_64[5], "swscanf, u64[5]");

	CASE_CHECK_EQ(cc1, c_validation_cc1, "swscanf, cc1");
	CASE_CHECK_EQ(wcscmp(cc2, c_validation_cc2), 0, "swscanf, cc2");

	CASE_CHECK_EQ(p, c_validation_p, "swscanf, ptr");

	CASE_CHECK_EQ(wcslen(ch), wcslen(c_validation_ch), "swscanf, string len");
	CASE_CHECK_EQ(wcscmp(ch, c_validation_ch), 0, "swscanf, string");
	CASE_CHECK_EQ(n, c_validation_n, "swscanf, n");
}

void test_wstring()
{
	printf("\ntest suite wstring:\n");
	test_wmemcpy();
	test_wmemmove();
	test_wmemcmp();
	test_wcscmp();
	test_wcslen();
	test_wcscpy();
	test_wcsncpy();
	test_wcscat();
	test_wcsncat();
	test_wcsncmp();
	test_wmemchr();
	test_wcschr();
	test_wcscspn();
	test_wcspbrk();
	test_wcsrchr();
	test_wcsspn();
	test_wcsstr();
	test_wmemset();
	test_wcstok();
	test_wcsxfrm();
	test_wcscoll();
	test_wcsftime();
	test_btowc_wctob();
	test_mbsinit();
	test_mbrlen();
	test_mbrtowc();
	test_mbsrtowcs();
	test_wcrtomb();
	test_wcsrtombs();
	testf_wprintf();
	test_swprintf();
	test_fwscanf();
	test_swscanf();
}