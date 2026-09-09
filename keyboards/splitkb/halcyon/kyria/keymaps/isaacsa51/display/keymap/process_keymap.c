#include "process_keymap.h"
#include "action_layer.h"
#include "keycode_strings.h"
#include "draw_keymap.h"
#include "../utils.h"

#define DISPLAY_WIDTH 135
#define DISPLAY_HEIGHT 240

static layer_state_t last_layer_state = 0;
static uint8_t last_default_layer = 0;

// Include the keymap data
extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];

// Function to get the active keymap as strings
void get_active_keymap_strings(const char* keymap_strings[5][6], bool is_right_side) {
    // Get the current active layer
    uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 6; col++) {
            int keyboard_row = row;
            int keyboard_col = col;
            get_keyboard_key_position(row, col, is_right_side, &keyboard_row, &keyboard_col);

            // Read the keycode from the keymap array
            uint16_t keycode = pgm_read_word(&keymaps[active_layer][keyboard_row][keyboard_col]);

            // Convert keycode to string using the existing function
            const char* key_string = get_keycode_string_hlc(keycode);

            // Store the string in our array
            keymap_strings[row][col] = key_string;
        }
    }
}

void draw_keymap_layout(painter_device_t surface) {
    qp_rect(surface, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, HSV_BLACK, 1);

    // Create arrays to hold the active keymap strings for left and right sides
    const char* left_keymap[5][6];
    const char* right_keymap[5][6];

    // Get the current active keymap as strings for both sides
    get_active_keymap_strings(left_keymap, false);  // Left side
    get_active_keymap_strings(right_keymap, true);  // Right side

    // Draw the layout grid with the actual keymap
    draw_layout_grid(surface, 0, 0, true, left_keymap);
    draw_layout_grid(surface, 0, 117, false, right_keymap);
}

bool should_redraw_keymap(layer_state_t last_layer_state, uint8_t last_default_layer) {
    // Check if layer state has changed
    layer_state_t current_layer_state = layer_state | default_layer_state;
    uint8_t current_default_layer = get_highest_layer(default_layer_state);

    return (current_layer_state != last_layer_state || current_default_layer != last_default_layer);
}

void update_layer_states(layer_state_t* last_layer_state, uint8_t* last_default_layer) {
    *last_layer_state = layer_state | default_layer_state;
    *last_default_layer = get_highest_layer(default_layer_state);
}

bool process_keymap_display(painter_device_t surface) {
    // Check if we need to redraw the keymap
    if (should_redraw_keymap(last_layer_state, last_default_layer)) {
        // Redraw the layout grid with the updated keymap
        draw_keymap_layout(surface);

        // Update our stored states
        update_layer_states(&last_layer_state, &last_default_layer);

        return true;
    }

    return false;
}

void reset_keymap_display(void) {
    last_layer_state = 0;
    last_default_layer = 0;
}
