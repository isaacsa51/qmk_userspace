#include "quantum.h"
#include "../layers.h"
#include "../custom_keys/custom_keys.h"

// Combos resolve against _ALPHA (layer 0) regardless of the active layer
// (COMBO_ONLY_FROM_LAYER in config.h), gated to the alpha layers below by
// combo_should_trigger(). HM_* are the home-row mod-tap aliases from layers.h;
// combo arrays must reference the exact same keycode as the _ALPHA layer to
// match on _CANARIA / _CRATE too.

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

// FancyWM desktop picker (_WMSEL) held for as long as the chord is held. Two
// activators: left bottom row Z+X+C+D -> pick with the RIGHT hand (numpad order);
// right bottom row H+,+.+/ -> pick with the LEFT hand (mirror-pair order).
// Same physical keys on _CANARIA / _CRATE (COMBO_ONLY_FROM_LAYER 0).
const uint16_t PROGMEM wmsel_combo_l[] = {KC_Z, KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM wmsel_combo_r[] = {KC_H, KC_COMM, KC_DOT, KC_SLSH, COMBO_END};

// _MOUSE: both mouse buttons at once -> middle click. COMBO_ONLY_FROM_LAYER 0
// resolves positions against _ALPHA, so this is the _ALPHA keycodes sitting under
// the _MOUSE MS_BTN1 / MS_BTN2 keys (top row R2 / R4). Gated to _MOUSE below.
const uint16_t PROGMEM mmb_combo[] = {KC_L, KC_Y, COMBO_END};

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
    COMBO(wmsel_combo_l, WM_SEL_L),       // Z+X+C+D -> hold picker, pick with right
    COMBO(wmsel_combo_r, WM_SEL_R),       // H+,+.+/ -> hold picker, pick with left
    COMBO(mmb_combo, MS_BTN3),            // _MOUSE: BTN1+BTN2 -> middle / wheel click
};

// With COMBO_ONLY_FROM_LAYER the combos fire on every layer; restrict them to
// the alpha layers so number/symbol rolls on NAV/SYM/etc. don't emit combos.
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    uint8_t layer = get_highest_layer(layer_state);
    // The middle-click combo lives on _MOUSE only.
    if (combo->keys == mmb_combo) return layer == _MOUSE;
    switch (layer) {
        case _ALPHA:
        case _CANARIA:
        case _CRATE:
            return true;
        default:
            return false;
    }
}

// The 4-key WM picker gestures need a wider window than the tight 2-key symbol
// combos — 4 keys can't realistically land within COMBO_TERM (30 ms).
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    if (combo->keys == wmsel_combo_l
        || combo->keys == wmsel_combo_r) return 80;
    return COMBO_TERM;
}
