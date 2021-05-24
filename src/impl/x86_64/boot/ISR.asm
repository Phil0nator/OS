; ISR.asm is used to register all of the ISR's for the kernel. See IDT.c

%include "src/impl/x86_64/boot/pushaqs.asm"
bits 64
section .text
global syscall_base_handle
extern fault_handler


; define interrupt exception handlers
%macro ISR_SINGLE_HANDLE 1
    cli
    PUSHAQS
    mov rdi, %1
    jmp isr_common_handle

%endmacro

%macro ISR_NOPUSH_HANDLE 1
    cli
    PUSHAQS
    mov rdi, %1
    jmp isr_common_handle
%endmacro

; error codes 0 through 31
isr_code0:
    ISR_SINGLE_HANDLE 0
isr_code1:
    ISR_SINGLE_HANDLE 1
isr_code2:
    ISR_SINGLE_HANDLE 2
isr_code3:
    ISR_SINGLE_HANDLE 3
isr_code4:
    ISR_SINGLE_HANDLE 4
isr_code5:
    ISR_SINGLE_HANDLE 5
isr_code6:
    ISR_SINGLE_HANDLE 6
isr_code7:
    ISR_SINGLE_HANDLE 7

isr_code8:
    ISR_NOPUSH_HANDLE 8

isr_code9:
    ISR_SINGLE_HANDLE 9

isr_code10:
    ISR_NOPUSH_HANDLE 10
isr_code11:
    ISR_NOPUSH_HANDLE 11
isr_code12:
    ISR_NOPUSH_HANDLE 12
isr_code13:
    ISR_NOPUSH_HANDLE 13
isr_code14:
    ISR_NOPUSH_HANDLE 14



isr_code15:
    ISR_SINGLE_HANDLE 15
isr_code16:
    ISR_SINGLE_HANDLE 16
isr_code17:
    ISR_SINGLE_HANDLE 17
isr_code18:
    ISR_SINGLE_HANDLE 18

; reserved
isr_code19:
    ISR_SINGLE_HANDLE 19
isr_code20:
    ISR_SINGLE_HANDLE 20
isr_code21:
    ISR_SINGLE_HANDLE 21
isr_code22:
    ISR_SINGLE_HANDLE 22
isr_code23:
    ISR_SINGLE_HANDLE 23
isr_code24:
    ISR_SINGLE_HANDLE 24
isr_code25:
    ISR_SINGLE_HANDLE 25
isr_code26:
    ISR_SINGLE_HANDLE 26
isr_code27:
    ISR_SINGLE_HANDLE 27
isr_code28:
    ISR_SINGLE_HANDLE 28
isr_code29:
    ISR_SINGLE_HANDLE 29
isr_code30:
    ISR_SINGLE_HANDLE 30
isr_code31:
    ISR_SINGLE_HANDLE 31

; common code for any error
isr_common_handle:
    push gs
    push fs
    ;call fault_handler
    push rax
    mov rax, fault_handler
    call rax       ; A special call, preserves the 'eip' register
    pop rax
    pop fs
    pop gs
    POPAQS
    iretq       ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!


global  isr_code0;
global  isr_code1;
global  isr_code2;
global  isr_code3;
global  isr_code4;
global  isr_code5;
global  isr_code6;
global  isr_code7;
global  isr_code8;
global  isr_code9;
global  isr_code10;
global  isr_code11;
global  isr_code12;
global  isr_code13;
global  isr_code14;
global  isr_code15;
global  isr_code16;
global  isr_code17;
global  isr_code18;
global  isr_code19;
global  isr_code20;
global  isr_code21;
global  isr_code22;
global  isr_code23;
global  isr_code24;
global  isr_code25;
global  isr_code26;
global  isr_code27;
global  isr_code28;
global  isr_code29;
global  isr_code30;
global  isr_code31;