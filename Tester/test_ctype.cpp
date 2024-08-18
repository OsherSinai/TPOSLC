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
#include <include\ctype.h>
void test_isspace()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsSpaceSTD = (i == ' ') || (i == '\f') || (i =='\n') || (i == '\r') || (i == '\t') || (i == '\v');
		if ((isspace(i) != 0) != bIsSpaceSTD)
		{
			bSuccess = false;
			break;
		}
	}

	CASE_ASSERT_EQ(bSuccess, true, "isspace total char range check");
}
void test_isblank()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsBlankSTD = (i == ' ') || (i == '\t');
		if ((isblank(i) != 0) != bIsBlankSTD)
		{
			bSuccess = false;
			break;
		}
	}

	CASE_ASSERT_EQ(bSuccess, true, "isblank total char range check");
}

void test_iscntrl()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsCtrlSTD = (i < ' ') || (i == 127);
		if ((iscntrl(i) != 0) != bIsCtrlSTD)
		{
			bSuccess = false;
			break;
		}
	}

	CASE_ASSERT_EQ(bSuccess, true, "iscntrl total char range check");
}

void test_isalpha()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsAlphaSTD = (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z');
		if ((isalpha(i) != 0) != bIsAlphaSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isalpha total char range check");
}
void test_isprint()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsPrintSTD = (i >= ' ') && (i < 127);
		if ((isprint(i) != 0) != bIsPrintSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isprint total char range check");
}
void test_isalnum()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsAlnumSTD = (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9');
		if ((isalnum(i) != 0) != bIsAlnumSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isalnum total char range check");
}
void test_isdigit()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsDigitSTD = (i >= '0' && i <= '9');
		if ((isdigit(i) != 0) != bIsDigitSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isdigit total char range check");
}
void test_isgraph()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsGraphSTD = (i > ' ') && (i < 127);
		if ((isgraph(i) != 0) != bIsGraphSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isgraph total char range check");
}
void test_ispunct()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsPunctSTD = 
			((i >= 33) && (i <= 47)) || 
			((i >= 58) && (i <= 64)) || 
			((i >= 91) && (i <= 96)) || 
			((i >= 123) && (i <= 126));
		if ((ispunct(i) != 0) != bIsPunctSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "ispunct total char range check");
}
void test_isxdigit()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsXDigitSTD = (i >= '0' && i <= '9') || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F');
		if ((isxdigit(i) != 0) != bIsXDigitSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isxdigit total char range check");
}

void test_islower()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsLowerSTD = (i >= 'a' && i <= 'z');
		if ((islower(i) != 0) != bIsLowerSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "islower total char range check");
}
void test_isupper()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		bool bIsUpperSTD = (i >= 'A' && i <= 'Z');
		if ((isupper(i) != 0) != bIsUpperSTD)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "isupper total char range check");
}

void test_tolower()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;
		
		if (i >= 'A' && i <= 'Z')
			conv = conv - 'A' + 'a';

		if (tolower(i) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "tolower total char range check");
}
void test_toupper()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;

		if (i >= 'a' && i <= 'z')
			conv = conv - 'a' + 'A';

		if (toupper(i) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "toupper total char range check");
}

void test_ctype()
{
	printf("\ntest suite ctype:\n");
	test_isspace();
	test_isblank();
	test_iscntrl();
	test_isalpha();
	test_isprint();
	test_isalnum();
	test_isdigit();
	test_isgraph();
	test_ispunct();
	test_isxdigit();
	test_islower();
	test_isupper();
	test_tolower();
	test_toupper();
}