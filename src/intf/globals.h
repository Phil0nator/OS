#pragma once
#include "libc/memory.h"


#define PAGE_SIZE 4096ULL

extern int errno;

extern PhysicalMemoryArea globalMemoryList[24];
extern size_t globalMemoryList_size;