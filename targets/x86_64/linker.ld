/* ENTRY(start)

SECTIONS 
{
    KERNEL_VMA = 0x00301000l
    . = 1M;
    .boot : 
    {
        KEEP(*(.multiboot_header))
    }

    .text : 
    {
        *(.text)
    }
}
 */


ENTRY(start)

SECTIONS 
{
    KERNEL_VMA = 0x00100000;
    . = KERNEL_VMA;

    .boot : ALIGN(4K)
    {
        KEEP(*(.multiboot_header))
    }

    /* .+=0xC0000000; */

    .text ALIGN(4K) : AT(ADDR(.text)/*-0xC0000000*/)
    {
        _KERNEL_START = ABSOLUTE(.);
        *(.start)
        *(.text)
        *(.rodata*)
    }
    

    

    .data ALIGN(4K) : AT(ADDR(.data)/*-0xC0000000*/)
    {
        *(.data)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss)/*-0xC0000000*/)
    {
        _BSS_START = ABSOLUTE(.);
        *(.bss)
        *(COMMON)
    }
    _BSS_SIZE = ABSOLUTE(.) - _BSS_START;
    _KERNEL_SIZE = ABSOLUTE(.) - _KERNEL_START;
}
