/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// Define Combos
enum combos {
    ESC_COMBO,
    TAB_COMBO,
    COMBO_LENGTH
};

// Combo key positions
const uint16_t PROGMEM esc_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_R, COMBO_END};

// Combo actions
combo_t key_combos[COMBO_LENGTH] = {
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
};

// Layer definitions
enum layers {
    _COLEMAK,
    _NAV,
    _SYM,
    _FUN,
    _NUMB,
    _MOUSE
};

// Custom keycodes
enum custom_keycodes {
    COLEMAK = SAFE_RANGE
};


#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define FUN MO(_FUN)
#define NUMB MO(_NUMB)
#define MOUSE MO(_MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Colemak Layer with Mod-Tap*/
  [_COLEMAK] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    MT(MOD_LGUI, KC_A), MT(MOD_LCTL, KC_R), MT(MOD_LALT, KC_S), MT(MOD_LSFT, KC_T), KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    MT(NAV, KC_Z),     KC_X,    KC_C,    KC_D,    KC_V,                      KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
    _______, _______, _______, NAV,     KC_LSFT,   MOUSE,            KC_SPC, SYM, _______
  ),

  [_NAV] = LAYOUT(
    KC_ESC,  OSM(MOD_LALT), OSM(MOD_LCTL), LALT(KC_RIGHT), KC_INS,  KC_PGUP, KC_PGDN, KC_HOME, KC_END,  KC_CAPS,
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_RALT), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL,
    LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), KC_LGUI,   KC_ENT,  KC_BSPC, KC_TAB,  KC_APP,  KC_PSCR,
    _______, _______, _______, _______, _______, _______,  KC_ENT,    FUN,     _______
  ),

  /* Symbol Layer
   * Symbols and special characters.
   */
  [_SYM] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_EQL,   KC_GRV,   KC_COLN, KC_SCLN, KC_PLUS,
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_CIRC, KC_ASTR,  KC_LPRN,  KC_LBRC, KC_LCBR, KC_MINS,
    _______, _______, KC_BSLS, KC_PIPE, KC_AMPR,        KC_TILD,  KC_RPRN,  KC_RBRC, KC_RCBR, KC_UNDS,
    _______, _______, _______, _______, _______,        _______,  _______,  _______, _______
  ),

  /* Function Layer
   * Media controls and function keys.
   */
  [_FUN] = LAYOUT(
    KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRIU,        KC_F12,   KC_F7,    KC_F8,   KC_F9,   TO(_COLEMAK),
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_BRID, KC_F11,   KC_F4,    KC_F5,   KC_F6,   TO(_NAV),
    KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,          KC_F10,   KC_F1,    KC_F2,   KC_F3,   _______,
    _______, _______, _______, _______, _______,        _______,  _______,  _______, _______
  ),

  /* Numeric Layer */
  [_NUMB] = LAYOUT(
    _______, _______, _______, _______, _______,        KC_EQL,   KC_7,     KC_8,    KC_9,    KC_PLUS,
    OSM(MOD_LALT), OSM(MOD_LGUI), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, KC_ASTR,  KC_4,     KC_5,    KC_6,    KC_MINS,
    _______, _______, _______, _______, _______,        KC_0,     KC_1,     KC_2,    KC_3,    KC_SLSH,
    _______, _______, _______, _______, _______,        _______,  _______,  _______, _______
  ),

  /* Mouse Layer */
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______ , _______,        _______,  _______,  _______, _______, _______,
    _______, KC_MS_L, KC_MS_U, KC_MS_R, _______,        KC_WH_U,  KC_BTN1,  KC_BTN2, KC_BTN3, _______,
    _______, _______, KC_MS_U, _______, _______,        KC_WH_D,  KC_BTN4,  KC_BTN5, _______, _______,
    _______, _______, _______, _______, _______,        _______,  _______,  _______, _______
  )
};

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    keyball_set_scroll_mode(get_highest_layer(state) == _MOUSE);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
