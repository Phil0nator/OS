section .multiboot_header
header_start:
    ; magic number
    dd 0xe85250d6
    ; --architecture
    dd 0
    ; header length
    dd header_end - header_start
    ; checksum
    dd 0x100000000 -  (0xe85250d6 + 0 + (header_end - header_start ) )
    
    mmap_infotag_start:
    ; request info tag:
    dd 6 ; type : info request
    dd mmap_infotag_end-mmap_infotag_start ;size
    dd 24 ; size of one entry
    dd 0  ; entry version (constant 0)
    
    resb 24 * 256 ; entries
    mmap_infotag_end:

    ; end tag:
    dw 0 ; type
    dw 0 ; flags
    dd 8 ; size
header_end:


