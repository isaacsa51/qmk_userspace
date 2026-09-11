#pragma once

enum layers {
    _ALPHA = 0,
    _CANARIA,
    _CRATE,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _WM,
    _GAME,
    _MOUSE,
    _WMSEL,
};

// Homerow mods — pinky..index: Alt, GUI, Shift, Ctrl (mirrored on the right hand).
// Shared with combos/combos.c, whose combo arrays must match these exact mod-tap
// keycodes to fire against the _ALPHA positions (COMBO_ONLY_FROM_LAYER 0).
#define HM_A LALT_T(KC_A)
#define HM_R LGUI_T(KC_R)
#define HM_S LSFT_T(KC_S)
#define HM_T LCTL_T(KC_T)
#define HM_N LCTL_T(KC_N)
#define HM_E LSFT_T(KC_E)
#define HM_I LGUI_T(KC_I)
#define HM_O LALT_T(KC_O)