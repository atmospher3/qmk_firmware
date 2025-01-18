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

#include "tap_dance_extra.h"

void tap_dance_mod_on_each_tap(tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_t *m = (tap_dance_mod_t *)user_data;

    if (state->count == 1 && m->layer_state_immediate) {
        layer_xor(m->layer_state_immediate);
    }

    register_mods(m->mods[state->count - 1]);
}

void tap_dance_mod_on_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_t *m = (tap_dance_mod_t *)user_data;

    if (!state->interrupted && m->layer_state_timeout) {
        layer_xor(m->layer_state_timeout);
    }
}

void tap_dance_mod_on_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_t *m = (tap_dance_mod_t *)user_data;

    if (!state->interrupted && m->layer_state_timeout && state->finished) {
        layer_xor(m->layer_state_timeout);
    }

    for (uint8_t i = state->count; i > 0; --i) {
        unregister_mods(m->mods[i - 1]);
    }

    if (m->layer_state_immediate) {
        layer_xor(m->layer_state_immediate);
    }
}

void tap_dance_mod_on_each_release(tap_dance_state_t *state, void *user_data) {
    tap_dance_mod_t *m = (tap_dance_mod_t *)user_data;

    if (m->mods[state->count] == UINT16_MAX) {
        reset_tap_dance(state);
    }
}
