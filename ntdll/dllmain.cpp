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
#include "pch.h"
//Functions in this DLL are just dummy functions so we'll have the reference to the exception dispatcher
#define DEFAULT_SECURITY_COOKIE ((uintptr_t)0x00002B992DDFA232)
uintptr_t __security_cookie = DEFAULT_SECURITY_COOKIE;
extern "C" void __security_check_cookie(uintptr_t sc) {
    if (__security_cookie != sc ||
        ((sc >> 48) & 0xFFFF) != 0)
    {
        // exit
        //TODO: Add signal for security fail
    }
}

extern "C" __declspec(dllexport) void
KiUserExceptionDispatcher(
    PEXCEPTION_RECORD ExceptionRecord,
    CONTEXT* ContextFrame
)
{

}