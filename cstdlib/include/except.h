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
#ifndef TOS_EXCEPT_H
#define TOS_EXCEPT_H

#include "setjmp.h"
#include "stddef.h"

LIBC_DEF_BEGIN
typedef void (*_tos_exception_value_free)(void*);
//non-0 on equal
typedef int (*_tos_exception_value_eq)(void*, void*);
typedef struct __tos_exception {
	int nThrown;
	void* pValue;
	_tos_exception_value_free procFree;
	_tos_exception_value_eq procEq;
}_tos_exception;


_tos_exception _tos_exception_try(int nSetjmpRet, jmp_buf JmpBuf);
void _tos_exception_throw(_tos_exception value);
void _tos_exception_handled();

#define TOS_THROW(excpt) _tos_exception_throw(excpt)

#define TOS_TRY \
{\
	jmp_buf jb;\
	_tos_exception TosTryReturn = _tos_exception_try(setjmp(jb), jb);\
	if(TosTryReturn.nThrown == 0)\
	{

#define TOS_EXCEPT(value)\
	}\
	if(TosTryReturn.nThrown && (TosTryReturn.procEq(TosTryReturn.pValue, value) != 0))\
	{\
		TosTryReturn.nThrown = 0;
#define TOS_EXCEPT_UNIVERSAL\
	}\
	if(TosTryReturn.nThrown)\
	{\
		TosTryReturn.nThrown = 0;
#define TOS_TRY_FINISH\
	}\
	_tos_exception_handled();\
	if(TosTryReturn.nThrown)\
	{\
		_tos_exception_throw(TosTryReturn);\
	}\
}
LIBC_DEF_END
#endif // !TOS_EXCEPT_H
