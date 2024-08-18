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
#include "ProcessInitializers.h"
/*
extern "C" void _tos_initialize_locale()
extern void _tos_Initialize_stdio();
extern "C" int _tos_initialize_environ();
extern "C" int _tos_initialize_time();
extern "C" void _tos_initialize_tss_program_dtors();
extern "C" void _tos_initialize_peb_signal_handler();
extern "C" void _tos_uninitialize_environment();
extern "C" int _tos_initialize_tss_thread_tss();
extern "C" int _tos_uninitialize_tss_thread_tss();
extern "C" void _tos_tss_call_thread_dtors();
extern "C" void _tos_uninitialize_time();

void _tos_Uninitialize_stdio()
*/


/*
initialize:
    windows
    __security_init_cookie(); win32
    DoDirtyThingsToNTDLL(); win32
    _tos_Initialize_stdio();
    _tos_initialize_locale();
	_tos_initialize_environ();
    _tos_initialize_time();
    _tos_initialize_tss_program_dtors();
    CreateArgv(&argv, &argc);


uninitialize:
	close and flush files
    _tos_initialize_tss_thread_tss();
    _tos_uninitialize_environment();
*/
//TODO: add custom structured exception

#ifdef _WIN32
extern "C" void __security_init_cookie();
extern int DoDirtyThingsToNTDLL();
extern "C" int _tos_InitializeSyscallTable();
#endif

extern void _tos_Initialize_stdio();
extern "C" void _tos_initialize_locale();
extern "C" int _tos_initialize_environ();
extern "C" int _tos_initialize_time();
extern "C" void _tos_initialize_tss_program_dtors();


extern "C" void _tos_InitializeException();
extern "C" void _tos_UninitializeException();
extern "C" void _tos_Initialize_rand();
extern "C" void _tos_InitializePrimaryThreadData();

extern "C" void _tos_initialize_peb_signal_handler();
extern "C" int _tos_initialize_tss_thread_tss();
extern "C" void _tos_InitializeFloatingPointEnvironment();

extern "C" void _tos_tss_call_thread_dtors();
extern "C" int _tos_uninitialize_tss_thread_tss();

int _tos_InitializeProcess()
{
    int nRet = 0;
#ifdef _WIN32
    __security_init_cookie();
    nRet = _tos_InitializeSyscallTable();
    if (nRet)
        goto cleanup;
    nRet = DoDirtyThingsToNTDLL();
    if (nRet)
        goto cleanup;
#endif
    nRet = _tos_initialize_environ();
    if (nRet)
        goto cleanup;

    _tos_initialize_tss_program_dtors();
    _tos_Initialize_stdio();
    _tos_initialize_locale();
    nRet = _tos_initialize_time();
    if (nRet)
        goto cleanup;
    _tos_InitializePrimaryThreadData();
    _tos_Initialize_rand();

    _tos_InitializeException();
    _tos_initialize_peb_signal_handler();
    _tos_InitializeFloatingPointEnvironment();
    nRet = _tos_initialize_tss_thread_tss();

cleanup:
    return nRet;
}

extern "C" void _tos_uninitialize_time();
extern "C" void _tos_uninitialize_environment();
extern "C" void _tos_UninitializePrimaryThreadData();

void _tos_UninitializeProcess()
{
    _tos_UninitializeException();
    _tos_tss_call_thread_dtors();
    _tos_uninitialize_tss_thread_tss();
    //TODO: add files cleanup
    _tos_UninitializePrimaryThreadData();
    _tos_uninitialize_time();
    _tos_uninitialize_environment();
}

/*
initialize:
	initialize tls and resources
	_tos_initialize_peb_signal_handler();
    _tos_initialize_tss_thread_tss();
uninitialize:
	free tls and resources
    _tos_tss_call_thread_dtors();
    _tos_uninitialize_tss_thread_tss();
*/
extern "C" int _tos_InitializeStaticTls(void** ppOld);
extern "C" void _tos_UninitializeStaticTls(void** ppOld);
int _tos_InitializeThread(void** pStaticTlsBuffer)
{
    int nRet;
    nRet = _tos_InitializeStaticTls(pStaticTlsBuffer);
    if (nRet != 0)
        goto cleanup;
    _tos_InitializeException();
    _tos_initialize_peb_signal_handler();
    _tos_InitializeFloatingPointEnvironment();
    nRet = _tos_initialize_tss_thread_tss();
cleanup:
    return nRet;
}
void _tos_UninitializeThread(void** pStaticTlsBuffer)
{
    //will be called before the thread join _tos_tss_call_thread_dtors();
    _tos_UninitializeException();
    _tos_uninitialize_tss_thread_tss();
    _tos_UninitializeStaticTls(pStaticTlsBuffer);
}