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
#include "win32_tls.h"
#include "win32_ntdll.h"
#include "win32_memory.h"
#include <include\string.h>
#include <include\stdlib.h>

#include "../lock.h"
static tos_lock g_win32_tls_lock = STATIC_INITIALIZE_TOS_LOCK;

RTL_BITMAP* PEBGetTlsBitmap()
{
	RTL_BITMAP* TlsBitmap;
	__asm {
		mov rbx, qword ptr gs : [30h]
		mov rcx, qword ptr[rbx + 60h]
		mov rcx, qword ptr[rcx + 78h]
		mov qword ptr[TlsBitmap], rcx
	}
	return TlsBitmap;
}

RTL_BITMAP* PEBGetTlsExpansionBitmap()
{
	RTL_BITMAP* TlsExpansionBitmap;
	__asm {
		mov rbx, qword ptr gs : [30h]
		mov rcx, qword ptr[rbx + 60h]
		mov rcx, qword ptr[rcx + 238h]
		mov qword ptr[TlsExpansionBitmap], rcx
	}
	return TlsExpansionBitmap;
}

void** PEBGetTlsSlots()
{
	void** tlsSlots;
	__asm {
		mov rbx, qword ptr gs : [30h]
		lea rbx, qword ptr[rbx + 1480h]
		mov qword ptr[tlsSlots], rbx
	}
	return tlsSlots;
}

void*** PEBGetTlsExpansionSlot()
{
	void*** tlsSlots;
	__asm {
		mov rbx, qword ptr gs : [30h]
		lea rdx, qword ptr[rbx + 1780h]
		mov qword ptr[tlsSlots], rdx
	}
	return tlsSlots;
}


void* PEBGetProcessHeap()
{
	uint64_t** tlsSlots;
	__asm {
		mov rbx, qword ptr gs : [60h]
		mov rdx, qword ptr[rbx + 30h]
		mov qword ptr[tlsSlots], rdx
	}
	return tlsSlots;
}

ULONG RtlFindClearBitAndSet(RTL_BITMAP* pBitmap, ULONG NumberToFind, ULONG Hint)
{
	//total mix tls available is 0x440

	//Error is 0xFFFFFFFF
	//Hint is the start
	//NumberToFind BitsNeeded
	ULONG Ret = ~0;
	int64_t BitsToFind = NumberToFind;
	uint64_t BitIndex = Hint;
	int64_t StartBits = ~0;
	uint64_t conqbits = 0;
	if (BitIndex >= pBitmap->SizeOfBitmap)
		BitIndex = 0;
	for (uint32_t i = 0; i < pBitmap->SizeOfBitmap; i++)
	{
		uint64_t bitpos = BitIndex & 07;
		uint64_t bytepos = BitIndex >> 3;

		if (((pBitmap->Buffer[bytepos] >> bitpos) & 0x1) == 0)
		{
			if (StartBits != ~0)
			{
				conqbits++;
			}
			else
			{
				StartBits = BitIndex;
				conqbits = 1;
			}
		}
		else
		{
			StartBits = -1;
			conqbits = 0;
		}

		if (conqbits >= BitsToFind)
			break;
		BitIndex++;
		if (BitIndex > pBitmap->SizeOfBitmap)
			BitIndex = 0;
	}

	if (StartBits > -1)
	{
		Ret = StartBits;
		BitIndex = StartBits;
		for (uint64_t i = 0; i < conqbits; i++)
		{
			uint64_t bitpos = BitIndex & 07;
			uint64_t bytepos = BitIndex >> 3;
			pBitmap->Buffer[bytepos] |= 0x1 << bitpos;
			BitIndex++;
			if (BitIndex > pBitmap->SizeOfBitmap)
				BitIndex = 0;
		}
	}

	return Ret;

}

BOOL RtlAreBitsSet(RTL_BITMAP* pBitmap, uint32_t idx, uint32_t count)
{
	BOOL bRet = TRUE;

	uint64_t BitIndex = idx;
	if (idx < pBitmap->SizeOfBitmap)
	{
		for (uint64_t i = 0; i < count; i++)
		{
			uint64_t bitpos = BitIndex & 07;
			uint64_t bytepos = BitIndex >> 3;
			if (((pBitmap->Buffer[bytepos] >> bitpos) & 0x1) == 0)
			{
				bRet = FALSE;
				break;
			}
			BitIndex++;
			if (BitIndex > pBitmap->SizeOfBitmap)
				BitIndex = 0;
		}
	}
	else
		bRet = FALSE;

	return bRet;
}

BOOL RtlClearBits(RTL_BITMAP* pBitmap, uint32_t idx, uint32_t count)
{
	BOOL bRet = TRUE;

	uint64_t BitIndex = idx;
	for (uint64_t i = 0; i < count; i++)
	{
		uint64_t bitpos = BitIndex & 07;
		uint64_t bytepos = BitIndex >> 3;
		pBitmap->Buffer[bytepos] &= ~(0x1 << bitpos);
		BitIndex++;
		if (BitIndex > pBitmap->SizeOfBitmap)
			BitIndex = 0;
	}

	return bRet;
}

void* RtlAllocateHeap(void* HeapHandle, ULONG Flags, size_t Size)
{
	
	void* pAddr = 0;
	size_t actual_alloc = 0;
	WinNtStatus stat = Win32NtAllocateVirtualMemory(
		&pAddr,
		Size,
		MEM_COMMIT, 
		PAGE_READWRITE,
		&actual_alloc);
	if (stat == WinNtStatus::Success)
	{
		memset(pAddr, 0, Size);
	}
	else
	{
		pAddr = 0;
	}
	return pAddr;
	// real allocation on windows should call RtlAllocateHeap, im not going to implement this
	//return RtlAllocateHeap(HeapHandle, Flags, Size);
}

DWORD TlsAlloc()
{
	void** tlsSlots = PEBGetTlsSlots();
	RTL_BITMAP* TlsBitmap = PEBGetTlsBitmap();
	RTL_BITMAP* TlsExpansionBitmap = PEBGetTlsExpansionBitmap();
	void*** ppTlsExpansionSlot = PEBGetTlsExpansionSlot();

	AquireLock(&g_win32_tls_lock);
	//process lock
	ULONG position = RtlFindClearBitAndSet(TlsBitmap, 1, 0);
	if (position != ~0)
	{
		//release process lock
		tlsSlots[position] = 0;
		FreeLock(&g_win32_tls_lock);
		return position;
	}

	if (*ppTlsExpansionSlot == nullptr)
	{
		//allocate expansion tls
		void* pHeap = PEBGetProcessHeap();
		//8 == HEAP_ZERO_MEMORY
		*ppTlsExpansionSlot = (void**)RtlAllocateHeap(pHeap, 8, 0x2000);
		if (*ppTlsExpansionSlot == nullptr)
		{
			FreeLock(&g_win32_tls_lock);
			return ~0;
		}
	}

	position = RtlFindClearBitAndSet(TlsExpansionBitmap, 1, 0);
	if (position != ~0)
	{
		(*ppTlsExpansionSlot)[position] = 0;

		FreeLock(&g_win32_tls_lock);
		return position + 0x40;
	}

	FreeLock(&g_win32_tls_lock);
	return ~0;
}

BOOL TlsFree(DWORD dwTlsIndex)
{
	BOOL bRet = FALSE;
	uint32_t dwIdx = dwTlsIndex;
	RTL_BITMAP* pBmp;
	void** pTlsSlots;
	if (dwIdx < 0x40)
	{
		pTlsSlots = PEBGetTlsSlots();
		pBmp = PEBGetTlsBitmap();
	}
	else
	{
		pTlsSlots = *PEBGetTlsExpansionSlot();
		dwIdx -= 0x40;
		pBmp = PEBGetTlsExpansionBitmap();
	}

	AquireLock(&g_win32_tls_lock);
	//aquire peb lock
	if (RtlAreBitsSet(pBmp, dwIdx, 1))
	{
		//HANDLE CurrHandle = NtCurrentThread();
		//Windows call to NtSetInformationThread, theres not much point for this
		//if (NtSetInformationThread(CurrHandle, 10, &dwTlsIndex, 4) >= 0)
		{
			if (pTlsSlots)
				pTlsSlots[dwIdx] = NULL;

			RtlClearBits(pBmp, dwIdx, 1);
			bRet = TRUE;
		}
	}
	//free peb lock
	FreeLock(&g_win32_tls_lock);
	return bRet;
}

BOOL TlsSetValue(DWORD dwTlsIndex, void* pTlsValue)
{
	if (dwTlsIndex < 0x40)
	{
		PEBGetTlsSlots()[dwTlsIndex] = pTlsValue;
	}
	else
	{
		void*** ppExtTlsSlots = PEBGetTlsExpansionSlot();
		if (*ppExtTlsSlots == nullptr)
		{
			//allocate expansion tls
			void* pHeap = PEBGetProcessHeap();
			*ppExtTlsSlots = (void**)RtlAllocateHeap(pHeap, 8, 0x2000);
			if (*ppExtTlsSlots == nullptr)
				return FALSE;
		}
		(*ppExtTlsSlots)[dwTlsIndex - 0x40] = pTlsValue;
	}
	return TRUE;
}

LPVOID TlsGetValue(DWORD dwTlsIndex)
{
	void* pRet;
	if (dwTlsIndex < 0x40)
	{
		pRet = PEBGetTlsSlots()[dwTlsIndex];
	}
	else
	{
		void*** ppExtTlsSlots = PEBGetTlsExpansionSlot();
		pRet = nullptr;
		if (*ppExtTlsSlots)
			pRet = (*ppExtTlsSlots)[dwTlsIndex - 0x40];
	}
	return pRet;
}

void FreeExpansionTlsSlots()
{
	void*** ppTlsExpansionSlot = PEBGetTlsExpansionSlot();
	if (*ppTlsExpansionSlot != nullptr)
	{
		//if were using an actual RtlAllocateHeap then we dont really need this function
		// the thread termination in end of the thread in ntdll calls RtlFreeHeap

		Win32NtFreeVirtualMemory(*ppTlsExpansionSlot, 0, MEM_FREE);
		*ppTlsExpansionSlot = NULL;
	}
}

extern "C" uint32_t _tls_index;
static void* swap_tls_slot(void* pnew, uint32_t tslot)
{
	void* pRet;
	__asm {
		mov ecx, dword ptr[tslot]
		mov rax, qword ptr gs : [58h]
		lea rdx, qword ptr[rax + rcx * 8]
		mov rcx, qword ptr[rdx]
		mov qword ptr[pRet], rcx
		mov rax, qword ptr[pnew]
		mov qword ptr[rdx], rax
	}
	return pRet;
}

extern "C" char** g_argv;
extern "C" int g_argc;

extern "C" ptrdiff_t _tos_GetTLSSize(const char* szFileName);
extern "C" int _tos_InitializeStaticTls(void** ppOld)
{
	//this function only initialize the static tls of the current exe+tosclib
	// if you want to extend this for all loaded dlls then you need to:
	// 1) search which loaded dlls contain tls
	// 2) out of those map tls size needed for each
	// 3) detect tls index of each
	// 4) call swap_tls_slot for each tls index
	// additionaly, you need to swap the ppOld variable to be allocated by this function
	int nRet = -1;
	ptrdiff_t tlsSize = 0;
	void* pNewStaticTls;
	if (g_argv)
	{
		tlsSize = _tos_GetTLSSize(*g_argv);
		if (tlsSize > 0)
		{
			pNewStaticTls = malloc(tlsSize);
			if (pNewStaticTls)
			{
				memset(pNewStaticTls, 0, tlsSize);
				ppOld[0] = swap_tls_slot(pNewStaticTls, _tls_index);
				nRet = 0;
			}
		}
	}

	return nRet;
}

extern "C" void _tos_UninitializeStaticTls(void** ppOld)
{
	// see initialize function for instructions on how to extend this function
	void* p;
	if (ppOld)
	{
		if (ppOld[0])
		{
			p = swap_tls_slot(ppOld[0], _tls_index);
			if (p)
				free(p);
		}
	}
}