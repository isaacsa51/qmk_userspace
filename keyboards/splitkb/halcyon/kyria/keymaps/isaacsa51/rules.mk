ENCODER_MAP_ENABLE = no

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules

# This adds custom functionality from keymaps
SRC += custom_keys/custom_keys.c
SRC += os_detection/os_layer.c
SRC += tap_dance/td_declarations.c

# combos/combos.c defines key_combos[]; QMK's keymap introspection needs that
# array's real definition (not just a declaration) in scope to size it, so it's
# pulled in via textual #include rather than compiled as its own translation
# unit. Do NOT also add it to SRC — see quantum/keymap_introspection.c.
INTROSPECTION_KEYMAP_C = combos/combos.c

# On-display keymap renderer (only meaningful with the TFT module)
ifeq ($(strip $(HLC_TFT_DISPLAY)), 1)
    SRC += display/hook.c
    SRC += display/utils.c
    SRC += display/keymap/keycode_strings.c
    SRC += display/keymap/draw_keymap.c
    SRC += display/keymap/process_keymap.c

    SRC += display/fonts/3x5.qff.c
    SRC += display/fonts/4x7.qff.c
    SRC += display/fonts/5x7.qff.c
    SRC += display/fonts/9x12.qff.c

    SRC += display/images/icons/backspace.qgf.c
    SRC += display/images/icons/tab.qgf.c
    SRC += display/images/icons/space.qgf.c
    SRC += display/images/icons/shift.qgf.c
    SRC += display/images/icons/enter.qgf.c
    SRC += display/images/icons/lock.qgf.c
    SRC += display/images/icons/mute.qgf.c
    SRC += display/images/icons/volume_down.qgf.c
    SRC += display/images/icons/volume_up.qgf.c
endif

# Enable combos
COMBO_ENABLE = yes

LAYER_LOCK_ENABLE = yes

POINTING_DEVICE_ENABLE = yes

# MS_* keycodes for the _MOUSE layer (cursor / wheel / buttons)
MOUSEKEY_ENABLE = yes

TAP_DANCE_ENABLE = yes

CAPS_WORD_ENABLE = yes
