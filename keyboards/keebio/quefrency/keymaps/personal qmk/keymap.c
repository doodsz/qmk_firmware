#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1
#define _GAME 2

enum custom_keycodes {
  TYPE1 = SAFE_RANGE,
  TYPE2,
  TYPE3,
};

// Tap Dance Declarations
enum {
    TD_1 = 0,
    TD_2,
    TD_3,
    TD_4,
    // ..., the rest of your tap dances
  };

  qk_tap_dance_action_t tap_dance_actions[] = {
      // simple tap dance
      [TD_1] = ACTION_TAP_DANCE_DOUBLE (LCTL(LSFT(KC_TAB)) , LALT(KC_LEFT)), //Browswer move left , browser back
      [TD_2] = ACTION_TAP_DANCE_DOUBLE (LCTL(KC_TAB) , LALT(KC_RGHT)),  //Browser move right, browser forward
      [TD_3] = ACTION_TAP_DANCE_DOUBLE (LCTL(KC_TAB), LCTL(LSFT(KC_TAB))), 	 // Switch Browser tabs
      [TD_4] = ACTION_TAP_DANCE_DOUBLE (LALT(KC_LEFT), LALT(KC_RGHT)),	 // Browser Forward and back
      /*<[TD_DISCSER] = ACTION_TAP_DANCE_DOUBLE (LCTL(LALT(KC_UP)), LCTL(LALT(KC_DOWN))),     // Discord Server up and down
      [TD_MUTEMIC] = ACTION_TAP_DANCE_DOUBLE ((KC_MUTE) , (KC_F24)), //   Mute Mic and Mute Volume
      [TD_WINDSTAT] = ACTION_TAP_DANCE_DOUBLE (LCAG(KC_EQUAL), LCAG(KC_EQUAL)) //(KDE shortcuts)Window State. Keep raised , shade window
      delete this>*/
    };

  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TYPE1:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("Hello you nerd!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case TYPE2:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("Hello bitch");
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_BSPC, KC_DEL, \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END, \
    KC_F5,   KC_F6,   LT(_GAME, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP, \
    KC_F7,   KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
    KC_F9,   KC_F10,  KC_LCTL, KC_LGUI, MO(_FN1), KC_LALT, KC_SPC,           KC_SPC, XXXXXXX, MO(_FN1), KC_RCTL, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    KC_F11, KC_F12, KC_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, _______, \
    KC_F13, KC_F14, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______, _______, _______, \
    KC_F15, KC_F16, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_F17, KC_F18, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MPLY, \
    KC_F19, KC_F20, KC_TILD, _______, _______, _______, _______,          _______, XXXXXXX, TT(_GAME), _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_GAME] = LAYOUT_65_with_macro(
    TD(TD_1),   TD(TD_2),   DM_RSTP, DM_REC1,    DM_REC2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,  KC_BSPC, KC_DEL, \
    TD(TD_3),   TD(TD_4),   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END, \
    TYPE1,   TYPE2,   KC_CAPS, KC_LEFT,    KC_S,    KC_RGHT,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP, \
    TYPE3,   KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
    DM_PLY1,  DM_PLY2,  KC_LCTL, KC_LGUI, MO(_FN1), KC_LALT, KC_SPC,           KC_SPC, XXXXXXX, MO(_FN1), TT(_BASE), KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  )

};
