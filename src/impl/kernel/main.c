#include "print.h"
#include "utils/cpuutils.h"
#include "IDT.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"

void kernel_main() {
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


    for (;;);


}