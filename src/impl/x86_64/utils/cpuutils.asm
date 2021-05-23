section .text
bits 64
; extern char inb(IOPort p);
; extern void outb(IOPort p, char o);
; extern short inw(IOPort p);
; extern void outw(IOPort p, short o);

global inb, outb, inw, outw, haltCPU

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