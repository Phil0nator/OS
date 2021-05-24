
#include "print.h"
#include "utils/cpuutils.h"
#include "IDT.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Starting the kernel.\n");
    
    // Startup tasks:
    print_str("Creating Interrupt Descriptor Table: ");
    install_IDT();
    print_success_ok();


    haltCPU();


}