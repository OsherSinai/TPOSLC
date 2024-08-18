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
#include "TOSThreadEnvironmentBlock.h"
#include <include\stdlib.h>
#ifdef _WIN32
#include "win32/win32_ntdll.h"
LIBC_DEF_BEGIN
#define DLL_PROCESS_ATTACH   1    
#define DLL_THREAD_ATTACH    2    
#define DLL_THREAD_DETACH    3    
#define DLL_PROCESS_DETACH   0   

typedef void
(*PIMAGE_TLS_CALLBACK) (
    void* DllHandle,
    uint32_t Reason,
    void* Reserved
    );

#ifdef _WIN32


#define _CRTALLOC(x) __declspec(allocate(x))
typedef void(*_PVFV)();

thread_local bool __tls_guard = false;


static _CRTALLOC(".CRT$XDA") _PVFV __xd_a;
static _CRTALLOC(".CRT$XDZ") _PVFV __xd_z;

void __dyn_tls_init(void*, uint32_t dwReason, void*) 
{
    if (dwReason != DLL_THREAD_ATTACH || __tls_guard == true)
        return;

    for (_PVFV* pFunc = &__xd_a; pFunc != &__xd_z; ++pFunc)
    {
        if (*pFunc)
            (*pFunc)();
    }
    __tls_guard = true;
}
void __dyn_tls_on_demand_init() 
{
    __dyn_tls_init(nullptr, DLL_THREAD_ATTACH, nullptr);
}

extern const PIMAGE_TLS_CALLBACK __dyn_tls_init_callback = __dyn_tls_init;
static _CRTALLOC(".CRT$XLC") PIMAGE_TLS_CALLBACK __xl_c = __dyn_tls_init;
extern "C" uint32_t _tls_index = 0;
unsigned long __safe_get_tls_index() 
{
    __dyn_tls_on_demand_init();

    return _tls_index;
}
#endif // _WIN32




//check if need to add the tlsdtor and tlssup

thread_local tos_thread_environment_block tos_teb = { 0 };
tos_thread_environment_block* _tos_GetTEB()
{
    return &(tos_teb);
}
LIBC_DEF_END
#endif // _WIN32