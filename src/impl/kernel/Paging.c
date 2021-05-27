#include "kernel/Paging.h"
#include "print.h"
#include "utils/cpuutils.h"

#define ONLY_BITS(number, bits) (number & ((1<<bits)-1))

size_t page_table_l4_counter = 1;


void setupPageTablel4Recursive( PageTable_t* l4 ) {
    // Recursive Table
    l4->entries[PAGE_ENTRIES_PER_TABLE-1] = (PagingEntryBitField_t) 
    {
        present: 1,
        writeable: 1,
        physicalAddress: (uint64_t) &l4->entries
    };
}
void setupGenericPageTable( PageTable_t* p ){
    for (int i = 0 ; i < PAGE_ENTRIES_PER_TABLE; i++){
        p->entries[i] = (PagingEntryBitField_t) {present:1, writeable: 1, 0ULL};
    }
}

size_t pageTableNextSlot(PageTable_t* p) {
    for (int i = 0 ; i < PAGE_ENTRIES_PER_TABLE; i++) {
        // If the entry is NULL 
        if ( !p->entries[i].present ){
            // Return the index
            return i;
        }
    }
    // Return -1 on none available
    return -1ULL;
}

VirtualAddress createVirtualAddress( uint64_t p4idx, uint64_t p3idx, uint64_t p2idx, uint64_t p1idx, uint64_t off ){

    return  (VirtualAddress)  ( (0b1111111111111111ULL << 48)   | 
                                (ONLY_BITS(off,12))             | 
                                (ONLY_BITS(p1idx, 9) << 12)     |
                                (ONLY_BITS(p2idx, 9) << 21)     |
                                (ONLY_BITS(p3idx, 9) << 30)     |
                                (ONLY_BITS(p4idx, 9) << 39));

}


VirtualAddress mapPageToKernelVirtualSpace( PhysicalAddress page ) {

    return page;

}