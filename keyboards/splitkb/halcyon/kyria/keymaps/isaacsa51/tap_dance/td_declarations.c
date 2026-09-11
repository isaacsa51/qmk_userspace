#include "td_declarations.h"
#include "caps_word.h"
#include "../os_detection/os_layer.h"
#include "../custom_keys/custom_keys.h"
#include "../layers.h"

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