#include QMK_KEYBOARD_H
#include <stdio.h>

enum sofle_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
};

#define LSFT_CAPS LSFT_T(KC_CAPS)
#define RSFT_ENT RSFT_T(KC_ENT)
#define RAISE_UP LT(_RAISE, KC_UP)
#define LOCKSCREEN LCTL(LSFT(KC_POWER))

#ifdef ENCODER_ENABLE
#include "encoders.h"
#endif

#ifdef OLED_DRIVER_ENABLE
#include "screens.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// DEFAULT LAYER
[_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC, \
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  LSFT_CAPS,KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  LOCKSCREEN,     KC_MUTE,KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RSFT_ENT, \
                    KC_LALT, KC_LGUI, KC_LOWER,   KC_ADJUST, KC_SPC,  KC_RALT,  KC_LEFT, KC_DOWN, RAISE_UP, KC_RIGHT \
),

// LOWER LAYER
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, KC_MINS, \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, KC_RBRC, \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, KC_GRV, \
  _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, KC_BSLS, _______, \
                    _______, _______, _______, _______, _______,  _______, KC_BSPC, _______, _______, KC_DEL \
),

[_RAISE] = LAYOUT( \
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______, \
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP, _______,   KC_UP, _______,_______, KC_BSPC, \
  _______, _______,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC, \
  _______,_______, _______, _______, _______, XXXXXXX,  _______,       _______,  XXXXXXX, _______, XXXXXXX, _______,   XXXXXXX, _______, \
                         _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______ \
),

[_ADJUST] = LAYOUT( \
  EEP_RST , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET  , XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX,XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, \
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    } else {
        set_keylog(0, record);
    }
    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
    }
    return true;
}

