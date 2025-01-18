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

#pragma once

#include "action_layer.h"
#include "process_tap_dance.h"

typedef struct {
    layer_state_t layer_state_immediate;
    layer_state_t layer_state_timeout;
    uint16_t *mods;
} tap_dance_mod_t;

#define ACTION_TAP_DANCE_MODIFIER(_state_immediate, _state_timeout, ...) \
    { \
        .fn = { \
            tap_dance_mod_on_each_tap, \
            tap_dance_mod_on_finished, \
            tap_dance_mod_on_reset, \
            tap_dance_mod_on_each_release \
        }, \
        .user_data = (void *)&((tap_dance_mod_t) { \
            .layer_state_immediate = (layer_state_t)(_state_immediate), \
            .layer_state_timeout = (layer_state_t)(_state_timeout), \
            .mods = (uint16_t[]) { __VA_ARGS__, UINT16_MAX } \
        }) \
    }

#define ACTION_TAP_DANCE_MODIFIER_MO(_state_timeout, ...) \
    { \
        .fn = { \
            tap_dance_mod_on_each_tap, \
            tap_dance_mod_on_finished, \
            tap_dance_mod_on_reset, \
            tap_dance_mod_on_each_release \
        }, \
        .user_data = (void *)&((tap_dance_mod_t) { \
            .layer_state_immediate = (layer_state_t)0, \
            .layer_state_timeout = (layer_state_t)(_state_timeout), \
            .mods = (uint16_t[]) { __VA_ARGS__, UINT16_MAX } \
        }) \
    }

void tap_dance_mod_on_each_tap(tap_dance_state_t *state, void *user_data);
void tap_dance_mod_on_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_mod_on_reset(tap_dance_state_t *state, void *user_data);
void tap_dance_mod_on_each_release(tap_dance_state_t *state, void *user_data);
