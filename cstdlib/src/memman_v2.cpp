#include "memman_v2.h"
#include "../include/signal.h"
#include "../include/string.h"

#if defined(TOS_KERNEL)
#error No other OSs are supported at this time (memman_base.cpp)
#elif defined(_WIN32)
#include "win32_memory.h"
#else
#error No other OSs are supported at this time (memman_base.cpp)
#endif

memman_v2::memman_v2() :
	m_pSmallPages(NULL),
	m_pBigPages(NULL)
{
}

memman_v2::~memman_v2()
{
}


template<typename _Ty>
static void CreateFooter(MMV2PageHeader<_Ty>* pPage, MMV2EntryHeader<_Ty>* pHeader)
{
	MMV2EntryFooter<_Ty>* pFooterLocation = (MMV2EntryFooter<_Ty>*)((size_t)(pHeader + 1) + (size_t)pHeader->Size);
	uint8_t* p = (uint8_t*)pFooterLocation;
	bool bIsZero = true;
	for (size_t i = 0; i < sizeof(MMV2EntryFooter<_Ty>); i++)
	{
		if (p[i])
		{
			bIsZero = false;
			break;
		}
	}

	if (bIsZero)
	{
		pFooterLocation->wCanary = IMM_CANARY_WORD;
		pFooterLocation->wHeaderOffset = (size_t)pFooterLocation - (size_t)pHeader;
	}
	else
	{
		if (pFooterLocation->wCanary == IMM_CANARY_WORD)
		{
			pFooterLocation->wHeaderOffset = (size_t)pFooterLocation - (size_t)pHeader;
		}
		else
		{
			__asm {
				int 3
			}
		}
	}
}

template<typename _Ty>
MMV2EntryFooter<_Ty>* GetFooterFromHeader(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry
)
{
	MMV2EntryFooter<_Ty>* pFooter = (MMV2EntryFooter<_Ty>*)(((uint8_t*)(pEntry + 1)) + pEntry->Size);
	if ((size_t)pFooter > ((size_t)pPage + (size_t)pPage->PageSize))
	{
		// footer is outsize of the page
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else if (pFooter->wCanary != IMM_CANARY_WORD)
	{
		//canary error, canary was overwritten
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else if ((size_t)pFooter - (size_t)pFooter->wHeaderOffset != (size_t)pEntry)
	{
		// incorrect offset
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	return pFooter;
}

template<typename _Ty>
MMV2EntryHeader<_Ty>* GetHeaderFromFooter(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryFooter<_Ty>* pFooter
)
{
	MMV2EntryHeader<_Ty>* pHeader = (MMV2EntryHeader<_Ty>*)(((uint8_t*)pFooter) - pFooter->wHeaderOffset);
	if ((size_t)pHeader < ((size_t)pPage + sizeof(MMV2PageHeader<_Ty>)))
	{
		// pHeader is outsize of the page
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else if (pHeader->wCanary != IMM_CANARY_WORD)
	{
		//canary error, canary was overwritten
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else if (((size_t)(pHeader + 1) + (size_t)pHeader->Size) != (size_t)pFooter)
	{
		// incorrect offset
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	return pHeader;
}

template<typename _Ty>
static MMV2PageHeader<_Ty>* AllocatePages(size_t PageCount)
{
	constexpr size_t PageHeaderAndEntryHeader =
		sizeof(MMV2PageHeader<_Ty>) +
		sizeof(MMV2EntryHeader<_Ty>);
	constexpr size_t PageHeaderAndEntryHeaderAndFooter =
		PageHeaderAndEntryHeader +
		sizeof(MMV2EntryFooter<_Ty>);

	bool bSuccess = false;
	size_t ActualAllocation = 0;
	MMV2PageHeader<_Ty>* pRet = NULL;
	size_t PageSize = PageCount * IMM_PAGE_SIZE;
#ifdef _WIN32

	WinNtStatus stat = Win32NtAllocateVirtualMemory((void**)&pRet, PageSize, MEM_COMMIT, PAGE_READWRITE, &ActualAllocation);
	bSuccess = stat == WinNtStatus::Success;
#else
#error No other OSs are supported at this time (memman_base.cpp)
#endif // _WIN32


	if (bSuccess)
	{
		memset(pRet, 0, ActualAllocation);
		pRet->PageSize = PageSize;
		pRet->BytesInUse = PageHeaderAndEntryHeaderAndFooter;
		pRet->pNextPage = 0;
		MMV2EntryHeader<_Ty>* pHeader = (MMV2EntryHeader<_Ty>*)(pRet + 1);
		pHeader->InUse = 0;
		pHeader->Offset = 0;
		pHeader->wCanary = IMM_CANARY_WORD;
		pHeader->Size = PageSize - PageHeaderAndEntryHeaderAndFooter;
		CreateFooter<_Ty>(pRet, pHeader);

		MMV2EntryFooter<_Ty>* pCheckFooter = GetFooterFromHeader(pRet, pHeader);
		MMV2EntryHeader<_Ty>* pCheckHeader = GetHeaderFromFooter(pRet, pCheckFooter);
		if (pCheckHeader != pHeader)
		{
			__asm {
				int 3
			}
		}
	}
	else
	{
		pRet = NULL;
	}


	return pRet;
}

static inline void FreePages(void* pPage, size_t PageSize)
{
#ifdef _WIN32
	Win32NtFreeVirtualMemory(pPage, 0, MEM_RELEASE);
#else

#endif
}

template<typename _Ty>
static constexpr void* GetEntryDataStart(MMV2EntryHeader<_Ty>* pEntry)
{
	return ((uint8_t*)(pEntry + 1)) + pEntry->Offset;
}
template<typename _Ty>
static constexpr void* GetEntryDataStartNoOffset(MMV2EntryHeader<_Ty>* pEntry)
{
	return (pEntry + 1);
}

static ptrdiff_t CheckEntryFitWithSizeAndAlignment(
	void* pPtr,
	size_t EntrySize,
	size_t Size, size_t Alignment
)
{
	/*
	entry would look like this
	Entry = { Header, [optional] offset for alignment, actual memory with added bytes for alignment, footer }
	*/
	ptrdiff_t ret;
	size_t PtrMod = (size_t)pPtr % Alignment;
	if (PtrMod)
		PtrMod = (Alignment - PtrMod);
	size_t TotalSize = PtrMod + Size;
	size_t TotSizeAlign = TotalSize % Alignment;
	if (TotSizeAlign)
		TotalSize += (Alignment - TotSizeAlign);
	ret = (ptrdiff_t)EntrySize - (ptrdiff_t)TotalSize;
	return ret;
}


template<typename _Ty, size_t PageSize, size_t Mult>
static size_t CalculatePageCount(size_t Size, size_t Alignment)
{
	size_t Ret;
	constexpr size_t PageHeaderAndEntryHeader =
		sizeof(MMV2PageHeader<_Ty>) +
		sizeof(MMV2EntryHeader<_Ty>);

	//passing 0 as entry size will let us get how many bytes we need for aligned memory
	// return will be the negative of the size needed
	ptrdiff_t Fit = CheckEntryFitWithSizeAndAlignment((void*)PageHeaderAndEntryHeader, 0, Size, Alignment);
	size_t NeededSize = (-Fit) + sizeof(MMV2EntryFooter<_Ty>);

	size_t NeededPages = NeededSize / PageSize;
	size_t NeededMod = NeededSize % PageSize;
	if (NeededMod)
		NeededPages++;

	NeededPages *= Mult;
	Ret = NeededPages;
	return Ret;
}


template<typename _Ty>
static MMV2EntryHeader<_Ty>* GetNextHeader(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry
)
{
	MMV2EntryFooter<_Ty>* pFooter = GetFooterFromHeader<_Ty>(pPage, pEntry);
	MMV2EntryHeader<_Ty>* pNextHeader = (MMV2EntryHeader<_Ty>*)(pFooter + 1);
	MMV2EntryFooter<_Ty>* pNextFooter;
	if ((size_t)pNextHeader >= ((size_t)pPage + (size_t)pPage->PageSize))
	{
		pNextHeader = NULL;
	}
	else if (pNextHeader->wCanary != IMM_CANARY_WORD)
	{
		//canary error, canary was overwritten
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else
	{
		pNextFooter = GetFooterFromHeader<_Ty>(pPage, pNextHeader);
		if (pNextFooter == NULL)
		{
			__asm {
				int 3
			}
			raise(SIGSEGV);
		}
	}

	return pNextHeader;
}

template<typename _Ty>
static MMV2EntryHeader<_Ty>* GetPrevHeader(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry
)
{
	MMV2EntryFooter<_Ty>* pPrevFooter = ((MMV2EntryFooter<_Ty>*)pEntry - 1);
	MMV2EntryHeader<_Ty>* pPrevHeader = NULL;
	if ((size_t)pPrevFooter < ((size_t)pPage + sizeof(MMV2PageHeader<_Ty>)))
	{
		//pPrevHeader = NULL;
	}
	else if (pPrevFooter->wCanary != IMM_CANARY_WORD)
	{
		//canary error, canary was overwritten
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}
	else
	{
		pPrevHeader = GetHeaderFromFooter<_Ty>(pPage, pPrevFooter);
	}

	return pPrevHeader;
}


template<typename _Ty>
static void VerifyEntry(MMV2EntryHeader<_Ty>* pEntry)
{
	if (pEntry)
	{
		if (pEntry->wCanary != IMM_CANARY_WORD)
		{
			__asm {
				int 3
			}
		}
	}
}

template<typename _Ty>
static size_t ReclaimMemory(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry
)
{
	constexpr size_t HeaderAndFooterSize =
		sizeof(MMV2EntryHeader<_Ty>) +
		sizeof(MMV2EntryFooter<_Ty>);
	size_t Ret = 0;
	if (pEntry->InUse == 0)
	{
		MMV2EntryHeader<_Ty>* pPrevHeader = GetPrevHeader<_Ty>(pPage, pEntry);
		MMV2EntryHeader<_Ty>* pNextHeader = GetNextHeader<_Ty>(pPage, pEntry);
		VerifyEntry<_Ty>(pPrevHeader);
		VerifyEntry<_Ty>(pNextHeader);

		if (pPrevHeader)
		{
			MMV2EntryFooter<_Ty>* pPrevFooter = GetFooterFromHeader<_Ty>(pPage, pPrevHeader);
			if (MergeEmptyEntries<_Ty>(pPage, pPrevHeader, pEntry))
			{
				MMV2EntryHeader<_Ty>* pPrevEnt = pEntry;
				Ret += HeaderAndFooterSize;
				pEntry = pPrevHeader;
				memset(pPrevEnt, 0, sizeof(MMV2EntryHeader<_Ty>));
				memset(pPrevFooter, 0, sizeof(MMV2EntryFooter<_Ty>));
			}
		}
		if (pNextHeader)
		{
			MMV2EntryFooter<_Ty>* pNextFooter = GetFooterFromHeader<_Ty>(pPage, pEntry);
			if (MergeEmptyEntries<_Ty>(pPage, pEntry, pNextHeader))
			{
				MMV2EntryHeader<_Ty>* pPrevEnt = pNextHeader;
				Ret += HeaderAndFooterSize;
				memset(pPrevEnt, 0, sizeof(MMV2EntryHeader<_Ty>));
				memset(pNextFooter, 0, sizeof(MMV2EntryFooter<_Ty>));
			}
		}
	}
	return Ret;
}
/*
			memset(pFooterFirst, 0, sizeof(MMV2EntryFooter<_Ty>));
			memset(pSecond, 0, sizeof(MMV2EntryFooter<_Ty>));
*/
template<typename _Ty>
static bool MergeEmptyEntries(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pFirst, MMV2EntryHeader<_Ty>* pSecond)
{
	bool bRet = false;
	constexpr size_t HeaderAndFooterSize =
		sizeof(MMV2EntryHeader<_Ty>) +
		sizeof(MMV2EntryFooter<_Ty>);

	if (pFirst && pSecond)
	{
		if (pFirst->InUse == 0 && pSecond->InUse == 0)
		{
			VerifyEntry<_Ty>(pFirst);
			VerifyEntry<_Ty>(pSecond);
			GetFooterFromHeader<_Ty>(pPage, pFirst);
			MMV2EntryFooter<_Ty>* pFooterSecond = GetFooterFromHeader<_Ty>(pPage, pSecond);

			pFirst->Size = pFirst->Size + pSecond->Size + HeaderAndFooterSize;
			CreateFooter<_Ty>(pPage, pFirst);

			VerifyEntry<_Ty>(pFirst);

			MMV2EntryHeader<_Ty>* pNewHeader = GetHeaderFromFooter<_Ty>(pPage, pFooterSecond);
			if (pNewHeader != pFirst)
			{
				__asm {
					int 3
				}
			}
			bRet = true;
		}
	}

	return bRet;
}

template<typename _Ty>
static size_t SplitEntry(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry,
	size_t Size,
	MMV2EntryHeader<_Ty>** pNewEntry
)
{
	constexpr size_t HeaderAndFooterSize =
		sizeof(MMV2EntryHeader<_Ty>) +
		sizeof(MMV2EntryFooter<_Ty>);

	size_t Ret = 0;
	MMV2EntryFooter<_Ty>* pOldFooter = GetFooterFromHeader<_Ty>(pPage, pEntry);

	pEntry->Size = Size;
	CreateFooter<_Ty>(pPage, pEntry);
	MMV2EntryFooter<_Ty>* pNewFooter = GetFooterFromHeader<_Ty>(pPage, pEntry);

	MMV2EntryHeader<_Ty>* pNewHeader = (MMV2EntryHeader<_Ty>*)(pNewFooter + 1);
	pNewHeader->Size = (size_t)pOldFooter - (size_t)pNewHeader - sizeof(MMV2EntryHeader<_Ty>);
	pNewHeader->InUse = 0;
	pNewHeader->Offset = 0;
	pNewHeader->Alignment = 1;
	pNewHeader->wCanary = IMM_CANARY_WORD;
	CreateFooter<_Ty>(pPage, pNewHeader);



	MMV2EntryHeader<_Ty>* pCheckOldHeader = GetHeaderFromFooter<_Ty>(pPage, pNewFooter);
	if (pEntry != pCheckOldHeader)
	{
		__asm {
			int 3
		}
	}

	MMV2EntryFooter<_Ty>* pCheckOldFooter = GetFooterFromHeader<_Ty>(pPage, pNewHeader);
	if (pOldFooter != pCheckOldFooter)
	{
		__asm {
			int 3
		}
	}

	*pNewEntry = pNewHeader;

	Ret = Size + HeaderAndFooterSize;
	return Ret;
}

template<typename _Ty>
static void FragmentEntry(
	MMV2PageHeader<_Ty>* pPage,
	MMV2EntryHeader<_Ty>* pEntry,
	size_t Alignment,
	size_t Size,
	ptrdiff_t Fit
)
{
	constexpr size_t HeaderAndFooterSize =
		sizeof(MMV2EntryHeader<_Ty>) +
		sizeof(MMV2EntryFooter<_Ty>);
	constexpr size_t MinimalEntrySize =
		HeaderAndFooterSize +
		16;
	size_t Used = pEntry->Size;
	void* pData = GetEntryDataStart<_Ty>(pEntry);
	size_t LowerAlignment = (size_t)pData % Alignment;
	if (LowerAlignment)
		LowerAlignment = Alignment - LowerAlignment;

	pEntry->InUse = 1;
	pEntry->wCanary = IMM_CANARY_WORD;
	pEntry->Offset = LowerAlignment;
	pEntry->Alignment = Alignment;

	if (Fit >= MinimalEntrySize)
	{
		MMV2EntryHeader<_Ty>* pNewEntry;
		memset(pData, 0, pEntry->Size - Fit);
		Used = SplitEntry<_Ty>(pPage, pEntry, pEntry->Size - Fit, &pNewEntry);
		//defrag the new entry
		size_t ReclaimedMemory = ReclaimMemory<_Ty>(pPage, pNewEntry);
		if (ReclaimedMemory != 0 && ReclaimedMemory != HeaderAndFooterSize && ReclaimedMemory != HeaderAndFooterSize * 2)
		{
			//if page is defraged than it should be equal to HeaderAndFooterSize or 0, the left side entry should always be inuse, if not something broke
			__asm {
				int 3
			}
			raise(SIGSEGV);
		}
		Used -= ReclaimedMemory;
	}
	else
	{
		//Use whole entry as its too small for fragmentation
		memset(pData, 0, pEntry->Size);

	}
	pPage->BytesInUse += Used;
}

template<typename _Ty>
static MMV2EntryHeader<_Ty>* AllocateEntryInList(
	MMV2PageHeader<_Ty>* pPages,
	size_t Alignment,
	size_t Size,
	MMV2PageHeader<_Ty>** ppLastChecked)
{
	MMV2EntryHeader<_Ty>* pRet = NULL;
	MMV2EntryHeader<_Ty>* pEntry = NULL;

	MMV2PageHeader<_Ty>* pCurrPage = pPages;
	MMV2PageHeader<_Ty>* pLastChecked = pPages;

	ptrdiff_t Fit;

	while (pCurrPage)
	{
		if ((pCurrPage->PageSize - pCurrPage->BytesInUse)
			>= Size)
		{
			pEntry = (MMV2EntryHeader<_Ty>*)(pCurrPage + 1);
			while (pEntry)
			{
				if (pEntry->InUse == 0)
				{

					Fit = CheckEntryFitWithSizeAndAlignment(
						GetEntryDataStart(pEntry),
						pEntry->Size,
						Size,
						Alignment
					);
					if (Fit >= 0)
					{
						FragmentEntry<_Ty>(pCurrPage, pEntry, Alignment, Size, Fit);
						pRet = pEntry;
						break;
					}
				}
				pEntry = GetNextHeader<_Ty>(pCurrPage, pEntry);
			}

		}
		if (pRet)
			break;
		pLastChecked = pCurrPage;
		pCurrPage = pCurrPage->pNextPage;
	}
	if (ppLastChecked)
		*ppLastChecked = pLastChecked;
	return pRet;
}

template<typename _Ty, size_t PageSize, size_t PageMult>
static void* AllocateEntry(
	MMV2PageHeader<_Ty>** ppPages,
	size_t Alignment,
	size_t Size)
{
	void* pRet = NULL;
	MMV2PageHeader<_Ty>* pFirstPage = *ppPages;
	MMV2PageHeader<_Ty>* pLastChecked = NULL;
	MMV2EntryHeader<_Ty>* pEntry = AllocateEntryInList<_Ty>(pFirstPage, Alignment, Size, &pLastChecked);
	MMV2PageHeader<_Ty>* pNewPage;

	if (pEntry == NULL)
	{
		size_t AllocatePageCount = CalculatePageCount<_Ty, PageSize, PageMult>(Size, Alignment);
		if (AllocatePageCount)
		{
			pNewPage = AllocatePages<_Ty>(AllocatePageCount);
			if (pNewPage)
			{
				pEntry = AllocateEntryInList<_Ty>(pNewPage, Alignment, Size, 0);

				if (pLastChecked)
					pLastChecked->pNextPage = pNewPage;
				else
					*ppPages = pNewPage;
			}
			else
			{
				//Couldnt allocate page
			}
		}
		else
		{
			//we somehow got 0 pages that needed to be allocated (how?)
			__asm {
				int 3
			}
			raise(SIGSEGV);
		}
	}

	if (pEntry)
		pRet = GetEntryDataStart<_Ty>(pEntry);

	return pRet;
}

void* memman_v2::aligned_alloc(size_t alignment, size_t size)
{
	void* pRet = NULL;
	if (alignment == 0)
		alignment = 1;
	else if (alignment > 64)
		goto cleanup;
	if (size == 0)
		goto cleanup;

	AquireLock(&this->m_Lock);
	if (size < IMM_PAGE_SIZE)
		pRet = AllocateEntry<uint16_t, IMM_PAGE_SIZE, 1>(
			&this->m_pSmallPages,
			alignment, size
		);
	else
		pRet = AllocateEntry<uint64_t, IMM_MEGAPAGE_MIN_SIZE, IMM_MEGAPAGE_MULT>(
			&this->m_pBigPages,
			alignment, size
		);
	FreeLock(&this->m_Lock);

cleanup:
	return pRet;
}

void* memman_v2::malloc(size_t size)
{
	return this->aligned_alloc(1, size);
}

template<typename _Ty>
static MMV2EntryHeader<_Ty>* FindInPage(void* ptr, MMV2PageHeader<_Ty>* pPage)
{
	MMV2EntryHeader<_Ty>* pRet = NULL;
	MMV2EntryHeader<_Ty>* pCurrHeader;
	MMV2EntryFooter<_Ty>* pCurrFooter;
	if ((size_t)ptr > (size_t)pPage + sizeof(MMV2PageHeader<_Ty>))
	{
		if ((size_t)ptr < (size_t)pPage + (size_t)pPage->PageSize)
		{
			pCurrHeader = (MMV2EntryHeader<_Ty>*)(pPage + 1);
			pCurrFooter = GetFooterFromHeader<_Ty>(pPage, pCurrHeader);
			pCurrHeader = GetHeaderFromFooter<_Ty>(pPage, pCurrFooter);
			while (pCurrHeader)
			{

				if ((size_t)ptr == (size_t)GetEntryDataStart<_Ty>(pCurrHeader))
				{
					pRet = pCurrHeader;
					break;
				}
				pCurrHeader = GetNextHeader<_Ty>(pPage, pCurrHeader);
				if (pCurrHeader == NULL)
					break;
				pCurrFooter = GetFooterFromHeader<_Ty>(pPage, pCurrHeader);
			}
		}
	}

	return pRet;
}

template<typename _Ty>
static MMV2EntryHeader<_Ty>* FindEntryAndPage(void* ptr, MMV2PageHeader<_Ty>* pPages, MMV2PageHeader<_Ty>** ppFoundPage, MMV2PageHeader<_Ty>** ppPrevPage)
{
	MMV2EntryHeader<_Ty>* pRet = NULL;
	MMV2PageHeader<_Ty>* pPrev = NULL;
	MMV2PageHeader<_Ty>* pCurr = pPages;
	while (pCurr)
	{
		pRet = FindInPage<_Ty>(ptr, pCurr);
		if (pRet)
			break;

		pPrev = pCurr;
		pCurr = pCurr->pNextPage;
	}

	*ppFoundPage = pCurr;
	*ppPrevPage = pPrev;

	return pRet;
}

template<typename _Ty>
static bool FreeEntry(MMV2PageHeader<_Ty>** ppPages, void* ptr)
{
	constexpr size_t TotalInitialUnuseableMemory =
		sizeof(MMV2PageHeader<_Ty>) +
		sizeof(MMV2EntryHeader<_Ty>) +
		sizeof(MMV2EntryFooter<_Ty>);

	bool bRet = false;
	MMV2PageHeader<_Ty>* pThisPage = NULL;
	MMV2PageHeader<_Ty>* pThisPagePrev = NULL;
	MMV2EntryHeader<_Ty>* pEntry = FindEntryAndPage<_Ty>(ptr, *ppPages, &pThisPage, &pThisPagePrev);
	size_t TotalMemoryReclaimed = 0;
	if (pEntry && pThisPage)
	{
		pEntry->InUse = 0;
		TotalMemoryReclaimed = pEntry->Size;
		memset(ptr, 0, pEntry->Size);

		size_t ReclaimedMemory = ReclaimMemory(pThisPage, pEntry);
		TotalMemoryReclaimed += ReclaimedMemory;
		pThisPage->BytesInUse -= TotalMemoryReclaimed;

		if (pThisPage->BytesInUse == TotalInitialUnuseableMemory)
		{
			if (pThisPagePrev)
			{
				//Not the first page
				pThisPagePrev->pNextPage = pThisPage->pNextPage;
			}
			else
			{
				*ppPages = pThisPage->pNextPage;
			}
			FreePages(pThisPage, pThisPage->PageSize);

		}
		else if (pThisPage->BytesInUse < TotalInitialUnuseableMemory)
		{
			__asm {
				int 3
			}
			raise(SIGSEGV);
		}
		bRet = true;
	}
	else if (pEntry || pThisPage)
	{
		// Invalid return
		__asm {
			int 3
		}
		raise(SIGSEGV);
	}

	return bRet;
}

template<typename _Ty>
static bool GetEntrySize(
	void* ptr,
	MMV2PageHeader<_Ty>* pPages,
	size_t* pSize
)
{
	bool bRet = false;
	MMV2PageHeader<_Ty>* pThisPage = NULL;
	MMV2PageHeader<_Ty>* pThisPagePrev = NULL;
	MMV2EntryHeader<_Ty>* pEntry = FindEntryAndPage<_Ty>(ptr, pPages, &pThisPage, &pThisPagePrev);
	*pSize = 0;
	if (pEntry)
	{
		*pSize = pEntry->Size - pEntry->Offset;
		bRet = true;
	}


	return bRet;
}


void* memman_v2::realloc(void* ptr, size_t size)
{
	//TODO: implement as proper realloc, for now it will be the naive implementation (not what described in this comment)
	//1. find entry
	//2. check if need to enlarge or shrink
	//3a. shrink
	//	4.check if there's enough space for frag
	//		5a. if theres enough space, fragment and defrag the remainder
	//		5b. if not enough space, do nothing
	//3b. enlarge
	//	4. check if there's enough space in the subsequent entry
	//		5a. enough space, merge with subsequent and frag remainder
	//		5b. not enough space, realloc and free original after copy
	void* pRet = NULL;
	bool bFound = false;
	size_t OldSize = 0;
	pRet = this->malloc(size);
	if (pRet)
	{
		if (ptr != 0)
		{
			AquireLock(&this->m_Lock);
			bFound = GetEntrySize<uint16_t>(ptr, this->m_pSmallPages, &OldSize);
			if (!bFound)
				bFound = GetEntrySize<uint64_t>(ptr, this->m_pBigPages, &OldSize);
			FreeLock(&this->m_Lock);
			if (bFound)
				memcpy(pRet, ptr, OldSize);
			else
			{
				this->free(pRet);
				pRet = NULL;
			}
		}
	}
	return pRet;
}

void memman_v2::free(void* ptr)
{
	AquireLock(&this->m_Lock);
	if (!FreeEntry<uint16_t>(&this->m_pSmallPages, ptr))
		FreeEntry<uint64_t>(&this->m_pBigPages, ptr);
	FreeLock(&this->m_Lock);
}

int memman_v2::CheckAlloc(void* ptr)
{
	int nRet = -1;
	bool bFound = false;
	size_t OldSize = 0;
	if (ptr != 0)
	{
		AquireLock(&this->m_Lock);
		bFound = GetEntrySize<uint16_t>(ptr, this->m_pSmallPages, &OldSize);
		if (!bFound)
			bFound = GetEntrySize<uint64_t>(ptr, this->m_pBigPages, &OldSize);
		FreeLock(&this->m_Lock);
		if (bFound)
			nRet = 0;
	}
	return nRet;
}
