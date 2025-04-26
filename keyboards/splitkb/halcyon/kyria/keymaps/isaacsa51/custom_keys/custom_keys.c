#include "quantum.h"
#include "custom_keys.h"
#include "../os_detection/os_layer.h"
#include "pointing_device.h"

static bool awaiting_smart_tilde = false;
static bool scrolling_enabled = false;

// Mapea los homerow mods a sus teclas base
uint16_t get_base_keycode(uint16_t keycode) {
    switch (keycode) {
        case LCTL_T(KC_A): return KC_A;
        case LALT_T(KC_R): return KC_R;
        case LGUI_T(KC_S): return KC_S;
        case LSFT_T(KC_T): return KC_T;
        case LSFT_T(KC_N): return KC_N;
        case LGUI_T(KC_E): return KC_E;
        case LALT_T(KC_I): return KC_I;
        case LCTL_T(KC_O): return KC_O;
        default: return keycode;
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_enabled) {
        report_mouse_t scroll = {};
        scroll.h = mouse_report.x;
        scroll.v = -mouse_report.y; // natural scroll
        return scroll;
    }
    return mouse_report;
}

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record) {

    if(keycode == DRAG_S && record->event.pressed) {
        scrolling_enabled = !scrolling_enabled;
        return false;
    }

    if (keycode == TILDE && record->event.pressed) {
        awaiting_smart_tilde = true;
        return false;
    }

    if (keycode == TG_OS && record->event.pressed) {
        current_os = (current_os == OS_MAC) ? OS_WIN : OS_MAC;
        return false;
    }

    if (keycode == CMD) {
        if (record->event.pressed) {
            register_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
        } else {
            unregister_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
        }
        return false;
    }

    if (awaiting_smart_tilde && record->event.pressed) {
        awaiting_smart_tilde = false;
    
        bool is_shift = get_mods() & MOD_MASK_SHIFT;
        bool is_caps = host_keyboard_led_state().caps_lock;
        bool is_upper = is_shift ^ is_caps;
    
        uint16_t base_kc = get_base_keycode(keycode); // 👈🏼 esto es clave
    
        switch (base_kc) {
            case KC_N:
                if (current_os == OS_WIN) {
                    if (is_upper) {
                        register_code(KC_RALT); register_code(KC_LSFT); tap_code(KC_N);
                        unregister_code(KC_LSFT); unregister_code(KC_RALT);
                    } else {
                        register_code(KC_RALT); tap_code(KC_N); unregister_code(KC_RALT);
                    }
                } else {
                    register_code(KC_LALT); tap_code(KC_E); unregister_code(KC_LALT);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(KC_N);
                    if (is_upper) unregister_code(KC_LSFT);
                }
                return false;
    
            case KC_A: case KC_E: case KC_I: case KC_O: case KC_U:
                if (current_os == OS_WIN) {
                    tap_code(KC_QUOTE);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(base_kc);
                    if (is_upper) unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LALT); tap_code(KC_E); unregister_code(KC_LALT);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(base_kc);
                    if (is_upper) unregister_code(KC_LSFT);
                }
                return false;
    
            default:
                // Comportamiento por defecto: manda '
                tap_code(KC_QUOTE);
                if (is_upper) register_code(KC_LSFT);
                tap_code(keycode);
                if (is_upper) unregister_code(KC_LSFT);
                return false;
                break;
        }
    }    

    return true;
}
