#pragma once

#include <stdint.h>

enum os_modes {
    OS_MAC,
    OS_WIN,
};

extern uint8_t current_os;

// Restores current_os from EEPROM. Call once from keyboard_post_init_user().
void os_layer_init(void);

// Persists current_os so it survives a replug. Call after toggling it.
void os_layer_save(void);
