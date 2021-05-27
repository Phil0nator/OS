#include "kernel/multiboot_loader.h"
#include "globals.h"

void loadMultiboot2_mmap( struct multiboot_tag* mmap_tag ){
    print_str("Loading Memory Map: ");
    size_t i = 0;
    for (
        multiboot_memory_map_t* mmap = ((struct multiboot_tag_mmap* ) mmap_tag)->entries;
        (multiboot_uint8_t*)mmap < (multiboot_uint8_t*) mmap_tag + mmap_tag->size;
        mmap = (multiboot_memory_map_t *) 
                   ((unsigned long) mmap
                    + ((struct multiboot_tag_mmap *) mmap_tag)->entry_size)
        )
    {

        globalMemoryList[i] = (PhysicalMemoryArea) { 
            chunk: (MemoryChunk) { 
                start: (char*) mmap->addr, 
                end: (char*) (mmap->addr + mmap->len)
                },
            type: mmap->type
            };    

        i++;
    }
    globalMemoryList_size = i;
    print_success_ok();

    

}



void loadMultiboot2Tags( void* addr, uint32_t magic ) {
    
    print_str("Checking Multiboot2 validity: ");
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        print_kernel_load_fail();
        haltCPU();
    }else {
        print_success_ok();
    }
    


    for (
        struct multiboot_tag* tag = (struct multiboot_tag*) (addr + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END; 
        tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag 
                                       + ((tag->size + 7) & ~7))
        )
        {
            switch ( tag->type )
            {
                case MULTIBOOT_TAG_TYPE_MMAP:
                    loadMultiboot2_mmap( tag );
                    break;
            }
        }

}