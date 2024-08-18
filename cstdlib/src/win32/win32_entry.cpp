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
#include <include\stdint.h>
#include <include\stddef.h>
#include <include\string.h>
#include <include\stdlib.h>
#include <include\stdio.h>
#include <include\stdnoreturn.h>
#include <include\except.h>
#include "win32_base.h"
#include "win32_except.h"
#include "win32_memory.h"
#include "../ProcessInitializers.h"
#include "../x86_msr.h"
#pragma weak main
//EX/
//https://drdobbs.com/packing-dlls-in-your-exe/184416443
//https://web.archive.org/web/20030810214010/http://www.microsoft.com/msj/0197/exception/exception.aspx
//https://learn.microsoft.com/en-us/archive/msdn-magazine/2001/september/under-the-hood-new-vectored-exception-handling-in-windows-xp
extern "C" int main(int argc, char* argv[]);
extern "C" void _tos_initialize_locale();


/*
#define STATUS_FLOAT_DENORMAL_OPERAND 0xC000008D
#define STATUS_FLOAT_DIVIDE_BY_ZERO 0xC000008E
#define STATUS_FLOAT_INEXACT_RESULT 0xC000008F
#define STATUS_FLOAT_INVALID_OPERATION 0xC0000090
#define STATUS_FLOAT_OVERFLOW 0xC0000091
#define STATUS_FLOAT_STACK_CHECK 0xC0000092
#define STATUS_FLOAT_UNDERFLOW 0xC0000093
#define STATUS_STACK_OVERFLOW 0xC00000FD
*/
extern "C" __declspec(dllimport) void
KiUserExceptionDispatcher(
    PEXCEPTION_RECORD ExceptionRecord,
    CONTEXT* ContextFrame
);
extern "C" void _tos_longjump_exception();
extern "C" int _tos_win32_signal_exception_propagator(DWORD ExceptionCode);

void
InnerKiUserExceptionDispatcher(
    PEXCEPTION_RECORD ExceptionRecord,
    CONTEXT* ContextFrame
)
{
    _tos_win32_signal_exception_propagator(ExceptionRecord->ExceptionCode);
    _tos_exception te = {0};
    //the throw wont be caught here, it will propagate to the next layer of try/except pair
    TOS_THROW(te);
}


static void
Inner_kued_Wrapper()
{
    __asm {
        cld
        mov rcx, rsp
        add rcx, 4f0h
        ; mov qword ptr[ExceptionRecord], rax; ExceptionRecord
        mov rdx, rsp
        ; mov qword ptr[ContextFrame], rax; ContextFrame
        call InnerKiUserExceptionDispatcher
    }
    //InnerKiUserExceptionDispatcher(ExceptionRecord, ContextFrame);
}
int DoDirtyThingsToNTDLL()
{
    int nRet = -1;
    void* p = (void*)KiUserExceptionDispatcher;
    uint8_t bytecode[] = {
        0x48, 0xb8, //mov rax, 
        0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, //func addr
        0xff,0xe0 // jmp
    };
    uint64_t Trampoline = (uint64_t)((void*)Inner_kued_Wrapper);
    uint32_t old = 0;
    uint32_t ignore = 0;
    *((uint64_t*)&bytecode[2]) = Trampoline;
    WinNtStatus stat = Win32NtProtectVirtualMemory(p, sizeof(bytecode), PAGE_READWRITE, &old);
    if (stat == WinNtStatus::Success)
    {
        memcpy(p, bytecode, sizeof(bytecode));
        stat = Win32NtProtectVirtualMemory(p, sizeof(bytecode), old, &ignore);
        nRet = 0;
    }
    return nRet;
}

#define DEFAULT_SECURITY_COOKIE ((uintptr_t)0x00002B992DDFA232)
#define CACHE_LINE_SIZE 64
extern "C" union __declspec(align(CACHE_LINE_SIZE)) {
    uintptr_t value;
} __security_cookie = { DEFAULT_SECURITY_COOKIE };


extern "C" void __security_check_cookie(uintptr_t sc) {
    if(__security_cookie.value != sc || 
        ((sc >> 48) & 0xFFFF) != 0)
    {
        // exit
        //TODO: Add signal for security fail
    }
}
extern "C" int _fltused{ 0x9875 };


extern "C" uint64_t __get_entropy()
{
    uint64_t Entropy;
    FILETIME ft = { {0} };
    LARGE_INTEGER le;
    GetSystemTimeAsFileTime(&ft);
    Entropy = ft.QWord ^
        GetCurrentProcessId(GetCurrentProcess()) ^
        GetCurrentThreadId();
    SyscallNtQueryPerformanceCounter(&le);
    Entropy =
        ((uint64_t)le.dwLow << 32) ^
        le.QWord ^
        (uint64_t)&Entropy;
    Entropy &= 0xffffffffffff;
    return Entropy;
}
extern "C" void __security_init_cookie()
{
    if ((__security_cookie.value == 0) || (__security_cookie.value == DEFAULT_SECURITY_COOKIE)) {
        
        uint64_t NewCookie = __get_entropy();
        if (NewCookie == DEFAULT_SECURITY_COOKIE)
            NewCookie = DEFAULT_SECURITY_COOKIE + 1;
        __security_cookie.value = NewCookie;
    }
}

static wchar_t* FindNonSpace(wchar_t* pWstr)
{
    while ((*pWstr != L'\0') && (*pWstr == L' '))
        pWstr++;
    if (*pWstr == L'\0')
        pWstr = NULL;
    return pWstr;
}

//TODO: use proper conversion from uchar
static wchar_t* GetNextArg(wchar_t* pWstr, wchar_t** ppStart, int* pSize, char** ppTarget)
{
    wchar_t* pNext = NULL;
    bool bQuoteOpened = false;
    int ActualSize = 0;
    char* pTarget = NULL;
    *pSize = ActualSize;
    pNext = FindNonSpace(pWstr);
    *ppStart = pNext;
    if (ppTarget)
        pTarget = *ppTarget;
    if (pNext)
    {
        while (*pNext != L'\0')
        {
            if (!bQuoteOpened)
            {
                if (*pNext == L' ')
                    break;
                else if (*pNext == L'\"')
                    bQuoteOpened = true;
                else
                {
                    ActualSize++;
                    if (pTarget)
                    {
                        *pTarget = (char)*pNext;
                        pTarget++;
                    }
                }
            }
            else
            {
                if (*pNext == L'\"')
                    bQuoteOpened = false;
                else
                {
                    ActualSize++;
                    if (pTarget)
                    {
                        *pTarget = (char)*pNext;
                        pTarget++;
                    }
                }
            }
            pNext++;
        }
    }
    *pSize = ActualSize;
    if (pNext && *pNext == L'\0')
        pNext = NULL;
    if (ppTarget)
    {
        *pTarget = '\0';
        pTarget++;
        *ppTarget = pTarget;
    }
    return pNext;
}

static wchar_t* GetUnicodeCommandlineBuffer()
{
    RTL_USER_PROCESS_PARAMETERS* pRtl;
    __asm {
        mov rax, qword ptr gs : [60h]
        mov rax, qword ptr[rax + 20h]
        mov qword ptr[pRtl], rax
    }
    return pRtl->CommandLine.Buffer;
}

static int CountArgc(size_t *pTotalSize)
{
    int Ret = 0;
    wchar_t* pch = GetUnicodeCommandlineBuffer();

    int StrSize = 0;
    wchar_t* pStart = NULL;
    wchar_t* pCurr = pch;
    *pTotalSize = 0;
    while (pCurr)
    {
        pCurr = GetNextArg(pCurr, &pStart, &StrSize, NULL);
        if (StrSize)
        {
            *pTotalSize += StrSize + 1;
            Ret++;
        }
    }
    return Ret;
}
static bool CreateArgv(char*** pArgv, int* pArgc)
{
    *pArgv = 0;
    *pArgc = 0;
    bool bRet = false;
    size_t TotalSize = 0;

    int Argc = CountArgc(&TotalSize);
    char** Argv = (char**)malloc(sizeof(char*) * (Argc + 1));
    if (Argv)
    {
        Argv[0] = (char*)malloc(TotalSize);
        if (Argv[0])
        {
            char* pTarget = Argv[0];
            int StrSize = 0;
            wchar_t* pStart = NULL;
            wchar_t* pCurr = GetUnicodeCommandlineBuffer();
            for (int i = 0; i < Argc; i++)
            {
                Argv[i] = pTarget;
                pCurr = GetNextArg(pCurr, &pStart, &StrSize, &pTarget);
            }
            Argv[Argc] = 0;
            *pArgv = Argv;
            *pArgc = Argc;
            bRet = true;
        }
    }
    return bRet;
}

static void DestroyArgv(char** Argv)
{
    if (Argv)
    {
        if (Argv[0])
            free(Argv[0]);
        free(Argv);
    }
}
extern void _tos_Initialize_stdio();

extern "C" char** g_argv = NULL;
extern "C" int g_argc = 0;
void noreturn tos_invoke_main()
{
    int nMainRet = -1;
    int argc = 0;
    char** argv = NULL;

    _tos_InitializeProcess();
    //_tos_InitializeThread();
    CreateArgv(&argv, &argc);
    g_argv = argv;
    g_argc = argc;
    TOS_TRY
    if (argv && argc)
    {
        nMainRet = main(argc, argv);
    }
    TOS_EXCEPT_UNIVERSAL
        fprintf(stderr, "\n(invoke_main): Caught crash in main\n");
    TOS_TRY_FINISH
    DestroyArgv(g_argv);

    //_tos_UninitializeThread();
    _tos_UninitializeProcess();
    _Exit(nMainRet);
}

//wWinMainCRTStartup;
extern "C" void __dyn_tls_init(void*, uint32_t dwReason, void*);
extern "C" DWORD mainCRTStartup(LPVOID p)
{
//    __dyn_tls_init(0, 888, 0);
    tos_invoke_main();
    return 0;
}
