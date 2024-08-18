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
#include <include\fenv.h>
#include <include\string.h>
#include "x86_msr.h"
//TODO: raise exceptions

x86_mxcsr x86GetMxcsr()
{
	x86_mxcsr ret;
	__asm {
		stmxcsr [ret]
	}
	return ret;
}
void x86SetMxcsr(x86_mxcsr x)
{
	//default is 0x1F80
	__asm {
		ldmxcsr [x]
	}
}

void x87ClearAllExceptions()
{
	__asm {fnclex}
}

void x87GetControlWord(x87_fpu_control_word* pMem)
{
	//uint16_t fpuword = 0;
	__asm {
		mov rax, qword ptr [pMem]
		FNSTCW word ptr [rax]
	}
	//pMem->word = fpuword;
}
void x87SetControlWord(x87_fpu_control_word* pMem)
{
	__asm {
		mov rax, qword ptr [pMem]
		FLDCW word ptr [rax]
	}
}


int feclearexcept(int excepts)
{
	excepts &= FE_ALL_EXCEPT;
	if (excepts == FE_ALL_EXCEPT)
		x87ClearAllExceptions();
	x86_mxcsr x = x86GetMxcsr();
	x.dword &= ~((uint32_t)excepts);
	x86SetMxcsr(x);
	return 0;
}
int fegetexceptflag(fexcept_t* flagp,
	int excepts)
{
	excepts &= FE_ALL_EXCEPT;
	x86_mxcsr x = x86GetMxcsr();
	*flagp = x.dword & ((uint32_t)excepts);
	return 0;
}
int feraiseexcept(int excepts)
{
	excepts &= FE_ALL_EXCEPT;
	x86_mxcsr x = x86GetMxcsr();
	x.dword |= ((uint32_t)excepts);
	x86SetMxcsr(x);
	return 0;
}
int fesetexceptflag(const fexcept_t* flagp,
	int excepts)
{
	excepts &= FE_ALL_EXCEPT;
	x86_mxcsr x = x86GetMxcsr();
	uint32_t u32Exc = (uint32_t)excepts;
	x.dword = (x.dword & ~(u32Exc)) | (*flagp & u32Exc);
	x86SetMxcsr(x);
	return 0;
}
int fetestexcept(int excepts)
{
	excepts &= FE_ALL_EXCEPT;
	x86_mxcsr x = x86GetMxcsr();
	x.dword = x.dword & ~((uint32_t)excepts);
	return (x.dword != 0) ? 1 : 0;
}
int fegetround(void)
{
	x86_mxcsr x = x86GetMxcsr();
	int nMode = (int)x.bitfield.RoundingControl;
	if ((FE_TONEAREST > nMode) || (nMode > FE_TOWARDZERO))
		nMode = -1;
	return nMode;
}
int fesetround(int round)
{
	int nRet = 0;
	if ((FE_TONEAREST <= round) && (round <= FE_TOWARDZERO))
	{
		x87_fpu_control_word cw = { {0} };
		x87GetControlWord(&cw);
		cw.bitfield.RoundingControl = (x87_fpu_rounding_control)round;
		x87SetControlWord(&cw);
		x86_mxcsr x = x86GetMxcsr();
		x.bitfield.RoundingControl = (x87_fpu_rounding_control)round;
		x86SetMxcsr(x);
	}
	else
		nRet = -1;

	return nRet;
}



int fegetenv(fenv_t* envp)
{
	int nRet = -1;
	_tos_x86_flt_env* penv = (_tos_x86_flt_env*)envp;

	if (penv)
	{
		penv->msr = x86GetMxcsr();
		x87GetControlWord(&penv->x87cw);
		nRet = 0;
	}
	return nRet;
}
int fesetenv(const fenv_t* envp)
{
	int nRet = -1;
	_tos_x86_flt_env* penv = (_tos_x86_flt_env*)envp;
	if (penv)
	{
		x86SetMxcsr(penv->msr);
		x87SetControlWord(&penv->x87cw);
		nRet = 0;
	}
	return nRet;
}
int feholdexcept(fenv_t* envp)
{
	int nRet = -1;
	if (envp)
	{
		_tos_x86_flt_env newenv;
		fegetenv((fenv_t*)&newenv);
		memcpy(envp, &newenv, sizeof(newenv));
		newenv.msr.bitfield.InvalidOpMask = 1;
		newenv.msr.bitfield.DenormalOpMask = 1;
		newenv.msr.bitfield.DivideByZeroMask = 1;
		newenv.msr.bitfield.OverflowMask = 1;
		newenv.msr.bitfield.UnderflowMask = 1;
		newenv.msr.bitfield.PrecisionMask = 1;

		newenv.x87cw.bitfield.InvalidOp = 1;
		newenv.x87cw.bitfield.DenormalOperand = 1;
		newenv.x87cw.bitfield.ZeroDivide = 1;
		newenv.x87cw.bitfield.Overflow = 1;
		newenv.x87cw.bitfield.Underflow = 1;
		newenv.x87cw.bitfield.Precision = 1;
		fesetenv((fenv_t*)&newenv);
		nRet = 0;
	}

	return nRet;
}
int feupdateenv(const fenv_t* envp)
{
	int nRet = -1;
	_tos_x86_flt_env curr;
	_tos_x86_flt_env* penv = (_tos_x86_flt_env*)envp;
	_tos_x86_flt_env updated;
	if (envp)
	{
		fegetenv((fenv_t*)&curr);
		memcpy(&updated, penv, sizeof(updated));

		updated.msr.dword = (curr.msr.dword & ~(FE_ALL_EXCEPT)) | (penv->msr.dword & ~(FE_ALL_EXCEPT));
		//updated.x87cw.word = (curr.x87cw.word & ~(FE_ALL_EXCEPT)) | (penv->x87cw.word & ~(FE_ALL_EXCEPT));
		fesetenv((fenv_t*)&updated);
		nRet = 0;
	}
	return nRet;
}

extern "C" int _tos_fenv_TestEnvEqual(const fenv_t* a, const fenv_t* b)
{
	_tos_x86_flt_env ca;
	_tos_x86_flt_env cb;
	memcpy(&ca, a, sizeof(_tos_x86_flt_env));
	memcpy(&cb, b, sizeof(_tos_x86_flt_env));
	ca.msr.bitfield.reserved = 0;
	ca.x87cw.bitfield.Reserve = 0;
	ca.x87cw.bitfield.Reserve2 = 0;
	cb.msr.bitfield.reserved = 0;
	cb.x87cw.bitfield.Reserve = 0;
	cb.x87cw.bitfield.Reserve2 = 0;
	return memcmp(&ca, &cb, sizeof(_tos_x86_flt_env));
}

extern "C" void _tos_InitializeFloatingPointEnvironment()
{
	fenv_t defenv = FE_DEF_ENV;
	_tos_x86_flt_env env;
	env.msr.dword = defenv[0];
	env.x87cw.word = defenv[1];
	fesetenv((fenv_t*)&env);
	x87ClearAllExceptions();
	return;
}