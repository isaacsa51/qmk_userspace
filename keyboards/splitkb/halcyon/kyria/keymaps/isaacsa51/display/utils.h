#pragma once

#include "quantum.h"

void get_display_key_position(int keyboard_row, int keyboard_col, int *display_row, int *display_col, bool* is_right_side);
void get_keyboard_key_position(int display_row, int display_col, bool is_right_side, int *keyboard_row, int *keyboard_col);
