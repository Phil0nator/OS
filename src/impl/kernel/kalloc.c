#include "kernel/kalloc.h"
#include "kernel/Paging.h"
#include "libc/delay.h"

// typedef struct kalloc_pf
// {
//     struct kalloc_pf* next;
//     struct kalloc_pf* prev;
// } kallocpf_t;

// struct kalloc_pf* kalloc_pf_base = NULL;

static void* page_entries[16384];
static size_t page_entries_pointer = 0;


static void* pop_page()
{
    page_entries_pointer--;
    return page_entries[page_entries_pointer];
}


static void push_page( void* pf )
{
    page_entries[page_entries_pointer++] = pf;
}


va_t kalloc_page()
{
    return (va_t) pop_page();
}
void kfree_page(va_t kchunk)
{
    push_page( (struct kalloc_pf*)kchunk );
}


void kalloc_init(  )
{
    size_t availableBytes = 0;
    for ( size_t i = 0 ; i < globalMemoryList_size; i++ )
    {
        if( physicalMemoryAreaValid( &globalMemoryList[i] )  )
        {
            pa_t start = (pa_t) globalMemoryList[i].chunk.start;
            pa_t end = (pa_t) globalMemoryList[i].chunk.end;
            
            start = (pa_t) PAGE_ALIGN_NEXT((uint64_t)(start));
            availableBytes += (size_t) (end-start);

            while (start < end )
            {
                if (start < (pa_t) 3178495ULL)
                {
                    void* startpf = (void*) start;
                    push_page( startpf );
                    start += PAGE_SIZE;
                }
                else
                {
                    goto end_kinit;
                }
            }

            
        }
    }
    end_kinit:
    print_str("Available bytes of memory: ");
    print_uint64( availableBytes );
    print_newline();

}