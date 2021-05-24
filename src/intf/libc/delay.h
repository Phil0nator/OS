#pragma once
#include <stddef.h>
#include <stdint.h>
#include "drivers/timer.h"


void delayticks(uint64_t ticks);
void delaysecs (uint64_t secs);