#pragma once
#ifndef TOS_MEMMAN_V2_H
#define TOS_MEMMAN_V2_H

#include "../include/stddef.h"
#include "lock.h"

#pragma pack(push, 1)
template<typename _Ty>
struct MMV2EntryHeader {
	using _Type = _Ty;
	_Ty Size;//2
	uint32_t InUse : 1;//6
	uint32_t Offset : 8;
	uint32_t Alignment : 7;
	uint32_t wCanary : 16;

};
template<typename _Ty>
struct MMV2EntryFooter {
	using _Type = _Ty;
	uint16_t wCanary;
	_Ty wHeaderOffset;
};
template<typename _Ty>
struct MMV2PageHeader {
	using _Type = _Ty;
	MMV2PageHeader<_Ty>* pNextPage;
	_Ty PageSize;
	// empty page has sizeof(MMV2PageHeader) + sizeof(MMV2EntryHeader) + sizeof(MMV2EntryFooter) = 38 or 62 bytes used on start
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


class memman_v2 {
private:
	MMV2PageHeader<uint16_t>* m_pSmallPages;
	MMV2PageHeader<uint64_t>* m_pBigPages;
	volatile tos_lock m_Lock;
public:
	memman_v2();
	~memman_v2();
	// Max alignment is 64 and min is 1
	void* aligned_alloc(size_t alignment, size_t size);
	void free(void* ptr);
	void* malloc(size_t size);
	void* realloc(void* ptr, size_t size);
	int CheckAlloc(void* ptr);

};

#endif // !TOS_MEMMAN_V2_H