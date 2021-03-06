#include "print.h"
#include "utils/cpuutils.h"
#include "IDT.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "libc/multiboot.h"
#include "kernel/multiboot_loader.h"
#include "globals.h"
#include "libc/delay.h"
#include "kernel/kalloc.h"
#include "kernel/Paging.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))




void kernel_main(void* addr, uint32_t magic) {
    
    print_clear();

    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Starting the kernel.\n");
    
    print_str("Setting up l4 Page: ");
    setupPageTablel4Recursive( &page_table_l4 );
    print_success_ok();


    // Startup tasks:
    print_str("Creating Interrupt Descriptor Table: ");
    install_IDT();
    print_success_ok();

    // Setup drivers
    print_str("Creating Timer Driver: ");
    register_timer_driver_irq();
    print_success_ok();

    print_str("Creating Keyboard Driver: ");
    register_keyboard_driver_irq();
    print_success_ok();

    print_str("Starting System Interrupts: ");
    start_system_interrupts();
    print_success_ok();

    loadMultiboot2Tags(addr, magic);
    
    
    
    kalloc_init();

    
    // va_t test = kalloc_page();
    // if (test) {
    //     memcpy(test, "\ntesting string\n", 17);
    // }else {
    //     print_str("No Memory Error.");
    // }

    //2146304                     -- sign --   |    l4  |  l3    |   l2   |  l1    |   offset  |
    // #define TESTINGNUM ((va_t)0b0000000000000000000000001000000000000000000000000000000000000000ULL)
    int *pa = (int*) kalloc_page();
    struct VirtualAddress va;
    va.OFF=0;
    va.ADDR=1;
    va.PDPT=1;
    va.PML4=1;
    wire_page( (pa_t)pa, *(va_t*)(&va) );
    // print_str("wire_page:\n");
    // //memcpy( TESTINGNUM, "\ntesting\n", 10 );
    // print_str( TESTINGNUM );
    
    *pa = 5;

    int* test = *(int**)(&va);
    // *test = 5;
    print_uint64(*test);

    for (;;);


}