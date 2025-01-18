/* Copyright 2025 atmospher3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <lib/lib8tion/lib8tion.h>
#include "keycodes_user.h"
#include "process_dual_space.h"
#include "process_grave_b.h"
#include "tap_dance_extra.h"
#include "usb_device_state.h"

// clang-format off

enum user_layer_defines {
    BASE,
    GAME,
    ALT,
    NAV,
    GN,
    CFG,

    LAYER_MAX,

    LAYER_STATE_BASE = 1 << BASE,
    LAYER_STATE_GAME = 1 << GAME,
    LAYER_STATE_ALT  = 1 << ALT,
    LAYER_STATE_NAV  = 1 << NAV,
    LAYER_STATE_GN   = 1 << GN,
    LAYER_STATE_CFG  = 1 << CFG,
};

enum tap_dance_defines {
    LCTL,
    LSFT,
    LALT,
    FN,
    CAPS,

    TAP_DANCE_MAX,

    TD_LCTL = TD(LCTL),
    TD_LSFT = TD(LSFT),
    TD_LALT = TD(LALT),
    TD_FN   = TD(FN),
    TD_CAPS = TD(CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        XXXXXXX,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        XXXXXXX,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        XXXXXXX,  TD_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        XXXXXXX,  TD_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      USR_GB,   KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  TD_CAPS,  KC_UP,
        XXXXXXX,  TD_LALT,  MO(CFG),            KC_LGUI,  USR_LSPC, TD_FN,                         USR_RSPC,           KC_RGUI,                      KC_LEFT,  KC_DOWN,  KC_RGHT),

    [GAME] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        XXXXXXX,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        XXXXXXX,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        XXXXXXX,  KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        XXXXXXX,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      USR_GB,   KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  TD_CAPS,  KC_UP,
        XXXXXXX,  KC_LALT,  MO(CFG),            KC_LGUI,  USR_LSPC, TD_FN,                         USR_RSPC,           KC_RGUI,                      KC_LEFT,  KC_DOWN,  KC_RGHT),

    [ALT] = LAYOUT_ansi_89(
        _______,  _______,  KC_BRID,  KC_BRIU,  XXXXXXX,  XXXXXXX,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  KC_DEL,   KC_INS,   _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [NAV] = LAYOUT_ansi_89(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  KC_ESC,   _______,  KC_PSCR,  _______,  _______,  KC_HOME,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_END,   _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       KC_BSPC,            KC_APP,                       _______,  _______,  _______),

    [GN] = LAYOUT_ansi_89(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [CFG] = LAYOUT_ansi_89(
        _______,  QK_BOOT,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  EE_CLR,             _______,
        _______,  RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  RM_PREV,  RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   QK_BOOT,  QK_BOOT,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

/*
    [] = LAYOUT_ansi_89(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),
*/
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [GAME] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [ALT]  = { ENCODER_CCW_CW(_______, _______) },
    [NAV]  = { ENCODER_CCW_CW(_______, _______) },
    [GN]   = { ENCODER_CCW_CW(_______, _______) },
    [CFG]  = { ENCODER_CCW_CW(_______, _______) },
};

const uint16_t PROGMEM dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES] = {
    DIP_SWITCH_OFF_ON(DF(BASE), DF(GAME)),
};

const uint8_t PROGMEM color_map[][3] = {
    [BASE] = { RGB_OFF },
    [GAME] = { RGB_OFF },
    [ALT]  = { RGB_TEAL },
    [NAV]  = { RGB_WHITE },
    [GN]   = { RGB_MAGENTA },
    [CFG]  = { RGB_RED }
};

tap_dance_action_t tap_dance_actions[] = {
    [LCTL] = ACTION_TAP_DANCE_MODIFIER_MO(LAYER_STATE_ALT, MOD_BIT_LCTRL, MOD_BIT_LSHIFT, MOD_BIT_LALT),
    [LSFT] = ACTION_TAP_DANCE_MODIFIER_MO(LAYER_STATE_ALT, MOD_BIT_LSHIFT, MOD_BIT_LALT, MOD_BIT_LCTRL),
    [LALT] = ACTION_TAP_DANCE_MODIFIER_MO(LAYER_STATE_ALT, MOD_BIT_LALT, MOD_BIT_LCTRL, MOD_BIT_LSHIFT),
    [FN]   = ACTION_TAP_DANCE_MODIFIER(LAYER_STATE_ALT | LAYER_STATE_NAV, LAYER_STATE_GN, 0, MOD_BIT_LSHIFT),
    [CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(
        process_dual_space(keycode, record) &&
        process_grave_b(keycode, record) &&
        true
    )) {
        return false;
    }

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t mods       = get_mods();
    uint8_t       controlled = mods & MOD_MASK_CTRL;
    uint8_t       shifted    = mods & MOD_MASK_SHIFT;
    uint8_t       altered    = mods & MOD_MASK_ALT;

    keypos_t key;
    for (key.row = 0; key.row < MATRIX_ROWS; ++key.row) {
        for (key.col = 0; key.col < MATRIX_COLS; ++key.col) {
            uint8_t index = g_led_config.matrix_co[key.row][key.col];
            if (index < led_min || index >= led_max) {
                continue;
            }

            RGB rgb = { 0, 0, 0 };
            uint8_t override = !HAS_ANY_FLAGS(g_led_config.flags[index], rgb_matrix_get_flags());
            for (uint8_t layer = 0; layer < LAYER_MAX; ++layer) {
                if (IS_LAYER_OFF_STATE(layer_state | default_layer_state, layer)) {
                    continue;
                }

                switch (keymap_key_to_keycode(layer, key)) {
                    case TD_FN: if (usb_device_state_get_protocol() == USB_PROTOCOL_REPORT) {
                        uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));

                        HSV hsv = rgb_matrix_config.hsv;
                        hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);

                        rgb = hsv_to_rgb(hsv);
                        override |= true;
                    } else {
                        rgb = (RGB){ RGB_RED };
                        override |= true;
                    }
                    break;

                    case KC_LCTL:
                    case TD_LCTL: if (controlled) {
                        rgb = (RGB){ 0, 255, 128 };
                        override |= true;
                    }
                    break;

                    case KC_LSFT:
                    case TD_LSFT: if (shifted) {
                        rgb = (RGB){ 0, 255, 128 };
                        override |= true;
                    }
                    break;

                    case KC_LALT:
                    case TD_LALT: if (altered) {
                        rgb = (RGB){ 0, 255, 128 };
                        override |= true;
                    }
                    break;

                    case KC_CAPS:
                    case TD_CAPS: if (host_keyboard_led_state().caps_lock) {
                        rgb = (RGB){ RGB_WHITE };
                        override |= true;
                    }
                    break;

                    case NK_TOGG: if (keymap_config.nkro) {
                        rgb = (RGB){ RGB_WHITE };
                        override |= true;
                    }
                    break;

                    case KC_TRANSPARENT:
                    break;

                    default: {
                        uint8_t r, g, b;
                        r = pgm_read_byte(&color_map[layer][0]);
                        g = pgm_read_byte(&color_map[layer][1]);
                        b = pgm_read_byte(&color_map[layer][2]);

                        if (r || g || b) {
                            rgb = (RGB){ r, g, b };
                            override |= true;
                        }
                    }
                }
            }

            if (override) {
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }

    return false;
}
