section .text
bits 64
; extern char inb(IOPort p);
; extern void outb(IOPort p, char o);
; extern short inw(IOPort p);
; extern void outw(IOPort p, short o);

global inb, outb, inw, outw, haltCPU, __cpuid, _cpu_getcr2

inb: ; ( word p )
    mov dx, di
    in al, dx
    ret

outb: ; (word p, char o)
    mov dx, di
    mov al, sil
    out dx, al
    ret

inw: ; (word p)
    mov dx, di
    in ax, dx
    ret

outw: ; (word p, word o )
    mov dx, di
    mov ax, si
    out dx, ax
    ret

haltCPU:
    hlt


__cpuid:
    push rbx
    push rcx
    push rdx

    mov rax, rdi
    cpuid
    mov [rsi], rbx
    mov [rsi+8], rcx
    mov [rsi+16], rdx

    pop rdx
    pop rcx
    pop rbx
    ret

_cpu_getcr2:
    mov rax, cr2
    ret