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
#ifndef X86_MSR_H
#define X86_MSR_H
#include <include\stddef.h>
enum class x87_fpu_precision_control : uint16_t {
	Single,
	Reserve,
	Double,
	ExtendedDouble
};
enum class x87_fpu_rounding_control : uint16_t {
	// Rounded result is the closest to the infinitely precise result. If two values are equally close, the
	// result is the even value(that is, the one with the least - significant bit of zero). 
	// Default
	nearest,
	//Rounded result is closest to but no greater than the infinitely precise result.
	floor,

	//Rounded result is closest to but no less than the infinitely precise result.
	ceiling,

	//Rounded result is closest to but no greater in absolute value than the infinitely precise result.
	trunc
};

enum class x87_fpu_tag : uint16_t
{
	valid,
	zero,
	special,
	empty
};

union x87_fpu_control_word {
	struct {
		uint16_t InvalidOp : 1;
		uint16_t DenormalOperand : 1;
		uint16_t ZeroDivide : 1;
		uint16_t Overflow : 1;
		uint16_t Underflow : 1;
		uint16_t Precision : 1;
		uint16_t Reserve : 2;
		x87_fpu_precision_control PrecisionControl : 2;
		x87_fpu_rounding_control RoundingControl : 2;
		uint16_t InfinityControl : 1;
		uint16_t Reserve2 : 3;
	}bitfield;
	uint16_t word;
};


union x87_fpu_status_word {
	struct {
		uint16_t InvalidOp : 1;
		uint16_t DenormalOperand : 1;
		uint16_t ZeroDivide : 1;
		uint16_t Overflow : 1;
		uint16_t Undeflow : 1;
		uint16_t Precision : 1;
		uint16_t StackFault : 1;
		uint16_t ExceptionStatus : 1;
		uint16_t ConditionCodeLower : 3;
		uint16_t Top : 3;
		uint16_t ConditionCodeUpper : 1;
		uint16_t Busy : 1;
	}bitfield;
	uint16_t word;
};

union x87_fpu_tag_word {
	struct {
		x87_fpu_tag Tag0 : 2;
		x87_fpu_tag Tag1 : 2;
		x87_fpu_tag Tag2 : 2;
		x87_fpu_tag Tag3 : 2;
		x87_fpu_tag Tag4 : 2;
		x87_fpu_tag Tag5 : 2;
		x87_fpu_tag Tag6 : 2;
		x87_fpu_tag Tag7 : 2;
	}bitfield;
	uint16_t word;
};

struct x87_fpu_environment {
	x87_fpu_control_word ControlWord;
	uint16_t unused1;
	x87_fpu_status_word StatusWord;
	uint16_t unused2;
	x87_fpu_tag_word TagWord;
	uint16_t unused3;
	uint32_t FPUInstructionPointerOffset;
	uint16_t FPUInstructionPointerSelector;
	uint16_t Opcod11Bits;
	uint32_t FPUDataPointerOffset;
	uint16_t FPUDataPointerSelector;
	uint16_t Unused4;
	uint8_t registers[80];
};

union x86_mxcsr {
	struct {
		uint16_t Invalidop : 1;
		uint16_t Denormal : 1;
		uint16_t DivideByZero : 1;
		uint16_t Overflow : 1;
		uint16_t Underflow : 1;
		uint16_t Precision : 1;
		uint16_t DenormalAreZero : 1;
		uint16_t InvalidOpMask : 1;
		uint16_t DenormalOpMask : 1;
		uint16_t DivideByZeroMask : 1;
		uint16_t OverflowMask : 1;
		uint16_t UnderflowMask : 1;
		uint16_t PrecisionMask : 1;
		x87_fpu_rounding_control RoundingControl : 2;
		uint16_t FlushToZero : 1;
		uint16_t reserved;
	}bitfield;
	uint32_t dword;
};

struct _tos_x86_flt_env {
	x86_mxcsr msr;
	x87_fpu_control_word x87cw;
};


x86_mxcsr x86GetMxcsr();
void x86SetMxcsr(x86_mxcsr x);

void x87ClearAllExceptions();

void x87GetControlWord(x87_fpu_control_word* pMem);
void x87SetControlWord(x87_fpu_control_word* pMem);

#endif // !X86_MSR_H
