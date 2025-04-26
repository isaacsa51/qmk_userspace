#include QMK_KEYBOARD_H
#include "combos.h"
#include "../os_detection/os_layer.h"

const uint16_t PROGMEM copy_combo[] = {KC_W, KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {KC_X, KC_C, KC_D, COMBO_END};

// const uint16_t PROGMEM question_combo[] = {KC_N, KC_U, COMBO_END};
// const uint16_t PROGMEM equal_combo[] = {KC_S, KC_T, COMBO_END};
// const uint16_t PROGMEM combo_bracket_l[]  = {KC_W, KC_F, COMBO_END}; // [    
// const uint16_t PROGMEM combo_bracket_r[]  = {KC_F, KC_P, COMBO_END}; // ]
// const uint16_t PROGMEM combo_dash[]       = {KC_R, KC_S, COMBO_END}; // -
// const uint16_t PROGMEM combo_brace_l[]    = {KC_X, KC_C, COMBO_END}; // {
// const uint16_t PROGMEM combo_brace_r[]    = {KC_C, KC_D, COMBO_END}; // }
// const uint16_t PROGMEM combo_plus[]       = {KC_T, KC_G, COMBO_END}; // +
// const uint16_t PROGMEM combo_at[]         = {KC_W, KC_R, COMBO_END}; // @
// const uint16_t PROGMEM combo_underscore[] = {KC_S, KC_D, COMBO_END}; // _
// const uint16_t PROGMEM combo_paren_l[]    = {KC_L, KC_U, COMBO_END}; // (
// const uint16_t PROGMEM combo_paren_r[]    = {KC_U, KC_Y, COMBO_END}; // )
// const uint16_t PROGMEM combo_colon[]      = {KC_N, KC_E, COMBO_END}; // :
// const uint16_t PROGMEM combo_pipe[]       = {KC_M, KC_N, COMBO_END}; // |
// const uint16_t PROGMEM combo_lt[]         = {KC_H, KC_COMM, COMBO_END}; // <
// const uint16_t PROGMEM combo_gt[]         = {KC_COMM, KC_DOT, COMBO_END}; // >
// const uint16_t PROGMEM combo_quote[]      = {KC_E, KC_I, COMBO_END}; // "
// const uint16_t PROGMEM combo_asterisk[]   = {KC_U, KC_E, COMBO_END}; // asterisk
// const uint16_t PROGMEM combo_bslash[]     = {KC_E, KC_DOT, COMBO_END}; // inverted slash
// const uint16_t PROGMEM combo_caret[]      = {KC_J, KC_M, COMBO_END}; // ^
// const uint16_t PROGMEM combo_exclaim[]    = {KC_F, KC_T, COMBO_END}; // !
// const uint16_t PROGMEM combo_dollar[]     = {KC_T, KC_P, COMBO_END}; // $
// const uint16_t PROGMEM combo_hash[]       = {KC_F, KC_S, COMBO_END}; // #

// combo_t key_combos[] = {
//     COMBO(equal_combo, KC_EQUAL),           // =
//     COMBO(question_combo, LSFT(KC_SLASH)),  // ?
//     COMBO(combo_bracket_l,  KC_LBRC),  // [
//     COMBO(combo_bracket_r,  KC_RBRC),  // ]
//     COMBO(combo_dash,       KC_MINS),  // -
//     COMBO(combo_brace_l,    KC_LCBR),  // {
//     COMBO(combo_brace_r,    KC_RCBR),  // }
//     COMBO(combo_plus,       KC_PLUS),  // +
//     COMBO(combo_at,         KC_AT),    // @
//     COMBO(combo_underscore, KC_UNDS),  // _
//     COMBO(combo_paren_l,    KC_LPRN),  // (
//     COMBO(combo_paren_r,    KC_RPRN),  // )
//     COMBO(combo_colon,      KC_COLN),  // :
//     COMBO(combo_pipe,       KC_PIPE),  // |
//     COMBO(combo_lt,         KC_LT),    // <
//     COMBO(combo_gt,         KC_GT),    // >
//     COMBO(combo_quote,      KC_DQUO),  // "
//     COMBO(combo_asterisk,   KC_ASTR),  // asterisk
//     COMBO(combo_bslash,     KC_BSLS),  // inverted slash
//     COMBO(combo_caret,      KC_CIRC),  // ^
//     COMBO(combo_exclaim,    KC_EXLM),  // !
//     COMBO(combo_dollar,     KC_DLR),   // $
//     COMBO(combo_hash,       KC_HASH),  // #
//                 // [COMBO_COPY] = COMBO(copy_combo, COMBO_COPY),
//                 // [COMBO_PASTE] = COMBO(paste_combo, COMBO_PASTE),
//                 // [COMBO_CUT] = COMBO(cut_combo, COMBO_CUT),
// };

// void process_combo_event(uint16_t combo_index, bool pressed) {
//     if (!pressed) return;

//     switch (combo_index) {
//         case COMBO_COPY:
//             if (current_os == OS_MAC) {
//                 tap_code16(LGUI(KC_C));
//             } else {
//                 tap_code16(LCTL(KC_INS));
//             }
//             break;
//         case COMBO_PASTE:
//             if (current_os == OS_MAC) {
//                 tap_code16(LGUI(KC_V));
//             } else {
//                 tap_code16(LSFT(KC_INS));
//             }
//             break;
//         case COMBO_CUT:
//             if (current_os == OS_MAC) {
//                 tap_code16(LGUI(KC_X));
//             } else {
//                 tap_code16(LCTL(KC_X));
//             }
//             break;
//     }
// }
