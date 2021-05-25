#include "kernel/kalloc.h"

// An indexer for loading raw physical memory areas from the multiboot
// mmap entry list.
static size_t kalloc_initialPageLoader = 0;

/**
 * a page node will be stored in the beggining of a freed page,
 * so the pointer value to the kalloc_page_node itself is a pointer to the
 * page, which is guarenteed to be of size 4096 (PAGE_SIZE)
 */
struct kalloc_page_node{
    struct kalloc_page_node* prev;
    struct kalloc_page_node* next;
};

typedef struct kalloc_page_node kalloc_page_node_t;

// A linked list storing physical addresses of free pages
static kalloc_page_node_t* kalloc_freePages = NULL;

// Add a new page to the linked list
static void push_free_page(void* p) {
    // If the list head exists already:
    if (kalloc_freePages) {
        // If there is a prev element:
        if (kalloc_freePages->prev) {
            // Update the end of the list with the appended page
            kalloc_freePages->prev->next = p;
            ((kalloc_page_node_t*) p)->prev = kalloc_freePages->prev;
            

        }else { // if there is no second element
            // Update the head->next
            kalloc_freePages->next = p;
            // setup a prev for p
            ((kalloc_page_node_t*) p)->prev = kalloc_freePages;

        }

        // Append p via ->prev 
        kalloc_freePages->prev = p;
        // Ensure that the next pointer doesn't dangle
        kalloc_freePages->prev->next = NULL;
    }else {
        // If the linked list does not yet exist:
        // Set it to P
        kalloc_freePages = p;
        kalloc_freePages->next = NULL;
        kalloc_freePages->prev = NULL;
    }

}



Page kalloc_page(){
    Page out;
    out.addr = NULL;
    // In order to return a page, there are two methods:
    //  1. Find an unopened page from the multiboot2 mmap entries
    //  2. Find a pre-existing page that has already been loaded from
    //      multiboot2
    // The first page will of course have to be loaded from multiboot
    // 


    // If there are no free existing pages available...
    if (kalloc_freePages == NULL) {
        
        // While loop to seach for valid memory
        while ( !out.addr ) {
            // If more memory remains in multiboot
            if (kalloc_initialPageLoader < globalMemoryList_size) {
                // Get the next area of physical memory (arbitrary size)
                PhysicalMemoryArea area;
                area.type = globalMemoryList[ kalloc_initialPageLoader ].type;
                area.chunk.start = globalMemoryList[ kalloc_initialPageLoader ].chunk.start;
                area.chunk.end = globalMemoryList[ kalloc_initialPageLoader ].chunk.end;


                // Check if the area is valid for RAM use...
                // if not, the loop continues
                if (physicalMemoryAreaValid( &area )) {
                    out.addr = area.chunk.start;
                    // since a valid page has been found,
                    // all other valid pages in this area need to be loaded into the free
                    // pages linked list so that they can be loaded too later.
                    char* ptr = out.addr + PAGE_SIZE;
                    while (ptr < area.chunk.end) {
                        // add each offset of PAGE_SIZE to the linked list
                        push_free_page(ptr);
                        ptr += PAGE_SIZE;
                    }
                    
                }

                kalloc_initialPageLoader ++ ;


            } else {
                return (Page){addr:NULL}; // Out of Memory Error
            }
        }

    }
    else 
    {
        // If a freed page does exist, simply return it
        // and pop it off the list
        out.addr = (char*) kalloc_freePages;
        kalloc_freePages = kalloc_freePages->next;
    }

    return out;

}
void kfree_page(Page p);

void * kalloc(size_t size);
void * krealloc(void* kchunk, size_t newsize);
void kfree(void* kchunk);