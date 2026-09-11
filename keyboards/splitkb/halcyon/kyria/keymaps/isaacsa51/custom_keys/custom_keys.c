#include "quantum.h"
#include "pointing_device.h"
#include "custom_keys.h"
#include "../os_detection/os_layer.h"
#include "../layers.h"

#ifdef CHORDAL_HOLD
// Kyria matrix: rows 0-3 are the left half, 4-7 the right half.
char chordal_hold_handedness(keypos_t key) {
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}
#endif

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// A pending smart tilde is dropped if the next key doesn't arrive within this window
#define SMART_TILDE_TIMEOUT_MS 1000

// Variables to store accumulated scroll values
float scroll_left_accumulated_h = 0;
float scroll_left_accumulated_v = 0;
float scroll_right_accumulated_h = 0;
float scroll_right_accumulated_v = 0;

bool set_scrolling = false;
bool awaiting_smart_tilde = false;
uint32_t smart_tilde_timer = 0;

// ---- RGB notification flash ---------------------------------------------------
#define NOTIFY_PHASE_MS 110
static uint8_t  notify_r = 0, notify_g = 0, notify_b = 0;
static uint8_t  notify_blinks_left = 0;   // remaining "on" phases
static bool     notify_phase_on = false;
static uint32_t notify_phase_timer = 0;

void rgb_notify(uint8_t r, uint8_t g, uint8_t b, uint8_t blinks) {
    notify_r = r; notify_g = g; notify_b = b;
    notify_blinks_left = blinks;
    notify_phase_on = true;
    notify_phase_timer = timer_read32();
}

// Flash red whenever Caps Word turns on (from the tap dance or anywhere else).
void caps_word_set_user(bool active) {
    if (active) rgb_notify(255, 0, 0, 3);
}

// Homerow mods / mod-taps -> their tapped keycode (letter). Any mod-tap, any layer.
uint16_t get_base_keycode(uint16_t keycode) {
    return IS_QK_MOD_TAP(keycode) ? QK_MOD_TAP_GET_TAP_KEYCODE(keycode) : keycode;
}

// Tap the macOS or Windows variant of an editing shortcut depending on current_os.
static void tap_os(uint16_t mac_kc, uint16_t win_kc) {
    tap_code16(current_os == OS_MAC ? mac_kc : win_kc);
}

// FancyWM: tap the Alt+Win activation chord, wait for the modal to arm, then
// send the secondary keycode (which may carry its own modifier, e.g. C(KC_LEFT)).
#define FANCYWM_ACTIVATION_MS 30
static void fancywm(uint16_t secondary) {
    // Drop whatever is currently held (homerow mods, one-shots, HYPER/MEH from
    // transparent thumb keys, ...) so FancyWM sees a clean Alt+Win chord.
    uint8_t saved_mods = get_mods();
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
    send_keyboard_report();
    wait_ms(5);

    register_code(KC_LALT);
    register_code(KC_LGUI);
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    wait_ms(FANCYWM_ACTIVATION_MS);
    tap_code16(secondary);

    set_mods(saved_mods);
    send_keyboard_report();
}

// 0 = focus, 1 = move (Ctrl+dir), 2 = swap (Shift+dir). Set by WM_MOVE / WM_SWAP.
static uint8_t wm_mode = 0;

// _WMSEL: 0 = inactive, 1 = left cluster held (pick with the right hand),
// 2 = right cluster held (pick with the left). Set by WM_SEL_L / WM_SEL_R.
static uint8_t wmsel_side = 0;

// _NAV right-thumb OS_SFT / OS_CTL: *_down while the key is held, *_held once it
// has been promoted to a real modifier by another keypress.
static bool osmod_sft_down = false, osmod_sft_held = false;
static bool osmod_ctl_down = false, osmod_ctl_held = false;

static void wm_dir(uint16_t focus_kc, uint16_t move_kc, uint16_t swap_kc) {
    fancywm(wm_mode == 1 ? move_kc : wm_mode == 2 ? swap_kc : focus_kc);
}

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record) {

    // _NAV right-thumb mods: tap -> one-shot (stacks); hold -> real modifier the
    // instant another key is pressed (no tapping-term wait).
    if (keycode == OS_SFT || keycode == OS_CTL) {
        uint8_t kc    = (keycode == OS_SFT) ? KC_LSFT : KC_LCTL;
        bool   *down  = (keycode == OS_SFT) ? &osmod_sft_down : &osmod_ctl_down;
        bool   *held  = (keycode == OS_SFT) ? &osmod_sft_held : &osmod_ctl_held;
        if (record->event.pressed) {
            *down = true;
            *held = false;
        } else {
            *down = false;
            if (*held) { unregister_code(kc); *held = false; }
            else       { add_oneshot_mods(MOD_BIT(kc)); }
        }
        return false;
    }
    // Any other keypress while a thumb mod is held -> promote it to a real hold.
    if (record->event.pressed) {
        if (osmod_sft_down && !osmod_sft_held) { register_code(KC_LSFT); osmod_sft_held = true; }
        if (osmod_ctl_down && !osmod_ctl_held) { register_code(KC_LCTL); osmod_ctl_held = true; }
    }

    // FancyWM held modes: switch the direction / desktop keys to move or swap.
    if (keycode == WM_MOVE) { wm_mode = record->event.pressed ? 1 : 0; return false; }
    if (keycode == WM_SWAP) { wm_mode = record->event.pressed ? 2 : 0; return false; }

    // Z+X+C+D (left) or H+,+.+/ (right) combo -> hold the FancyWM desktop picker
    // (_WMSEL) while the chord is held. wmsel_side tells the RGB which hand holds
    // (1 = left cluster -> pick with the right, 2 = right cluster -> pick left).
    if (keycode == WM_SEL_L || keycode == WM_SEL_R) {
        if (record->event.pressed) {
            wmsel_side = (keycode == WM_SEL_L) ? 1 : 2;
            layer_on(_WMSEL);
        } else {
            wmsel_side = 0;
            layer_off(_WMSEL);
        }
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case TILDE:
                awaiting_smart_tilde = true;
                smart_tilde_timer = timer_read32();
                return false;

            case TG_OS:
                current_os = (current_os == OS_MAC) ? OS_WIN : OS_MAC;
                os_layer_save();            // persist across replug/reboot
                rgb_notify(0, 255, 0, 2);   // flash green twice on OS change
                return false;

            case CMD:
                register_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
                return false;

            case U_COPY:  tap_os(G(KC_C), C(KC_C));       return false;
            case U_CUT:   tap_os(G(KC_X), C(KC_X));       return false;
            case U_PASTE: tap_os(G(KC_V), C(KC_V));       return false;
            case U_DWORD: tap_os(A(KC_BSPC), C(KC_BSPC)); return false;  // opt+bksp / ctrl+bksp
            case U_WORDL: tap_os(A(KC_LEFT), C(KC_LEFT)); return false;  // word left
            case U_WORDR: tap_os(A(KC_RGHT), C(KC_RGHT)); return false;  // word right
            case ALTTAB:  tap_os(G(KC_TAB),  A(KC_TAB));  return false;  // cmd+tab / alt+tab

            case U_DLINE:
                if (current_os == OS_MAC) {
                    tap_code16(G(KC_BSPC));                              // delete to line start
                } else {
                    tap_code16(KC_HOME); tap_code16(S(KC_END)); tap_code16(KC_BSPC);
                }
                return false;

            // ---- FancyWM ------------------------------------------------------
            case WM_L: wm_dir(KC_LEFT,  C(KC_LEFT),  S(KC_LEFT));  return false;
            case WM_R: wm_dir(KC_RGHT,  C(KC_RGHT),  S(KC_RGHT));  return false;
            case WM_U: wm_dir(KC_UP,    C(KC_UP),    S(KC_UP));    return false;
            case WM_D: wm_dir(KC_DOWN,  C(KC_DOWN),  S(KC_DOWN));  return false;

            case WM_PANH:  fancywm(KC_H);   return false;
            case WM_PANV:  fancywm(KC_V);   return false;
            case WM_PANS:  fancywm(KC_S);   return false;
            case WM_FLOAT: fancywm(KC_F);   return false;
            case WM_PROMO: fancywm(KC_ENT); return false;
            case WM_REFR:  fancywm(KC_R);   return false;
            case WM_TOGL:  fancywm(KC_F11); return false;
            case WM_SHDSK: fancywm(KC_D);   return false;
            case WM_CANC:  fancywm(KC_ESC); return false;

            case WM_DPRV: fancywm(KC_Q); return false;
            case WM_DL:   fancywm(wm_mode == 1 ? S(KC_Z) : KC_Z); return false;
            case WM_DR:   fancywm(wm_mode == 1 ? S(KC_X) : KC_X); return false;

            case WM_1 ... WM_9: {
                // Move window instead of switching when WM_MOVE is held (wm_mode)
                // or Shift is active (the _WMSEL one-shot Shift) -> FancyWM Shift+N.
                bool move = wm_mode == 1
                            || ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT);
                uint16_t n = KC_1 + (keycode - WM_1);   // KC_1..KC_9 are consecutive
                fancywm(move ? (QK_LSFT | n) : n);
                return false;
            }
        }
    } else {
        if (keycode == CMD) {
            unregister_code(current_os == OS_MAC ? KC_LGUI : KC_LCTL);
            return false;
        }
    }

    if (awaiting_smart_tilde && record->event.pressed) {
        // Stale latch (TILDE pressed and then nothing): forget it, type normally.
        if (timer_elapsed32(smart_tilde_timer) > SMART_TILDE_TIMEOUT_MS) {
            awaiting_smart_tilde = false;
            return true;
        }

        // A modifier between TILDE and the target key (e.g. Shift for an uppercase
        // accent) passes through without consuming the pending accent.
        if (IS_MODIFIER_KEYCODE(keycode)) return true;

        awaiting_smart_tilde = false;

        bool is_shift = get_mods() & MOD_MASK_SHIFT;
        bool is_caps  = host_keyboard_led_state().caps_lock;
        bool is_upper = is_shift ^ is_caps;

        uint16_t base_kc = get_base_keycode(keycode);

        switch (base_kc) {
            case KC_N:  // ñ / Ñ
                if (current_os == OS_WIN) {
                    if (is_upper) {
                        register_code(KC_RALT); register_code(KC_LSFT); tap_code(KC_N);
                        unregister_code(KC_LSFT); unregister_code(KC_RALT);
                    } else {
                        register_code(KC_RALT); tap_code(KC_N); unregister_code(KC_RALT);
                    }
                } else {
                    register_code(KC_LSFT); tap_code(KC_GRV); unregister_code(KC_LSFT);
                    if (is_upper) register_code(KC_LSFT);
                    tap_code(KC_N);
                    if (is_upper) unregister_code(KC_LSFT);
                }
                return false;

            case KC_A: case KC_E: case KC_I: case KC_O: case KC_U:  // á é í ó ú
                tap_code(KC_QUOTE);                 // dead acute (US-International)
                if (is_upper) register_code(KC_LSFT);
                tap_code(base_kc);
                if (is_upper) unregister_code(KC_LSFT);
                return false;

            // English apostrophe before s l m d r t c  (McDonald's, I'll, I'm, I'd,
            // you're, don't, c'mon). '+space resolves the dead acute to a literal '
            // — a bare ' before c would otherwise give ç on US-International.
            case KC_S: case KC_L: case KC_M: case KC_D: case KC_R: case KC_T: case KC_C:
                tap_code(KC_QUOTE); tap_code(KC_SPC);
                if (is_upper) register_code(KC_LSFT);
                tap_code(base_kc);
                if (is_upper) unregister_code(KC_LSFT);
                return false;

            case KC_SPC:  // literal apostrophe
                tap_code(KC_QUOTE);
                tap_code(KC_SPC);
                return false;

            default:
                // Not an accent target: drop the pending TILDE and let the key
                // be processed normally instead of emitting garbage.
                return true;
        }
    }

    return true;
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
      // Calculate and accumulate scroll values based on mouse movement and divisors
      scroll_left_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
      scroll_left_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;
      scroll_right_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
      scroll_right_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;
  
      // Assign integer parts of accumulated scroll values to the mouse report
      left_report.h = (int16_t)scroll_left_accumulated_h;
      left_report.v = (int16_t)scroll_left_accumulated_v;
      right_report.h = (int16_t)scroll_right_accumulated_h;
      right_report.v = (int16_t)scroll_right_accumulated_v;
  
      // Update accumulated scroll values by subtracting the integer parts
      scroll_left_accumulated_h -= (int16_t)scroll_left_accumulated_h;
      scroll_left_accumulated_v -= (int16_t)scroll_left_accumulated_v;
      scroll_right_accumulated_h -= (int16_t)scroll_right_accumulated_h;
      scroll_right_accumulated_v -= (int16_t)scroll_right_accumulated_v;
  
      // Clear the X and Y values of the mouse report
      left_report.x = 0;
      left_report.y = 0;
      right_report.x = 0;
      right_report.y = 0;
    }
    return pointing_device_combine_reports(left_report, right_report);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
      case _NAV:
        set_scrolling = true;
      break;
      default:
        if (set_scrolling) {
          set_scrolling = false;
        }
      break;
    }
    return state;
}

#ifdef RGB_MATRIX_ENABLE
// _NAV = per-key colours by function. _SYM / _FUNCTION / _ADJUST / _MOUSE = flat
// wash (green / yellow / white / magenta). _WMSEL = held cluster white, picker
// desktops green, picker OSM Shift blue (only the active side lit). Plus the flash.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Notification flash — solid colour blink over the whole board, any layer.
    if (notify_blinks_left > 0) {
        if (timer_elapsed32(notify_phase_timer) >= NOTIFY_PHASE_MS) {
            notify_phase_timer = timer_read32();
            if (notify_phase_on) {
                notify_phase_on = false;      // finished an "on" phase
                notify_blinks_left--;
            } else {
                notify_phase_on = true;       // start the next "on" phase
            }
        }
        for (uint8_t i = led_min; i < led_max; i++) {
            if (notify_phase_on) rgb_matrix_set_color(i, notify_r, notify_g, notify_b);
            else                 rgb_matrix_set_color(i, RGB_BLACK);
        }
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state);
    if (layer != _NAV && layer != _SYM && layer != _FUNCTION && layer != _ADJUST
        && layer != _MOUSE && layer != _WMSEL) return false;

    // Blank everything in this batch (keys + underglow) so only the mapped keys
    // below light up. Drop this loop to keep the running animation underneath.
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, RGB_BLACK);
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) continue;

            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});

            // _WMSEL: light only the side in play. wmsel_side 1 = left cluster
            // held -> right hand picks; 2 = right cluster held -> left hand picks.
            // Held cluster = white, picker desktops = green, picker's OSM Shift = blue.
            if (layer == _WMSEL) {
                bool on_left = row < MATRIX_ROWS / 2;
                bool pick_hand = (wmsel_side == 1 && !on_left) || (wmsel_side == 2 && on_left);
                uint16_t base = keymap_key_to_keycode(_ALPHA, (keypos_t){col, row});
                bool held =
                    (wmsel_side == 1 && (base == KC_Z || base == KC_X || base == KC_C || base == KC_D)) ||
                    (wmsel_side == 2 && (base == KC_H || base == KC_COMM || base == KC_DOT || base == KC_SLSH));

                if (held) {
                    rgb_matrix_set_color(led, RGB_WHITE);
                } else if (pick_hand && kc >= WM_1 && kc <= WM_9) {
                    rgb_matrix_set_color(led, RGB_GREEN);
                } else if (pick_hand && kc == OSM(MOD_LSFT)) {
                    rgb_matrix_set_color(led, RGB_BLUE);
                }
                continue;
            }

            // _SYM / _FUNCTION / _ADJUST / _MOUSE: flat wash over every non-blank key.
            if (layer != _NAV) {
                if (kc == KC_TRNS || kc == KC_NO) continue;
                if      (layer == _SYM)      rgb_matrix_set_color(led, RGB_GREEN);
                else if (layer == _FUNCTION) rgb_matrix_set_color(led, RGB_YELLOW);
                else if (layer == _ADJUST)  rgb_matrix_set_color(led, RGB_WHITE);
                else                        rgb_matrix_set_color(led, RGB_MAGENTA);  // _MOUSE
                continue;
            }

            switch (kc) {
                case KC_1 ... KC_0:                                       // numpad
                    rgb_matrix_set_color(led, RGB_BLUE);   break;
                case KC_LEFT: case KC_RIGHT: case KC_UP: case KC_DOWN:    // arrows
                    rgb_matrix_set_color(led, RGB_RED);    break;
                case U_WORDL: case U_WORDR: case KC_PGUP: case KC_PGDN:  // word / page nav
                    rgb_matrix_set_color(led, RGB_GREEN);  break;
                case KC_BSPC: case KC_DEL: case U_DWORD: case U_DLINE:    // delete
                    rgb_matrix_set_color(led, RGB_ORANGE); break;
                case U_COPY: case U_CUT: case U_PASTE:                    // clipboard
                    rgb_matrix_set_color(led, RGB_PURPLE); break;
                case KC_VOLU: case KC_VOLD: case KC_MUTE:
                case KC_MPRV: case KC_MPLY: case KC_MNXT:                 // media
                    rgb_matrix_set_color(led, RGB_YELLOW); break;
                case SELWORD:                                            // select word
                    rgb_matrix_set_color(led, RGB_CYAN);   break;
                case OS_SFT: case OS_CTL:                                // thumb mods
                    rgb_matrix_set_color(led, RGB_WHITE);  break;
                default:
                    break;
            }
        }
    }
    return false;
}
#endif
