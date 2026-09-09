#pragma once
#include QMK_KEYBOARD_H

enum {
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

    // OS-aware editing (macOS / Windows)
    U_WORDL, U_WORDR,     // word left / right: Alt+arrow (mac) / Ctrl+arrow (win)
    U_DWORD, U_DLINE,     // delete word / delete line
    U_COPY, U_CUT, U_PASTE,
    ALTTAB,               // quick window switch: Cmd+Tab (mac) / Alt+Tab (win)

    // FancyWM (Windows) — each sends the Shift+Win activation chord, then a secondary
    WM_L, WM_R, WM_U, WM_D,        // direction: focus, or move/swap while WM_MOVE/WM_SWAP held
    WM_MOVE, WM_SWAP,              // held modes for the direction + desktop keys
    WM_PANH, WM_PANV, WM_PANS,     // create horizontal / vertical / stack panel
    WM_FLOAT,                      // toggle floating
    WM_PROMO,                      // pull window up (promote out of panel)
    WM_REFR,                       // refresh workspace
    WM_TOGL,                       // toggle the manager on/off (F11)
    WM_SHDSK,                      // show desktop
    WM_CANC,                       // cancel
    WM_DPRV, WM_DL, WM_DR,         // virtual desktop: previous / left / right
    WM_1, WM_2, WM_3, WM_4, WM_5, WM_6, WM_7, WM_8, WM_9,  // switch (or move-to while WM_MOVE)
};

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record);
uint16_t get_base_keycode(uint16_t keycode);

// Blink every LED <blinks> times in the given colour, then return to normal.
void rgb_notify(uint8_t r, uint8_t g, uint8_t b, uint8_t blinks);
