#pragma once

#include <stdint.h>
#include <stddef.h>

void memset (char* start, char c, size_t n);
void memmove(char* dest, char* source, size_t n);
void memcpy (char* dest, char* source, size_t n);