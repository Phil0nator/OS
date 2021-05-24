#pragma once
#include "utils/cpuutils.h"

struct idt_entry {

    unsigned short base_lo;
    unsigned short sel;
    unsigned char  zero;
    unsigned char  flags;
    unsigned short base_mid;
    unsigned int base_high;
    unsigned int reserved;

} __attribute__((packed));

struct idt_ptr 
{
    unsigned short limit;
    size_t base;
} __attribute__((packed));

// struct register_state {
//     size_t fs, gs;
//     size_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
//     size_t int_no, errCode;
//     size_t rip, cs, eflags, useresp, ss;
// };

/* This defines what the stack looks like after an ISR was running */
struct register_state
{
    size_t gs, fs;      /* pushed the segs last */
    size_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    size_t int_no, err_code;    /* our 'push byte #' and ecodes do this */
    size_t eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

extern struct idt_entry IDT[256];
extern struct idt_ptr hardcodedIDTP;

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
extern unsigned char* cpu_exceptions_messages[31];


extern void* irq_routines[16];

void setIDTGate(uint8_t num, size_t base, uint16_t sel, uint8_t flags);
void install_IDT();
void irq_remap();
void installIRQHandler(int irq, void(*handler)(uint64_t r));
void uninstallIRQHandler(int irq);
void install_IRQs();
void fault_handler(uint64_t err);
void irq_handler(uint64_t err);