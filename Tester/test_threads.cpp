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
#include "TestCaseUtils.h"
#include "TestSuites.h"
#include <include/threads.h>
#include <include/time.h>

//void call_once(once_flag* flag, void (*func)(void));
bool g_test_call_once_flag;
static void cofunc()
{
	g_test_call_once_flag = true;
}
void test_call_once()
{
	once_flag of = ONCE_FLAG_INIT;
	g_test_call_once_flag = false;
	CASE_CHECK_EQ(g_test_call_once_flag, false, "call_once before 1st call");
	call_once(&of, cofunc);
	CASE_CHECK_EQ(g_test_call_once_flag, true, "call_once after 1st call");
	g_test_call_once_flag = false;
	CASE_CHECK_EQ(g_test_call_once_flag, false, "call_once before 2nd call");
	call_once(&of, cofunc);
	CASE_CHECK_EQ(g_test_call_once_flag, false, "call_once after 2nd call");
}



void test_mtx_init_destroy()
{
	mtx_t plain = {0};
	mtx_t timed = { 0 };
	mtx_t plain_recursive = { 0 };
	mtx_t timed_recursive = { 0 };
	int nRet = 0;

	nRet = mtx_init(&plain, mtx_plain);
	CASE_CHECK_EQ(nRet, thrd_success, "mtx_init, plain, ret");
	mtx_destroy(&plain);
	nRet = mtx_init(&timed, mtx_timed);
	CASE_CHECK_EQ(nRet, thrd_success, "mtx_init, timed, ret");
	mtx_destroy(&timed);
	nRet = mtx_init(&plain_recursive, mtx_plain | mtx_recursive);
	CASE_CHECK_EQ(nRet, thrd_success, "mtx_init, plain recursive, ret");
	mtx_destroy(&plain_recursive);
	nRet = mtx_init(&timed_recursive, mtx_timed | mtx_recursive);
	CASE_CHECK_EQ(nRet, thrd_success, "mtx_init, timed recursive, ret");
	mtx_destroy(&timed_recursive);
}

void test_mtx_trylock()
{
	int nRet = 0;
	mtx_t plain = { 0 };
	mtx_t timed = { 0 };
	mtx_t plain_recursive = { 0 };
	mtx_t timed_recursive = { 0 };
	nRet = mtx_init(&plain, mtx_plain);
	if (nRet == thrd_success)
	{
		nRet = mtx_trylock(&plain);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain, first lock)");
		nRet = mtx_trylock(&plain);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, plain, second lock)");
		mtx_destroy(&plain);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, plain, init failed");
	}

	nRet = mtx_init(&timed, mtx_timed);
	if (nRet == thrd_success)
	{
		nRet = mtx_trylock(&timed);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed, first lock");
		nRet = mtx_trylock(&timed);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, timed, second lock");
		mtx_destroy(&timed);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, timed, init failed");
	}
	nRet = mtx_init(&plain_recursive, mtx_plain | mtx_recursive);
	if (nRet == thrd_success)
	{
		nRet = mtx_trylock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain recursive, first lock");
		nRet = mtx_trylock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain recursive, second lock");

		mtx_destroy(&plain_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, plain recursive, init failed");
	}
	nRet = mtx_init(&timed_recursive, mtx_timed | mtx_recursive);
	if (nRet == thrd_success)
	{
		nRet = mtx_trylock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed recursive, first lock");
		nRet = mtx_trylock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed recursive, second lock");
		mtx_destroy(&timed_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, timed recursive, init failed");
	}
}

void test_mtx_unlock()
{
	int nRet = 0;
	mtx_t plain = { 0 };
	mtx_t timed = { 0 };
	mtx_t plain_recursive = { 0 };
	mtx_t timed_recursive = { 0 };
	nRet = mtx_init(&plain, mtx_plain);
	if (nRet == thrd_success)
	{
		mtx_trylock(&plain);
		nRet = mtx_unlock(&plain);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain, first lock)");
		nRet = mtx_unlock(&plain);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, plain, second lock)");
		mtx_destroy(&plain);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, plain, init failed");
	}
	nRet = mtx_init(&timed, mtx_timed);
	if (nRet == thrd_success)
	{
		mtx_trylock(&timed);
		nRet = mtx_unlock(&timed);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed, first lock)");
		nRet = mtx_unlock(&timed);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, timed, second lock)");
		mtx_destroy(&timed);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, timed, init failed");
	}
	nRet = mtx_init(&plain_recursive, mtx_plain | mtx_recursive);
	if (nRet == thrd_success)
	{
		mtx_trylock(&plain_recursive);
		mtx_trylock(&plain_recursive);
		nRet = mtx_unlock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain recursive, first lock)");
		nRet = mtx_unlock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, plain recursive, second lock)");
		nRet = mtx_unlock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, plain recursive, third lock)");
		mtx_destroy(&plain_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, plain recursive, init failed");
	}
	nRet = mtx_init(&timed_recursive, mtx_timed | mtx_recursive);
	if (nRet == thrd_success)
	{
		mtx_trylock(&timed_recursive);
		mtx_trylock(&timed_recursive);
		nRet = mtx_unlock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed recursive, first lock)");
		nRet = mtx_unlock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_trylock, timed recursive, second lock)");
		nRet = mtx_unlock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_trylock, timed recursive, third lock)");
		mtx_destroy(&timed_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, timed recursive, init failed");
	}
}

//int mtx_lock(mtx_t* mtx);
void test_mtx_lock()
{
	int nRet = 0;
	mtx_t plain = { 0 };
	mtx_t timed = { 0 };
	mtx_t plain_recursive = { 0 };
	mtx_t timed_recursive = { 0 };
	nRet = mtx_init(&plain, mtx_plain);
	if (nRet == thrd_success)
	{
		nRet = mtx_lock(&plain);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain, first lock)");
		nRet = mtx_trylock(&plain);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_lock, plain, second lock)");
		nRet = mtx_unlock(&plain);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain, unlock)");
		mtx_destroy(&plain);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_lock, plain, init failed");
	}

	nRet = mtx_init(&timed, mtx_timed);
	if (nRet == thrd_success)
	{
		nRet = mtx_trylock(&timed);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed, first lock");
		nRet = mtx_trylock(&timed);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_lock, timed, second lock");
		nRet = mtx_unlock(&timed);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed, unlock)");
		mtx_destroy(&timed);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_lock, timed, init failed");
	}
	nRet = mtx_init(&plain_recursive, mtx_plain | mtx_recursive);
	if (nRet == thrd_success)
	{
		nRet = mtx_lock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain recursive, first lock");
		nRet = mtx_lock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain recursive, second lock");
		nRet = mtx_unlock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain recursive, first unlock)");
		nRet = mtx_unlock(&plain_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, plain recursive, second unlock)");

		mtx_destroy(&plain_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, plain recursive, init failed");
	}
	nRet = mtx_init(&timed_recursive, mtx_timed | mtx_recursive);
	if (nRet == thrd_success)
	{
		nRet = mtx_lock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed recursive, first lock");
		nRet = mtx_lock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed recursive, second lock");
		nRet = mtx_unlock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed recursive, first unlock)");
		nRet = mtx_unlock(&timed_recursive);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_lock, timed recursive, second unlock)");
		mtx_destroy(&timed_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_trylock, timed recursive, init failed");
	}
}

void test_mtx_timedlock()
{
	int nRet = 0;
	mtx_t plain = { 0 };
	mtx_t timed = { 0 };
	mtx_t plain_recursive = { 0 };
	mtx_t timed_recursive = { 0 };
	timespec tp = { 0 };
	nRet = mtx_init(&plain, mtx_plain);
	if (nRet == thrd_success)
	{
		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&plain, &tp);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_timedlock, plain, lock fail (plain cannot lock)");
		mtx_destroy(&plain);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_timedlock, plain, init failed");
	}

	nRet = mtx_init(&timed, mtx_timed);
	if (nRet == thrd_success)
	{

		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&timed, &tp);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_timedlock, timed, first lock");
		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&timed, &tp);
		CASE_CHECK_EQ(nRet, thrd_timedout, "mtx_timedlock, timed, second lock");

		mtx_destroy(&timed);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_timedlock, timed, init failed");
	}
	nRet = mtx_init(&plain_recursive, mtx_plain | mtx_recursive);
	if (nRet == thrd_success)
	{
		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&plain_recursive, &tp);
		CASE_CHECK_EQ(nRet, thrd_error, "mtx_timedlock, plain recursive, lock fail (plain cannot lock)");

		mtx_destroy(&plain_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_timedlock, plain recursive, init failed");
	}
	nRet = mtx_init(&timed_recursive, mtx_timed | mtx_recursive);
	if (nRet == thrd_success)
	{
		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&timed_recursive, &tp);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_timedlock, timed recursive, first lock");
		timespec_get(&tp, TIME_UTC);
		tp.tv_sec += 2;
		nRet = mtx_timedlock(&timed_recursive, &tp);
		CASE_CHECK_EQ(nRet, thrd_success, "mtx_timedlock, timed recursive, second lock");
		mtx_destroy(&timed_recursive);
	}
	else
	{
		CASE_CHECK_EQ(1, 0, "mtx_timedlock, timed recursive, init failed");
	}
}


void test_thrd_current_and_sleep()
{
	timespec dur = { 0 };
	timespec rem = { 0 };
	timespec tp1 = { 0 };
	timespec tp2 = { 0 };
	int nRet;
	thrd_t curr = thrd_current();
	CASE_CHECK_NE(curr.pHandle, 0, "thrd_current, handle");
	CASE_CHECK_NE(curr.qwTid, 0, "thrd_current, tid");
	dur.tv_sec = 1;
	timespec_get(&tp1, TIME_UTC);
	nRet = thrd_sleep(&dur, &rem);
	timespec_get(&tp2, TIME_UTC);
	if (nRet == -1)
	{
		//interrupted
		CASE_CHECK_EQ(nRet, 0, "thrd_sleep, time elapsed, interrupted");
		CASE_MANUAL_CHECK_START();
		printf("thrd_sleep, remaining time = [sec = %llu, nsec = %ld]\n", rem.tv_sec, rem.tv_nsec);
		CASE_MANUAL_CHECK_END();
	}
	else if (nRet < -1)
	{
		CASE_CHECK_EQ(true, false, "thrd_sleep, failed");
	}
	else
	{
		size_t ld1 = tp1.tv_sec * 1'000'000'000 + tp1.tv_nsec;
		size_t ld2 = tp2.tv_sec * 1'000'000'000 + tp2.tv_nsec;
		CASE_CHECK_EQ(nRet, 0, "thrd_sleep, time elapsed");
		CASE_CHECK_BE(ld2 - ld1, 1'000'000'000, "time slept");
	}
}

//int thrd_create(thrd_t* thr, thrd_start_t func, void* arg);
//int thrd_equal(thrd_t thr0, thrd_t thr1);
//int thrd_detach(thrd_t thr);
static int immthrd(void* p )
{
	bool* p1 = (bool*)p;
	*p1 = true;
	timespec tp1 = { 0 };
	timespec tp2 = { 0 };
	tp1.tv_sec = 4;
	tp1.tv_nsec = 0;
	thrd_sleep(&tp1, &tp2);
	return 88;
}
void test_thrd_create_equal_detach()
{
	bool bparam = false;
	thrd_t thrd = {0};
	int nRet = thrd_create(&thrd, immthrd, &bparam);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create, success");
	if (nRet == thrd_success)
	{
		CASE_CHECK_NE(thrd_equal(thrd, thrd), 0, "thrd_equal, same");
		CASE_CHECK_EQ(thrd_equal(thrd, thrd_current()), 0, "thrd_equal, different");

		timespec tp1 = { 0 };
		timespec tp2 = { 0 };
		timespec_get(&tp1, TIME_UTC);
		size_t ld1 = tp1.tv_sec * 1'000'000'000 + tp1.tv_nsec;
		while (bparam == false)
		{
			timespec_get(&tp2, TIME_UTC);
			size_t ld2 = tp2.tv_sec * 1'000'000'000 + tp2.tv_nsec;
			if (bparam)
				break;
			else if (ld2 - ld1 > 60'000'000'000)
				break;
		}

		CASE_CHECK_EQ(bparam, true, "thrd_create, parameter set");
		nRet = thrd_detach(thrd);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_detach");
		tp2 = { 0 };
		tp1.tv_sec = 4;
		tp1.tv_nsec = 0;
		thrd_sleep(&tp1, &tp2);
	}
}

//int thrd_join(thrd_t thr, int* res);
void test_thrd_create_equal_join()
{
	bool bparam = false;
	thrd_t thrd = { 0 };
	int nThrdRet = 0;
	int nRet = thrd_create(&thrd, immthrd, &bparam);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create, success");
	if (nRet == thrd_success)
	{
		CASE_CHECK_NE(thrd_equal(thrd, thrd), 0, "thrd_equal, same");
		CASE_CHECK_EQ(thrd_equal(thrd, thrd_current()), 0, "thrd_equal, different");

		nRet = thrd_join(thrd, &nThrdRet);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_join, ret");
		CASE_CHECK_EQ(nThrdRet, 88, "thrd_join, thread ret");
		CASE_CHECK_EQ(bparam, true, "thrd_create, parameter set");

	}
}

static int trmthrd(void* p)
{
	bool* p1 = (bool*)p;
	*p1 = true;
	thrd_exit(33);
	return 88;
}
//_Noreturn void thrd_exit(int res);
void test_thrd_create_terminate_join()
{
	bool bparam = false;
	thrd_t thrd = { 0 };
	int nThrdRet = 0;
	int nRet = thrd_create(&thrd, trmthrd, &bparam);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create, success");
	if (nRet == thrd_success)
	{
		timespec tp1 = { 0 };
		timespec tp2 = { 0 };
		tp1.tv_sec = 4;
		thrd_sleep(&tp1, &tp2);


		nRet = thrd_join(thrd, &nThrdRet);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_join, ret");
		CASE_CHECK_EQ(nThrdRet, 33, "thrd_join, thread ret");
		CASE_CHECK_EQ(bparam, true, "thrd_create, parameter set");

	}
}


//int cnd_signal(cnd_t* cond);
//int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx,const struct timespec* restrict ts);
//int cnd_wait(cnd_t* cond, mtx_t* mtx);
void test_cnd_init_destroy()
{
	cnd_t cnd;
	int nRet = cnd_init(&cnd);
	CASE_CHECK_EQ(nRet, thrd_success, "cnd_init, return 1");
	cnd_destroy(&cnd);
}

struct tcstww
{
	bool b;
	mtx_t mtx;
	cnd_t cnd;
};

static int tcstww_thrd(void* param)
{
	timespec tp1 = { 0 };
	timespec tp2 = { 0 };
	tcstww* ppack = (tcstww*)param;
	cnd_signal(&ppack->cnd);
	while (!ppack->b);

	tp1.tv_sec = 1;
	tp1.tv_nsec = 0;
	thrd_sleep(&tp1, &tp2);
	cnd_signal(&ppack->cnd);

	while (!ppack->b);
	mtx_lock(&ppack->mtx);
	cnd_wait(&ppack->cnd, &ppack->mtx);
	return 11;
}

void test_cnd_signal_timed_wait_wait()
{
	tcstww pack;
	pack.b = false;
	cnd_init(&pack.cnd);
	mtx_init(&pack.mtx, mtx_timed);
	thrd_t thrd = { 0 };
	int nRet = thrd_create(&thrd, tcstww_thrd, &pack);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create, success");
	if (nRet == thrd_success)
	{
		mtx_lock(&pack.mtx);
		nRet = cnd_wait(&pack.cnd, &pack.mtx);
		CASE_CHECK_EQ(nRet, thrd_success, "cnd_wait, ret");

		timespec tp1 = { 0 };
		timespec tp2 = { 0 };
		timespec_get(&tp1, TIME_UTC);
		tp1.tv_sec += 4;
		mtx_lock(&pack.mtx);
		
		nRet = cnd_timedwait(&pack.cnd, &pack.mtx, &tp1);
		CASE_CHECK_EQ(nRet, thrd_timedout, "cnd_timedwait, timeout");
		pack.b = true;

		tp1 = { 0 };
		timespec_get(&tp1, TIME_UTC);
		tp1.tv_sec += 4;
		mtx_lock(&pack.mtx);
		nRet = cnd_timedwait(&pack.cnd, &pack.mtx, &tp1);
		CASE_CHECK_EQ(nRet, thrd_success, "cnd_timedwait, no timeout");
		pack.b = true;

		tp1.tv_sec = 4;
		tp1.tv_nsec = 0;
		thrd_sleep(&tp1, &tp2);

		nRet = cnd_signal(&pack.cnd);
		CASE_CHECK_EQ(nRet, thrd_success, "cnd_signal, ret");

		int nRes = 0;
		nRet = thrd_join(thrd, &nRes);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_join, ret");
		CASE_CHECK_EQ(nRes, 11, "thrd_join, thread ret");
	}
	cnd_destroy(&pack.cnd);
	mtx_destroy(&pack.mtx);
}

struct tcbdb
{
	bool blk;
	bool bsig;
	mtx_t* pmtx;
	cnd_t* pcnd;
};
int tcndb_thrd(void* p)
{
	tcbdb* pack = (tcbdb*)p;
	pack->blk = true;
	mtx_lock(pack->pmtx);
	cnd_wait(pack->pcnd, pack->pmtx);
	pack->bsig = true;
	return 44;
}

//int cnd_broadcast(cnd_t* cond);
void test_cnd_broadcast()
{
	mtx_t mtx;
	cnd_t cnd;
	mtx_init(&mtx, mtx_timed);
	cnd_init(&cnd);
	tcbdb pack1;
	tcbdb pack2;
	pack1.blk = false;
	pack1.bsig = false;
	pack1.pcnd = &cnd;
	pack1.pmtx = &mtx;
	pack2.blk = false;
	pack2.bsig = false;
	pack2.pcnd = &cnd;
	pack2.pmtx = &mtx;
	thrd_t thrd1;
	thrd_t thrd2;
	int nRet = thrd_create(&thrd1, tcndb_thrd, &pack1);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create 1, success");
	nRet = thrd_create(&thrd2, tcndb_thrd, &pack2);
	CASE_CHECK_EQ(nRet, thrd_success, "thrd_create 2, success");

	if (nRet == thrd_success)
	{
		while (!pack1.blk);
		while (!pack2.blk);

		timespec tp1 = { 0 };
		timespec tp2 = { 0 };
		tp1.tv_sec = 1;
		tp1.tv_nsec = 0;
		thrd_sleep(&tp1, &tp2);

		nRet = cnd_broadcast(&cnd);
		CASE_CHECK_EQ(nRet, thrd_success, "cnd_broadcast, ret");

		int nRes = 0;
		nRet = thrd_join(thrd1, &nRes);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_join 1, ret");
		CASE_CHECK_EQ(nRes, 44, "thrd_join 1, thread ret");
		nRet = thrd_join(thrd2, &nRes);
		CASE_CHECK_EQ(nRet, thrd_success, "thrd_join 2, ret");
		CASE_CHECK_EQ(nRes, 44, "thrd_join 2, thread ret");

		CASE_CHECK_EQ(pack1.bsig, true, "thread 1, got broadcast");
		CASE_CHECK_EQ(pack2.bsig, true, "thread 2, got broadcast");
	}
	cnd_destroy(&cnd);
	mtx_destroy(&mtx);
}


//int tss_create(tss_t* key, tss_dtor_t dtor);
//void tss_delete(tss_t key);
//void* tss_get(tss_t key);
//int tss_set(tss_t key, void* val);

void test_tss_all_local()
{
	tss_t key1 = { 0 };
	tss_t key2 = { 0 };
	int nRet = tss_create(&key1, 0);
	CASE_CHECK_EQ(nRet, thrd_success, "tss_create, return");
	if (nRet == thrd_success)
	{
		uint64_t tssval1 = 0x12345678llu;
		uint64_t tssval2 = 0;

		nRet = tss_set(key1, (void*)tssval1);
		CASE_CHECK_EQ(nRet, thrd_success, "tss_set, return");

		tssval2 = (uint64_t)tss_get(key1);
		CASE_CHECK_EQ(tssval1, tssval2, "tss_get, tssval1 == tssval2");


		tss_delete(key1);
		nRet = tss_create(&key2, 0);
		CASE_CHECK_EQ(nRet, thrd_success, "tss_create, return");
		tss_delete(key2);
		CASE_CHECK_EQ(key1.dwIdx, key2.dwIdx, "tss_create, k1 == k2");
	}
}
void ttssallr_dtor(void* p)
{
	bool* b = (bool*)p;
	if(b)
		*b = true;
}

struct ttssallr_pack {
	void* p;
	tss_t key;
};

int ttssallr_thrd(void* p)
{
	ttssallr_pack* pack = (ttssallr_pack*)p;
	tss_set(pack->key, pack->p);
	return 2;
}


void test_tss_all_remote()
{
	bool bDtorCalled = false;
	tss_t key1 = { 0 };
	ttssallr_pack pack;
	int nRet = tss_create(&key1, ttssallr_dtor);
	CASE_CHECK_EQ(nRet, thrd_success, "tss_create, return");
	if (nRet == thrd_success)
	{
		pack.key = key1;
		pack.p = &bDtorCalled;
		thrd_t thrd1;
		nRet = thrd_create(&thrd1, ttssallr_thrd, &pack);
		if (nRet == thrd_success)
		{
			int nRes = 0;

			thrd_join(thrd1, &nRes);
			CASE_CHECK_EQ(nRes, 2, "thrd_join, res");
		}
		tss_delete(key1);
		CASE_CHECK_EQ(bDtorCalled, true, "destructor called");
	}
}


void test_threads()
{
	printf("\ntest suite threads:\n");

	test_tss_all_local();
	test_tss_all_remote();
	test_call_once();
	test_mtx_init_destroy();
	test_mtx_trylock();
	test_mtx_timedlock();
	test_mtx_unlock();
	test_mtx_lock();
	test_thrd_current_and_sleep();
	test_thrd_create_equal_detach();
	test_thrd_create_equal_join();
	test_thrd_create_terminate_join();
	test_cnd_init_destroy();
	test_cnd_signal_timed_wait_wait();
	test_cnd_broadcast();
	return;
}