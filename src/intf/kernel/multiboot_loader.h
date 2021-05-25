#pragma once
#include <stddef.h>
#include <stdint.h>
#include "libc/multiboot.h"
#include "print.h"
#include "utils/cpuutils.h"

void loadMultiboot2_mmap( struct multiboot_tag* mmap_tag );

void loadMultiboot2Tags( void* addr, uint32_t magic );


