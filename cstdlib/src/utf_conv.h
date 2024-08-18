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
#ifndef TOS_UTF_CONVERTORS_H
#define TOS_UTF_CONVERTORS_H
#include <include\stddef.h>

LIBC_DEF_BEGIN
union utf_conv_ctx {
	uint8_t chArr[4];
	uint16_t wArr[2];
	uint32_t buf;
};
enum _tos_UTFValidationResult {
	UTFValidationResult_surrogate = -3,
	UTFValidationResult_incomplete = -2,
	UTFValidationResult_encoding_error = -1,
	UTFValidationResult_null = 0,
	UTFValidationResult_success = 1
};

_tos_UTFValidationResult _tos_UTF8_ValidateEncodedArray(uint8_t* pArr, size_t ArrSize, uint8_t* pSize);
uint8_t _tos_UTF8_DecodeSymbol(uint8_t* pArr, utf_conv_ctx* pCtx);
uint8_t _tos_UTF8_EncodeSymbol(uint32_t dwSym, utf_conv_ctx* pCtx);
_tos_UTFValidationResult _tos_UTF16_ValidateEncodedArray(uint16_t* pArr, size_t ArrLen, uint8_t* pLen);
uint8_t _tos_UTF16_DecodeSymbol(uint16_t* pArr, utf_conv_ctx* pCtx);
uint8_t _tos_UTF16_EncodeSymbol(uint32_t dwSym, utf_conv_ctx* pCtx);
LIBC_DEF_END
#endif // !TOS_UTF_CONVERTORS_H
