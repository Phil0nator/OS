; IDT.asm provides a C-accessible implimentation of the 'lidt' instruction

bits 64
section .text
global load_interdesctable
extern hardcodedIDTP ; hard coded interrupt descriptor table pointer
global start_system_interrupts

; load the IDTP into the cpu's internal register
load_interdesctable:
    lidt [hardcodedIDTP]
    ret

start_system_interrupts:
    sti
    ret