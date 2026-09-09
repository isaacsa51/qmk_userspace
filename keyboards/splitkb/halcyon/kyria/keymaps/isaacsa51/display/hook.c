// Draws the current layer's key grid on the Halcyon TFT.
//
// The stock hlc_tft_display module calls this weak hook from
// display_module_housekeeping_task_kb() and does nothing more if it returns
// false. We take that over: draw the keymap ourselves, flush, return false.
// (Same pattern the AnythingFromScrap fork uses in display/controller.c.)

#include "quantum.h"
#include "qp.h"
#include "qp_surface.h"
#include "keymap/process_keymap.h"

// Provided by users/halcyon_modules/splitkb/hlc_tft_display.c
extern painter_device_t lcd;
extern painter_device_t lcd_surface;

bool display_module_housekeeping_task_user(bool second_display) {
#ifndef HLC_TFT_DISPLAY
    return true;
#else
    // Kyria rev4 has a single display; the second one never exists here.
    if (second_display) return true;

    // process_keymap_display() only redraws on a layer change, so this is cheap.
    if (process_keymap_display(lcd_surface)) {
        qp_surface_draw(lcd_surface, lcd, 0, 0, false);
        qp_flush(lcd);
    }

    // false -> stock module skips its own layer-number / caps-num-scroll screen.
    return false;
#endif
}
