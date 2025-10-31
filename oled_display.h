#pragma once

#include "quantum.h"
#include "layers.h"

void        draw_separator(uint8_t row);
const char *get_layer_name(void);

#ifdef OLED_ENABLE
bool            oled_task_user(void);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
#endif
