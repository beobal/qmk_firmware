#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_moonlander(
    XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,            XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,      
    XXXXXXX,       KC_Q   ,       KC_W   ,       KC_F   ,       KC_P   ,       KC_B   ,       XXXXXXX,            XXXXXXX,       KC_J   ,       KC_L   ,       KC_U   ,       KC_Y   ,       KC_QUOT,       XXXXXXX,
    KC_GESC,       A_LCTL ,       R_LOPT ,       S_LSFT ,       T_LCMD ,       KC_G   ,       XXXXXXX,            XXXXXXX,       KC_M   ,       N_RCMD ,       E_RSFT ,       I_ROPT ,       O_RCTL ,       KC_SCLN,
    CPS_WRD,       KC_Z   ,       KC_X   ,       KC_C   ,       D_HYPR ,       KC_V   ,                                          KC_K   ,       H_HYPR ,       KC_COMM,       KC_DOT ,       KC_SLSH,       KC_BSLS,
    XXXXXXX,       XXXXXXX,       XXXXXXX,       TAB_LWR,       KC_SPC ,                      XXXXXXX,            XXXXXXX,                      KC_BSPC,       ENT_RSE,       XXXXXXX,       XXXXXXX,       XXXXXXX,      
                                                                RAISE  ,       FNCT   ,       XXXXXXX,            XXXXXXX,       FNCT   ,         LOWER
  ),

  [_LOWER] = LAYOUT_moonlander(
    _______,       _______,       _______,       _______,       _______,       _______,       _______,            _______,       _______,       _______,       _______,       _______,       _______,       _______, 
    _______,       KC_1,          KC_2,          KC_3,          KC_4,          KC_5,          _______,            _______,       KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          _______,
    _______,       KC_EXLM,       KC_PLUS,       KC_LPRN,       KC_RPRN,       KC_HASH,       _______,            _______,       KC_PIPE,       KC_MINS,       KC_EQL,        KC_UNDS,       KC_ASTR,       KC_GRV,
    KC_CIRC,       KC_DLR,        KC_AT,         KC_LCBR,       KC_RCBR,       KC_AMPR,                                          KC_PERC,       KC_LBRC,       KC_RBRC,       KC_KP_DOT,     _______,       _______, 
    _______,       _______,       _______,       _______,       _______,                      _______,            _______,                      _______,       _______,       _______,       _______,       _______, 
                                                                _______,       _______,       _______,            _______,       _______,       _______
  ),

  [_RAISE] = LAYOUT_moonlander(
    _______,       _______,       _______,       _______,       _______,       _______,       _______,            _______,       _______,       _______,       _______,       _______,       _______,       _______,          
    _______,       KC_MUTE,       KC_VOLD,       KC_VOLU,       KC_MPLY,       _______,       _______,            _______,       _______,       KC_PGUP,       PRV_WRD,       LNE_BEG,       DEL_LNE,       _______,
    KC_GESC,       KC_LCTL,       KC_LALT,       KC_LSFT,       KC_LCMD,       KC_CAPS,       _______,            _______,       KC_LEFT,       KC_DOWN,       KC_UP  ,       KC_RIGHT,      XXXXXXX,       _______, 
    _______,       UNDO   ,       CUT    ,       COPY   ,       PASTE  ,       REDO   ,                                          _______,       KC_PGDN,       NXT_WRD,       LNE_END,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,                      _______,            _______,                      _______,       _______,       _______,       _______,       _______, 
                                                                TO(0),         _______,       _______,            _______,       _______,       _______
  ),

  [_FUNC] = LAYOUT_moonlander(
    _______,       _______,       _______,       _______,       _______,       _______,       _______,            _______,       _______,       _______,       _______,       _______,       _______,       _______, 
    _______,       KC_F1  ,       KC_F2  ,       KC_F3  ,       KC_F4  ,       KC_F5  ,       _______,            _______,       KC_F6  ,       KC_F7  ,       KC_F8  ,       KC_F9  ,       KC_F10 ,       _______, 
		_______,       KC_LCTL,       KC_LALT,       KC_LSFT,       KC_LCMD,       _______,       _______,            _______,       XXXXXXX,       KC_LCMD,       KC_RSFT,       KC_RALT,       KC_F11 ,       _______, 
    _______,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       _______,                                          _______,       _______,       _______,       _______,       KC_F12 ,       _______, 
    _______,       _______,       _______,       _______,       _______,                      _______,            _______,                      _______,       _______,       _______,       _______,       _______, 
                                                                TO(0),         _______,       _______,            _______,       _______,       _______
  ),

};

// CAPS_WORD: A "smart" Caps Lock key that only capitalizes the next identifier you type
// and then toggles off Caps Lock automatically when you're done.
bool caps_word_on;
void caps_word_enable(void) {
    caps_word_on = true;
    if (!(host_keyboard_led_state().caps_lock)) {
        tap_code(KC_CAPS);
    }
}

void caps_word_disable(void) {
    caps_word_on = false;
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

void process_caps_word(uint16_t keycode, const keyrecord_t *record) {
    // Update caps word state
    if (caps_word_on) {
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) { return; }
                // Get the base tapping keycode of a mod- or layer-tap key
                keycode = GET_TAP_KC(keycode);
                break;
            default:
                break;
        }

        switch (keycode) {
            // Keycodes to shift
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    caps_word_enable();
                }
            // Keycodes that enable caps word but shouldn't get shifted
            case KC_MINS:
            case KC_BSPC:
            case KC_UNDS:
            case KC_PIPE:
            case CPS_WRD:
                // If chording mods, disable caps word
                if (record->event.pressed && (get_mods() != MOD_LSFT) && (get_mods() != 0)) {
                    caps_word_disable();
                }
                break;
            default:
                // Any other keycode should automatically disable caps
                if (record->event.pressed) {
                    caps_word_disable();
                }
                break;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
		process_caps_word(keycode, record);

    switch (keycode) {
    case CPS_WRD:
        // Toggle `caps_word_on`
        if (record->event.pressed) {
            if (caps_word_on) {
                caps_word_disable();
            } else {
                caps_word_enable();
            }
            return false;
        }
        break; 

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;

    case LINE_NAV:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
          // release shift so we don't select text
          clear_mods();          
          // move to end of line
          SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LGUI));
        } else {
          // move to start of line
          SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LGUI));
        }
      }
      return false;

    case LINE_SEL:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
          // release shift so we don't select text too early
          clear_mods();          
          // move to start of line
          SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_UP(X_LGUI));
          // move to end of line holding shift
          SEND_STRING(SS_DOWN(X_LSHIFT) SS_DOWN(X_LGUI) SS_TAP(X_RIGHT) SS_UP(X_LGUI) SS_UP(X_LSHIFT));
        }
      }
      return false;
  }
  return true;
}


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    // _BASE
    [0] = {
      
      // left half, first col is the leftmost
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 1
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 2 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 3 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 4
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 5 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},                             // col 6 
      {134,255,213}, {134,255,213}, {134,255,213},                                            // col 7 
      {12,225,241}, {12,225,241}, {134,255,213},                                              // piano keys 
      {134,255,213},                                                                          // launch/any 

      // right half, first col is the rightmost
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 7 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 6 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 5 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 4 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},              // col 3 
      {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213},                             // col 2 
      {134,255,213}, {134,255,213}, {134,255,213},                                            // col 1 
      {12,225,241}, {12,225,241}, {134,255,213},                                              // piano keys 
      {134,255,213}                                                                           // launch/any 
    },

    // _LOWER
    [1] = { 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233},
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233},
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, 
      {12,225,241}, {12,225,241}, {180,255,233}, 
      {180,255,233}, 
      
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233},
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233},
      {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, 
      {180,255,233}, {180,255,233}, {180,255,233}, 
      {12,225,241}, {12,225,241}, {180,255,233}, 
      {180,255,233} 
    },

    // _RAISE
    [2] = { 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255},
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255},
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255},
      {14,255,255}, {14,255,255}, {14,255,255}, 
      {12,225,241}, {12,225,241}, {14,255,255}, 
      {14,255,255}, 

      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255},
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255},
      {14,255,255}, {14,255,255}, {14,255,255}, {14,255,255}, 
      {14,255,255}, {14,255,255}, {14,255,255}, 
      {12,225,241}, {12,225,241}, {14,255,255}, 
      {14,255,255} 
    },

    // _FUNC
    [3] = { 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159},
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159},
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, 
      {12,225,241}, {12,225,241}, {255,228,159}, 
      {255,228,159}, 
      
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159},
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159},
      {255,228,159}, {255,228,159}, {255,228,159}, {255,228,159}, 
      {255,228,159}, {255,228,159}, {255,228,159}, 
      {12,225,241}, {12,225,241}, {255,228,159}, 
      {255,228,159} 
    },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}
