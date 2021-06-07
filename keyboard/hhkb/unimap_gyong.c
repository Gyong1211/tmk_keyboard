/*
 * Magic ESC, ARROW
 */
#include "unimap_trans.h"


/*
 * user defined action function
 */
enum function_id {
    ESCAPE,         // Magic escape
    ARROW_H,
    ARROW_J,
    ARROW_K,
    ARROW_L
};

#define AC_L1       ACTION_LAYER_TOGGLE(1)
#define AC_L2       ACTION_LAYER_MOMENTARY(2)
#define AC_MESC     ACTION_FUNCTION(ESCAPE)
#define AC_ARWH     ACTION_FUNCTION(ARROW_H)
#define AC_ARWJ     ACTION_FUNCTION(ARROW_J)
#define AC_ARWK     ACTION_FUNCTION(ARROW_K)
#define AC_ARWL     ACTION_FUNCTION(ARROW_L)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    [0] = UNIMAP_HHKB(
            MESC,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSLS, DEL,    \
             TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSPC,         \
            LCTL,   A,   S,   D,   F,   G,ARWH,ARWJ,ARWK,ARWL,SCLN,QUOT, ENT,              \
            LSFT,   Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,RSFT,  L2,            \
                 LALT,LGUI,           SPC,               RGUI,RALT
          ),

    [1] = UNIMAP_HHKB(
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      \
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           \
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,           \
                 LGUI,LALT,          TRNS,               RALT,RGUI
          ),

    [2] = UNIMAP_HHKB(
             PWR,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, INS,TRNS,  \
            CAPS,  L1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,  UP,TRNS,TRNS,      \
            TRNS,VOLD,VOLU,MUTE,EJCT,TRNS,PAST,PSLS,HOME,PGUP,LEFT,RGHT,PENT,            \
            TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PPLS,PMNS, END,PGDN,DOWN,TRNS,TRNS,            \
                 TRNS,TRNS,          TRNS,               TRNS,TRNS
          ),
};




void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    #define MODS_ALT_MASK   MOD_BIT(KC_LALT)
    static uint8_t alt;
    bool isLShiftPressed;
    bool isRShiftPressed;
    bool isLAltPressed;
    bool isLCmdPressed;

    switch (id) {
        // Shift + Esc = Shift + Grave_accent (Tilde)
        // Command + Esc = Command + Grave_accent
        // Alt + Esc = Grave_accent

        case ESCAPE:
            isLShiftPressed = get_mods() == MOD_BIT(KC_LSFT);   // press only left shift
            isRShiftPressed = get_mods() == MOD_BIT(KC_RSFT);   // press only right shift
            isLAltPressed = get_mods() == MOD_BIT(KC_LALT);     // press only left alt
            isLCmdPressed = get_mods() == MOD_BIT(KC_LGUI);     // press only left command

            if (record->event.pressed) {
                if (isLShiftPressed || isRShiftPressed || isLCmdPressed) {  // if only Shift or LGui pressed
                    add_key(KC_GRV);                            // add grave_accent
                    send_keyboard_report();                     // send key (one modifier + grave_accent)
                }
                else if (isLAltPressed) {                       // if LAlt pressed
                    del_mods(MOD_BIT(KC_LALT));                 // remove left alt
                    add_key(KC_GRV);                            // add grave_accent
                    send_keyboard_report();                     // send key (grave_accent only)
                    add_mods(MOD_BIT(KC_LALT));                 // add left alt
                }
                else {
                    add_key(KC_ESC);                            // add ESC key
                    send_keyboard_report();                     // send key (esc or esc with multiple modifiers)
                }
            }
            else {
                if (isLShiftPressed || isRShiftPressed || isLCmdPressed || isLAltPressed) {
                    del_key(KC_GRV);
                    send_keyboard_report();
                }
                else {
                    del_key(KC_ESC);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_H:
            alt = get_mods()&MODS_ALT_MASK;     // check press left alt

            if (record->event.pressed) {
                if (alt) {                      // if press left alt
                    del_mods(MOD_BIT(KC_LALT)); // remove left alt
                    add_key(KC_LEFT);           // add left arrow
                    send_keyboard_report();     // send key
                    add_mods(MOD_BIT(KC_LALT)); // add left alt
                }
                else {                          // if not press left alt
                    add_key(KC_H);              // add h
                    send_keyboard_report();     // send key
                }
            }
            else {
                if (alt) {
                    del_key(KC_LEFT);
                    send_keyboard_report();
                }
                else {                          // if not press left alt
                    del_key(KC_H);              // remove h
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_J:
            alt = get_mods()&MODS_ALT_MASK;

            if (record->event.pressed) {
                if (alt) {
                    del_mods(MOD_BIT(KC_LALT));
                    add_key(KC_DOWN);
                    send_keyboard_report();
                    add_mods(MOD_BIT(KC_LALT));
                }
                else {
                    add_key(KC_J);
                    send_keyboard_report();
                }
            }
            else {
                if (alt) {
                    del_key(KC_DOWN);
                    send_keyboard_report();
                }
                else {
                    del_key(KC_J);
                    send_keyboard_report();
                }
            }
            break;
        case ARROW_K:
            alt = get_mods()&MODS_ALT_MASK;

            if (record->event.pressed) {
                if (alt) {
                    del_mods(MOD_BIT(KC_LALT));
                    add_key(KC_UP);
                    send_keyboard_report();
                    add_mods(MOD_BIT(KC_LALT));
                }
                else {
                    add_key(KC_K);
                    send_keyboard_report();
                }
            }
            else {
                if (alt) {
                    del_key(KC_UP);
                    send_keyboard_report();
                }
                else {
                    del_key(KC_K);
                    send_keyboard_report();
                }
            }
            break;

        case ARROW_L:
            alt = get_mods()&MODS_ALT_MASK;

            if (record->event.pressed) {
                if (alt) {
                    del_mods(MOD_BIT(KC_LALT));
                    add_key(KC_RIGHT);
                    send_keyboard_report();
                    add_mods(MOD_BIT(KC_LALT));
                }
                else {
                    add_key(KC_L);
                    send_keyboard_report();
                }
            }
            else {
                if (alt) {
                    del_key(KC_RIGHT);
                    send_keyboard_report();
                }
                else {
                    del_key(KC_L);
                    send_keyboard_report();
                }
            }
            break;
    }
}
