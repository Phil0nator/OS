#include "kernel/Paging.h"
#include "print.h"
#include "utils/cpuutils.h"
#include "kernel/kalloc.h"
#define ONLY_BITS(number, bits) (number & ((1ULL<<bits)-1))
#define ONLY_BIT_RANGE( number, bitslow, bitshigh ) (ONLY_BITS((number), (bitshigh)) >> (bitslow)) 

#define PAGE_OFFSET(x) ONLY_BITS(x, 12)
#define PAGE_P1IDX(x) ONLY_BIT_RANGE( x, 12, 21 )
#define PAGE_P2IDX(x) ONLY_BIT_RANGE( x, 21, 30 )
#define PAGE_P3IDX(x) ONLY_BIT_RANGE( x, 30, 39 )
#define PAGE_P4IDX(x) ONLY_BIT_RANGE( x, 39, 48 )


PageTable_t page_table_l1;
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

static void setPresWrit( PageTable_t* p, size_t entry )
{
    p->entries[entry].writeable = 1;
    p->entries[entry].present = 1;
}

void setupGenericPageTable( PageTable_t* p ){
    for (int i = 0 ; i < PAGE_ENTRIES_PER_TABLE; i++){
        p->entries[i] = (PagingEntryBitField_t) {present:1, writeable: 1, 0ULL};
    }
}


va_t createVirtualAddress( uint64_t p4idx, uint64_t p3idx, uint64_t p2idx, uint64_t p1idx, uint64_t off ){

    return  (va_t)  ( (0b1111111111111111ULL << 48)   | 
                                (ONLY_BITS(off,12))             | 
                                (ONLY_BITS(p1idx, 9) << 12)     |
                                (ONLY_BITS(p2idx, 9) << 21)     |
                                (ONLY_BITS(p3idx, 9) << 30)     |
                                (ONLY_BITS(p4idx, 9) << 39));

}

// void identityMap( pa_t pa )
// {
//     page_table_l4.entries[ PAGE_P4IDX(pa) ].physicalAddress = (uint64_t)(&page_table_l3.entries);
//     setPresWrit( &page_table_l4,  PAGE_P4IDX(pa) );
//     page_table_l3.entries[ PAGE_P3IDX(pa) ].physicalAddress = (uint64_t)(&page_table_l3.entries);
//     setPresWrit( &page_table_l3, PAGE_P3IDX(pa) );
//     page_table_l2.entries[ PAGE_P2IDX(pa) ].physicalAddress = (uint64_t)(&page_table_l1.entries);
//     setPresWrit( &page_table_l2, PAGE_P2IDX(pa) );
//     page_table_l1.entries[ PAGE_P1IDX(pa) ].physicalAddress = (uint64_t)( PAGE_ALIGN( pa ) );
//     setPresWrit( &page_table_l1, PAGE_P1IDX(pa) );
// }

void wire_page( pa_t pa, va_t va )
{

    struct VirtualAddress vas;
    vas = *(struct VirtualAddress*)(va);
    
    if ( !page_table_l4.entries[vas.PML4].present )
    {
        pa_t newl3 = kalloc_page();
        page_table_l4.entries[vas.PML4].physicalAddress = newl3;
        setPresWrit( &page_table_l4, vas.PML4 );
    }

    PageTable_t* l3 = (PageTable_t*) page_table_l4.entries[vas.PML4].physicalAddress; 
    if (!l3->entries[vas.PDPT].present)
    {
        pa_t newl2 = kalloc_page();
        l3->entries[vas.PDPT].physicalAddress = newl2;
        setPresWrit( l3, vas.PDPT );
    }

    PageTable_t* l2 = (PageTable_t*) l3->entries[vas.PDPT].physicalAddress;

    if (!l2->entries[vas.TABL].present)
    {
        pa_t newl1 = kalloc_page();
        l2->entries[vas.TABL].physicalAddress = newl1;
        setPresWrit( l2, vas.TABL );
    }

    PageTable_t* l1 = (PageTable_t*) l2->entries[vas.TABL].physicalAddress;

    if (!l1->entries[vas.ADDR].present)
    {
        pa_t newaddr = kalloc_page();
        l1->entries[vas.ADDR].physicalAddress = newaddr;
        setPresWrit( l1, vas.ADDR );
    }


    // *((char*)
    // ((PageTable_t*)
    // ((PageTable_t*)
    // ((PageTable_t*)page_table_l4.entries[ PAGE_P4IDX((uint64_t)va) ].physicalAddress)
    // ->entries[ PAGE_P3IDX((uint64_t)va) ].physicalAddress)
    // ->entries[ PAGE_P2IDX((uint64_t)va) ].physicalAddress)
    // ->entries[ PAGE_P1IDX((uint64_t)va) ].physicalAddress) = 'c';
    
    

    

}
