/*
 * Copyright 2022 Florian Brandner
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
 *
 *************************************************
 * Keymap for the Sofle RGB, based on the design made by Dane Evans
 */


#include <stdio.h>
#include "config.h"
#include "keymap_us_international.h"
#include "sendstring_us_international.h"

#include QMK_KEYBOARD_H

#define MIN_ANIM_SPEED      10            // WPM Threshold for walk anim
#define SPRITE_DURATION     500           // Length in ms for a sprite
#define SPRITE_SIZE         320           // Size of one sprite in byte

enum layers {
    _DEFAULT = 0,
    _QWERTY = 0,
    _LOWER,
    _RAISE,
};

/**************************************************** CUSTOM KEYCODES */

// enum custom_keycodes {
//     ESIGN = SAFE_RANGE,
//     BRK_L1,
//     BRK_R1,
//     BRK_L2,
//     BRK_R2
// };

/**************************************************** TAP DANCES */

enum {
    TD_ESC_GRV,
    TD_SHIFT_CAPS,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_GRV]   = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),     // ESC -> GRV on double tap
  [TD_SHIFT_CAPS]   = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),     // SHIFT -> CAPSLOCK on double tap
};

/**************************************************** THE LAYERS */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,---------------------------------------------------.                     ,-----------------------------------------------------.
    TD(TD_ESC_GRV),KC_1,  KC_2,   KC_3,   KC_4,  KC_5,                          KC_6,    KC_7,     KC_8,    KC_9,  KC_0,  KC_BSPC,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    KC_TAB, KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,   KC_ENT,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    TD(TD_SHIFT_CAPS), KC_A,    KC_S,     KC_D,   KC_F,    KC_G,                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_MUTE,    KC_MPLY, KC_COMM,  KC_N,    KC_M,    KC_DOT,  KC_SLSH, KC_RSFT,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
                      KC_LCTL, KC_LALT, MO(_LOWER), KC_LCMD, KC_SPC,     MO(_RAISE),KC_RCMD,KC_RALT,KC_LBRC, KC_RBRC
  //                \--------+--------+--------+--------+---------|   |-------+--------+--------+--------+-------/
),
  [_RAISE] = LAYOUT(
  //,---------------------------------------------------.                     ,-----------------------------------------------------.
    KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                       _______, _______, _______, KC_MINS, KC_EQL,  KC_F12,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    _______, _______, KC_UP, _______, _______, _______,                         _______ ,_______, _______, _______, _______, _______,
  //|------+---------+--------+--------+--------+--------|  =====  |   |  ===  |--------+--------+--------+--------+--------+--------|
    _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,  _______,    _______,  _______,  _______, _______, _______, _______, _______,
  //|------+--------+--------+--------+--------+--------|  =====  |   |  ===  |--------+--------+--------+--------+--------+--------|
                      _______, _______, _______, _______,  _______,    _______, _______, _______, _______, _______
  //                \--------+--------+--------+--------+---------|   |-------+--------+--------+--------+-------/
),
  //,---------------------------------------------------.                     ,-----------------------------------------------------.
  [_LOWER] = LAYOUT(
    KC_GRV, _______, _______, _______, _______, QK_BOOT,                       _______, _______, _______, _______, _______, KC_DEL,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    _______, UG_TOGG, UG_NEXT, _______, UG_SPDD, UG_SPDU,                       _______, _______, KC_UP  , _______, _______, _______,
  //|------+--------+--------+--------+--------+--------|                     |--------+--------+--------+--------+--------+--------|
    KC_CAPS, _______  , KC_UP, _______, _______, _______,                       _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______,
  //|------+--------+--------+--------+--------+--------|  =====  |   |  ===  |--------+--------+--------+--------+--------+--------|
    _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|------+--------+--------+--------+--------+--------|  =====  |   |  ===  |--------+--------+--------+--------+--------+--------|
                      _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //                \--------+--------+--------+--------+---------|   |-------+--------+--------+--------+-------/
),
};

// clang-format on

/**************************************************** KEYCODE PROCESSING */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
};

/**************************************************** THE ENCODER */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {           // First encoder (Left Side)
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) {    // Second encoder (Right Side)
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  }
  return true;
}
#endif // ENCODER_ENABLE

/**************************************************** OLEDs */
#ifdef OLED_ENABLE
static uint32_t sleep_timer;

#ifdef IS_LEFT
static uint32_t   text_offset = 0;
static uint32_t   text_anim_timer = 0;
static const char PROGMEM text[20] = "mark@sofle         ";

#define FRAME_DURATION 750
static void print_left(void) {

  // Note: Do not use snprintf, it needs too much flash

  // OLED Sleep Mode
  if (get_current_wpm() > 0) {
    oled_on();
    sleep_timer = timer_read32();
  } else if (timer_elapsed32(sleep_timer) > OLED_TIMEOUT) {
    oled_off();
  }

  if (is_oled_on()) {
    if (timer_elapsed32(text_anim_timer) > FRAME_DURATION) {
        text_anim_timer = timer_read32();
        text_offset += 1;
    }

    oled_write_P(PSTR("\n-----"), false);

    for (int i = 0; i < 5; i++) {
        uint8_t index = (text_offset + i) % 15;
        oled_write_char(pgm_read_byte(&text[index]), false);
    };

    oled_write("\n", false);

    oled_write_P(PSTR("-----\n\n\n"), false);

    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    oled_set_cursor(0, 15);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
  } // is_oled_on
} // print_left()

#else // IS_LEFT

#ifdef WPM_ENABLE
static uint32_t anim_timer = 0;       // animation timer
static uint8_t current_frame = 0;     // current frame

static void render_bongo(int PosX, int PosY) {
    static const char PROGMEM cat_tap[2][320] = {
        {
            0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0x7c, 0x70, 0x40, 0x40, 0x61, 0x5e, 0x80, 0xc0, 0xbc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0f, 0x3f, 0xf8, 0xf0, 0xf0, 0x20, 0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1e, 0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19, 0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
        },
        {0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f, 0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80, 0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05, 0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x07, 0x03, 0x0f, 0x3f, 0xff, 0x03, 0x01, 0x03, 0x07, 0x18, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf3, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80, 0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01},
    };

  // Animate
  if (timer_elapsed32(anim_timer) > SPRITE_DURATION) {
    anim_timer = timer_read32();

    oled_set_cursor(PosX, PosY);

    if (get_current_wpm() >= MIN_ANIM_SPEED) {
      current_frame = (current_frame + 1) % 2;
    }
    oled_write_raw_P(cat_tap[current_frame], SPRITE_SIZE);
  }
}
#endif  // WPM_ENABLE

extern oled_rotation_t oled_rotation;

static void print_right(void) {

  if (get_current_wpm() > 0) {
    oled_on();
    sleep_timer = timer_read32();
  } else if (timer_elapsed32(sleep_timer) > OLED_TIMEOUT) {
    oled_off();
  }

  if (is_oled_on()) {
    if (oled_rotation != OLED_ROTATION_270) oled_init(OLED_ROTATION_270);  // Orientation for status
#ifdef WPM_ENABLE

    oled_set_cursor(0, 1);

    int  wpm = get_current_wpm();
    char wpm_str[4];

    wpm_str[3] = '\0';
    wpm_str[2] = '0' + wpm % 10;
    wpm_str[1] = '0' + (wpm /= 10) % 10;
    wpm_str[0] = '0' + wpm / 10;

    oled_set_cursor(0, 12);
    oled_write(wpm_str, false);
    oled_set_cursor(0, 13);
    oled_write("  wpm", false);
    render_bongo(0, 0);
#endif
  } // is_oled_on
} // print_right()
#endif

bool oled_task_user(void) {
#ifdef IS_LEFT
  print_left();
#else
  print_right();
#endif
  return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef IS_LEFT
  return OLED_ROTATION_270;
#endif
  // Orientation of slave is handled in the display function
  return rotation;
}
#endif // OLED_ENABLE


// /**************************************************** RGB Light Layers */
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  return true;
}
#endif // RGB_MATRIX_ENABLE
