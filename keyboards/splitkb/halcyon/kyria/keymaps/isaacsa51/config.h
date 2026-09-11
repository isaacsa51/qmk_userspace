#pragma once

// PaletteFx (getreuer module) as the base-layer RGB. Effect = Reactive, palette
// = Polarized. The module only *registers* PALETTEFX_REACTIVE when key tracking
// is on, hence RGB_MATRIX_KEYPRESSES. PaletteFx maps the RGB Matrix hue onto the
// palette index; palettes enable alphabetically -> Polarized = index 9
// (afterburn 0, amber 1, badwolf 2, carnival 3, classic 4, dracula 5, groovy 6,
// notpink 7, phosphor 8, polarized 9). RGB_MATRIX_DEFAULT_* only bite on a fresh
// EEPROM, so keyboard_post_init_user() in keymap.c re-forces this on every
// plug-in.
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_PALETTEFX_REACTIVE
#define RGB_MATRIX_DEFAULT_HUE  (RGB_MATRIX_HUE_STEP * 9)

// Home-row mods: Chordal Hold resolves opposite-hand chords as HOLD instantly and
// same-hand rolls as TAP, so the tapping term is only a fallback for same-hand holds.
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
#define TAPPING_TERM 200          // was 325; tune 170-220 to taste
#define QUICK_TAP_TERM 0          // replaces the deprecated TAPPING_FORCE_HOLD
#define TAPPING_TOGGLE 2

// Combos resolve against _ALPHA (layer 0) regardless of the active layer,
// gated to the alpha layers by combo_should_trigger() in combos/combos.c
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_SHOULD_TRIGGER

// Whole combo must land within COMBO_TERM of the FIRST key (no per-key reset) —
// tightens the window against fast-roll misfires without adding typing latency.
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
// Per-combo term so the 4-key WM picker gestures get a wider window than the
// tight 2-key symbol combos (see get_combo_term in combos/combos.c).
#define COMBO_TERM_PER_COMBO

// _MOUSE layer: kinetic-curve cursor (MK_KINETIC_SPEED,
// https://docs.qmk.fm/features/mouse_keys#kinetic-mode) — ramps from a slow,
// precise start up to BASE_SPEED the longer a direction is held, unlike the
// flat MK_3_SPEED constant mode this replaces (which felt sluggish since it
// has no ramp-up). BASE_SPEED is the top-end knob; raise it further if the
// cursor still feels slow at full ramp.
#define MK_KINETIC_SPEED
#define MOUSEKEY_INITIAL_SPEED 100
#define MOUSEKEY_BASE_SPEED    6000

// Cirque trackpad config
#undef CIRQUE_PINNACLE_TAP_ENABLE
#undef CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
