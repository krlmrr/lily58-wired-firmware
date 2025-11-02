#include QMK_KEYBOARD_H
#include "oled_display.h"
#include "layers.h"
#include "oled_right.c"
#include "oled_left.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_task_left();
        // oled_task_right(); // Here for testing on the main display
    } else {
        oled_task_right();
    }
    return false;
}
