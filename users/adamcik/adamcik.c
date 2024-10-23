#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "definitions.h"


#ifndef POINTING_DEVICE_ENABLE
#define DRGSCRL KC_NO
#define DPI_MOD KC_NO
#define S_D_MOD KC_NO
#define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_adamcik(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        LA_PTR,  KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                          LA_NAV,  KC_LSFT, XXXXXXX, XXXXXXX, KC_SPC,  LA_SYM
    ),

    [SYM] = LAYOUT_adamcik(
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  OS_ALTG, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC, KC_HASH, KC_SLSH, KC_AMPR, KC_QUES, KC_EXLM,
                          _______, _______, _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_adamcik(
        KC_TAB,  XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, KC_BRIU, KC_HOME, KC_UP,   KC_END,  KC_DEL,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  OS_ALTG, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        XXXXXXX, KC_MRWD, KC_MSTP, KC_MPLY, KC_MNXT, KC_BRID, KC_PGDN, KC_INS,  KC_PGUP, KC_ENT,
                          _______, _______, _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_adamcik(
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_F11,  KC_F10,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,   KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                          _______, _______, _______, _______, _______, _______
    ),

    [PTR] = LAYOUT_adamcik(
        XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  OS_ALTG, OS_ALTG, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        _______, DRGSCRL, SNIPING, EE_CLR,  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX, XXXXXXX
    )
};


/*
const key_override_t next_track_override =
    ko_make_with_layers_negmods_and_options(
        MOD_MASK_CTRL, KC_MPLY, KC_MNXT, ~0, MOD_MASK_SA,
        ko_option_no_reregister_trigger);

const key_override_t prev_track_override =
    ko_make_with_layers_negmods_and_options(
        MOD_MASK_CS, KC_MPLY, KC_MPRV, ~0, MOD_MASK_SA,
        ko_option_no_reregister_trigger);

const key_override_t **key_overrides = (const key_override_t *[]){
    &next_track_override,  // Ctrl + play/pause         --> next track
    &prev_track_override,  // Ctrl + shift + play/pause --> prev track
    NULL,
};

bool sw_alt_active = false;
*/

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
