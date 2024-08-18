
;    TPOSLC
;    A LibC implementation for TPOS (Testing and Prototyping Operating System).
;
;    Copyright © 2024 by Osher Sinai.
;
;    This file is part of TPOSLC (Testing and Prototyping Operating System LibC).
;
;    TPOSLC is free software:
;    you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
;    either version 3 of the License, or (at your option) any later version.
;
;    TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
;    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
;    See the GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License along with TPOSLC.
;    If not, see <https://www.gnu.org/licenses/>.

.data
extern g_time_HypervisorSharedPageInfo:qword
extern g_dwNtQuerySystemInformation:dword
extern g_dwNtAllocateVirtualMemory:dword
extern g_dwNtFreeVirtualMemory:dword
extern g_dwNtProtectVirtualMemory:dword
extern g_dwNtTerminateProcess:dword
extern g_dwNtQueryInformationProcess:dword
extern g_dwNtOpenFile:dword
extern g_dwNtClose:dword
extern g_dwNtCreateFile:dword
extern g_dwNtSetInformationFile:dword
extern g_dwNtQueryInformationFile:dword
extern g_dwNtWriteFile:dword
extern g_dwNtReadFile:dword
extern g_dwNtFlushBuffersFile:dword
extern g_dwNtQueryPerformanceCounter:dword
extern g_dwNtDelayExecution:dword
extern g_dwNtTerminateThread:dword
extern g_dwNtQueryInformationThread:dword
extern g_dwNtDuplicateObject:dword
extern g_dwNtCreateThreadEx:dword


.code
RtlQueryPerformanceCounter proc
		push rbx
		push r11
		push r10
		sub rsp,20

		mov r9, qword ptr[7FFE03C6h]
		test r9, 1
		jz RtlQueryPerformanceCounter_do_syscall_QPC
		mov r8, qword ptr[7FFE03B8h]
		mov rbx, rcx 
		test r9, 2
		jz RtlQueryPerformanceCounter_no_hypervisor

		mov r10, qword ptr [g_time_HypervisorSharedPageInfo]
	RtlQueryPerformanceCounter_loop:
		mov r11d, dword ptr[r10]
		test r9b, r9b
		jns RtlQueryPerformanceCounter_loop_ns
		rdtscp
	RtlQueryPerformanceCounter_loop_cnt :
		shl rdx, 20h
		or rdx, rax
		mov rax, qword ptr[r10 + 8h]
		mov rcx, qword ptr[r10 + 10h]
		mul rdx
		mov eax, dword ptr[r10]
		add rdx, rcx
		cmp eax, r11d
		jne RtlQueryPerformanceCounter_loop

	RtlQueryPerformanceCounter_loop_exit:
		mov cl, byte ptr [7FFE03C7h]
		add rdx, r8
		shr rdx, cl
		mov qword ptr[rbx], rdx
		jmp RtlQueryPerformanceCounter_end

	RtlQueryPerformanceCounter_loop_ns:
		rdtsc
		jmp RtlQueryPerformanceCounter_loop_cnt

	RtlQueryPerformanceCounter_no_hypervisor:

		mov r11d, dword ptr[r10]
		test r9b, r9b
		jns RtlQueryPerformanceCounter_nh_ns
		rdtscp
	RtlQueryPerformanceCounter_nh_cnt:
		shl rdx, 20h
		or rdx, rax
		jmp RtlQueryPerformanceCounter_loop_exit
	RtlQueryPerformanceCounter_nh_ns:
		rdtsc
		jmp RtlQueryPerformanceCounter_nh_cnt

	RtlQueryPerformanceCounter_do_syscall_QPC:
		call SyscallNtQueryPerformanceCounter
	RtlQueryPerformanceCounter_end:
	
		add rsp,20
		pop r11
		pop r10
		pop rbx
		xor eax, eax
		inc eax
		ret
RtlQueryPerformanceCounter endp

SyscallNtQuerySystemInformation proc
	mov r10, rcx
	;mov eax, 36h
	mov eax, dword ptr [g_dwNtQuerySystemInformation]
	syscall
	ret
SyscallNtQuerySystemInformation endp

SyscallNtAllocateVirtualMemory proc
	mov r10, rcx
	;mov eax, 18h
	mov eax, dword ptr [g_dwNtAllocateVirtualMemory]
	syscall
	ret
SyscallNtAllocateVirtualMemory endp

SyscallNtFreeVirtualMemory proc
	mov r10, rcx
	;mov eax, 1eh
	mov eax, dword ptr [g_dwNtFreeVirtualMemory]
	syscall
	ret
SyscallNtFreeVirtualMemory endp

SyscallNtProtectVirtualMemory proc
	mov r10, rcx
	;mov eax, 50h
	mov eax, dword ptr [g_dwNtProtectVirtualMemory]
	syscall
	ret
SyscallNtProtectVirtualMemory endp

SyscallNtTerminateProcess proc
	mov r10, rcx
	;mov eax, 2ch
	mov eax, dword ptr [g_dwNtTerminateProcess]
	syscall
	ret
SyscallNtTerminateProcess endp

SyscallNtQueryInformationProcess proc
	mov r10, rcx
	;mov eax, 19h
	mov eax, dword ptr [g_dwNtQueryInformationProcess]
	syscall
	ret
SyscallNtQueryInformationProcess endp

SyscallNtOpenFile proc
	mov r10, rcx
	;mov eax, 33h
	mov eax, dword ptr [g_dwNtOpenFile]
	syscall
	ret
SyscallNtOpenFile endp

SyscallNtClose proc
	mov r10, rcx
	;mov eax, 0fh
	mov eax, dword ptr [g_dwNtClose]
	syscall
	ret
SyscallNtClose endp

SyscallNtCreateFile proc
	mov r10, rcx
	;mov eax, 55h
	mov eax, dword ptr [g_dwNtCreateFile]
	syscall
	ret
SyscallNtCreateFile endp

SyscallNtSetInformationFile proc
	mov r10, rcx
	;mov eax, 27h
	mov eax, dword ptr [g_dwNtSetInformationFile]
	syscall
	ret
SyscallNtSetInformationFile endp

SyscallNtQueryInformationFile proc
	mov r10, rcx
	;mov eax, 11h
	mov eax, dword ptr [g_dwNtQueryInformationFile]
	syscall
	ret
SyscallNtQueryInformationFile endp

SyscallNtWriteFile proc
	mov r10, rcx
	;mov eax, 08h
	mov eax, dword ptr [g_dwNtWriteFile]
	syscall
	ret
SyscallNtWriteFile endp

SyscallNtReadFile proc
	mov r10, rcx
	;mov eax, 06h
	mov eax, dword ptr [g_dwNtReadFile]
	syscall
	ret
SyscallNtReadFile endp

SyscallNtFlushBuffersFile proc
	mov r10, rcx
	;mov eax, 04bh
	mov eax, dword ptr [g_dwNtFlushBuffersFile]
	syscall
	ret
SyscallNtFlushBuffersFile endp

SyscallNtQueryPerformanceCounter proc
	mov r10, rcx
	;mov eax, 31h
	mov eax, dword ptr [g_dwNtQueryPerformanceCounter]
	syscall
	ret
SyscallNtQueryPerformanceCounter endp

SyscallNtDelayExecution proc
	mov r10, rcx
	;mov eax, 34h
	mov eax, dword ptr [g_dwNtDelayExecution]
	syscall
	ret
SyscallNtDelayExecution endp

SyscallNtCreateThreadEx proc
	mov r10, rcx
	;mov eax, 0c2h
	mov eax, dword ptr [g_dwNtCreateThreadEx]
	syscall
	ret
SyscallNtCreateThreadEx endp

SyscallNtTerminateThread proc
	mov r10, rcx
	;mov eax, 53h
	mov eax, dword ptr [g_dwNtTerminateThread]
	syscall
	ret
SyscallNtTerminateThread endp

SyscallNtQueryInformationThread proc
	mov r10, rcx
	;mov eax, 25h
	mov eax, dword ptr [g_dwNtQueryInformationThread]
	syscall
	ret
SyscallNtQueryInformationThread endp

SyscallNtDuplicateObject proc
	mov r10, rcx
	;mov eax, 3ch
	mov eax, dword ptr [g_dwNtDuplicateObject]
	syscall
	ret
SyscallNtDuplicateObject endp

RtlCaptureContext proc
	pushfq
	mov qword ptr[rcx + 078h], rax
	mov qword ptr[rcx + 080h], rcx
	mov qword ptr[rcx + 088h], rdx
	mov qword ptr[rcx + 0b8h], r8
	mov qword ptr[rcx + 0c0h], r9
	mov qword ptr[rcx + 0c8h], r10
	mov qword ptr[rcx + 0d0h], r11
	fxsave [rcx+100h]

	mov word ptr[rcx + 038h], cs
	mov word ptr[rcx + 03ah],ds
	mov word ptr[rcx + 03ch],es
	mov word ptr[rcx + 042h],ss
	mov word ptr[rcx + 03eh],fs
	mov word ptr[rcx + 040h],gs


	mov qword ptr[rcx + 090h],rbx
	mov qword ptr[rcx + 0a0h],rbp
	mov qword ptr[rcx + 0a8h],rsi
	mov qword ptr[rcx + 0b0h],rdi
	mov qword ptr[rcx + 0d8h],r12
	mov qword ptr[rcx + 0e0h],r13
	mov qword ptr[rcx + 0e8h],r14
	mov qword ptr[rcx + 0f0h],r15

	stmxcsr dword ptr [rcx + 34h]
	lea rax, [rsp+10h]
	mov qword ptr[rcx + 98h], rax
	mov rax, qword ptr [rsp + 8h]
	mov qword ptr[rcx + 0f8h], rax
	mov eax, dword ptr [rsp]
	mov dword ptr [rcx+44h], eax
	mov dword ptr [rcx+30h], 10000fh
	add rsp, 8h
	ret
RtlCaptureContext endp

__chkstk proc
	sub rsp, 10h
	mov qword ptr [rsp], r10
	mov qword ptr [rsp + 8h], r11
	xor r11, r11
	lea r10, [rsp + 18h]
	sub r10, rax
	cmovb r10, r11
	mov r11, qword ptr gs:[10h]
	cmp r10, r11
	jae __chkstk_skip
	and r10w, 0F000h
__chkstk_loop:
	lea r11, [r11-1000h]
	mov byte ptr [r11], 0
	cmp r10, r11
	jne __chkstk_loop
__chkstk_skip:
	mov r10, qword ptr [rsp]
	mov r11, qword ptr [rsp+8]
	add rsp, 10h
	ret
__chkstk endp

GetCurrentThreadId proc
	mov rax, qword ptr gs:[30h]
	mov eax, dword ptr [rax+48h]
	ret
GetCurrentThreadId endp


end