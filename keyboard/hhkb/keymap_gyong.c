/*
 * Magic ESC, ARROW
 */
#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|DEL|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  BSp|
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
     * `-----------------------------------------------------------'
     *       |Alt|Gui  |          Space        |Gui  |Alt|
     *       `-------------------------------------------'
     */
    KEYMAP(
             FN1,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSLS, DEL,  \
             TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSPC,       \
            LCTL,   A,   S,   D,   F,   G, FN2, FN3, FN4, FN5,SCLN,QUOT, ENT,             \
            LSFT,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT, FN0,             \
                 LALT,LGUI,           SPC,                RGUI,RALT
    ),

    /* Layer 1: GUI & ALT SWAP mode (For windows) */
    KEYMAP(
             FN1,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSLS, DEL,  \
             TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSPC,       \
            LCTL,   A,   S,   D,   F,   G, FN2, FN3, FN4, FN5,SCLN,QUOT, ENT,             \
            LSFT,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT, FN0,             \
                 LGUI,LALT,           SPC,               RALT,RGUI
    ),

    /* Layer 2: HHKB mode (HHKB Fn)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|   |
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
     * |-----------------------------------------------------------|
     * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |        |   |   |   |   |   |  +|  -|End|PgD|Dow|      |   |
     * `-----------------------------------------------------------'
     *       |   |     |                       |     |   |
     *       `-------------------------------------------'
     */
    KEYMAP(
             PWR, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, TRNS,  \
            CAPS, FN6,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS, UP, TRNS, TRNS,      \
            TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,PENT,            \
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS,END, PGDN,DOWN,TRNS,TRNS,            \
                 TRNS,TRNS,          TRNS,               TRNS,TRNS),
};


/*
 * user defined action function
 */

enum function_id {
    ESCAPE,
    ARROW_H,
    ARROW_J,
    ARROW_K,
    ARROW_L
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
#   define MAGIC_MOD        MOD_BIT(KC_LCTL)
    static uint8_t isMagicModPressed;
    bool isOnlyLShift;
    bool isOnlyRShift;
    bool isOnlyLAlt;
    bool isOnlyLGui;

    switch (id) {
        // Shift + Esc = Shift + Grave_accent (Tilde)
        // Command + Esc = Command + Grave_accent
        // Alt + Esc = Grave_accent

        case ESCAPE:
            isOnlyLShift = get_mods() == MOD_BIT(KC_LSFT);
            isOnlyRShift = get_mods() == MOD_BIT(KC_RSFT);
            isOnlyLAlt = get_mods() == MOD_BIT(KC_LALT);
            isOnlyLGui = get_mods() == MOD_BIT(KC_LGUI);

            if (record->event.pressed) {
                if (isOnlyLShift || isOnlyRShift || isOnlyLGui) {
                    add_key(KC_GRV);
                    send_keyboard_report();
                }
                else if (isOnlyLAlt) {
                    del_mods(MOD_BIT(KC_LALT));
                    send_keyboard_report();
                    add_key(KC_GRV);
                    send_keyboard_report();
                    add_mods(MOD_BIT(KC_LALT));
                }
                else {
                    add_key(KC_ESC);
                    send_keyboard_report();
                }
            }
            else {
                if (isOnlyLAlt) {
                    del_mods(MOD_BIT(KC_LALT));
                    del_key(KC_ESC);
                    del_key(KC_GRV);
                    send_keyboard_report();
                    add_mods(MOD_BIT(KC_LALT));
                }
                else {
                    del_key(KC_ESC);
                    del_key(KC_GRV);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_H:
            isMagicModPressed = get_mods() & MAGIC_MOD;

            if (record->event.pressed) {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    send_keyboard_report();
                    add_key(KC_LEFT);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    add_key(KC_H);
                    send_keyboard_report();
                }
            }
            else {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    del_key(KC_LEFT);
                    del_key(KC_H);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    del_key(KC_LEFT);
                    del_key(KC_H);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_J:
            isMagicModPressed  = get_mods() & MAGIC_MOD;

            if (record->event.pressed) {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    send_keyboard_report();
                    add_key(KC_DOWN);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    add_key(KC_J);
                    send_keyboard_report();
                }
            }
            else {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    del_key(KC_DOWN);
                    del_key(KC_J);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    del_key(KC_DOWN);
                    del_key(KC_J);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_K:
            isMagicModPressed = get_mods() & MAGIC_MOD;

            if (record->event.pressed) {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    send_keyboard_report();
                    add_key(KC_UP);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    add_key(KC_K);
                    send_keyboard_report();
                }
            }
            else {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    del_key(KC_UP);
                    del_key(KC_K);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    del_key(KC_UP);
                    del_key(KC_K);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_L:
            isMagicModPressed = get_mods() & MAGIC_MOD;

            if (record->event.pressed) {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    send_keyboard_report();
                    add_key(KC_RIGHT);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    add_key(KC_L);
                    send_keyboard_report();
                }
            }
            else {
                if (isMagicModPressed) {
                    del_mods(MAGIC_MOD);
                    del_key(KC_RIGHT);
                    del_key(KC_L);
                    send_keyboard_report();
                    add_mods(MAGIC_MOD);
                }
                else {
                    del_key(KC_RIGHT);
                    del_key(KC_L);
                    send_keyboard_report();
                }
            }
            break;
    }
}

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(2),
    [1] = ACTION_FUNCTION(ESCAPE),
    [2] = ACTION_FUNCTION(ARROW_H),
    [3] = ACTION_FUNCTION(ARROW_J),
    [4] = ACTION_FUNCTION(ARROW_K),
    [5] = ACTION_FUNCTION(ARROW_L),
    [6] = ACTION_LAYER_TOGGLE(1),
};
