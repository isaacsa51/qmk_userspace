#pragma once

#include "qp.h"
#include "quantum.h"

// Function declarations for keymap processing functionality
void get_active_keymap_strings(const char* keymap_strings[5][6], bool is_right_side);
void draw_keymap_layout(painter_device_t surface);
bool should_redraw_keymap(layer_state_t last_layer_state, uint8_t last_default_layer);
void update_layer_states(layer_state_t* last_layer_state, uint8_t* last_default_layer);
bool process_keymap_display(painter_device_t surface);
void reset_keymap_display(void);
