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
#ifndef TOS_PRINT_UTILS_H
#define TOS_PRINT_UTILS_H
//TODO: Merge these functions, no need to have one for file and one for string
#include <include\stdio.h>
#include <include\stddef.h>
#include <include\stdint.h>
#include <include\stdarg.h>
#include "IEEE754Parsers.h"
enum class sf_bitwidth {
	byte,
	word,
	dword,
	qword,
	imax,
	size,
	ptrdiff,
	longd,
	unknown
};

enum class sf_convtype {
	decimal,
	udecimal_oct,
	udecimal_unsigned,
	udecimal_hex,
	double_dec,
	double_exponent,
	double_dec_or_exp,
	double_hex_exp,
	charconv,
	string,
	pointer,
	n,
	noconv,
	unknown
};
typedef uint8_t type_sf_real10[10];
union x86_reg_struct {
	int8_t sbyte;
	uint8_t byte;
	int16_t sword;
	uint16_t word;
	int32_t sdword;
	uint32_t dword;
	int64_t sqword;
	uint64_t qword;
	double real8;
	// long double, because windows doesnt support long double
	long double real10;
};

struct sf_flags {
	bool bLeftJustified;
	bool bSign;
	bool bSpace;
	bool bAltForm;
	bool bZeroPad;
	int nPrecision;
	int nMinFieldWidth;
};

#ifdef __cplusplus
extern "C" {
#else
#endif // __cplusplus

sf_convtype ParseConvType(char cType, bool* pBig);
sf_bitwidth ParseBitWidth(const char* s);

char llutoch(uint64_t i, bool bUpper);
char* llutoa(
	uint64_t v,
	uint64_t radix,
	size_t MinimumCharacters,
	bool bUpper,
	bool bSigned,
	char buffer[23],
	size_t* pOutSize);

const char* ParseSpecial(
	const char* buffer,
	sf_convtype* conv,
	sf_bitwidth* width,
	bool* pUppercase,
	sf_flags* flags,
	char TempBuffer[sizeof(dbl_to_str_state::szBuffer)]);

const char* FindNextSpecial(const char* format);

size_t CopyTextWithLimits(
	char* restrict s, size_t n,
	size_t* pWrote,
	const char* szSource,
	size_t SourceSize);

int CopyText_File(
	FILE* restrict stream,
	size_t* pWrote,
	const char* szSource,
	size_t SourceSize);

size_t SetTextWithLimits(
	char* restrict s, size_t n,
	size_t* pWrote,
	const char chPadding,
	size_t SetSize);

size_t WritePaddedTextNoDouble(
	char* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	const char* szSource,
	size_t SourceSize);
int WritePaddedTextNoDouble_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	const char* szSource,
	size_t SourceSize);

size_t WritePaddedTextDoubleReal(
	char* restrict s, size_t n,
	size_t* pWrote,
	sf_flags* pFlags,
	char* szSource,
	size_t SourceSize);
int WritePaddedTextDoubleReal_File(
	FILE* restrict stream,
	size_t* pWrote,
	sf_flags* pFlags,
	char* szSource,
	size_t SourceSize);

size_t ProcessParameter_vsprintf(
	char* restrict s, size_t n, size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState
);
int ProcessParameter_vfprintf(
	FILE* restrict stream,
	size_t* wrote,
	sf_convtype ConvType,
	sf_bitwidth BitWidth,
	bool bUpper,
	x86_reg_struct* reg,
	sf_flags* pFlags,
	dbl_to_str_state* pState
);
bool ReadVararg(
	va_list* pList, 
	sf_convtype ConvType, 
	sf_bitwidth BitWidth, 
	x86_reg_struct* pReg);
#ifdef __cplusplus
};
#endif // __cplusplus

#endif // !TOS_PRINT_UTILS_H
