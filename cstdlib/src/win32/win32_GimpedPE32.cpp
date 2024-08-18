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
#include "win32_GimpedPE32.h"
#include "win32_PE32Structures.h"
#include <include\stdlib.h>
#include <include\stdio.h>
#include <include\string.h>
/*
from microsoft's reference, pe format - the tls section

1) At link time, the linker sets the Address of Index field of the TLS directory.
This field points to a location where the program expects to receive the TLS index.

The Microsoft run-time library facilitates this process by defining a memory image of the TLS directory
and giving it the special name "__tls_used" (Intel x86 platforms) or "_tls_used" (other platforms).
The linker looks for this memory image and uses the data there to create the TLS directory.
Other compilers that support TLS and work with the Microsoft linker must use this same technique.

2) When a thread is created, the loader communicates the address of the thread's TLS array by 
placing the address of the thread environment block (TEB) in the FS register (gs on x64).
A pointer to the TLS array is at the offset of 0x2C (0x58 on x64) from the beginning of TEB.
This behavior is Intel x86-specific.

3) The loader assigns the value of the TLS index to the place that was indicated by the Address of Index field.

4) The executable code retrieves the TLS index and also the location of the TLS array.

5) The code uses the TLS index and the TLS array location (multiplying the index by 4 and using it as an offset to the array [8 on x64]) to get the address of the TLS data area for the given program and module.
Each thread has its own TLS data area, but this is transparent to the program, which does not need to know how data is allocated for individual threads.

6) An individual TLS data object is accessed as some fixed offset into the TLS data area.

*/

static void* LoadWholeFileAndSize(const char* szFileName, size_t* pSize)
{
	void* pRet = NULL;
	FILE* pFile = fopen(szFileName, "r");
	*pSize = 0;
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		*pSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		pRet = malloc(*pSize);
		if (pRet)
			fread(pRet, 1, *pSize, pFile);
		fclose(pFile);
	}

	return pRet;
}

static void* OffsetAndVerify(void* ptr, size_t offsetby, size_t* curroffset, size_t totalsize)
{
	void* pRet = NULL;
	if (*curroffset + offsetby <= totalsize)
	{
		(*curroffset) += offsetby;
		pRet = (uint8_t*)ptr + offsetby;
	}
	return pRet;
}

static int OffsetVerify(void* ptr, size_t offsetby, size_t curroffset, size_t totalsize)
{
	int nRet = 0;
	if (curroffset + offsetby <= totalsize)
	{
		(curroffset) += offsetby;
		nRet = 1;
	}
	return nRet;
}
#define W32_GPE32_ADVANCE(struc) {\
	ptr = OffsetAndVerify(ptr, sizeof(struc), &curroff, size);\
	if(ptr == NULL) goto cleanup;\
}
#define W32_GPE32_LIT(off) {\
	ptr = OffsetAndVerify(ptr, off, &curroff, size);\
	if(ptr == NULL) goto cleanup;\
}
#define W32_VERIFY_SIZE(off) {\
	int n = OffsetVerify(ptr, sizeof(off), curroff, size);\
	if(n == 0) goto cleanup;\
}
#define W32_VERIFY_SIZE_LIT(off) {\
	int n = OffsetVerify(ptr, off, curroff, size);\
	if(n == 0) goto cleanup;\
}


static ptrdiff_t FindTlsSectionRawSize(void* ptr, size_t size)
{
	ptrdiff_t Ret = -1;
	size_t curroff = 0;
	uint8_t name[9] = {0};
	COFF_MSDOSStub* pDos = (COFF_MSDOSStub*)ptr;
	COFF_Header* pCoff;
	uint16_t* pMagic;
	//PE32_Optional_Header* pOH32;

	//PE32P_Optional_Header* pOH32P;

	PE32_Image_Section_Header* pISH;
	W32_GPE32_LIT(pDos->PEOffset);
	pCoff = (COFF_Header*)ptr;
	W32_VERIFY_SIZE(COFF_Header);
	if (pCoff->SizeOfOptionalHeader == 0)
		goto cleanup;
	W32_GPE32_ADVANCE(COFF_Header);
	pMagic = (uint16_t*)ptr;
	W32_VERIFY_SIZE(uint16_t);
	W32_GPE32_ADVANCE(uint16_t);
	if (*pMagic == PE32_OPTIONAL_HEADER_MAGIC_PE32)
	{
		W32_VERIFY_SIZE(PE32_Optional_Header);
		//pOH32 = (PE32_Optional_Header*)ptr;
		W32_GPE32_ADVANCE(PE32_Optional_Header);
		W32_VERIFY_SIZE_LIT(pCoff->NumberOfSections * sizeof(PE32_Image_Section_Header));

	}
	else if (*pMagic == PE32_OPTIONAL_HEADER_MAGIC_PE32P)
	{
		W32_VERIFY_SIZE(PE32P_Optional_Header);
		//pOH32P = (PE32P_Optional_Header*)ptr;
		W32_GPE32_ADVANCE(PE32P_Optional_Header);
		W32_VERIFY_SIZE_LIT(pCoff->NumberOfSections * sizeof(PE32_Image_Section_Header));
	}
	else
		goto cleanup;
	
	pISH = (PE32_Image_Section_Header*)ptr;
	for (size_t i = 0; i < pCoff->NumberOfSections; i++)
	{
		PE32_Image_Section_Header* pCurr = pISH + i;
		memcpy(name, pCurr->Name, 8);
		if (strcmp((char*)name, ".tls") == 0)
		{
			Ret = pCurr->SizeOfRawData;
			break;
		}
		else if (strcmp((char*)name, ".tls$") == 0)
		{
			Ret = pCurr->SizeOfRawData;
			break;
		}
	}

cleanup:
	return Ret;
}

ptrdiff_t _tos_GetTLSSize(const char* szFileName)
{
	ptrdiff_t ret = -1;
	size_t FileSize;
	void* pFile = LoadWholeFileAndSize(szFileName, &FileSize);
	if (pFile)
	{
		ret = FindTlsSectionRawSize(pFile, FileSize);
		free(pFile);
	}
	return ret;
}
