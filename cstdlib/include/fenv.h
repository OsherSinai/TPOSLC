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
#ifndef TOS_FLOATING_POINT_ENV_H
#define TOS_FLOATING_POINT_ENV_H

#include "stddef.h"

#define FE_DIVBYZERO (0x04)
#define FE_INEXACT (0x20)
#define FE_INVALID (0x01)
#define FE_OVERFLOW (0x08)
#define FE_UNDERFLOW (0x10)
#define FE_ALL_EXCEPT (FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

#define FE_DOWNWARD 1
#define FE_TONEAREST 0
#define FE_TOWARDZERO 3
#define FE_UPWARD 2


typedef uint32_t fenv_t[2];
typedef uint32_t fexcept_t;
// There isn't really a way to reenable actual exceptions on floating error as it can break quite a lot
// If you (me probably) intend to use exceptions emulate it with fetestexcept
// TODO: add macros/functions to enable specific exception in an fenv_t
#define FE_DEF_ENV {0x1f80u, 0x133fu}

LIBC_DEF_BEGIN
int feclearexcept(int excepts);
int fegetexceptflag(fexcept_t* flagp,
	int excepts);
int feraiseexcept(int excepts);
int fesetexceptflag(const fexcept_t* flagp,
	int excepts);
int fetestexcept(int excepts);
int fegetround(void);
int fesetround(int round);
int fegetenv(fenv_t* envp);
int feholdexcept(fenv_t* envp);
int fesetenv(const fenv_t* envp);
int feupdateenv(const fenv_t* envp);
LIBC_DEF_END
#endif // !TOS_FLOATING_POINT_ENV_H
