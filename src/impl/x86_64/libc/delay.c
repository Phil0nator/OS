#include "libc/delay.h"

void delayticks(uint64_t ticks){
    uint64_t startt = get_system_ticks();
    while (get_system_ticks() - startt < ticks) {}
}
void delaysecs (uint64_t secs){
    while (secs) {
        if (get_system_ticks() % SYSTEM_TICKS_PER_SECOND == 0){
            secs --;
        }
    }
}