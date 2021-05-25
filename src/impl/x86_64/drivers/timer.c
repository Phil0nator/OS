#include "drivers/timer.h"
#include "print.h"

uint64_t system_timer_ticks;

uint64_t get_system_ticks() {
    return system_timer_ticks;
}

void timer_driver_handle(uint64_t n) {
    n++;
    system_timer_ticks ++;
    // if (system_timer_ticks % 18 == 0){
    //     print_str("One second passed!\n");
    // }
}


void register_timer_driver_irq(){
    installIRQHandler( 0, timer_driver_handle );
}
