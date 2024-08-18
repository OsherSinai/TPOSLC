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
#include <include\except.h>
#include <include\setjmp.h>
#include <include\threads.h>
#include <include\stdlib.h>
#include <include\string.h>
#include <include\stdio.h>

#include "LinkedList.h"
#include "TOSThreadEnvironmentBlock.h"

struct tls_exception_llent {
	TosLinkedListEntry entry;
	jmp_buf buffer;
};

extern "C" void _tos_longjump_exception() 
{
	
	if (_tos_GetTEB()->Exceptions.List.pEnd)
	{
		longjmp(((tls_exception_llent*)_tos_GetTEB()->Exceptions.List.pEnd)->buffer, 1);
	}
	else
	{
		fprintf(stderr, "Uncaught exception\n");
		_Exit(1);
	}
}

extern "C" void _tos_InitializeException()
{
	_exception_struct* pExceptS = &_tos_GetTEB()->Exceptions;
	memset(pExceptS, 0, sizeof(_exception_struct));
	LListInitialize(&pExceptS->List);
}
extern "C" void _tos_UninitializeException()
{
	LListUninitialize(&_tos_GetTEB()->Exceptions.List);

}

_tos_exception _tos_exception_try(int nSetjmpRet, jmp_buf JmpBuf)
{
	_tos_exception ret = {0};
	if (nSetjmpRet == 0)
	{
		tls_exception_llent* pent = (tls_exception_llent*)LListCreateAtEnd(&_tos_GetTEB()->Exceptions.List, sizeof(tls_exception_llent), 0);
		memcpy(pent->buffer, JmpBuf, sizeof(jmp_buf));
	}
	else
	{
		ret = _tos_GetTEB()->Exceptions.exception;
	}
	return ret;
}

static int default_eq(void* a, void* b)
{
	return a == b;
}

void _tos_exception_throw(_tos_exception value)
{
	value.nThrown = 1;
	if (value.procEq == NULL)
		value.procEq = default_eq;
	_tos_GetTEB()->Exceptions.exception = value;
	_tos_longjump_exception();
}
void _tos_exception_handled()
{
	if (_tos_GetTEB()->Exceptions.exception.procFree)
		_tos_GetTEB()->Exceptions.exception.procFree(_tos_GetTEB()->Exceptions.exception.pValue);
	if (_tos_GetTEB()->Exceptions.List.pEnd)
		LListDeleteEntry(&_tos_GetTEB()->Exceptions.List, _tos_GetTEB()->Exceptions.List.pEnd, 0, 0);
	memset(&_tos_GetTEB()->Exceptions.exception, 0, sizeof(_tos_exception));
}