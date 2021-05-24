#pragma once
#include "IDT.h"


#define KBDUS_BIT_SPECIAL (1 << 7)

#define KBDUS_ALT (18 | KBDUS_BIT_SPECIAL)
#define KBDUS_CAPS_LOCK (20 | KBDUS_BIT_SPECIAL)
#define KBDUS_TAB (9 | KBDUS_BIT_SPECIAL)
#define KBDUS_CTRL (17 | KBDUS_BIT_SPECIAL)
#define KBDUS_F1 (112 | KBDUS_BIT_SPECIAL)
#define KBDUS_F2 (113 | KBDUS_BIT_SPECIAL)
#define KBDUS_F3 (114 | KBDUS_BIT_SPECIAL)
#define KBDUS_F4 (115 | KBDUS_BIT_SPECIAL)
#define KBDUS_F5 (116 | KBDUS_BIT_SPECIAL)
#define KBDUS_F6 (117 | KBDUS_BIT_SPECIAL)
#define KBDUS_F7 (118 | KBDUS_BIT_SPECIAL)
#define KBDUS_F8 (119 | KBDUS_BIT_SPECIAL)
#define KBDUS_F9 (120 | KBDUS_BIT_SPECIAL)
#define KBDUS_F10 (121 | KBDUS_BIT_SPECIAL)
#define KBDUS_F11 (122 | KBDUS_BIT_SPECIAL)
#define KBDUS_F12 (123 | KBDUS_BIT_SPECIAL)
#define KBDUS_HOME (36 | KBDUS_BIT_SPECIAL)
#define KBDUS_UP (38 | KBDUS_BIT_SPECIAL)
#define KBDUS_PAGEUP (33 | KBDUS_BIT_SPECIAL)
#define KBDUS_LEFT (37 | KBDUS_BIT_SPECIAL)
#define KBDUS_RIGHT (39 | KBDUS_BIT_SPECIAL)
#define KBDUS_END (35 | KBDUS_BIT_SPECIAL)
#define KBDUS_DOWN (40 | KBDUS_BIT_SPECIAL)
#define KBDUS_PAGEDOWN (34 | KBDUS_BIT_SPECIAL)
#define KBDUS_INS (45 | KBDUS_BIT_SPECIAL)
#define KBDUS_DEL (46 | KBDUS_BIT_SPECIAL)


/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
extern unsigned char kbdus[128];


void keyboard_driver_irqhandle(uint64_t e);
void register_keyboard_driver_irq();