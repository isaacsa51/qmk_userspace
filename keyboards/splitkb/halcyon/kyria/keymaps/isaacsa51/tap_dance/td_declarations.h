#pragma once

#include QMK_KEYBOARD_H

void dance_cmd_finished(tap_dance_state_t *state, void *user_data);
void dance_cmd_reset(tap_dance_state_t *state, void *user_data);

extern bool awaiting_smart_tilde;
extern uint8_t current_os;

void oshtsf_finished(tap_dance_state_t *state, void *user_data);
void oshtsf_reset(tap_dance_state_t *state, void *user_data);
void oshtct_finished(tap_dance_state_t *state, void *user_data);
void oshtct_reset(tap_dance_state_t *state, void *user_data);
void td_caps_finished(tap_dance_state_t *state, void *user_data);
void td_caps_reset(tap_dance_state_t *state, void *user_data);