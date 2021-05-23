
#include "IDT.h"
#include "libc/memory.h"
#include "print.h"

struct idt_entry IDT[256];
struct idt_ptr hardcodedIDTP;

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


/* These are function prototypes for all of the exception
*  handlers: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */
extern void isr_code0();
extern void isr_code1();
extern void isr_code2();
extern void isr_code3();
extern void isr_code4();
extern void isr_code5();
extern void isr_code6();
extern void isr_code7();
extern void isr_code8();
extern void isr_code9();
extern void isr_code10();
extern void isr_code11();
extern void isr_code12();
extern void isr_code13();
extern void isr_code14();
extern void isr_code15();
extern void isr_code16();
extern void isr_code17();
extern void isr_code18();
extern void isr_code19();
extern void isr_code20();
extern void isr_code21();
extern void isr_code22();
extern void isr_code23();
extern void isr_code24();
extern void isr_code25();
extern void isr_code26();
extern void isr_code27();
extern void isr_code28();
extern void isr_code29();
extern void isr_code30();
extern void isr_code31();

void create_isrs(){

    setIDTGate(0, ((size_t)isr_code0), 0x08, 0x8E);
    setIDTGate(1, ((size_t)isr_code1), 0x08, 0x8E);
    setIDTGate(2, ((size_t)isr_code2), 0x08, 0x8E);
    setIDTGate(3, ((size_t)isr_code3), 0x08, 0x8E);
    setIDTGate(4, ((size_t)isr_code4), 0x08, 0x8E);
    setIDTGate(5, ((size_t)isr_code5), 0x08, 0x8E);
    setIDTGate(6, ((size_t)isr_code6), 0x08, 0x8E);
    setIDTGate(7, ((size_t)isr_code7), 0x08, 0x8E);

    setIDTGate(8, ((size_t)isr_code8), 0x08, 0x8E);
    setIDTGate(9, ((size_t)isr_code9), 0x08, 0x8E);
    setIDTGate(10, ((size_t)isr_code10), 0x08, 0x8E);
    setIDTGate(11, ((size_t)isr_code11), 0x08, 0x8E);
    setIDTGate(12, ((size_t)isr_code12), 0x08, 0x8E);
    setIDTGate(13, ((size_t)isr_code13), 0x08, 0x8E);
    setIDTGate(14, ((size_t)isr_code14), 0x08, 0x8E);
    setIDTGate(15, ((size_t)isr_code15), 0x08, 0x8E);

    setIDTGate(16, ((size_t)isr_code16), 0x08, 0x8E);
    setIDTGate(17, ((size_t)isr_code17), 0x08, 0x8E);
    setIDTGate(18, ((size_t)isr_code18), 0x08, 0x8E);
    setIDTGate(19, ((size_t)isr_code19), 0x08, 0x8E);
    setIDTGate(20, ((size_t)isr_code20), 0x08, 0x8E);
    setIDTGate(21, ((size_t)isr_code21), 0x08, 0x8E);
    setIDTGate(22, ((size_t)isr_code22), 0x08, 0x8E);
    setIDTGate(23, ((size_t)isr_code23), 0x08, 0x8E);

    setIDTGate(24, ((size_t)isr_code24), 0x08, 0x8E);
    setIDTGate(25, ((size_t)isr_code25), 0x08, 0x8E);
    setIDTGate(26, ((size_t)isr_code26), 0x08, 0x8E);
    setIDTGate(27, ((size_t)isr_code27), 0x08, 0x8E);
    setIDTGate(28, ((size_t)isr_code28), 0x08, 0x8E);
    setIDTGate(29, ((size_t)isr_code29), 0x08, 0x8E);
    setIDTGate(30, ((size_t)isr_code30), 0x08, 0x8E);
    setIDTGate(31, ((size_t)isr_code31), 0x08, 0x8E);

}


void install_IDT(){

    // setup the limits for the descriptor pointer
    hardcodedIDTP.limit = (sizeof (struct idt_entry) * 256) - 1;
    hardcodedIDTP.base =  ( (size_t) &IDT );

    memset( (char*) &IDT, 0, sizeof(struct idt_entry)*256);
    
    create_isrs();
    load_interdesctable();

}

void setIDTGate(uint8_t num, size_t base, uint16_t sel, uint8_t flags){

    // Setup the routine's base address
    IDT[num].base_lo = (base & 0xFFFF);
    IDT[num].base_mid = (base >> 16) & 0xFFFF;
    IDT[num].base_high = (base >> 32) & 0xFFFFFFFF;

    // set the segment 'selector' that the entry will use
    IDT[num].sel = sel;
    IDT[num].zero = 0;
    IDT[num].flags = flags;
    IDT[num].reserved = 0;

}
void fault_handler(struct register_state regs) {
    
    print_str("CPU Error: ");
    print_uint64(regs.int_no);
    haltCPU();

    if (regs.int_no < 32) 
    {
        print_set_color(PRINT_COLOR_RED,PRINT_COLOR_BLACK);
        print_str(exception_messages[regs.int_no]);
        haltCPU();
    }
}