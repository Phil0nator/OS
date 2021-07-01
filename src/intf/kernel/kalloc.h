#pragma once
#include "libc/memory.h"
#include "globals.h"
#include "print.h"
#include "Paging.h"



va_t kalloc_page();
void kfree_page(va_t kchunk);

void kalloc_init(  );