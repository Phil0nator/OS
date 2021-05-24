; irq.asm is used to register all of the irq's for the kernel. See IDT.c

%include "src/impl/x86_64/boot/pushaqs.asm"
bits 64
section .text
extern irq_handler


; define interrupt exception handlers
%macro IRQ_SINGLE_HANDLE 1
    cli
    PUSHAQS
    mov rdi, %1
    jmp irq_common_handle

%endmacro

%macro IRQ_NOPUSH_HANDLE 1
    cli
    PUSHAQS
    mov rdi, %1
    jmp irq_common_handle
%endmacro

; irq codes 31 through 47
irq_code0:
    IRQ_SINGLE_HANDLE 32
irq_code1:
    IRQ_SINGLE_HANDLE 33
irq_code2:
    IRQ_SINGLE_HANDLE 34
irq_code3:
    IRQ_SINGLE_HANDLE 35
irq_code4:
    IRQ_SINGLE_HANDLE 36
irq_code5:
    IRQ_SINGLE_HANDLE 37
irq_code6:
    IRQ_SINGLE_HANDLE 38
irq_code7:
    IRQ_SINGLE_HANDLE 39
irq_code8:
    IRQ_SINGLE_HANDLE 40
irq_code9:
    IRQ_SINGLE_HANDLE 41
irq_code10:
    IRQ_SINGLE_HANDLE 42
irq_code11:
    IRQ_SINGLE_HANDLE 43
irq_code12:
    IRQ_SINGLE_HANDLE 44
irq_code13:
    IRQ_SINGLE_HANDLE 45
irq_code14:
    IRQ_SINGLE_HANDLE 46
irq_code15:
    IRQ_SINGLE_HANDLE 47



; common code for any error
irq_common_handle:
    ;push gs
    ;push fs
    ;call fault_handler
    push rax
    mov rax, irq_handler
    call rax       ; A special call, preserves the 'eip' register
    pop rax
    ;pop fs
    ;pop gs
    POPAQS
    iretq       ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
    

global  irq_code0;
global  irq_code1;
global  irq_code2;
global  irq_code3;
global  irq_code4;
global  irq_code5;
global  irq_code6;
global  irq_code7;
global  irq_code8;
global  irq_code9;
global  irq_code10;
global  irq_code11;
global  irq_code12;
global  irq_code13;
global  irq_code14;
global  irq_code15;
global  irq_code16;
