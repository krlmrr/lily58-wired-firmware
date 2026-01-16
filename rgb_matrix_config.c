#ifdef RGB_MATRIX_ENABLE
#include QMK_KEYBOARD_H

// Only working LEDs: underglow (0-11), top row keys (12-17)
led_config_t g_led_config = {
    {
        // Matrix to LED mapping - only top row works (offset by 12 for underglow)
        // Left side
        { 12, 13, 14, 15, 16, 17 },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        // Right side - no LEDs for now
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    }, {
        // LED 0-5: Left underglow
        {  20,  64 }, {  40,  64 }, {  60,  64 }, {  80,  64 }, {  60,  32 }, {  40,  32 },
        // LED 6-11: Right underglow
        { 164,  32 }, { 144,  32 }, { 164,  64 }, { 144,  64 }, { 164,  64 }, { 184,  64 },
        // LED 12-17: Top row keys only
        {   0,  13 }, {  15,  10 }, {  30,   6 }, {  45,   3 }, {  60,   6 }, {  75,   9 }
    }, {
        // LED flags: 2=underglow, 4=key
        2, 2, 2, 2, 2, 2,  // Left underglow
        2, 2, 2, 2, 2, 2,  // Right underglow
        4, 4, 4, 4, 4, 4   // Top row keys
    }
};
#endif
