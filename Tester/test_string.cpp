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
#include <include/string.h>
#include <include/errno.h>


void test_memcpy()
{
	unsigned char BufferDst1[16] = { 0 };
	unsigned char BufferDst2[16] = { 0 };
	unsigned char BufferDst3[16] = { 0 };
	unsigned char BufferSrc[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	bool bEq;
	void* Ret = memcpy(BufferDst1, BufferSrc, sizeof(BufferSrc));
	CASE_CHECK_EQ(Ret, BufferDst1, "memcpy test 1, Return value");
	bEq = true;
	for (int i = 0; i < 16; i++)
	{
		if (BufferSrc[i] != BufferDst1[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memcpy test 1, Equality");
	Ret = memcpy(BufferDst2, BufferSrc, sizeof(BufferSrc) / 2);
	CASE_CHECK_EQ(Ret, BufferDst2, "memcpy test 2, Return value");
	bEq = true;
	for (int i = 0; i < sizeof(BufferSrc) / 2; i++)
	{
		if (BufferSrc[i] != BufferDst2[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memcpy test 2, Equality");
	Ret = memcpy(BufferDst3, BufferSrc, 0);
	CASE_CHECK_EQ(Ret, BufferDst3, "memcpy test 3, Return value");
	bEq = true;
	for (int i = 0; i < sizeof(BufferSrc) / 2; i++)
	{
		if (0 != BufferDst3[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memcpy test 3, Equality");
}
void test_memmove()
{
	unsigned char ControlResult1[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	unsigned char ControlResult2[16] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15 };
	unsigned char ControlResult3[16] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 12, 13, 14, 15, 13, 14, 15 };

	unsigned char BufferDst[16] = { 0 };
	unsigned char BufferSrc[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	bool bEq;
	void* Ret = memmove(BufferDst, BufferSrc, sizeof(BufferSrc));
	CASE_CHECK_EQ(Ret, BufferDst, "memmove test 1, Return value");
	bEq = true;
	for (int i = 0; i < 16; i++)
	{
		if (ControlResult1[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memmove test 1, Equality\t");
	Ret = memmove(BufferDst + 4, BufferDst, 8);
	CASE_CHECK_EQ(Ret, BufferDst + 4, "memmove test 2, Return value");
	bEq = true;
	for (int i = 0; i < 16; i++)
	{
		if (ControlResult2[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memmove test 2, Equality\t");
	Ret = memmove(BufferDst + 9, BufferDst + 12, 4);
	CASE_CHECK_EQ(Ret, BufferDst + 9, "memmove test 3, Return value");
	bEq = true;
	for (int i = 0; i < 16; i++)
	{
		if (ControlResult3[i] != BufferDst[i])
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "memmove test 3, Equality\t");
}

void test_memcmp()
{
	unsigned char ControlResult1[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	unsigned char ControlResult2[16] = { 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15 };

	int nRet;
	nRet = memcmp(ControlResult1, ControlResult1, 16);
	CASE_CHECK_EQ(nRet, 0, "memcmp test 1, Equality");
	nRet = memcmp(ControlResult1, ControlResult2, 16);
	CASE_CHECK_BT(nRet, 0, "memcmp test 2, Equality");
	nRet = memcmp(ControlResult2, ControlResult1, 16);
	CASE_CHECK_ST(nRet, 0, "memcmp test 3, Equality");
	nRet = memcmp(ControlResult2, ControlResult2, 4);
	CASE_CHECK_EQ(nRet, 0, "memcmp test 4, Equality");

}
void test_strcmp()
{
	CASE_CHECK_EQ(strcmp("abcd", "abcd"), 0, "strcmp test 1, equal");
	CASE_CHECK_ST(strcmp("abcd", "abcdc"), 0, "strcmp test 2, s2 bigger");
	CASE_CHECK_BT(strcmp("abcdc", "abcd"), 0, "strcmp test 3, s1 bigger");
	CASE_CHECK_ST(strcmp("abcc", "abcd"), 0, "strcmp test 4, s1 smaller");
	CASE_CHECK_BT(strcmp("abcd", "abcc"), 0, "strcmp test 5, s2 smaller");
}
void test_strlen()
{
	CASE_CHECK_EQ(strlen("abcd\n"), 5, "strlen test 1, \"abcd\" == 4");
	CASE_CHECK_EQ(strlen(""), 0, "strlen test 2, \"\" == 0");
	CASE_CHECK_EQ(strlen("145\0\\4444"), 3, "strlen test 3, \"145\\0\\4444\" == 3");
}
void test_strcpy()
{
	char Buffer[8] = { 0 };
	char Src[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	char ControlResult1[4] = { 'a', 'b', 'c', 0 };
	char ControlResult2[8] = { 'a', 'b', 'c', 0, 'e', 'f', 'g', 0 };
	char* ret;
	ret = strcpy(Buffer, Src);
	CASE_CHECK_EQ(Buffer, ret, "strcpy test 1 (return)");
	CASE_CHECK_EQ(memcmp(Buffer, Src, 8), 0, "strcpy test 2 (memory cmp)");
	ret = strcpy(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "strcpy test 3 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 3, "strcpy test 4 (strlen == 3)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult2, 8), 0, "strcpy test 5 (memory cmp)");
}
void test_strncpy()
{
	char Buffer[8] = { 0 };
	char Src[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	char ControlResult1[4] = { 'a', 'b', 'c', 0 };
	char ControlResult2[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 0 };
	char ControlResult3[8] = { 'a', 'b', 'c', 0, 0, 0, 'g', 0};
	char* ret;
	ret = strncpy(Buffer, Src, 8);
	CASE_CHECK_EQ(Buffer, ret, "strncpy test 1 (return)");
	CASE_CHECK_EQ(memcmp(Buffer, Src, 8), 0, "strncpy test 2 (memory cmp)");
	ret = strncpy(Buffer, ControlResult1, 3);
	CASE_CHECK_EQ(Buffer, ret, "strncpy test 3 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 7, "strncpy test 4 (strlen == 7)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult2, 8), 0, "strncpy test 5 (memory cmp)");
	ret = strncpy(Buffer, ControlResult1, 6);
	CASE_CHECK_EQ(Buffer, ret, "strncpy test 6 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 3, "strncpy test 7 (strlen == 3)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult3, 8), 0, "strncpy test 8 (memory cmp)");
}
void test_strcat()
{
	char Buffer[8] = { 0 };
	char ControlResult1[8] = { 'a', 'b', 'c', 0, 0, 0, 0, 0 };
	char ControlResult2[8] = { 'a', 'b', 'c', 'a', 'b', 'c', 0, 0};
	char* ret;
	ret = strcat(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "strcat test 1 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 3, "strcat test 2 (strlen = 3)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult1, 8), 0, "strcat test 3 (memory cmp)");

	ret = strcat(Buffer, ControlResult1);
	CASE_CHECK_EQ(Buffer, ret, "strcat test 4 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 6, "strcat test 5 (strlen = 6)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult2, 8), 0, "strcat test 6 (memory cmp)");

}
void test_strncat()
{
	char Buffer[8] = { 0 };
	char ControlResult1[8] = { 'a', 'b', 'c', 0, 0, 0, 0, 0 };
	char ControlResult2[8] = { 'a', 'b', 'c', 'a', 'b', 0, 0, 0 };
	char* ret;
	ret = strncat(Buffer, ControlResult1, 5);
	CASE_CHECK_EQ(Buffer, ret, "strncat test 1 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 3, "strncat test 2 (strlen = 3)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult1, 8), 0, "strncat test 3 (memory cmp)");

	ret = strncat(Buffer, ControlResult1, 2);
	CASE_CHECK_EQ(Buffer, ret, "strncat test 4 (return)");
	CASE_CHECK_EQ(strlen(Buffer), 5, "strncat test 5 (strlen = 5)");
	CASE_CHECK_EQ(memcmp(Buffer, ControlResult2, 8), 0, "strncat test 6 (memory cmp)");

}

void test_strncmp()
{
	char ControlResult1[8] = { 'a', 'b', 'c', 0, 0, 0, 0, 0 };
	char ControlResult2[8] = { 'a', 'b', 'c', 'a', 'b', 0, 0, 0 };
	char ControlResult3[8] = { 'a', 'b', 'd', 0, 0, 0, 0, 0 };
	CASE_CHECK_EQ(strncmp(ControlResult1, ControlResult1, 3), 0, "strncmp test 1, equal");
	CASE_CHECK_EQ(strncmp(ControlResult1, ControlResult2, 3), 0, "strncmp test 2, equal");
	CASE_CHECK_EQ(strncmp(ControlResult2, ControlResult1, 3), 0, "strncmp test 3, s1 bigger");
	CASE_CHECK_ST(strncmp(ControlResult1, ControlResult2, 4), 0, "strncmp test 4, s1 smaller");
	CASE_CHECK_BT(strncmp(ControlResult2, ControlResult1, 4), 0, "strncmp test 5, s2 smaller");
	CASE_CHECK_ST(strncmp(ControlResult1, ControlResult3, 4), 0, "strncmp test 6, s1 smaller");
	CASE_CHECK_BT(strncmp(ControlResult3, ControlResult1, 4), 0, "strncmp test 7, s2 smaller");
}
void test_memchr()
{
	unsigned char  uch[255];
	for (int i = 0; i < 255; i++)
		uch[i] = i;
	bool bSuccess = true;
	for (int i = 0; i < 255; i++)
	{
		unsigned char* p = (unsigned char*)memchr(uch, i, sizeof(uch));
		if (p != (uch + i))
		{
			bSuccess = false;
			break;
		}
	}
	if (bSuccess)
	{
		unsigned char* p = (unsigned char*)memchr(uch, 255, sizeof(uch));
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "memchr test, uint8 range check");
}
void test_strchr()
{
	char uch[255];
	for (int i = 1; i < 255; i++)
		uch[i-1] = i;
	uch[254] = 0;
	bool bSuccess = true;
	for (int i = 1; i < 255; i++)
	{
		char* p = strchr(uch, i);
		if (p != (uch + (i - 1)))
		{
			bSuccess = false;
			break;
		}
	}
	if (bSuccess)
	{
		char* p = strchr(uch, 255);
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "strchr test, uint8 range check");
}
void test_strcspn()
{
	CASE_CHECK_EQ(strcspn("", "abcdefg"), 0, "strcspn test 1, len = 0");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "hij"), 23, "strcspn test 2, len = 23");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "g"), 17, "strcspn test 3, len = 17");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "fg"), 14, "strcspn test 4, len = 14");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "efg"), 10, "strcspn test 5, len = 10");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "defg"), 6, "strcspn test 6, len = 6");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "cdefg"), 5, "strcspn test 7, len = 5");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "bcdefg"), 3, "strcspn test 8, len = 3");
	CASE_CHECK_EQ(strcspn("aaabbcddddeeeefffgggggg", "abcdefg"), 0, "strcspn test 9, len = 0");
}
void test_strpbrk()
{
	char str[2];
	char span[2];
	str[1] = 0;
	span[1] = 0;
	bool bSuccess = true;
	for (int i = 1; i < 255; i++)
	{
		str[0] = i;
		span[0] = i;
		char* p = strpbrk(str, span);
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
		char* p = strpbrk(str, span);
		if (p != nullptr)
		{
			bSuccess = false;
		}
	}
	CASE_CHECK_EQ(bSuccess, true, "strchr test, uint8 range check");
}
void test_strrchr()
{
	char ControlResult1[8] = "aaa";
	char ControlResult2[8] = "bbaaa";
	CASE_CHECK_EQ(strrchr(ControlResult1, '\0'), ControlResult1 + 3, "strrchr test 1, null terminator");
	CASE_CHECK_EQ(strrchr(ControlResult1, 'a'), ControlResult1 + 2, "strrchr test 2, last");
	CASE_CHECK_EQ(strrchr(ControlResult1, 'b'), 0, "strrchr test 3, not found");
	CASE_CHECK_EQ(strrchr(ControlResult2, 'b'), ControlResult2 + 1, "strrchr test 4, last of sequence 1");
	CASE_CHECK_EQ(strrchr(ControlResult2, 'a'), ControlResult2 + 4, "strrchr test 5, last of sequence 2");

}
void test_strspn()
{
	CASE_CHECK_EQ(strspn("", "abcdefg"), 0, "strspn test 1, len = 0");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "abcdefg"), 23, "strspn test 2, len = 23");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "abcdef"), 17, "strspn test 3, len = 17");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "abcde"), 14, "strspn test 4, len = 14");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "abcd"), 10, "strspn test 5, len = 10");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "abc"), 6, "strspn test 6, len = 6");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "ab"), 5, "strspn test 7, len = 5");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "a"), 3, "strspn test 8, len = 3");
	CASE_CHECK_EQ(strspn("aaabbcddddeeeefffgggggg", "hijk"), 0, "strspn test 9, len = 0");
}
void test_strstr()
{
	char ControlResult1[8] = "aabbaaa";
	char ControlResult2[8] = "aaa";
	char ControlResult3[8] = "aa";
	char ControlResult4[8] = "bb";
	char ControlResult5[8] = "cc";
	CASE_CHECK_EQ(strstr(ControlResult1, ControlResult5), 0, "strstr test 1");
	CASE_CHECK_EQ(strstr(ControlResult1, ControlResult2), ControlResult1 + 4, "strstr test 2");
	CASE_CHECK_EQ(strstr(ControlResult1, ControlResult3), ControlResult1, "strstr test 3");
	CASE_CHECK_EQ(strstr(ControlResult1, ControlResult4), ControlResult1 + 2, "strstr test 4");
}
void test_memset()
{
	unsigned char ch[256];
	void* pRet;
	bool bSuccess = true;

	pRet = memset(ch, 0, sizeof(ch));
	for (int i = 0; i < 256; i++)
	{
		if (ch[i] != 0)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_CHECK_EQ(pRet, ch, "memset test 1, return");
	CASE_CHECK_EQ(bSuccess, true, "memset test 2, set to 0x00");

	bSuccess = true;
	pRet = memset(ch, 0xF0, sizeof(ch));
	for (int i = 0; i < 256; i++)
	{
		if (ch[i] != 0xF0)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_CHECK_EQ(pRet, ch, "memset test 3, return");
	CASE_CHECK_EQ(bSuccess, true, "memset test 4, set to 0xF0");
}
void test_strerror()
{
	errno = 0;
	CASE_CHECK_NE(strerror(0)				, 0, "strerror test 1, SUCCESS");
	CASE_CHECK_NE(strerror(EPERM)			, 0, "strerror test 2, EPERM");
	CASE_CHECK_NE(strerror(ENOENT)			, 0, "strerror test 3, ENOENT");
	CASE_CHECK_NE(strerror(ESRCH)			, 0, "strerror test 4, ESRCH");
	CASE_CHECK_NE(strerror(EINTR)			, 0, "strerror test 5, EINTR");
	CASE_CHECK_NE(strerror(EIO)				, 0, "strerror test 6, EIO");
	CASE_CHECK_NE(strerror(ENXIO)			, 0, "strerror test 7, ENXIO");
	CASE_CHECK_NE(strerror(E2BIG)			, 0, "strerror test 8, E2BIG");
	CASE_CHECK_NE(strerror(ENOEXEC)			, 0, "strerror test 9, ENOEXEC");
	CASE_CHECK_NE(strerror(EBADF)			, 0, "strerror test 10, EBADF");
	CASE_CHECK_NE(strerror(ECHILD)			, 0, "strerror test 11, ECHILD");
	CASE_CHECK_NE(strerror(EAGAIN)			, 0, "strerror test 12, EAGAIN");
	CASE_CHECK_NE(strerror(ENOMEM)			, 0, "strerror test 13, ENOMEM");
	CASE_CHECK_NE(strerror(EACCES)			, 0, "strerror test 14, EACCES");
	CASE_CHECK_NE(strerror(EFAULT)			, 0, "strerror test 15, EFAULT");
	CASE_CHECK_NE(strerror(ENOTBLK)			, 0, "strerror test 16, ENOTBLK");
	CASE_CHECK_NE(strerror(EBUSY)			, 0, "strerror test 17, EBUSY");
	CASE_CHECK_NE(strerror(EEXIST)			, 0, "strerror test 18, EEXIST");
	CASE_CHECK_NE(strerror(EXDEV)			, 0, "strerror test 19, EXDEV");
	CASE_CHECK_NE(strerror(ENODEV)			, 0, "strerror test 20, ENODEV");
	CASE_CHECK_NE(strerror(ENOTDIR)			, 0, "strerror test 21, ENOTDIR");
	CASE_CHECK_NE(strerror(EISDIR)			, 0, "strerror test 22, EISDIR");
	CASE_CHECK_NE(strerror(EINVAL)			, 0, "strerror test 23, EINVAL");
	CASE_CHECK_NE(strerror(ENFILE)			, 0, "strerror test 24, ENFILE");
	CASE_CHECK_NE(strerror(EMFILE)			, 0, "strerror test 25, EMFILE");
	CASE_CHECK_NE(strerror(ENOTTY)			, 0, "strerror test 26, ENOTTY");
	CASE_CHECK_NE(strerror(ETXTBSY)			, 0, "strerror test 27, ETXTBSY");
	CASE_CHECK_NE(strerror(EFBIG)			, 0, "strerror test 28, EFBIG");
	CASE_CHECK_NE(strerror(ENOSPC)			, 0, "strerror test 29, ENOSPC");
	CASE_CHECK_NE(strerror(ESPIPE)			, 0, "strerror test 30, ESPIPE");
	CASE_CHECK_NE(strerror(EROFS)			, 0, "strerror test 31, EROFS");
	CASE_CHECK_NE(strerror(EMLINK)			, 0, "strerror test 32, EMLINK");
	CASE_CHECK_NE(strerror(EPIPE)			, 0, "strerror test 33, EPIPE");
	CASE_CHECK_NE(strerror(EDOM)			, 0, "strerror test 34, EDOM");
	CASE_CHECK_NE(strerror(ERANGE)			, 0, "strerror test 35, ERANGE");
	CASE_CHECK_NE(strerror(EDEADLK)			, 0, "strerror test 36, EDEADLK");
	CASE_CHECK_NE(strerror(ENAMETOOLONG)	, 0, "strerror test 37, ENAMETOOLONG");
	CASE_CHECK_NE(strerror(ENOLCK)			, 0, "strerror test 38, ENOLCK");
	CASE_CHECK_NE(strerror(ENOSYS)			, 0, "strerror test 39, ENOSYS");
	CASE_CHECK_NE(strerror(ENOTEMPTY)		, 0, "strerror test 40, ENOTEMPTY");
	CASE_CHECK_NE(strerror(ELOOP)			, 0, "strerror test 41, ELOOP");
	CASE_CHECK_NE(strerror(ENOMSG)			, 0, "strerror test 42, ENOMSG");
	CASE_CHECK_NE(strerror(EIDRM)			, 0, "strerror test 43, EIDRM");
	CASE_CHECK_NE(strerror(ECHRNG)			, 0, "strerror test 44, ECHRNG");
	CASE_CHECK_NE(strerror(EL2NSYNC)		, 0, "strerror test 45, EL2NSYNC");
	CASE_CHECK_NE(strerror(EL3HLT)			, 0, "strerror test 46, EL3HLT");
	CASE_CHECK_NE(strerror(EL3RST)			, 0, "strerror test 47, EL3RST");
	CASE_CHECK_NE(strerror(ELNRNG)			, 0, "strerror test 48, ELNRNG");
	CASE_CHECK_NE(strerror(EUNATCH)			, 0, "strerror test 49, EUNATCH");
	CASE_CHECK_NE(strerror(ENOCSI)			, 0, "strerror test 50, ENOCSI");
	CASE_CHECK_NE(strerror(EL2HLT)			, 0, "strerror test 51, EL2HLT");
	CASE_CHECK_NE(strerror(EBADE)			, 0, "strerror test 52, EBADE");
	CASE_CHECK_NE(strerror(EBADR)			, 0, "strerror test 53, EBADR");
	CASE_CHECK_NE(strerror(EXFULL)			, 0, "strerror test 54, EXFULL");
	CASE_CHECK_NE(strerror(ENOANO)			, 0, "strerror test 55, ENOANO");
	CASE_CHECK_NE(strerror(EBADRQC)			, 0, "strerror test 56, EBADRQC");
	CASE_CHECK_NE(strerror(EBADSLT)			, 0, "strerror test 57, EBADSLT");
	CASE_CHECK_NE(strerror(EBFONT)			, 0, "strerror test 58, EBFONT");
	CASE_CHECK_NE(strerror(ENOSTR)			, 0, "strerror test 59, ENOSTR");
	CASE_CHECK_NE(strerror(ENODATA)			, 0, "strerror test 60, ENODATA");
	CASE_CHECK_NE(strerror(ETIME)			, 0, "strerror test 61, ETIME");
	CASE_CHECK_NE(strerror(ENOSR)			, 0, "strerror test 62, ENOSR");
	CASE_CHECK_NE(strerror(ENONET)			, 0, "strerror test 63, ENONET");
	CASE_CHECK_NE(strerror(ENOPKG)			, 0, "strerror test 64, ENOPKG");
	CASE_CHECK_NE(strerror(EREMOTE)			, 0, "strerror test 65, EREMOTE");
	CASE_CHECK_NE(strerror(ENOLINK)			, 0, "strerror test 66, ENOLINK");
	CASE_CHECK_NE(strerror(EADV)			, 0, "strerror test 67, EADV");
	CASE_CHECK_NE(strerror(ESRMNT)			, 0, "strerror test 68, ESRMNT");
	CASE_CHECK_NE(strerror(ECOMM)			, 0, "strerror test 69, ECOMM");
	CASE_CHECK_NE(strerror(EPROTO)			, 0, "strerror test 70, EPROTO");
	CASE_CHECK_NE(strerror(EMULTIHOP)		, 0, "strerror test 71, EMULTIHOP");
	CASE_CHECK_NE(strerror(EDOTDOT)			, 0, "strerror test 72, EDOTDOT");
	CASE_CHECK_NE(strerror(EBADMSG)			, 0, "strerror test 73, EBADMSG");
	CASE_CHECK_NE(strerror(EOVERFLOW)		, 0, "strerror test 74, EOVERFLOW");
	CASE_CHECK_NE(strerror(ENOTUNIQ)		, 0, "strerror test 75, ENOTUNIQ");
	CASE_CHECK_NE(strerror(EBADFD)			, 0, "strerror test 76, EBADFD");
	CASE_CHECK_NE(strerror(EREMCHG)			, 0, "strerror test 77, EREMCHG");
	CASE_CHECK_NE(strerror(ELIBACC)			, 0, "strerror test 78, ELIBACC");
	CASE_CHECK_NE(strerror(ELIBBAD)			, 0, "strerror test 79, ELIBBAD");
	CASE_CHECK_NE(strerror(ELIBSCN)			, 0, "strerror test 80, ELIBSCN");
	CASE_CHECK_NE(strerror(ELIBMAX)			, 0, "strerror test 81, ELIBMAX");
	CASE_CHECK_NE(strerror(ELIBEXEC)		, 0, "strerror test 82, ELIBEXEC");
	CASE_CHECK_NE(strerror(EILSEQ)			, 0, "strerror test 83, EILSEQ");
	CASE_CHECK_NE(strerror(ERESTART)		, 0, "strerror test 84, ERESTART");
	CASE_CHECK_NE(strerror(ESTRPIPE)		, 0, "strerror test 85, ESTRPIPE");
	CASE_CHECK_NE(strerror(EUSERS)			, 0, "strerror test 86, EUSERS");
	CASE_CHECK_NE(strerror(ENOTSOCK)		, 0, "strerror test 87, ENOTSOCK");
	CASE_CHECK_NE(strerror(EDESTADDRREQ)	, 0, "strerror test 88, EDESTADDRREQ");
	CASE_CHECK_NE(strerror(EMSGSIZE)		, 0, "strerror test 89, EMSGSIZE");
	CASE_CHECK_NE(strerror(EPROTOTYPE)		, 0, "strerror test 90, EPROTOTYPE");
	CASE_CHECK_NE(strerror(ENOPROTOOPT)		, 0, "strerror test 91, ENOPROTOOPT");
	CASE_CHECK_NE(strerror(EPROTONOSUPPORT)	, 0, "strerror test 92, EPROTONOSUPPORT");
	CASE_CHECK_NE(strerror(ESOCKTNOSUPPORT)	, 0, "strerror test 93, ESOCKTNOSUPPORT");
	CASE_CHECK_NE(strerror(EOPNOTSUPP)		, 0, "strerror test 94, EOPNOTSUPP");
	CASE_CHECK_NE(strerror(EPFNOSUPPORT)	, 0, "strerror test 95, EPFNOSUPPORT");
	CASE_CHECK_NE(strerror(EAFNOSUPPORT)	, 0, "strerror test 96, EAFNOSUPPORT");
	CASE_CHECK_NE(strerror(EADDRINUSE)		, 0, "strerror test 97, EADDRINUSE");
	CASE_CHECK_NE(strerror(EADDRNOTAVAIL)	, 0, "strerror test 98, EADDRNOTAVAIL");
	CASE_CHECK_NE(strerror(ENETDOWN)		, 0, "strerror test 99, ENETDOWN");
	CASE_CHECK_NE(strerror(ENETUNREACH)		, 0, "strerror test 100, ENETUNREACH");
	CASE_CHECK_NE(strerror(ENETRESET)		, 0, "strerror test 101, ENETRESET");
	CASE_CHECK_NE(strerror(ECONNABORTED)	, 0, "strerror test 102, ECONNABORTED");
	CASE_CHECK_NE(strerror(ECONNRESET)		, 0, "strerror test 103, ECONNRESET");
	CASE_CHECK_NE(strerror(ENOBUFS)			, 0, "strerror test 104, ENOBUFS");
	CASE_CHECK_NE(strerror(EISCONN)			, 0, "strerror test 105, EISCONN");
	CASE_CHECK_NE(strerror(ENOTCONN)		, 0, "strerror test 106, ENOTCONN");
	CASE_CHECK_NE(strerror(ESHUTDOWN)		, 0, "strerror test 107, ESHUTDOWN");
	CASE_CHECK_NE(strerror(ETOOMANYREFS)	, 0, "strerror test 108, ETOOMANYREFS");
	CASE_CHECK_NE(strerror(ETIMEDOUT)		, 0, "strerror test 109, ETIMEDOUT");
	CASE_CHECK_NE(strerror(ECONNREFUSED)	, 0, "strerror test 110, ECONNREFUSED");
	CASE_CHECK_NE(strerror(EHOSTDOWN)		, 0, "strerror test 111, EHOSTDOWN");
	CASE_CHECK_NE(strerror(EHOSTUNREACH)	, 0, "strerror test 112, EHOSTUNREACH");
	CASE_CHECK_NE(strerror(EALREADY)		, 0, "strerror test 113, EALREADY");
	CASE_CHECK_NE(strerror(EINPROGRESS)		, 0, "strerror test 114, EINPROGRESS");
	CASE_CHECK_NE(strerror(ESTALE)			, 0, "strerror test 115, ESTALE");
	CASE_CHECK_NE(strerror(EUCLEAN)			, 0, "strerror test 116, EUCLEAN");
	CASE_CHECK_NE(strerror(ENOTNAM)			, 0, "strerror test 117, ENOTNAM");
	CASE_CHECK_NE(strerror(ENAVAIL)			, 0, "strerror test 118, ENAVAIL");
	CASE_CHECK_NE(strerror(EISNAM)			, 0, "strerror test 119, EISNAM");
	CASE_CHECK_NE(strerror(EREMOTEIO)		, 0, "strerror test 120, EREMOTEIO");
	CASE_CHECK_NE(strerror(EDQUOT)			, 0, "strerror test 121, EDQUOT");
	CASE_CHECK_NE(strerror(ENOMEDIUM)		, 0, "strerror test 122, ENOMEDIUM");
	CASE_CHECK_NE(strerror(EMEDIUMTYPE)		, 0, "strerror test 123, EMEDIUMTYPE");
	CASE_CHECK_NE(strerror(ECANCELED)		, 0, "strerror test 124, ECANCELED");
	CASE_CHECK_NE(strerror(ENOKEY)			, 0, "strerror test 125, ENOKEY");
	CASE_CHECK_NE(strerror(EKEYEXPIRED)		, 0, "strerror test 126, EKEYEXPIRED");
	CASE_CHECK_NE(strerror(EKEYREVOKED)		, 0, "strerror test 127, EKEYREVOKED");
	CASE_CHECK_NE(strerror(EKEYREJECTED)	, 0, "strerror test 128, EKEYREJECTED");
	errno = 0;
}
void test_strtok()
{
	// example taken from c17 proposal
	char str[] = "?a???b,,,#c";
	char* t;
	t = strtok(str, "?"); // t points to the token "a"
	CASE_CHECK_EQ(strcmp(t, "a"), 0, "strtok test 1, part 1");
	t = strtok(NULL, ","); // t points to the token "??b"
	CASE_CHECK_EQ(strcmp(t, "??b"), 0, "strtok test 2, part 2");
	t = strtok(NULL, "#,"); // t points to the token "c"
	CASE_CHECK_EQ(strcmp(t, "c"), 0, "strtok test 3, part 3");
	t = strtok(NULL, "?"); // t is a null pointer
	CASE_CHECK_EQ(t, 0, "strtok test 4, end");
}
void test_strxfrm()
{
	char Dst[16] = {0};
	char Src[16] = "abcdef";
	size_t NeededSize = strxfrm(0, Src, 0);
	CASE_CHECK_EQ(NeededSize, 6, "strxfrm test 1, needed size");
	NeededSize = strxfrm(Dst, Src, NeededSize);
	CASE_CHECK_EQ(NeededSize, 6, "strxfrm test 2, needed size");
	CASE_CHECK_EQ(strcmp(Dst, Src), 0, "strxfrm test 3, string cmp");
}
void test_strcoll()
{
	CASE_CHECK_EQ(strcoll("abcd", "abcd"), 0, "strcoll test 1, equal");
	CASE_CHECK_ST(strcoll("abcd", "abcdc"), 0, "strcoll test 2, s2 bigger");
	CASE_CHECK_BT(strcoll("abcdc", "abcd"), 0, "strcoll test 3, s1 bigger");
	CASE_CHECK_ST(strcoll("abcc", "abcd"), 0, "strcoll test 4, s1 smaller");
	CASE_CHECK_BT(strcoll("abcd", "abcc"), 0, "strcoll test 5, s2 smaller");
}

void test_string()
{
	printf("\ntest suite string:\n");
	test_memcpy();
	test_memmove();
	test_memcmp();
	test_strcmp();
	test_strlen();
	test_strcpy();
	test_strncpy();
	test_strcat();
	test_strncat();
	test_strncmp();
	test_memchr();
	test_strchr();
	test_strcspn();
	test_strpbrk();
	test_strrchr();
	test_strspn();
	test_strstr();
	test_memset();
	test_strerror();
	test_strtok();
	test_strxfrm();
	test_strcoll();
}