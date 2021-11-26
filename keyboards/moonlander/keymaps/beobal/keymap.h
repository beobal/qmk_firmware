#include QMK_KEYBOARD_H

// LINE_NAV is used to emulate vim '^' & '$' in the NAV layer. 
enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  LINE_NAV,
  LINE_SEL,
  CPS_WRD,
};

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _FUNC,
};

// Layer switching
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define FNCT    MO(_FUNC)
#define TAB_LWR LT(_LOWER, KC_TAB)
#define ESC_RSE LT(_RAISE, KC_ESC)
#define ENT_RSE LT(_RAISE, KC_ENT)

// Home row mods
#define A_LCTL LCTL_T(KC_A)
#define R_LOPT LOPT_T(KC_R)
#define S_LSFT LSFT_T(KC_S)
#define T_LCMD LCMD_T(KC_T)
#define D_HYPR HYPR_T(KC_D)
#define H_HYPR HYPR_T(KC_H)
#define N_RCMD RCMD_T(KC_N)
#define E_RSFT RSFT_T(KC_E)
#define I_ROPT ROPT_T(KC_I)
#define O_RCTL RCTL_T(KC_O)

// Text navigation / manipulation
#define LNE_BEG LCMD(KC_LEFT)
#define LNE_END LCMD(KC_RGHT)
#define DEL_LNE LCMD(KC_BSPC)
#define PRV_WRD LOPT(KC_LEFT)
#define NXT_WRD LOPT(KC_RGHT)

// Undo / redo / cut / copy / paste
#define UNDO  LCMD(KC_Z)
#define REDO  LSFT(UNDO)
#define CUT   LCMD(KC_X)
#define COPY  LCMD(KC_C)
#define PASTE LCMD(KC_V)

// Prev tab / next tab
#define NXT_TAB LCTL(KC_TAB)
#define PRV_TAB LSFT(NXT_TAB)

// CAPS_WORD
bool caps_word_on;
void caps_word_enable(void);
void caps_word_disable(void);

