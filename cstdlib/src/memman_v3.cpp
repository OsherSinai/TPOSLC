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
#include <include\signal.h>
#include <include\string.h>


#if defined(TOS_KERNEL)
#error No other OSs are supported at this time (memman_base.cpp)
#elif defined(_WIN32)
#include "win32/win32_memory.h"
#else
#error No other OSs are supported at this time (memman_base.cpp)
#endif

#define MMV3_INT3 __asm{int 3}

template<typename _Ty>
static MMV3EntryFooter<_Ty>* BasicGetFooter(MMV3EntryHeader<_Ty>* pHeader)
{
	return (MMV3EntryFooter<_Ty>*)(((size_t)(pHeader + 1)) + pHeader->Size);
}
template<typename _Ty>
static MMV3EntryHeader<_Ty>* BasicGetHeader(MMV3EntryFooter<_Ty>* pFooter)
{
	return (MMV3EntryHeader<_Ty>*)(((size_t)pFooter) - pFooter->wHeaderOffset);
}

template<typename _Ty>
static constexpr void* GetEntryDataStart(MMV3EntryHeader<_Ty>* pEntry)
{
	return ((uint8_t*)(pEntry + 1)) + pEntry->Offset;
}

template<typename _Ty>
static bool ValidateEntry(MMV3EntryHeader<_Ty>* pHeader)
{
	bool bRet = false;
	MMV3EntryFooter<_Ty>* pFooter = BasicGetFooter<_Ty>(pHeader);
	MMV3EntryHeader<_Ty>* pCalcHeader = BasicGetHeader<_Ty>(pFooter);
	if (pHeader->wCanary != IMM_CANARY_WORD)
	{
		MMV3_INT3;
		goto cleanup;
	}
	else if (pFooter->wCanary != IMM_CANARY_WORD)
	{
		MMV3_INT3;
		goto cleanup;
	}
	else if (pCalcHeader != pHeader)
	{
		MMV3_INT3;
		goto cleanup;
	}
	else if (pFooter->wCanary != IMM_CANARY_WORD)
	{
		MMV3_INT3;
		goto cleanup;
	}

	bRet = true;
cleanup:
	return bRet;
}

template<typename _Ty>
static MMV3EntryFooter<_Ty>* CheckedGetFooter(MMV3EntryHeader<_Ty>* pHeader)
{
	MMV3EntryFooter<_Ty>* pFooter = BasicGetFooter<_Ty>(pHeader);
	if (!ValidateEntry<_Ty>(pHeader))
	{
		MMV3_INT3;
	}
	return pFooter;
}
template<typename _Ty>
static MMV3EntryHeader<_Ty>* CheckedGetHeader(MMV3EntryFooter<_Ty>* pFooter)
{
	MMV3EntryHeader<_Ty>* pCalcHeader = BasicGetHeader<_Ty>(pFooter);
	MMV3EntryFooter<_Ty>* pCalcFooter = BasicGetFooter<_Ty>(pCalcHeader);
	if (pCalcFooter != pFooter)
	{
		MMV3_INT3;
	}
	if (!ValidateEntry<_Ty>(pCalcHeader))
	{
		MMV3_INT3;
	}

	return pCalcHeader;
}

template<typename _Ty>
static void RemoveEntryFromLL(MMV3PageHeader<_Ty>* pPage, MMV3EmptyEntryHeader<_Ty>* pEntry)
{
	if (pEntry->LinkedList.pPrev == NULL)
	{
		pPage->pNextInPageFree = pEntry->LinkedList.pNext;
		if (pEntry->LinkedList.pNext)
			pEntry->LinkedList.pNext->LinkedList.pPrev = NULL;
	}
	else
	{
		pEntry->LinkedList.pPrev->LinkedList.pNext = pEntry->LinkedList.pNext;
		if (pEntry->LinkedList.pNext)
			pEntry->LinkedList.pNext->LinkedList.pPrev = pEntry->LinkedList.pPrev;
	}
}

template<typename _Ty>
static void InsertEntryToLL(MMV3PageHeader<_Ty>* pPage, MMV3EmptyEntryHeader<_Ty>* pEntry)
{
	pEntry->LinkedList.pNext = NULL;
	pEntry->LinkedList.pPrev = NULL;
	if (pPage->pNextInPageFree == NULL)
	{
		pPage->pNextInPageFree = pEntry;
	}
	else
	{
		MMV3EmptyEntryHeader<_Ty>* pCurr = pPage->pNextInPageFree;
		while (pCurr && pCurr->LinkedList.pNext && pCurr->LinkedList.pNext < pEntry)
		{
			pCurr = pCurr->LinkedList.pNext;
		}

		if (pEntry < pCurr)
		{
			if (pCurr->LinkedList.pPrev)
			{
				pCurr->LinkedList.pPrev->LinkedList.pNext = pEntry;
				pEntry->LinkedList.pPrev = pCurr->LinkedList.pPrev;
				pEntry->LinkedList.pNext = pCurr;

			}
			else
			{
				pPage->pNextInPageFree = pEntry;
				pEntry->LinkedList.pNext = pCurr;
				pCurr->LinkedList.pPrev = pEntry;

			}
		}
		else if (!pCurr->LinkedList.pNext)
		{
			pCurr->LinkedList.pNext = pEntry;
		}
		else
		{
			pEntry->LinkedList.pNext = pCurr->LinkedList.pNext;
			pCurr->LinkedList.pNext = pEntry;
			pEntry->LinkedList.pNext->LinkedList.pPrev = pEntry;
			pEntry->LinkedList.pPrev = pCurr;
		}

	}
}
template<typename _Ty>
static void InsertEntryToLLAfter(MMV3EmptyEntryHeader<_Ty>* pExistingEntry, MMV3EmptyEntryHeader<_Ty>* pEntryToEntry)
{
	pEntryToEntry->LinkedList.pNext = pExistingEntry->LinkedList.pNext;
	pEntryToEntry->LinkedList.pPrev = pExistingEntry;
	pExistingEntry->LinkedList.pNext = pEntryToEntry;
}
//this function will also remove entry from the empty list and set it as in use
template<typename _Ty>
static MMV3EntryHeader<_Ty>* CreateOrSplitEntry(
	MMV3PageHeader<_Ty>* pPage,
	MMV3EntryHeader<_Ty>* pEntry,
	size_t Size,
	bool bForce)
{
	constexpr size_t HeaderPlusFooter = sizeof(MMV3EntryHeader<_Ty>) + sizeof(MMV3EntryFooter<_Ty>);
	constexpr size_t HeaderPlusFooterPlusLL = HeaderPlusFooter + sizeof(MMV3EmptyEntryLL<_Ty>);
	constexpr size_t HeaderPlusFooterPlusPage = HeaderPlusFooter + sizeof(MMV3PageHeader<_Ty>);
	MMV3EntryHeader<_Ty>* pSplitEntry = NULL;

	if (bForce)
	{
		pEntry->InUse = 0;
		pEntry->Alignment = 1;
		pEntry->Offset = 0;
		pEntry->wCanary = IMM_CANARY_WORD;
		pEntry->Size = pPage->PageSize - HeaderPlusFooterPlusPage;
		auto NewFooter = BasicGetFooter<_Ty>(pEntry);
		NewFooter->wCanary = IMM_CANARY_WORD;
		NewFooter->wHeaderOffset = ((size_t)NewFooter) - ((size_t)pEntry);
		pPage->pNextInPageFree = (MMV3EmptyEntryHeader<_Ty>*)pEntry;
		pPage->pNextInPageFree->LinkedList.pNext = NULL;
		pPage->pNextInPageFree->LinkedList.pPrev = NULL;
		ValidateEntry<_Ty>(pEntry);
	}
	else if (pEntry->Size >= Size + HeaderPlusFooterPlusLL)
	{
		if (!ValidateEntry<_Ty>(pEntry))
		{
			MMV3_INT3;
		}

		RemoveEntryFromLL<_Ty>(pPage, (MMV3EmptyEntryHeader<_Ty>*)pEntry);
		pEntry->InUse = 1;
		auto pOldFooter = BasicGetFooter<_Ty>(pEntry);
		pEntry->Size = Size;
		auto pNewFooter = BasicGetFooter<_Ty>(pEntry);
		pNewFooter->wCanary = IMM_CANARY_WORD;
		pNewFooter->wHeaderOffset = ((size_t)pNewFooter) - ((size_t)pEntry);

		pPage->BytesInUse += pEntry->Size;
		pPage->BytesInUse += HeaderPlusFooter;

		pSplitEntry = (MMV3EntryHeader<_Ty>*)(pNewFooter + 1);
		pSplitEntry->InUse = 0;
		pSplitEntry->Alignment = 1;
		pSplitEntry->Offset = 0;
		pSplitEntry->Size = (size_t)pOldFooter - ((size_t)(pSplitEntry + 1));
		pSplitEntry->wCanary = IMM_CANARY_WORD;
		auto pNewFooter2 = BasicGetFooter<_Ty>(pSplitEntry);
		if (pNewFooter2 != pOldFooter)
		{
			MMV3_INT3;
		}
		pNewFooter2->wHeaderOffset = ((size_t)pNewFooter2) - ((size_t)pSplitEntry);
		if (!ValidateEntry<_Ty>(pEntry))
		{
			MMV3_INT3;
		}
		if (!ValidateEntry<_Ty>(pSplitEntry))
		{
			MMV3_INT3;
		}

		if (pEntry->InUse)
		{
			InsertEntryToLL<_Ty>(pPage, (MMV3EmptyEntryHeader<_Ty>*)pSplitEntry);
		}
		else
		{
			InsertEntryToLLAfter<_Ty>((MMV3EmptyEntryHeader<_Ty>*)pEntry, (MMV3EmptyEntryHeader<_Ty>*)pSplitEntry);
		}
	}
	else
	{
		if (!ValidateEntry<_Ty>(pEntry))
		{
			MMV3_INT3;
		}

		RemoveEntryFromLL<_Ty>(pPage, (MMV3EmptyEntryHeader<_Ty>*)pEntry);
		pEntry->InUse = 1;
		pPage->BytesInUse += pEntry->Size;
		ValidateEntry<_Ty>(pEntry);
	}

	return pSplitEntry;
}

template<typename _Ty>
static void MergeEntries(
	MMV3PageHeader<_Ty>* pPage,
	MMV3EntryHeader<_Ty>* pEntry1,
	MMV3EntryHeader<_Ty>* pEntry2
)
{
	constexpr size_t HeaderPlusFooter = sizeof(MMV3EntryHeader<_Ty>) + sizeof(MMV3EntryFooter<_Ty>);
	//constexpr size_t HeaderPlusFooterPlusLL = HeaderPlusFooter + sizeof(MMV3EmptyEntryLL<_Ty>);
	//constexpr size_t HeaderPlusFooterPlusPage = HeaderPlusFooter + sizeof(MMV3PageHeader<_Ty>);

	MMV3EntryFooter<_Ty>* pFooterEnt1 = CheckedGetFooter<_Ty>(pEntry1);
	MMV3EntryFooter<_Ty>* pFooterEnt2 = CheckedGetFooter<_Ty>(pEntry2);
	MMV3EntryFooter<_Ty>* pNewFooter;
	if (pEntry2->InUse == 0)
		RemoveEntryFromLL<_Ty>(pPage, (MMV3EmptyEntryHeader<_Ty>*)pEntry2);
	else
		goto cleanup;
	pEntry1->Size += pEntry2->Size + HeaderPlusFooter;
	pFooterEnt2->wHeaderOffset = ((size_t)pFooterEnt2) - ((size_t)pEntry1);
	pNewFooter = CheckedGetFooter<_Ty>(pEntry1);
	if (pNewFooter != pFooterEnt2)
	{
		MMV3_INT3;
	}
	if (!ValidateEntry<_Ty>(pEntry1))
	{
		MMV3_INT3
	}
	pPage->BytesInUse -= HeaderPlusFooter;
	memset(pEntry2, 0, sizeof(MMV3EmptyEntryHeader<_Ty>));
	memset(pFooterEnt1, 0, sizeof(MMV3EntryFooter<_Ty>));

cleanup:
	return;
}

template<typename _Ty>
static MMV3EntryHeader<_Ty>* GetNextEntry(
	MMV3PageHeader<_Ty>* pPage,
	MMV3EntryHeader<_Ty>* pEntry)
{
	MMV3EntryFooter<_Ty>* pFooter = CheckedGetFooter<_Ty>(pEntry);
	MMV3EntryHeader<_Ty>* pNext = (MMV3EntryHeader<_Ty>*)(pFooter + 1);
	if ((size_t)pNext >= (((size_t)pPage) + pPage->PageSize))
		pNext = NULL;
	else
	{
		if (!ValidateEntry<_Ty>(pNext))
		{
			MMV3_INT3;
		}
	}
	return pNext;
}

template<typename _Ty>
static MMV3EntryHeader<_Ty>* GetPrevEntry(
	MMV3PageHeader<_Ty>* pPage,
	MMV3EntryHeader<_Ty>* pEntry)
{
	MMV3EntryFooter<_Ty>* pFooter = ((MMV3EntryFooter<_Ty>*)pEntry) - 1;
	MMV3EntryHeader<_Ty>* pPrev = NULL;
	if ((size_t)pFooter > (size_t)(pPage + 1))
	{
		pPrev = CheckedGetHeader<_Ty>(pFooter);
		if (!ValidateEntry<_Ty>(pPrev))
		{
			MMV3_INT3;
		}
	}
	return pPrev;
}

template<typename _Ty>
static void DefragEntries(
	MMV3PageHeader<_Ty>* pPage,
	MMV3EntryHeader<_Ty>* pEntry)
{
	MMV3EntryHeader<_Ty>* pNext = GetNextEntry<_Ty>(pPage, pEntry);
	MMV3EntryHeader<_Ty>* pPrev = GetPrevEntry<_Ty>(pPage, pEntry);
	if (pNext && pNext->InUse == 0)
	{
		MergeEntries<_Ty>(pPage, pEntry, pNext);
	}
	if (pPrev && pPrev->InUse == 0)
	{
		MergeEntries<_Ty>(pPage, pPrev, pEntry);
	}
}


static size_t CalcEntryFitWithSizeAndAlignment(
	void* pPtr,
	size_t EntrySize,
	size_t Size, size_t Alignment
)
{
	/*
	entry would look like this
	Entry = { Header, [optional] offset for alignment, actual memory with added bytes for alignment, footer }
	*/
	size_t PtrMod = (size_t)pPtr % Alignment;
	if (PtrMod)
		PtrMod = (Alignment - PtrMod);
	size_t TotalSize = PtrMod + Size;
	size_t TotSizeAlign = TotalSize % Alignment;
	if (TotSizeAlign)
		TotalSize += (Alignment - TotSizeAlign);
	return TotalSize;
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
	size_t TotalSize = CalcEntryFitWithSizeAndAlignment(pPtr, EntrySize, Size, Alignment);
	ret = (ptrdiff_t)EntrySize - (ptrdiff_t)TotalSize;
	return ret;
}


template<typename _Ty, size_t PageSize, size_t Mult>
static size_t CalculatePageCount(size_t Size, size_t Alignment)
{
	size_t Ret;
	constexpr size_t PageHeaderAndEntryHeader =
		sizeof(MMV3PageHeader<_Ty>) +
		sizeof(MMV3EntryHeader<_Ty>);

	//passing 0 as entry size will let us get how many bytes we need for aligned memory
	// return will be the negative of the size needed
	ptrdiff_t Fit = CheckEntryFitWithSizeAndAlignment((void*)PageHeaderAndEntryHeader, 0, Size, Alignment);
	size_t NeededSize = (-Fit) + sizeof(MMV3EntryFooter<_Ty>);

	size_t NeededPages = NeededSize / PageSize;
	size_t NeededMod = NeededSize % PageSize;
	if (NeededMod)
		NeededPages++;

	NeededPages *= Mult;
	Ret = NeededPages;
	return Ret;
}

template<typename _Ty>
static MMV3EntryHeader<_Ty>* AllocateInPageList(MMV3PageHeader<_Ty>* pPage, size_t Size, size_t Alignment, MMV3PageHeader<_Ty>** ppEnd)
{
	MMV3EntryHeader<_Ty>* pRet = NULL;
	MMV3PageHeader<_Ty>* pPrev = NULL;
	while (pPage)
	{
		if ((pPage->PageSize - pPage->BytesInUse)
			>= Size)
		{
			MMV3EmptyEntryHeader<_Ty>* pEmptyEntry = pPage->pNextInPageFree;
			while (pEmptyEntry)
			{
				MMV3EntryHeader<_Ty>* pEntry = (MMV3EntryHeader<_Ty>*)pEmptyEntry;
				ptrdiff_t Fit = CheckEntryFitWithSizeAndAlignment(
					pEntry + 1,
					pEntry->Size,
					Size,
					Alignment
				);
				if (Fit >= 0)
				{
					size_t TotalSize = CalcEntryFitWithSizeAndAlignment(pEntry + 1,
						pEntry->Size,
						Size,
						Alignment);
					MMV3EntryHeader<_Ty>* pFragment = CreateOrSplitEntry<_Ty>(pPage, pEntry, TotalSize, false);

					size_t LowerAlignment = ((size_t)(pEntry+1)) % Alignment;
					if (LowerAlignment)
						LowerAlignment = Alignment - LowerAlignment;

					pEntry->InUse = 1;
					pEntry->Offset = LowerAlignment;
					memset(pEntry + 1, 0, pEntry->Size);
					if (pFragment)
					{
						DefragEntries<_Ty>(pPage, pFragment);
					}
					pRet = pEntry;
					break;
				}
				pEmptyEntry = pEmptyEntry->LinkedList.pNext;
			}
		}
		if (pRet)
			break;
		pPrev = pPage;
		pPage = pPage->pNextPage;
	}
	if (ppEnd)
		*ppEnd = pPrev;
	return pRet;
}


template<typename _Ty>
static MMV3PageHeader<_Ty>* AllocatePages(size_t PageCount)
{
	constexpr size_t PageHeaderAndEntryHeaderAndFooter = sizeof(MMV3EntryHeader<_Ty>) + sizeof(MMV3EntryFooter<_Ty>) + sizeof(MMV3PageHeader<_Ty>);
	bool bSuccess = false;
	size_t ActualAllocation = 0;
	MMV3PageHeader<_Ty>* pRet = NULL;
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
		MMV3EntryHeader<_Ty>* pEntry = (MMV3EntryHeader<_Ty>*)(pRet + 1);
		CreateOrSplitEntry<_Ty>(pRet, pEntry, 0, true);
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

template<typename _Ty, size_t PageSize, size_t PageMult>
static void* AllocateEntry(MMV3PageHeader<_Ty>** ppPage, size_t Size, size_t Alignment)
{
	void* pRet = NULL;
	MMV3PageHeader<_Ty>* pLastPage = NULL;

	MMV3EntryHeader<_Ty>* pEntry = AllocateInPageList<_Ty>(*ppPage, Size, Alignment, &pLastPage);
	if (!pEntry)
	{
		size_t AllocatePageCount = CalculatePageCount<_Ty, PageSize, PageMult>(Size, Alignment);
		if (AllocatePageCount)
		{
			MMV3PageHeader<_Ty>* pNewPage = AllocatePages<_Ty>(AllocatePageCount);
			if (pNewPage)
			{
				pEntry = AllocateInPageList<_Ty>(pNewPage, Size, Alignment, 0);
				if (pLastPage)
					pLastPage->pNextPage = pNewPage;
				else
					*ppPage = pNewPage;
			}
			else
			{
				MMV3_INT3;
			}
		}
		else
		{
			MMV3_INT3;
		}
	}
	if (pEntry)
	{
		pRet = GetEntryDataStart<_Ty>(pEntry);
	}
	return pRet;
}

memman_v3::memman_v3()
{
	m_Lock = STATIC_INITIALIZE_TOS_LOCK;
	m_pBigPages = NULL;
	m_pSmallPages = NULL;
}
memman_v3::~memman_v3()
{

}

void* memman_v3::aligned_alloc(size_t alignment, size_t size)
{
	void* pRet = NULL;
	if (alignment == 0)
		alignment = 1;
	else if (alignment > 64)
		goto cleanup;
	if (size == 0)
		goto cleanup;
	else if (size < 16)
		size = 16;
	AquireLock(&this->m_Lock);
	if (size < IMM_PAGE_SIZE)
		pRet = AllocateEntry<uint16_t, IMM_PAGE_SIZE, 1>(&this->m_pSmallPages, size, alignment);
	else
		pRet = AllocateEntry<uint64_t, IMM_MEGAPAGE_MIN_SIZE, IMM_MEGAPAGE_MULT>(&this->m_pBigPages, size, alignment);
	FreeLock(&this->m_Lock);
cleanup:
	return pRet;
}

void* memman_v3::malloc(size_t size)
{
	return this->aligned_alloc(1, size);
}

template<typename _Ty>
static MMV3EntryHeader<_Ty>* FindInPage(void* ptr, MMV3PageHeader<_Ty>* pPage)
{
	MMV3EntryHeader<_Ty>* pRet = NULL;
	MMV3EntryHeader<_Ty>* pCurrHeader;
	if ((size_t)ptr > (size_t)pPage + sizeof(MMV3PageHeader<_Ty>))
	{
		if ((size_t)ptr < (size_t)pPage + (size_t)pPage->PageSize)
		{
			pCurrHeader = (MMV3EntryHeader<_Ty>*)(pPage + 1);
			while (pCurrHeader)
			{
				if ((size_t)ptr == (size_t)GetEntryDataStart<_Ty>(pCurrHeader))
				{
					pRet = pCurrHeader;
					break;
				}
				pCurrHeader = GetNextEntry<_Ty>(pPage, pCurrHeader);
				if (pCurrHeader == NULL)
					break;
			}
		}
	}

	return pRet;
}

template<typename _Ty>
static MMV3EntryHeader<_Ty>* FindEntryAndPage(void* ptr, MMV3PageHeader<_Ty>* pPages, MMV3PageHeader<_Ty>** ppFoundPage, MMV3PageHeader<_Ty>** ppPrevPage)
{
	MMV3EntryHeader<_Ty>* pRet = NULL;
	MMV3PageHeader<_Ty>* pPrev = NULL;
	MMV3PageHeader<_Ty>* pCurr = pPages;
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
static void VerifyAndFreePage(MMV3PageHeader<_Ty>** ppPages, MMV3PageHeader<_Ty>* pPageInQuestion, MMV3PageHeader<_Ty>* pPrevPage)
{
	constexpr size_t MinimalPageSize = sizeof(MMV3PageHeader<_Ty>) + sizeof(MMV3EntryHeader<_Ty>) + sizeof(MMV3EntryFooter<_Ty>);
	if (pPageInQuestion->BytesInUse == MinimalPageSize)
	{
		if (*ppPages == pPageInQuestion)
		{
			*ppPages = pPageInQuestion->pNextPage;
		}
		else if (pPrevPage)
		{
			pPrevPage->pNextPage = pPageInQuestion->pNextPage;
		}
		else
		{
			MMV3_INT3;
		}

		FreePages(pPageInQuestion, pPageInQuestion->PageSize);
	}
}

template<typename _Ty>
static bool FreeEntry(void* ptr, MMV3PageHeader<_Ty>** ppPages)
{
	bool bRet = false;
	MMV3PageHeader<_Ty>* pFoundPage = NULL;
	MMV3PageHeader<_Ty>* pPrevPage = NULL;
	MMV3EntryHeader<_Ty>* pEntry = FindEntryAndPage<_Ty>(ptr, *ppPages, &pFoundPage, &pPrevPage);
	if (pEntry)
	{
		pEntry->InUse = 0;
		pEntry->Offset = 1;
		pFoundPage->BytesInUse -= pEntry->Size;
		memset(pEntry + 1, 0, pEntry->Size);
		ValidateEntry<_Ty>(pEntry);
		InsertEntryToLL(pFoundPage, (MMV3EmptyEntryHeader<_Ty>*)pEntry);
		DefragEntries<_Ty>(pFoundPage, pEntry);
		bRet = true;
	}
	if(pFoundPage)
		VerifyAndFreePage<_Ty>(ppPages, pFoundPage, pPrevPage);
	return bRet;
}

void memman_v3::free(void* ptr)
{
	if (ptr)
	{
		AquireLock(&this->m_Lock);
		if (!FreeEntry<uint16_t>(ptr, &this->m_pSmallPages))
			FreeEntry<uint64_t>(ptr, &this->m_pBigPages);
		FreeLock(&this->m_Lock);
	}
}

static bool FindSizeOfEntry(
	void* pPtr,
	MMV3PageHeader<uint16_t>* pSmallPages,
	MMV3PageHeader<uint64_t>* pBigPages,
	size_t* pSize)
{
	bool bRet = false;
	MMV3EntryHeader<uint16_t>* pSmallPtr = NULL;
	MMV3PageHeader<uint16_t>* pSmallFoundPage = NULL;
	MMV3PageHeader<uint16_t>* pSmallPrevPage = NULL;
	MMV3EntryHeader<uint64_t>* pBigPtr = NULL;
	MMV3PageHeader<uint64_t>* pBigFoundPage = NULL;
	MMV3PageHeader<uint64_t>* pBigPrevPage = NULL;
	pSmallPtr = FindEntryAndPage<uint16_t>(pPtr, pSmallPages, &pSmallFoundPage, &pSmallPrevPage);
	if (!pSmallPtr)
	{
		pBigPtr = FindEntryAndPage<uint64_t>(pPtr, pBigPages, &pBigFoundPage, &pBigPrevPage);
		if (pBigPtr)
		{
			*pSize = pBigPtr->Size - pBigPtr->Offset;
			bRet = true;
		}
	}
	else
	{
		if (pSize)
			*pSize = pSmallPtr->Size - pSmallPtr->Offset;
		bRet = true;
	}
	return bRet;
}

void* memman_v3::realloc(void* ptr, size_t size)
{
	bool bHasEntry = false;
	void* pRet = this->malloc(size);
	if (ptr)
	{
		if (pRet)
		{
			size_t EntrySize = 0;
			AquireLock(&this->m_Lock);
			bHasEntry = FindSizeOfEntry(ptr, this->m_pSmallPages, this->m_pBigPages, &EntrySize);
			FreeLock(&this->m_Lock);
			if (bHasEntry)
			{
				if (size > EntrySize)
				{
					memcpy(pRet, ptr, EntrySize);
				}
				else
				{
					memcpy(pRet, ptr, size);
				}
			}
			else
			{
				this->free(pRet);
				pRet = NULL;
			}
		}
		this->free(ptr);
	}
	return pRet;
}

int memman_v3::CheckAlloc(void* ptr)
{
	int nRet = 0;
	size_t EntrySize = 0;
	AquireLock(&this->m_Lock);
	nRet = FindSizeOfEntry(ptr, this->m_pSmallPages, this->m_pBigPages, &EntrySize) == true ? 0 : -1;
	FreeLock(&this->m_Lock);
	return nRet;
}
