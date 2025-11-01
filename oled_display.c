#include QMK_KEYBOARD_H
#include "oled_display.h"
#include "layers.h"

#ifdef WPM_ENABLE
#    include "wpm.h"
#endif
#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#endif

// --- Heartbeat configuration ---
#define HEARTBEAT_INTERVAL 300 // ms between frames
#define HEARTBEAT_FRAMES 3
static uint16_t oled_timer_heartbeat = 0;
static uint8_t  heartbeat_frame      = 0;

// --- Row layout ---
#define ROW_LAYER 0
#define ROW_SEP1 2
#define ROW_MOD_START 4
#define ROW_CG_TOGG 9
#define ROW_WPM_LABEL 11
#define ROW_WPM_COUNT 12
#define ROW_BOTTOM 14

// --- Static strings in PROGMEM ---
static const char LAYER_BASE[] PROGMEM  = "macOS";
static const char LAYER_WIN[] PROGMEM   = "Win";
static const char LAYER_LIN[] PROGMEM   = "Linux";
static const char LAYER_LOWER[] PROGMEM = "LOWER";
static const char LAYER_RAISE[] PROGMEM = "RAISE";
static const char LAYER_ADJ[] PROGMEM   = "ADJUST";

// --- Layer array ---
static const char *const LAYERS[] PROGMEM = {LAYER_BASE, LAYER_WIN, LAYER_LIN, LAYER_LOWER, LAYER_RAISE, LAYER_ADJ};

static const char MOD_CTRL[] PROGMEM  = "Ctrl";
static const char MOD_SHIFT[] PROGMEM = "Shift";
static const char MOD_ALT[] PROGMEM   = "Alt";
static const char MOD_GUI[] PROGMEM   = "GUI";

static const char CAPS_STR[] PROGMEM  = "CAP ";
static const char KM_STR[] PROGMEM    = "KM  ";
static const char WPM_LABEL[] PROGMEM = "WPM:";

// --- Heartbeat frames (use real escaped bytes) ---
static const char HEART_FRAME_1[] PROGMEM = "\x04"; // bigger heart glyph
static const char HEART_FRAME_2[] PROGMEM = "\x03"; // small heart glyph
static const char HEART_FRAME_3[] PROGMEM = " ";    // off

// --- Modifier array ---
static const char *const MODS[] PROGMEM = {MOD_CTRL, MOD_SHIFT, MOD_ALT, MOD_GUI};

// --- Separator array in PROGMEM ---
static const char SEPARATOR[32] PROGMEM = {[0 ... 31] = 0xFF};

// --- Draw a horizontal line separator ---
void draw_separator(uint8_t row) {
    oled_set_cursor(0, row);
    oled_write_raw_P(SEPARATOR, sizeof(SEPARATOR));
}

// --- Get current active layer name ---
const char *get_layer_name(void) {
    static char buf[12];
    uint8_t     l = get_highest_layer(layer_state);
    if (l > _ADJUST) l = 0;
    const char *ptr = (const char *)pgm_read_ptr(&LAYERS[l]);
    strcpy_P(buf, ptr);
    return buf;
}

// --- Rotate screen for vertical orientation ---
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// --- OLED display task ---
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // --- Heartbeat animation ---
        if (timer_elapsed(oled_timer_heartbeat) > HEARTBEAT_INTERVAL) {
            oled_timer_heartbeat = timer_read();
            heartbeat_frame      = (heartbeat_frame + 1) % HEARTBEAT_FRAMES;
        }

        // --- Layer name ---
        oled_set_cursor(0, ROW_LAYER);
        oled_write_ln(get_layer_name(), false);

        // --- First separator ---
        draw_separator(ROW_SEP1);

        // --- Active modifiers vertically ---
        uint8_t mods = get_mods();
        for (uint8_t i = 0; i < 4; i++) {
            oled_set_cursor(0, ROW_MOD_START + i);
            char        modbuf[8];
            const char *m = (const char *)pgm_read_ptr(&MODS[i]);
            strcpy_P(modbuf, m);
            oled_write_ln(modbuf, mods & (MOD_MASK_CTRL << i));
        }

#ifdef WPM_ENABLE
        oled_set_cursor(0, ROW_WPM_LABEL);
        oled_write_ln_P(WPM_LABEL, false);

        oled_set_cursor(0, ROW_WPM_COUNT);
        char wpm_str[16];
        snprintf(wpm_str, sizeof(wpm_str), " %03d", get_current_wpm());
        oled_write_ln(wpm_str, false);
#endif
        // --- Bottom row: KM/CAPS + heartbeat animation ---
        oled_set_cursor(0, ROW_BOTTOM);
        oled_write_P(is_caps_word_on() ? CAPS_STR : KM_STR, false);

        switch (heartbeat_frame) {
            case 0:
                oled_write_P(HEART_FRAME_1, false);
                break;
            case 1:
                oled_write_P(HEART_FRAME_2, false);
                break;
            case 2:
                oled_write_P(HEART_FRAME_3, false);
                break;
        }

    } else {
        // --- Heartbeat animation for slave ---
        if (timer_elapsed(oled_timer_heartbeat) > HEARTBEAT_INTERVAL) {
            oled_timer_heartbeat = timer_read();
            heartbeat_frame      = (heartbeat_frame + 1) % HEARTBEAT_FRAMES;
        }

        // --- Bottom row: KM + heartbeat (mirror master layout) ---
        oled_set_cursor(0, ROW_BOTTOM);
        oled_write_P(is_caps_word_on() ? CAPS_STR : KM_STR, false);
        switch (heartbeat_frame) {
            case 0:
                oled_write_P(HEART_FRAME_1, false);
                break;
            case 1:
                oled_write_P(HEART_FRAME_2, false);
                break;
            case 2:
                oled_write_P(HEART_FRAME_3, false);
                break;
        }
    }

    return false;
}
