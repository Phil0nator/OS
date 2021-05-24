#pragma once
#include "IDT.h"
#define SYSTEM_TICKS_PER_SECOND 18

extern uint64_t system_timer_ticks;


void timer_driver_handle(uint64_t n);
void register_timer_driver_irq();

uint64_t get_system_ticks();