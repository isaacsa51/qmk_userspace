// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later
// Adapted for the isaacsa51 keymap.

#include "keycode_strings.h"
#include "../../layers.h"
#include "../../custom_keys/custom_keys.h"

const char* get_keycode_string_hlc(uint16_t keycode) {
    // Show the tapped key for home-row mods / mod-taps (HM_A, LSA_T(KC_SPC), ...)
    if (IS_QK_MOD_TAP(keycode)) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }
    // Show the base key for modded keycodes (A(KC_SPC), A(KC_1), A(KC_LEFT), ...)
    if (IS_QK_MODS(keycode)) {
        keycode &= 0xFF;
    }

    switch (keycode) {
        // Letters
        case KC_A: return "A"; case KC_B: return "B"; case KC_C: return "C";
        case KC_D: return "D"; case KC_E: return "E"; case KC_F: return "F";
        case KC_G: return "G"; case KC_H: return "H"; case KC_I: return "I";
        case KC_J: return "J"; case KC_K: return "K"; case KC_L: return "L";
        case KC_M: return "M"; case KC_N: return "N"; case KC_O: return "O";
        case KC_P: return "P"; case KC_Q: return "Q"; case KC_R: return "R";
        case KC_S: return "S"; case KC_T: return "T"; case KC_U: return "U";
        case KC_V: return "V"; case KC_W: return "W"; case KC_X: return "X";
        case KC_Y: return "Y"; case KC_Z: return "Z";

        // Digits
        case KC_0: return "0"; case KC_1: return "1"; case KC_2: return "2";
        case KC_3: return "3"; case KC_4: return "4"; case KC_5: return "5";
        case KC_6: return "6"; case KC_7: return "7"; case KC_8: return "8";
        case KC_9: return "9";

        // Function keys
        case KC_F1: return "F1";   case KC_F2: return "F2";   case KC_F3: return "F3";
        case KC_F4: return "F4";   case KC_F5: return "F5";   case KC_F6: return "F6";
        case KC_F7: return "F7";   case KC_F8: return "F8";   case KC_F9: return "F9";
        case KC_F10: return "F10"; case KC_F11: return "F11"; case KC_F12: return "F12";

        // Modifiers (plain)
        case KC_LCTL: case KC_RCTL: return "CTL";
        case KC_LSFT: case KC_RSFT: return "SFT";
        case KC_LALT: case KC_RALT: return "ALT";
        case KC_LGUI: case KC_RGUI: return "GUI";
        case KC_MEH:  return "MEH";
        case KC_HYPR: return "HYP";

        // Common keys
        case KC_TAB:  return "TAB";
        case KC_ESC:  return "ESC";
        case KC_ENT:  return "ENT";
        case KC_BSPC: return "BSP";
        case KC_SPC:  return "SPC";
        case KC_DEL:  return "DEL";
        case KC_INS:  return "INS";
        case KC_HOME: return "HOME";
        case KC_END:  return "END";
        case KC_PGUP: return "PGUP";
        case KC_PGDN: return "PGDN";
        case KC_PSCR: return "PSCR";
        case KC_PAUS: return "PAUS";

        // Arrows
        case KC_LEFT: return "<"; case KC_RGHT: return ">";
        case KC_UP:   return "^"; case KC_DOWN: return "v";

        // Punctuation / symbols
        case KC_COMM: return ","; case KC_DOT: return ".";  case KC_SLSH: return "/";
        case KC_SCLN: return ";"; case KC_QUOT: return "'"; case KC_GRV:  return "`";
        case KC_TILD: return "~"; case KC_EXLM: return "!"; case KC_AT:   return "@";
        case KC_HASH: return "#"; case KC_DLR:  return "$"; case KC_PERC: return "%";
        case KC_CIRC: return "^"; case KC_AMPR: return "&"; case KC_ASTR: return "*";
        case KC_LPRN: return "("; case KC_RPRN: return ")"; case KC_UNDS: return "_";
        case KC_PLUS: return "+"; case KC_EQL:  return "="; case KC_MINS: return "-";
        case KC_LBRC: return "["; case KC_RBRC: return "]"; case KC_LCBR: return "{";
        case KC_RCBR: return "}"; case KC_LABK: return "<"; case KC_RABK: return ">";
        case KC_PIPE: return "|"; case KC_BSLS: return "\\"; case KC_COLN: return ":";
        case KC_QUES: return "?";

        // Media / volume
        case KC_MUTE: return "MUTE"; case KC_VOLU: return "VOL+"; case KC_VOLD: return "VOL-";
        case KC_MPLY: return "PLAY"; case KC_MPRV: return "PREV"; case KC_MNXT: return "NEXT";

        // Mouse keys (_MOUSE layer)
        case MS_UP: return "M^"; case MS_DOWN: return "Mv"; case MS_LEFT: return "M<"; case MS_RGHT: return "M>";
        case MS_WHLU: return "WU"; case MS_WHLD: return "WD"; case MS_WHLL: return "WL"; case MS_WHLR: return "WR";
        case MS_BTN1: return "LMB"; case MS_BTN2: return "RMB"; case MS_BTN3: return "MMB";

        // RGB matrix
        case RM_TOGG: return "TOG"; case RM_NEXT: return "RM>"; case RM_PREV: return "RM<";
        case RM_HUEU: return "H+";  case RM_HUED: return "H-";
        case RM_SATU: return "S+";  case RM_SATD: return "S-";
        case RM_VALU: return "V+";  case RM_VALD: return "V-";

        // Transparent / no-op
        case KC_NO: case KC_TRNS: return "";

        // isaacsa51 custom keycodes
        case TILDE:   return "~";
        case TG_OS:   return "OS";
        case CMD:     return "CMD";
        case U_WORDL: return "W<";
        case U_WORDR: return "W>";
        case U_DWORD: return "DWD";
        case U_DLINE: return "DLN";
        case U_COPY:  return "CPY";
        case U_CUT:   return "CUT";
        case U_PASTE: return "PST";
        case ALTTAB:  return "ATB";
        case SELWORD: return "SELW";

        // FancyWM
        case WM_L: return "<";  case WM_R: return ">";  case WM_U: return "^";  case WM_D: return "v";
        case WM_MOVE: return "MOV"; case WM_SWAP: return "SWP";
        case WM_PANH: return "PNH"; case WM_PANV: return "PNV"; case WM_PANS: return "PNS";
        case WM_FLOAT: return "FLT"; case WM_PROMO: return "PRO"; case WM_REFR: return "RFR";
        case WM_TOGL: return "TGL"; case WM_SHDSK: return "DSK"; case WM_CANC: return "ESC";
        case WM_DPRV: return "D~"; case WM_DL: return "D<"; case WM_DR: return "D>";
        case WM_1: return "D1"; case WM_2: return "D2"; case WM_3: return "D3";
        case WM_4: return "D4"; case WM_5: return "D5"; case WM_6: return "D6";
        case WM_7: return "D7"; case WM_8: return "D8"; case WM_9: return "D9";

        // One-shot mods
        case OSM(MOD_LSFT): return "OSF";
        case OSM(MOD_LALT): return "OAL";
        case OSM(MOD_LCTL): return "OCT";

        // Tap dances
        case TD(TD_CMD_TILDE): return "CMD";
        case TD(TD_OSHTSF):    return "SF*";
        case TD(TD_OSHTCT):    return "CT*";
        case TD(TD_CAPS):      return "CAPS";

        // Layer switches
        case DF(_ALPHA):    return "ALPH";
        case DF(_CANARIA):  return "CANA";
        case DF(_CRATE):    return "CRAT";
        case TG(_GAME):     return "GAME";
        case TT(_SYM):      return "SYM";
        case TT(_NAV):      return "NAV";
        case TT(_FUNCTION): return "FN";
        case TT(_ADJUST):   return "ADJ";
        case TT(_WM):       return "WM";
        case MO(_MOUSE):    return "MOU";
        case TO(_ALPHA):    return "BASE";

        default: return "-";
    }
}
