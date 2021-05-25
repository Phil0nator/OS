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

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))




void kernel_main(void* addr, uint32_t magic) {
    
    print_clear();
    
    
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Starting the kernel.\n");
    


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

    /* To print the results: (after interrupts exists please)
    for (size_t i = 0 ; i < globalMemoryList_size ; i ++) {
        print_str("{\n     start: ");
        print_uint64((size_t)globalMemoryList[i].chunk.start);
        print_str("\n     end: ");
        print_uint64((size_t)globalMemoryList[i].chunk.end);
        print_str("\n}\n");
        delayticks(5*18);
    }
     */

    //Page test = kalloc_page();
    //print_uint64((size_t)test.addr);
    //memcpy(test.addr, "testing string", 15);
    //print_str(test.addr);

    for (;;);


}