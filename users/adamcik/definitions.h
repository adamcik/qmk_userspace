#pragma once

#include QMK_KEYBOARD_H

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_PTR MO(PTR)

enum layers {
    COL = 0,
    QWE,
    SYM,
    NAV,
    NUM,
    PTR,
};

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_ALTG,
};
