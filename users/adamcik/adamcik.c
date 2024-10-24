#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "definitions.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [COL] = LAYOUT_adamcik(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,        KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                          LA_PTR,  LA_NAV,  KC_SPC,      KC_LSFT, LA_SYM,  XXXXXXX
    ),
    [QWE] = LAYOUT_adamcik(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          LA_PTR,  LA_NAV,  KC_SPC,      KC_LSFT, LA_SYM,  XXXXXXX
    ),
    [SYM] = LAYOUT_adamcik(
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,     KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,      OS_ALTG, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC,     KC_HASH, KC_SLSH, KC_AMPR, KC_QUES, KC_EXLM,
                          _______, _______, _______,     _______, _______, _______
    ),
    [NAV] = LAYOUT_adamcik(
        KC_TAB,  KC_VOLU, KC_MUTE, KC_VOLD, QK_BOOT,     KC_BRIU, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  OS_ALTG,     TG(QWE), KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        KC_MRWD, KC_MSTP, KC_MPLY, KC_MNXT, EE_CLR,      KC_BRID, KC_PGDN, KC_INS,  KC_PGUP, KC_ENT,
                          _______, _______, _______,     _______, _______, _______
    ),
    [NUM] = LAYOUT_adamcik(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,        KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_F11,      KC_F12,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,       KC_F8,   KC_F10,  KC_F2,   KC_F4,   KC_F6,
                          _______, _______, _______,     _______, _______, _______
    ),
    [PTR] = LAYOUT_adamcik(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_BTN2, KC_BTN1, KC_BTN3, DRGSCRL, SNIPING,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S_D_MOD,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
    )
};

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_altg_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);
    update_oneshot(&os_altg_state, KC_RALT, OS_ALTG, keycode, record);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

void keyboard_post_init_user(void) {
#if defined RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_sethsv_noeeprom(0,0,255);
#endif
}
