# isaacsa51 keymap — working notes

Running list of keymap/behaviour changes discussed. Tags:
**[done]** applied · **[bug]** found, not fixed · **[cleanup]** dead/redundant · **[decide]** needs a call · **[new]** feature to add

File paths are relative to this keymap folder unless noted.

---

## On-display keymap renderer (ported from AnythingFromScrap/qmk_userspace)

- [x] **[done]** New `display/` tree in this keymap:
  - `hook.c` — overrides the module's weak `display_module_housekeeping_task_user`; draws the current layer's key grid to `lcd_surface` and returns `false` (so the stock layer-number / caps-num-scroll screen is skipped). Grid is drawn on **every** layer including base.
  - `keymap/process_keymap.c` — orchestration; only redraws on a layer change.
  - `keymap/draw_keymap.c` — QP drawing of 22x20 key squares + fonts + icons. Fork's `_MACROS` branch, macro/vim includes, and the RGB-hue/`col % 4` colour heuristic all removed. Colour is now: **letter keys white, everything else green** (`HSV_ALPHA` / `HSV_MOD` defines at the top; classified by whether the label is a single `A`-`Z` char).
  - `keymap/keycode_strings.c` — **rewritten for this keymap**: unwraps mod-taps + modded keycodes, then maps every keycode used here (custom keycodes, tap dances, one-shots, `DF`/`TT`/`TG` layer keys, `SELWORD`) to a short label. Unknown -> `"-"`.
  - `utils.c` — 5x6 display grid <-> `LAYOUT_split_3x6_5` matrix mapping (verbatim; same physical Kyria).
  - `fonts/{3x5,4x7,5x7,9x12}.qff.*` + `images/icons/*.qgf.*` — generated blobs, copied verbatim.
- [x] **[done]** `rules.mk` — `SRC +=` for all of the above, wrapped in `ifeq ($(strip $(HLC_TFT_DISPLAY)), 1)` so non-display builds skip it.
- [ ] **[verify]** Not compiled here (this shell can't pass `SHELL` to `qmk.exe`). If QP rejects the `mono4` fonts/icons, add `QUANTUM_PAINTER_COMPRESSION_ENABLE = yes` to `rules.mk` — but the source fork builds them fine with the same stock module, so it should be a no-op.
- [ ] **[note]** Trade-off: the stock layer number + Caps/Num/Scroll indicators + game-of-life screensaver are replaced by the grid. To keep the stock screen on the base layer, change `hook.c` to `if (get_highest_layer(layer_state) == 0) return true;` before the draw (and add a one-shot surface clear on the nav->base transition).

---

## Build & flash (reference)

- This is a QMK **userspace** overlay — needs `qmk_firmware` + `qmk` CLI alongside. Build from the **QMK MSYS** terminal, not Git Bash.
- `qmk config user.qmk_home` / `user.overlay_dir`. Per-half builds: `-e HLC_TFT_DISPLAY=1` (left), `-e HLC_CIRQUE_TRACKPAD=1` (right). Command needs `-km isaacsa51`.
- Flash = RP2040 UF2: double-tap reset -> `RPI-RP2` drive -> drop `.uf2`, once per half. Handedness is automatic (GP24 pin); flash the same handedness build to both sides.
- CI targets `splitkb/vial-qmk`, but its `halcyon` branch no longer exists -> CI `qmk_ref` silently falls back. Local builds run against mainline `qmk/qmk_firmware`.

---

## Fixes applied this session

- [x] **[done]** `os_detection/os_layer.h` — added `#include <stdint.h>` (mainline QMK dropped the implicit include; `uint8_t` failed).
- [x] **[done]** `../../../../../users/halcyon_modules/splitkb/halcyon.h` — added `#include <stdbool.h>` (same cause; `bool` failed, cascaded into `hlc_tft_display.c`).
- [x] **[done]** `_CRATE` layer — matched the analyzer image ("swap kj yl"): Y<->L left-top, U->K right-top, K->U right-home; kept `TILDE` on the outer pinky.
- [x] **[done]** Deleted `_GIT` and `_DROID` layers (redundant with the IDE's own keymaps). Removed from `layers.h`, both layer bodies + comments in `keymap.c`, the `DROID`/`GIT` defines, `MO(DROID)` in `_SYM` -> `_______`. Removed `GIT` + all 19 IDE keycodes from `custom_keys.h`, their handler cases, and the `SWTCHR` ctrl-sticky machinery (`ctrl_sticky_active`, `is_ignorable_key`) from `custom_keys.c`. This also resolves the `RFACTR`, `SWTCHR`-hold, and `MO(DROID)`-fragile bugs by removal.
- [x] **[done]** Smart-tilde rewrite (`custom_keys/custom_keys.c`): fixed the `default` case (was `tap_code()` on a 16-bit value); non-accent keys now pass through untouched instead of emitting `'`+junk; a modifier held between `TILDE` and the letter passes through without consuming the latch (so `TILDE`, Shift, vowel -> uppercase accent); collapsed the byte-identical WIN/MAC vowel branch; `TILDE`+Space is now an explicit literal apostrophe. `n -> ñ` OS split is unchanged (tested `ed74715`).
- [x] **[done]** Smart-tilde English apostrophe — `TILDE` + `s l m d r t c` now emits a literal `'` + letter (`McDonald's`, `I'll`, `I'm`, `I'd`, `you're`, `don't`, `c'mon`). Done via `'`+space (dead acute resolved to `'`) so `'`+`c` doesn't come out as `ç` on US-International. Other consonants still fall through `default` (latch dropped, key typed as-is).
- [x] **[done]** Smart-tilde timeout — `smart_tilde_timer` (`timer_read32()`) set when the latch is armed (both `case TILDE:` and `dance_cmd_finished` double-tap); at the next keypress, if `> SMART_TILDE_TIMEOUT_MS` (1000) elapsed the latch is dropped and the key types normally. No `deferred_exec` / rules.mk change needed — the check runs at the next keypress, which is the only moment it matters.
- [x] **[done]** `oshtsf` / `oshtct` single-tap — now `set_oneshot_mods(MOD_BIT(KC_LSFT))` / `MOD_BIT(KC_LCTL))`, a real one-shot that applies to the next key. Double-tap (hold-until-release) branch unchanged.
- **[decide]** The two include fixes are the alternative to switching local `qmk_firmware` to `splitkb/vial-qmk`. Currently staying on mainline + patching.

---

## Bugs found, not fixed

_(none open)_

---

## Dead code / cleanup

- [ ] **[cleanup]** `combos/combos.c` — `copy/paste/cut_combo` arrays defined, `key_combos[]` + `process_combo_event` fully commented, `combos.h` is 100% comment; `rules.mk` still compiles it. Live table is in `keymap.c` (`// TODO: Migrate...` at line 108). Pick one home.
- [ ] **[cleanup]** Dead keycodes in `enum custom_keycodes`: `DRAG_S`, `DEL_LINE` (never handled; drag-scroll is layer-driven via `set_scrolling`). Keep `DEL_LINE` if the OS-aware editing feature will use it.
- [x] **[done]** `get_base_keycode` (`custom_keys/custom_keys.c`) — was a hand-maintained 8-entry switch; now `IS_QK_MOD_TAP(kc) ? QK_MOD_TAP_GET_TAP_KEYCODE(kc) : kc`. Handles any mod-tap on any layer, so the smart-tilde no longer breaks when a home-row mod moves.
- [ ] **[cleanup]** Stale header advice (`keymap.c` `[ Dev tips ]`) — "running out of RAM / PROGMEM / disable RGB" is AVR guidance; rev4 is RP2040 (264 KB).

---

## Layer structure

- [x] **[done]** Home-row mods: `CHORDAL_HOLD` + `PERMISSIVE_HOLD` in `config.h`, `TAPPING_TERM` 325 -> 200, `TAPPING_FORCE_HOLD` -> `QUICK_TAP_TERM 0`. `chordal_hold_handedness()` in `custom_keys.c` (rows 0-3 = left, 4-7 = right). Opposite-hand chords now resolve as hold instantly; tune `TAPPING_TERM` 170-220, drop `PERMISSIVE_HOLD` if same-hand rolls misfire.
- [x] **[done]** Home-row mod order is **Alt, GUI, Shift, Ctrl** (pinky..index), mirrored on the right hand. `HM_A/R/S/T` + `HM_N/E/I/O` in `keymap.c`. Added to **all three** alpha layers: `_ALPHA` and `_CANARIA` left row already used `HM_*`; `_CRATE` left row (`C R A T`) + the right-pinky letters (`_CRATE` `U`, `_CANARIA` `C`) get `HC_C`/`HC_A`/`HC_U` (same fingers, different letters).
- [x] **[done]** `_WM` has a hard escape: `TO(_ALPHA)` on the left pinky bottom (labelled `BASE`), in case the `TT(_WM)` toggle gets stuck.
- [ ] **[decide]** Three alpha layers (`_ALPHA`/`_CANARIA`/`_CRATE`) — keep all three only if actively A/B testing; otherwise drop two. Home-row mods now match across all three; combos still resolve via `COMBO_ONLY_FROM_LAYER 0` so they track automatically.
- [ ] **[decide]** `_SYM` vs combos — SYM is a complete superset fallback (adds `& % ~` backtick over every combo symbol). Legit safety net; question is whether it earns a dedicated `TT` toggle.
- [x] **[done]** `_WM` rebuilt for **FancyWM** (`github.com/FancyWM/fancywm`). Every key = `fancywm()` helper: **clears all held mods** (homerow / one-shot / HYPER-MEH), sends a clean **`Alt+Win`** activation chord, waits `FANCYWM_ACTIVATION_MS` (30), sends the secondary, restores mods. (Set FancyWM's activation hotkey to `Alt + Win` in its settings to match.) `WM_L/R/U/D` = move focus; hold `WM_MOVE` -> move window (Ctrl+dir), `WM_SWAP` -> swap (Shift+dir); `WM_MOVE` also turns `WM_1-9`/`D<`/`D>` into move-to-desktop. Plus panels H/V/S, float, promote, refresh, toggle-manager, show-desktop, cancel, desktop prev/left/right. `WM_MOVE`/`WM_SWAP` on the right thumb (row 4). 27 `WM_*` keycodes; display labels in `keycode_strings.c`.
- [x] **[done]** Every non-WM key on `_WM` is now `KC_NO` (was `_______`) — the transparent thumb keys were leaking `_ALPHA`'s `OALT`/`HYPER`/`MEH` into the chord, which is why the activation was landing as `Alt+Win` instead of `Shift+Win`. Only `WM` (layer toggle, left thumb) stays live.
- [ ] **[note]** `fancywm()` blocks the scan ~35 ms per press (`wait_ms`). Bump `FANCYWM_ACTIVATION_MS` if FancyWM still drops actions, lower it if laggy. Old GlazeWM/AeroSpace `A(KC_n)` bindings are gone.

---

## OS-awareness infrastructure

- [ ] **[decide]** `os_detection/` does no detection — it's a manual `TG_OS` toggle of a global. Fine choice, but the name lies; QMK's real `OS_DETECTION` exists.
- [ ] **[bug/QoL]** `current_os` not persisted -> resets to Windows every unplug. One `eeconfig` byte fixes it.
- [ ] **[cleanup]** `current_os` re-declared `extern` in `os_detection/os_layer.h` and `tap_dance/td_declarations.h:9` — the second should just include the first.
- [x] **[done]** `tap_os(mac_kc, win_kc)` helper added in `custom_keys.c` — minimal version of alvaro-prieto's `osKeys[][2]` table.

---

## New feature: OS-aware editing (delete / move / copy / cut / paste)

- [x] **[done]** Keycodes `U_WORDL`, `U_WORDR`, `U_DWORD`, `U_DLINE`, `U_COPY`, `U_CUT`, `U_PASTE` in `custom_keys.h` + handlers in `custom_keys.c`. `U_WORDL`/`U_WORDR` = word left/right: Ctrl+arrow (win) / Alt+arrow (mac). `U_DWORD` = opt+bksp / ctrl+bksp. `U_DLINE` = cmd+bksp (mac) / Home+Shift+End+Bksp (win).
- [x] **[done]** `_NAV` left cols 1-2 (were dead) now: `DelLn`/`DelWrd` (row 1), real `KC_BSPC`/`U_PASTE` (row 2), `Cut`/`Copy` (row 3). Arrow T untouched.
- [x] **[done]** Deleted the `Click` key (`TD_MOUSE` = `ACTION_TAP_DANCE_DOUBLE(MS_BTN1, MS_BTN2)`), replaced with `ALTTAB` on all three alpha layers' left outer thumb — OS-aware quick window switch: `Cmd+Tab` (mac) / `Alt+Tab` (win). Removed `TD_MOUSE` from the TD enum + `tap_dance_actions[]` + the `MOUSE` define. `MOUSEKEY_ENABLE` now unused but left on.
- [x] **[done]** Dropped `WMOD` (the held word-modifier). Word motion is now on the `_NAV` arrow-row flanks: `KC_HOME` -> `U_WORDL`, `KC_END` -> `U_WORDR` (OS-aware, self-contained). Word *select* = tap `OSHTSF` first (one-shot Shift stacks onto the `S(C(KC_LEFT))` the keycode sends).
- [x] **[done]** `_NAV` right thumb order `OSHTCT, MO(_MOUSE), OSHTSF` — the freed WMOD slot now holds the momentary `_MOUSE` layer; Shift/Ctrl one-shots flank it. `SELWORD` (tap to extend) is the other selection path.
- [x] **[done]** New combo: whole left homerow **A+R+S+T** -> `U_DWORD` (OS-aware delete word). `homerow_dword_combo` in `keymap.c`, gated to the alpha layers by the existing `combo_should_trigger`; fires on the same physical keys on `_CANARIA` / `_CRATE` via `COMBO_ONLY_FROM_LAYER 0`. Wider window (`get_combo_term` -> 80 ms, needs `COMBO_TERM_PER_COMBO` in `config.h`) since 4 keys can't land inside the 30 ms symbol-combo window.
- [ ] **[note]** `current_os` defaults to `OS_WIN` and doesn't persist (see the os_detection item). On macOS, press `TG_OS` after every reconnect or the OS-aware keys send the Windows combo.
- [ ] **[decide]** `U_DLINE` behaviour is asymmetric — mac deletes to line start, win clears the line contents. Both editor-dependent; tune per real usage.
- [ ] **[note]** `_NAV` media row (`MPRV/MPLY/MNXT/MUTE`) untouched for now — relocate to `_ADJUST`/`_FUNCTION` only if those slots are needed later.
- [ ] **[note]** Works on all layers via `combo_should_trigger` for combos, but these are plain keycodes so they work everywhere regardless. Test both OS states after flashing.

---

## New layer: `_GAME` (FPS)

- [x] **[done]** Left 3x6 = QWERTY block (`Tab/Q/W/E/R/T`, `LCtrl/A/S/D/F/G`, `LShift/Z/X/C/V/B`) — plain keycodes, no mod-taps. Left thumbs = `Space` x3 (jump) + `LAlt`. Right hand + all unused keys are `KC_NO` so no homerow mods / tap dances fire mid-game; `combo_should_trigger` already excludes `_GAME`.
- [x] **[done]** Right hand: `Bksp`/`Enter`/`Esc` (chat/menu) only. `GAME` = `TG(_GAME)` toggle on `_ADJUST` (col 5, next to the alpha switches) to enter, and on `_GAME` twice (left outer thumb + right inner thumb) to exit.
- [ ] **[note]** No weapon number keys — left hand is full with the QWERTY block. Add `1`-`5` on a thumb or the right hand if wanted.
- [ ] **[note]** No distinct RGB for `_GAME` — extend `rgb_matrix_indicators_advanced_user` with a `_GAME` branch if you want one.

---

## New layer: `_MOUSE`

- [x] **[done]** Held from `_NAV` — `MO(_MOUSE)` on the middle-right thumb (the old `WMOD` slot). `#define MOUSE MO(_MOUSE)` alias; `_MOUSE` appended to `layers.h` (index 8, above `_NAV` so `MO` wins).
- [x] **[done]** Layout mirrors the `_NAV` arrow inverted-T. **Left hand** = scroll wheel T (`MS_WHLU` on the middle-finger column, `MS_WHLL`/`MS_WHLD`/`MS_WHLR` on the row below — mirror of the right-hand arrow columns). **Right hand** = pointer move on the exact `_NAV` arrow keys (`MS_UP` / `MS_LEFT` / `MS_DOWN` / `MS_RGHT`), with `MS_BTN1` / `MS_BTN2` in the `U_WORDL` / `U_WORDR` slots above pointer-left / -right. Everything else `_______` (falls through to `_NAV`).
- [x] **[done]** `MOUSEKEY_ENABLE = yes` added to `rules.mk` (`MS_*` keycodes). `MS_*` + `MO(_MOUSE)` labels added to `display/keymap/keycode_strings.c`.
- [x] **[done]** Acceleration disabled — `MK_3_SPEED` in `config.h` (constant-speed mousekeys). With no `MS_ACL*` keys on the keymap it's a single fixed speed: `MK_C_OFFSET_UNMOD 10` px / `MK_C_INTERVAL_UNMOD 16` ms (stock is 16/16). Lower the offset / raise the interval to slow further. Wheel left at stock (`MK_W_*_UNMOD`, 1 notch / 40 ms).
- [ ] **[note]** Image also had browser back/fwd, volume, and second-hand mouse buttons — left off; add on the free `_MOUSE` columns if wanted.

---

## Per-layer RGB (`_NAV` / `_SYM` / `_FUNCTION` / `_ADJUST` / `_MOUSE`)

- [x] **[done]** `rgb_matrix_indicators_advanced_user` in `custom_keys.c` (`#ifdef RGB_MATRIX_ENABLE`) — runs when any of `_NAV` / `_SYM` / `_FUNCTION` / `_ADJUST` / `_MOUSE` is on top. `_NAV` colours by keycode so it survives layout changes:
  numpad = blue, arrows = red, `U_WORDL`/`U_WORDR`/PgUp/PgDn = green, delete keys = orange, Cut/Copy/Paste = purple, media/volume = yellow, `SELWORD` = cyan, `OSHTSF`/`OSHTCT` = white.
- [x] **[done]** `_SYM` = flat **green**, `_FUNCTION` = flat **yellow**, `_ADJUST` = flat **white**, `_MOUSE` = flat **magenta** — every non-`_______`/`KC_NO` key on the layer lit in the one colour (single `keymap_key_to_keycode(layer, ...)` walk shared with the `_NAV` branch).
- [x] **[done]** Everything else is blanked — a `for (i = led_min..led_max) rgb_matrix_set_color(i, RGB_BLACK)` pass runs before the per-key colours, so unmapped keys and underglow go dark instead of showing the animation. Delete that loop to keep the animation underneath. Palettefx keeps running (state advances); its output is just overwritten each frame.
- [ ] **[note]** Tune `_NAV` by editing the `switch` cases; change a flat-layer colour in the `layer != _NAV` block; add another layer by extending the guard `if` + the colour `if/else` chain.
- [x] **[done]** RGB notification flash — `rgb_notify(r,g,b,blinks)` in `custom_keys.c` blinks every LED over any layer (state machine driven by `rgb_matrix_indicators_advanced_user`, `NOTIFY_PHASE_MS 110`). Wired: `TG_OS` -> green ×2; `caps_word_set_user(true)` and the Caps-Lock tap in `td_caps_finished` -> red ×3. OS mode stays manual/non-persistent as before, just visible now.

---

## Combos

- **[note]** Design intent: iconic/gestural cipher — shape (`-` = home-row swipe, `\` = down-right diagonal, `^` = up-reach) and tone (`?` = up = rising); brackets/braces/parens by row + roll direction for open/close.
- [x] **[done]** Misfires on fast Spanish typing — added `COMBO_STRICT_TIMER` + `COMBO_TERM 30` in `config.h` (whole combo within 30 ms of the first key, no per-key reset; tighter window, no added latency). Bump `COMBO_TERM` to ~40 if intentional combos get hard to hit.
- [x] **[done]** `A+R+S+T` (whole left homerow) -> `U_DWORD` (OS-aware delete word). `COMBO_TERM_PER_COMBO` now on; `get_combo_term` gives this one combo 80 ms (matched by `combo->keys == homerow_dword_combo`), everything else stays at `COMBO_TERM`.
- [ ] **[new]** If specific 2-key ones still slip: `COMBO_MUST_HOLD_PER_COMBO`, must-hold(~90ms) on the 6 Spanish-collision offenders (`= - _ ? : *`), instant for the rest. Put callbacks in `combos/combos.c` (revives the dead file).
- [ ] **[decide]** Or just delete those 6 from `key_combos[]` — single chars already on `_SYM`; keep the collision-free shape combos.
- [x] **[done]** `COMBO_ONLY_FROM_LAYER 0` + `COMBO_SHOULD_TRIGGER` in `config.h`; `combo_should_trigger()` in `keymap.c` gated to `_ALPHA`/`_CANARIA`/`_CRATE`. Combos now fire on the same physical keys across all three alpha layers, and not on NAV/SYM/etc. (caveat: letters under the keys differ on CRATE -> position-memory, not shape-memory).
- [ ] **[new]** Add a header comment documenting the cipher.
