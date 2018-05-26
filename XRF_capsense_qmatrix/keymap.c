#include <avr/pgmspace.h>
#include "keycode.h"


/* Realforce 87U
 * ,---.   ,---------------. ,---------------. ,---------------.  ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12|  |Psc|Slk|Pau|
 * `---'   `---------------' `---------------' `---------------'  `-----------'
 * ,-----------------------------------------------------------.  ,-----------.  
 * |`  |1  |2  |3  |4  |5  |6  |7  |8  |9  |-  |=  |\  |   |Bs |  |Ins|Hom|PgU|  
 * |-----------------------------------------------------------|  |-----------|  
 * |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  |]  |\    |  |Del|End|PgD| 
 * |-----------------------------------------------------------|  `-----------'  
 * |Ctrl  |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |#  |Ent |                 
 * |-----------------------------------------------------------|      ,---.     
 * |Shift|\ |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |Shift |Fn |      |Up |    
 * |-----------------------------------------------------------|  ,-----------.
 * |     |   |     |         Spc            |     |   |   |    |  |Lef|Dow|Rig|
 * `-----------------------------------------------------------'  `-----------'
 */
#define KEYMAP( \
    K000,       K002, K003, K004, K005, K006, K007, K008, K009,       K011, K012, K013, K014, K015, K016, K017, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K314,                   \
	K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414,       K416,       \
    K500, K501, K502,                   K506,                   K510, K511, K512,       K514, K515, K516, K517  \
) { \
    {KC_##K000, KC_##K100, KC_##K200, KC_##K300, KC_##K400, KC_##K500}, \
    {KC_NO,     KC_##K101, KC_##K201, KC_##K301, KC_##K401, KC_##K501}, \
    {KC_##K002, KC_##K102, KC_##K202, KC_##K302, KC_##K402, KC_##K502}, \
    {KC_##K003, KC_##K103, KC_##K203, KC_##K303, KC_##K403, KC_NO    }, \
    {KC_##K004, KC_##K104, KC_##K204, KC_##K304, KC_##K404, KC_NO    }, \
    {KC_##K005, KC_##K105, KC_##K205, KC_##K305, KC_##K405, KC_NO    }, \
    {KC_##K006, KC_##K106, KC_##K206, KC_##K306, KC_##K406, KC_##K506}, \
    {KC_##K007, KC_##K107, KC_##K207, KC_##K307, KC_##K407, KC_NO    }, \
    {KC_##K008, KC_##K108, KC_##K208, KC_##K308, KC_##K408, KC_NO    }, \
    {KC_##K009, KC_##K109, KC_##K209, KC_##K309, KC_##K409, KC_NO    }, \
    {KC_NO,     KC_##K110, KC_##K210, KC_##K310, KC_##K410, KC_##K510}, \
    {KC_##K011, KC_##K111, KC_##K211, KC_##K311, KC_##K411, KC_##K511}, \
    {KC_##K012, KC_##K112, KC_##K212, KC_##K312, KC_##K412, KC_##K512}, \
    {KC_##K013, KC_##K113, KC_NO,     KC_NO,     KC_NO,     KC_NO    }, \
    {KC_##K014, KC_##K114, KC_##K214, KC_##K314, KC_##K414, KC_##K514}, \
    {KC_##K015, KC_##K115, KC_##K215, KC_NO,     KC_NO,     KC_##K515}, \
    {KC_##K016, KC_##K116, KC_##K216, KC_NO,     KC_##K416, KC_##K516}, \
    {KC_##K017, KC_##K117, KC_##K217, KC_NO,     KC_NO,     KC_##K517} \
}


const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    [0] = KEYMAP(
ESC,       F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,       F9,  F10, F11, F12,  PSCR,SLCK,PAUS,
GRV,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,BSPC, INS, HOME,PGUP,
TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS, DEL, END, PGDN,
LCTL, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,     ENT,                      
LSFT, NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,     RSFT,      UP,       
LCTRL,LGUI,LALT,               SPC,                RALT,RGUI,LEFT,     RCTRL,LEFT,DOWN,RGHT),
};

const uint16_t fn_actions[] PROGMEM = {
};
