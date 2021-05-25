#pragma once
#include "libc/memory.h"
#include "globals.h"
#include "print.h"


Page kalloc_page();
void kfree_page(Page p);

void * kalloc(size_t size);
void * krealloc(void* kchunk, size_t newsize);
void kfree(void* kchunk);