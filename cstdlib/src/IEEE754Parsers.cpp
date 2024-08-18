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
#include <include\string.h>
#include <include\stdlib.h>
#include <include\float.h>
#include <include\math.h>
#include "IEEE754Parsers.h"
#include "VariableSizeMath.h"
static void revstr(char* buffer)
{
	char* plow = buffer;
	char* phigh = buffer + strlen(buffer) - 1;
	char tmp;
	while (plow < phigh)
	{
		tmp = *plow;
		*plow = *phigh;
		*phigh = tmp;
		phigh--;
		plow++;
	}
}



static bool dbltofx_inner_break_loop_if_zero(uint64_t* buffer, uint8_t size, bool reverse)
{
	bool bRet = true;
	if (reverse)
	{
		for (uint8_t i = 0; i < size; i++)
		{
			if (*buffer)
			{
				bRet = false;
				break;
			}
			buffer--;
		}
	}
	else
	{
		for (uint8_t i = 0; i < size; i++)
		{
			if (*buffer)
			{
				bRet = false;
				break;
			}
			buffer++;
		}
	}
	return bRet;
}

static size_t dbltofx_last_set_bit(uint64_t d)
{
	size_t ret = 64;
	for (size_t i = 0; i < 64; i++)
	{
		if ((d >> i) & 1)
		{
			ret = i;
			break;
		}
	}
	return ret;
}

static int64_t dbltof_assign_qword(uint64_t* buffer, ptrdiff_t msb_bit_pos, uint64_t val)
{
	int64_t arrpoint;
	int64_t bits_to_copy;
	int64_t shift;
	if (msb_bit_pos < 0)
		arrpoint = -1;
	else
		arrpoint = 0;
	arrpoint += msb_bit_pos / 64;
	bits_to_copy = llabs(msb_bit_pos % 64);
	if (msb_bit_pos >= 0)
	{
		if (52 > bits_to_copy)
		{
			shift = (52 - bits_to_copy);
			buffer[arrpoint] = val >> shift;
			buffer[arrpoint - 1] = val << (64 - shift);
		}
		else
		{
			shift = (bits_to_copy - 52);
			buffer[arrpoint] = val << shift;
		}
	}
	else
	{
		if (12 > bits_to_copy)
		{
			buffer[arrpoint] = val << (12 - bits_to_copy);
		}
		else
		{
			shift = (bits_to_copy - 12);
			buffer[arrpoint] = val >> shift;
			buffer[arrpoint - 1] = val << (64 - shift);
		}
	}

	return arrpoint;
}

template<size_t bits>
consteval size_t dbltofx_CalcMask()
{
	size_t ret = 0;
	for (size_t i = 0; i < bits; i++)
		ret = (ret << 1) | 1;
	return ret;
}

static int64_t dbltofx(double d, dbltofx_inner* buffer, int64_t* start_pos)
{
	constexpr uint64_t mant_bits = DBL_MANT_DIG - 1;
	constexpr uint64_t exp_bits = sizeof(double) * 8 - mant_bits - 1;
	constexpr uint64_t exp_mask = dbltofx_CalcMask<exp_bits>();
	constexpr uint64_t mant_mask = dbltofx_CalcMask<mant_bits>();

	uint64_t exp_raw;
	int64_t exp;
	uint64_t mant;

	exp_raw = (*(uint64_t*)&d) >> mant_bits;
	exp_raw = exp_raw & exp_mask;
	mant = (*(uint64_t*)&d);
	mant = (mant & mant_mask);

	exp = (int64_t)exp_raw - ((1llu << (exp_bits - 1)) - 1);
	mant |= (0x1llu << mant_bits);

	memset(buffer, 0, sizeof(*buffer));

	*start_pos = dbltof_assign_qword(buffer->num, exp, mant);
	return exp;
}

extern "C" void dbltostr(double d, int* frac_limit, bool bUppercase, dbl_to_str_state * state)
{
	memset(state, 0, sizeof(*state));
	if (isnan(d))
	{
		if(bUppercase)
			strcpy(state->szBuffer, "NAN");
		else
			strcpy(state->szBuffer, "nan");
		*frac_limit = -1;
	}
	else if (isinf(d))
	{
		char* pBuffPos = state->szBuffer;
		if (*(uint64_t*)&d >> 63)
		{
			*pBuffPos = '-';
			pBuffPos++;
		}
		if(bUppercase)
			strcpy(pBuffPos, "INFINITY");
		else
			strcpy(pBuffPos, "infinity");
		*frac_limit = -1;
	}
	else
	{
		int64_t start_pos;
		char* buffpos = state->szBuffer;
		int64_t bit_position = dbltofx(d, &state->fixed_point, &start_pos);
		state->fraction_buffer_adder[0] = 5;
		if (!*frac_limit)
			*frac_limit = 6;
		if (start_pos >= 0)
		{

			if (bit_position > 52)
			{
				//only normal number
			}
			else
			{
				// got a  fraction
				//3.969376087188720703125
				int64_t shift = 63;
				size_t break_at = dbltofx_last_set_bit(state->fixed_point.num[start_pos - 1]);
				while (break_at <= shift)
				{
					VariSizeMult64(state->fraction_buffer_acc, 10, dbltofx_inner::numlen);
					if ((state->fixed_point.num[start_pos - 1] >> shift) & 1)
					{
						// change this so we wont always have to add multiple zero bytes
						VariSizeAdd64(state->fraction_buffer_acc, state->fraction_buffer_adder, dbltofx_inner::numlen);
					}
					VariSizeMult64(state->fraction_buffer_adder, 5, dbltofx_inner::numlen);
					shift--;
				}
				do {
					*buffpos = (char)VariSizeDiv64(state->fraction_buffer_acc, 10, dbltofx_inner::numlen) + '0';
					buffpos++;
				} while (!dbltofx_inner_break_loop_if_zero(state->fraction_buffer_acc, dbltofx_inner::numlen, false));

			}

			*buffpos = '.';
			buffpos++;

			do {
				*buffpos = (char)VariSizeDiv64(state->fixed_point.num, 10, start_pos + 1) + '0';
				buffpos++;
			} while (!dbltofx_inner_break_loop_if_zero(state->fixed_point.num, start_pos + 1, false));
		}
		else
		{
			int64_t needed_digits = 0;
			int64_t actual_digits = 0;
			for (int64_t itr = -1; itr > start_pos; itr--)
			{
				for (uint64_t lp = 0; lp < 64; lp++)
				{
					needed_digits++;
					VariSizeMult64(state->fraction_buffer_adder, 5, dbltofx_inner::numlen);
				}
			}


			// smaller than 1
			int64_t shift = 63;
			int64_t break_at = dbltofx_last_set_bit(state->fixed_point.num[start_pos]);
			while (break_at <= shift)
			{
				needed_digits++;

				//if (needed_digits >= *frac_limit)
				//	break;

				VariSizeMult64(state->fraction_buffer_acc, 10, dbltofx_inner::numlen);
				if ((state->fixed_point.num[start_pos] >> shift) & 1)
				{
					// change this so we wont always have to add multiple zero bytes
					VariSizeAdd64(state->fraction_buffer_acc, state->fraction_buffer_adder, dbltofx_inner::numlen);
				}
				VariSizeMult64(state->fraction_buffer_adder, 5, dbltofx_inner::numlen);
				shift--;
			}
			if (break_at == 0)
			{
				shift = 63;
				break_at = dbltofx_last_set_bit(state->fixed_point.num[start_pos - 1]);
				while (break_at <= shift)//needed_digits < *frac_limit && 
				{
					needed_digits++;
					VariSizeMult64(state->fraction_buffer_acc, 10, dbltofx_inner::numlen);
					if ((state->fixed_point.num[start_pos - 1] >> shift) & 1)
					{
						// change this so we wont always have to add multiple zero bytes
						VariSizeAdd64(state->fraction_buffer_acc, state->fraction_buffer_adder, dbltofx_inner::numlen);
					}
					shift--;
				}
				VariSizeMult64(state->fraction_buffer_adder, 5, dbltofx_inner::numlen);
				shift--;
			}

			if (1)//needed_digits <= *frac_limit
			{
				do {
					actual_digits++;
					*buffpos = (char)VariSizeDiv64(state->fraction_buffer_acc, 10, dbltofx_inner::numlen) + '0';
					buffpos++;
				} while (!dbltofx_inner_break_loop_if_zero(state->fraction_buffer_acc, dbltofx_inner::numlen, false));
			}

			for (size_t i = actual_digits; i < needed_digits; i++)
			{
				*buffpos = '0';
				buffpos++;
			}

			*buffpos = '.';
			buffpos++;
			*buffpos = '0';
			buffpos++;
		}
		if (*(uint64_t*)&d >> 63)
		{
			*buffpos = '-';
			buffpos++;
		}
		revstr(state->szBuffer);
	}
}


void dbl_extract_values(dbltofx_inner * pState, int64_t * pExponent, uint64_t * pFraq)
{
	int64_t qwExpo = pState->numlen * 64 * 2 - 1;
	uint64_t qwFraq = 0;
	bool bBreak = false;
	for (int i = (pState->numlen * 2) - 1; i >= 0; i--)
	{
		if (pState->arr[i] == 0)
		{
			qwExpo -= 64;
		}
		else
		{
			for (int j = 63; j >= 0; j--)
			{
				if ((pState->arr[i] >> j) & 1)
				{
					bBreak = true;
					break;
				}
				qwExpo--;
			}
		}
		if (bBreak)
			break;
	}

	if (qwExpo > 1)
	{
		uint64_t shft = qwExpo % 64;
		uint64_t idx = qwExpo / 64;
		uint64_t s1 = pState->arr[idx] << (64 - shft);
		uint64_t s2 = pState->arr[idx - 1] >> shft;

		qwFraq = s1 | s2;
	}
	else if (qwExpo == 0)
	{
		uint64_t shft = qwExpo % 64;
		qwFraq = (pState->arr[0] << shft);
	}

	*pExponent = qwExpo - pState->numlen * 64;
	*pFraq = qwFraq;
}