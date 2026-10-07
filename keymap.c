#include QMK_KEYBOARD_H
#include <stdint.h>
#include "layers.h"
#include "quantum.h"

enum custom_keycodes {
    ARROW = SAFE_RANGE, // "->"
    DBLARROW,           // "=>"
    RETURN,             // "return"
};

#define MY_MEH LCAG(KC_NO)

// Home-row mods (testing)
#define HRM_S MT(MOD_LALT, KC_S)
#define HRM_L MT(MOD_RALT, KC_L)
#define HRM_D MT(MOD_LCTL, KC_D)
#define HRM_K MT(MOD_RCTL, KC_K)
#define HRM_F MT(MOD_LSFT, KC_F)
#define HRM_J MT(MOD_RSFT, KC_J)

#define send_string_on_press(record, string) \
    do {                                     \
        if ((record)->event.pressed) {       \
            SEND_STRING(string);             \
        }                                    \
        return false;                        \
    } while (0)

static bool is_home_row_mod(uint16_t keycode) {
    switch (keycode) {
        case HRM_S:
        case HRM_L:
        case HRM_D:
        case HRM_K:
        case HRM_F:
        case HRM_J:
            return true;
        default:
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return !is_home_row_mod(keycode);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return is_home_row_mod(keycode);
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return is_home_row_mod(keycode) ? HRM_QUICK_TAP_TERM : QUICK_TAP_TERM;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (is_home_row_mod(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}

bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    if (keycode == MT(MOD_LCTL, KC_ESC)) {
        return false;
    }
    const uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    return (mods & (MOD_LCTL | MOD_LSFT)) == (mods & (MOD_HYPR));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            send_string_on_press(record, "->");
        case DBLARROW:
            send_string_on_press(record, "=>");
        case RETURN:
            send_string_on_press(record, "return");
    }
    return true;
}

// COMB(QUIT, LALT(KC_F4), )
const uint16_t PROGMEM combo_ctrl_spc_q[] = {MT(MOD_LCTL, KC_SPC), KC_Q, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_ctrl_spc_q, LALT(KC_F4)),
};

const key_override_t plus_equal_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_PLUS, KC_EQUAL, 1 << _LOWER);

const key_override_t *key_overrides[] = {
    &plus_equal_override,
};

// Thumb rows shared across base layers so positions stay identical on every OS
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define THUMBS_MAC  OS_HYPR, KC_LALT, MO(_RAISE), MT(MOD_LGUI, KC_SPC), KC_SPC, MO(_LOWER), KC_RALT, MY_MEH
#define THUMBS_PC   OS_HYPR, KC_LALT, MO(_RAISE), MT(MOD_LCTL, KC_SPC), MT(MOD_RCTL, KC_SPC), MO(_LOWER), KC_RALT, KC_LGUI
#define THUMBS_GAME KC_LGUI, KC_LALT, MO(_RAISE), KC_SPC, KC_SPC, MO(_LOWER), KC_RALT, KC_LGUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                    KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, 
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                    KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, 
        MT(MOD_LCTL, KC_ESC), KC_A, HRM_S, HRM_D, HRM_F, KC_G,      KC_H, HRM_J, HRM_K, HRM_L, KC_SCLN, KC_QUOT, KC_LSFT, 
        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT,                    KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_LSFT), 
        THUMBS_MAC
    ),

    [_WIN] = LAYOUT_wrapper(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, MT(MOD_LCTL, KC_ESC), KC_A, HRM_S, HRM_D, HRM_F, KC_G, KC_H, HRM_J, HRM_K, HRM_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_LSFT), THUMBS_PC),

    [_GAME] = LAYOUT_wrapper(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ENT, KC_BSPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, THUMBS_GAME),

    [_LOWER] = LAYOUT(KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_TRNS, KC_HASH, KC_AMPR, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_PLUS, KC_MINS, ARROW, DBLARROW, KC_NO, KC_TRNS, KC_EXLM, KC_DLR, KC_LPRN, KC_RPRN, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, RETURN, KC_TRNS, KC_DEL, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_RAISE] = LAYOUT(KC_NO, PDF(_QWERTY), PDF(_WIN), PDF(_GAME), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_ADJUST] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, AC_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};
