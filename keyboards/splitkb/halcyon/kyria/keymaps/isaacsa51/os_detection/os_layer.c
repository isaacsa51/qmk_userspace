#include "os_layer.h"
#include "eeconfig.h"

uint8_t current_os = OS_WIN;

// Runs once on a fresh/reset EEPROM (factory default, or after EE_CLR) to seed
// the persisted value with the same default as the current_os initializer above.
void eeconfig_init_user(void) {
    eeconfig_update_user(OS_WIN);
}

void os_layer_init(void) {
    current_os = (uint8_t)eeconfig_read_user();
}

void os_layer_save(void) {
    eeconfig_update_user(current_os);
}
