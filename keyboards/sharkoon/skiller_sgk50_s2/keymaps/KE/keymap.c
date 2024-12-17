// Copyright 2024 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

//Macro Definitions
enum {
    M_SD = SAFE_RANGE,   //System Shut down
    M_RGBO, M_RGBD, M_RGB1       //RGB Effects
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_all(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PAUS, KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,     KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_P4,   KC_P5,   KC_P6,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                               MO(1),   KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT
    ),

    [1] = LAYOUT_all(
        EE_CLR,  _______, _______, _______, M_SD ,    _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______,          _______, _______, _______,
        KC_CAPS, _______, _______, _______, KC_CALC,  _______, _______, _______,  _______,  _______, _______, _______,          KC_CAPS, KC_VOLU, _______, _______, _______, _______,
        _______, _______, _______,                             _______,                              _______, _______, MO(2),   KC_F23,  KC_VOLD, KC_F24,  _______, _______
    ),

    [2] = LAYOUT_all(
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        M_RGBO,  M_RGBD,  M_RGB1,  _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______,          _______, _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______,  _______,  _______, _______, _______,          _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                             _______,                              _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

//Init
void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_DEFAULT); //Start with right Effect
}

//Macros
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case M_SD:
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_T) SS_UP(X_LGUI) SS_DELAY(100) SS_DOWN(X_LALT) SS_TAP(X_F4) SS_UP(X_LALT) SS_DELAY(100) SS_TAP(X_ENT));
                return false; break;

            //RGB Effects
            case M_RGBO:
                rgb_matrix_mode(RGB_MATRIX_NONE);
                return false; break;
            case M_RGBD:
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_DEFAULT);
                return false; break;
            case M_RGB1:
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_test_effect_1);
                return false; break;
        }
    }
    return true;
};


//Indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //CAPS LOCK
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (i==97 || i == 98 || i==99 || i == 14) {
                rgb_matrix_set_color(i, RGB_WHITE);
            }
        }
    }

    //Num Block
    if (host_keyboard_led_state().num_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (i==7 || i==8 || i==10 || i==11 || i==12 || i==38 || i==39 || i==40 || i==42 || i==43 || i==44 || i==72) {
                rgb_matrix_set_color(i, RGB_WHITE);
            }
        }
    }

    //Layer
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_WHITE);
                }
            }
        }
    }

    return false;
}

