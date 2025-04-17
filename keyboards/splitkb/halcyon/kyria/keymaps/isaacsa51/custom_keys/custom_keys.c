#include "quantum.h"
#include "custom_keys.h"
#include "../os_detection/os_layer.h"
#include "pointing_device.h"
#include "../layers.h"

static bool awaiting_smart_tilde = false;
static bool scrolling_enabled = false;
static bool ctrltab_sticky_active = false;

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

bool is_ignorable_key(uint16_t keycode) {
    switch (keycode) {
        case KC_TRNS:
        case KC_NO:
        case TT(_NAV):
        case TT(_SYM):
        case OSL(_GIT):
        case TG(_DROID):
            return true;
        default:
            return false;
    }
}

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        if (ctrltab_sticky_active && keycode != SWTCHR && record->event.pressed && !is_ignorable_key(keycode)){
            unregister_code(KC_LCTL);
            ctrltab_sticky_active = false;
        }

        switch (keycode) {
            case DRAG_S:
                scrolling_enabled = !scrolling_enabled;
                return false;

            case TILDE:
                awaiting_smart_tilde = true;
                return false;

            case TG_OS:
                current_os = (current_os == OS_MAC) ? OS_WIN : OS_MAC;
                return false;

            case CMD:
                register_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
                return false;

            case RUN:
                register_code(KC_LCTL); register_code(KC_LALT); tap_code(KC_R);
                unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case DEBUG:
                register_code(KC_LCTL); register_code(KC_LALT); tap_code(KC_D);
                unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case QCKACT:
                register_code(KC_LALT); tap_code(KC_ENT); unregister_code(KC_LALT);
                return false;

            case NEWFLE:
                register_code(KC_LCTL); register_code(KC_LALT); tap_code(KC_N);
                unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case PRETAB:
                register_code(KC_LCTL); register_code(KC_LSFT); tap_code(KC_LBRC);
                unregister_code(KC_LSFT); unregister_code(KC_LCTL);
                return false;

            case NXTAB:
                register_code(KC_LCTL); register_code(KC_LSFT); tap_code(KC_RBRC);
                unregister_code(KC_LSFT); unregister_code(KC_LCTL);
                return false;

            case FCLWN:
                register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_LSFT); tap_code(KC_PGDN);
                unregister_code(KC_LSFT); unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case FCRWN:
                register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_LSFT); tap_code(KC_PGUP);
                unregister_code(KC_LSFT); unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case BRKPNT:
                register_code(KC_LCTL); tap_code(KC_F8); unregister_code(KC_LCTL);
                return false;

            case GLDSYN:
                register_code(KC_LCTL); register_code(KC_LSFT); tap_code(KC_O);
                unregister_code(KC_LSFT); unregister_code(KC_LCTL);
                return false;

            case FIND:
                register_code(KC_LCTL); tap_code(KC_F); unregister_code(KC_LCTL);
                return false;

            case RPLCE:
                register_code(KC_LCTL); tap_code(KC_R); unregister_code(KC_LCTL);
                return false;

            case JUMP:
                register_code(KC_LCTL); tap_code(KC_SCLN); unregister_code(KC_LCTL);
                return false;

            case CLOSE:
                register_code(KC_LCTL); tap_code(KC_W); unregister_code(KC_LCTL);
                return false;

            case SWTCHR:
                register_code(KC_LCTL);     // Presiona Ctrl
                register_code(KC_TAB);           // Tab
                ctrltab_sticky_active = true;  // Activa el "sticky"
                return false;

            case IDENT:
                register_code(KC_LCTL); register_code(KC_LALT); tap_code(KC_I);
                unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case RFORMT:
                register_code(KC_LCTL); register_code(KC_LALT); tap_code(KC_L);
                unregister_code(KC_LALT); unregister_code(KC_LCTL);
                return false;

            case RFACTR:
                register_code(KC_LCTL); tap_code(KC_LALT); tap_code(KC_T); // TODO: Cambiar/investigar shortcut
                unregister_code(KC_LCTL);
                return false;

            case SEARCH:
                tap_code16(KC_LSFT); tap_code16(KC_LSFT); // Double shift
                return false;
        }
    } else {
        if (keycode == CMD) {
            unregister_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
            return false;
        }
    }

    if (awaiting_smart_tilde && record->event.pressed) {
        awaiting_smart_tilde = false;
    
        bool is_shift = get_mods() & MOD_MASK_SHIFT;
        bool is_caps = host_keyboard_led_state().caps_lock;
        bool is_upper = is_shift ^ is_caps;
    
        uint16_t base_kc = get_base_keycode(keycode);
    
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
