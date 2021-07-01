#pragma once
#include "libc/memory.h"


#define PAGE_SIZE 4096ULL
#define PAGE_ALIGN(x) (((x) >> 12) << 12)
#define PAGE_ALIGN_NEXT(x) PAGE_ALIGN( ((x)+(1<<12)-1) )



extern int errno;

extern PhysicalMemoryArea globalMemoryList[24];
extern size_t globalMemoryList_size;

extern size_t _BSS_SIZE;
extern void* _KERNEL_START;
extern size_t _KERNEL_SIZE;