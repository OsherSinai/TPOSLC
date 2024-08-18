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
#pragma once
#ifndef TEST_SUITES_H
#define TEST_SUITES_H

#include <include\stddef.h>

void test_stdint();
void test_ctype();
void test_errno();
void test_string();
void test_fenv();
void test_setjmp();
void test_stdarg();
void test_signal();
void test_time();
void test_math();

void test_stdlib();
void test_abort();
void test_atexit();
void test_quick_exit();

void test_inttypes();

void test_complex();

void test_threads();
void test_uchar();

void test_wctype();

void test_stdio();
void test_wstring();
#endif // !TEST_SUITES_H
