// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
        __  __      __                     
       / / / /___ _/ /______  ______  ____ 
      / /_/ / __ `/ / ___/ / / / __ \/ __ \
     / __  / /_/ / / /__/ /_/ / /_/ / / / /
    /_/ /_/\__,_/_/\___/\__, /\____/_/ /_/ 
        __ __          /____/              
       / //_/_  _______(_)___ _            
      / ,< / / / / ___/ / __ `/            
     / /| / /_/ / /  / / /_/ /             
    /_/ |_\__, /_/  /_/\__,_/              
         /____/                            

    Halcyon Kyria from SplitKB.com (created by Isaac Serrano)
    =====================================================

    [ Features ]
     ¯¯¯¯¯¯¯¯¯¯
    - Target user: spanish software developer using a Windows computer with a MacOS as working laptop
    - Shotcuts are OS independent, which means they are translated into different key combinations
      according to the selected OS mode (Windows by default).
    - Custom per-key RGB themes and notifications. Online theme editor: https://codepen.io/alvaro-prieto/full/gOLrwKm
    - Modifier keys can behave as modifiers (if they are operated in conjunction with other keys),
      or as normal keys (if they are pressed independently).
    - Support for Os dependent key outputs, key sequences, unicode, and more.
    - Some keys has been moved from their usual location to improve accessibility and ergonomics
    - Hyper key. This key has been created to allow custom shortcuts depending on the focused application.
      You can implement this kind of behaviour in programs such as Kanata.
    - Advanced Tap Dance: some keys behave differently, based on the amount of times that they have been tapped. Added
      compatibility for OS dependent key combinations, sequences, instant TD, extended uint16_t keycodes, and more.
    - Official Tap Dance source code has been fixed to allow multiple tap dances in a row without interruption issues.
    - A visual keymap APP has been created as reminder, using meaningful symbols and colors.


    [ Hardware ]
     ¯¯¯¯¯¯¯¯¯¯
    - Developed for Halcyon Kyria Rev. 4 (Screen + Cirque Trackpad)

    [ Todo ]
     ¯¯¯¯¯¯¯¯¯¯
    - Add rgb lighting depending on the current layer.



    [ Settings ]
     ¯¯¯¯¯¯¯¯¯¯
    - Check notes.txt in order to apply some minor modifications to your QMK if you want to compile this source.
    - QMK version keymap was released at April 4, 2025.
    - Check config.h for required keyboard ID specification to mimic a real Apple keyboard
    - Some modifications where made to Tap Dance source code and and rgb matrix state. Read notes.txt for further info
    - Some shortcuts have not an equivalence in different OS.
    - In macOS settings -> keyboard. Disable: "Use F1, F2 , etc. keys as standard function keys"
    - In macOS, window management is managed using AeroSpace, a tiling WM
    - In Windows, same as MacOS, window management is managed by GlazeWM.
    - This keyboard is pretending to be used using the keyboard layout of: English (US - International)
    - Some shortcuts / outputs, might require third party software.

    [ External software dependent features ]
     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
    - Per-app hyper shortcuts
    - Split screen features in macOs
    - Lines (key output)
    - Moving APP to certain desktop

   [ Dev tips ]
    ¯¯¯¯¯¯¯¯¯¯
    - If you are modifying this keymap and your keyboard doesn't output anything, probably you are running out
      of 'RAM' (Data Space). If so, try to move your data to Program Space using PROGMEM, or just add less stuff

    - During develpment, it is recomended to turn off: RGB_MATRIX_ENABLE=no  RGB_MATRIX_CUSTOM_USER=no in rules.mk
      to save some memory, and disable NO_DEBUG in config.h to be able to trace the code.
*/

#include QMK_KEYBOARD_H
#include "custom_keys/custom_keys.h"
#include "combos/combos.h"
#include "os_detection/os_layer.h"

enum layers {
    _ALPHA = 0,
    _CANARIA,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _WM,
    _DROID,
};

// Aliases for readability
#define ALPHA   DF(_ALPHA)
#define CANARIA DF(_CANARIA)

#define SYM      TT(_SYM)
#define NAV      TT(_NAV)
#define FKEYS    TT(_FUNCTION)
#define ADJUST   TT(_ADJUST)
#define WM       TT(_WM)
#define DROID    TT(_DROID)

// Homerow mods
#define HM_A LCTL_T(KC_A)
#define HM_R LALT_T(KC_R)
#define HM_S LGUI_T(KC_S)
#define HM_T LSFT_T(KC_T)
#define HM_N LSFT_T(KC_N)
#define HM_E LGUI_T(KC_E)
#define HM_I LALT_T(KC_I)
#define HM_O LCTL_T(KC_O)

// Aliases for One Shot mods keys
#define OSHFT    OSM(MOD_LSFT)

// TODO: Migrate these combos to combos.c
const uint16_t PROGMEM question_combo[] = {HM_N, KC_U, COMBO_END};
const uint16_t PROGMEM equal_combo[] = {HM_S, HM_T, COMBO_END};
const uint16_t PROGMEM combo_dash[] = {HM_R, HM_S, COMBO_END};
const uint16_t PROGMEM combo_colon[] = {HM_N, HM_E, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_M, HM_N, COMBO_END};
const uint16_t PROGMEM combo_quote[] = {HM_E, HM_I, COMBO_END};
const uint16_t PROGMEM combo_asterisk[] = {KC_U, HM_E, COMBO_END};
const uint16_t PROGMEM combo_bslash[] = {HM_E, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_exclaim[] = {KC_F, HM_T, COMBO_END};
const uint16_t PROGMEM combo_dollar[] = {HM_T, KC_P, COMBO_END};
const uint16_t PROGMEM combo_hash[] = {KC_F, HM_S, COMBO_END};
const uint16_t PROGMEM combo_bracket_l[]  = {KC_W, KC_F, COMBO_END}; 
const uint16_t PROGMEM combo_bracket_r[]  = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_brace_l[]    = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_brace_r[]    = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_plus[]       = {HM_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_at[]         = {KC_W, HM_R, COMBO_END};
const uint16_t PROGMEM combo_underscore[] = {HM_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_paren_l[]    = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_paren_r[]    = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_lt[]         = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_gt[]         = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_caret[]      = {KC_J, KC_M, COMBO_END};

combo_t key_combos[] = {
    COMBO(equal_combo, KC_EQUAL),           // =
    COMBO(question_combo, LSFT(KC_SLASH)),  // ?
    COMBO(combo_bracket_l,  KC_LBRC),  // [
    COMBO(combo_bracket_r,  KC_RBRC),  // ]
    COMBO(combo_dash,       KC_MINS),  // -
    COMBO(combo_brace_l,    KC_LCBR),  // {
    COMBO(combo_brace_r,    KC_RCBR),  // }
    COMBO(combo_plus,       KC_PLUS),  // +
    COMBO(combo_at,         KC_AT),    // @
    COMBO(combo_underscore, KC_UNDS),  // _
    COMBO(combo_paren_l,    KC_LPRN),  // (
    COMBO(combo_paren_r,    KC_RPRN),  // )
    COMBO(combo_colon,      KC_COLN),  // :
    COMBO(combo_pipe,       KC_PIPE),  // |
    COMBO(combo_lt,         KC_LT),    // <
    COMBO(combo_gt,         KC_GT),    // >
    COMBO(combo_quote,      KC_DQUO),  // "
    COMBO(combo_asterisk,   KC_ASTR),  // asterisk
    COMBO(combo_bslash,     KC_BSLS),  // inverted slash
    COMBO(combo_caret,      KC_CIRC),  // ^
    COMBO(combo_exclaim,    KC_EXLM),  // !
    COMBO(combo_dollar,     KC_DLR),   // $
    COMBO(combo_hash,       KC_HASH),  // #
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * Homerow mods on: ARST NEIO 
 * In this order: CTRL, ALT, GUI, SHIFT
 * 
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | MOUSE|CapsLk|  |F-keys|  WM  |   K  |   H  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust|  WM  |  NAV | Space|AltSpc|  | Enter| Space|  SYM | RGUI | Menu |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ALPHA] = LAYOUT_split_3x6_5_hlc(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_ESC,
        CMD ,     HM_A ,  HM_R   ,  HM_S  ,   HM_T ,   KC_G ,                                        KC_M,   HM_N ,  HM_E ,   HM_I ,  HM_O , TILDE,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , DRAG_S ,KC_CAPS,     FKEYS  ,      WM, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                    ADJUST,    WM  ,   NAV  , KC_SPC ,A(KC_SPC),  KC_ENTER, KC_BSPC, SYM , KC_RGUI, KC_APP,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Second alpha layer: Canaria A-C Swapped - https://github.com/christoofar/canaria
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   W  |   L  |   Y  |   P  |   B  |                              |   F  |   J  |   O  |   U  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   C  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Q  |   Z  |   V  |   D  |   K  | MOUSE|CapsLk|  |F-keys|  WM  |   X  |   H  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt | Space| Nav  |  | Sym  | Space| Enter| RGUI | Menu |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_CANARIA] = LAYOUT_split_3x6_5_hlc(
    KC_TAB  , KC_W ,  KC_L   ,  KC_Y  ,   KC_P ,   KC_B ,                                        KC_F,   KC_J ,  KC_O ,   KC_U ,KC_SCLN, KC_ESC,
    CMD ,     HM_A ,  HM_R   ,  HM_S  ,   HM_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_C , TILDE,
    KC_LSFT , KC_Q ,  KC_Z   ,  KC_V  ,   KC_D ,   KC_K , KC_LBRC,KC_CAPS,     FKEYS  ,   WM   , KC_X,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                ADJUST, KC_LGUI, KC_LALT, KC_SPC , NAV   ,     SYM    , KC_BSPC,KC_ENTER,KC_RGUI, KC_APP,
    KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Nav Layer: Media, number & navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  7   |   8  |   9  |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  4   |   5  |   6  |  0   |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  1   |   2  |   3  |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
    _______, _______,  KC_7  ,  KC_8  ,  KC_9  , _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
    _______, _______,  KC_4  ,  KC_5  ,  KC_6  ,   KC_0 ,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
    _______, _______,  KC_1  ,  KC_2  ,  KC_3  , _______, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,_______,_______,                                                _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Just symbols, some of them are excluded or barely used bc of combos...
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  &   |  $   |  [   |  ]   |  %   |                              |      |  "   |  <   |  >   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  (   |  )   |  |   |                              |   ^  |  -   |  *   |  :   |  #   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   \  |  `   |  {   |  }   |  +   |      |      |  |      |      |      |  _   |  ,   |  .   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_SYM] = LAYOUT_split_3x6_5_hlc(
    _______ , KC_AMPR, KC_DLR , KC_LBRC, KC_RBRC, KC_PERC,                                     _______,  KC_DQT, KC_LABK, KC_RABK, _______, _______,
    KC_TILD , KC_EXLM,  KC_AT , KC_LPRN, KC_RPRN, KC_PIPE,                                     KC_CIRC, KC_MINS, KC_ASTR, KC_COLN, KC_HASH, _______,
    _______ , KC_BSLS, KC_GRV , KC_LCBR, KC_RCBR, KC_PLUS, _______, _______, _______, _______, _______, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_FUNCTION] = LAYOUT_split_3x6_5_hlc(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |ALPHA |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |CANARI|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ADJUST] = LAYOUT_split_3x6_5_hlc(
    _______, _______, _______, ALPHA  , _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, CANARIA, _______, _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
    _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                               _______, _______, _______,_______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______,                                                      _______, _______, _______, _______, _______
    ),

/*
 * Windown Manager: Tiling window manager shortcuts for AeroSpace and GlazeWM.
 * Notes: Mostly actions are done using Shift key, that's why there's is a One Shot Shift on thumb cluster and one normal in case of needing one...
 * Declarations:
 *   - W1, W2, WN...: Workspace number = Alt+N
 *   - FLOAT: Toggle floating window = Alt+Shift+Space
 *   - DIRE: Change tiling direction = Alt+v
 *   - ICW/DCW: Decrease/Increase window width = Alt+U / Alt+P
 *   - ICH/DCH: ...               windows height = Alt+I / Alt+O
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      | FCW ↑|      | DCW  |  ICW   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | DIRE | FCW ←| FCW ↓| FCW →| DCH  |  ICH   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  W1  |  W2  |  W3  |  W4  |  W5  |      |      |  |      |      |  W6  |  W7  |  W8  |  W9  |  W10 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      | FLOAT| SHIFT|  |      | OSHFT|      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_WM] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, _______, _______, _______,                                     _______, _______   , A(KC_UP) ,   _______, A(KC_U), A(KC_P),
      _______, _______, _______, _______, _______, _______,                                     A(KC_V), A(KC_LEFT),A(KC_DOWN),A(KC_RGHT), A(KC_I), A(KC_O),
      _______, A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5), _______, _______, _______, _______, A(KC_6), A(KC_7)   , A(KC_8)  ,   A(KC_9), A(KC_0), _______,
                                 _______, _______,LSA_T(KC_SPC),KC_LSFT,    _______, _______, OSHFT  , _______,    _______,   _______,
      _______, _______, _______, _______, _______,                                                       _______,    _______, _______, _______, _______
    ),

/*
 * Android/IntelliJ: Basic shortcouts for JetBrains IDE using Mac for all plugin to match macOS and Windows shortcuts 
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_DROID] = LAYOUT_split_3x6_5_hlc(
    _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

    _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
  ),
};

bool awaiting_smart_tilde = false;
bool set_scrolling = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user_custom(keycode, record)) return false;
    return true;
}