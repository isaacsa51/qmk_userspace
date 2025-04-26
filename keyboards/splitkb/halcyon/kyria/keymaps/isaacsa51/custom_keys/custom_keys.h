#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    TILDE,
    TG_OS,
    CMD,
    DRAG_S,
    DEL_LINE,
};

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record);

uint16_t get_base_keycode(uint16_t keycode);
