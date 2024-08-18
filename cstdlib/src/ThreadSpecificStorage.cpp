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
#include <include\threads.h>
#include <include\string.h>
#include "TOSThreadEnvironmentBlock.h"
#include "lock.h"

#ifdef _WIN32
#include "win32/win32_tls.h"
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32


typedef struct _tos_tss_destructors {
	tss_dtor_t dtors[TOS_MIN_TSS_IDX];
}tos_tss_destructors;

static tos_tss_destructors g_tss_destructor_array;
static tos_lock g_tss_lock;
extern "C" void _tos_initialize_tss_program_dtors()
{
	InitializeLock(&g_tss_lock);
	memset(&g_tss_destructor_array, 0, sizeof(g_tss_destructor_array));
}

extern "C" int _tos_initialize_tss_thread_tss()
{
#ifdef _WIN32
	// the Tls* functions in win32_tls handle the tls expansion
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
	return 0;
}
extern "C" int _tos_uninitialize_tss_thread_tss()
{
#ifdef _WIN32
	// if we wont call this once the thread exit the program will crash as we're not using an actual heap
	FreeExpansionTlsSlots();
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
	return 0;
}

extern "C" void _tos_tss_call_thread_dtors()
{
	AquireLock(&g_tss_lock);

	for (size_t i = 0; i < TOS_MIN_TSS_IDX; i++)
	{
		if (g_tss_destructor_array.dtors[i] != 0)
		{
			void* val;
#ifdef _WIN32
			val = TlsGetValue(i);
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
			if(g_tss_destructor_array.dtors[i])
				g_tss_destructor_array.dtors[i](val);
		}
	}

	FreeLock(&g_tss_lock);
}

int tss_create(tss_t* key, tss_dtor_t dtor)
{
	int nRet;
#ifdef _WIN32
	key->dwIdx = TlsAlloc();
	if (key->dwIdx != ~0)
	{
		AquireLock(&g_tss_lock);
		g_tss_destructor_array.dtors[key->dwIdx] = dtor;
		FreeLock(&g_tss_lock);
		nRet = thrd_success;
	}
	else
	{
		nRet = thrd_error;
	}
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
	return nRet;
}

void tss_delete(tss_t key)
{
#ifdef _WIN32
	TlsFree(key.dwIdx);
	AquireLock(&g_tss_lock);
	g_tss_destructor_array.dtors[key.dwIdx] = 0;
	FreeLock(&g_tss_lock);
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
}

void* tss_get(tss_t key)
{
	void* pRet;
#ifdef _WIN32
	pRet = TlsGetValue(key.dwIdx);
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
	return pRet;
}
int tss_set(tss_t key, void* val)
{
	int nRet;
#ifdef _WIN32
	if (TlsSetValue(key.dwIdx, val) == TRUE)
		nRet = thrd_success;
	else
		nRet = thrd_error;
#else
#error Not implemeneted (ThreadSpecificStorage.cpp)
#endif // _WIN32
	return nRet;
}