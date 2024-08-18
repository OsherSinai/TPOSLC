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
#include <include\signal.h>
#include <include\threads.h>
#include <include\errno.h>

#include "TOSThreadEnvironmentBlock.h"

#if defined(TOS_KERNEL)
#elif defined(_WIN32)
#include "win32/win32_except.h"
extern "C" NTSTATUS SyscallNtTerminateProcess(uint64_t Handle, NTSTATUS Status);
#else
#error No other OSs are supported at this time (signal.cpp)
#endif

/*
static void DefaultSignalHandler(int i)
{
	// Add internal exit function 
	//NtTerminateProcess  0x002c 
	
#ifdef _WIN32
	SyscallNtTerminateProcess(~0, 3);
#else

#endif // _WIN32

}
*/
static void IgnoreSignalHandler(int i)
{

}

extern "C" void _tos_initialize_peb_signal_handler()
{
	//auto toss_auto = &tos_teb;
	tos_HandlerPack* pthp = &tos_teb.SignalHandlers;
	pthp->SigIntHandler = IgnoreSignalHandler;
	pthp->SigILLHandler = IgnoreSignalHandler;
	pthp->SigAbortHandler = IgnoreSignalHandler;
	pthp->SigFPEHandler = IgnoreSignalHandler;
	pthp->SigSegvHandler = IgnoreSignalHandler;
	pthp->SigTermHandler = IgnoreSignalHandler;
}

void (*signal(int sig, void (*func)(int)))(int)
{
	TOSSignalHandler Return = SIG_ERR;
	TOSSignalHandler* TargetHandler;
	TOSSignalHandler Handler;

	errno = 0;

	if (func == SIG_DFL)
		Handler = IgnoreSignalHandler;// DefaultSignalHandler;
	else if (func == SIG_IGN)
		Handler = IgnoreSignalHandler;
	else
		Handler = func;

	switch (sig)
	{
	case SIGINT        : TargetHandler = &tos_teb.SignalHandlers.SigIntHandler; break;
	case SIGILL        : TargetHandler = &tos_teb.SignalHandlers.SigILLHandler; break;
	case SIGABRT_COMPAT: TargetHandler = &tos_teb.SignalHandlers.SigAbortHandler; break;
	case SIGFPE        : TargetHandler = &tos_teb.SignalHandlers.SigFPEHandler; break;
	case SIGSEGV       : TargetHandler = &tos_teb.SignalHandlers.SigSegvHandler; break;
	case SIGTERM       : TargetHandler = &tos_teb.SignalHandlers.SigTermHandler; break;
	case SIGABRT       : TargetHandler = &tos_teb.SignalHandlers.SigAbortHandler; break;
	default:
		goto cleanup;
	}

	Return = *TargetHandler;
	*TargetHandler = Handler;

cleanup:
	if (Return == SIG_ERR)
		errno = EINVAL;
	return Return;
}

int raise(int sig)
{
	int nRet = 0;
	switch (sig)
	{
	case SIGINT			: tos_teb.SignalHandlers.SigIntHandler(sig); break;
	case SIGILL			: tos_teb.SignalHandlers.SigILLHandler(sig); break;
	case SIGABRT_COMPAT	: tos_teb.SignalHandlers.SigAbortHandler(sig); break;
	case SIGFPE			: tos_teb.SignalHandlers.SigFPEHandler(sig); break;
	case SIGSEGV		: tos_teb.SignalHandlers.SigSegvHandler(sig); break;
	case SIGTERM		: tos_teb.SignalHandlers.SigTermHandler(sig); break;
	case SIGABRT		: tos_teb.SignalHandlers.SigAbortHandler(sig); break;
	default:
		nRet = -1;
	}
	return nRet;
}

#ifdef _WIN32
extern "C" int _tos_win32_signal_exception_propagator(DWORD ExceptionCode)
{
	int nRet = 0;
	switch (ExceptionCode)
	{
	case STATUS_ACCESS_VIOLATION:
	case EXCEPTION_DATATYPE_MISALIGNMENT:
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
	case EXCEPTION_IN_PAGE_ERROR:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		break;
	case STATUS_FLOAT_DENORMAL_OPERAND :
	case STATUS_FLOAT_DIVIDE_BY_ZERO   :
	case STATUS_FLOAT_INEXACT_RESULT   :
	case STATUS_FLOAT_INVALID_OPERATION:
	case STATUS_FLOAT_OVERFLOW         :
	case STATUS_FLOAT_STACK_CHECK      :
	case STATUS_FLOAT_UNDERFLOW        :
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_BREAKPOINT:
	case EXCEPTION_SINGLE_STEP:
		tos_teb.SignalHandlers.SigIntHandler(SIGINT);
		break;
	case EXCEPTION_PRIV_INSTRUCTION:
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		tos_teb.SignalHandlers.SigILLHandler(SIGILL);
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
	case EXCEPTION_INVALID_DISPOSITION:
		tos_teb.SignalHandlers.SigAbortHandler(SIGABRT_COMPAT);
		break;
	case CONTROL_C_EXIT:
	case CONTROL_C_DEBUG_EXIT:
		tos_teb.SignalHandlers.SigTermHandler(SIGTERM);
		break;
	default:
		nRet = -1;
		break;
	}
	return nRet;
}



// temporary untill ill figure out how to set it by myself
LONG NTAPI vecex(
	_EXCEPTION_POINTERS* ExceptionInfo
)
{
	LONG ret = EXCEPTION_CONTINUE_EXECUTION;
	switch (ExceptionInfo->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_BREAKPOINT:
		tos_teb.SignalHandlers.SigIntHandler(SIGINT);
		break;
	case EXCEPTION_SINGLE_STEP:
		tos_teb.SignalHandlers.SigIntHandler(SIGINT);
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_FLT_DENORMAL_OPERAND:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_FLT_INEXACT_RESULT:
		break;
	case EXCEPTION_FLT_INVALID_OPERATION:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_FLT_OVERFLOW:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_FLT_STACK_CHECK:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_FLT_UNDERFLOW:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_INT_OVERFLOW:
		tos_teb.SignalHandlers.SigFPEHandler(SIGFPE);
		break;
	case EXCEPTION_PRIV_INSTRUCTION:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_IN_PAGE_ERROR:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		tos_teb.SignalHandlers.SigILLHandler(SIGILL);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		tos_teb.SignalHandlers.SigAbortHandler(SIGABRT_COMPAT);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_STACK_OVERFLOW:
		tos_teb.SignalHandlers.SigSegvHandler(SIGSEGV);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case EXCEPTION_INVALID_DISPOSITION:
		tos_teb.SignalHandlers.SigAbortHandler(SIGABRT_COMPAT);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	case CONTROL_C_EXIT:
	case CONTROL_C_DEBUG_EXIT:
		tos_teb.SignalHandlers.SigTermHandler(SIGTERM);
		ret = EXCEPTION_EXECUTE_HANDLER;
		break;
	default:
		break;
	}
	return ret;
}
//void* g_Win32SpecificSigAddr = AddVectoredExceptionHandler(1, vecex);
#endif // _WIN32
