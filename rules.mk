LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Disable RGB Light completely
RGB_MATRIX_ENABLE = yes     # Enable per-key RGB matrix
RGB_MATRIX_DRIVER = ws2812  # WS2812 LED driver
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
WPM_ENABLE = yes            # Words Per Minute feature
CAPS_WORD_ENABLE = yes      # Caps Word feature
COMBO_ENABLE = yes
# VIA_ENABLE = yes


# If you want to change the display of OLED, you need to change here
SRC +=  oled_display.c \
        ./lib/layer_state_reader.c \
        rgb_matrix_config.c \
        $(QUANTUM_DIR)/quantum.c
