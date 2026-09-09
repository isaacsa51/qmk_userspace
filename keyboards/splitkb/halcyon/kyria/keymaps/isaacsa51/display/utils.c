#include "utils.h"

void get_display_key_position(int keyboard_row, int keyboard_col, int *display_row, int *display_col, bool* is_right_side) {
    // Determine which side based on keyboard_row
    *is_right_side = (keyboard_row >= 5);

    // Reverse the final transformations from get_keyboard_key_position
    int temp_row = *is_right_side ? (keyboard_row - 5) : keyboard_row;
    int temp_col = *is_right_side ? (keyboard_col - 1) : (6 - keyboard_col);

    // Start with the basic mapping (reverse of the initial assignment)
    *display_row = temp_row;
    *display_col = temp_col;

    // Handle special thumb key cases in reverse
    if (*is_right_side) {
        // Reverse the thumb key mappings for right side
        if (temp_row == 2 && temp_col == -1) {
            *display_row = 3;
            *display_col = 0;
            return;
        }
        if (temp_row == 3 && temp_col == 2) {
            *display_row = 3;
            *display_col = 1;
            return;
        }
        if (temp_row == 3) {
            // Handle row 4 display mappings
            if (temp_col == -1) {
                *display_row = 4;
                *display_col = 0;
                return;
            }
            if (temp_col == 4) {
                *display_row = 4;
                *display_col = 1;
                return;
            }
            if (temp_col == 0) {
                *display_row = 4;
                *display_col = 2;
                return;
            }
            if (temp_col == 1) {
                *display_row = 4;
                *display_col = 3;
                return;
            }
            if (temp_col == 3) {
                *display_row = 4;
                *display_col = 4;
                return;
            }
        }
    } else {
        // Reverse the thumb key mappings for left side
        if (temp_row == 2 && temp_col == 6) {
            *display_row = 3;
            *display_col = 5;
            return;
        }
        if (temp_row == 3 && temp_col == 3) {
            *display_row = 3;
            *display_col = 4;
            return;
        }
        if (temp_row == 3) {
            // Handle row 4 display mappings
            if (temp_col == 2) {
                *display_row = 4;
                *display_col = 1;
                return;
            }
            if (temp_col == 4) {
                *display_row = 4;
                *display_col = 2;
                return;
            }
            if (temp_col == 5) {
                *display_row = 4;
                *display_col = 3;
                return;
            }
            if (temp_col == 1) {
                *display_row = 4;
                *display_col = 4;
                return;
            }
            if (temp_col == 6) {
                *display_row = 4;
                *display_col = 5;
                return;
            }
        }
    }
}

void get_keyboard_key_position(int display_row, int display_col, bool is_right_side, int *keyboard_row, int *keyboard_col) {
    *keyboard_col = display_col;
    *keyboard_row = display_row;

    // Thumb keys are in a weird order
    if (is_right_side) {
        if (display_row == 3) {
            if (display_col == 0) {
                *keyboard_row = 2;
                *keyboard_col = -1;
            }
            if (display_col == 1) {
                *keyboard_row = 3;
                *keyboard_col = 2;
            }
        }

        if (display_row == 4) {
            *keyboard_row = 3;
            switch (display_col) {
                case 0: *keyboard_col = -1; break;
                case 1: *keyboard_col = 4; break;
                case 2: *keyboard_col = 0; break;
                case 3: *keyboard_col = 1; break;
                case 4: *keyboard_col = 3; break;
            }
        }
    } else {
        if (display_row == 3) {
            if (display_col == 5) {
                *keyboard_row = 2;
                *keyboard_col = 6;
            }
            if (display_col == 4) {
                *keyboard_row = 3;
                *keyboard_col = 3;
            }
        }

        if (display_row == 4) {
            *keyboard_row = 3;
            switch (display_col) {
                case 1: *keyboard_col = 2; break;
                case 2: *keyboard_col = 4; break;
                case 3: *keyboard_col = 5; break;
                case 4: *keyboard_col = 1; break;
                case 5: *keyboard_col = 6; break;
            }
        }
    }

    // For the left side, reverse the column order
    *keyboard_col = is_right_side ? (*keyboard_col + 1) : (6 - *keyboard_col);
    *keyboard_row = is_right_side ? (*keyboard_row + 5) : *keyboard_row;
}
