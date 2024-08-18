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
#ifndef TOS_SIGNAL_H
#define TOS_SIGNAL_H

#include "stddef.h"
#include "stdatomic.h"

typedef volatile atomic_int sig_atomic_t;
typedef void(*TOSSignalHandler)(int);
#define SIG_ERR ((TOSSignalHandler)-1)
#define SIG_DFL ((TOSSignalHandler)0)     // default signal action
#define SIG_IGN ((TOSSignalHandler)1)     // ignore signal

//Windows signal entries
#define SIGINT          2   // interrupt
#define SIGILL          4   // illegal instruction - invalid function image
#define SIGABRT_COMPAT  6   // SIGABRT compatible with other platforms, same as SIGABRT
#define SIGFPE          8   // floating point exception
#define SIGSEGV         11  // segment violation
#define SIGTERM         15  // Software termination signal from kill
#define SIGABRT         22  // abnormal termination triggered by abort call

LIBC_DEF_BEGIN
void (*signal(int sig, void (*func)(int)))(int);
int raise(int sig);
LIBC_DEF_END
#endif // !TOS_SIGNAL_H
