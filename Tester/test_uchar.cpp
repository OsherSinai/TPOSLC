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
#include <include/uchar.h>
#include <include/string.h>

void test_mbrtoc16()
{
    mbstate_t state = {0};
    const char8_t str8[11] = u8"zß水🍌";
    char16_t converted[11] = {0};

    const char8_t* p = str8;
    const char8_t* end = str8 + sizeof(str8);
    char16_t* pcnv = converted;
    size_t rc = 0;
    
    rc = mbrtoc16(pcnv, (char*)p, end - p, &state);
    while (rc)
    {
        if (rc == (size_t)-1 || rc == (size_t)-2)
            break;
        else
        {
            if(rc != (size_t)-1)
                p += rc;
            pcnv += 1;
        };
        rc = mbrtoc16(pcnv, (char*)p, end - p, &state);
    } 

    size_t TotalSizeOfConv = (size_t)(pcnv - converted + 1);
    uint16_t ValidationData[6] = { 0x7a, 0xdf, 0x6c34, 0xd83c, 0xdf4c, 0 };
    CASE_CHECK_EQ(TotalSizeOfConv, 6, "mbrtoc16, Conversion length");
    CASE_CHECK_EQ(memcmp(ValidationData, converted, sizeof(ValidationData)), 0, "mbrtoc16, Conversion content");
    return;
}

void test_mbrtoc32()
{
    mbstate_t state = { 0 };
    const char8_t str8[11] = u8"zß水🍌";
    char32_t converted[11] = { 0 };

    const char8_t* p = str8;
    const char8_t* end = str8 + sizeof(str8);
    char32_t* pcnv = converted;
    size_t rc = 0;

    rc = mbrtoc32(pcnv, (char*)p, end - p, &state);
    while (rc)
    {
        if (rc == (size_t)-1 || rc == (size_t)-2)
            break;
        else
        {
            if (rc != (size_t)-1)
                p += rc;
            pcnv += 1;
        };
        rc = mbrtoc32(pcnv, (char*)p, end - p, &state);
    }

    size_t TotalSizeOfConv = (size_t)(pcnv - converted + 1);
    uint32_t ValidationData[5] = { 0x7A, 0xDF, 0x6C34, 0x1F34C, 0 };
    CASE_CHECK_EQ(TotalSizeOfConv, 5, "mbrtoc32, Conversion length");
    CASE_CHECK_EQ(memcmp(ValidationData, converted, sizeof(ValidationData)), 0, "mbrtoc32, Conversion content");
    return;
}

void test_c16rtomb()
{
    mbstate_t state = { 0 };
    const char16_t str16[] = u"zß水🍌";
    constexpr size_t orglen = sizeof(str16) / sizeof(str16[0]);
    char8_t converted[11] = { 0 };

    const char16_t* p = str16;
    char8_t* pcnv = converted;
    size_t rc = 0;

    for (size_t i = 0; i < orglen; i++)
    {
        rc = c16rtomb((char*)pcnv, p[i], &state);
        if (rc == (size_t)-1)
            break;
        pcnv += rc;
    }
    if (rc != -1)
    {
        size_t TotalSizeOfConv = (size_t)(pcnv - converted);
        char8_t ValidationData[11] = u8"zß水🍌";
        CASE_CHECK_EQ(TotalSizeOfConv, 11, "c16rtomb, Conversion length");
        CASE_CHECK_EQ(memcmp(ValidationData, converted, sizeof(ValidationData)), 0, "c16rtomb, Conversion content");
    }
    else
    {
        CASE_CHECK_EQ(false, true, "c16rtomb, conversion");
    }
    return;
}
void test_c32rtomb()
{
    mbstate_t state = { 0 };
    const char32_t str32[] = U"zß水🍌";
    constexpr size_t orglen = sizeof(str32) / sizeof(str32[0]);
    char8_t converted[11] = { 0 };

    const char32_t* p = str32;
    char8_t* pcnv = converted;
    size_t rc = 0;

    for (size_t i = 0; i < orglen; i++)
    {
        rc = c32rtomb((char*)pcnv, p[i], &state);
        if (rc == (size_t)-1)
            break;
        pcnv += rc;
    }
    if (rc != -1)
    {
        size_t TotalSizeOfConv = (size_t)(pcnv - converted);
        char8_t ValidationData[11] = u8"zß水🍌";
        CASE_CHECK_EQ(TotalSizeOfConv, 11, "c32rtomb, Conversion length");
        CASE_CHECK_EQ(memcmp(ValidationData, converted, sizeof(ValidationData)), 0, "c32rtomb, Conversion content");
    }
    else
    {
        CASE_CHECK_EQ(false, true, "c32rtomb, conversion");
    }
    return;
}

void test_uchar()
{
	printf("\ntest suite uchar:\n");

    test_mbrtoc16();
    test_mbrtoc32();
    test_c16rtomb();
    test_c32rtomb();
}