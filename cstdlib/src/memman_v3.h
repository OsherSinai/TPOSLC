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
#ifndef TOS_MEMMAN_V2_H
#define TOS_MEMMAN_V2_H

#include <include\stddef.h>
#include "lock.h"

#pragma pack(push, 1)
template<typename _Ty>
struct MMV3EmptyEntryHeader;
template<typename _Ty>
struct MMV3EmptyEntryLL //16 bytes
{
	struct MMV3EmptyEntryHeader<_Ty>* pNext;
	struct MMV3EmptyEntryHeader<_Ty>* pPrev;
};
template<typename _Ty>
struct MMV3EntryHeader { //16[6bytes], 32[8bytes],64[12 bytes]
	using _Type = _Ty;
	_Ty Size;
	uint32_t InUse : 1;
	uint32_t Offset : 8;
	uint32_t Alignment : 7;
	uint32_t wCanary : 16;
};
template<typename _Ty>
struct MMV3EmptyEntryHeader { //16[6bytes], 32[8bytes],64[12 bytes]
	using _Type = _Ty;
	_Ty Size;
	uint32_t InUse : 1;
	uint32_t Offset : 8;
	uint32_t Alignment : 7;
	uint32_t wCanary : 16;
	MMV3EmptyEntryLL<_Ty> LinkedList;
};
template<typename _Ty>
struct MMV3EntryFooter { //16[4bytes], 32[6bytes],64[10 bytes]
	using _Type = _Ty;
	uint16_t wCanary;
	_Ty wHeaderOffset;
};
template<typename _Ty>
struct MMV3PageHeader { //16[20bytes], 32[24bytes],64[32 bytes]
	using _Type = _Ty;
	MMV3PageHeader<_Ty>* pNextPage;
	MMV3EmptyEntryHeader<_Ty>* pNextInPageFree;
	_Ty PageSize;
	// empty pages are 
	//16= 6+4+20 = 30 bytes
	//32= 8+6+24 = 38 bytes
	//64= 12+10+32 = 54 bytes
	_Ty BytesInUse;
};
#pragma pack(pop)

#ifndef IMM_CANARY_BYTE
#define IMM_CANARY_WORD 0xDEAD
#define IMM_CANARY_DWORD 0xDEADDEAD
#endif

#define IMM_PAGE_SIZE (4096ull)

#ifndef IMM_KEEP_PAGES
#define IMM_KEEP_PAGES 8
#endif 


#ifndef IMM_MEGAPAGE_MULT
#define IMM_MEGAPAGE_MULT 8
#endif 
#ifndef IMM_MEGAPAGE_MIN_SIZE
#define IMM_MEGAPAGE_MIN_SIZE (IMM_PAGE_SIZE*IMM_MEGAPAGE_MULT)
#endif


class memman_v3 {
private:
	MMV3PageHeader<uint16_t>* m_pSmallPages;
	MMV3PageHeader<uint64_t>* m_pBigPages;
	volatile tos_lock m_Lock;
public:
	memman_v3();
	~memman_v3();
	// Max alignment is 64 and min is 1
	void* aligned_alloc(size_t alignment, size_t size);
	void* malloc(size_t size);
	void free(void* ptr);
	void* realloc(void* ptr, size_t size);
	int CheckAlloc(void* ptr);

};

#endif // !TOS_MEMMAN_V2_H