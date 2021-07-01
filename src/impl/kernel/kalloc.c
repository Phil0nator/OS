#include "kernel/kalloc.h"
#include "kernel/Paging.h"
#include "libc/delay.h"

typedef struct kalloc_pf
{
    struct kalloc_pf* next;
    struct kalloc_pf* prev;
} kallocpf_t;

struct kalloc_pf* kalloc_pf_base = NULL;

static struct kalloc_pf* pop_page()
{
    if (kalloc_pf_base)
    {
        struct kalloc_pf* out = kalloc_pf_base->prev;
        if (out)
        {
            kalloc_pf_base->prev = out->prev;
            if (out->prev) out->prev->next = kalloc_pf_base;
        }
        else
        {
            out = kalloc_pf_base;
            kalloc_pf_base = NULL;
        }
        print_uint64( (uint64_t)out );
        print_newline();
        // bzero( (va_t)out, PAGE_SIZE );
        return out;
    }
    else
    {
        return NULL;
    }
}

static void push_page( struct kalloc_pf* pf )
{
    if ( kalloc_pf_base )
    {
        if (kalloc_pf_base->prev){
            kalloc_pf_base->prev->next = pf;
            
        }
        pf->prev = kalloc_pf_base->prev;
        kalloc_pf_base->prev = pf;
        pf->next = kalloc_pf_base;
        
    }
    else
    {
        kalloc_pf_base = pf;
        pf->next = NULL;
        pf->prev = NULL;
        
    }
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
                if (start < (pa_t) 3178496ULL)
                {
                    kallocpf_t* startpf = (kallocpf_t*) start;
                    push_page( startpf );
                    start += PAGE_SIZE;
                }
                else
                {
                    return;
                }
            }

            
        }
    }

    print_str("Available bytes of memory: ");
    print_uint64( availableBytes );
    print_newline();

}