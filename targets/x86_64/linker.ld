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
    KERNEL_VMA = 0x00301000;
    . = KERNEL_VMA;

    .text : ALIGN(4K)
    {
        _KERNEL_START = ABSOLUTE(.);
        *(.start)
        *(.text)
        *(.rodata*)
    }

    .boot : ALIGN(4K)
    {
        KEEP(*(.multiboot_header))
    }

    .data : ALIGN(4K)
    {
        *(.data)
    }

    .bss : ALIGN(4K)
    {
        _BSS_START = ABSOLUTE(.);
        *(.bss)
        *(COMMON)
    }
    _BSS_SIZE = ABSOLUTE(.) - _BSS_START;
    _KERNEL_SIZE = ABSOLUTE(.) - _KERNEL_START;
}
