#pragma once
#include QMK_KEYBOARD_H

enum custom_keycodes {
    TILDE,
    TG_OS,
    CMD,
    DRAG_S,
    DEL_LINE,

    GIT = SAFE_RANGE,    // One-shot layer for GIT actions

    // IntelliJ actions
    RUN,       // Ctrl+Alt+R
    DEBUG,     // Ctrl+Alt+D
    QCKACT,    // Alt+Enter
    NEWFLE,    // Ctrl+Alt+N
    PRETAB,    // Ctrl+Shift+[
    NXTAB,     // Ctrl+Shift+]
    FCLWN,     // Ctrl+Alt+Shift+Page Down
    FCRWN,     // Ctrl+Alt+Shift+Page Up
    BRKPNT,    // Ctrl+F8
    GLDSYN,    // Ctrl+Shift+O
    FIND,      // Ctrl+F
    RPLCE,     // Ctrl+R
    JUMP,      // Ctrl+;
    CLOSE,     // Ctrl+W
    SWTCHR,    // Ctrl+Tab
    IDENT,     // Ctrl+Alt+I
    RFORMT,    // Ctrl+Alt+L
    RFACTR,    // Refactor this (typically Ctrl+Alt+Shift+T or similar)
    SEARCH,    // Double Shift (can simulate with shift + tap shift quickly)
};

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record);

uint16_t get_base_keycode(uint16_t keycode);
