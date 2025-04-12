ENCODER_MAP_ENABLE = no

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules

# This adds custom functionality from keymaps
SRC += custom_keys/custom_keys.c
SRC += os_detection/os_layer.c
SRC += combos/combos.c
# Enable combos
COMBO_ENABLE = yes

LAYER_LOCK_ENABLE = yes