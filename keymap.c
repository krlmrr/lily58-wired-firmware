#include QMK_KEYBOARD_H
#include "layers.h"

enum custom_keycodes {
    ARROW = SAFE_RANGE, // "->"
    DBLARROW,           // "=>"
    RETURN,             // "return"
    QWERTY_LAYER,       // Custom keycode for QWERTY layer
    WIN_LAYER,          // Custom keycode for WIN layer
    LIN_LAYER           // Custom keycode for LIN layer
};

#define send_string_on_press(record, string) \
    do {                                     \
        if ((record)->event.pressed) {       \
            SEND_STRING(string);             \
        }                                    \
        return false;                        \
    } while (0)

void set_and_persist_layer(uint8_t layer) {
    layer_state_set(1UL << layer);
    set_single_persistent_default_layer(layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            send_string_on_press(record, "->");
        case DBLARROW:
            send_string_on_press(record, "=>");
        case RETURN:
            send_string_on_press(record, "return");
        case QWERTY_LAYER:
            if (record->event.pressed) {
                set_and_persist_layer(_QWERTY);
            }
            return false;
        case WIN_LAYER:
            if (record->event.pressed) {
                set_and_persist_layer(_WIN);
            }
            return false;
        case LIN_LAYER:
            if (record->event.pressed) {
                set_and_persist_layer(_LIN);
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_LALT, OS_HYPR, MO(_RAISE), MT(MOD_LGUI, KC_SPC), MT(MOD_RGUI, KC_SPC), MO(_LOWER), OS_HYPR, KC_RALT),

    [_WIN] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_LALT, KC_LGUI, MO(_RAISE), MT(MOD_LCTL, KC_SPC), MT(MOD_RCTL, KC_SPC), MO(_LOWER), OS_HYPR, KC_RALT),

    [_LIN] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT, KC_LALT, KC_LGUI, MO(_RAISE), MT(MOD_LCTL, KC_SPC), MT(MOD_RCTL, KC_SPC), MO(_LOWER), OS_HYPR, KC_RALT),

    [_LOWER] = LAYOUT(KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_TRNS, KC_HASH, KC_AMPR, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_EQUAL, KC_NO, ARROW, DBLARROW, KC_NO, KC_TRNS, KC_EXLM, KC_DLR, KC_LPRN, KC_RPRN, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, RETURN, KC_TRNS, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_RAISE] = LAYOUT(QWERTY_LAYER, WIN_LAYER, LIN_LAYER, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_ADJUST] = LAYOUT(TO(_QWERTY), TO(_WIN), TO(_LIN), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
