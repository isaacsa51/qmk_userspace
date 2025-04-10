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

    [ Passwords ]
     ¯¯¯¯¯¯¯¯¯¯
    - To unlock the keyboard type "ao". It will flash a purple notification to let you know that it is active.
      If you want to change the keyword, you can change it in before_key_handler to something like "me" or "hi"


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

enum layers {
    _ALPHA = 0,
    _CANARIA,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
    _NUM,
    _WM,
    _DROID,
};

enum custom_keycodes {
    TILDE,
    TG_OS,
    CMD,
    DRAG_S,
};

// Define OS from layers 
enum os_modes {
    OS_MAC,
    OS_WIN,
};

// Aliases for readability
#define ALPHA   DF(_ALPHA)
#define CANARIA DF(_CANARIA)

#define SYM      TT(_SYM)
#define NAV      TT(_NAV)
#define FKEYS    TT(_FUNCTION)
#define ADJUST   TT(_ADJUST)
#define NUM      MO(_NUM)
#define WM       MO(_WM)
#define DROID    MO(_DROID)

// Aliases for One Shot mods keys
#define OSHFT    OSM(MOD_LSFT)

const uint16_t PROGMEM question_combo[] = {KC_N, KC_U, COMBO_END};

combo_t key_combos[] = {
    COMBO(question_combo, LSFT(KC_SLASH)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | MOUSE|CapsLk|  |F-keys|      |   K  |   H  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Adjust| LGUI | LAlt | Space| Nav  |  | Sym  | Space| Enter| RGUI | Menu |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ALPHA] = LAYOUT_split_3x6_5_hlc(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_ESC,
        CMD ,     KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , TILDE,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , KC_LBRC,KC_CAPS,     FKEYS  ,      WM, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                    ADJUST, KC_LGUI, KC_LALT, KC_SPC , NAV   ,     SYM    , KC_BSPC,KC_ENTER,KC_RGUI, KC_APP,
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
 * | LShift |   Q  |   Z  |   V  |   D  |   K  | MOUSE|CapsLk|  |F-keys|      |   X  |   H  | ,  < | . >  | /  ? | TG_OS  |
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
    CMD ,     KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                        KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_C , TILDE,
    KC_LSFT , KC_Q ,  KC_Z   ,  KC_V  ,   KC_D ,   KC_K , KC_LBRC,KC_CAPS,     FKEYS  , _______, KC_X,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                ADJUST, KC_LGUI, KC_LALT, KC_SPC , NAV   ,     SYM    , KC_BSPC,KC_ENTER,KC_RGUI, KC_APP,
    KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |ScLck |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
    _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, KC_SCRL, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
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
 * Numbers Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |  7   |   8  |   9  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |  4   |   5  |   6  |  0   |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  1   |   2  |   3  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------' 
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
[_NUM] = LAYOUT_split_3x6_5_hlc(
    _______, _______,  KC_7  ,  KC_8  ,  KC_9  , _______,                                     _______, _______, _______, _______, _______, _______,
    _______, _______,  KC_4  ,  KC_5  ,  KC_6  ,   KC_0 ,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
    _______, _______,  KC_1  ,  KC_2  ,  KC_3  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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
 *   - W1, W2, WN... = Workspace number
 *   - FLOAT = Toggle floating window
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      | FCW ↑|      | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI |  Alt | Ctrl | Shift|      |                              |      | FCW ←| FCW ↓| FCW →| VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  W1  |  W2  |  W3  |  W4  |  W5  |      |      |  |      |      |  W6  |  W7  |  W8  |  W9  |  W10 |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      | FLOAT|      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_WM] = LAYOUT_split_3x6_5_hlc(
      _______, _______, _______, _______, _______, _______,                                     _______, _______   , A(KC_UP) ,   _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, A(KC_LEFT),A(KC_DOWN),A(KC_RGHT), _______, _______,
      _______, A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5), _______, _______, _______, _______, A(KC_6), A(KC_7)   , A(KC_8)  ,   A(KC_9), A(KC_0), _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,
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

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [5] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [6] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

bool awaiting_smart_tilde = false;
bool set_scrolling = false;
static uint8_t current_os = OS_WIN;
static uint8_t mod_state;

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
    
    if (keycode == DRAG_S && record->event.pressed) {
        set_scrolling = !set_scrolling;
    }
    return true;

    switch (keycode) {
        case TILDE:
            if (record->event.pressed) {
                awaiting_smart_tilde = true;
            }
            return false;

        case CMD:
            if (record->event.pressed) {
                if (current_os == OS_MAC) {
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (current_os == OS_MAC) {
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            return false;

        case KC_BSPC:
            if(record->event.pressed) {
                mod_state = get_mods() | get_oneshot_mods();
                
                bool shift = mod_state & MOD_MASK_SHIFT;
                bool cmd = mod_state & (MOD_LGUI | MOD_RGUI);

                del_mods(MOD_MASK_SHIFT | MOD_MASK_GUI);

                if (cmd && shift) {
                    // CMD + SHIFT + BSPC → Suprimir
                    tap_code(KC_DEL);
                } else if (cmd) {
                    // CMD + BSPC → Borrar palabra
                    if (current_os == OS_MAC) {
                        tap_code16(LALT(KC_BSPC));  // Opción + Backspace
                    } else {
                        tap_code16(LCTL(KC_BSPC)); // Ctrl + Backspace
                    }
                } else if (shift) {
                    // SHIFT + BSPC → Borrar línea
                    if (current_os == OS_MAC) {
                        // En Mac: CMD + Backspace → borrar línea
                        tap_code16(LGUI(KC_BSPC));
                    } else {
                        // En Linux/Win: Ctrl + U
                        tap_code16(LCTL(KC_U));
                    }
                } else {
                    // Solo BSPC
                    tap_code(KC_BSPC);
                }

                set_mods(mod_state);
                return false;
            }

        case TG_OS:
            if (record->event.pressed) {
                current_os = (current_os == OS_MAC) ? OS_WIN : OS_MAC;
            }
            return false;
    }

    if (awaiting_smart_tilde) {
        if (record->event.pressed) {
            awaiting_smart_tilde = false;

            // Detectar mayúsculas
            bool is_shift = get_mods() & MOD_MASK_SHIFT;
            bool is_caps = host_keyboard_led_state().caps_lock;
            bool is_upper = is_shift ^ is_caps;

            switch (keycode) {
                case KC_N:
                    // Enviar ñ (o Ñ si mayúscula)
                    if (current_os == OS_WIN) {
                        if (is_upper) {
                            // AltGr + Shift + N → Ñ
                            register_code(KC_RALT);
                            register_code(KC_LSFT);
                            tap_code(KC_N);
                            unregister_code(KC_LSFT);
                            unregister_code(KC_RALT);
                        } else {
                            // AltGr + n → ñ
                            register_code(KC_RALT);
                            tap_code(KC_N);
                            unregister_code(KC_RALT);
                        }
                    } else if (current_os == OS_MAC) {
                        // Option + E + N or Shift+N
                        register_code(KC_LALT);
                        tap_code(KC_E);
                        unregister_code(KC_LALT);
                        if (is_upper) {
                            register_code(KC_LSFT);
                            tap_code(KC_N);
                            unregister_code(KC_LSFT);
                        } else {
                            tap_code(KC_N);
                        }
                    }
                    return false;

                case KC_A: case KC_E: case KC_I: case KC_O: case KC_U:
                    // Tilde + vocal
                    if (current_os == OS_WIN) {
                        register_code(KC_RALT);
                        tap_code(KC_QUOTE); // ´
                        unregister_code(KC_RALT);
                        if (is_upper) register_code(KC_LSFT);
                        tap_code(keycode);
                        if (is_upper) unregister_code(KC_LSFT);
                    } else if (current_os == OS_MAC) {
                        register_code(KC_LALT);
                        tap_code(KC_E); // alt+e para ´
                        unregister_code(KC_LALT);
                        if (is_upper) register_code(KC_LSFT);
                        tap_code(keycode);
                        if (is_upper) unregister_code(KC_LSFT);
                    }
                    return false;

                case KC_G:
                    // diéresis + g
                    if (is_upper) tap_code(KC_G); else tap_code(KC_G);

                    if (current_os == OS_MAC) {
                        register_code(KC_LALT);
                        tap_code(KC_U); // Option + u = ¨
                        unregister_code(KC_LALT);
                        tap_code(KC_SPC); // En mac, luego espacio
                    } else {
                        register_code(KC_RALT);
                        tap_code(KC_QUOT); // AltGr + "
                        unregister_code(KC_RALT);
                    }
                    return false;

                case KC_S: case KC_L: case KC_M: case KC_D:
                case KC_R: case KC_T: case KC_C:
                    // Apóstrofe inglés + letra
                    tap_code(KC_QUOTE);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(keycode);
                    if (is_upper) unregister_code(KC_LSFT);
                    return false;

                default:
                    // Comportamiento por defecto: manda '
                    tap_code(KC_QUOTE);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(keycode);
                    if (is_upper) unregister_code(KC_LSFT);
                    return false;
            }
        }
    }
    
    return true;
}
