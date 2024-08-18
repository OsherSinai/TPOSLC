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
#ifndef TOS_THREADS_H
#define TOS_THREADS_H
#include "stddef.h"
#include "time.h"
#ifndef __cplusplus
#define thread_local _Thread_local
#endif // !__cplusplus

#define TOS_MIN_TSS_IDX 1088

#define ONCE_FLAG_INIT {0}
#define TSS_DTOR_ITERATIONS 1

typedef struct {
	void* pHandle;
} cnd_t;
typedef struct {
	void* pHandle;
	uint64_t qwTid;
} thrd_t;
typedef struct {
	uint32_t dwIdx;
} tss_t;


typedef struct _tos_mtx_base {
	uint8_t bRecursive : 1;
	uint8_t bTimed : 1;
}tos_mtx_base;
typedef struct {
	tos_mtx_base* pBase;
} mtx_t;
typedef struct {
	uint32_t reserve;
} once_flag;
typedef void(*tss_dtor_t)(void*);
typedef int(*thrd_start_t)(void*);
enum { mtx_plain, mtx_recursive, mtx_timed};
enum { thrd_success, thrd_nomem, thrd_timedout, thrd_busy, thrd_error };

LIBC_DEF_BEGIN

int cnd_broadcast(cnd_t* cond);
void cnd_destroy(cnd_t* cond);
int cnd_init(cnd_t* cond);
int cnd_signal(cnd_t* cond);
int cnd_timedwait(cnd_t* restrict cond, mtx_t* restrict mtx,
	const struct timespec* restrict ts);
int cnd_wait(cnd_t* cond, mtx_t* mtx);

/* mutex.cpp */
void mtx_destroy(mtx_t* mtx);
int mtx_init(mtx_t* mtx, int type);
int mtx_lock(mtx_t* mtx);
int mtx_timedlock(mtx_t* restrict mtx, const struct timespec* restrict ts);
int mtx_trylock(mtx_t* mtx);
int mtx_unlock(mtx_t* mtx);

/* threads.cpp */
void call_once(once_flag* flag, void (*func)(void));
int thrd_create(thrd_t* thr, thrd_start_t func, void* arg);
thrd_t thrd_current();
int thrd_detach(thrd_t thr);
int thrd_equal(thrd_t thr0, thrd_t thr1);
_Noreturn void thrd_exit(int res);
int thrd_join(thrd_t thr, int* res);
int thrd_sleep(const struct timespec* duration, struct timespec* remaining);
void thrd_yield();

/* thread_specific_storage.cpp */
int tss_create(tss_t* key, tss_dtor_t dtor);
void tss_delete(tss_t key);
void* tss_get(tss_t key);
int tss_set(tss_t key, void* val);

LIBC_DEF_END
#endif // !TOS_THREADS_H
