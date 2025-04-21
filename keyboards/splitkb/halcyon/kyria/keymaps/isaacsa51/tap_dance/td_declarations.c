#include "td_declarations.h"
#include "caps_word.h"
#include "../os_detection/os_layer.h"
#include "../custom_keys/custom_keys.h"
#include "../layers.h"

typedef struct {
    bool is_hold;
} td_hold_state_t;
  
static td_hold_state_t td_shift_state = { .is_hold = false };
static td_hold_state_t td_ctrl_state = { .is_hold = false };

void dance_cmd_finished(tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
        register_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
    } else if (state->count == 2) {
        awaiting_smart_tilde = true;
    }
}

void dance_cmd_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
    }
}

void oshtsf_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      // One-shot Shift
      register_code(KC_LSFT);
      unregister_code(KC_LSFT);
    } else if (state->count == 2) {
      // Hold Shift
      register_code(KC_LSFT);
      td_shift_state.is_hold = true;
    }
}
  
void oshtsf_reset(tap_dance_state_t *state, void *user_data) {
    if (td_shift_state.is_hold) {
      unregister_code(KC_LSFT);
      td_shift_state.is_hold = false;
    }
}

void oshtct_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      // One-shot Ctrl
      register_code(KC_LCTL);
      unregister_code(KC_LCTL);
    } else if (state->count == 2) {
      // Hold Ctrl
      register_code(KC_LCTL);
      td_ctrl_state.is_hold = true;
    }
}
  
void oshtct_reset(tap_dance_state_t *state, void *user_data) {
    if (td_ctrl_state.is_hold) {
      unregister_code(KC_LCTL);
      td_ctrl_state.is_hold = false;
    }
}

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_CAPS); // Activa Caps Lock
    } else if (state->count == 2) {
        caps_word_on();    // Activa Caps Word
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    
}