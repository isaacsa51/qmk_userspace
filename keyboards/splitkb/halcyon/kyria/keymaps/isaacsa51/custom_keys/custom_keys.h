#pragma once
#include QMK_KEYBOARD_H

enum {
    TD_MOUSE,
    TD_CMD_TILDE,
    TD_OSHTSF,
    TD_OSHTCT,
    TD_CAPS,
    TD_COUNT
};

enum custom_keycodes {
    TILDE = SAFE_RANGE,
    TG_OS,
    CMD,
    DRAG_S,
    DEL_LINE,

    GIT,    // One-shot layer for GIT actions

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
    RFACTR,    // Refactor this
    SEARCH     // Double Shift
};

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record);
uint16_t get_base_keycode(uint16_t keycode);