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

#include "matrix.h"
#include "atomic_util.h"
#include "gpio.h"
#include "wait.h"


#ifndef SR_INPUT_DELAY
#    define SR_INPUT_DELAY (CPU_CLOCK / 1000000L / 4 * 7)
#endif

#define waitSrDelay() wait_cpuclock(SR_INPUT_DELAY)

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

#ifdef MATRIX_ROW_PINS
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static const pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

static const pin_t ds_pin = A7;
static const pin_t shcp_pin = B1;
static const pin_t stcp_pin = B0;

static inline void gpio_atomic_set_pin_output_low(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void gpio_atomic_set_pin_output_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_high(pin);
    }
}

static inline void gpio_atomic_set_pin_input_high(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_input_high(pin);
    }
}

static inline void gpio_atomic_sr_output_pulse(void) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(shcp_pin);
        gpio_set_pin_output(stcp_pin);

        gpio_write_pin_high(shcp_pin);
        gpio_write_pin_high(stcp_pin);
        gpio_write_pin_low(shcp_pin);
        gpio_write_pin_low(stcp_pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (gpio_read_pin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        gpio_atomic_set_pin_output_low(pin);
    }
    return true;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        gpio_atomic_set_pin_output_high(pin);
#else
        gpio_atomic_set_pin_input_high(pin);
#endif
    }

    if (col == MATRIX_ORDINARY_COLS - 1) {
        gpio_atomic_set_pin_output_low(ds_pin);
    } else if (col == MATRIX_ORDINARY_COLS) {
        gpio_atomic_set_pin_output_high(ds_pin);
    }

    gpio_atomic_sr_output_pulse();
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col(x);
    }
}

void matrix_init_pins(void) {
    gpio_atomic_set_pin_output_low(shcp_pin);
    gpio_atomic_set_pin_output_low(stcp_pin);

    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            gpio_atomic_set_pin_input_high(row_pins[x]);
        }
    }
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    if (line < MATRIX_ORDINARY_COLS) {
        return;
    }

    waitSrDelay();
}

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Check row pin state
        if (readMatrixPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}
