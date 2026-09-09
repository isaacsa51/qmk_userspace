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
        smart_tilde_timer = timer_read32();
    }
}

void dance_cmd_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
    }
}

void oshtsf_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      // One-shot Shift: applies to the next key press (add_ so OSHTSF + OSHTCT stack)
      add_oneshot_mods(MOD_BIT(KC_LSFT));
    } else if (state->count == 2) {
      // Hold Shift until released
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
      // One-shot Ctrl: applies to the next key press
      add_oneshot_mods(MOD_BIT(KC_LCTL));
    } else if (state->count == 2) {
      // Hold Ctrl until released
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
        tap_code(KC_CAPS);          // Caps Lock
        rgb_notify(255, 0, 0, 3);   // flash red
    } else if (state->count == 2) {
        caps_word_on();             // Caps Word (caps_word_set_user flashes red)
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    
}