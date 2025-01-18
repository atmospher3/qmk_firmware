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

#include "process_dual_space.h"
#include "keycodes_user.h"
#include "modifiers.h"
#include "action_util.h"

static bool lspace_was_shifted = false;
static bool rspace_was_shifted = false;

bool process_dual_space(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_USER_LEFT_SPACE: {
            const uint8_t mods    = get_mods();
            uint8_t       shifted = mods & MOD_MASK_SHIFT;

            if (record->event.pressed) {
                lspace_was_shifted = shifted;
                add_key(shifted ? KC_LEFT_BRACKET : KC_SPACE);
            } else {
                del_key(lspace_was_shifted ? KC_LEFT_BRACKET : KC_SPACE);
            }

            send_keyboard_report();
        }
        return false;

        case QK_USER_RIGHT_SPACE: {
            const uint8_t mods    = get_mods();
            uint8_t       shifted = mods & MOD_MASK_SHIFT;

            if (record->event.pressed) {
                rspace_was_shifted = shifted;
                add_key(shifted ? KC_RIGHT_BRACKET : KC_SPACE);
            } else {
                del_key(rspace_was_shifted ? KC_RIGHT_BRACKET : KC_SPACE);
            }

            send_keyboard_report();
        }
        return false;
    }

    return true;
}
