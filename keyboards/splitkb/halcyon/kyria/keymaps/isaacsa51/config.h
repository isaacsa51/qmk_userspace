#pragma once

// Home-row mods: Chordal Hold resolves opposite-hand chords as HOLD instantly and
// same-hand rolls as TAP, so the tapping term is only a fallback for same-hand holds.
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
#define TAPPING_TERM 200          // was 325; tune 170-220 to taste
#define QUICK_TAP_TERM 0          // replaces the deprecated TAPPING_FORCE_HOLD
#define TAPPING_TOGGLE 2

// Combos resolve against _ALPHA (layer 0) regardless of the active layer,
// gated to the alpha layers by combo_should_trigger() in keymap.c
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_SHOULD_TRIGGER

// Whole combo must land within COMBO_TERM of the FIRST key (no per-key reset) —
// tightens the window against fast-roll misfires without adding typing latency.
#define COMBO_TERM 30
#define COMBO_STRICT_TIMER
// Per-combo term so the 4-key homerow "delete word" gesture gets a wider window
// than the tight 2-key symbol combos (see get_combo_term in keymap.c).
#define COMBO_TERM_PER_COMBO

// _MOUSE layer: constant-speed cursor, no acceleration. MK_3_SPEED with no
// MS_ACL* keys on the keymap = one fixed speed (the *_UNMOD values). Lower the
// offset or raise the interval to slow it further.
#define MK_3_SPEED
#define MK_C_OFFSET_UNMOD   10   // px per step  (stock 16)
#define MK_C_INTERVAL_UNMOD 16   // ms per step  (stock 16)

// Cirque trackpad config
#undef CIRQUE_PINNACLE_TAP_ENABLE
#undef CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
