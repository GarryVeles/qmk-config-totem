/* 
                                             ▀▀▀▀▀     ▀▀▀▀▀          ▀▀█▀▀
                                             ▄▀▀▀▄  ▄  ▄▀▀▀▄  ▄  ▄▀▀▀▄  █  ▄▀▀▀▄
                                             █   █  █  █   █  █  █   █  █  █   █
                                              ▀▀▀   █   ▀▀▀   █   ▀▀▀   ▀   ▀▀▀
                                                    █      ▄▄▄█▄▄▄    █   █  
                                                    ▀      █  █  █     █▄█
                                                  ▀▀▀▀▀    █  █  █      ▀   
                                                           ▀  ▀  ▀  G A R R Y  
                                                                                                                                  
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "totem.h"

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                  │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                       │
// └─────────────────────────────────────────────────┘ 

enum totem_layers {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJ1,
    _ADJ2,
    _ADJ3,
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   k e y c o d e s                   │
// └─────────────────────────────────────────────────┘

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    LOWER,
    LOWER2,
    RAISE,
    RAISE2,
    ADJ1,
    ADJ2,
    ADJ3,
    OS_SWAP,
    MAKE_H,
    SNAP
};

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   T a p - D a n c e'                │
// └─────────────────────────────────────────────────┘
// https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_tap_dance.md

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  B_CTL = 0,
  Q_ESC = 1,
  Z_BSPC = 2,
  SOME_OTHER_DANCE
};

int cur_dance (tap_dance_state_t *state);

//for the b tap dance. Put it here so it can be used in any keymap
void b_finished (tap_dance_state_t *state, void *user_data);
void b_reset (tap_dance_state_t *state, void *user_data);

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s               │
// └─────────────────────────────────────────────────┘

// LEFT HAND HOME ROW MODS QWERTY ├──────────────────┐

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_S MT(MOD_LALT, KC_S)
#define CTL_D MT(MOD_LCTL, KC_D)
#define SHT_F MT(MOD_LSFT, KC_F)
#define CTL_X MT(MOD_LCTL, KC_X)
#define SHT_C MT(MOD_LSFT, KC_C)

// RIGHT HAND HOME ROW MODS QWERTY ├─────────────────┐

#define SHT_J MT(MOD_RSFT, KC_J)
#define CTL_K MT(MOD_LCTL, KC_K)
#define ALT_L MT(MOD_LALT, KC_L)
#define GUI_S MT(MOD_LGUI, KC_SCLN)


// LEFT HAND HOME ROW MODS COLEMAK ├─────────────────┐

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_R MT(MOD_LALT, KC_R)
#define CTL_S MT(MOD_LCTL, KC_S)
#define SHT_T MT(MOD_LSFT, KC_T)

// RIGHT HAND HOME ROW MODS COLEMAK ├────────────────┐

#define SHT_N MT(MOD_RSFT, KC_N)
#define CTL_E MT(MOD_LCTL, KC_E)
#define ALT_I MT(MOD_LALT, KC_I)
#define GUI_O MT(MOD_LGUI, KC_O)




#define LOWER LT(_LOWER, KC_TAB)
#define LOWER2 LT(_LOWER, KC_QUOT)
#define RAISE LT(_RAISE, KC_ESC)
#define RAISE2 LT(_RAISE, KC_GRV)
#define ADJ1 MO(_ADJ1)
#define ADJ2 MO(_ADJ2)
#define ADJ3 MO(_ADJ3)


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
   ┌─────────────────────────────────────────────────┐
   │ q w e r t y                                     │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    Q    │    W    │    E    │    R    │    T    ││    Y    │    U    │    I    │    O    │    P    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    A    │    S    │    D    │    F    │    G    ││    H    │    J    │    K    │    L    │    ;    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    `    │    Z    │    X    │    C    │    V    │    B    ││    N    │    M    │    ,    │    .    │    /    │    '    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   DEL   │  LOWER  │  SPACE  ││  BSPC   │  RAISE  │  ENTER  │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘*/ 

   [_QWERTY] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              TD(Q_ESC), KC_W,    KC_E,     KC_R,     KC_T,         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  
              GUI_A,    ALT_S,    CTL_D,    SHT_F,    KC_G,         KC_H,     SHT_J,    CTL_K,    ALT_L,    GUI_S,    
    RAISE2,   TD(Z_BSPC), CTL_X,  SHT_C,    KC_V,     KC_B,    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  LOWER2,
                                  KC_DEL,   LOWER,    KC_SPC,       KC_BSPC,  RAISE,    KC_ENT
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ r a i s e                                       │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡ CAPSLCK │  HOME   │    ↑    │   END   │  BREAK  ││   WH↑   │   L_C   │   [↑]   │   R_C   │   WH→   │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │ NUMLCK  │    ←    │    ↓    │    →    │  FRWD   ││   WH↓   │   [←]   │   [↓]   │   [→]   │   ←WH   │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │ SCRNSHT │  SCRL   │   PG↑   │   INS   │   PG↓   │  BACK   ││    _    │    |    │    -    │    +    │    =    │    \    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │  ADJ1   │    ▼    ││    ▼    │    ▼    │    ▼    │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */ 

   [_RAISE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_CAPS,  KC_HOME,  KC_UP,    KC_END,   KC_BRK,     KC_WH_U,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_WH_R,
              KC_NUM,   KC_LEFT,  KC_DOWN,  KC_RGHT,  RCS(KC_Z),  KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_L,  
    KC_PSCR,  KC_SCRL,  KC_PGUP,  KC_INS,   KC_PGDN,  C(KC_Z),    KC_UNDS,  KC_PIPE,  KC_MINS,  KC_PLUS,  KC_EQL,  KC_NUBS,
                                  _______,  ADJ1,     _______,    _______,  _______,  _______
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ l o w e r                                       │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡   F1    │   F2    │   F3    │   F4    │    {    ││    }    │    7    │    8    │    9    │    -    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │   F5    │   F6    │   F7    │   F8    │    [    ││    ]    │    4    │    5    │    6    │    +    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │ SCRNSHT │   F9    │   F10   │   F11   │   F12   │    (    ││    )    │    1    │    2    │    3    │    *    │    /    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    ││    ▼    │  ADJ2   │    0    │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */ 

   [_LOWER] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_LCBR,    KC_RCBR,  KC_P7,    KC_P8,    KC_P9,    KC_MINS,
              KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_LBRC,    KC_RBRC,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS, 
    KC_PSCR,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_LPRN,    KC_RPRN,  KC_P1,    KC_P2,    KC_P3,    KC_PAST,  KC_PSLS, 
                                  _______,  _______,  _______,    _______,  ADJ2,     KC_P0
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ a d j 1                                         │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    !    │    @    │    #    │    $    │    %    ││    ^    │    &    │    *    │    (    │    )    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    1    │    2    │    3    │    4    │    5    ││    6    │    7    │    8    │    9    │    0    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   F1    │   F2    │   F3    │   F4    │   F5    │   F6    ││   F7    │   F8    │   F9    │   F10   │   F11   │   F12   │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */ 

   [_ADJ1] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,
              KC_P1,    KC_P2,    KC_P3,    KC_P4,    KC_P5,      KC_P6,    KC_P7,    KC_P8,    KC_P9,    KC_P0,  
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
                                  _______,  _______,  _______,    _______,  _______,  _______
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ a d j 2                                         │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡   WH↑   │   L_C   │   [↑]   │   R_C   │   WH→   ││    \    │    |    │    -    │  NEXT   │  VOLU   │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │   WH↓   │   [←]   │   [↓]   │   [→]   │   ←WH   ││    =    │    _    │    +    │  PREV   │  VOLD   │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    `    │    !    │    @    │    #    │    $    │    %    ││    ^    │    &    │    *    │    (    │    )    │  PLAY   │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │  ADJ3   │    ▼    ││    ▼    │    ▼    │    ▼    │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */ 

   [_ADJ2] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_WH_R,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_WH_U,     KC_NUBS,  KC_PIPE,  KC_MINS,  KC_PGDN,  KC_UP,
              KC_WH_L,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,     KC_EQL,   KC_UNDS,  KC_PLUS,  KC_PGUP,  KC_DOWN, 
    KC_GRV,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,     KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_SPC, 
                                  _______,  ADJ3,     _______,     _______,  _______,  _______
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸
   
   ┌─────────────────────────────────────────────────┐
   │ a d j 3                                         │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡  RESET  │         │         │         │         ││  SAVE   │   F1    │   F2    │   F3    │   F4    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │  DEBUG  │ QWERTY  │         │         │         ││         │   F5    │   F6    │   F7    │   F8    │   
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  MAKE   │ OS SWAP │ COLEMAK │ DM REC1 │ DM STOP │ DM PLY1 ││         │   F9    │   F10   │   F11   │   F12   │   CUE   │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ */ 

   [_ADJ3] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     C(KC_S),  KC_F1,    KC_F2,    KC_F3,    KC_F4,   
              DB_TOGG,  QWERTY,   XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  KC_F5,    KC_F6,    KC_F7,    KC_F8,
    MAKE_H,   OS_SWAP,  COLEMAK,  DM_REC1,  DM_RSTP,  DM_PLY1,     XXXXXXX,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   RALT(KC_C),
                                  _______,  _______,  _______,     _______,  _______,  _______  
 ),

 /*

   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ c o l e m a k                                   │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    Q    │    W    │    F    │    P    │    G    ││    J    │    L    │    U    │    Y    │    ;    │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    A    │    R    │    S    │    T    │    D    ││    H    │    N    │    E    │    I    │    O    │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    Q    │    Z    │    X    │    C    │    V    │    B    ││    K    │    M    │    ,    │    .    │    /    │    ;    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │   DEL   │  LOWER  │  SPACE  ││  BSPC   │  RAISE  │  ENTER  │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘*/ 

   [_COLEMAK] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,         KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  
              GUI_A,    ALT_R,    CTL_S,    SHT_T,    KC_D,         KC_H,     SHT_N,    CTL_E,    ALT_I,    GUI_O,  
    KC_Q,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,         KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_SCLN,
                                  KC_DEL,   LOWER,    KC_SPC,       KC_BSPC,  RAISE,    KC_ENT
 )

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ t e m p l a t e                                 │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │         │         │         │         ││         │         │         │         │         │   
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │         │         │         │         │         ││         │         │         │         │         │    
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         ││         │         │         │  
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘ 

   [_TEMPLATE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,  
              _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______, _______,
                                  _______,  _______,   _______,  _______,  _______,  _______,
 ),
*/
};



// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ M A C R O S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case OS_SWAP: 
            if (record->event.pressed) {
                if (!keymap_config.swap_lctl_lgui) {
                  keymap_config.swap_lctl_lgui = true;  // ─── MAC
                }
                else {
                  keymap_config.swap_lctl_lgui = false; // ─── WIN
                }
            eeconfig_update_keymap(keymap_config.raw);
            clear_keyboard();  // ──── clear to prevent stuck keys    
            return false;
          }


// ┌─────────────────────────────────────────────────┐
// │ l a y e r                                       │
// └─────────────────────────────────────────────────┘

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

// ┌─────────────────────────────────────────────────┐
// │ q m k                                           │
// └─────────────────────────────────────────────────┘

        case MAKE_H:
          if (record->event.pressed) {
            SEND_STRING ("qmk compile -kb totem -km garry");
            tap_code(KC_ENTER); 
          } 
          break;

// ┌─────────────────────────────────────────────────┐
// │ p r o d u c t i v i t y                         │
// └─────────────────────────────────────────────────┘

      case SNAP:
          if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) {
              SEND_STRING(SS_LSFT(SS_LCMD(SS_LCTL("4"))));  //MAC           
            } else {
              SEND_STRING(SS_LSFT(SS_LWIN("S")));           //WIN
            }
          }
          break;
    }
    return true;
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap btap_state = {
  .is_press_action = true,
  .state = 0
};

void b_finished (tap_dance_state_t *state, void *user_data) {
  btap_state.state = cur_dance(state);
  switch (btap_state.state) {
    case SINGLE_TAP: register_code(KC_B); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_TAP: register_code(KC_ENT); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_B); unregister_code(KC_B); register_code(KC_B);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void b_reset (tap_dance_state_t *state, void *user_data) {
  switch (btap_state.state) {
    case SINGLE_TAP: unregister_code(KC_B); break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_TAP: unregister_code(KC_ENT); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_B);
  }
  btap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
  [B_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
  [Q_ESC]     = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [Z_BSPC]    = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_BSPC)
};
/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


                                                          ██████
                                                            ██  ▄▄▄▄
                                                            ██ ██▀▀██
                                                            ▀▀ ██▄▄██
                                                        ██████  ▀▀▀▀
                                                          ██ ▄▄▄▄▄▄
                                                          ██ ██▀▀▀▀
                                                          ██ ██████
                                                             ██▄▄▄▄
                                                             ▀▀▀▀▀▀
                                                           ████████
                                                           ██ ██ ██
                                                           ██ ██ ██
                                                           ▀▀ ▀▀ ▀▀
                                                          ████████

*/



