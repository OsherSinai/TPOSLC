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
#include <include\string.h>
void* bsearch(const void* key, const void* base,
	size_t nmemb, size_t size,
	int (*compar)(const void*, const void*))
{
	void* pRet = NULL;
	ptrdiff_t offlow = 0;
	ptrdiff_t offhigh = nmemb - 1;
	const void* pElem = base;
	ptrdiff_t offset;

	if (!nmemb)
		goto cleanup;

	while (offlow <= offhigh)
	{ 
		offset = ((offhigh - offlow) >> 1) + offlow;
		pElem = (const void*)((size_t)base + (size * offset));
		int nCompRet = compar(key, pElem);
		if (nCompRet == 0)
		{
			pRet = (void*)pElem;
			break;
		}
		else if(nCompRet < 0)
		{
			offlow = offset + 1;
		}
		else
		{
			offhigh = offset - 1;
		}
	}
cleanup:
	return pRet;
}


static inline constexpr void Swap(void* elem1, void* elem2, size_t nmemb)
{
	while (nmemb)
	{
		uint8_t b = *(uint8_t*)elem1;
		*(uint8_t*)elem1 = *(uint8_t*)elem2;
		*(uint8_t*)elem2 = b;
		elem1 = (uint8_t*)elem1 + 1;
		elem2 = (uint8_t*)elem2 + 1;
		nmemb--;
	}
}


typedef int (*CompProc)(const void* elem1, const void* elem2);
struct QSConsts {
	uint8_t* pData;
	int* pTmp;
	size_t size;
	CompProc proc;
};

/*
* can be optimized by passing the pointer at low already, so we wouldnt need to have pAj
* 
*/
static ptrdiff_t QSortPartition(
	QSConsts* pConsts,
	ptrdiff_t low, 
	ptrdiff_t high)
{
	ptrdiff_t membsize = pConsts->size;
	ptrdiff_t i = low - 1;
	ptrdiff_t j = high + 1;

	uint8_t* pAi = pConsts->pData + membsize * i;
	uint8_t* pAj = pConsts->pData + membsize * j;
	memcpy(pConsts->pTmp, pConsts->pData + membsize * low, membsize);
	
	while (1)
	{
		do {
			i++;
			pAi += membsize;
		} while (pConsts->proc(pAi, pConsts->pTmp) < 0);
		do {
			j--;
			pAj -= membsize;
		} while (pConsts->proc(pAj, pConsts->pTmp) > 0);

		if (i >= j)
			return j;

		Swap(pAi, pAj, membsize);
	}
}
static void QuickSort(QSConsts* pConsts, ptrdiff_t low, ptrdiff_t high)
{
	if (low >= 0 && high >= 0 && low < high)
	{
		ptrdiff_t pivot = QSortPartition(pConsts, low, high);
		QuickSort(pConsts, low, pivot);
		QuickSort(pConsts, pivot+1, high);
	}
}
void qsort(void* base, size_t nmemb, size_t size,
	int (*compar)(const void*, const void*))
{
	QSConsts qsc;
	qsc.pData = (uint8_t*)base;
	qsc.size = size;
	qsc.proc = compar;

	if (size < 1024)
	{
		uint8_t tmp[size];
		qsc.pTmp = (int*)tmp;
		QuickSort(&qsc, 0, nmemb -1);
	}
	else
	{
		qsc.pTmp = (int*)malloc(size);
		if (qsc.pTmp)
		{
			QuickSort(&qsc, 0, nmemb - 1);
			free(qsc.pTmp);
		}
	}
}
