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
#include <include\stddef.h>

int abs(int j)
{
	constexpr size_t shift = (sizeof(j)*8) - 1;
	decltype(j) mask = j >> shift;
	j ^= mask;
	j += mask & 1;
	return j;
}
long int labs(long int j)
{
	constexpr size_t shift = (sizeof(j) * 8) - 1;
	decltype(j) mask = j >> shift;
	j ^= mask;
	j += mask & 1;
	return j;
}
long long int llabs(long long int j)
{
	constexpr size_t shift = (sizeof(j) * 8) - 1;
	decltype(j) mask = j >> shift;
	j ^= mask;
	j += mask & 1;
	return j;
}
div_t div(int numer, int denom)
{
	div_t ret;
	ret.q = numer / denom;
	ret.rem = numer % denom;
	return ret;
}
ldiv_t ldiv(long int numer, long int denom)
{
	ldiv_t ret;
	ret.q = numer / denom;
	ret.rem = numer % denom;
	return ret;
}
lldiv_t lldiv(long long int numer, long long int denom)
{
	lldiv_t ret;
	ret.q = numer / denom;
	ret.rem = numer % denom;
	return ret;
}
