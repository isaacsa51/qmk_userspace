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

    Halcyon Kyria from SplitKB.com (keymap by Isaac Serrano)
    =====================================================

    [ Features ]
     ¯¯¯¯¯¯¯¯¯¯
    - Target user: spanish software developer using a Windows computer with a MacOS as working laptop
    - Shortcuts are OS independent, which means they are translated into different key combinations
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
    - A visual keymap APP has been created as reminder, using meaningful symbols and colors.


    [ Hardware ]
     ¯¯¯¯¯¯¯¯¯¯
    - Developed for Halcyon Kyria Rev. 4 (Screen + Cirque Trackpad)

    [ Settings ]
     ¯¯¯¯¯¯¯¯¯¯
    - QMK version keymap was released at April 4, 2025.
    - Check config.h for required keyboard ID specification to mimic a real Apple keyboard
    - Some shortcuts have not an equivalence in different OS.
    - In macOS, window management is managed using AeroSpace, a tiling WM
    - In Windows, same as MacOS, window management is managed by FancyWM.
    - This keyboard is pretending to be used using the keyboard layout of: English (US - International)
    - Some shortcuts / outputs, might require third party software.

   [ Dev tips ]
    ¯¯¯¯¯¯¯¯¯¯
    - If you are modifying this keymap and your keyboard doesn't output anything, probably you are running out
      of 'RAM' (Data Space). If so, try to move your data to Program Space using PROGMEM, or just add less stuff

    - During develpment, it is recomended to turn off: RGB_MATRIX_ENABLE=no  RGB_MATRIX_CUSTOM_USER=no in rules.mk
      to save some memory, and disable NO_DEBUG in config.h to be able to trace the code.

  [ ToDo ]
   ¯¯¯¯¯¯
    - Add rgb lighting depending on the current layer.
    - Smart tilde (accents) assumes a US-International layout on both Windows and macOS.
      Only the n -> ñ path branches on OS (AltGr+n on Windows, dead ~ on macOS).
*/

#include QMK_KEYBOARD_H
#include "custom_keys/custom_keys.h"
#include "os_detection/os_layer.h"
#include "tap_dance/td_declarations.h"
#include "layers.h"

// Aliases for readability
#define ALPHA   DF(_ALPHA)
#define CANARIA DF(_CANARIA)
#define CRATE   DF(_CRATE)

#define SYM      TT(_SYM)
#define NAV      TT(_NAV)
#define FKEYS    TT(_FUNCTION)
#define ADJUST   TT(_ADJUST)
#define WM       TT(_WM)
#define GAME     TG(_GAME)
#define MOUSE    MO(_MOUSE)

// _CRATE / _CANARIA home row: different letters under the same fingers.
#define HC_C LALT_T(KC_C)   // pinky  -> Alt   (_CRATE left, _CANARIA right)
#define HC_A LSFT_T(KC_A)   // middle -> Shift (_CRATE left)
#define HC_U LALT_T(KC_U)   // pinky  -> Alt   (_CRATE right)

// Aliases for One Shot mods keys
#define OSHFT    OSM(MOD_LSFT)
#define OALT     OSM(MOD_LALT)
#define OCTRL    OSM(MOD_LCTL)

// Aliases for tap dance
#define TDCMD  TD(TD_CMD_TILDE)
#define CAPS   TD(TD_CAPS)

// _NAV right thumb: tap = one-shot mod (stacks), hold = held mod (engages on the
// next keypress). Custom keycodes, handled in custom_keys.c.
#define OSHTSF OS_SFT
#define OSHTCT OS_CTL

tap_dance_action_t tap_dance_actions[] = {
    [TD_CMD_TILDE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cmd_finished, dance_cmd_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * Homerow mods on: ARST NEIO
 * In this order (pinky..index): ALT, GUI, SHIFT, CTRL  (mirrored on the right)
 * 
 * Declaration:
 *    - CAPS: Tap dance (1 tap Caps word, 2 taps Caps Lock)
 *    - ALT: One shot at thumb level
 * 
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  |  ALT | CAPS |  |F-keys| SHIFT|   K  |   H  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |AltTab|  WM  |  NAV | Space|AltSpc|  | Enter|Bckspc|  SYM | MEH  |HYPER |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_ALPHA] = LAYOUT_split_3x6_5_hlc(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_ESC,
        TDCMD   , HM_A ,  HM_R   ,  HM_S  ,   HM_T ,   KC_G ,                                        KC_M,   HM_N ,  HM_E ,   HM_I ,  HM_O , TILDE,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , OALT   , CAPS    ,     FKEYS, OSHFT  , KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                     ALTTAB,   WM  ,   NAV  , KC_SPC ,A(KC_SPC),  KC_ENTER, KC_BSPC, SYM , KC_MEH ,KC_HYPR,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Second Alpha Layer: Crate, a custom spanish focused layout created by Isaac Serrano.
 *
 * Homerow mods on CRAT / NEIU (pinky..index: ALT, GUI, SHIFT, CTRL, mirrored right)
 *
 * Declaration:
 *    - CAPS: Tap dance (1 tap Caps word, 2 taps Caps Lock)
 *    - ALT: One shot at thumb level
 * 
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   W  |   Y  |   L  |   P  |   B  |                              |   J  |   F  |   O  |   K  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   C  |   R  |   A  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   U  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   X  |   Z  |   Q  |   D  |   V  |  ALT | CAPS |  |F-keys| SHIFT|   H  |   S  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |AltTab|  WM  |  NAV | Space|AltSpc|  | Enter|Bckspc|  SYM | MEH  |HYPER |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
  [_CRATE] = LAYOUT_split_3x6_5_hlc(
    KC_TAB  , KC_W ,  KC_Y   ,  KC_L  ,   KC_P ,   KC_B ,                                        KC_J,   KC_F ,  KC_O ,   KC_K ,KC_SCLN, KC_ESC,
    TDCMD   , HC_C ,  HM_R   ,  HC_A  ,   HM_T ,   KC_G ,                                        KC_M,   HM_N ,  HM_E ,   HM_I ,  HC_U , TILDE,
    KC_LSFT , KC_X ,  KC_Z   ,  KC_Q  ,   KC_D ,   KC_V , OALT   , CAPS    ,     FKEYS, OSHFT  , KC_H,   KC_S ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                 ALTTAB,   WM  ,   NAV  , KC_SPC ,A(KC_SPC),  KC_ENTER, KC_BSPC, SYM , KC_MEH ,KC_HYPR,
    KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
  ),

/*
 * Third alpha layer: Canaria A-C Swapped - https://github.com/christoofar/canaria
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TAB   |   W  |   L  |   Y  |   P  |   B  |                              |   F  |   J  |   O  |   U  | ;  : |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CMD   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   C  | TILDE  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Q  |   Z  |   V  |   D  |   K  |  ALT |CapsLk|  |F-keys|  WM  |   X  |   H  | ,  < | . >  | /  ? | TG_OS  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |AltTab|  WM  |  NAV | Space|AltSpc|  | Enter|Bckspc|  SYM | MEH  | HYPER|
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * | MUTE | ____ | _____ | ____ | ____ |                                              | MUTE | ____ | _____ | ____ | ____ |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_CANARIA] = LAYOUT_split_3x6_5_hlc(
    KC_TAB  , KC_W ,  KC_L   ,  KC_Y  ,   KC_P ,   KC_B ,                                        KC_F,   KC_J ,  KC_O ,   KC_U ,KC_SCLN, KC_ESC,
    TDCMD   , HM_A ,  HM_R   ,  HM_S  ,   HM_T ,   KC_G ,                                        KC_M,   HM_N ,  HM_E ,   HM_I ,  HC_C , TILDE,
    KC_LSFT , KC_Q ,  KC_Z   ,  KC_V  ,   KC_D ,   KC_K ,   OALT , CAPS   ,   FKEYS  ,    OSHFT , KC_X,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, TG_OS,
                                 ALTTAB,   WM  ,   NAV  , KC_SPC ,A(KC_SPC),  KC_ENTER, KC_BSPC, SYM , KC_MEH ,KC_HYPR,
    KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Nav Layer: Media, number & navigation
 *
 * Declarations:
 *    - OSHTSF / OSHTCT: tap = one-shot (Shift / Ctrl, stackable); hold = held mod
 *      that engages on the next keypress (no tapping-term wait).
 *    - W< / W>: word left / right — Ctrl+arrow (Windows) / Alt+arrow (macOS). OSHTSF first = word select.
 *    - Left cluster is OS-aware: DelLn / DelWrd / real Bkspc / Cut / Copy / Paste.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | DelLn  |DelWrd|  7   |   8  |   9  |      |                              | PgUp |  W<  |   ↑  |  W>  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | Bkspc  |Paste |  4   |   5  |   6  |  0   |                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  Cut   | Copy |  1   |   2  |   3  |SELWRD|      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      | XXXX |      |      |  |OSHTCT| Bksp |OSHTSF|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 * ,-----------------------------------.                                              ,-----------------------------------.
 * |      |      |       |      |      |                                              |      |      |       |      |      |
 * `-----------------------------------'                                              `-----------------------------------'
 */
    [_NAV] = LAYOUT_split_3x6_5_hlc(
    U_DLINE, U_DWORD,  KC_7  ,  KC_8  ,  KC_9  , _______,                                     KC_PGUP, U_WORDL, KC_UP,   U_WORDR, KC_VOLU, KC_DEL,
    KC_BSPC, U_PASTE,  KC_4  ,  KC_5  ,  KC_6  ,   KC_0 ,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
    U_CUT  , U_COPY ,  KC_1  ,  KC_2  ,  KC_3  , SELWORD, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                               _______, _______, _______, _______, _______, OSHTCT , MOUSE  , OSHTSF , _______, _______,
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
 *                        |      |      |      |      |      |  |      |      | XXXX |      |      |
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
                                _______, _______, _______, _______  , _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI | ADJUST |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  | XXXX |      |      |      |      |      |      |        |
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
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, ADJUST ,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, ADJUST , _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |ALPHA |CANARI|CRATE | GAME |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
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
    _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
    _______, ALPHA  , CANARIA, CRATE  , GAME   , _______,                                    RM_TOGG, RM_SATU, RM_HUEU, RM_VALU, RM_NEXT, _______,
    _______, _______, _______, _______, _______, _______,_______, _______, _______, _______, _______, RM_SATD, RM_HUED, RM_VALD, RM_PREV, _______,
                               _______, _______, _______,_______, _______, _______, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______,                                                      _______, _______, _______, _______, _______
    ),

/*
 * Windows Manager: FancyWM (https://github.com/FancyWM/fancywm), a Windows tiling WM.
 *
 * How a key fires: fancywm() (custom_keys.c) drops every held mod, taps FancyWM's
 * two-key activation chord (Alt+Win — set the same in FancyWM's settings), waits
 * ~30 ms for its modal to arm, then taps one secondary key. So each key below =
 * "enter FancyWM command mode, then press X".
 *
 * Held mode keys (right thumb) re-purpose the direction + desktop keys:
 *   MOV  WM_MOVE  hold: L/R/U/D now MOVE the focused window; D1..D9 / D< / D>
 *                 now SEND the window to that desktop (instead of just switching)
 *   SWP  WM_SWAP  hold: L/R/U/D now SWAP the focused window with its neighbour
 *
 * Keyword glossary  —  label (on the TFT) : keycode : what it does in FancyWM
 *   <  >  ^  v : WM_L/R/U/D : move keyboard FOCUS to the tiled window in that
 *               direction  (or move / swap it, per the held mode above)
 *   D1..D9    : WM_1..WM_9  : switch to virtual desktop 1..9
 *   D<  /  D> : WM_DL / WM_DR : switch to the virtual desktop left / right of here
 *   D~        : WM_DPRV     : jump back to the previously-focused virtual desktop
 *   PNH       : WM_PANH     : wrap the focused window in a new HORIZONTAL panel
 *   PNV       : WM_PANV     : ... a new VERTICAL panel
 *   PNS       : WM_PANS     : ... a new STACK panel (one window shown, rest hidden)
 *   FLT       : WM_FLOAT    : toggle the focused window between tiled and floating
 *   PRO       : WM_PROMO    : promote the focused window to the main / largest pane
 *   RFR       : WM_REFR     : re-run the tiling layout on the current workspace
 *   TGL       : WM_TOGL     : turn the FancyWM tiling manager on / off entirely
 *   DSK       : WM_SHDSK    : "show desktop" — minimise / restore all windows
 *   ESC       : WM_CANC     : cancel the pending command, dismiss the FancyWM modal
 *   WM        : TT(_WM)     : this layer's key (tap = lock the layer, hold = momentary)
 *   BASE      : TO(_ALPHA)  : hard exit straight back to the base alpha layer
 *
 * Every non-WM key on this layer is KC_NO (not transparent) so no ambient mod
 * (HYPER / MEH / OALT / home-row) can leak into the Alt+Win activation chord.
 *
 * D1..D9 follow the _NAV numpad (7 8 9 / 4 5 6 / 1 2 3, top to bottom).
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  TGL   | RFR  |  D7  |  D8  |  D9  |  D~  |                              | PNH  | PNV  |   ^  | PNS  |  DSK  |  ESC   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  FLT   |  D<  |  D4  |  D5  |  D6  |  D>  |                              |      |  <   |   v  |   >  |      |  PRO   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | BASE   |      |  D1  |  D2  |  D3  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  WM  |      |      |      |  | SWP  | MOV  |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_WM] = LAYOUT_split_3x6_5_hlc(
      WM_TOGL , WM_REFR, WM_7  , WM_8  , WM_9  , WM_DPRV,                                     WM_PANH, WM_PANV, WM_U  , WM_PANS, WM_SHDSK, WM_CANC ,
      WM_FLOAT, WM_DL  , WM_4  , WM_5  , WM_6  , WM_DR  ,                                     KC_NO  , WM_L   , WM_D  , WM_R  , KC_NO   , WM_PROMO,
      TO(_ALPHA), KC_NO, WM_1  , WM_2  , WM_3  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO , KC_NO , KC_NO   , KC_NO   ,
                                 KC_NO  , WM     , KC_NO  , KC_NO  , KC_NO  , WM_SWAP, WM_MOVE, KC_NO  , KC_NO  , KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Game Layer: left-hand QWERTY block for FPS games. Toggle on/off with GAME (on _ADJUST,
 * and on this layer's right inner thumb). Right hand and unused keys are KC_NO so no
 * homerow mods / tap dances / combos can fire mid-game.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              | XXXX | XXXX | XXXX | XXXX | XXXX |  Bksp  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |                              | XXXX | XXXX | XXXX | XXXX | XXXX | Enter  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  | LAlt |Space |  | GAME | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |  Esc   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GAME | XXXX |Space |Space |Space |  | XXXX | XXXX | XXXX | XXXX | XXXX |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT_split_3x6_5_hlc(
    KC_TAB , KC_Q , KC_W , KC_E , KC_R , KC_T ,                                        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
    KC_LCTL, KC_A , KC_S , KC_D , KC_F , KC_G ,                                        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ENT ,
    KC_LSFT, KC_Z , KC_X , KC_C , KC_V , KC_B , KC_LALT, KC_SPC ,     GAME , KC_NO   , KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_ESC ,
                                 GAME , KC_NO, KC_SPC , KC_SPC , KC_SPC ,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),

/*
 * Mouse Layer: held from _NAV (middle-right thumb, where WMOD used to be).
 * Left hand = scroll wheel, right hand = pointer move — both an inverted-T
 * mirroring the _NAV arrow cluster. Left / right click sit above pointer-left /
 * pointer-right (the U_WORDL / U_WORDR slots on _NAV).
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |ScrlUp|      |      |                              |      | LMB  | MsUp | RMB  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |ScrlR |ScrlDn|ScrlL |      |                              |      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      | held |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MOUSE] = LAYOUT_split_3x6_5_hlc(
    _______, _______, _______, MS_WHLU, _______, _______,                                     _______, MS_BTN1, MS_UP  , MS_BTN2, _______, _______,
    _______, _______, MS_WHLR, MS_WHLD, MS_WHLL, _______,                                     _______, MS_LEFT, MS_DOWN, MS_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

/*
 * WM desktop picker: held via a 4-key combo from an alpha layer, for as long as
 * the chord is held. Two ways in, and you pick with whichever hand is free:
 *   hold Z+X+C+D (left bottom)  -> pick with the RIGHT hand, numpad order
 *   hold H+,+.+/ (right bottom) -> pick with the LEFT hand, mirror-pair order
 * Tap that hand's inner thumb (one-shot Shift) first -> MOVE the focused window
 * to the desktop instead of switching (FancyWM Shift+N). RGB lights only the
 * side in play (held cluster white, desktops green, Shift blue).
 *
 *   right (numpad)    left (mirror pairs)
 *     D7 D8 D9           home:  A R S T G -> D8 D7 D6 D5 D9
 *     D4 D5 D6           bot :  Z X C D   -> D4 D3 D2 D1
 *     D1 D2 D3
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |  D7  |  D8  |  D9  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  D8  |  D7  |  D6  |  D5  |  D9  |                              |      |  D4  |  D5  |  D6  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  D4  |  D3  |  D2  |  D1  |      |      |      |  |      |      |      |  D1  |  D2  |  D3  |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      | OSSf |  | OSSf |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_WMSEL] = LAYOUT_split_3x6_5_hlc(
    _______, _______, _______, _______, _______, _______,                                     _______, WM_7   , WM_8   , WM_9   , _______, _______,
    _______, WM_8   , WM_7   , WM_6   , WM_5   , WM_9   ,                                     _______, WM_4   , WM_5   , WM_6   , _______, _______,
    _______, WM_4   , WM_3   , WM_2   , WM_1   , _______, _______, _______, _______, _______, _______, WM_1   , WM_2   , WM_3   , _______, _______,
                               _______, _______, _______, _______, OSHFT  , OSHFT  , _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user_custom(keycode, record)) return false;
    return true;
}

void keyboard_post_init_user(void) {
    os_layer_init();  // restore the persisted mac/win mode
#ifdef RGB_MATRIX_ENABLE
    // Force PaletteFx Reactive + Polarized palette on every plug-in — the EEPROM
    // usually holds a stale mode, so RGB_MATRIX_DEFAULT_* alone never takes.
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_PALETTEFX_REACTIVE);
    rgb_matrix_sethsv_noeeprom(RGB_MATRIX_HUE_STEP * 9, 255, rgb_matrix_get_val());
#endif
}