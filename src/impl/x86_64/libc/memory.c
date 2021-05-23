#include "libc/memory.h"

void memset (char* start, char c, size_t n){
    for (char* iter = start; iter < start + n; iter ++) {
        *iter = c;
    }
}
void memmove(char* dest, char* source, size_t n);
void memcpy (char* dest, char* source, size_t n);