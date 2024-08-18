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
#include <include\ctype.h>
#include <include\string.h>
#include <include\stdbool.h>
#include <include\threads.h>
#include <include\errno.h>
#include "TOSThreadEnvironmentBlock.h"
void* memcpy(
	void* restrict s1,
	const void* restrict s2,
	size_t n)
{
	void* pRet = s1;
	for (; n != 0; n--)
	{
		*((uint8_t*)s1) = *((uint8_t*)s2);
		s1 = ((uint8_t*)s1) + 1;
		s2 = ((uint8_t*)s2) + 1;
	}
	return pRet;
}

static void* memcpy_reverse(
	void* restrict s1,
	const void* restrict s2,
	size_t n)
{
	void* pRet = s1;
	s1 = ((uint8_t*)s1) + n - 1;
	s2 = ((uint8_t*)s2) + n - 1;
	for (; n != 0; n--)
	{
		*((uint8_t*)s1) = *((uint8_t*)s2);
		s1 = ((uint8_t*)s1) - 1;
		s2 = ((uint8_t*)s2) - 1;
	}
	return pRet;
}
static inline bool CheckOverlap(void* s1, const void* s2, size_t n, bool* pS1Overlap)
{
	bool bRet = false;
	size_t s1s = (size_t)s1;
	size_t s2s = (size_t)s2;
	*pS1Overlap = false;
	if (s1s < s2s)
	{
		if (s1s + n < s2s)
		{
			// no overlap
		}
		else
		{
			// overlap
			bRet = true;
			*pS1Overlap = true;
		}
	}
	else
	{

		if (s2s + n < s1s)
		{
			// no overlap
		}
		else
		{
			// overlap
			bRet = true;
		}
	}
	return bRet;
}
void* memmove(void* s1, const void* s2, size_t n)
{
	bool bOverlapType = false;
	if (CheckOverlap(s1, s2, n, &bOverlapType))
	{
		// the buffers overlap
		if (bOverlapType)
		{
			// we will overwrite the first bytes of s2 after theyre copied so we can safely just memcpy
			memcpy(s1, s2, n);
		}
		else
		{
			// we will overwrite some bytes of s2 before theyre copied so we need to copy the memory in reverse
			memcpy_reverse(s1, s2, n);
		}
	}
	else
	{
		memcpy(s1, s2, n);
	}
	return s1;
}

char* strcpy(
	char* restrict s1,
	const char* restrict s2
)
{
	char* pRet = s1;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = *s2;
	return pRet;
}

char* strncpy(
	char* restrict s1,
	const char* restrict s2,
	size_t n
)
{
	char* pRet = s1;
	while (n && *s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	while (n)
	{
		*s1 = 0;
		s1++;
		n--;
	}
	return pRet;
}


char* strcat(
	char* restrict s1,
	const char* restrict s2
)
{
	char* pRet = s1;

	while (*s1 != 0)
		s1++;

	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = 0;

	return pRet;
}

char* strncat(
	char* restrict s1,
	const char* restrict s2,
	size_t n
)
{
	char* pRet = s1;

	while (*s1 != 0 && n)
	{
		s1++;
	}

	while (*s2 && n)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	while (n)
	{
		*s1 = 0;
		s1++;
		n--;
	}
	return pRet;
}

//TODO: fix strxfrm
size_t strxfrm(char* restrict s1, const char* restrict s2, size_t n)
{
	size_t ret = strlen(s2);
	if (s1)
		memcpy(s1, s2, ret);
	return ret;
}

int memcmp(const void* s1, const void* s2, size_t b)
{
	int nRet = 0;

	while (b)
	{
		if (*(uint8_t*)s1 != *(uint8_t*)s2)
			break;
		s1 = ((uint8_t*)s1) + 1;
		s2 = ((uint8_t*)s2) + 1;
		b--;
	}
	if (b)
		nRet = *(uint8_t*)s1 - *(uint8_t*)s2;

	return nRet;
}

int strcmp(const char* s1, const char* s2)
{
	int nRet = 0;

	while (*s1 && *s2)
	{
		if (*(uint8_t*)s1 != *(uint8_t*)s2)
			break;
		s1++;
		s2++;
	}
	nRet = *(uint8_t*)s1 - *(uint8_t*)s2;

	return nRet;
}

int strcoll(const char* s1, const char* s2)
{
	int nRet = 0;

	while (tolower(*s1) == tolower(*s2))
	{
		nRet = *s1 - *s2;
		if (nRet != 0 || *s1 == 0)
			break;
		s1++;
		s2++;
	}
	if (*s1 != 0 || *s2 != 0)
	{
		nRet = *s1 - *s2;
	}
	return nRet;
}

int strncmp(const char* s1, const char* s2, size_t n)
{
	int nRet = 0;

	while (*s1 && *s2 && n)
	{
		if (*(uint8_t*)s1 != *(uint8_t*)s2)
			break;
		s1++;
		s2++;
		n--;
	}
	if(n)
		nRet = *(uint8_t*)s1 - *(uint8_t*)s2;

	return nRet;
}

void* memchr(const void* s, int c, size_t n)
{
	void* pRet = NULL;
	uint8_t newc = (uint8_t)c;
	while (n && (*(uint8_t*)s != newc))
	{
		s = (uint8_t*)s + 1;
		n--;
	}
	if (*(uint8_t*)s == newc)
		pRet = (void*)s;

	return pRet;
}
char* strchr(const char* s, int c)
{
	char* pRet = NULL;
	char newc = (char)c;
	while (*s && (*s != newc))
		s++;
	if (*s == newc)
		pRet = (char*)s;

	return pRet;
}

static bool IsPresent(const char* s, char c)
{
	bool bRet = false;
	while (*s)
	{
		if (*s == c)
		{
			bRet = true;
			break;
		}
		s++;
	}
	return bRet;
}
size_t strcspn(const char* s1, const char* s2)
{
	size_t Ret = 0;
	
	while (*s1)
	{
		if (IsPresent(s2, *s1) == true)
			break;
		Ret++;
		s1++;
	}

	return Ret;
}

char* strpbrk(const char* s1, const char* s2)
{
	char* pRet = NULL;

	while (*s1)
	{
		if (IsPresent(s2, *s1) == true)
		{
			pRet = (char*)s1;
			break;
		}
		s1++;
	}
	return pRet;
}

char* strrchr(const char* s, int c)
{
	char* pRet = NULL;
	char newc = (char)c;

	while (*s)
	{
		if (*s == newc)
			pRet = (char*)s;
		s++;
	}

	if (*s == newc)
		pRet = (char*)s;

	return pRet;
}

size_t strspn(const char* s1, const char* s2)
{
	size_t Ret = 0;

	while (*s1)
	{
		if (IsPresent(s2, *s1) == false)
			break;
		Ret++;
		s1++;
	}

	return Ret;
}

inline static bool ContainSubstr(const char* s1, const char* s2)
{
	bool bRet = false;

	while (*s1 && *s2 && *s1 == *s2) {
		s1++;
		s2++;
	}
	bRet = *s2 == 0;

	return bRet;
}
char* strstr(const char* s1, const char* s2)
{
	char* pRet = NULL;

	while (*s1)
	{
		if (ContainSubstr(s1, s2) == true)
		{
			pRet = (char*)s1;
			break;
		}
		s1++;
	}
	return pRet;
}

void* memset(void* s, int c, size_t n)
{
	void* pRet = s;
	uint8_t newc = (uint8_t)c;
	while (n)
	{
		*(uint8_t*)s = newc;
		s = (uint8_t*)s + 1;
		n--;
	}
	return pRet;
}
size_t strlen(const char* s)
{
	size_t len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	
	return len;
}

char* strtok(char* restrict s1,
	const char* restrict seq)
{
	char** ppInterstr = &_tos_GetTEB()->pStrtok;
	char* pRet = NULL;
	char* pTmp = NULL;
	/*
	if (s1)
	{
		*ppInterstr = s1;
		pRet = *ppInterstr;
	}
	if (*ppInterstr)
	{
		do
		{
			pTmp = strpbrk(*ppInterstr, seq);
			if (*ppInterstr == pTmp)
			{
				*ppInterstr++;
			}
		} while (pTmp);

		if (pTmp)
		{
			*ppInterstr = pTmp;
			pTmp = strpbrk(*ppInterstr, seq);
			if (pTmp)
			{
				pRet = *ppInterstr;
				*ppInterstr = pTmp + 1;
				*pTmp = 0;
			}
			else
			{
				pRet = *ppInterstr;
				*ppInterstr = NULL;
			}
		}
		else
		{
			*ppInterstr = NULL;
		}
	}
	*/

	if (s1)
	{
		*ppInterstr = s1;
		pRet = *ppInterstr;
	}
	if (*ppInterstr)
	{
		do
		{
			if (*ppInterstr == pTmp)
				(*ppInterstr)++;
			pTmp = strpbrk(*ppInterstr, seq);
		} while (*ppInterstr == pTmp);

		if (pTmp)
		{
			pRet = *ppInterstr;
			*pTmp = 0;
			*ppInterstr = pTmp + 1;
		}
		else
		{
			if (**ppInterstr == '\0')
				pRet = NULL;
			else
				pRet = *ppInterstr;
			*ppInterstr = NULL;
		}
	}
	return pRet;
}
#define TOS_STRERROR_CASE(d, s) case d: pRet = s; break
char* strerror(int errnum)
{
	const char* pRet = NULL;
	int nError = errnum;
	if (nError == 0)
	{
		nError = errno;
	}

	switch (nError)
	{
		TOS_STRERROR_CASE(0, "Success");
		TOS_STRERROR_CASE(EPERM		 , "Operation not permitted.");
		TOS_STRERROR_CASE(ENOENT		 , "No such file or directory.");
		TOS_STRERROR_CASE(ESRCH		 , "No such process.");
		TOS_STRERROR_CASE(EINTR		 , "Interrupted system call.");
		TOS_STRERROR_CASE(EIO			 , "I/O error.");
		TOS_STRERROR_CASE(ENXIO		 , "No such device or address.");
		TOS_STRERROR_CASE(E2BIG		 , "Argument list too long.");
		TOS_STRERROR_CASE(ENOEXEC		 , "Exec format error.");
		TOS_STRERROR_CASE(EBADF		 , "Bad file number.");
		TOS_STRERROR_CASE(ECHILD		, "No child processes.");
		TOS_STRERROR_CASE(EAGAIN		, "Try again.");
		TOS_STRERROR_CASE(ENOMEM		, "Out of memory.");
		TOS_STRERROR_CASE(EACCES		, "Permission denied.");
		TOS_STRERROR_CASE(EFAULT		, "Bad address.");
		TOS_STRERROR_CASE(ENOTBLK		, "Block device required.");
		TOS_STRERROR_CASE(EBUSY		, "Device or resource busy.");
		TOS_STRERROR_CASE(EEXIST		, "File exists.");
		TOS_STRERROR_CASE(EXDEV		, "Cross-device link.");
		TOS_STRERROR_CASE(ENODEV		, "No such device.");
		TOS_STRERROR_CASE(ENOTDIR		, "Not a directory.");
		TOS_STRERROR_CASE(EISDIR		, "Is a directory.");
		TOS_STRERROR_CASE(EINVAL		, "Invalid argument.");
		TOS_STRERROR_CASE(ENFILE		, "File table overflow.");
		TOS_STRERROR_CASE(EMFILE		, "Too many open files.");
		TOS_STRERROR_CASE(ENOTTY		, "Not a typewriter.");
		TOS_STRERROR_CASE(ETXTBSY		, "Text file busy.");
		TOS_STRERROR_CASE(EFBIG		, "File too large.");
		TOS_STRERROR_CASE(ENOSPC		, "No space left on device.");
		TOS_STRERROR_CASE(ESPIPE		, "Illegal seek.");
		TOS_STRERROR_CASE(EROFS		, "Read-only file system.");
		TOS_STRERROR_CASE(EMLINK		, "Too many links.");
		TOS_STRERROR_CASE(EPIPE		, "Broken pipe.");
		TOS_STRERROR_CASE(EDOM		, "Math argument out of domain of func.");
		TOS_STRERROR_CASE(ERANGE		, "Math result not representable.");
		TOS_STRERROR_CASE(EDEADLK		, "Resource deadlock would occur.");
		TOS_STRERROR_CASE(ENAMETOOLONG	, "File name too long.");
		TOS_STRERROR_CASE(ENOLCK		, "No record locks available.");
		TOS_STRERROR_CASE(ENOSYS		, "Invalid system call number.");
		TOS_STRERROR_CASE(ENOTEMPTY	, "Directory not empty.");
		TOS_STRERROR_CASE(ELOOP		, "Too many symbolic links encountered.");
		TOS_STRERROR_CASE(ENOMSG		, "No message of desired type.");
		TOS_STRERROR_CASE(EIDRM		, "Identifier removed.");
		TOS_STRERROR_CASE(ECHRNG		, "Channel number out of range.");
		TOS_STRERROR_CASE(EL2NSYNC	, "Level 2 not synchronized.");
		TOS_STRERROR_CASE(EL3HLT		, "Level 3 halted.");
		TOS_STRERROR_CASE(EL3RST		, "Level 3 reset.");
		TOS_STRERROR_CASE(ELNRNG		, "Link number out of range.");
		TOS_STRERROR_CASE(EUNATCH		, "Protocol driver not attached.");
		TOS_STRERROR_CASE(ENOCSI		, "No CSI structure available.");
		TOS_STRERROR_CASE(EL2HLT		, "Level 2 halted.");
		TOS_STRERROR_CASE(EBADE		, "Invalid exchange.");
		TOS_STRERROR_CASE(EBADR		, "Invalid request descriptor.");
		TOS_STRERROR_CASE(EXFULL		, "Exchange full.");
		TOS_STRERROR_CASE(ENOANO		, "No anode.");
		TOS_STRERROR_CASE(EBADRQC		, "Invalid request code.");
		TOS_STRERROR_CASE(EBADSLT		, "Invalid slot.");
		TOS_STRERROR_CASE(EBFONT		, "Bad font file format.");
		TOS_STRERROR_CASE(ENOSTR		, "Device not a stream.");
		TOS_STRERROR_CASE(ENODATA		, "No data available.");
		TOS_STRERROR_CASE(ETIME		, "Timer expired.");
		TOS_STRERROR_CASE(ENOSR		, "Out of streams resources.");
		TOS_STRERROR_CASE(ENONET		, "Machine is not on the network.");
		TOS_STRERROR_CASE(ENOPKG		, "Package not installed.");
		TOS_STRERROR_CASE(EREMOTE		, "Object is remote.");
		TOS_STRERROR_CASE(ENOLINK		, "Link has been severed.");
		TOS_STRERROR_CASE(EADV		, "Advertise error.");
		TOS_STRERROR_CASE(ESRMNT		, "Srmount error.");
		TOS_STRERROR_CASE(ECOMM		, "Communication error on send.");
		TOS_STRERROR_CASE(EPROTO		, "Protocol error.");
		TOS_STRERROR_CASE(EMULTIHOP	, "Multihop attempted.");
		TOS_STRERROR_CASE(EDOTDOT		, "RFS specific error.");
		TOS_STRERROR_CASE(EBADMSG		, "Not a data message.");
		TOS_STRERROR_CASE(EOVERFLOW	, "Value too large for defined data type.");
		TOS_STRERROR_CASE(ENOTUNIQ	, "Name not unique on network.");
		TOS_STRERROR_CASE(EBADFD		, "File descriptor in bad state.");
		TOS_STRERROR_CASE(EREMCHG		, "Remote address changed.");
		TOS_STRERROR_CASE(ELIBACC		, "Can not access a needed shared library.");
		TOS_STRERROR_CASE(ELIBBAD		, "Accessing a corrupted shared library.");
		TOS_STRERROR_CASE(ELIBSCN		, ".lib section in a.out corrupted.");
		TOS_STRERROR_CASE(ELIBMAX		, "Attempting to link in too many shared libraries.");
		TOS_STRERROR_CASE(ELIBEXEC	, "Cannot exec a shared library directly.");
		TOS_STRERROR_CASE(EILSEQ		, "Illegal byte sequence.");
		TOS_STRERROR_CASE(ERESTART	, "Interrupted system call should be restarted.");
		TOS_STRERROR_CASE(ESTRPIPE	, "Streams pipe error.");
		TOS_STRERROR_CASE(EUSERS		, "Too many users.");
		TOS_STRERROR_CASE(ENOTSOCK	, "Socket operation on non-socket.");
		TOS_STRERROR_CASE(EDESTADDRREQ	, "Destination address required.");
		TOS_STRERROR_CASE(EMSGSIZE	, "Message too long.");
		TOS_STRERROR_CASE(EPROTOTYPE	, "Protocol wrong type for socket.");
		TOS_STRERROR_CASE(ENOPROTOOPT	, "Protocol not available.");
		TOS_STRERROR_CASE(EPROTONOSUPPORT	, "Protocol not supported.");
		TOS_STRERROR_CASE(ESOCKTNOSUPPORT	, "Socket type not supported.");
		TOS_STRERROR_CASE(EOPNOTSUPP	, "Operation not supported on transport endpoint.");
		TOS_STRERROR_CASE(EPFNOSUPPORT	, "Protocol family not supported.");
		TOS_STRERROR_CASE(EAFNOSUPPORT	, "Address family not supported by protocol.");
		TOS_STRERROR_CASE(EADDRINUSE	, "Address already in use.");
		TOS_STRERROR_CASE(EADDRNOTAVAIL	, "Cannot assign requested address.");
		TOS_STRERROR_CASE(ENETDOWN	, "Network is down.");
		TOS_STRERROR_CASE(ENETUNREACH	, "Network is unreachable.");
		TOS_STRERROR_CASE(ENETRESET	, "Network dropped connection because of reset.");
		TOS_STRERROR_CASE(ECONNABORTED	, "Software caused connection abort.");
		TOS_STRERROR_CASE(ECONNRESET	, "Connection reset by peer.");
		TOS_STRERROR_CASE(ENOBUFS		, "No buffer space available.");
		TOS_STRERROR_CASE(EISCONN		, "Transport endpoint is already connected.");
		TOS_STRERROR_CASE(ENOTCONN	, "Transport endpoint is not connected.");
		TOS_STRERROR_CASE(ESHUTDOWN	, "Cannot send after transport endpoint shutdown.");
		TOS_STRERROR_CASE(ETOOMANYREFS	, "Too many references: cannot splice.");
		TOS_STRERROR_CASE(ETIMEDOUT	, "Connection timed out.");
		TOS_STRERROR_CASE(ECONNREFUSED	, "Connection refused.");
		TOS_STRERROR_CASE(EHOSTDOWN	, "Host is down.");
		TOS_STRERROR_CASE(EHOSTUNREACH	, "No route to host.");
		TOS_STRERROR_CASE(EALREADY	, "Operation already in progress.");
		TOS_STRERROR_CASE(EINPROGRESS	, "Operation now in progress.");
		TOS_STRERROR_CASE(ESTALE		, "Stale file handle.");
		TOS_STRERROR_CASE(EUCLEAN		, "Structure needs cleaning.");
		TOS_STRERROR_CASE(ENOTNAM		, "Not a XENIX named type file.");
		TOS_STRERROR_CASE(ENAVAIL		, "No XENIX semaphores available.");
		TOS_STRERROR_CASE(EISNAM		, "Is a named type file.");
		TOS_STRERROR_CASE(EREMOTEIO	, "Remote I/O error.");
		TOS_STRERROR_CASE(EDQUOT		, "Quota exceeded.");
		TOS_STRERROR_CASE(ENOMEDIUM	, "No medium found.");
		TOS_STRERROR_CASE(EMEDIUMTYPE	, "Wrong medium type.");
		TOS_STRERROR_CASE(ECANCELED	, "Operation Canceled.");
		TOS_STRERROR_CASE(ENOKEY		, "Required key not available.");
		TOS_STRERROR_CASE(EKEYEXPIRED	, "Key has expired.");
		TOS_STRERROR_CASE(EKEYREVOKED	, "Key has been revoked.");
		TOS_STRERROR_CASE(EKEYREJECTED, "Key was rejected by service.");
	default:
		pRet = "Undefined error";
		break;
	}
	return (char*)pRet;
}
#undef TOS_STRERROR_CASE