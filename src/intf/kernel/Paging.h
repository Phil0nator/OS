#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "globals.h"
#define PAGE_ENTRIES_PER_TABLE 512


typedef char* va_t;         // Virtual address
typedef uint64_t pa_t;      // Physical address

struct PagingEntryBitField{

    bool present: 1;
    bool writeable: 1;
    bool user_accessbile: 1;
    bool write_through_caching: 1;
    bool disable_cache: 1;
    bool accessed: 1;
    bool dirty: 1;
    bool huge: 1;
    bool global: 1;
    uint32_t free_space: 3;
    uint64_t physicalAddress: 39;
    uint32_t free_space2: 10;
    bool no_execute: 1; 

};


typedef struct PagingEntryBitField PagingEntryBitField_t;


struct PageTable {
    PagingEntryBitField_t entries[PAGE_ENTRIES_PER_TABLE];
};

typedef struct PageTable PageTable_t;

void setupPageTablel4Recursive( PageTable_t* l4 );
void setupGenericPageTable( PageTable_t* p );
va_t createVirtualAddress( 
                                        uint64_t p4idx, 
                                        uint64_t p3idx, 
                                        uint64_t p2idx, 
                                        uint64_t p1idx, 
                                        uint64_t off 
                                    );

void wire_page( pa_t pa, va_t va );

extern PageTable_t page_table_l4;
extern PageTable_t page_table_l3;
extern PageTable_t page_table_l2;
extern PageTable_t page_table_l1;

extern size_t page_table_l4_counter;


