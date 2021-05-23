global start
extern long_mode_start
section .text
bits 32

%define MAGIC_BOOT 0x36d76289
%define CPUID_FLAG_BIT 21
%define CPUID_LONGMODE_BIT 29
%define PAGING_ENABLE_PAE_BIT 5
%define ENABLE_LONGMODE_BIT 8
%define ENABLE_PAGING_BIT 31

start:
    mov esp, stack_top
    
    call check_multiboot
    call check_cpuid
    call check_long_mode

    call setup_page_tables
    call enable_paging

    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start ; jump into 64 bit code

    

enable_paging:
    ; pass page table location to cpu
    mov eax, page_table_l4
    mov cr3, eax ; cpu uses cr3 as pointer to l4 page 
    ; enable PAE

    mov eax, cr4
    or eax, 1  << PAGING_ENABLE_PAE_BIT
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xC0000080 ; <- magic number
    rdmsr ; read model specific register
    ; places value into eax:
    ; Set the paging bit in the flags
    or eax, 1 << ENABLE_LONGMODE_BIT
    wrmsr ; write model specific register

    ; enable paging
    mov eax, cr0
    or eax, 1 << ENABLE_PAGING_BIT
    mov cr0, eax

    ret

setup_page_tables: ; the page tables have a number of bits for flags at the start
    mov eax, page_table_l3 
    or  eax, 0b11 ; present, writeable bits set
    mov [page_table_l4], eax ; make l4 point to l3
    
    mov eax, page_table_l2
    or eax, 0b11 ; present, writeable bits set
    mov [page_table_l3], eax ; make l3 point to l2

    ; now we need to fill in all the entries of l2
    mov ecx, 0 ; counter
    .loop:
    
    mov eax, 0x200000 ; 2 MiB
    mul ecx
    or eax, 0b10000011
    mov [page_table_l2 + ecx * 8], eax
    
    inc ecx
    cmp ecx, 512
    jne .loop

    ret

check_multiboot: ; check if multiboot is present
    cmp eax, MAGIC_BOOT ; magic number from bootloader
    jne .no_multiboot ; if no multiboot, show error
    ret ; otherwise, return as normal
.no_multiboot: ; if there is no multiboot,
    mov al, 'M' ; show error code M for multiboot
    jmp error ; goto error code 


check_long_mode: ; in order to check if there is longmode...
    ; first we need to check if the CPU supports extended cpuid info
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_longmode
    ; then we can check for the actual feature, longmode
    mov eax, 0x80000001
    cpuid
    test edx, 1 << CPUID_LONGMODE_BIT
    jz .no_longmode
    ret


.no_longmode
    mov al, 'L'
    jmp error


check_cpuid:
    ; in order to check if the cpu supports CPUID, try to flip bit #21 of the flag register
    ; this is mostly stack manipulation to move the flag register around and check if it was changed
    ; while preserving its original state
    pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 << CPUID_FLAG_BIT
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax, ecx
	je .no_cpuid
	ret
.no_cpuid:
    mov al, 'C'
    jmp error

error:
    mov dword[0xb8000], 0x4f524f45 ; "ERR: "
    mov dword[0xb8004], 0x4f3a4f52
    mov dword[0xb8008], 0x4f204f20
    mov byte[0xb800a], al
    hlt ; noreturn


section .bss
align 4096

page_table_l4:
    resb 4096
page_table_l3:
    resb 4096
page_table_l2:
    resb 4096

stack_bottom:
    resb 4096*4
stack_top:

section .rodata
gdt64:
	dq 0 ; zero entry
.code_segment: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; code segment
.pointer:
	dw $ - gdt64 - 1 ; length
	dq gdt64 ; address