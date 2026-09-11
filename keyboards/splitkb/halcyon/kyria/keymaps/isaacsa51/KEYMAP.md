# isaacsa51 — Halcyon Kyria keymap

Reference for this keymap: every layer, every combo, the tap dances, the
OS‑aware keys, the smart‑tilde dead key, and the RGB behaviour. Generated from
`keymap.c` / `custom_keys.c` / `config.h`; keep it in sync when those change.

> The folder's other `readme.md` is the **inherited splitkb default** keymap doc
> and does not describe this keymap.

---

## At a glance

| | |
|---|---|
| **Board** | Halcyon Kyria rev4 (RP2040) — TFT display on the left half, Cirque trackpad on the right |
| **Bases** | Colemak‑DH (default) · Crate (Spanish‑tuned) · Canaria — swapped at runtime on the Adjust layer |
| **Home‑row mods** | `ALT GUI SHFT CTRL` pinky→index, mirrored. Chordal Hold + `PERMISSIVE_HOLD`, `TAPPING_TERM 200`, `QUICK_TAP_TERM 0` |
| **OS mode** | Windows by default. `TG_OS` flips Win ⇄ Mac and **persists** across replug/reboot. |
| **OS layout** | The keymap assumes **US‑International** on the host (dead keys for accents). |
| **Combos** | Fire **by position** — resolved against layer 0, so the same physical keys trigger them on every base. `COMBO_TERM 30` (`COMBO_STRICT_TIMER`), 80 ms for the 4‑key gestures. Gated to the three base layers. |
| **RGB** | PaletteFx **Reactive** effect + **Polarized** palette, forced on every plug‑in. Per‑layer indicators on the overlay layers (below). |
| **Mouse** | Kinetic speed curve, ramps up while held (`MK_KINETIC_SPEED`, base 6000 px/s). |

---

## Layers

`_______` = transparent (falls through to the layer below). `XXXXX` = the key
that got you here. Home‑row mods are shown as the tapped letter; hold for the mod.

### `_ALPHA` — Colemak‑DH  ·  default base

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  Esc   |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Cmd/~  |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | TILDE  |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   D  |   V  | OS ⌥ | CAPS |  |F-keys|OS ⇧ |   K  |   H  | ,  < | . >  | /  ? | TG_OS  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |AltTab|  WM  |  Nav | Space|A/Spc |  | Enter|Bkspc |  Sym | MEH  | HYPER|
                       `----------------------------------'  `----------------------------------'
```

* **Home‑row mods (hold):** `A`=Alt `R`=GUI `S`=Shift `T`=Ctrl  ·  `N`=Ctrl `E`=Shift `I`=GUI `O`=Alt.
* **Cmd / ~** = `TD_CMD_TILDE` tap dance — tap+hold for ⌘/Ctrl, double‑tap arms the tilde.
* **OS ⌥ / OS ⇧** = one‑shot Alt / one‑shot Shift (thumb level).
* **CAPS** = tap dance — 1 tap Caps Lock, 2 taps Caps Word.
* **F‑keys / Sym / Nav** = tap‑toggle layer keys (`TT`). **WM** = `TT(_WM)`.
* **A/Spc** = `Alt` + `Space`.

### `_CRATE` — Spanish‑tuned  ·  `DF(_CRATE)` on Adjust

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   W  |   Y  |   L  |   P  |   B  |                              |   J  |   F  |   O  |   K  | ;  : |  Esc   |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Cmd/~  |   C  |   R  |   A  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   U  | TILDE  |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   X  |   Z  |   Q  |   D  |   V  | OS ⌥ | CAPS |  |F-keys|OS ⇧ |   H  |   S  | ,  < | . >  | /  ? | TG_OS  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |AltTab|  WM  |  Nav | Space|A/Spc |  | Enter|Bkspc |  Sym | MEH  | HYPER|
                       `----------------------------------'  `----------------------------------'
```

* **Home‑row mods (hold):** `C`=Alt `R`=GUI `A`=Shift `T`=Ctrl  ·  `N`=Ctrl `E`=Shift `I`=GUI `U`=Alt.
* Same thumb / combo behaviour as `_ALPHA` — only the letters move.
* Origin: akl.gg **crate** layout with `kj` / `yl` swapped.

### `_CANARIA`  ·  `DF(_CANARIA)` on Adjust

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   W  |   L  |   Y  |   P  |   B  |                              |   F  |   J  |   O  |   U  | ;  : |  Esc   |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Cmd/~  |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   C  | TILDE  |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Q  |   Z  |   V  |   D  |   K  | OS ⌥ | CAPS |  |F-keys|OS ⇧ |   X  |   H  | ,  < | . >  | /  ? | TG_OS  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |AltTab|  WM  |  Nav | Space|A/Spc |  | Enter|Bkspc |  Sym | MEH  | HYPER|
                       `----------------------------------'  `----------------------------------'
```

* **Home‑row mods (hold):** `A`=Alt `R`=GUI `S`=Shift `T`=Ctrl  ·  `N`=Ctrl `E`=Shift `I`=GUI `C`=Alt.
* Canaria A‑C swapped — <https://github.com/christoofar/canaria>.

### `_NAV` — numbers, arrows, media, editing  ·  hold **Nav** (left thumb)

```
,-------------------------------------------.                              ,-------------------------------------------.
| DelLn  |DelWrd|  7   |   8  |   9  |      |                              | PgUp |  W<  |   ↑  |  W>  | Vol+ | Delete |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| Bkspc  |Paste |  4   |   5  |   6  |  0   |                              | PgDn |  ←   |   ↓  |   →  | Vol- | Insert |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|  Cut   | Copy |  1   |   2  |   3  |SelWrd|      |      |  |      |      | Pause| Prev | Play | Next | Mute | PrtSc  |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      | XXXX |      |      |  |OS Ctl| Mouse|OS Sft|      |      |
                       `----------------------------------'  `----------------------------------'
```

* **W< / W>** = word left / right — OS‑aware (Ctrl+arrow on Windows, ⌥+arrow on macOS). Tap **OS Sft** first to *select* by word.
* **DelLn / DelWrd / Cut / Copy / Paste** = OS‑aware editing (see the OS table).
* **SelWrd** = getreuer `select_word` — tap to select the word, tap again to extend.
* **OS Ctl / OS Sft** = `OS_CTL` / `OS_SFT` — **tap** = one‑shot mod (stacks); **hold** = held mod that engages on the next keypress. **Mouse** = `MO(_MOUSE)`.

### `_SYM` — symbols  ·  hold **Sym** (right thumb)

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |  &   |  $   |  [   |  ]   |  %   |                              |      |  "   |  <   |  >   |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|   ~    |  !   |  @   |  (   |  )   |  |   |                              |   ^  |  -   |  *   |  :   |  #   |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |  \   |  `   |  {   |  }   |  +   |      |      |  |      |      |      |  _   |  ,   |  .   |  /   |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      | XXXX |      |      |
                       `----------------------------------'  `----------------------------------'
```

Complete symbol set — a fallback for anything the combos don't cover (`& % ~` backtick).

### `_FUNCTION` — F‑keys + mods  ·  hold **F‑keys** (upper‑right thumb, next to CAPS)

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI | ADJUST |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |  F1  |  F2  |  F3  |  F4  |      |      |      |  | XXXX |      |      |      |      |      |      |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Right‑hand home row is plain modifiers so you can hold `Fn` and stack mods. **ADJUST** takes you to the Adjust layer.

### `_ADJUST` — default layer + RGB  ·  from **Function**

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |      |      |      |                              |      |      |      |      |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |ALPHA |CANARI|CRATE | GAME |      |                              | RGB  | Sat+ | Hue+ | Val+ | Mode+|        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |      |  |      |      |      | Sat- | Hue- | Val- | Mode-|        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |      |      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

* **ALPHA / CANARI / CRATE** = `DF()` — set the default base layer.
* **GAME** = `TG(_GAME)` — toggle the game layer.
* **RGB row** = `RM_TOGG` / `RM_SATU/D` / `RM_HUEU/D` / `RM_VALU/D` / `RM_NEXT/PREV`. On a PaletteFx effect, **Hue = palette selector**.

### `_WM` — window manager (FancyWM)  ·  tap **WM** (left thumb) to lock, hold for momentary

```
,-------------------------------------------.                              ,-------------------------------------------.
|  TGL   | RFR  |  D7  |  D8  |  D9  |  D~  |                              | PNH  | PNV  |   ^  | PNS  |  DSK  |  ESC   |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|  FLT   |  D<  |  D4  |  D5  |  D6  |  D>  |                              |      |  <   |   v  |   >  |      |  PRO   |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| BASE   |      |  D1  |  D2  |  D3  |      |      |      |  |      |      |      |      |      |      |      |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |  WM  |      |      |      |  | SWP  | MOV  |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Every key clears held mods, taps FancyWM's **Alt+Win** activation chord, waits
~30 ms, then taps one secondary key. Set FancyWM's activation hotkey to `Alt+Win`.
Desktops `D1..D9` follow the Nav numpad (`7 8 9 / 4 5 6 / 1 2 3`).

| Label | Keycode | FancyWM action |
|---|---|---|
| `< > ^ v` | `WM_L/R/U/D` | move **focus** in that direction (see modes below) |
| `D1..D9` | `WM_1..WM_9` | switch to virtual desktop 1–9 |
| `D< / D>` | `WM_DL / WM_DR` | switch to the desktop left / right of here |
| `D~` | `WM_DPRV` | jump back to the previously‑focused desktop |
| `PNH / PNV / PNS` | `WM_PANH/V/S` | wrap the focused window in a new horizontal / vertical / stack panel |
| `FLT` | `WM_FLOAT` | toggle focused window tiled ⇄ floating |
| `PRO` | `WM_PROMO` | promote the focused window to the main pane |
| `RFR` | `WM_REFR` | re‑run the tiling layout |
| `TGL` | `WM_TOGL` | turn the FancyWM manager on / off |
| `DSK` | `WM_SHDSK` | show desktop (minimise / restore all) |
| `ESC` | `WM_CANC` | cancel the pending command / dismiss the modal |
| `MOV` | `WM_MOVE` | **hold:** `< > ^ v` and `D1..D9` now *move* the window there |
| `SWP` | `WM_SWAP` | **hold:** `< > ^ v` now *swap* the window with its neighbour |
| `BASE` | `TO(_ALPHA)` | hard exit back to the base layer |

Every non‑WM key on this layer is `KC_NO` so no ambient mod leaks into the chord.

### `_GAME` — FPS left‑hand block  ·  toggle **GAME** on Adjust

```
,-------------------------------------------.                              ,-------------------------------------------.
|  Tab   |   Q  |   W  |   E  |   R  |   T  |                              | XXXX | XXXX | XXXX | XXXX | XXXX |  Bksp  |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
| LCtrl  |   A  |   S  |   D  |   F  |   G  |                              | XXXX | XXXX | XXXX | XXXX | XXXX | Enter  |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
| LShift |   Z  |   X  |   C  |   V  |   B  | LAlt |Space |  | GAME | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |  Esc   |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       | GAME | XXXX |Space |Space |Space |  | XXXX | XXXX | XXXX | XXXX | XXXX |
                       `----------------------------------'  `----------------------------------'
```

Plain QWERTY block — no mod‑taps, tap dances, or combos fire mid‑game. `GAME` (either the Adjust key or this layer's inner‑right thumb) toggles back out.

### `_MOUSE` — cursor + wheel + clicks  ·  hold from Nav (middle‑right thumb)

```
,-------------------------------------------.                              ,-------------------------------------------.
|        |      |      |Whl ↑ |      |      |                              |      | LMB  | Ms ↑ | RMB  |      |        |
|--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
|        |      |Whl → |Whl ↓ |Whl ← |      |                              |      | Ms ← | Ms ↓ | Ms → |      |        |
|--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
|        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
`----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
                       |      |      |      |      |      |  |  held|      |      |      |      |
                       `----------------------------------'  `----------------------------------'
```

Left hand = scroll wheel, right hand = pointer, mirroring the Nav arrow inverted‑T.
**Combo:** press `LMB` + `RMB` together → middle / wheel click.

### `_WMSEL` — FancyWM desktop picker  ·  **combo**, held

Hold a 4‑key row from a base layer for as long as you want to pick a desktop:

* **`Z X C D`** (left bottom row) → pick with the **right** hand, numpad order:
  ```
     D7 D8 D9
     D4 D5 D6
     D1 D2 D3
  ```
* **`H , . /`** (right bottom row) → pick with the **left** hand:
  ```
  home:  A R S T G  ->  D8 D7 D6 D5 D9
  bot :  Z X C D    ->  D4 D3 D2 D1
  ```

Tap the picking hand's inner‑thumb **one‑shot Shift** first → *move* the focused
window to that desktop (FancyWM `Shift+N`) instead of switching.

---

## Home‑row mods

Order pinky→index is **Alt · GUI · Shift · Ctrl**, mirrored on the right hand, on
all three base layers.

| Finger | Left | Right |
|---|---|---|
| pinky | Alt | Alt |
| ring | GUI | GUI |
| middle | Shift | Shift |
| index | Ctrl | Ctrl |

* **Chordal Hold:** an opposite‑hand chord resolves as **hold** instantly; a
  same‑hand roll stays a **tap**. `TAPPING_TERM` (200 ms) is only the fallback for
  a same‑hand hold. Tune 170–220; drop `PERMISSIVE_HOLD` if same‑hand rolls misfire.
* The index‑inner keys (`G` left, `M` right) have **no** mod.

---

## Tap dances

| Key | 1 tap | 2 taps / hold |
|---|---|---|
| **Cmd / ~** (`TD_CMD_TILDE`, left home outer) | tap+hold → ⌘ (mac) / Ctrl (win) | double‑tap → **arm the smart tilde** (same as the `~` key) |
| **CAPS** (`TD_CAPS`, upper‑left thumb) | Caps Lock | Caps Word |

Caps Lock and Caps Word both flash the board **red ×3**.

### `_NAV` right‑thumb mods — `OS_SFT` / `OS_CTL`

Not tap dances — custom keycodes (`custom_keys.c`).

* **Tap** → one‑shot Shift / Ctrl (applies to the next key; the two **stack**).
* **Hold** → real Shift / Ctrl that engages the **instant another key is
  pressed** and stays held until release — no tapping‑term wait. So holding
  `OS_SFT` + typing shifts everything; holding it + arrows selects by word.

---

## Combos

Combos resolve against layer 0, so they fire on the **same physical keys** on
every base — the table shows the Colemak‑DH letters. Window ≈ 30 ms
(`COMBO_STRICT_TIMER`); 80 ms for the two 4‑key WM picker rows. Active only on
`_ALPHA` / `_CRATE` / `_CANARIA`.

**Brackets & parens**

| Keys | Out |
|---|---|
| `W` + `F` | `[` |
| `F` + `P` | `]` |
| `X` + `C` | `{` |
| `C` + `D` | `}` |
| `L` + `U` | `(` |
| `U` + `Y` | `)` |

**Operators**

| Keys | Out |
|---|---|
| `R` + `S` | `-` |
| `S` + `T` | `=` |
| `T` + `G` | `+` |
| `S` + `D` | `_` |
| `U` + `E` | `*` |
| `E` + `.` | `\` |
| `J` + `M` | `^` |

**Prompts & angles**

| Keys | Out |
|---|---|
| `N` + `U` | `?` |
| `F` + `T` | `!` |
| `E` + `I` | `"` |
| `H` + `,` | `<` |
| `,` + `.` | `>` |

**Code symbols**

| Keys | Out |
|---|---|
| `W` + `R` | `@` |
| `F` + `S` | `#` |
| `T` + `P` | `$` |
| `N` + `E` | `:` |
| `M` + `N` | `\|` |

**Full‑row gestures**

| Keys | Action |
|---|---|
| `Z` `X` `C` `D` (left bottom row) | WM desktop picker — pick with the **right** hand |
| `H` `,` `.` `/` (right bottom row) | WM desktop picker — pick with the **left** hand |
| `LMB` + `RMB` (on `_MOUSE`) | middle / wheel click |

> `Z X C D` overlaps the `{` / `}` combos and `H , . /` overlaps `<` / `>` —
> slap the four keys as one chord; an uneven roll can emit a stray bracket.

---

## OS‑aware keys

`TG_OS` flips these between macOS and Windows. Default is **Windows**, and the
choice **persists** across replug/reboot (stored in EEPROM).

| Key | macOS | Windows |
|---|---|---|
| **Cmd** | ⌘ (hold) | Ctrl (hold) |
| **Copy / Cut / Paste** | ⌘C / ⌘X / ⌘V | Ctrl C / X / V |
| **W< / W>** (word move) | ⌥← / ⌥→ | Ctrl← / Ctrl→ |
| **DelWrd** | ⌥⌫ | Ctrl⌫ |
| **DelLn** | ⌘⌫ | Home, ⇧End, ⌫ |
| **AltTab** | ⌘Tab | Alt+Tab |
| **~ → ñ** | dead `~`, then `n` | AltGr + `n` |
| **WM layer** | — (built for FancyWM on Windows) | taps Alt+Win, then a key |

Everything else in the smart tilde is OS‑independent (US‑International dead keys).

---

## Smart tilde

The `~` key (right home outer) and a double‑tap of **Cmd / ~** arm a one‑shot
dead key. The next key decides:

| Next key | Output |
|---|---|
| `a e i o u` | `á é í ó ú` |
| `n` | `ñ` |
| `s l m d r t c` | straight `'` + that letter (`McDonald's`, `I'll`, `c'mon`) |
| space | a lone `'` |
| anything else | the tilde is dropped, the key types normally |

Assumes a **US‑International** OS layout. A modifier pressed between `~` and the
target passes through, so `~` → Shift → vowel gives an uppercase accent. The latch
also expires after ~1 s.

---

## RGB

PaletteFx (`getreuer/palettefx`, wired via `keymap.json` + `rgb_matrix_user.inc`).
`config.h` sets `RGB_MATRIX_KEYPRESSES`, default mode
`RGB_MATRIX_CUSTOM_PALETTEFX_REACTIVE`, default hue `RGB_MATRIX_HUE_STEP * 9`
(palette 9 = Polarized). `keyboard_post_init_user()` re‑forces mode + palette with
`*_noeeprom` on **every plug‑in** (the EEPROM otherwise keeps a stale mode).

| Layer | RGB |
|---|---|
| bases (`_ALPHA` / `_CRATE` / `_CANARIA`), `_GAME`, `_WM` | PaletteFx Reactive animation |
| `_NAV` | per‑key by function — numpad **blue**, arrows **red**, word/page nav **green**, delete **orange**, clipboard **purple**, media **yellow**, `SELWORD` **cyan**, one‑shot mods **white** |
| `_SYM` | flat **green** |
| `_FUNCTION` | flat **yellow** |
| `_ADJUST` | flat **white** |
| `_MOUSE` | flat **magenta** |
| `_WMSEL` | held cluster **white**, available desktops **green**, one‑shot Shift **blue** |

Notification flashes over any layer: OS switch → **green ×2**; Caps Lock / Caps
Word → **red ×3**.

Cycle at runtime with the RGB row on `_ADJUST` — `RM_NEXT/PREV` for the effect,
`RM_HUEU/HUED` for the palette.

---

## Building & flashing

QMK **userspace** overlay — needs a sibling `qmk_firmware` + the `qmk` CLI. Build
from the **QMK MSYS** terminal.

```
# left half (TFT display module)
qmk compile -kb splitkb/halcyon/kyria/rev4 -km isaacsa51 -e HLC_TFT_DISPLAY=1 -e TARGET=kyria_display

# right half (Cirque trackpad module)
qmk compile -kb splitkb/halcyon/kyria/rev4 -km isaacsa51 -e HLC_CIRQUE_TRACKPAD=1 -e TARGET=kyria_cirque
```

`TARGET` just names the output `.uf2`. The module flag (`HLC_TFT_DISPLAY` /
`HLC_CIRQUE_TRACKPAD` / `HLC_ENCODER` / `HLC_NONE`) is what selects the per‑half
build.

Flash: double‑tap reset → the `RPI-RP2` drive mounts → drop the matching `.uf2`,
once per half. Handedness is automatic (GP24 pin) — flash the same handedness
build to both sides.

If a fresh build ignores `RGB_MATRIX_DEFAULT_*`, reset EEPROM once (hold `EE_CLR`
while plugging in, or flash and bootloader‑reset).
