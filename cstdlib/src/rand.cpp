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
#include <include\stdint.h>
#include <include\time.h>
#include "lock.h"
#define RAND_ROL(x, r) ((x << r) | (x >> (64 - r)))

struct xoshiro256ss_state {
	uint64_t state[4];
};

static uint64_t xoshiro256ss(xoshiro256ss_state* pState)
{
	uint64_t res = RAND_ROL(pState->state[1] * 5, 7) * 9;
	uint64_t shift = pState->state[1] << 17;
	pState->state[2] ^= pState->state[0];
	pState->state[3] ^= pState->state[1];
	pState->state[1] ^= pState->state[2];
	pState->state[0] ^= pState->state[3];
	pState->state[2] ^= shift;
	pState->state[3] = RAND_ROL(pState->state[3], 45);
	return res;
}

static uint64_t splitmix64(uint64_t* state) {
	uint64_t result = (*state += 0x9E3779B97f4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}

static void xorshift256_init(xoshiro256ss_state* pState, uint64_t seed) {
	pState->state[0] = splitmix64(&seed);
	pState->state[1] = splitmix64(&seed);
	pState->state[2] = splitmix64(&seed);
	pState->state[3] = splitmix64(&seed);
}

static xoshiro256ss_state lock_random_state = {
	0xaba19546ceade0de,
	0xaba19546ceade0de,
	0xaba19546ceade0de,
	0xaba19546ceade0de
};
static tos_lock g__lrs_lock = STATIC_INITIALIZE_TOS_LOCK;

extern "C" int rand(void)
{
	int nRnd;
	AquireLock(&g__lrs_lock);
	nRnd = xoshiro256ss(&lock_random_state) % RAND_MAX;
	FreeLock(&g__lrs_lock);
	return nRnd;
}
extern "C" void srand(unsigned int seed)
{
	AquireLock(&g__lrs_lock);
	xorshift256_init(&lock_random_state, seed);
	FreeLock(&g__lrs_lock);
}

extern "C" void _tos_Initialize_rand()
{
	srand(time(0));
}

#undef RAND_ROL