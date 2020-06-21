#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_uk.h"
#include "sendstring_uk.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define EDIT 3 // shortcuts

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  MY_SELALL = SAFE_RANGE,
  MY_UNDO,
  MY_CUT,
  MY_COPY,
  MY_PASTE,
  MY_CTRLTAB,
  MY_ALTTAB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | GESC   |   1  |   2  |   3  |   4  |   5  |   -  |           |   =  |   6  |   7  |   8  |   9  |   0  | BSpace |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           | ~L3  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCtrl | GUI  | ALT  | Left | Right|                                       | Down | Up |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | SPC  | DEL  |------|       |------|  Tab   |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
  // left hand
  KC_GESC,                  UK_1,              UK_2,          UK_3,       UK_4,    UK_5,    UK_MINS,
  UK_TAB,                   UK_Q,              UK_W,          UK_E,       UK_R,    UK_T,    TG(SYMB),
  UK_BSPC,                  UK_A,              UK_S,          UK_D,       UK_F,    UK_G,
  UK_LSFT,                  UK_Z,              UK_X,          UK_C,       UK_V,    UK_B,    ALL_T(KC_NO),
  KC_LCTL,                  KC_LGUI,  ALT_T(KC_APP),       UK_LEFT,    UK_RGHT,
                                                                                   ALT_T(KC_APP), UK_LGUI,
                                                                                                  UK_HOME,
                                                                                  KC_SPC, UK_DEL, UK_END,
  // right hand
  UK_EQL,             UK_6,       UK_7,       UK_8,       UK_9,              UK_0,        UK_BSPC,
  TT(EDIT),     UK_Y,       UK_U,       UK_I,       UK_O,              UK_P,        UK_BSLS,
                      UK_H,       UK_J,       UK_K,       UK_L,           UK_SCLN,        UK_QUOT,
  MEH_T(KC_NO),       UK_N,       UK_M,    UK_COMM,     UK_DOT,           UK_SLSH,        UK_RSFT,
                               UK_DOWN,      UK_UP,    UK_LBRC,           UK_RBRC,       TT(SYMB),
  UK_RALT, CTL_T(UK_ESC),
  UK_PGUP,
  UK_PGDN, UK_TAB, UK_ENT
),

/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |   F7 |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, UK_F1,   UK_F2,   UK_F3,   UK_F4,   UK_F5,   UK_F6,
  KC_TRNS, UK_EXLM, UK_AT,   UK_LCBR, UK_RCBR, UK_PIPE, KC_TRNS,
  KC_TRNS, UK_HASH, UK_DLR,  UK_LPRN, UK_RPRN, UK_GRV,
  KC_TRNS, UK_PERC, UK_CIRC, UK_LBRC, UK_RBRC, UK_TILD, KC_TRNS,
  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  UK_F7,   UK_F8,   UK_F9,   UK_F10,  UK_F11, UK_F12, KC_TRNS,
  KC_TRNS, UK_UP,   UK_7,    UK_8,    UK_9,    UK_ASTR, UK_F12,
  UK_DOWN, UK_4,    UK_5,    UK_6,    UK_PLUS, KC_TRNS,
  KC_TRNS, UK_AMPR, UK_1,    UK_2,    UK_3,    UK_BSLS, KC_TRNS,
  KC_TRNS, UK_DOT,  UK_0,    UK_EQL,  KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                    KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: text editing shortcuts and helpful stuff
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |   F7 |  F8  |  F9  |  F10 |  F11 |  F12 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |AltTab|Ct Tab|      |      |      |      |           | N/A  |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           | L3   |------+------+------+------+------+--------|
 * |        |S_All |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Undo |  Cut | Copy | Paste|      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[EDIT] = LAYOUT_ergodox(
    // Left hand
    KC_TRNS,   UK_F1,   UK_F2,   UK_F3,   UK_F4,   UK_F5,   UK_F6,
    KC_TRNS,   MY_ALTTAB,  MY_CTRLTAB, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS,   MY_SELALL,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS,   MY_UNDO,    MY_CUT,     MY_COPY, MY_PASTE, KC_TRNS, KC_TRNS,
    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,

                                                       KC_TRNS, KC_TRNS,
                                                                KC_TRNS,
                                              KC_TRNS, KC_TRNS, KC_TRNS,

    // right hand
    UK_F7,   UK_F8,   UK_F9,   UK_F10,  UK_F11, UK_F12, KC_TRNS,
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS,   KC_TRNS
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_SELALL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("a"));  // Control + a
                break;
            }
        case MY_UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("z"));  // Control + z
                break;
            }
        case MY_CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));  // Control + x
                break;
            }
        case MY_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));  // Control + c
                break;
            }
        case MY_PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));  // Control + v
                break;
            }
        case MY_CTRLTAB:
            if (record->event.pressed) {
                register_code(KC_LCTL);     // Hold Left control
                SEND_STRING(SS_TAP(X_TAB)); // Tap Tab
                unregister_code(KC_LCTL);   // Release Left Control
                break;
            }
        case MY_ALTTAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
        switch (layer) {
            case 0:

            break;
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 4:
            ergodox_right_led_3_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }
    return state;
};

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
