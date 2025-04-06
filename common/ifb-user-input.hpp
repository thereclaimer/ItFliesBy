#ifndef IFB_USER_INPUT_HPP
#define IFB_USER_INPUT_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "ifb-macros.hpp"

namespace ifb {
/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef u16 key_code_t;
typedef u16 gamepad_button_code_t; 

struct key_code_composite_t;
struct keyboard_t;
struct mouse_position_t;
struct mouse_t;
struct gamepad_t;
struct input_t;

namespace input {

          void keyboard_key_down    (keyboard_t& keyboard, const key_code_t key_code);
          void keyboard_key_up      (keyboard_t& keyboard, const key_code_t key_code);
    const b8   keyboard_key_is_down (keyboard_t& keyboard, const key_code_t key_code);
    const b8   keyboard_key_is_up   (keyboard_t& keyboard, const key_code_t key_code);
    
    const key_code_composite_t keyboard_key_composite (const key_code_t key_code);

          void gamepad_button_down    (gamepad_t& gamepad, const gamepad_button_code_t button_code);
          void gamepad_button_up      (gamepad_t& gamepad, const gamepad_button_code_t button_code);
    const b8   gamepad_button_is_down (gamepad_t& gamepad, const gamepad_button_code_t button_code);

          void clear                  (input_t& input_ref);
};

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum key_code_ {
    key_code_Back                  = 0,
    key_code_Tab                   = 1,
    key_code_Clear                 = 2,
    key_code_Return                = 3,
    key_code_Shift                 = 4,
    key_code_Control               = 5,
    key_code_Menu                  = 6,
    key_code_Pause                 = 7,
    key_code_Capital               = 8,
    key_code_Escape                = 9,
    key_code_Space                 = 10,
    key_code_Prior                 = 11,
    key_code_Next                  = 12,
    key_code_End                   = 13,
    key_code_Home                  = 14,
    key_code_Left                  = 15,
    key_code_Up                    = 16, 
    key_code_Right                 = 17, 
    key_code_Down                  = 18, 
    key_code_Select                = 19, 
    key_code_Print                 = 20, 
    key_code_Snapshot              = 21,  
    key_code_Insert                = 22,  
    key_code_Delete                = 23, 
    key_code_Help                  = 24,
    key_code_0                     = 25,
    key_code_1                     = 26,
    key_code_2                     = 27,
    key_code_3                     = 28,
    key_code_4                     = 29,
    key_code_5                     = 30,
    key_code_6                     = 31,
    key_code_7                     = 32,
    key_code_8                     = 33,
    key_code_9                     = 34,
    key_code_A                     = 35,
    key_code_B                     = 36,
    key_code_C                     = 37,
    key_code_D                     = 38,
    key_code_E                     = 39,
    key_code_F                     = 40,
    key_code_G                     = 41,
    key_code_H                     = 42,
    key_code_I                     = 43,
    key_code_J                     = 44,
    key_code_K                     = 45,
    key_code_L                     = 46,
    key_code_M                     = 47,
    key_code_N                     = 48,
    key_code_O                     = 49,
    key_code_P                     = 50,
    key_code_Q                     = 51,
    key_code_R                     = 52,
    key_code_S                     = 53,
    key_code_T                     = 54,
    key_code_U                     = 55,
    key_code_V                     = 56,
    key_code_W                     = 57,
    key_code_X                     = 58,
    key_code_Y                     = 59,
    key_code_Z                     = 60,
    key_code_WinLeft               = 61,
    key_code_WinRight              = 62,
    key_code_Apps                  = 63,
    key_code_Numpad0               = 64,
    key_code_Numpad1               = 65,
    key_code_Numpad2               = 66,
    key_code_Numpad3               = 67,
    key_code_Numpad4               = 68,
    key_code_Numpad5               = 69,
    key_code_Numpad6               = 70,
    key_code_Numpad7               = 71,
    key_code_Numpad8               = 72,
    key_code_Numpad9               = 73,
    key_code_Multiply              = 74,
    key_code_Add                   = 75,
    key_code_Separator             = 76,
    key_code_Subtract              = 77,
    key_code_Decimal               = 78,
    key_code_Divide                = 79,
    key_code_F1                    = 80,
    key_code_F2                    = 81,
    key_code_F3                    = 82,
    key_code_F4                    = 83,
    key_code_F5                    = 84,
    key_code_F6                    = 85,
    key_code_F7                    = 86,
    key_code_F8                    = 87,
    key_code_F9                    = 88,
    key_code_F10                   = 89,
    key_code_F11                   = 90,
    key_code_F12                   = 91,
    key_code_Numlock               = 92,
    key_code_ShiftLeft             = 93,
    key_code_ShiftRight            = 94,
    key_code_ControlLeft           = 95,
    key_code_ControlRight          = 96,
    key_code_MenuLeft              = 97,
    key_code_MenuRight             = 98,
    key_code_VolumeMute            = 99,
    key_code_VolumeDown            = 100,
    key_code_VolumeUp              = 101,
    key_code_Plus                  = 102,
    key_code_Comma                 = 103,
    key_code_Minus                 = 104,
    key_code_Period                = 105,
    key_code_SlashForward_Question = 106,
    key_code_Tilde                 = 107,
    key_code_BracketOpen           = 108,
    key_code_SlashBack_Pipe        = 109,
    key_code_BracketClose          = 110,
    key_code_Quote                 = 111,
    key_code_Count                 = 112
};


#define IFB_KEYCODE_ARRAY_SIZE  key_code_Count / 8

struct keyboard_t {
    byte keycodes[IFB_KEYCODE_ARRAY_SIZE];
};

struct key_code_composite_t {
    u8 group_index;
    u8 bit_index;
};

inline const key_code_composite_t 
input::keyboard_key_composite(
    const key_code_t key_code) {

    key_code_composite_t composite = {0};

    const u32 key_group_size       = 8; 
    const f32 key_code_f32         = (f32)key_code; 
    const f32 key_group_index_f32  = key_code / key_group_size;
    const u32 key_group_index_u32  = (u32)key_group_index_f32;
    const u32 key_bit_index        = key_code - (key_group_index_u32 * key_group_size); 

    composite.bit_index   = key_bit_index;
    composite.group_index = key_group_index_u32;

    return(composite);
}

inline void
input::keyboard_key_down(
          keyboard_t& keyboard,
    const key_code_t   key_code) {

    const key_code_composite_t composite = input::keyboard_key_composite(key_code);

    ifb_macro_bit_set(composite.bit_index, keyboard.keycodes[composite.group_index]);
}

inline void
input::keyboard_key_up(
    keyboard_t& keyboard,
    key_code_t   key_code) {

    const key_code_composite_t composite = input::keyboard_key_composite(key_code);

    ifb_macro_bit_clear(composite.bit_index, keyboard.keycodes[composite.group_index]);
}

inline const b8
input::keyboard_key_is_down(
    keyboard_t& keyboard,
    key_code_t   key_code) {

    const key_code_composite_t composite = input::keyboard_key_composite(key_code);

    const b8 key_is_down = ifb_macro_bit_test(composite.bit_index, keyboard.keycodes[composite.group_index]);

    return(key_is_down);
}

inline const b8
input::keyboard_key_is_up(
    keyboard_t& keyboard,
    key_code_t   key_code) {

    const b8 key_is_up = !input::keyboard_key_is_down(keyboard,key_code);

    return(key_is_up);
}

namespace input {

    inline void keyboard_key_down_back                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Back);                  }
    inline void keyboard_key_down_tab                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Tab);                   }
    inline void keyboard_key_down_clear                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Clear);                 }
    inline void keyboard_key_down_return                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Return);                }
    inline void keyboard_key_down_shift                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Shift);                 }
    inline void keyboard_key_down_control                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Control);               }
    inline void keyboard_key_down_menu                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Menu);                  }
    inline void keyboard_key_down_pause                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Pause);                 }
    inline void keyboard_key_down_capital                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Capital);               }
    inline void keyboard_key_down_escape                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Escape);                }
    inline void keyboard_key_down_space                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Space);                 }
    inline void keyboard_key_down_prior                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Prior);                 }
    inline void keyboard_key_down_next                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Next);                  }
    inline void keyboard_key_down_end                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_End);                   }
    inline void keyboard_key_down_home                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Home);                  }
    inline void keyboard_key_down_left                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Left);                  }
    inline void keyboard_key_down_up                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Up);                    }
    inline void keyboard_key_down_right                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Right);                 }
    inline void keyboard_key_down_down                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Down);                  }
    inline void keyboard_key_down_select                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Select);                }
    inline void keyboard_key_down_print                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Print);                 }
    inline void keyboard_key_down_snapshot                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Snapshot);              }
    inline void keyboard_key_down_insert                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Insert);                }
    inline void keyboard_key_down_delete                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Delete);                }
    inline void keyboard_key_down_help                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Help);                  }
    inline void keyboard_key_down_0                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_0);                     }
    inline void keyboard_key_down_1                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_1);                     }
    inline void keyboard_key_down_2                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_2);                     }
    inline void keyboard_key_down_3                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_3);                     }
    inline void keyboard_key_down_4                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_4);                     }
    inline void keyboard_key_down_5                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_5);                     }
    inline void keyboard_key_down_6                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_6);                     }
    inline void keyboard_key_down_7                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_7);                     }
    inline void keyboard_key_down_8                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_8);                     }
    inline void keyboard_key_down_9                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_9);                     }
    inline void keyboard_key_down_a                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_A);                     }
    inline void keyboard_key_down_b                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_B);                     }
    inline void keyboard_key_down_c                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_C);                     }
    inline void keyboard_key_down_d                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_D);                     }
    inline void keyboard_key_down_e                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_E);                     }
    inline void keyboard_key_down_f                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F);                     }
    inline void keyboard_key_down_g                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_G);                     }
    inline void keyboard_key_down_h                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_H);                     }
    inline void keyboard_key_down_i                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_I);                     }
    inline void keyboard_key_down_j                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_J);                     }
    inline void keyboard_key_down_k                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_K);                     }
    inline void keyboard_key_down_l                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_L);                     }
    inline void keyboard_key_down_m                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_M);                     }
    inline void keyboard_key_down_n                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_N);                     }
    inline void keyboard_key_down_o                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_O);                     }
    inline void keyboard_key_down_p                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_P);                     }
    inline void keyboard_key_down_q                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Q);                     }
    inline void keyboard_key_down_r                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_R);                     }
    inline void keyboard_key_down_s                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_S);                     }
    inline void keyboard_key_down_t                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_T);                     }
    inline void keyboard_key_down_u                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_U);                     }
    inline void keyboard_key_down_v                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_V);                     }
    inline void keyboard_key_down_w                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_W);                     }
    inline void keyboard_key_down_x                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_X);                     }
    inline void keyboard_key_down_y                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Y);                     }
    inline void keyboard_key_down_z                            (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Z);                     }
    inline void keyboard_key_down_winleft                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_WinLeft);               }
    inline void keyboard_key_down_winright                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_WinRight);              }
    inline void keyboard_key_down_apps                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Apps);                  }
    inline void keyboard_key_down_numpad0                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad0);               }
    inline void keyboard_key_down_numpad1                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad1);               }
    inline void keyboard_key_down_numpad2                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad2);               }
    inline void keyboard_key_down_numpad3                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad3);               }
    inline void keyboard_key_down_numpad4                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad4);               }
    inline void keyboard_key_down_numpad5                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad5);               }
    inline void keyboard_key_down_numpad6                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad6);               }
    inline void keyboard_key_down_numpad7                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad7);               }
    inline void keyboard_key_down_numpad8                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad8);               }
    inline void keyboard_key_down_numpad9                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numpad9);               }
    inline void keyboard_key_down_multiply                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Multiply);              }
    inline void keyboard_key_down_add                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Add);                   }
    inline void keyboard_key_down_separator                    (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Separator);             }
    inline void keyboard_key_down_subtract                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Subtract);              }
    inline void keyboard_key_down_decimal                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Decimal);               }
    inline void keyboard_key_down_divide                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Divide);                }
    inline void keyboard_key_down_f1                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F1);                    }
    inline void keyboard_key_down_f2                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F2);                    }
    inline void keyboard_key_down_f3                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F3);                    }
    inline void keyboard_key_down_f4                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F4);                    }
    inline void keyboard_key_down_f5                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F5);                    }
    inline void keyboard_key_down_f6                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F6);                    }
    inline void keyboard_key_down_f7                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F7);                    }
    inline void keyboard_key_down_f8                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F8);                    }
    inline void keyboard_key_down_f9                           (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F9);                    }
    inline void keyboard_key_down_f10                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F10);                   }
    inline void keyboard_key_down_f11                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F11);                   }
    inline void keyboard_key_down_f12                          (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_F12);                   }
    inline void keyboard_key_down_numlock                      (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Numlock);               }
    inline void keyboard_key_down_shiftleft                    (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_ShiftLeft);             }
    inline void keyboard_key_down_shiftright                   (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_ShiftRight);            }
    inline void keyboard_key_down_controlleft                  (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_ControlLeft);           }
    inline void keyboard_key_down_controlright                 (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_ControlRight);          }
    inline void keyboard_key_down_menuleft                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_MenuLeft);              }
    inline void keyboard_key_down_menuright                    (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_MenuRight);             }
    inline void keyboard_key_down_volumemute                   (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_VolumeMute);            }
    inline void keyboard_key_down_volumedown                   (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_VolumeDown);            }
    inline void keyboard_key_down_volumeup                     (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_VolumeUp);              }
    inline void keyboard_key_down_plus                         (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Plus);                  }
    inline void keyboard_key_down_comma                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Comma);                 }
    inline void keyboard_key_down_minus                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Minus);                 }
    inline void keyboard_key_down_period                       (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Period);                }
    inline void keyboard_key_down_slashforward_question        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_SlashForward_Question); }
    inline void keyboard_key_down_tilde                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Tilde);                 }
    inline void keyboard_key_down_bracketopen                  (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_BracketOpen);           }
    inline void keyboard_key_down_slashback_pipe               (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_SlashBack_Pipe);        }
    inline void keyboard_key_down_bracketclose                 (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_BracketClose);          }
    inline void keyboard_key_down_quote                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Quote);                 }
    inline void keyboard_key_down_count                        (keyboard_t& keyboard) { input::keyboard_key_down(keyboard,key_code_Count);                 }

    inline void keyboard_key_up_back                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Back);                  }
    inline void keyboard_key_up_tab                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Tab);                   }
    inline void keyboard_key_up_clear                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Clear);                 }
    inline void keyboard_key_up_return                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Return);                }
    inline void keyboard_key_up_shift                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Shift);                 }
    inline void keyboard_key_up_control                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Control);               }
    inline void keyboard_key_up_menu                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Menu);                  }
    inline void keyboard_key_up_pause                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Pause);                 }
    inline void keyboard_key_up_capital                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Capital);               }
    inline void keyboard_key_up_escape                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Escape);                }
    inline void keyboard_key_up_space                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Space);                 }
    inline void keyboard_key_up_prior                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Prior);                 }
    inline void keyboard_key_up_next                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Next);                  }
    inline void keyboard_key_up_end                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_End);                   }
    inline void keyboard_key_up_home                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Home);                  }
    inline void keyboard_key_up_left                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Left);                  }
    inline void keyboard_key_up_up                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Up);                    }
    inline void keyboard_key_up_right                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Right);                 }
    inline void keyboard_key_up_down                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Down);                  }
    inline void keyboard_key_up_select                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Select);                }
    inline void keyboard_key_up_print                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Print);                 }
    inline void keyboard_key_up_snapshot                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Snapshot);              }
    inline void keyboard_key_up_insert                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Insert);                }
    inline void keyboard_key_up_delete                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Delete);                }
    inline void keyboard_key_up_help                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Help);                  }
    inline void keyboard_key_up_0                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_0);                     }
    inline void keyboard_key_up_1                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_1);                     }
    inline void keyboard_key_up_2                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_2);                     }
    inline void keyboard_key_up_3                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_3);                     }
    inline void keyboard_key_up_4                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_4);                     }
    inline void keyboard_key_up_5                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_5);                     }
    inline void keyboard_key_up_6                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_6);                     }
    inline void keyboard_key_up_7                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_7);                     }
    inline void keyboard_key_up_8                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_8);                     }
    inline void keyboard_key_up_9                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_9);                     }
    inline void keyboard_key_up_a                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_A);                     }
    inline void keyboard_key_up_b                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_B);                     }
    inline void keyboard_key_up_c                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_C);                     }
    inline void keyboard_key_up_d                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_D);                     }
    inline void keyboard_key_up_e                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_E);                     }
    inline void keyboard_key_up_f                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F);                     }
    inline void keyboard_key_up_g                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_G);                     }
    inline void keyboard_key_up_h                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_H);                     }
    inline void keyboard_key_up_i                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_I);                     }
    inline void keyboard_key_up_j                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_J);                     }
    inline void keyboard_key_up_k                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_K);                     }
    inline void keyboard_key_up_l                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_L);                     }
    inline void keyboard_key_up_m                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_M);                     }
    inline void keyboard_key_up_n                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_N);                     }
    inline void keyboard_key_up_o                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_O);                     }
    inline void keyboard_key_up_p                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_P);                     }
    inline void keyboard_key_up_q                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Q);                     }
    inline void keyboard_key_up_r                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_R);                     }
    inline void keyboard_key_up_s                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_S);                     }
    inline void keyboard_key_up_t                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_T);                     }
    inline void keyboard_key_up_u                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_U);                     }
    inline void keyboard_key_up_v                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_V);                     }
    inline void keyboard_key_up_w                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_W);                     }
    inline void keyboard_key_up_x                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_X);                     }
    inline void keyboard_key_up_y                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Y);                     }
    inline void keyboard_key_up_z                              (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Z);                     }
    inline void keyboard_key_up_winleft                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_WinLeft);               }
    inline void keyboard_key_up_winright                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_WinRight);              }
    inline void keyboard_key_up_apps                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Apps);                  }
    inline void keyboard_key_up_numpad0                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad0);               }
    inline void keyboard_key_up_numpad1                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad1);               }
    inline void keyboard_key_up_numpad2                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad2);               }
    inline void keyboard_key_up_numpad3                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad3);               }
    inline void keyboard_key_up_numpad4                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad4);               }
    inline void keyboard_key_up_numpad5                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad5);               }
    inline void keyboard_key_up_numpad6                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad6);               }
    inline void keyboard_key_up_numpad7                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad7);               }
    inline void keyboard_key_up_numpad8                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad8);               }
    inline void keyboard_key_up_numpad9                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numpad9);               }
    inline void keyboard_key_up_multiply                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Multiply);              }
    inline void keyboard_key_up_add                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Add);                   }
    inline void keyboard_key_up_separator                      (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Separator);             }
    inline void keyboard_key_up_subtract                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Subtract);              }
    inline void keyboard_key_up_decimal                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Decimal);               }
    inline void keyboard_key_up_divide                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Divide);                }
    inline void keyboard_key_up_f1                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F1);                    }
    inline void keyboard_key_up_f2                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F2);                    }
    inline void keyboard_key_up_f3                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F3);                    }
    inline void keyboard_key_up_f4                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F4);                    }
    inline void keyboard_key_up_f5                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F5);                    }
    inline void keyboard_key_up_f6                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F6);                    }
    inline void keyboard_key_up_f7                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F7);                    }
    inline void keyboard_key_up_f8                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F8);                    }
    inline void keyboard_key_up_f9                             (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F9);                    }
    inline void keyboard_key_up_f10                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F10);                   }
    inline void keyboard_key_up_f11                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F11);                   }
    inline void keyboard_key_up_f12                            (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_F12);                   }
    inline void keyboard_key_up_numlock                        (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Numlock);               }
    inline void keyboard_key_up_shiftleft                      (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_ShiftLeft);             }
    inline void keyboard_key_up_shiftright                     (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_ShiftRight);            }
    inline void keyboard_key_up_controlleft                    (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_ControlLeft);           }
    inline void keyboard_key_up_controlright                   (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_ControlRight);          }
    inline void keyboard_key_up_menuleft                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_MenuLeft);              }
    inline void keyboard_key_up_menuright                      (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_MenuRight);             }
    inline void keyboard_key_up_volumemute                     (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_VolumeMute);            }
    inline void keyboard_key_up_volumedown                     (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_VolumeDown);            }
    inline void keyboard_key_up_volumeup                       (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_VolumeUp);              }
    inline void keyboard_key_up_plus                           (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Plus);                  }
    inline void keyboard_key_up_comma                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Comma);                 }
    inline void keyboard_key_up_minus                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Minus);                 }
    inline void keyboard_key_up_period                         (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Period);                }
    inline void keyboard_key_up_slashforward_question          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_SlashForward_Question); }
    inline void keyboard_key_up_tilde                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Tilde);                 }
    inline void keyboard_key_up_bracketopen                    (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_BracketOpen);           }
    inline void keyboard_key_up_slashback_pipe                 (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_SlashBack_Pipe);        }
    inline void keyboard_key_up_bracketclose                   (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_BracketClose);          }
    inline void keyboard_key_up_quote                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Quote);                 }
    inline void keyboard_key_up_count                          (keyboard_t& keyboard) { input::keyboard_key_up(keyboard,key_code_Count);                 }

    inline const b8 keyboard_key_is_up_back                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Back));                  }
    inline const b8 keyboard_key_is_up_tab                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Tab));                   }
    inline const b8 keyboard_key_is_up_clear                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Clear));                 }
    inline const b8 keyboard_key_is_up_return                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Return));                }
    inline const b8 keyboard_key_is_up_shift                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Shift));                 }
    inline const b8 keyboard_key_is_up_control                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Control));               }
    inline const b8 keyboard_key_is_up_menu                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Menu));                  }
    inline const b8 keyboard_key_is_up_pause                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Pause));                 }
    inline const b8 keyboard_key_is_up_capital                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Capital));               }
    inline const b8 keyboard_key_is_up_escape                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Escape));                }
    inline const b8 keyboard_key_is_up_space                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Space));                 }
    inline const b8 keyboard_key_is_up_prior                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Prior));                 }
    inline const b8 keyboard_key_is_up_next                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Next));                  }
    inline const b8 keyboard_key_is_up_end                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_End));                   }
    inline const b8 keyboard_key_is_up_home                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Home));                  }
    inline const b8 keyboard_key_is_up_left                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Left));                  }
    inline const b8 keyboard_key_is_up_up                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Up));                    }
    inline const b8 keyboard_key_is_up_right                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Right));                 }
    inline const b8 keyboard_key_is_up_down                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Down));                  }
    inline const b8 keyboard_key_is_up_select                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Select));                }
    inline const b8 keyboard_key_is_up_print                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Print));                 }
    inline const b8 keyboard_key_is_up_snapshot                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Snapshot));              }
    inline const b8 keyboard_key_is_up_insert                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Insert));                }
    inline const b8 keyboard_key_is_up_delete                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Delete));                }
    inline const b8 keyboard_key_is_up_help                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Help));                  }
    inline const b8 keyboard_key_is_up_0                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_0));                     }
    inline const b8 keyboard_key_is_up_1                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_1));                     }
    inline const b8 keyboard_key_is_up_2                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_2));                     }
    inline const b8 keyboard_key_is_up_3                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_3));                     }
    inline const b8 keyboard_key_is_up_4                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_4));                     }
    inline const b8 keyboard_key_is_up_5                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_5));                     }
    inline const b8 keyboard_key_is_up_6                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_6));                     }
    inline const b8 keyboard_key_is_up_7                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_7));                     }
    inline const b8 keyboard_key_is_up_8                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_8));                     }
    inline const b8 keyboard_key_is_up_9                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_9));                     }
    inline const b8 keyboard_key_is_up_a                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_A));                     }
    inline const b8 keyboard_key_is_up_b                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_B));                     }
    inline const b8 keyboard_key_is_up_c                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_C));                     }
    inline const b8 keyboard_key_is_up_d                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_D));                     }
    inline const b8 keyboard_key_is_up_e                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_E));                     }
    inline const b8 keyboard_key_is_up_f                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F));                     }
    inline const b8 keyboard_key_is_up_g                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_G));                     }
    inline const b8 keyboard_key_is_up_h                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_H));                     }
    inline const b8 keyboard_key_is_up_i                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_I));                     }
    inline const b8 keyboard_key_is_up_j                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_J));                     }
    inline const b8 keyboard_key_is_up_k                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_K));                     }
    inline const b8 keyboard_key_is_up_l                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_L));                     }
    inline const b8 keyboard_key_is_up_m                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_M));                     }
    inline const b8 keyboard_key_is_up_n                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_N));                     }
    inline const b8 keyboard_key_is_up_o                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_O));                     }
    inline const b8 keyboard_key_is_up_p                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_P));                     }
    inline const b8 keyboard_key_is_up_q                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Q));                     }
    inline const b8 keyboard_key_is_up_r                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_R));                     }
    inline const b8 keyboard_key_is_up_s                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_S));                     }
    inline const b8 keyboard_key_is_up_t                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_T));                     }
    inline const b8 keyboard_key_is_up_u                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_U));                     }
    inline const b8 keyboard_key_is_up_v                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_V));                     }
    inline const b8 keyboard_key_is_up_w                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_W));                     }
    inline const b8 keyboard_key_is_up_x                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_X));                     }
    inline const b8 keyboard_key_is_up_y                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Y));                     }
    inline const b8 keyboard_key_is_up_z                       (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Z));                     }
    inline const b8 keyboard_key_is_up_winleft                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_WinLeft));               }
    inline const b8 keyboard_key_is_up_winright                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_WinRight));              }
    inline const b8 keyboard_key_is_up_apps                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Apps));                  }
    inline const b8 keyboard_key_is_up_numpad0                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad0));               }
    inline const b8 keyboard_key_is_up_numpad1                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad1));               }
    inline const b8 keyboard_key_is_up_numpad2                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad2));               }
    inline const b8 keyboard_key_is_up_numpad3                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad3));               }
    inline const b8 keyboard_key_is_up_numpad4                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad4));               }
    inline const b8 keyboard_key_is_up_numpad5                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad5));               }
    inline const b8 keyboard_key_is_up_numpad6                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad6));               }
    inline const b8 keyboard_key_is_up_numpad7                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad7));               }
    inline const b8 keyboard_key_is_up_numpad8                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad8));               }
    inline const b8 keyboard_key_is_up_numpad9                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numpad9));               }
    inline const b8 keyboard_key_is_up_multiply                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Multiply));              }
    inline const b8 keyboard_key_is_up_add                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Add));                   }
    inline const b8 keyboard_key_is_up_separator               (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Separator));             }
    inline const b8 keyboard_key_is_up_subtract                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Subtract));              }
    inline const b8 keyboard_key_is_up_decimal                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Decimal));               }
    inline const b8 keyboard_key_is_up_divide                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Divide));                }
    inline const b8 keyboard_key_is_up_f1                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F1));                    }
    inline const b8 keyboard_key_is_up_f2                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F2));                    }
    inline const b8 keyboard_key_is_up_f3                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F3));                    }
    inline const b8 keyboard_key_is_up_f4                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F4));                    }
    inline const b8 keyboard_key_is_up_f5                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F5));                    }
    inline const b8 keyboard_key_is_up_f6                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F6));                    }
    inline const b8 keyboard_key_is_up_f7                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F7));                    }
    inline const b8 keyboard_key_is_up_f8                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F8));                    }
    inline const b8 keyboard_key_is_up_f9                      (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F9));                    }
    inline const b8 keyboard_key_is_up_f10                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F10));                   }
    inline const b8 keyboard_key_is_up_f11                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F11));                   }
    inline const b8 keyboard_key_is_up_f12                     (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_F12));                   }
    inline const b8 keyboard_key_is_up_numlock                 (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Numlock));               }
    inline const b8 keyboard_key_is_up_shiftleft               (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_ShiftLeft));             }
    inline const b8 keyboard_key_is_up_shiftright              (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_ShiftRight));            }
    inline const b8 keyboard_key_is_up_controlleft             (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_ControlLeft));           }
    inline const b8 keyboard_key_is_up_controlright            (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_ControlRight));          }
    inline const b8 keyboard_key_is_up_menuleft                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_MenuLeft));              }
    inline const b8 keyboard_key_is_up_menuright               (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_MenuRight));             }
    inline const b8 keyboard_key_is_up_volumemute              (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_VolumeMute));            }
    inline const b8 keyboard_key_is_up_volumedown              (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_VolumeDown));            }
    inline const b8 keyboard_key_is_up_volumeup                (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_VolumeUp));              }
    inline const b8 keyboard_key_is_up_plus                    (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Plus));                  }
    inline const b8 keyboard_key_is_up_comma                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Comma));                 }
    inline const b8 keyboard_key_is_up_minus                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Minus));                 }
    inline const b8 keyboard_key_is_up_period                  (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Period));                }
    inline const b8 keyboard_key_is_up_slashforward_question   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_SlashForward_Question)); }
    inline const b8 keyboard_key_is_up_tilde                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Tilde));                 }
    inline const b8 keyboard_key_is_up_bracketopen             (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_BracketOpen));           }
    inline const b8 keyboard_key_is_up_slashback_pipe          (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_SlashBack_Pipe));        }
    inline const b8 keyboard_key_is_up_bracketclose            (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_BracketClose));          }
    inline const b8 keyboard_key_is_up_quote                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Quote));                 }
    inline const b8 keyboard_key_is_up_count                   (keyboard_t& keyboard) { return(input::keyboard_key_is_up(keyboard,key_code_Count));                 }

    inline const b8 keyboard_key_is_down_back                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Back));                  }
    inline const b8 keyboard_key_is_down_tab                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Tab));                   }
    inline const b8 keyboard_key_is_down_clear                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Clear));                 }
    inline const b8 keyboard_key_is_down_return                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Return));                }
    inline const b8 keyboard_key_is_down_shift                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Shift));                 }
    inline const b8 keyboard_key_is_down_control               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Control));               }
    inline const b8 keyboard_key_is_down_menu                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Menu));                  }
    inline const b8 keyboard_key_is_down_pause                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Pause));                 }
    inline const b8 keyboard_key_is_down_capital               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Capital));               }
    inline const b8 keyboard_key_is_down_escape                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Escape));                }
    inline const b8 keyboard_key_is_down_space                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Space));                 }
    inline const b8 keyboard_key_is_down_prior                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Prior));                 }
    inline const b8 keyboard_key_is_down_next                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Next));                  }
    inline const b8 keyboard_key_is_down_end                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_End));                   }
    inline const b8 keyboard_key_is_down_home                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Home));                  }
    inline const b8 keyboard_key_is_down_left                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Left));                  }
    inline const b8 keyboard_key_is_down_up                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Up));                    }
    inline const b8 keyboard_key_is_down_right                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Right));                 }
    inline const b8 keyboard_key_is_down_down                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Down));                  }
    inline const b8 keyboard_key_is_down_select                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Select));                }
    inline const b8 keyboard_key_is_down_print                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Print));                 }
    inline const b8 keyboard_key_is_down_snapshot              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Snapshot));              }
    inline const b8 keyboard_key_is_down_insert                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Insert));                }
    inline const b8 keyboard_key_is_down_delete                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Delete));                }
    inline const b8 keyboard_key_is_down_help                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Help));                  }
    inline const b8 keyboard_key_is_down_0                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_0));                     }
    inline const b8 keyboard_key_is_down_1                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_1));                     }
    inline const b8 keyboard_key_is_down_2                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_2));                     }
    inline const b8 keyboard_key_is_down_3                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_3));                     }
    inline const b8 keyboard_key_is_down_4                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_4));                     }
    inline const b8 keyboard_key_is_down_5                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_5));                     }
    inline const b8 keyboard_key_is_down_6                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_6));                     }
    inline const b8 keyboard_key_is_down_7                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_7));                     }
    inline const b8 keyboard_key_is_down_8                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_8));                     }
    inline const b8 keyboard_key_is_down_9                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_9));                     }
    inline const b8 keyboard_key_is_down_a                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_A));                     }
    inline const b8 keyboard_key_is_down_b                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_B));                     }
    inline const b8 keyboard_key_is_down_c                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_C));                     }
    inline const b8 keyboard_key_is_down_d                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_D));                     }
    inline const b8 keyboard_key_is_down_e                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_E));                     }
    inline const b8 keyboard_key_is_down_f                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F));                     }
    inline const b8 keyboard_key_is_down_g                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_G));                     }
    inline const b8 keyboard_key_is_down_h                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_H));                     }
    inline const b8 keyboard_key_is_down_i                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_I));                     }
    inline const b8 keyboard_key_is_down_j                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_J));                     }
    inline const b8 keyboard_key_is_down_k                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_K));                     }
    inline const b8 keyboard_key_is_down_l                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_L));                     }
    inline const b8 keyboard_key_is_down_m                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_M));                     }
    inline const b8 keyboard_key_is_down_n                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_N));                     }
    inline const b8 keyboard_key_is_down_o                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_O));                     }
    inline const b8 keyboard_key_is_down_p                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_P));                     }
    inline const b8 keyboard_key_is_down_q                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Q));                     }
    inline const b8 keyboard_key_is_down_r                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_R));                     }
    inline const b8 keyboard_key_is_down_s                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_S));                     }
    inline const b8 keyboard_key_is_down_t                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_T));                     }
    inline const b8 keyboard_key_is_down_u                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_U));                     }
    inline const b8 keyboard_key_is_down_v                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_V));                     }
    inline const b8 keyboard_key_is_down_w                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_W));                     }
    inline const b8 keyboard_key_is_down_x                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_X));                     }
    inline const b8 keyboard_key_is_down_y                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Y));                     }
    inline const b8 keyboard_key_is_down_z                     (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Z));                     }
    inline const b8 keyboard_key_is_down_winleft               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_WinLeft));               }
    inline const b8 keyboard_key_is_down_winright              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_WinRight));              }
    inline const b8 keyboard_key_is_down_apps                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Apps));                  }
    inline const b8 keyboard_key_is_down_numpad0               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad0));               }
    inline const b8 keyboard_key_is_down_numpad1               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad1));               }
    inline const b8 keyboard_key_is_down_numpad2               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad2));               }
    inline const b8 keyboard_key_is_down_numpad3               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad3));               }
    inline const b8 keyboard_key_is_down_numpad4               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad4));               }
    inline const b8 keyboard_key_is_down_numpad5               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad5));               }
    inline const b8 keyboard_key_is_down_numpad6               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad6));               }
    inline const b8 keyboard_key_is_down_numpad7               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad7));               }
    inline const b8 keyboard_key_is_down_numpad8               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad8));               }
    inline const b8 keyboard_key_is_down_numpad9               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numpad9));               }
    inline const b8 keyboard_key_is_down_multiply              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Multiply));              }
    inline const b8 keyboard_key_is_down_add                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Add));                   }
    inline const b8 keyboard_key_is_down_separator             (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Separator));             }
    inline const b8 keyboard_key_is_down_subtract              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Subtract));              }
    inline const b8 keyboard_key_is_down_decimal               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Decimal));               }
    inline const b8 keyboard_key_is_down_divide                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Divide));                }
    inline const b8 keyboard_key_is_down_f1                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F1));                    }
    inline const b8 keyboard_key_is_down_f2                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F2));                    }
    inline const b8 keyboard_key_is_down_f3                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F3));                    }
    inline const b8 keyboard_key_is_down_f4                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F4));                    }
    inline const b8 keyboard_key_is_down_f5                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F5));                    }
    inline const b8 keyboard_key_is_down_f6                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F6));                    }
    inline const b8 keyboard_key_is_down_f7                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F7));                    }
    inline const b8 keyboard_key_is_down_f8                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F8));                    }
    inline const b8 keyboard_key_is_down_f9                    (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F9));                    }
    inline const b8 keyboard_key_is_down_f10                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F10));                   }
    inline const b8 keyboard_key_is_down_f11                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F11));                   }
    inline const b8 keyboard_key_is_down_f12                   (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_F12));                   }
    inline const b8 keyboard_key_is_down_numlock               (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Numlock));               }
    inline const b8 keyboard_key_is_down_shiftleft             (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_ShiftLeft));             }
    inline const b8 keyboard_key_is_down_shiftright            (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_ShiftRight));            }
    inline const b8 keyboard_key_is_down_controlleft           (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_ControlLeft));           }
    inline const b8 keyboard_key_is_down_controlright          (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_ControlRight));          }
    inline const b8 keyboard_key_is_down_menuleft              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_MenuLeft));              }
    inline const b8 keyboard_key_is_down_menuright             (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_MenuRight));             }
    inline const b8 keyboard_key_is_down_volumemute            (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_VolumeMute));            }
    inline const b8 keyboard_key_is_down_volumedown            (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_VolumeDown));            }
    inline const b8 keyboard_key_is_down_volumeup              (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_VolumeUp));              }
    inline const b8 keyboard_key_is_down_plus                  (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Plus));                  }
    inline const b8 keyboard_key_is_down_comma                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Comma));                 }
    inline const b8 keyboard_key_is_down_minus                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Minus));                 }
    inline const b8 keyboard_key_is_down_period                (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Period));                }
    inline const b8 keyboard_key_is_down_slashforward_question (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_SlashForward_Question)); }
    inline const b8 keyboard_key_is_down_tilde                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Tilde));                 }
    inline const b8 keyboard_key_is_down_bracketopen           (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_BracketOpen));           }
    inline const b8 keyboard_key_is_down_slashback_pipe        (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_SlashBack_Pipe));        }
    inline const b8 keyboard_key_is_down_bracketclose          (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_BracketClose));          }
    inline const b8 keyboard_key_is_down_quote                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Quote));                 }
    inline const b8 keyboard_key_is_down_count                 (keyboard_t& keyboard) { return(input::keyboard_key_is_down(keyboard,key_code_Count));                 }
};

/**********************************************************************************/
/* MOUSE                                                                          */
/**********************************************************************************/

struct mouse_position_t {
    s32 x;
    s32 y;
};

struct mouse_t {
    struct {
        mouse_position_t current;
        mouse_position_t delta;
    } position;
    s32 wheel;
    b8  button_left;
    b8  button_right;
};

/**********************************************************************************/
/* GAMEPAD                                                                        */
/**********************************************************************************/

enum gamepad_button_code_t_ {
    gamepad_button_code_t_DpadUp      = 0x00, 
    gamepad_button_code_t_DpadDown    = 0x01, 
    gamepad_button_code_t_DpadLeft    = 0x02, 
    gamepad_button_code_t_DpadRight   = 0x03, 
    gamepad_button_code_t_Start       = 0x04, 
    gamepad_button_code_t_Select      = 0x05, 
    gamepad_button_code_t_StickLeft   = 0x06, 
    gamepad_button_code_t_StickRight  = 0x07, 
    gamepad_button_code_t_BumberLeft  = 0x08, 
    gamepad_button_code_t_BumberRight = 0x09, 
    gamepad_button_code_t_BpadA       = 0x0C, 
    gamepad_button_code_t_BpadB       = 0x0D, 
    gamepad_button_code_t_BpadX       = 0x0E, 
    gamepad_button_code_t_BpadY       = 0x0F, 
};

struct gamepad_t {
    gamepad_button_code_t button_codes;
    struct {
        f32 left;
        f32 right;
    } triggers;
};

inline void
input::gamepad_button_down(
    gamepad_t&          gamepad,
    gamepad_button_code_t button_code) {

    ifb_macro_bit_set(
        button_code,
        gamepad.button_codes);                
}

inline void
input::gamepad_button_up(
    gamepad_t&          gamepad,
    gamepad_button_code_t button_code) {
    
    ifb_macro_bit_clear(            
        button_code,
        gamepad.button_codes);                
}

inline const b8
input::gamepad_button_is_down(
    gamepad_t&          gamepad,
    gamepad_button_code_t button_code) {

    const b8 key_is_down = ifb_macro_bit_test(
        button_code,
        gamepad.button_codes);                        

    return(key_is_down);
}

/**********************************************************************************/
/* INPUT                                                                          */
/**********************************************************************************/

struct input_t {
    keyboard_t keyboard;
    mouse_t    mouse;
    gamepad_t  gamepad;
};

inline void
input::clear(
    input_t& input_ref) {
    
    input_ref = {0};
}
};//namespace ifb
#endif //IFB_USER_INPUT_HPP