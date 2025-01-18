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

#include "process_grave_b.h"
#include "keycodes_user.h"
#include "modifiers.h"
#include "action_util.h"

static bool grave_b_was_shifted = false;

bool process_grave_b(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_USER_GRAVE_B) {
        const uint8_t mods    = get_mods();
        uint8_t       shifted = mods & MOD_MASK_CS;

        if (record->event.pressed) {
            grave_b_was_shifted = shifted;
            add_key(shifted ? KC_GRAVE : KC_B);
        } else {
            del_key(grave_b_was_shifted ? KC_GRAVE : KC_B);
        }

        send_keyboard_report();
        return false;
    }

    return true;
}
