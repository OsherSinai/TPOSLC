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
#include <include\signal.h>
#include <include\stdlib.h>
#include <include\string.h>
#include <include\except.h>
#include "TOSThreadEnvironmentBlock.h"
#include "ProcessInitializers.h"
#include "lock.h"
#include "LinkedList.h"
#ifdef _WIN32
#include "win32/win32_ntdll.h"
#endif // _WIN32

struct thrd_creation_package {
	TosLinkedListEntry LLEntry;
	thrd_t Thread;
	thrd_start_t Func;
	void* pArg;
	int nRet;
	mtx_t Mtx;
	cnd_t Cnd;
	bool bDetached;
	bool bFinished;
	uint8_t ThreadRefCounter;
	void* pTlsBufferBackup;
};

static TosLinkedList g_ThreadsLinkedList;
static volatile tos_lock g_ThreadArrayLock = STATIC_INITIALIZE_TOS_LOCK;

extern "C" void _tos_InitializeThreadLList()
{
	AquireLock(&g_ThreadArrayLock);
	LListInitialize(&g_ThreadsLinkedList);
	FreeLock(&g_ThreadArrayLock);
}
extern "C" void _tos_UninitializeThreadLList()
{
	AquireLock(&g_ThreadArrayLock);
	LListUninitialize(&g_ThreadsLinkedList);
	FreeLock(&g_ThreadArrayLock);
}

extern "C" void _tos_InitializePrimaryThreadData()
{
	AquireLock(&g_ThreadArrayLock);
	LListInitialize(&g_ThreadsLinkedList);
	FreeLock(&g_ThreadArrayLock);
#ifdef _WIN32
	DuplicateHandle(
		GetCurrentProcess(),
		NtCurrentThread(),
		GetCurrentProcess(),
		&tos_teb.CurrentThread.pHandle,
		0,
		FALSE,
		DUPLICATE_SAME_ACCESS
	);
	//tos_teb.CurrentThread.pHandle = (void*)~(0llu);
	tos_teb.CurrentThread.qwTid = GetCurrentThreadId();
#else
#error _tos_InitializePrimaryThreadData unimplemented
#endif // _WIN32
}
extern "C" void _tos_UninitializePrimaryThreadData()
{
#ifdef _WIN32
	SyscallNtClose(tos_teb.CurrentThread.pHandle);
#else
#error _tos_InitializePrimaryThreadData unimplemented
#endif // _WIN32
	AquireLock(&g_ThreadArrayLock);
	LListUninitialize(&g_ThreadsLinkedList);
	FreeLock(&g_ThreadArrayLock);
}


extern "C" void _tos_tss_call_thread_dtors();

static int thrd_start_wrapper(void* pArg)
{
	void* pTlsBuffer = NULL;
	int nRet = 0;
	uint64_t dwTid = 0;
	nRet = _tos_InitializeThread(&pTlsBuffer);
	//Initialize all thread variables
	thrd_creation_package* tcp = (thrd_creation_package*)pArg;
	if (nRet)
		goto cleanup;

	tcp->pTlsBufferBackup = pTlsBuffer;

	tos_teb.CurrentThread.pHandle = tcp->Thread.pHandle;
	dwTid = GetCurrentThreadId();
	tos_teb.CurrentThread.qwTid = GetCurrentThreadId();
	tcp->Thread.qwTid = dwTid;;

	TOS_TRY
		nRet = tcp->Func(tcp->pArg);
	TOS_EXCEPT_UNIVERSAL
		nRet = -1;
		fprintf(stderr, "uncaught exception in thread, [0x%p], id [0x%016llx], terminating thread\n", tos_teb.CurrentThread.pHandle, tos_teb.CurrentThread.qwTid);
	TOS_TRY_FINISH

	mtx_lock(&tcp->Mtx);
	tcp->nRet = nRet;
	tcp->bFinished = true;
	mtx_unlock(&tcp->Mtx);

cleanup:
	_tos_tss_call_thread_dtors();
	bool bFreeTCP = false;
	mtx_lock(&tcp->Mtx);
	tcp->ThreadRefCounter--;
	bFreeTCP = tcp->ThreadRefCounter == 0;
	cnd_signal(&tcp->Cnd);
	mtx_unlock(&tcp->Mtx);

	if (bFreeTCP)
	{
		AquireLock(&g_ThreadArrayLock);
		LListRemoveEntry(&g_ThreadsLinkedList, &tcp->LLEntry);
		FreeLock(&g_ThreadArrayLock);
		mtx_destroy(&tcp->Mtx);
		cnd_destroy(&tcp->Cnd);
#ifdef _WIN32
		SyscallNtClose(tcp->Thread.pHandle);
#endif // _WIN32
		free(tcp);
	}

	_tos_UninitializeThread(&pTlsBuffer);
	return nRet;
}

void call_once(once_flag* flag, void (*func)(void))
{
	if (TryAquireLock((tos_lock*)&flag->reserve) == 0)
		func();
}

int thrd_create(thrd_t* thr, thrd_start_t func, void* arg)
{
	int nRet = thrd_error;
	thrd_creation_package* tcp = NULL;
#ifdef _WIN32
	NTSTATUS ntStat;
	//CLIENT_ID cid = { 0 };
	PS_ATTRIBUTE_LIST psAttrList;
	void* clientteb = NULL;
	//psAttrList.Attributes[0].Attribute = 0x10003;
	//psAttrList.Attributes[0].Size = 0x10;
	//psAttrList.Attributes[0].ReturnLength = 0;
	//psAttrList.Attributes[0].ValuePtr = &cid;

	psAttrList.Attributes[0].Attribute = 0x10004;
	psAttrList.Attributes[0].Size = sizeof(void*);
	psAttrList.Attributes[0].ReturnLength = 0;
	psAttrList.Attributes[0].ValuePtr = &clientteb;

	psAttrList.TotalLength = sizeof(PS_ATTRIBUTE_LIST);
	//PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE)
#endif // _WIN32


	if (!thr || !func)
		goto cleanup;

	thr->pHandle = NULL;
	thr->qwTid = 0;

	tcp = (thrd_creation_package*)malloc(sizeof(thrd_creation_package));
	if (tcp == NULL)
	{
		nRet = thrd_nomem;
		goto cleanup;
	}
	tcp->Func = func;
	tcp->pArg = arg;
	tcp->Thread.pHandle = NULL;
	tcp->Thread.qwTid = 0;
	tcp->ThreadRefCounter = 2;
	nRet = mtx_init(&tcp->Mtx, mtx_plain);
	if (nRet != thrd_success)
	{
		nRet = thrd_nomem;
		goto cleanup;
	}
	nRet = cnd_init(&tcp->Cnd);
	if (nRet != thrd_success)
	{
		nRet = thrd_nomem;
		goto cleanup;
	}

	AquireLock(&g_ThreadArrayLock);
	LListInsertAtEnd(&g_ThreadsLinkedList, &tcp->LLEntry);
	FreeLock(&g_ThreadArrayLock);

#ifdef _WIN32
	ntStat = SyscallNtCreateThreadEx(
		&tcp->Thread.pHandle,
		THREAD_ALL_ACCESS,
		0,
		(HANDLE)NtCurrentProcess(),
		thrd_start_wrapper,
		tcp,
		0,
		0,
		0,
		0,
		&psAttrList
	);

	thr->pHandle = tcp->Thread.pHandle;
	if (ntStat == STATUS_SUCCESS)
	{
		CLIENT_ID* pCid = (CLIENT_ID*)(((uint8_t*)clientteb) + 0x40);
		thr->qwTid = (uint64_t)pCid->UniqueThread;
		tcp->Thread.qwTid = thr->qwTid;
		nRet = thrd_success;
		tcp = NULL;
	}
#else
#error Unimplemented (thread.cpp)
#endif // _WIN32


cleanup:
	if (tcp)
	{
		AquireLock(&g_ThreadArrayLock);
		LListRemoveEntry(&g_ThreadsLinkedList, &tcp->LLEntry);
		FreeLock(&g_ThreadArrayLock);

		cnd_destroy(&tcp->Cnd);
		mtx_destroy(&tcp->Mtx);
		free(tcp);
	}
	return nRet;
}
thrd_t thrd_current()
{
	return tos_teb.CurrentThread;
}
int thrd_detach(thrd_t thr)
{
	int nRet = thrd_error;
	//uint16_t wPos = 0;
	thrd_creation_package* pTCP;
	AquireLock(&g_ThreadArrayLock);
	pTCP = (thrd_creation_package*)g_ThreadsLinkedList.pStart;
	while (pTCP && thrd_equal(thr, pTCP->Thread) == 0)
	{
		pTCP = (thrd_creation_package*)pTCP->LLEntry.pNext;
	}
	FreeLock(&g_ThreadArrayLock);

	if (pTCP)
	{
		bool bFreeTCP;
		mtx_lock(&pTCP->Mtx);
		pTCP->bDetached = true;
		pTCP->ThreadRefCounter--;
		bFreeTCP = pTCP->ThreadRefCounter == 0;
		mtx_unlock(&pTCP->Mtx);
		nRet = thrd_success;

		if (bFreeTCP)
		{
			AquireLock(&g_ThreadArrayLock);
			LListRemoveEntry(&g_ThreadsLinkedList, &pTCP->LLEntry);
			FreeLock(&g_ThreadArrayLock);
			mtx_destroy(&pTCP->Mtx);
			cnd_destroy(&pTCP->Cnd);
#ifdef _WIN32
			SyscallNtClose(pTCP->Thread.pHandle);
#endif // _WIN32
			free(pTCP);
		}
	}
	return nRet;
}
int thrd_equal(thrd_t thr0, thrd_t thr1)
{
	return (thr0.pHandle == thr1.pHandle) && (thr0.qwTid == thr1.qwTid);
}
_Noreturn void thrd_exit(int res)
{

	void* pTlsBuffer;
	thrd_creation_package* pTCP;
	AquireLock(&g_ThreadArrayLock);
	pTCP = (thrd_creation_package*)g_ThreadsLinkedList.pStart;
	while (pTCP && thrd_equal(thrd_current(), pTCP->Thread) == 0)
	{
		pTCP = (thrd_creation_package*)pTCP->LLEntry.pNext;
	}
	FreeLock(&g_ThreadArrayLock);

	if (pTCP == NULL)
	{
		__asm {int 3};
	}
	else
	{
		_tos_tss_call_thread_dtors();
		pTCP->nRet = res;
		bool bFreeTCP = false;
		mtx_lock(&pTCP->Mtx);
		pTCP->bFinished = true;
		pTCP->ThreadRefCounter--;
		bFreeTCP = pTCP->ThreadRefCounter == 0;
		cnd_signal(&pTCP->Cnd);
		mtx_unlock(&pTCP->Mtx);
		pTlsBuffer = pTCP->pTlsBufferBackup;
		if (bFreeTCP)
		{
			AquireLock(&g_ThreadArrayLock);
			LListRemoveEntry(&g_ThreadsLinkedList, &pTCP->LLEntry);
			FreeLock(&g_ThreadArrayLock);
			mtx_destroy(&pTCP->Mtx);
			cnd_destroy(&pTCP->Cnd);
#ifdef _WIN32
			SyscallNtClose(pTCP->Thread.pHandle);
#endif // _WIN32
			free(pTCP);
		}

		_tos_UninitializeThread(&pTlsBuffer);
	}

#ifdef _WIN32
	//call uninitialize thread
	NTSTATUS ntStat = SyscallNtTerminateThread(NULL, res);
	if (STATUS_CANT_TERMINATE_SELF == ntStat)
		raise(SIGTERM);
#else
#endif // _WIN32
	_Exit(SIGTERM);
	//unreachable
}
int thrd_join(thrd_t thr, int* res)
{
	int nRet = thrd_error;
	thrd_creation_package* pTCP;
	AquireLock(&g_ThreadArrayLock);
	pTCP = (thrd_creation_package*)g_ThreadsLinkedList.pStart;
	while (pTCP && thrd_equal(thr, pTCP->Thread) == 0)
	{
		pTCP = (thrd_creation_package*)pTCP->LLEntry.pNext;
	}
	FreeLock(&g_ThreadArrayLock);

	if (pTCP)
	{
		mtx_lock(&pTCP->Mtx);
		if (!pTCP->bFinished)
			cnd_wait(&pTCP->Cnd, &pTCP->Mtx);
		else
			mtx_unlock(&pTCP->Mtx);

		if (res)
			*res = pTCP->nRet;

		bool bFreeTCP;
		mtx_lock(&pTCP->Mtx);
		pTCP->ThreadRefCounter--;
		bFreeTCP = pTCP->ThreadRefCounter == 0;
		mtx_unlock(&pTCP->Mtx);

		if (bFreeTCP)
		{
			AquireLock(&g_ThreadArrayLock);
			LListRemoveEntry(&g_ThreadsLinkedList, &pTCP->LLEntry);
			FreeLock(&g_ThreadArrayLock);
			mtx_destroy(&pTCP->Mtx);
			cnd_destroy(&pTCP->Cnd);
#ifdef _WIN32
			SyscallNtClose(pTCP->Thread.pHandle);
#endif // _WIN32
			free(pTCP);
			nRet = thrd_success;
		}
	}

	return nRet;
}

int thrd_sleep(const struct timespec* duration, struct timespec* remaining)
{
	int nRet = 0;
	remaining->tv_sec = 0;
	remaining->tv_nsec = 0;
	timespec ts_start;
	timespec ts_end;
	timespec_get(&ts_start, TIME_UTC);
#ifdef _WIN32
	LARGE_INTEGER YieldTime;
	YieldTime.QWord = -(duration->tv_sec * 10'000'000llu + duration->tv_nsec / 100);
	NTSTATUS ntStat = SyscallNtDelayExecution(true, &YieldTime);
	if (ntStat == STATUS_USER_APC || ntStat == STATUS_ALERTED)
	{
		nRet = -1;
	}
	else if(ntStat < 0)
	{
		nRet = -2;
	}
#else
#error Unimplemented (thread.cpp)
#endif // _WIN32
	if (nRet == -1 || nRet == 0)
	{
		timespec_get(&ts_end, TIME_UTC);

		ts_end.tv_sec = ts_end.tv_sec - ts_start.tv_sec;
		ts_end.tv_nsec = ts_end.tv_nsec - ts_start.tv_nsec;
		if (ts_end.tv_nsec < 0)
		{
			ts_end.tv_nsec = 1'000'000'000 + ts_end.tv_nsec;
			ts_end.tv_sec--;
		}
		remaining->tv_sec = duration->tv_sec - ts_end.tv_sec;
		remaining->tv_nsec = duration->tv_nsec - ts_end.tv_nsec;
		if (remaining->tv_nsec < 0)
		{
			remaining->tv_nsec = 1'000'000'000 + ts_end.tv_nsec;
			remaining->tv_sec--;
		}
	}
	return nRet;
}
void thrd_yield()
{
#ifdef _WIN32
	constexpr LARGE_INTEGER c_YieldTime = { {0llu} };
	SyscallNtDelayExecution(false, &c_YieldTime);
#else
#error Unimplemented (thread.cpp)
#endif // _WIN32
}