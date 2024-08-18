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
#ifndef TOS_WPRINT_UTILS_H
#define TOS_WPRINT_UTILS_H
//TODO: Merge these functions, no need to have one for file and one for string
#include <include\stdio.h>
#include <include\stddef.h>
#include <include\stdint.h>
#include <include\stdarg.h>
#include <include\wchar.h>
#include "IEEE754Parsers.h"
#include "printf_utils.h"
#ifdef __cplusplus
extern "C" {
#else
#endif // __cplusplus

sf_convtype WideParseConvType(wchar_t cType, bool* pBig);
sf_bitwidth WideParseBitWidth(const wchar_t* s);

wchar_t Widellutoch(uint64_t i, bool bUpper);
wchar_t* Widellutoa(
	uint64_t v,
	uint64_t radix,
	size_t MinimumCharacters,
	bool bUpper,
	bool bSigned,
	wchar_t buffer[23],
	size_t* pOutSize);

const wchar_t* WideParseSpecial(
	const wchar_t* buffer,
	sf_convtype* conv,
	sf_bitwidth* width,
	bool* pUppercase,
	sf_flags* flags,
	wchar_t TempBuffer[sizeof(dbl_to_str_state::szBuffer)]);

const wchar_t* WideFindNextSpecial(const wchar_t* format);

size_t WideCopyTextWithLimits(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	const wchar_t* szSource,
	size_t SourceSize);

int WideCopyText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const wchar_t* szSource,
	size_t SourceSize);

size_t WideSetTextWithLimits(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	const wchar_t chPadding,
	size_t SetSize);

size_t WideWritePaddedTextNoDouble(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	const wchar_t* szSource,
	size_t SourceSize);
int WideWritePaddedTextNoDouble_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	const wchar_t* szSource,
	size_t SourceSize);

size_t WideWritePaddedTextDoubleReal(
	wchar_t* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	wchar_t* szSource,
	size_t SourceSize);
int WideWritePaddedTextDoubleReal_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	wchar_t* szSource,
	size_t SourceSize);

size_t WideProcessParameter_vsprintf(
	wchar_t* restrict s, size_t n, size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState,
	wchar_t wcsBuffer[sizeof(dbl_to_str_state::szBuffer) / sizeof(dbl_to_str_state::szBuffer[0])]
);
int WideProcessParameter_vfprintf(
	FILE* restrict stream,
	size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState,
	wchar_t wcsBuffer[sizeof(dbl_to_str_state::szBuffer) / sizeof(dbl_to_str_state::szBuffer[0])]
);
bool WideReadVararg(
	va_list* pList,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	x86_reg_struct* pReg);
#ifdef __cplusplus
};
#endif // __cplusplus

#endif // !TOS_PRINT_UTILS_H
