#include "libc/memory.h"
#include "libc/multiboot.h"

void memset (char* start, char c, size_t n){
    for (char* iter = start; iter < start + n; iter ++) {
        *iter = c;
    }
}
void memmove(char* dest, char* source, size_t n);
void memcpy (char* dest, char* source, size_t n){
    for ( n--; n != -1ULL; n-- )
        dest[n] = source[n];
}


size_t memsize(const MemoryChunk* m){
    return m->end - m->start;
}
bool memcontains(const MemoryChunk* m, char* ptr){
    return ptr > m->start && ptr < m->end;
}

bool physicalMemoryAreaValid(const PhysicalMemoryArea* pma) {
    return 
        pma->type == MULTIBOOT_MEMORY_AVAILABLE &&
        pma->chunk.start != NULL //&& 
        //(!memcontains(&pma->chunk, &physicalMemoryAreaValid)); // check if the memory area contains kernel code
        ;
}
