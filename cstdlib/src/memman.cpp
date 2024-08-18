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
#include "memman_v3.h"
memman_v3 g_IMM;

LIBC_DEF_BEGIN
void* aligned_alloc(size_t alignment, size_t size)
{
	void* pRet;
	pRet = g_IMM.aligned_alloc(alignment, size);
	return pRet;
}
void* calloc(size_t nmemb, size_t size)
{
	void* pRet;
	size *= nmemb;
	pRet = g_IMM.malloc(size);
	return pRet;
}
void free(void* ptr)
{
	g_IMM.free(ptr);
}
void* malloc(size_t size)
{
	void* pRet;
	pRet = g_IMM.malloc(size);
	return pRet;
}

void* realloc(void* ptr, size_t size)
{
	void* pRet;
	pRet = g_IMM.realloc(ptr, size);
	return pRet;
}

extern "C" int _tos_CheckPtr(void* ptr)
{
	int nRet;
	nRet = g_IMM.CheckAlloc(ptr);
	return nRet;
}
LIBC_DEF_END