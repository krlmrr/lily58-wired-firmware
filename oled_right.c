#include QMK_KEYBOARD_H
#include "oled_display.h"

// Dimensions of the display
#define OLED_WIDTH 5
#define OLED_HEIGHT 15

// Ball size
#define BALL_WIDTH 2
#define BALL_HEIGHT 2

// Ball state
static int8_t   ball_x      = 0;
static int8_t   ball_y      = 0;
static int8_t   vel_x       = 1;
static int8_t   vel_y       = 1;
static uint16_t last_update = 0;
#define BALL_INTERVAL 150 // ms between ball moves

// Clear the screen
void oled_clear_screen(void) {
    for (uint8_t y = 0; y < OLED_HEIGHT; y++) {
        oled_set_cursor(0, y);
        oled_write("     ", false); // full width
    }
}

// Draw the 2x2 ball
void oled_draw_ball(void) {
    for (uint8_t y = 0; y < BALL_HEIGHT; y++) {
        oled_set_cursor(ball_x, ball_y + y);
        oled_write("@@", false); // 2 characters wide
    }
}

// Update ball position (timed)
void oled_update_ball(void) {
    if (timer_elapsed(last_update) < BALL_INTERVAL) return;
    last_update = timer_read();

    // Move the ball
    ball_x += vel_x;
    ball_y += vel_y;

    // Bounce if hitting edges
    if (ball_x < 0 || ball_x > OLED_WIDTH - BALL_WIDTH) vel_x = -vel_x;
    if (ball_y < 0 || ball_y > OLED_HEIGHT - BALL_HEIGHT) vel_y = -vel_y;

    // Clamp inside bounds
    if (ball_x < 0) ball_x = 0;
    if (ball_x > OLED_WIDTH - BALL_WIDTH) ball_x = OLED_WIDTH - BALL_WIDTH;
    if (ball_y < 0) ball_y = 0;
    if (ball_y > OLED_HEIGHT - BALL_HEIGHT) ball_y = OLED_HEIGHT - BALL_HEIGHT;
}

// OLED task for secondary display
bool oled_task_right(void) {
    oled_clear_screen();
    oled_draw_ball();
    oled_update_ball();
    return false;
}
