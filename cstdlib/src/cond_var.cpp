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
#include "lock.h"
#include "TOSThreadEnvironmentBlock.h"

#ifndef MTX_SLEEP_ON_RETRY
#define MTX_SLEEP_ON_RETRY (10)
#endif

struct tos_internal_cndvar {
	tos_cndvar_tls* pFirst;
};


#ifdef _WIN32
#include "win32/win32_ntdll.h"
consteval LARGE_INTEGER InitializeUSSleep()
{
	LARGE_INTEGER ret;
	ret.QWord = { (uint64_t)(-10ll) };
	return ret;
}
constexpr LARGE_INTEGER c_YieldTime = { {0llu} };
constexpr LARGE_INTEGER c_ForcedYield = InitializeUSSleep();
#endif // _WIN32

int cnd_broadcast(cnd_t* cond)
{
	int nRet = thrd_error;
	tos_cndvar_tls* pNext = NULL;
	tos_cndvar_tls* pCurr;
	if (cond)
	{
		pCurr = ((tos_internal_cndvar*)cond)->pFirst;
		while (pCurr)
		{
			AquireLock(&pCurr->lock);
			pNext = pCurr->pNext;
			pCurr->pNext = NULL;
			pCurr->bSignaled = true;
			FreeLock(&pCurr->lock);
			pCurr = pNext;
		}
		nRet = thrd_success;
		cond->pHandle = NULL;
	}
	return nRet;
}
void cnd_destroy(cnd_t* cond)
{
	if (cond)
		cond->pHandle = NULL;
}
int cnd_init(cnd_t* cond)
{
	int nRet = thrd_error;
	if (cond)
	{
		cond->pHandle = NULL;
		nRet = thrd_success;
	}
	return nRet;
}
int cnd_signal(cnd_t* cond)
{
	int nRet = thrd_error;
	tos_cndvar_tls* pCurr;
	if (cond)
	{
		pCurr = ((tos_internal_cndvar*)cond)->pFirst;
		if (pCurr)
		{
			AquireLock(&pCurr->lock);
			cond->pHandle = pCurr->pNext;
			pCurr->pNext = NULL;
			pCurr->bSignaled = true;
			FreeLock(&pCurr->lock);
		}
		nRet = thrd_success;
	}
	return nRet;
}

extern "C" bool tos_check_elapse_timespec(const struct timespec restrict * target);

int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx,
	const struct timespec* restrict ts)
{
	int nRet = thrd_error;
	tos_cndvar_tls* pCurr;
	tos_cndvar_tls* pNext;
	uint64_t RetryCount = 0;
	tos_cndvar_tls* pOur = &tos_teb.CondVar;
	if (!cond || !mtx)
		goto cleanup;
	if (cond->pHandle)
	{
		pCurr = ((tos_internal_cndvar*)cond)->pFirst;
		while (pCurr)
		{
			AquireLock(&pCurr->lock);
			pNext = pCurr->pNext;
			if (pNext == NULL)
			{
				
				pCurr->pNext = pOur;
				pOur->bSignaled = false;
				pOur->pNext = NULL;
				FreeLock(&pCurr->lock);
				break;
			}
			FreeLock(&pCurr->lock);
			pCurr = pNext;
		}
	}
	else
		cond->pHandle = pOur;
	mtx_unlock(mtx);

	do {
		AquireLock(&pOur->lock);
		if (pOur->bSignaled)
		{
			nRet = thrd_success;
			pOur->bSignaled = false;
			FreeLock(&pOur->lock);
			break;
		}
		FreeLock(&pOur->lock);
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
	} while (nRet != thrd_success);
cleanup:
	return nRet;
}
int cnd_wait(cnd_t* cond, mtx_t* mtx)
{
	int nRet = thrd_error;
	tos_cndvar_tls* pCurr;
	tos_cndvar_tls* pNext;
	tos_cndvar_tls* pOur = &tos_teb.CondVar;
	uint64_t RetryCount = 0;
	if (!cond || !mtx)
		goto cleanup;
	if (cond->pHandle)
	{
		pCurr = ((tos_internal_cndvar*)cond)->pFirst;
		while (pCurr)
		{
			AquireLock(&pCurr->lock);
			pNext = pCurr->pNext;
			if (pNext == NULL)
			{
				pCurr->pNext = pOur;
				pOur->bSignaled = false;
				pOur->pNext = NULL;
				FreeLock(&pCurr->lock);
				break;
			}
			FreeLock(&pCurr->lock);
			pCurr = pNext;
		}
	}
	else
		cond->pHandle = pOur;
	mtx_unlock(mtx);

	while(1) 
	{
		AquireLock(&pOur->lock);
		if (pOur->bSignaled)
		{
			nRet = thrd_success;
			pOur->bSignaled = false;
			FreeLock(&pOur->lock);
			break;
		}
		FreeLock(&pOur->lock);
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

cleanup:
	return nRet;
}