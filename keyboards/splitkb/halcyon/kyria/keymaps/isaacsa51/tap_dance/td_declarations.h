#pragma once

#include QMK_KEYBOARD_H

void dance_cmd_finished(tap_dance_state_t *state, void *user_data);
void dance_cmd_reset(tap_dance_state_t *state, void *user_data);

extern bool awaiting_smart_tilde;
extern uint32_t smart_tilde_timer;
extern uint8_t current_os;

void td_caps_finished(tap_dance_state_t *state, void *user_data);
void td_caps_reset(tap_dance_state_t *state, void *user_data);