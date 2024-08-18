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
#ifndef TOS_WIN32_NTDLL_H
#define TOS_WIN32_NTDLL_H
#include "win32_base.h"
#include <include\wchar.h>
#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)
#define STATUS_INVALID_HANDLE            ((NTSTATUS)0xC0000008L)
#define STATUS_NO_MEMORY                 ((NTSTATUS)0xC0000017L)
#define STATUS_CONFLICTING_ADDRESSES     ((NTSTATUS)0xC0000018L)
#define STATUS_ALREADY_COMMITTED         ((NTSTATUS)0xC0000021L)
#define STATUS_ACCESS_DENIED             ((NTSTATUS)0xC0000022L)
#define STATUS_OBJECT_TYPE_MISMATCH      ((NTSTATUS)0xC0000024L)
#define STATUS_INVALID_PAGE_PROTECTION   ((NTSTATUS)0xC0000045L)
#define STATUS_INSUFFICIENT_RESOURCES    ((NTSTATUS)0xC000009AL)
#define STATUS_PROCESS_IS_TERMINATING    ((NTSTATUS)0xC000010AL)
#define STATUS_COMMITMENT_LIMIT          ((NTSTATUS)0xC000012DL)
#define STATUS_HANDLE_NOT_CLOSABLE       ((NTSTATUS)0xC0000235L)
#define STATUS_INVALID_PARAMETER         ((NTSTATUS)0xC000000DL)
#define STATUS_OBJECT_PATH_SYNTAX_BAD    ((NTSTATUS)0xC000003BL)
#define STATUS_OBJECT_NAME_INVALID       ((NTSTATUS)0xC0000033L)
#define STATUS_END_OF_FILE               ((NTSTATUS)0xC0000011L)
#define STATUS_NAME_TOO_LONG			 ((NTSTATUS)0xC0000106L)
#define STATUS_NO_YIELD_PERFORMED        ((NTSTATUS)0x40000024L)
#define STATUS_ALERTED                   ((NTSTATUS)0x00000101L)
#define STATUS_USER_APC                  ((NTSTATUS)0x000000C0L)
#define STATUS_CANT_TERMINATE_SELF       ((NTSTATUS)0xC00000DBL)
#define STATUS_PRIVILEGE_NOT_HELD		 ((NTSTATUS)0xC0000061L)

#define SYNCHRONIZE                      (0x00100000L)
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define THREAD_ALL_ACCESS         (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)
#define GENERIC_ALL                      (0x10000000L)
#define DUPLICATE_CLOSE_SOURCE      0x00000001  
#define DUPLICATE_SAME_ACCESS       0x00000002  
#define DUPLICATE_SAME_ATTRIBUTES   0x00000004
//Support is from win10 onwards.
//win7, win8 and win8.1 are somewhat different and as such won't be supported 

struct alignas(16) CONTEXT {

	//
	// Register parameter home addresses.
	//
	// N.B. These fields are for convience - they could be used to extend the
	//      context record in the future.
	//

	ULONG64 P1Home;
	ULONG64 P2Home;
	ULONG64 P3Home;
	ULONG64 P4Home;
	ULONG64 P5Home;
	ULONG64 P6Home;

	//
	// Control flags.
	//

	ULONG ContextFlags;
	ULONG MxCsr;

	//
	// Segment Registers and processor flags.
	//

	USHORT SegCs;
	USHORT SegDs;
	USHORT SegEs;
	USHORT SegFs;
	USHORT SegGs;
	USHORT SegSs;
	ULONG EFlags;

	//
	// Debug registers
	//

	ULONG64 Dr0;
	ULONG64 Dr1;
	ULONG64 Dr2;
	ULONG64 Dr3;
	ULONG64 Dr6;
	ULONG64 Dr7;

	//
	// Integer registers.
	//

	ULONG64 Rax;
	ULONG64 Rcx;
	ULONG64 Rdx;
	ULONG64 Rbx;
	ULONG64 Rsp;
	ULONG64 Rbp;
	ULONG64 Rsi;
	ULONG64 Rdi;
	ULONG64 R8;
	ULONG64 R9;
	ULONG64 R10;
	ULONG64 R11;
	ULONG64 R12;
	ULONG64 R13;
	ULONG64 R14;
	ULONG64 R15;

	//
	// Program counter.
	//

	ULONG64 Rip;

	//
	// Floating point state.
	//

	union {
		XMM_SAVE_AREA32 FltSave;
		struct {
			M128A Header[2];
			M128A Legacy[8];
			M128A Xmm0;
			M128A Xmm1;
			M128A Xmm2;
			M128A Xmm3;
			M128A Xmm4;
			M128A Xmm5;
			M128A Xmm6;
			M128A Xmm7;
			M128A Xmm8;
			M128A Xmm9;
			M128A Xmm10;
			M128A Xmm11;
			M128A Xmm12;
			M128A Xmm13;
			M128A Xmm14;
			M128A Xmm15;
		} DUMMYSTRUCTNAME;
	} DUMMYUNIONNAME;

	//
	// Vector registers.
	//

	M128A VectorRegister[26];
	ULONG64 VectorControl;

	//
	// Special debug control registers.
	//

	ULONG64 DebugControl;
	ULONG64 LastBranchToRip;
	ULONG64 LastBranchFromRip;
	ULONG64 LastExceptionToRip;
	ULONG64 LastExceptionFromRip;
};

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

struct OBJECT_ATTRIBUTES {
	ULONG           Length;
	void* RootDirectory;
	UNICODE_STRING* ObjectName;
	ULONG           Attributes;
	PVOID           SecurityDescriptor;
	PVOID           SecurityQualityOfService;
};

struct IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID    Pointer;
	};
	ULONG_PTR Information;
};

struct CURDIR {
	UNICODE_STRING DosPath;
	HANDLE Handle;
};

struct RTL_USER_PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	HANDLE ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StandardInput;
	HANDLE StandardOutput;
	HANDLE StandardError;
	CURDIR CurrentDirectory;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PVOID Environment;
	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopInfo;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
};

struct FILE_STANDARD_INFORMATION {
	uint64_t AllocationSize;
	uint64_t EndOfFile;
	ULONG         NumberOfLinks;
	BOOLEAN       DeletePending;
	BOOLEAN       Directory;
} ;

struct RTL_BITMAP {
	ULONG SizeOfBitmap;
	PULONG Buffer;
};

enum class FILE_INFORMATION_CLASS {
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation = 2,
	FileBothDirectoryInformation = 3,
	FileBasicInformation = 4,
	FileStandardInformation = 5,
	FileInternalInformation = 6,
	FileEaInformation = 7,
	FileAccessInformation = 8,
	FileNameInformation = 9,
	FileRenameInformation = 10,
	FileLinkInformation = 11,
	FileNamesInformation = 12,
	FileDispositionInformation = 13,
	FilePositionInformation = 14,
	FileFullEaInformation = 15,
	FileModeInformation = 16,
	FileAlignmentInformation = 17,
	FileAllInformation = 18,
	FileAllocationInformation = 19,
	FileEndOfFileInformation = 20,
	FileAlternateNameInformation = 21,
	FileStreamInformation = 22,
	FilePipeInformation = 23,
	FilePipeLocalInformation = 24,
	FilePipeRemoteInformation = 25,
	FileMailslotQueryInformation = 26,
	FileMailslotSetInformation = 27,
	FileCompressionInformation = 28,
	FileObjectIdInformation = 29,
	FileCompletionInformation = 30,
	FileMoveClusterInformation = 31,
	FileQuotaInformation = 32,
	FileReparsePointInformation = 33,
	FileNetworkOpenInformation = 34,
	FileAttributeTagInformation = 35,
	FileTrackingInformation = 36,
	FileIdBothDirectoryInformation = 37,
	FileIdFullDirectoryInformation = 38,
	FileValidDataLengthInformation = 39,
	FileShortNameInformation = 40,
	FileIoCompletionNotificationInformation = 41,
	FileIoStatusBlockRangeInformation = 42,
	FileIoPriorityHintInformation = 43,
	FileSfioReserveInformation = 44,
	FileSfioVolumeInformation = 45,
	FileHardLinkInformation = 46,
	FileProcessIdsUsingFileInformation = 47,
	FileNormalizedNameInformation = 48,
	FileNetworkPhysicalNameInformation = 49,
	FileIdGlobalTxDirectoryInformation = 50,
	FileIsRemoteDeviceInformation = 51,
	FileUnusedInformation = 52,
	FileNumaNodeInformation = 53,
	FileStandardLinkInformation = 54,
	FileRemoteProtocolInformation = 55,
	FileRenameInformationBypassAccessCheck = 56,
	FileLinkInformationBypassAccessCheck = 57,
	FileVolumeNameInformation = 58,
	FileIdInformation = 59,
	FileIdExtdDirectoryInformation = 60,
	FileReplaceCompletionInformation = 61,
	FileHardLinkFullIdInformation = 62,
	FileIdExtdBothDirectoryInformation = 63,
	FileDispositionInformationEx = 64,
	FileRenameInformationEx = 65,
	FileRenameInformationExBypassAccessCheck = 66,
	FileDesiredStorageClassInformation = 67,
	FileStatInformation = 68,
	FileMemoryPartitionInformation = 69,
	FileStatLxInformation = 70,
	FileCaseSensitiveInformation = 71,
	FileLinkInformationEx = 72,
	FileLinkInformationExBypassAccessCheck = 73,
	FileStorageReserveIdInformation = 74,
	FileCaseSensitiveInformationForceAccessCheck = 75,
	FileKnownFolderInformation = 76,
	FileStatBasicInformation = 77,
	FileId64ExtdDirectoryInformation = 78,
	FileId64ExtdBothDirectoryInformation = 79,
	FileIdAllExtdDirectoryInformation = 80,
	FileIdAllExtdBothDirectoryInformation = 81,
	FileStreamReservationInformation,
	FileMupProviderInfo,
	FileMaximumInformation
} ;
typedef enum _PROCESSINFOCLASS {
	ProcessBasicInformation = 0,
	ProcessQuotaLimits = 1,
	ProcessIoCounters = 2,
	ProcessVmCounters = 3,
	ProcessTimes = 4,
	ProcessBasePriority = 5,
	ProcessRaisePriority = 6,
	ProcessDebugPort = 7,
	ProcessExceptionPort = 8,
	ProcessAccessToken = 9,
	ProcessLdtInformation = 10,
	ProcessLdtSize = 11,
	ProcessDefaultHardErrorMode = 12,
	ProcessIoPortHandlers = 13,   // Note: this is kernel mode only
	ProcessPooledUsageAndLimits = 14,
	ProcessWorkingSetWatch = 15,
	ProcessUserModeIOPL = 16,
	ProcessEnableAlignmentFaultFixup = 17,
	ProcessPriorityClass = 18,
	ProcessWx86Information = 19,
	ProcessHandleCount = 20,
	ProcessAffinityMask = 21,
	ProcessPriorityBoost = 22,
	ProcessDeviceMap = 23,
	ProcessSessionInformation = 24,
	ProcessForegroundInformation = 25,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
	ProcessLUIDDeviceMapsEnabled = 28,
	ProcessBreakOnTermination = 29,
	ProcessDebugObjectHandle = 30,
	ProcessDebugFlags = 31,
	ProcessHandleTracing = 32,
	ProcessIoPriority = 33,
	ProcessExecuteFlags = 34,
	ProcessTlsInformation = 35,
	ProcessCookie = 36,
	ProcessImageInformation = 37,
	ProcessCycleTime = 38,
	ProcessPagePriority = 39,
	ProcessInstrumentationCallback = 40,
	ProcessThreadStackAllocation = 41,
	ProcessWorkingSetWatchEx = 42,
	ProcessImageFileNameWin32 = 43,
	ProcessImageFileMapping = 44,
	ProcessAffinityUpdateMode = 45,
	ProcessMemoryAllocationMode = 46,
	ProcessGroupInformation = 47,
	ProcessTokenVirtualizationEnabled = 48,
	ProcessOwnerInformation = 49,
	ProcessWindowInformation = 50,
	ProcessHandleInformation = 51,
	ProcessMitigationPolicy = 52,
	ProcessDynamicFunctionTableInformation = 53,
	ProcessHandleCheckingMode = 54,
	ProcessKeepAliveCount = 55,
	ProcessRevokeFileHandles = 56,
	ProcessWorkingSetControl = 57,
	ProcessHandleTable = 58,
	ProcessCheckStackExtentsMode = 59,
	ProcessCommandLineInformation = 60,
	ProcessProtectionInformation = 61,
	ProcessMemoryExhaustion = 62,
	ProcessFaultInformation = 63,
	ProcessTelemetryIdInformation = 64,
	ProcessCommitReleaseInformation = 65,
	ProcessReserved1Information = 66,
	ProcessReserved2Information = 67,
	ProcessSubsystemProcess = 68,
	ProcessInPrivate = 70,
	ProcessRaiseUMExceptionOnInvalidHandleClose = 71,
	ProcessSubsystemInformation = 75,
	ProcessWin32kSyscallFilterInformation = 79,
	ProcessEnergyTrackingState = 82,
	MaxProcessInfoClass                             // MaxProcessInfoClass should always be the last enum
} PROCESSINFOCLASS;

typedef enum _THREADINFOCLASS
{
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	ThreadSwitchLegacyState,
	ThreadIsTerminated,
	ThreadLastSystemCall,
	ThreadIoPriority,
	ThreadCycleTime,
	ThreadPagePriority,
	ThreadActualBasePriority,
	ThreadTebInformation,
	ThreadCSwitchMon,
	ThreadCSwitchPmu,
	ThreadWow64Context,
	ThreadGroupInformation,
	ThreadUmsInformation,
	ThreadCounterProfiling,
	ThreadIdealProcessorEx,
	ThreadCpuAccountingInformation,
	ThreadSuspendCount,
	ThreadHeterogeneousCpuPolicy,
	ThreadContainerId,
	ThreadNameInformation,
	ThreadSelectedCpuSets,
	ThreadSystemThreadInformation,
	ThreadActualGroupAffinity,
	ThreadDynamicCodePolicyInfo,
	ThreadExplicitCaseSensitivity,
	ThreadWorkOnBehalfTicket,
	ThreadSubsystemInformation,
	ThreadDbgkWerReportActive,
	ThreadAttachContainer,
	ThreadManageWritesToExecutableMemory,
	ThreadPowerThrottlingState,
	ThreadWorkloadClass,
	ThreadCreateStateChange,
	ThreadApplyStateChange,
	ThreadStrongerBadHandleChecks,
	ThreadEffectiveIoPriority,
	ThreadEffectivePagePriority,
	ThreadUpdateLockOwnership,
	ThreadSchedulerSharedDataSlot,
	ThreadTebInformationAtomic,
	ThreadIndexInformation,
	MaxThreadInfoClass
} THREADINFOCLASS;

typedef struct _WIN32_TIME_FIELDS {
	short Year; // 1600<
	short Month; // 1-12
	short Day; // 1-31
	short Hour; // 0-23
	short Minute; // 0-59
	short Second; // 0-59
	short Milliseconds; // 0-999
	short Weekday; // 0-6 = Sunday-Saturday
}WIN32_TIME_FIELDS;
// described in TIME_ZONE_INFORMATION as for some reason these structs are identical yet are not treated as such
typedef struct _RTL_TIMEZONE_INFO {
	//Offset to UTC from local time
	LONG Bias;
	WCHAR StandardName[32];
	WIN32_TIME_FIELDS StandardStart;
	LONG StandardBias;
	WCHAR DaylightName[32];
	WIN32_TIME_FIELDS DaylightStart;
	LONG DaylightBias;
}RTL_TIMEZONE_INFO;


typedef struct _PROCESS_BASIC_INFORMATION {
	NTSTATUS ExitStatus;
	void* PebBaseAddress;
	ULONG_PTR AffinityMask;
	uint32_t BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

union FILETIME {
	struct
	{
		uint32_t dwLowDateTime;
		uint32_t dwHighDateTime;
	};
	uint64_t QWord;
};
union LARGE_INTEGER {
	struct
	{
		uint32_t dwLow;
		uint32_t dwHigh;
	};
	uint64_t QWord;
};

typedef int(NTAPI* Win32UserThreadStartRoutine)(
	void* ThreadParameter
	);

struct PS_ATTRIBUTE
{
	ULONG_PTR Attribute;
	uint64_t Size;
	union
	{
		ULONG_PTR Value;
		PVOID ValuePtr;
	};
	uint64_t* ReturnLength;
};

struct PS_ATTRIBUTE_LIST
{
	uint64_t TotalLength;
	PS_ATTRIBUTE Attributes[1];
};

NTSTATUS RtlInitUnicodeStringEx(UNICODE_STRING* pDest, wchar_t* pSrc);
NTSTATUS RtlDosPathNameToNtPathName_U_WithStatus(
	wchar_t* DosFileName,
	PUNICODE_STRING NtFileName,
	PWSTR* FilePart,
	PVOID Reserved
);


extern "C" NTSTATUS SyscallNtAllocateVirtualMemory(
	uint64_t    ProcessHandle,
	void** BaseAddress,
	uint64_t ZeroBits,
	size_t * RegionSize,
	uint32_t     AllocationType,
	uint32_t     Protect);
extern "C" NTSTATUS SyscallNtFreeVirtualMemory(uint64_t ProcessHandle, void** ppAddr, uint64_t * pSize, uint32_t dwFreeType);
extern "C" NTSTATUS SyscallNtProtectVirtualMemory(uint64_t ProcessHandle, void** ppAddr, uint64_t * pSize, uint32_t NewProtect, uint32_t * pOldProtect);

extern "C" NTSTATUS SyscallNtOpenFile(
	HANDLE * FileHandle,
	uint64_t        DesiredAccess,
	OBJECT_ATTRIBUTES * ObjectAttributes,
	IO_STATUS_BLOCK * IoStatusBlock,
	uint64_t ShareAccess,
	uint64_t OpenOptions
);

extern "C" NTSTATUS SyscallNtClose(
	HANDLE FileHandle
);

extern "C" NTSTATUS SyscallNtCreateFile(
	HANDLE * pHandle,
	uint64_t DesiredAccess,
	OBJECT_ATTRIBUTES * ObjectAttributes,
	IO_STATUS_BLOCK * IoStatusBlock,
	uint64_t * AllocationSize,
	uint64_t FileAttributes,
	uint64_t ShareAccess,
	uint64_t CreateDisposition,
	uint64_t CreateOptions,
	PVOID EaBuffer,
	ULONG EaLength
);


extern "C" NTSTATUS SyscallNtSetInformationFile(
	HANDLE                 FileHandle,
	IO_STATUS_BLOCK*       IoStatusBlock,
	PVOID                  FileInformation,
	ULONG                  Length,
	FILE_INFORMATION_CLASS FileInformationClass
);
extern "C" NTSTATUS SyscallNtQueryInformationFile(
	HANDLE                 FileHandle,
	IO_STATUS_BLOCK*       IoStatusBlock,
	PVOID                  FileInformation,
	ULONG                  Length,
	FILE_INFORMATION_CLASS FileInformationClass
);

extern "C" NTSTATUS SyscallNtWriteFile(
	HANDLE           FileHandle,
	HANDLE           Event,
	void* ApcRoutine,
	PVOID            ApcContext,
	IO_STATUS_BLOCK * IoStatusBlock,
	const void*            Buffer,
	ULONG            Length,
	uint64_t * ByteOffset,
	ULONG * Key
);
extern "C" NTSTATUS SyscallNtReadFile(
	HANDLE           FileHandle,
	HANDLE           Event,
	void* ApcRoutine,
	PVOID            ApcContext,
	IO_STATUS_BLOCK * IoStatusBlock,
	PVOID            Buffer,
	ULONG            Length,
	uint64_t * ByteOffset,
	ULONG * Key
);

extern "C" NTSTATUS SyscallNtFlushBuffersFile(
	HANDLE hFile,
	IO_STATUS_BLOCK * IoStatusBlock
);

extern "C" NTSTATUS SyscallNtQueryInformationProcess
(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass,
	void* ProcessInformation, ULONG ProcessInformationLength, ULONG * ReturnLength);

extern "C" _Noreturn NTSTATUS SyscallNtTerminateProcess(uint64_t Handle, NTSTATUS Status);

extern "C" NTSTATUS SyscallNtQueryPerformanceCounter(LARGE_INTEGER * pCtr);
extern "C" BOOL RtlQueryPerformanceCounter(LARGE_INTEGER * pCtr);
extern "C" void RtlCaptureContext(CONTEXT * pContext);

extern "C" HANDLE GetCurrentProcess();
extern "C" uint64_t GetCurrentProcessId(HANDLE hProcess);
/*
FILETIME is the time in 100ns from 1 jan 1601
*/
extern "C" void GetSystemTimeAsFileTime(FILETIME * pTime);
extern "C" uint32_t GetTickCount();
extern "C" bool RtlQueryPerformanceFrequency(LARGE_INTEGER * pFrequency);
extern "C" NTSTATUS SyscallNtQuerySystemInformation(
	uint64_t InfoClass,
	void* pSystemInfo,
	uint32_t SystemInfoLength,
	uint32_t * pRetLen
);
extern "C" uint64_t GetCurrentThreadId();
extern "C" uint64_t SyscallNtDelayExecution(BOOLEAN Alertable, const LARGE_INTEGER * pDelayInterval);
extern "C" NTSTATUS SyscallNtCreateThreadEx(
	HANDLE * ThreadHandle,
	uint64_t DesiredAccess,
	OBJECT_ATTRIBUTES * ObjectAttributes,
	HANDLE ProcessHandle,
	Win32UserThreadStartRoutine StartRoutine,
	PVOID Argument,
	ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
	uint64_t ZeroBits,
	uint64_t StackSize,
	uint64_t MaximumStackSize,
	PS_ATTRIBUTE_LIST * AttributeList //optional
);

extern "C" NTSTATUS SyscallNtTerminateThread(HANDLE hThread, NTSTATUS ExitCode);

extern "C" NTSTATUS SyscallNtQueryInformationThread(
	HANDLE ThreadHandle,
	THREADINFOCLASS ThreadInformationClass,
	void* ThreadInformation,
	uint32_t ThreadInformationLength,
	uint32_t * ReturnLength
);

extern "C" uint64_t GetThreadId(HANDLE hThread);
extern "C" NTSTATUS SyscallNtDuplicateObject(
	HANDLE      SourceProcessHandle,
	HANDLE      SourceHandle,
	HANDLE      TargetProcessHandle,
	HANDLE*     TargetHandle,
	uint64_t     DesiredAccess,
	ULONG       HandleAttributes,
	ULONG       Options
);


/*
extern "C" NTSTATUS RtlGetCurrentUmsThread(void* pThread);
extern "C" NTSTATUS SyscallNtYieldExecution();
*/

BOOL DuplicateHandle(
	HANDLE   hSourceProcessHandle,
	HANDLE   hSourceHandle,
	HANDLE   hTargetProcessHandle,
	HANDLE*  lpTargetHandle,
	DWORD    dwDesiredAccess,
	BOOL     bInheritHandle,
	DWORD    dwOptions
);

uint64_t* GetThreadLocalStoragePointer();



typedef struct _CLIENT_ID {
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
}CLIENT_ID;
//BOOL SwitchToThread();
#endif // !TOS_WIN32_NTDLL_H
