#include QMK_KEYBOARD_H
#include "oled_display.h"
#include "layers.h"
#include "transactions.h"
#include "oled_left.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    return oled_task_left();
}

static bool remote_caps_word = false;

bool caps_word_active(void) {
    return is_keyboard_master() ? is_caps_word_on() : remote_caps_word;
}

static void receive_caps_word(uint8_t in_len, const void *in_data, uint8_t out_len, void *out_data) {
    remote_caps_word = *(const bool *)in_data;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_CAPS_WORD, receive_caps_word);
    if (!autocorrect_is_enabled()) {
        autocorrect_enable();
    }
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    static bool     last_sent = false;
    static uint32_t last_sync = 0;
    bool            active    = is_caps_word_on();

    if (active != last_sent || timer_elapsed32(last_sync) > 500) {
        if (transaction_rpc_send(USER_SYNC_CAPS_WORD, sizeof(active), &active)) {
            last_sent = active;
            last_sync = timer_read32();
        }
    }
}
