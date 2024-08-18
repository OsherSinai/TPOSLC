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
#ifndef TOS_WIN32_BASE_H
#define TOS_WIN32_BASE_H
#include <include\stddef.h>
typedef int64_t LONG_PTR, * PLONG_PTR;
typedef uint64_t ULONG_PTR, * PULONG_PTR;
typedef uint64_t ULONG64, * PULONG64;
typedef uint64_t DWORD64, * PDWORD64;
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;
typedef uint16_t USHORT;


typedef void* HANDLE;
typedef void* PVOID;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT* PFLOAT;
typedef BOOL * PBOOL;
typedef BOOL * LPBOOL;
typedef BYTE * PBYTE;
typedef BYTE * LPBYTE;
typedef int * PINT;
typedef int * LPINT;
typedef WORD * PWORD;
typedef WORD * LPWORD;
typedef long * LPLONG;
typedef DWORD * PDWORD;
typedef DWORD * LPDWORD;
typedef void * LPVOID;
typedef const void * LPCVOID;
typedef BYTE  BOOLEAN;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int* PUINT;
typedef unsigned long ULONG;
typedef ULONG* PULONG;
typedef long LONG;
typedef LONG NTSTATUS;
typedef wchar_t WCHAR;
typedef WCHAR* NWPSTR, * LPWSTR, * PWSTR;
#define NTAPI __stdcall
#define NtCurrentThread() ((void*)((size_t)-2))
#define NtCurrentProcess() ((void*)((size_t)-1))

#define TRUE 1
#define FALSE 0

typedef struct __declspec(align(16)) _M128A {
    ULONGLONG Low;
    LONGLONG High;
} M128A, * PM128A;
typedef struct __declspec(align(16)) _XSAVE_FORMAT {
    WORD   ControlWord;
    WORD   StatusWord;
    BYTE  TagWord;
    BYTE  Reserved1;
    WORD   ErrorOpcode;
    DWORD ErrorOffset;
    WORD   ErrorSelector;
    WORD   Reserved2;
    DWORD DataOffset;
    WORD   DataSelector;
    WORD   Reserved3;
    DWORD MxCsr;
    DWORD MxCsr_Mask;
    M128A FloatRegisters[8];

    M128A XmmRegisters[16];
    BYTE  Reserved4[96];

} XSAVE_FORMAT, * PXSAVE_FORMAT;
typedef XSAVE_FORMAT XMM_SAVE_AREA32, * PXMM_SAVE_AREA32;


enum class WinNtStatus {
    Success,
    AccessDenied,
    AlreadyCommitted,
    CommitmentLimit,
    ConflictingAddress,
    InsufficientResources,
    InvalidHandle,
    InvalidPageProtection,
    NoMemory,
    ObjectTypeMismatch,
    ProcessIsTerminating,
    NotCloseable,
    HandleNotCloseable,
    PathSyntaxBad,
    ObjectNameInvalid,
    EndOfFile,
    Unknown

};
#endif // !WIN32_BASE_H
