#pragma once
#include "libc/memory.h"


#define PAGE_SIZE 4096ULL


extern MemoryChunk globalMemoryList[256];
extern size_t globalMemoryList_size;