#pragma once
#include <stdint.h>
#include <stddef.h>

enum CPUException {
    DIVZER = 0,
    DEBUG = 1,
    NON_MASKABLE_INTERRUPT = 2,
    BREAKPOINT  = 3,
    OVERFLOW  = 4,
    OUT_OF_BOUNDS = 5,
    INVALID_OPCODE = 6,
    NO_COPROCESSOR = 7,
    DOUBLE_FAULT = 8,
    COPROCESSOR_SEGMENT_OVERRUN = 9,
    BAD_TSS  =10,
    SEGMENT_NOT_PRESENT = 11,
    STACK_FAULT = 12,
    GENERAL_PROTECTION = 13,
    PAGE_FAULT = 14,
    UNKOWN_INTERRUPT = 15,
    COPROCESSOR_FAULT = 16,
    ALIGNMENT_CHECK = 17,
    MACHINE_CHECK = 18,
    MAX_ERR = 31

};

typedef uint16_t IOPort;

extern void haltCPU();

extern char inb(IOPort p);
extern void outb(IOPort p, char o);
extern short inw(IOPort p);
extern void outw(IOPort p, short o);

extern void load_interdesctable();
extern void start_system_interrupts();
