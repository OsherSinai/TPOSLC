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
#ifndef TOS_THREAD_ENVIRONMENT_BLOCK_H
#define TOS_THREAD_ENVIRONMENT_BLOCK_H
#include <include\stddef.h>
#include <include\errno.h>
#include <include\threads.h>
#include <include\signal.h>
#include <include\time.h>
#include <include\wchar.h>
#include <include\except.h>
#include "lock.h"
#include "LinkedList.h"

typedef struct __exception_struct {
	TosLinkedList List;
	_tos_exception exception;
}_exception_struct;

typedef struct _tos_HandlerPack {
	TOSSignalHandler SigIntHandler;
	TOSSignalHandler SigILLHandler;
	TOSSignalHandler SigAbortHandler;
	TOSSignalHandler SigFPEHandler;
	TOSSignalHandler SigSegvHandler;
	TOSSignalHandler SigTermHandler;
}tos_HandlerPack;
typedef struct _tos_cndvar_tls {
	struct _tos_cndvar_tls* pNext;
	tos_lock lock;
	bool bSignaled;
}tos_cndvar_tls;

typedef struct _tos_thread_environment_block{
	int nError;
	thrd_t CurrentThread;
	tos_cndvar_tls CondVar;
	tos_HandlerPack SignalHandlers;
	char* pStrtok;
	struct tm LocalTime;
	struct tm UTCTime;
	_exception_struct Exceptions;
}tos_thread_environment_block;


extern "C" thread_local tos_thread_environment_block tos_teb;
LIBC_DEF_BEGIN
tos_thread_environment_block* _tos_GetTEB();
void __dyn_tls_on_demand_init();
LIBC_DEF_END
#endif // !TOS_THREAD_ENVIRONMENT_BLOCK_H
