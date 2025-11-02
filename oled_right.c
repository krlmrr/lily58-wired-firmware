#include QMK_KEYBOARD_H
#include "oled_display.h"
#include <string.h> // for strlen

// Dimensions of the display
#define OLED_WIDTH 5
#define OLED_HEIGHT 15

// Ball state
static int8_t   ball_x      = 0;
static int8_t   ball_y      = 0;
static int8_t   vel_x       = 1;
static int8_t   vel_y       = 1;
static uint16_t last_update = 0;
#define BALL_INTERVAL 200 // ms between ball moves

// Ball string (1 to 3 characters)
static const char *BALL_STR = "km"; // change to "@", "km", or "abc"

// Clear the screen
void oled_clear_screen(void) {
    for (uint8_t y = 0; y < OLED_HEIGHT; y++) {
        oled_set_cursor(0, y);
        oled_write("     ", false); // full width
    }
}

// Draw the ball
void oled_draw_ball(void) {
    oled_set_cursor(ball_x, ball_y);
    oled_write(BALL_STR, false);
}

// Update ball position (timed)
void oled_update_ball(void) {
    if (timer_elapsed(last_update) < BALL_INTERVAL) return;
    last_update = timer_read();

    uint8_t ball_width = strlen(BALL_STR);

    // Move the ball
    ball_x += vel_x;
    ball_y += vel_y;

    // Bounce off edges considering ball width
    if (ball_x <= 0 || ball_x + ball_width > OLED_WIDTH) vel_x = -vel_x;
    if (ball_y <= 0 || ball_y >= OLED_HEIGHT - 1) vel_y = -vel_y;

    // Keep inside bounds
    if (ball_x < 0) ball_x = 0;
    if (ball_x + ball_width > OLED_WIDTH) ball_x = OLED_WIDTH - ball_width;
    if (ball_y < 0) ball_y = 0;
    if (ball_y >= OLED_HEIGHT) ball_y = OLED_HEIGHT - 1;
}

// OLED task for secondary display
bool oled_task_right(void) {
    oled_clear_screen();
    oled_draw_ball();
    oled_update_ball();
    return false;
}
