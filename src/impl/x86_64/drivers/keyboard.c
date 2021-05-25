#include "drivers/keyboard.h"
#include "print.h"

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    KBDUS_CTRL,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    KBDUS_ALT,	/* Alt */
  ' ',	/* Space bar */
    KBDUS_CAPS_LOCK,	/* Caps lock */
    KBDUS_F1,	/* 59 - F1 key ... > */
    KBDUS_F2,   KBDUS_F3,   KBDUS_F4,   KBDUS_F5,   KBDUS_F6,  KBDUS_F7,   KBDUS_F8,   KBDUS_F9,
    KBDUS_F10,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    KBDUS_HOME,	/* Home key */
    KBDUS_UP,	/* Up Arrow */
    KBDUS_PAGEUP,	/* Page Up */
  '-',
    KBDUS_LEFT,	/* Left Arrow */
    0,
    KBDUS_RIGHT,	/* Right Arrow */
  '+',
    KBDUS_END,	/* 79 - End key*/
    KBDUS_DOWN,	/* Down Arrow */
    KBDUS_PAGEDOWN,	/* Page Down */
    KBDUS_INS,	/* Insert Key */
    KBDUS_DEL,	/* Delete Key */
    0,   0,   0,
    KBDUS_F11,	/* F11 Key */
    KBDUS_F12,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_driver_irqhandle(uint64_t e){
    
    e++;

    unsigned char scancode = inb(0x60);
    
    if (scancode & 0x80){
        // released shift / alt/ ctrl keys
    }
    else 
    {
        // key pressed
        print_char( kbdus[scancode] );
    }
}

void register_keyboard_driver_irq(){
    installIRQHandler( 1, keyboard_driver_irqhandle );
}