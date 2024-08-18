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
#include "LinkedList.h"
#include <include\stdint.h>
#include <include\stddef.h>
#include <include\stdlib.h>

extern "C" {

	void LListInitialize(TosLinkedList* pList)
	{
		pList->pStart = NULL;
		pList->pEnd = NULL;
	}
	void LListUninitialize(TosLinkedList* pList)
	{
		TosLinkedListEntry* pStartAt = pList->pStart;
		TosLinkedListEntry* pCurr = pList->pStart;
		TosLinkedListEntry* pNext;

		while (pCurr && pStartAt != pCurr)
		{
			pNext = pCurr->pNext;
			free(pCurr);
			pCurr = pNext;
		}
	}
	int LListIsEmpty(TosLinkedList* pList)
	{
		return (!pList->pStart && !pList->pEnd);
	}


	void* LListCreateAtStart(TosLinkedList* pList, size_t Size, size_t FieldOffset)
	{
		void* ptr = malloc(Size);
		TosLinkedListEntry* pEntry;
		if (ptr)
		{
			TosLinkedListEntry* pPrevEntry = pList->pStart;
			pEntry = (TosLinkedListEntry*)((uint8_t*)ptr + FieldOffset);
			pList->pStart = pEntry;
			if(pList->pEnd == NULL)
				pList->pEnd= pEntry;
			pEntry->pPrev = 0;
			pEntry->pNext = pPrevEntry;
			if (pPrevEntry)
				pPrevEntry->pPrev = pEntry;
		}
		return ptr;
	}
	void* LListCreateAtEnd(TosLinkedList* pList, size_t Size, size_t FieldOffset)
	{
		void* ptr = malloc(Size);
		TosLinkedListEntry* pEntry;
		if (ptr)
		{
			TosLinkedListEntry* pPrevEntry = pList->pEnd;
			pEntry = (TosLinkedListEntry*)((uint8_t*)ptr + FieldOffset);
			pList->pEnd = pEntry;
			if (pList->pStart == NULL)
				pList->pStart = pEntry;
			pEntry->pPrev = pPrevEntry;
			pEntry->pNext = 0;
			if (pPrevEntry)
				pPrevEntry->pNext = pEntry;
		}
		return ptr;
	}
	void LListDeleteEntry(TosLinkedList* pList, void* pMemory, size_t FieldOffset, LListEntryUninitializer proc)
	{
		TosLinkedListEntry* pEntry = (TosLinkedListEntry*)((uint8_t*)pMemory + FieldOffset);
		if (pEntry->pNext)
			pEntry->pNext->pPrev = pEntry->pPrev;
		if (pEntry->pPrev)
			pEntry->pPrev->pNext = pEntry->pNext;

		if (pList->pStart == pEntry)
			pList->pStart = pEntry->pNext;
		if (pList->pEnd == pEntry)
			pList->pEnd = pEntry->pPrev;

		if (proc)
			proc(pMemory);

		free(pMemory);
	}


	void LListInsertAtStart(TosLinkedList* pList, TosLinkedListEntry* pEntry)
	{
		TosLinkedListEntry* pPrevEntry = pList->pStart;
		if (pList->pEnd == NULL)
			pList->pEnd = pEntry;
		pList->pStart = pEntry;
		pEntry->pPrev = 0;
		pEntry->pNext = pPrevEntry;
		if (pPrevEntry)
			pPrevEntry->pPrev = pEntry;
	}
	void LListInsertAtEnd(TosLinkedList* pList, TosLinkedListEntry* pEntry)
	{
		TosLinkedListEntry* pPrevEntry = pList->pEnd;
		if (pList->pStart == NULL)
			pList->pStart = pEntry;
		pList->pEnd = pEntry;
		pEntry->pPrev = pPrevEntry;
		pEntry->pNext = 0;
		if (pPrevEntry)
			pPrevEntry->pNext = pEntry;
	}
	void LListRemoveEntry(TosLinkedList* pList, TosLinkedListEntry* pEntry)
	{
		if (pEntry->pNext)
			pEntry->pNext->pPrev = pEntry->pPrev;
		if (pEntry->pPrev)
			pEntry->pPrev->pNext = pEntry->pNext;

		if (pList->pStart == pEntry)
			pList->pStart = pEntry->pNext;
		if (pList->pEnd == pEntry)
			pList->pEnd = pEntry->pPrev;
		pEntry->pNext = NULL;
		pEntry->pPrev = NULL;
	}
};