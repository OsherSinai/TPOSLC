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
#ifndef TOS_LOCK_H
#define TOS_LOCK_H

#include <include\stddef.h>

typedef volatile uint32_t tos_lock;
typedef volatile uint64_t tos_lock64;

#define STATIC_INITIALIZE_TOS_LOCK (0)
#define STATIC_INITIALIZE_TOS_LOCK64 (0llu)

LIBC_DEF_BEGIN
	
void InitializeLock(tos_lock* pLock);
int TryAquireLock(tos_lock* pLock);
void AquireLock(volatile tos_lock* pLock);
int FreeLock(volatile tos_lock* pLock);


void InitializeLock64(tos_lock64* pLock);
uint64_t TryAquireLock64(tos_lock64* pLock, uint64_t val);
void AquireLock64(tos_lock64* pLock, uint64_t val);
void FreeLock64(tos_lock64* pLock, uint64_t val);

LIBC_DEF_END

#endif // !TOS_LOCK_H
