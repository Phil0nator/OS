#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct { 
    char* start;
    char* end;
} MemoryChunk;

typedef struct {

    MemoryChunk chunk;
    uint32_t type;

} PhysicalMemoryArea;

// REQUIRE: size of 4096
typedef struct {
    void* addr;
} Page; 


size_t memsize(const MemoryChunk* m);
bool physicalMemoryAreaValid(const PhysicalMemoryArea* pma);

void memset (char* start, char c, size_t n);
void memmove(char* dest, char* source, size_t n);
void memcpy (char* dest, char* source, size_t n);