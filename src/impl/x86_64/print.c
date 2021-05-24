#include "print.h"
#include "libc/memory.h"
const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct VMChar {

    uint8_t ch;
    uint8_t color;

};

struct VMChar* buffer = (struct VMChar*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct VMChar empty = (struct VMChar) {
        ch: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct VMChar character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct VMChar) {
        ch: (uint8_t) character,
        color: color,
    };

    col++;
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_uint64(uint64_t x){
    if(x == 0){
        print_str("0");
        return;
    }
    
    char buffer[22];
    memset(buffer, 0, 22);
    int numbers[14], n=0;
    while (x > 0) {
        numbers[n] = x % 10;
        x = x / 10;
        n++;
    }
    int i = 0;
    buffer[n] = '\0';
    n--;
    while (n >= 0) {
        buffer[i] = numbers[n] + '0';
        n--;
        i++;
    }
    print_str(buffer);
}


void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void print_success_ok() {
    uint8_t cc = color;
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("[ ");
    print_set_color(PRINT_COLOR_LIGHT_GREEN, PRINT_COLOR_BLACK);
    print_str("OK");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str(" ]\n");
    color = cc;
}