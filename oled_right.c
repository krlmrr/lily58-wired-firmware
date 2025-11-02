#include QMK_KEYBOARD_H
#include "oled_display.h"

// --- Screen dimensions ---
#define ROWS 14
#define COLS 32

bool oled_task_right(void) {
    oled_clear();

    for (uint8_t c = 0; c < COLS; c++) {
        oled_set_cursor(c, 0);
        oled_write("█", false);
        oled_set_cursor(c, ROWS - 2);
        oled_write("█", false);
    }

    // --- Draw left and right borders ---
    for (uint8_t r = 1; r < ROWS - 2; r++) {
        oled_set_cursor(0, r);
        oled_write("█", false);
        oled_set_cursor(COLS - 1, r);
        oled_write("█", false);
    }

    return false;
}
