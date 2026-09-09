#include "qp.h"
#include "draw_keymap.h"
#include "../fonts/3x5.qff.h"
#include "../fonts/4x7.qff.h"
#include "../fonts/5x7.qff.h"
#include "../fonts/9x12.qff.h"
#include "../images/icons/backspace.qgf.h"
#include "../images/icons/tab.qgf.h"
#include "../images/icons/space.qgf.h"
#include "../images/icons/shift.qgf.h"
#include "../images/icons/enter.qgf.h"
#include "../images/icons/lock.qgf.h"
#include "../images/icons/mute.qgf.h"
#include "../images/icons/volume_down.qgf.h"
#include "../images/icons/volume_up.qgf.h"
#include "quantum.h"
#include <string.h>

#define BORDER_COLOR 0, 0, 100

// Key label colours on the display
#define HSV_ALPHA 0, 0, 255      // white  — letter keys
#define HSV_MOD   85, 255, 255   // green  — everything else (mods, layers, symbols)

// Offsets array for column positioning
static const int offsets[] = {10, 7, 0, 5, 20, 18};
static const int thumb_offsets[] = {10, 7, 4, 2, 2};
static const int square_width = 22;
static const int square_height = 20;

// Prepare fonts
static painter_font_handle_t font_9x12_handle = NULL;
static painter_font_handle_t font_5x7_handle = NULL;
static painter_font_handle_t font_4x7_handle = NULL;
static painter_font_handle_t font_3x5_handle = NULL;

// Icon handles
static painter_image_handle_t backspace_icon = NULL;
static painter_image_handle_t tab_icon = NULL;
static painter_image_handle_t space_icon = NULL;
static painter_image_handle_t shift_icon = NULL;
static painter_image_handle_t enter_icon = NULL;
static painter_image_handle_t lock_icon = NULL;
static painter_image_handle_t mute_icon = NULL;
static painter_image_handle_t volume_down_icon = NULL;
static painter_image_handle_t volume_up_icon = NULL;

// Function to initialize icons if not already loaded
static void init_icons(void) {
    if (backspace_icon == NULL) {
        backspace_icon = qp_load_image_mem(gfx_backspace);
    }
    if (tab_icon == NULL) {
        tab_icon = qp_load_image_mem(gfx_tab);
    }
    if (space_icon == NULL) {
        space_icon = qp_load_image_mem(gfx_space);
    }
    if (shift_icon == NULL) {
        shift_icon = qp_load_image_mem(gfx_shift);
    }
    if (enter_icon == NULL) {
        enter_icon = qp_load_image_mem(gfx_enter);
    }
    if (lock_icon == NULL) {
        lock_icon = qp_load_image_mem(gfx_lock);
    }
    if (mute_icon == NULL) {
        mute_icon = qp_load_image_mem(gfx_mute);
    }
    if (volume_down_icon == NULL) {
        volume_down_icon = qp_load_image_mem(gfx_volume_down);
    }
    if (volume_up_icon == NULL) {
        volume_up_icon = qp_load_image_mem(gfx_volume_up);
    }
}

// Function to check if label is an icon and return the appropriate icon handle
static painter_image_handle_t get_icon_for_label(const char* label) {
    if (!label) return NULL;

    // Check for common icon label variations
    if (strcmp(label, "BKSP") == 0 || strcmp(label, "BACKSPACE") == 0 || strcmp(label, "BSP") == 0) {
        return backspace_icon;
    }
    if (strcmp(label, "TAB") == 0) {
        return tab_icon;
    }
    if (strcmp(label, "SPC") == 0 || strcmp(label, "SPACE") == 0) {
        return space_icon;
    }
    if (strcmp(label, "SHFT") == 0 || strcmp(label, "SHIFT") == 0 || strcmp(label, "SFT") == 0) {
        return shift_icon;
    }
    if (strcmp(label, "ENT") == 0 || strcmp(label, "ENTER") == 0 || strcmp(label, "RET") == 0) {
        return enter_icon;
    }
    if (strcmp(label, "LOCK") == 0) {
        return lock_icon;
    }
    if (strcmp(label, "VOL-") == 0) {
        return volume_down_icon;
    }
    if (strcmp(label, "VOL+") == 0) {
        return volume_up_icon;
    }

    return NULL;
}

// Function to draw a key label at the specified position
void draw_key_label(painter_device_t surface, int x, int y, int row, int col, const char* label, bool is_left_side) {
    (void)row; (void)col; (void)is_left_side;  // no longer used for colour
    // Initialize icons if needed
    init_icons();

    // Letter keys white, everything else (mods, layers, symbols) green.
    bool is_alpha = label && label[0] >= 'A' && label[0] <= 'Z' && label[1] == '\0';
    hsv_t hsv = is_alpha ? (hsv_t){HSV_ALPHA} : (hsv_t){HSV_MOD};

    // Check if this label should be drawn as an icon
    painter_image_handle_t icon = get_icon_for_label(label);
    if (icon != NULL) {
        // Calculate center position for the 16x16 icon within the 22x20 key square
        int icon_x = x + (square_width - 16) / 2;   // (22 - 16) / 2 = 3
        int icon_y = y + (square_height - 16) / 2;  // (20 - 16) / 2 = 2

        // Draw the icon with white color and black background
        qp_drawimage_recolor(surface, icon_x, icon_y, icon, hsv.h, hsv.s, 255, HSV_BLACK);
        return;
    }

    // If not an icon, draw as text (existing code)
    // Load font if not already loaded
    if (font_9x12_handle == NULL) {
        font_9x12_handle = qp_load_font_mem(font_9x12);
    }
    if (font_5x7_handle == NULL) {
        font_5x7_handle = qp_load_font_mem(font_5x7);
    }
    if (font_4x7_handle == NULL) {
        font_4x7_handle = qp_load_font_mem(font_4x7);
    }
    if (font_3x5_handle == NULL) {
        font_3x5_handle = qp_load_font_mem(font_3x5);
    }

    const painter_font_handle_t font_handle =
        (label && label[0] && !label[1]) ? font_9x12_handle : // 1 char
        (label && label[0] && label[1] && !label[2]) ? font_9x12_handle : // 2 chars
        (label && label[0] && label[1] && label[2] && !label[3]) ? font_5x7_handle : // 3 chars
        (label && label[0] && label[1] && label[2] && label[3] && !label[4]) ? font_4x7_handle : // 4 chars
        font_3x5_handle; // 5 or more chars

    // Calculate center position for the text within the key square
    int16_t text_width = qp_textwidth(font_handle, label);
    int16_t text_height = font_handle->line_height;

    // Center the text horizontally and vertically within the key square
    int text_x = x + (square_width - text_width) / 2;
    int text_y = y + (square_height - text_height) / 2 + 1;

    // Draw the text
    qp_drawtext_recolor(surface, text_x, text_y, font_handle, label, hsv.h, hsv.s, 255, HSV_BLACK);
}

// Function to draw a complete key (clear, label, border)
void draw_key(painter_device_t surface, int x, int y, int row, int col, const char* label, bool is_left_side) {
    // Clear the rectangle
    qp_rect(surface, x, y, x + square_width, y + square_height, HSV_BLACK, 1);

    // Draw the label
    draw_key_label(surface, x, y, row, col, label, is_left_side);

    // Draw the border
    qp_rect(surface, x, y, x + square_width, y + square_height, BORDER_COLOR, 0);
}

// Function to draw a 3x5 grid layout
void draw_layout_grid(painter_device_t surface, int x, int y, bool mirrored, const char* keymap[5][6]) {
    const int columns = 6;
    const int rows = 3;

    // For right side (mirrored = false), adjust the x offset to position correctly
    int x_offset = x;
    if (!mirrored) {
        // Right side should be positioned to show correct physical layout
        // Based on the layout, right side keys start at x=8.5, so we need to adjust
        x_offset = x + 2; // Adjust this value to position correctly
    }

    for (int col = 0; col < columns; col++) {
        int actual_col = mirrored ? (columns - 1 - col) : col;
        int col_x = x_offset + (actual_col * square_width);
        int col_y = y + offsets[col];

        for (int row = 0; row < rows; row++) {
            int square_y = col_y + (row * square_height);
            draw_key(surface, col_x, square_y, row, actual_col, keymap[row][actual_col], mirrored);
        }
    }

    // Thumb square buttons
    const int thumb_row_offset = 8;
    for (int col = 0; col < 2; col++) {
        int actual_col = mirrored ? (columns - 1 - col) : col; // Reverse order when mirrored
        int col_x = x_offset + (actual_col * square_width);
        for (int row = 0; row < 2; row++) {
            int square_y = y + rows * square_height + thumb_offsets[col] + (row * square_height) + thumb_row_offset;
            draw_key(surface, col_x, square_y, row + 3, actual_col, keymap[row + 3][actual_col], mirrored);
        }
    }

    // Rest of thumb buttons
    for (int col = 2; col < 5; col++) {
        int actual_col = mirrored ? (columns - 1 - col) : col; // Reverse order when mirrored
        int col_x = x_offset + (actual_col * square_width);
        int square_y = y + rows * square_height + thumb_offsets[col] + square_height + thumb_row_offset;
        draw_key(surface, col_x, square_y, 4, actual_col, keymap[4][actual_col], mirrored);
    }
}
