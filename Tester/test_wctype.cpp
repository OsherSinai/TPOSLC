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
#include <include/ctype.h>
#include <include/wctype.h>

void test_iswalnum()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswalnum((wint_t)i) != isalnum((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswalnum, range check");
}
void test_iswalpha()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswalpha((wint_t)i) != isalpha((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswalpha, range check");
}
void test_iswblank()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswblank((wint_t)i) != isblank((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswblank, range check");
}
void test_iswcntrl()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswcntrl((wint_t)i) != iscntrl((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswcntrl, range check");
}
void test_iswdigit()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswdigit((wint_t)i) != isdigit((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswdigit, range check");
}
void test_iswgraph()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswgraph((wint_t)i) != isgraph((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswgraph, range check");
}
void test_iswlower()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswlower((wint_t)i) != islower((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswlower, range check");
}
void test_iswprint()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswprint((wint_t)i) != isprint((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswprint, range check");
}
void test_iswpunct()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswpunct((wint_t)i) != ispunct((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswpunct, range check");
}
void test_iswspace()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswspace((wint_t)i) != isspace((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswspace, range check");
}
void test_iswupper()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswupper((wint_t)i) != isupper((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswupper, range check");
}
void test_iswxdigit()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswxdigit((wint_t)i) != isxdigit((int)i))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswxdigit, range check");
}

void test_wctype_func()
{
	CASE_CHECK_EQ(wctype("alnum"), 1, "wctype alnum");
	CASE_CHECK_EQ(wctype("alpha"), 2, "wctype alpha");
	CASE_CHECK_EQ(wctype("blank"), 3, "wctype blank");
	CASE_CHECK_EQ(wctype("cntrl"), 4, "wctype cntrl");
	CASE_CHECK_EQ(wctype("digit"), 5, "wctype digit");
	CASE_CHECK_EQ(wctype("graph"), 6, "wctype graph");
	CASE_CHECK_EQ(wctype("lower"), 7, "wctype lower");
	CASE_CHECK_EQ(wctype("print"), 8, "wctype print");
	CASE_CHECK_EQ(wctype("punct"), 9, "wctype punct");
	CASE_CHECK_EQ(wctype("space"), 10, "wctype space");
	CASE_CHECK_EQ(wctype("upper"), 11, "wctype upper");
	CASE_CHECK_EQ(wctype("xdigit"), 12, "wctype xdigit");

}
void test_iswctype()
{
	bool bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswalnum((wint_t)i) != iswctype((wint_t)i, wctype("alnum")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswalnum, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswalpha((wint_t)i) != iswctype((wint_t)i, wctype("alpha")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswalpha, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswblank((wint_t)i) != iswctype((wint_t)i, wctype("blank")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswblank, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswcntrl((wint_t)i) != iswctype((wint_t)i, wctype("cntrl")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswcntrl, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswdigit((wint_t)i) != iswctype((wint_t)i, wctype("digit")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswdigit, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswgraph((wint_t)i) != iswctype((wint_t)i, wctype("graph")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswgraph, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswlower((wint_t)i) != iswctype((wint_t)i, wctype("lower")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswlower, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswprint((wint_t)i) != iswctype((wint_t)i, wctype("print")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswprint, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswpunct((wint_t)i) != iswctype((wint_t)i, wctype("punct")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswpunct, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswspace((wint_t)i) != iswctype((wint_t)i, wctype("space")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswspace, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswupper((wint_t)i) != iswctype((wint_t)i, wctype("upper")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswupper, range check");
	bEq = true;
	for (size_t i = 0; i < 256; i++)
	{
		if (iswxdigit((wint_t)i) != iswctype((wint_t)i, wctype("xdigit")))
		{
			bEq = false;
			break;
		}
	}
	CASE_CHECK_EQ(bEq, true, "iswctype, iswxdigit, range check");
}

void test_towlower()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;

		if (i >= L'A' && i <= L'Z')
			conv = conv - L'A' + L'a';

		if (towlower(i) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "towlower total char range check");
}
void test_towupper()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;

		if (i >= L'a' && i <= L'z')
			conv = conv - L'a' + L'A';

		if (towupper(i) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "towupper total char range check");
}

void test_wctrans()
{
	CASE_ASSERT_EQ(wctrans("tolower"), 0, "wctrans, tolower");
	CASE_ASSERT_EQ(wctrans("toupper"), 1, "wctrans, toupper");
}

void test_towctrans()
{
	bool bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;

		if (i >= L'A' && i <= L'Z')
			conv = conv - L'A' + L'a';

		if (towctrans(i, wctrans("tolower")) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "towctrans, tolower total char range check");
	bSuccess = true;
	for (int i = 0; i < 256; i++)
	{
		int conv = i;

		if (i >= L'a' && i <= L'z')
			conv = conv - L'a' + L'A';

		if (towctrans(i, wctrans("toupper")) != conv)
		{
			bSuccess = false;
			break;
		}
	}
	CASE_ASSERT_EQ(bSuccess, true, "towctrans, toupper total char range check");
}

void test_wctype()
{
	printf("\ntest suite wctype:\n");

	test_iswalnum();
	test_iswalpha();
	test_iswblank();
	test_iswcntrl();
	test_iswdigit();
	test_iswgraph();
	test_iswlower();
	test_iswprint();
	test_iswpunct();
	test_iswspace();
	test_iswupper();
	test_iswxdigit();

	test_wctype_func();
	test_iswctype();

	test_towlower();
	test_towupper();

	test_wctrans();
	test_towctrans();
}