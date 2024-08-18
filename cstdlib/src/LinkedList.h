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
#ifndef TOS_LINKED_LIST_H
#define TOS_LINKED_LIST_H

#include <include\stddef.h>
typedef struct _TosLinkedListEntry {
	struct _TosLinkedListEntry* pNext;
	struct _TosLinkedListEntry* pPrev;
}TosLinkedListEntry;

typedef struct _TosLinkedList {
	TosLinkedListEntry* pStart;
	TosLinkedListEntry* pEnd;
}TosLinkedList;

typedef void (*LListEntryUninitializer)(void* pEntry);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	void LListInitialize(TosLinkedList* pList);
	void LListUninitialize(TosLinkedList* pList);
	int LListIsEmpty(TosLinkedList* pList);

	void* LListCreateAtStart(TosLinkedList* pList, size_t Size, size_t FieldOffset);
	void* LListCreateAtEnd(TosLinkedList* pList, size_t Size, size_t FieldOffset);
	void LListDeleteEntry(TosLinkedList* pList, void* pMemory, size_t FieldOffset, LListEntryUninitializer proc);

	
	void LListInsertAtStart(TosLinkedList* pList, TosLinkedListEntry* pEntry);
	void LListInsertAtEnd(TosLinkedList* pList, TosLinkedListEntry* pEntry);
	void LListRemoveEntry(TosLinkedList* pList, TosLinkedListEntry* pEntry);

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // !TOS_LINKED_LIST_H
