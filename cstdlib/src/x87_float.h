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
#ifndef X87_FLOAT_H
#define X87_FLOAT_H
#include <include\stddef.h>
#pragma pack(push, 1)
union x87_float {
	struct {
		uint32_t fraction : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	}bitfield;
	float val;
	uint32_t uval;
};
union x87_double {
	struct {
		uint64_t fraction : 52;
		uint64_t exponent : 11;
		uint64_t sign : 1;
	}bitfield;
	double val;
	uint64_t uval;
};
union x87_long_double {
	struct {
		uint64_t fraction : 63;
		uint64_t intpart : 1;
		uint16_t exponent : 15;
		uint16_t sign : 1;
	}bitfield;
	struct {
		uint64_t u1;
		uint16_t u2;
	}composite;
	uint16_t iarr[5];
	long double val;
};
#pragma pack(pop)
#endif // !X87_FLOAT_H
