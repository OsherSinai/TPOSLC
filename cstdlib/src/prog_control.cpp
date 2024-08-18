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
#include <include\stdlib.h>
#include <include\signal.h>
#include <include\string.h>


#if defined(TOS_KERNEL)
#error No other OSs are supported at this time (prog_control.cpp)
#elif defined(_WIN32)
#include "win32/win32_except.h"
extern "C" NTSTATUS SyscallNtTerminateProcess(uint64_t Handle, NTSTATUS Status);
#else
#error No other OSs are supported at this time (prog_control.cpp)
#endif

size_t _environ_data_ptrs = 0;
char** _environ = 0;
wchar_t** _wenviron = 0;

static size_t count_needed_ptrs_in_environ_win32(wchar_t* pEnvironment, size_t size)
{
	size_t ret = 1;
	size_t totalst = 0;
	size_t i = 0;
	size_t currlen = 0;
	while (totalst < size)
	{
		wchar_t wch = pEnvironment[i];
		if (wch == 0)
		{
			if (currlen)
				ret++;
			currlen = 0;
		}
		else
		{
			currlen++;
		}
		totalst += 2;
		i++;
	}

	return ret;
}

static wchar_t** allocate_needed_ptr_array(wchar_t* pEnvironment, size_t size, size_t count)
{
	wchar_t** pRet = (wchar_t**)malloc(sizeof(wchar_t*) * count);
	if (pRet)
	{
		memset(pRet, 0, sizeof(wchar_t*) * count);
		wchar_t* pStart = pEnvironment;
		size_t totalst = 0;
		size_t i = 0;
		size_t currlen = 0;
		size_t curridx = 0;
		while (totalst < size)
		{
			wchar_t wch = pEnvironment[i];
			if (wch == 0)
			{
				if (currlen)
				{
					pRet[curridx] = pStart;
					curridx++;
				}
				currlen = 0;
				pStart = &pEnvironment[i + 1];
			}
			else
			{
				currlen++;
			}
			totalst += 2;
			i++;
		}
	}
	return pRet;
}

extern "C" int _tos_initialize_environ()
{
	int nSuccess = 0;
	wchar_t** ppEnvironment;
	wchar_t* pEnvironment;
	ULONG_PTR* pEnvironmentSize;
	ULONG_PTR* pEnvironmentVersion;
#ifdef _WIN32
	__asm {
		mov rax, gs: [60h]
		mov rax, [rax + 20h]
		mov rbx, rax

		mov rax, rbx
		add rax, 080h
		mov qword ptr[ppEnvironment], rax
		mov rax, rbx
		add rax, 03F8h
		mov qword ptr[pEnvironmentVersion], rax
		mov rax, rbx
		add rax, 03F0h
		mov qword ptr[pEnvironmentSize], rax
	}


	pEnvironment = *ppEnvironment;

	_environ_data_ptrs = count_needed_ptrs_in_environ_win32(pEnvironment, *pEnvironmentSize);
	if (_environ_data_ptrs != 0)
	{

		_wenviron = allocate_needed_ptr_array(pEnvironment, *pEnvironmentSize, _environ_data_ptrs);
		if (_wenviron)
		{
			_environ = (char**)malloc(_environ_data_ptrs * sizeof(char*));
			if (_environ)
			{
				size_t NeededSizeForEnv = 0;
				for (size_t i = 0; i < _environ_data_ptrs; i++)
				{
					const wchar_t* ptr = _wenviron[i];
					mbstate_t state = { 0 };
					size_t rt = wcsrtombs(NULL, &ptr, (size_t)~0, &state);
					if (rt >= 0)
					{
						NeededSizeForEnv += rt + 1;
					}
				}
				NeededSizeForEnv += 2;
				size_t RemainingBytes = NeededSizeForEnv;
				char* save = (char*)malloc(sizeof(char) * NeededSizeForEnv);
				_environ[0] = save;
				_environ[_environ_data_ptrs - 1] = NULL;

				for (size_t i = 0; i < _environ_data_ptrs; i++)
				{
					const wchar_t* ptr = _wenviron[i];
					_environ[i] = save;
					mbstate_t state = { 0 };
					size_t rt = wcsrtombs(save, &ptr, RemainingBytes, &state);
					if (rt >= 0)
					{
						save += rt + 1;
					}
					else
					{
						*save = '\0';
						save++;
					}
				}

			}
			else
			{
				nSuccess = -1;
				free(_wenviron);
				_wenviron = NULL;
			}
		}
		else
			nSuccess = -1;
	}
	else
		nSuccess = -1;

#else
#error _tos_initialize_environ not implemented (prog_control.cpp)
#endif // _WIN32
	return nSuccess;
}
extern "C" void _tos_uninitialize_environment()
{
	if (_environ)
	{
#ifdef _WIN32
		if (_environ[0])
			free(_environ[0]);
#endif // _WIN32
		free(_environ);
		_environ = NULL;
	}
	if (_wenviron)
	{
#ifndef _WIN32
		if (_wenviron[0])
			free(_wenviron[0]);
#endif // !_WIN32
		free(_wenviron);
		_wenviron = NULL;
	}
}

typedef void (*at_exit_func_proc)(void);
typedef struct __at_exit_funcs {
	uint16_t Funcs;
	at_exit_func_proc FuncArray[256];
} _at_exit_funcs;
typedef struct __at_quick_exit_funcs {
	uint16_t Funcs;
	at_exit_func_proc FuncArray[256];
} _at_quick_exit_funcs;
static _at_exit_funcs at_exit_funcs = { 0 };
static _at_quick_exit_funcs at_quick_exit_funcs = { 0 };

extern "C" _Noreturn void abort(void)
{
	raise(SIGABRT);
	_Exit(SIGABRT);

}
extern "C" _Noreturn void quick_exit(int status)
{
	for (int i = ((int)at_quick_exit_funcs.Funcs) - 1; i >= 0; i--)
		at_quick_exit_funcs.FuncArray[i]();
	_Exit(status);
}
extern "C" _Noreturn void exit(int status)
{
	for (int i = ((int)at_exit_funcs.Funcs) - 1; i >= 0; i--)
		at_exit_funcs.FuncArray[i]();
	_Exit(status);
}

extern "C" _Noreturn void _Exit(int status)
{
#ifdef _WIN32
	SyscallNtTerminateProcess(~0, status);
#else
#error Unimplemented abort (prog_control.cpp)
#endif // _WIN32
}

extern "C" char* getenv(const char* name)
{
	char* ret = NULL;
#ifdef _WIN32
	for (char** curr = _environ; *curr; curr++)
	{
		char* chpos = strchr(*curr, '=');
		if (chpos != NULL)
		{
			size_t dist = chpos - *curr;
			if (dist && strncmp(*curr, name, dist) == 0)
			{
				ret = chpos + 1;
				break;
			}
		}
	}
#else
#error Unimplemented getenv (prog_control.cpp)
#endif // _WIN32
	return ret;
}

extern "C" int system(const char* string)
{
	/*
	After a few days of researching how to actually spawn processes and redirecting their pipes I've deceided to provide minimal implementation.
	The amount of work to implement this function is absurd for how little payoff there is.
	I'll maybe release the finding but dont count on it.
	*/
	return 0;
}

extern "C" int atexit(void (*func)(void))
{
	int nRet = -1;
	if (func)
	{
		if (at_exit_funcs.Funcs < 256)
		{
			at_exit_funcs.FuncArray[at_exit_funcs.Funcs] = func;
			at_exit_funcs.Funcs++;
			nRet = 0;
		}
	}
	return nRet;
}
extern "C" int at_quick_exit(void (*func)(void))
{
	int nRet = -1;
	if (func)
	{
		if (at_quick_exit_funcs.Funcs < 256)
		{
			at_quick_exit_funcs.FuncArray[at_quick_exit_funcs.Funcs] = func;
			at_quick_exit_funcs.Funcs++;
			nRet = 0;
		}
	}
	return nRet;
}