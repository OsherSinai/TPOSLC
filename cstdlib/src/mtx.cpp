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
#include <include\stdlib.h>

#ifdef _WIN32
#include "win32/win32_ntdll.h"
#else
#error Unimplemeted (mtx.cpp)
#endif // _WIN32

#ifndef MTX_SLEEP_ON_RETRY
#define MTX_SLEEP_ON_RETRY (10)
#endif


#include "lock.h"

//TODO: add detection of deadlocks
//TODO: add error codes
struct plain_mtx {
	tos_mtx_base base;
	tos_lock lock;
};
struct recursive_mtx {
	plain_mtx plain;
	uint64_t qwTid;
	uint64_t qwRecurseCount;
};

#ifdef _WIN32
consteval LARGE_INTEGER InitializeUSSleep()
{
	LARGE_INTEGER ret;
	ret.QWord = { (uint64_t)(-10ll) };
	return ret;
}
constexpr LARGE_INTEGER c_YieldTime = { {0llu} };
constexpr LARGE_INTEGER c_ForcedYield = InitializeUSSleep();
#endif // _WIN32

void mtx_destroy(mtx_t* mtx)
{
	if (mtx->pBase)
	{
		free(mtx->pBase);
		mtx->pBase = 0;
	}
}
int mtx_init(mtx_t* mtx, int type)
{
	int nRet = thrd_error;
	char uchIsRecursive = (type & mtx_recursive) == mtx_recursive ? 1 : 0;
	recursive_mtx* pMtx;
	if(uchIsRecursive)
		pMtx = (recursive_mtx*)malloc(sizeof(recursive_mtx));
	else
		pMtx = (recursive_mtx*)malloc(sizeof(plain_mtx));

	if (pMtx)
	{
		nRet = thrd_success;
		pMtx->plain.base.bRecursive = uchIsRecursive;
		pMtx->plain.base.bTimed = (type & mtx_timed) == mtx_timed ? 1 : 0;
		InitializeLock(&pMtx->plain.lock);
		if (uchIsRecursive)
		{
			pMtx->qwRecurseCount = 0;
			pMtx->qwTid = 0;
		}
		mtx->pBase = (tos_mtx_base*)pMtx;
	}

	return nRet;
}



static inline int mtx_trylock_inner(mtx_t* mtx, uint64_t tid)
{
	int nRet;
	if (mtx->pBase->bRecursive)
	{
		recursive_mtx* rmtx = (recursive_mtx*)mtx->pBase;
		tos_lock* pLock = &rmtx->plain.lock;
		nRet = TryAquireLock(pLock);
		if (nRet == 0)
		{
			if (rmtx->qwTid == tid || (rmtx->qwTid == 0 && rmtx->qwRecurseCount == 0))
			{
				rmtx->qwTid = tid;
				rmtx->qwRecurseCount++;
				nRet = thrd_success;
			}
			else
				nRet = thrd_error;
		}
		else
			nRet = thrd_error;
		FreeLock(pLock);
	}
	else
	{
		plain_mtx* pmtx = (plain_mtx*)mtx->pBase;
		tos_lock* pLock = &(pmtx->lock);
		nRet = TryAquireLock(pLock);
		if (nRet == 0)
			nRet = thrd_success;
		else
			nRet = thrd_error;
	}
	return nRet;
}

int mtx_lock(mtx_t* mtx)
{
	int nRet = thrd_success;
	uint64_t tid = GetCurrentThreadId();
	uint64_t RetryCount = 0;
	do {
		nRet = mtx_trylock_inner(mtx, tid);
		if (nRet != thrd_success) [[likely]]
		{
			RetryCount++;
			if (RetryCount > MTX_SLEEP_ON_RETRY) [[unlikely]]
			{
				RetryCount = 0;
#ifdef _WIN32
				if (SyscallNtDelayExecution(false, &c_YieldTime) == STATUS_NO_YIELD_PERFORMED)
					SyscallNtDelayExecution(false, &c_ForcedYield);
#else
#error Unimplemented (mtx.cpp)
#endif // _WIN32
			}
		}
	} while (nRet != thrd_success);
	return nRet;
}

extern "C" bool tos_check_elapse_timespec(const struct timespec restrict * target)
{
	struct timespec now;
	struct timespec target2 = *target;
	timespec_get(&now, TIME_UTC);
	target2.tv_sec -= now.tv_sec;
	target2.tv_nsec -= now.tv_nsec;
	if (target2.tv_nsec < 0)
		target2.tv_sec--;
	return target2.tv_sec < 0;
}
int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts)
{
	int nRet = thrd_success;
	uint64_t tid = GetCurrentThreadId();
	uint64_t RetryCount = 0;
	if (mtx->pBase->bTimed == 0)
	{
		nRet = thrd_error;
	}
	else
	{
		do {
			nRet = mtx_trylock_inner(mtx, tid);
			if (nRet != thrd_success)
			{
				if (!tos_check_elapse_timespec(ts)) [[likely]]
				{
					RetryCount++;
					if (RetryCount > MTX_SLEEP_ON_RETRY)
					{
						RetryCount = 0;
#ifdef _WIN32
						if (SyscallNtDelayExecution(false, &c_YieldTime) == STATUS_NO_YIELD_PERFORMED)
							SyscallNtDelayExecution(false, &c_ForcedYield);
#else
#error Unimplemented (mtx.cpp)
#endif // _WIN32
					}
				}
				else [[unlikely]]
				{
					nRet = thrd_timedout;
					break;
				}
			}
		} while (nRet != thrd_success);
	}
	return nRet;
}

int mtx_trylock(mtx_t* mtx)
{
	return mtx_trylock_inner(mtx, GetCurrentThreadId());
}
int mtx_unlock(mtx_t* mtx)
{
	int nRet = thrd_error;
	size_t RetryCount = 0;
	if (mtx->pBase->bRecursive)
	{
		recursive_mtx* pReMtx = (recursive_mtx*)mtx->pBase;
		uint64_t tid = GetCurrentThreadId();
		tos_lock* pLock = &pReMtx->plain.lock;
		while (1)
		{
			int nLockAquired = TryAquireLock(pLock);
			if (nLockAquired == 0)
			{
				if (pReMtx->qwTid == tid)
				{
					pReMtx->qwRecurseCount--;
					if (pReMtx->qwRecurseCount == 0)
					{
						pReMtx->qwTid = 0;
					}
					FreeLock(pLock);
					nRet = thrd_success;
					break;
				}
				else
				{
					FreeLock(pLock);
					//TODO: error set errno
					break;
				}
				FreeLock(pLock);
			}

			RetryCount++;
			if ((RetryCount > MTX_SLEEP_ON_RETRY))
			{
				RetryCount = 0;
#ifdef _WIN32
				if ((SyscallNtDelayExecution(false, &c_YieldTime) == STATUS_NO_YIELD_PERFORMED))
					SyscallNtDelayExecution(false, &c_ForcedYield);
#else
#error Unimplemented (mtx.cpp)
#endif // _WIN32
			}
		}
	}
	else
	{
		plain_mtx* pMtx = (plain_mtx*)mtx->pBase;
		tos_lock* pLock = &pMtx->lock;
		nRet = FreeLock(pLock);
		nRet = (nRet != 0) ? thrd_success : thrd_error;
		//nRet = thrd_success;
	}
	return nRet;
}