/*
Copyright 2018 Kenneth Aloysius

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

enum custom_keycodes {
  TYPE1 = SAFE_RANGE,
  TYPE2,
  TYPE3,
};

enum layers {
  _LAYER0,
  _LAYER1,
  _LAYER2,
  _LAYER3,
  _LAYER4
};

// Tap Dance Declarations
enum {
    TD_TABS = 0,
    TD_FORBACK,
    TD_DISCSER,
    BRSL_BACK,
    BRSR_FORW,
    TD_MUTEMIC,
    TD_WINDSTAT,
    // ..., the rest of your tap dances
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
  case TYPE1:
    if (record->event.pressed) {
      // when keycode QMKBEST is pressed
      SEND_STRING("make "staryu":"doodsz SS_TAP(X_ENTER));
    } else {
      // when keycode QMKBEST is released
    }
    break;
  case TYPE2:
    if (record->event.pressed) {
      // when keycode QMKURL is pressed
      SEND_STRING("make keebio/quefrency:doodsz:dfu\n"); //\n means new line mapped to KC_ENT
    } else {
      // when keycode QMKURL is released
    }
    break;
  case TYPE3:
    if (record->event.pressed) {
              SEND_STRING(SS_LCTL("ac")); // selects all and copies
    }
    break;
}
return true;
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // simple tap dance
    [BRSL_BACK] = ACTION_TAP_DANCE_DOUBLE (LCTL(LSFT(KC_TAB)) , LALT(KC_LEFT)), //Browswer move left , browser back
    [BRSR_FORW] = ACTION_TAP_DANCE_DOUBLE (LCTL(KC_TAB) , LALT(KC_RGHT)),  //Browser move right, browser forward
    [TD_TABS] = ACTION_TAP_DANCE_DOUBLE (LCTL(KC_TAB), LCTL(LSFT(KC_TAB))), 	 // Switch Browser tabs
    [TD_FORBACK] = ACTION_TAP_DANCE_DOUBLE (LALT(KC_LEFT), LALT(KC_RGHT)),	 // Browser Forward and back
    [TD_DISCSER] = ACTION_TAP_DANCE_DOUBLE (LCTL(LALT(KC_UP)), LCTL(LALT(KC_DOWN))),     // Discord Server up and down
    [TD_MUTEMIC] = ACTION_TAP_DANCE_DOUBLE ((KC_MUTE) , (KC_F24)), //   Mute Mic and Mute Volume
    [TD_WINDSTAT] = ACTION_TAP_DANCE_DOUBLE (LCAG(KC_EQUAL), LCAG(KC_EQUAL)) //(KDE shortcuts)Window State. Keep raised , shade window
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LAYER0] = LAYOUT(
/* ┌─────────┬─────────┬─────────┐ */  		//SPRING GREEN
    	       TD(BRSL_BACK),  TD(BRSR_FORW),
/* ├─────────┼─────────┼─────────┤ */
   TO(_LAYER1),TD(TD_DISCSER),  TD(TD_MUTEMIC)
/* └─────────┴─────────┴─────────┘ */
  ),

  [_LAYER1] = LAYOUT(
/* ┌─────────┬─────────┬─────────┐ */		//CORAL
                TD(TD_WINDSTAT), LCAG(KC_BSLASH), //resize window
/* ├─────────┼─────────┼─────────┤ */
   TO(_LAYER2), SGUI(KC_PSCR),  KC_MPLY             //print rectangular screenshot
/* └─────────┴─────────┴─────────┘ */
  ),

  [_LAYER2] = LAYOUT(
/* ┌─────────┬─────────┬─────────┐ */		//MAGENTA
              KC_VOLU,  KC_MNXT,
/* ├─────────┼─────────┼─────────┤ */
    TO(_LAYER0), KC_VOLD,  KC_MPRV
/* └─────────┴─────────┴─────────┘ */
  ),

};

void eeconfig_init_user(void) {
  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_BREATHING+1);

  backlight_enable();
}

void keyboard_post_init_user(void) {
  //layer_state_set_user is not called for inital state - set it here
  rgblight_sethsv_noeeprom_springgreen();
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _LAYER1:
        rgblight_sethsv_noeeprom_coral();
        break;
    case _LAYER2:
        rgblight_sethsv_noeeprom_magenta();
        break;
//    case _LAYER3:
//        rgblight_sethsv_noeeprom_red();
//        break;
//    case _LAYER4:
//        rgblight_sethsv_noeeprom_orange();
//        break;
    case _LAYER0:
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom_springgreen();
        break;
    }
  return state;
}
