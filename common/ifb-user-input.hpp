#ifndef IFB_USER_INPUT_HPP
#define IFB_USER_INPUT_HPP

#include "ifb-types-primitives.hpp"
#include "ifb-scopes.hpp"
#include "ifb-macros.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef IFBU16 IFBKeyCode;
typedef IFBU16 IFBGamepadButtonCode; 

struct IFBKeyCodeComposite;
struct IFBKeyboard;
struct IFBMousePosition;
struct IFBMouse;
struct IFBGamepad;
struct IFBInput;

namespace ifb_input {

          IFBVoid keyboard_key_down      (IFBKeyboard& keyboard, const IFBKeyCode key_code);
          IFBVoid keyboard_key_up        (IFBKeyboard& keyboard, const IFBKeyCode key_code);
    const IFBB8   keyboard_key_is_down   (IFBKeyboard& keyboard, const IFBKeyCode key_code);
    const IFBB8   keyboard_key_is_up     (IFBKeyboard& keyboard, const IFBKeyCode key_code);
    
    const IFBKeyCodeComposite keyboard_key_composite (const IFBKeyCode key_code);

          IFBVoid gamepad_button_down    (IFBGamepad& gamepad, const IFBGamepadButtonCode button_code);
          IFBVoid gamepad_button_up      (IFBGamepad& gamepad, const IFBGamepadButtonCode button_code);
    const IFBB8   gamepad_button_is_down (IFBGamepad& gamepad, const IFBGamepadButtonCode button_code);

          IFBVoid clear                  (IFBInput& input_ref);
};

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum IFBKeyCode_ {
    IFBKeyCode_Back                  = 0,
    IFBKeyCode_Tab                   = 1,
    IFBKeyCode_Clear                 = 2,
    IFBKeyCode_Return                = 3,
    IFBKeyCode_Shift                 = 4,
    IFBKeyCode_Control               = 5,
    IFBKeyCode_Menu                  = 6,
    IFBKeyCode_Pause                 = 7,
    IFBKeyCode_Capital               = 8,
    IFBKeyCode_Escape                = 9,
    IFBKeyCode_Space                 = 10,
    IFBKeyCode_Prior                 = 11,
    IFBKeyCode_Next                  = 12,
    IFBKeyCode_End                   = 13,
    IFBKeyCode_Home                  = 14,
    IFBKeyCode_Left                  = 15,
    IFBKeyCode_Up                    = 16, 
    IFBKeyCode_Right                 = 17, 
    IFBKeyCode_Down                  = 18, 
    IFBKeyCode_Select                = 19, 
    IFBKeyCode_Print                 = 20, 
    IFBKeyCode_Snapshot              = 21,  
    IFBKeyCode_Insert                = 22,  
    IFBKeyCode_Delete                = 23, 
    IFBKeyCode_Help                  = 24,
    IFBKeyCode_0                     = 25,
    IFBKeyCode_1                     = 26,
    IFBKeyCode_2                     = 27,
    IFBKeyCode_3                     = 28,
    IFBKeyCode_4                     = 29,
    IFBKeyCode_5                     = 30,
    IFBKeyCode_6                     = 31,
    IFBKeyCode_7                     = 32,
    IFBKeyCode_8                     = 33,
    IFBKeyCode_9                     = 34,
    IFBKeyCode_A                     = 35,
    IFBKeyCode_B                     = 36,
    IFBKeyCode_C                     = 37,
    IFBKeyCode_D                     = 38,
    IFBKeyCode_E                     = 39,
    IFBKeyCode_F                     = 40,
    IFBKeyCode_G                     = 41,
    IFBKeyCode_H                     = 42,
    IFBKeyCode_I                     = 43,
    IFBKeyCode_J                     = 44,
    IFBKeyCode_K                     = 45,
    IFBKeyCode_L                     = 46,
    IFBKeyCode_M                     = 47,
    IFBKeyCode_N                     = 48,
    IFBKeyCode_O                     = 49,
    IFBKeyCode_P                     = 50,
    IFBKeyCode_Q                     = 51,
    IFBKeyCode_R                     = 52,
    IFBKeyCode_S                     = 53,
    IFBKeyCode_T                     = 54,
    IFBKeyCode_U                     = 55,
    IFBKeyCode_V                     = 56,
    IFBKeyCode_W                     = 57,
    IFBKeyCode_X                     = 58,
    IFBKeyCode_Y                     = 59,
    IFBKeyCode_Z                     = 60,
    IFBKeyCode_WinLeft               = 61,
    IFBKeyCode_WinRight              = 62,
    IFBKeyCode_Apps                  = 63,
    IFBKeyCode_Numpad0               = 64,
    IFBKeyCode_Numpad1               = 65,
    IFBKeyCode_Numpad2               = 66,
    IFBKeyCode_Numpad3               = 67,
    IFBKeyCode_Numpad4               = 68,
    IFBKeyCode_Numpad5               = 69,
    IFBKeyCode_Numpad6               = 70,
    IFBKeyCode_Numpad7               = 71,
    IFBKeyCode_Numpad8               = 72,
    IFBKeyCode_Numpad9               = 73,
    IFBKeyCode_Multiply              = 74,
    IFBKeyCode_Add                   = 75,
    IFBKeyCode_Separator             = 76,
    IFBKeyCode_Subtract              = 77,
    IFBKeyCode_Decimal               = 78,
    IFBKeyCode_Divide                = 79,
    IFBKeyCode_F1                    = 80,
    IFBKeyCode_F2                    = 81,
    IFBKeyCode_F3                    = 82,
    IFBKeyCode_F4                    = 83,
    IFBKeyCode_F5                    = 84,
    IFBKeyCode_F6                    = 85,
    IFBKeyCode_F7                    = 86,
    IFBKeyCode_F8                    = 87,
    IFBKeyCode_F9                    = 88,
    IFBKeyCode_F10                   = 89,
    IFBKeyCode_F11                   = 90,
    IFBKeyCode_F12                   = 91,
    IFBKeyCode_Numlock               = 92,
    IFBKeyCode_ShiftLeft             = 93,
    IFBKeyCode_ShiftRight            = 94,
    IFBKeyCode_ControlLeft           = 95,
    IFBKeyCode_ControlRight          = 96,
    IFBKeyCode_MenuLeft              = 97,
    IFBKeyCode_MenuRight             = 98,
    IFBKeyCode_VolumeMute            = 99,
    IFBKeyCode_VolumeDown            = 100,
    IFBKeyCode_VolumeUp              = 101,
    IFBKeyCode_Plus                  = 102,
    IFBKeyCode_Comma                 = 103,
    IFBKeyCode_Minus                 = 104,
    IFBKeyCode_Period                = 105,
    IFBKeyCode_SlashForward_Question = 106,
    IFBKeyCode_Tilde                 = 107,
    IFBKeyCode_BracketOpen           = 108,
    IFBKeyCode_SlashBack_Pipe        = 109,
    IFBKeyCode_BracketClose          = 110,
    IFBKeyCode_Quote                 = 111,
    IFBKeyCode_Count                 = 112
};


#define IFB_KEYCODE_ARRAY_SIZE  IFBKeyCode_Count / 8

struct IFBKeyboard {
    IFBByte keycodes[IFB_KEYCODE_ARRAY_SIZE];
};

struct IFBKeyCodeComposite {
    IFBU8 group_index;
    IFBU8 bit_index;
};

inline const IFBKeyCodeComposite 
ifb_input::keyboard_key_composite(
    const IFBKeyCode key_code) {

    IFBKeyCodeComposite composite = {0};

    const IFBU32 key_group_size       = 8; 
    const IFBF32 key_code_f32         = (IFBF32)key_code; 
    const IFBF32 key_group_index_f32  = key_code / key_group_size;
    const IFBU32 key_group_index_u32  = (IFBU32)key_group_index_f32;
    const IFBU32 key_bit_index        = key_code - (key_group_index_u32 * key_group_size); 

    composite.bit_index   = key_bit_index;
    composite.group_index = key_group_index_u32;

    return(composite);
}

inline IFBVoid
ifb_input::keyboard_key_down(
          IFBKeyboard& keyboard,
    const IFBKeyCode   key_code) {

    const IFBKeyCodeComposite composite = ifb_input::keyboard_key_composite(key_code);

    ifb_macro_bit_set(composite.bit_index, keyboard.keycodes[composite.group_index]);
}

inline IFBVoid
ifb_input::keyboard_key_up(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    const IFBKeyCodeComposite composite = ifb_input::keyboard_key_composite(key_code);

    ifb_macro_bit_clear(composite.bit_index, keyboard.keycodes[composite.group_index]);
}

inline const IFBB8
ifb_input::keyboard_key_is_down(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    const IFBKeyCodeComposite composite = ifb_input::keyboard_key_composite(key_code);

    const IFBB8 key_is_down = ifb_macro_bit_test(composite.bit_index, keyboard.keycodes[composite.group_index]);

    return(key_is_down);
}

inline const IFBB8
ifb_input::keyboard_key_is_up(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    const IFBB8 key_is_up = !ifb_input::keyboard_key_is_down(keyboard,key_code);

    return(key_is_up);
}

namespace ifb_input {

    inline IFBVoid keyboard_key_down_back                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Back);                  }
    inline IFBVoid keyboard_key_down_tab                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Tab);                   }
    inline IFBVoid keyboard_key_down_clear                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Clear);                 }
    inline IFBVoid keyboard_key_down_return                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Return);                }
    inline IFBVoid keyboard_key_down_shift                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Shift);                 }
    inline IFBVoid keyboard_key_down_control                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Control);               }
    inline IFBVoid keyboard_key_down_menu                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Menu);                  }
    inline IFBVoid keyboard_key_down_pause                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Pause);                 }
    inline IFBVoid keyboard_key_down_capital                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Capital);               }
    inline IFBVoid keyboard_key_down_escape                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Escape);                }
    inline IFBVoid keyboard_key_down_space                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Space);                 }
    inline IFBVoid keyboard_key_down_prior                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Prior);                 }
    inline IFBVoid keyboard_key_down_next                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Next);                  }
    inline IFBVoid keyboard_key_down_end                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_End);                   }
    inline IFBVoid keyboard_key_down_home                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Home);                  }
    inline IFBVoid keyboard_key_down_left                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Left);                  }
    inline IFBVoid keyboard_key_down_up                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Up);                    }
    inline IFBVoid keyboard_key_down_right                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Right);                 }
    inline IFBVoid keyboard_key_down_down                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Down);                  }
    inline IFBVoid keyboard_key_down_select                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Select);                }
    inline IFBVoid keyboard_key_down_print                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Print);                 }
    inline IFBVoid keyboard_key_down_snapshot                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Snapshot);              }
    inline IFBVoid keyboard_key_down_insert                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Insert);                }
    inline IFBVoid keyboard_key_down_delete                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Delete);                }
    inline IFBVoid keyboard_key_down_help                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Help);                  }
    inline IFBVoid keyboard_key_down_0                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_0);                     }
    inline IFBVoid keyboard_key_down_1                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_1);                     }
    inline IFBVoid keyboard_key_down_2                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_2);                     }
    inline IFBVoid keyboard_key_down_3                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_3);                     }
    inline IFBVoid keyboard_key_down_4                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_4);                     }
    inline IFBVoid keyboard_key_down_5                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_5);                     }
    inline IFBVoid keyboard_key_down_6                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_6);                     }
    inline IFBVoid keyboard_key_down_7                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_7);                     }
    inline IFBVoid keyboard_key_down_8                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_8);                     }
    inline IFBVoid keyboard_key_down_9                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_9);                     }
    inline IFBVoid keyboard_key_down_a                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_A);                     }
    inline IFBVoid keyboard_key_down_b                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_B);                     }
    inline IFBVoid keyboard_key_down_c                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_C);                     }
    inline IFBVoid keyboard_key_down_d                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_D);                     }
    inline IFBVoid keyboard_key_down_e                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_E);                     }
    inline IFBVoid keyboard_key_down_f                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F);                     }
    inline IFBVoid keyboard_key_down_g                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_G);                     }
    inline IFBVoid keyboard_key_down_h                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_H);                     }
    inline IFBVoid keyboard_key_down_i                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_I);                     }
    inline IFBVoid keyboard_key_down_j                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_J);                     }
    inline IFBVoid keyboard_key_down_k                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_K);                     }
    inline IFBVoid keyboard_key_down_l                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_L);                     }
    inline IFBVoid keyboard_key_down_m                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_M);                     }
    inline IFBVoid keyboard_key_down_n                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_N);                     }
    inline IFBVoid keyboard_key_down_o                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_O);                     }
    inline IFBVoid keyboard_key_down_p                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_P);                     }
    inline IFBVoid keyboard_key_down_q                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Q);                     }
    inline IFBVoid keyboard_key_down_r                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_R);                     }
    inline IFBVoid keyboard_key_down_s                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_S);                     }
    inline IFBVoid keyboard_key_down_t                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_T);                     }
    inline IFBVoid keyboard_key_down_u                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_U);                     }
    inline IFBVoid keyboard_key_down_v                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_V);                     }
    inline IFBVoid keyboard_key_down_w                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_W);                     }
    inline IFBVoid keyboard_key_down_x                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_X);                     }
    inline IFBVoid keyboard_key_down_y                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Y);                     }
    inline IFBVoid keyboard_key_down_z                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Z);                     }
    inline IFBVoid keyboard_key_down_winleft                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_WinLeft);               }
    inline IFBVoid keyboard_key_down_winright                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_WinRight);              }
    inline IFBVoid keyboard_key_down_apps                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Apps);                  }
    inline IFBVoid keyboard_key_down_numpad0                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad0);               }
    inline IFBVoid keyboard_key_down_numpad1                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad1);               }
    inline IFBVoid keyboard_key_down_numpad2                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad2);               }
    inline IFBVoid keyboard_key_down_numpad3                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad3);               }
    inline IFBVoid keyboard_key_down_numpad4                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad4);               }
    inline IFBVoid keyboard_key_down_numpad5                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad5);               }
    inline IFBVoid keyboard_key_down_numpad6                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad6);               }
    inline IFBVoid keyboard_key_down_numpad7                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad7);               }
    inline IFBVoid keyboard_key_down_numpad8                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad8);               }
    inline IFBVoid keyboard_key_down_numpad9                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numpad9);               }
    inline IFBVoid keyboard_key_down_multiply                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Multiply);              }
    inline IFBVoid keyboard_key_down_add                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Add);                   }
    inline IFBVoid keyboard_key_down_separator                    (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Separator);             }
    inline IFBVoid keyboard_key_down_subtract                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Subtract);              }
    inline IFBVoid keyboard_key_down_decimal                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Decimal);               }
    inline IFBVoid keyboard_key_down_divide                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Divide);                }
    inline IFBVoid keyboard_key_down_f1                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F1);                    }
    inline IFBVoid keyboard_key_down_f2                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F2);                    }
    inline IFBVoid keyboard_key_down_f3                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F3);                    }
    inline IFBVoid keyboard_key_down_f4                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F4);                    }
    inline IFBVoid keyboard_key_down_f5                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F5);                    }
    inline IFBVoid keyboard_key_down_f6                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F6);                    }
    inline IFBVoid keyboard_key_down_f7                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F7);                    }
    inline IFBVoid keyboard_key_down_f8                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F8);                    }
    inline IFBVoid keyboard_key_down_f9                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F9);                    }
    inline IFBVoid keyboard_key_down_f10                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F10);                   }
    inline IFBVoid keyboard_key_down_f11                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F11);                   }
    inline IFBVoid keyboard_key_down_f12                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_F12);                   }
    inline IFBVoid keyboard_key_down_numlock                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Numlock);               }
    inline IFBVoid keyboard_key_down_shiftleft                    (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_ShiftLeft);             }
    inline IFBVoid keyboard_key_down_shiftright                   (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_ShiftRight);            }
    inline IFBVoid keyboard_key_down_controlleft                  (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_ControlLeft);           }
    inline IFBVoid keyboard_key_down_controlright                 (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_ControlRight);          }
    inline IFBVoid keyboard_key_down_menuleft                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_MenuLeft);              }
    inline IFBVoid keyboard_key_down_menuright                    (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_MenuRight);             }
    inline IFBVoid keyboard_key_down_volumemute                   (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_VolumeMute);            }
    inline IFBVoid keyboard_key_down_volumedown                   (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_VolumeDown);            }
    inline IFBVoid keyboard_key_down_volumeup                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_VolumeUp);              }
    inline IFBVoid keyboard_key_down_plus                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Plus);                  }
    inline IFBVoid keyboard_key_down_comma                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Comma);                 }
    inline IFBVoid keyboard_key_down_minus                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Minus);                 }
    inline IFBVoid keyboard_key_down_period                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Period);                }
    inline IFBVoid keyboard_key_down_slashforward_question        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_SlashForward_Question); }
    inline IFBVoid keyboard_key_down_tilde                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Tilde);                 }
    inline IFBVoid keyboard_key_down_bracketopen                  (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_BracketOpen);           }
    inline IFBVoid keyboard_key_down_slashback_pipe               (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_SlashBack_Pipe);        }
    inline IFBVoid keyboard_key_down_bracketclose                 (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_BracketClose);          }
    inline IFBVoid keyboard_key_down_quote                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Quote);                 }
    inline IFBVoid keyboard_key_down_count                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_down(keyboard,IFBKeyCode_Count);                 }

    inline IFBVoid keyboard_key_up_back                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Back);                  }
    inline IFBVoid keyboard_key_up_tab                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Tab);                   }
    inline IFBVoid keyboard_key_up_clear                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Clear);                 }
    inline IFBVoid keyboard_key_up_return                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Return);                }
    inline IFBVoid keyboard_key_up_shift                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Shift);                 }
    inline IFBVoid keyboard_key_up_control                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Control);               }
    inline IFBVoid keyboard_key_up_menu                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Menu);                  }
    inline IFBVoid keyboard_key_up_pause                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Pause);                 }
    inline IFBVoid keyboard_key_up_capital                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Capital);               }
    inline IFBVoid keyboard_key_up_escape                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Escape);                }
    inline IFBVoid keyboard_key_up_space                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Space);                 }
    inline IFBVoid keyboard_key_up_prior                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Prior);                 }
    inline IFBVoid keyboard_key_up_next                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Next);                  }
    inline IFBVoid keyboard_key_up_end                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_End);                   }
    inline IFBVoid keyboard_key_up_home                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Home);                  }
    inline IFBVoid keyboard_key_up_left                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Left);                  }
    inline IFBVoid keyboard_key_up_up                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Up);                    }
    inline IFBVoid keyboard_key_up_right                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Right);                 }
    inline IFBVoid keyboard_key_up_down                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Down);                  }
    inline IFBVoid keyboard_key_up_select                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Select);                }
    inline IFBVoid keyboard_key_up_print                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Print);                 }
    inline IFBVoid keyboard_key_up_snapshot                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Snapshot);              }
    inline IFBVoid keyboard_key_up_insert                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Insert);                }
    inline IFBVoid keyboard_key_up_delete                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Delete);                }
    inline IFBVoid keyboard_key_up_help                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Help);                  }
    inline IFBVoid keyboard_key_up_0                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_0);                     }
    inline IFBVoid keyboard_key_up_1                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_1);                     }
    inline IFBVoid keyboard_key_up_2                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_2);                     }
    inline IFBVoid keyboard_key_up_3                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_3);                     }
    inline IFBVoid keyboard_key_up_4                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_4);                     }
    inline IFBVoid keyboard_key_up_5                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_5);                     }
    inline IFBVoid keyboard_key_up_6                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_6);                     }
    inline IFBVoid keyboard_key_up_7                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_7);                     }
    inline IFBVoid keyboard_key_up_8                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_8);                     }
    inline IFBVoid keyboard_key_up_9                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_9);                     }
    inline IFBVoid keyboard_key_up_a                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_A);                     }
    inline IFBVoid keyboard_key_up_b                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_B);                     }
    inline IFBVoid keyboard_key_up_c                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_C);                     }
    inline IFBVoid keyboard_key_up_d                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_D);                     }
    inline IFBVoid keyboard_key_up_e                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_E);                     }
    inline IFBVoid keyboard_key_up_f                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F);                     }
    inline IFBVoid keyboard_key_up_g                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_G);                     }
    inline IFBVoid keyboard_key_up_h                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_H);                     }
    inline IFBVoid keyboard_key_up_i                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_I);                     }
    inline IFBVoid keyboard_key_up_j                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_J);                     }
    inline IFBVoid keyboard_key_up_k                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_K);                     }
    inline IFBVoid keyboard_key_up_l                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_L);                     }
    inline IFBVoid keyboard_key_up_m                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_M);                     }
    inline IFBVoid keyboard_key_up_n                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_N);                     }
    inline IFBVoid keyboard_key_up_o                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_O);                     }
    inline IFBVoid keyboard_key_up_p                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_P);                     }
    inline IFBVoid keyboard_key_up_q                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Q);                     }
    inline IFBVoid keyboard_key_up_r                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_R);                     }
    inline IFBVoid keyboard_key_up_s                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_S);                     }
    inline IFBVoid keyboard_key_up_t                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_T);                     }
    inline IFBVoid keyboard_key_up_u                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_U);                     }
    inline IFBVoid keyboard_key_up_v                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_V);                     }
    inline IFBVoid keyboard_key_up_w                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_W);                     }
    inline IFBVoid keyboard_key_up_x                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_X);                     }
    inline IFBVoid keyboard_key_up_y                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Y);                     }
    inline IFBVoid keyboard_key_up_z                              (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Z);                     }
    inline IFBVoid keyboard_key_up_winleft                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_WinLeft);               }
    inline IFBVoid keyboard_key_up_winright                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_WinRight);              }
    inline IFBVoid keyboard_key_up_apps                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Apps);                  }
    inline IFBVoid keyboard_key_up_numpad0                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad0);               }
    inline IFBVoid keyboard_key_up_numpad1                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad1);               }
    inline IFBVoid keyboard_key_up_numpad2                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad2);               }
    inline IFBVoid keyboard_key_up_numpad3                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad3);               }
    inline IFBVoid keyboard_key_up_numpad4                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad4);               }
    inline IFBVoid keyboard_key_up_numpad5                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad5);               }
    inline IFBVoid keyboard_key_up_numpad6                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad6);               }
    inline IFBVoid keyboard_key_up_numpad7                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad7);               }
    inline IFBVoid keyboard_key_up_numpad8                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad8);               }
    inline IFBVoid keyboard_key_up_numpad9                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numpad9);               }
    inline IFBVoid keyboard_key_up_multiply                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Multiply);              }
    inline IFBVoid keyboard_key_up_add                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Add);                   }
    inline IFBVoid keyboard_key_up_separator                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Separator);             }
    inline IFBVoid keyboard_key_up_subtract                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Subtract);              }
    inline IFBVoid keyboard_key_up_decimal                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Decimal);               }
    inline IFBVoid keyboard_key_up_divide                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Divide);                }
    inline IFBVoid keyboard_key_up_f1                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F1);                    }
    inline IFBVoid keyboard_key_up_f2                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F2);                    }
    inline IFBVoid keyboard_key_up_f3                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F3);                    }
    inline IFBVoid keyboard_key_up_f4                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F4);                    }
    inline IFBVoid keyboard_key_up_f5                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F5);                    }
    inline IFBVoid keyboard_key_up_f6                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F6);                    }
    inline IFBVoid keyboard_key_up_f7                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F7);                    }
    inline IFBVoid keyboard_key_up_f8                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F8);                    }
    inline IFBVoid keyboard_key_up_f9                             (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F9);                    }
    inline IFBVoid keyboard_key_up_f10                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F10);                   }
    inline IFBVoid keyboard_key_up_f11                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F11);                   }
    inline IFBVoid keyboard_key_up_f12                            (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_F12);                   }
    inline IFBVoid keyboard_key_up_numlock                        (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Numlock);               }
    inline IFBVoid keyboard_key_up_shiftleft                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_ShiftLeft);             }
    inline IFBVoid keyboard_key_up_shiftright                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_ShiftRight);            }
    inline IFBVoid keyboard_key_up_controlleft                    (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_ControlLeft);           }
    inline IFBVoid keyboard_key_up_controlright                   (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_ControlRight);          }
    inline IFBVoid keyboard_key_up_menuleft                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_MenuLeft);              }
    inline IFBVoid keyboard_key_up_menuright                      (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_MenuRight);             }
    inline IFBVoid keyboard_key_up_volumemute                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_VolumeMute);            }
    inline IFBVoid keyboard_key_up_volumedown                     (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_VolumeDown);            }
    inline IFBVoid keyboard_key_up_volumeup                       (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_VolumeUp);              }
    inline IFBVoid keyboard_key_up_plus                           (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Plus);                  }
    inline IFBVoid keyboard_key_up_comma                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Comma);                 }
    inline IFBVoid keyboard_key_up_minus                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Minus);                 }
    inline IFBVoid keyboard_key_up_period                         (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Period);                }
    inline IFBVoid keyboard_key_up_slashforward_question          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_SlashForward_Question); }
    inline IFBVoid keyboard_key_up_tilde                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Tilde);                 }
    inline IFBVoid keyboard_key_up_bracketopen                    (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_BracketOpen);           }
    inline IFBVoid keyboard_key_up_slashback_pipe                 (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_SlashBack_Pipe);        }
    inline IFBVoid keyboard_key_up_bracketclose                   (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_BracketClose);          }
    inline IFBVoid keyboard_key_up_quote                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Quote);                 }
    inline IFBVoid keyboard_key_up_count                          (IFBKeyboard& keyboard) { ifb_input::keyboard_key_up(keyboard,IFBKeyCode_Count);                 }

    inline const IFBB8 keyboard_key_is_up_back                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Back));                  }
    inline const IFBB8 keyboard_key_is_up_tab                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Tab));                   }
    inline const IFBB8 keyboard_key_is_up_clear                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Clear));                 }
    inline const IFBB8 keyboard_key_is_up_return                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Return));                }
    inline const IFBB8 keyboard_key_is_up_shift                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Shift));                 }
    inline const IFBB8 keyboard_key_is_up_control                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Control));               }
    inline const IFBB8 keyboard_key_is_up_menu                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Menu));                  }
    inline const IFBB8 keyboard_key_is_up_pause                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Pause));                 }
    inline const IFBB8 keyboard_key_is_up_capital                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Capital));               }
    inline const IFBB8 keyboard_key_is_up_escape                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Escape));                }
    inline const IFBB8 keyboard_key_is_up_space                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Space));                 }
    inline const IFBB8 keyboard_key_is_up_prior                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Prior));                 }
    inline const IFBB8 keyboard_key_is_up_next                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Next));                  }
    inline const IFBB8 keyboard_key_is_up_end                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_End));                   }
    inline const IFBB8 keyboard_key_is_up_home                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Home));                  }
    inline const IFBB8 keyboard_key_is_up_left                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Left));                  }
    inline const IFBB8 keyboard_key_is_up_up                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Up));                    }
    inline const IFBB8 keyboard_key_is_up_right                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Right));                 }
    inline const IFBB8 keyboard_key_is_up_down                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Down));                  }
    inline const IFBB8 keyboard_key_is_up_select                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Select));                }
    inline const IFBB8 keyboard_key_is_up_print                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Print));                 }
    inline const IFBB8 keyboard_key_is_up_snapshot                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Snapshot));              }
    inline const IFBB8 keyboard_key_is_up_insert                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Insert));                }
    inline const IFBB8 keyboard_key_is_up_delete                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Delete));                }
    inline const IFBB8 keyboard_key_is_up_help                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Help));                  }
    inline const IFBB8 keyboard_key_is_up_0                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_0));                     }
    inline const IFBB8 keyboard_key_is_up_1                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_1));                     }
    inline const IFBB8 keyboard_key_is_up_2                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_2));                     }
    inline const IFBB8 keyboard_key_is_up_3                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_3));                     }
    inline const IFBB8 keyboard_key_is_up_4                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_4));                     }
    inline const IFBB8 keyboard_key_is_up_5                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_5));                     }
    inline const IFBB8 keyboard_key_is_up_6                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_6));                     }
    inline const IFBB8 keyboard_key_is_up_7                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_7));                     }
    inline const IFBB8 keyboard_key_is_up_8                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_8));                     }
    inline const IFBB8 keyboard_key_is_up_9                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_9));                     }
    inline const IFBB8 keyboard_key_is_up_a                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_A));                     }
    inline const IFBB8 keyboard_key_is_up_b                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_B));                     }
    inline const IFBB8 keyboard_key_is_up_c                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_C));                     }
    inline const IFBB8 keyboard_key_is_up_d                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_D));                     }
    inline const IFBB8 keyboard_key_is_up_e                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_E));                     }
    inline const IFBB8 keyboard_key_is_up_f                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F));                     }
    inline const IFBB8 keyboard_key_is_up_g                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_G));                     }
    inline const IFBB8 keyboard_key_is_up_h                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_H));                     }
    inline const IFBB8 keyboard_key_is_up_i                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_I));                     }
    inline const IFBB8 keyboard_key_is_up_j                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_J));                     }
    inline const IFBB8 keyboard_key_is_up_k                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_K));                     }
    inline const IFBB8 keyboard_key_is_up_l                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_L));                     }
    inline const IFBB8 keyboard_key_is_up_m                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_M));                     }
    inline const IFBB8 keyboard_key_is_up_n                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_N));                     }
    inline const IFBB8 keyboard_key_is_up_o                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_O));                     }
    inline const IFBB8 keyboard_key_is_up_p                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_P));                     }
    inline const IFBB8 keyboard_key_is_up_q                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Q));                     }
    inline const IFBB8 keyboard_key_is_up_r                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_R));                     }
    inline const IFBB8 keyboard_key_is_up_s                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_S));                     }
    inline const IFBB8 keyboard_key_is_up_t                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_T));                     }
    inline const IFBB8 keyboard_key_is_up_u                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_U));                     }
    inline const IFBB8 keyboard_key_is_up_v                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_V));                     }
    inline const IFBB8 keyboard_key_is_up_w                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_W));                     }
    inline const IFBB8 keyboard_key_is_up_x                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_X));                     }
    inline const IFBB8 keyboard_key_is_up_y                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Y));                     }
    inline const IFBB8 keyboard_key_is_up_z                       (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Z));                     }
    inline const IFBB8 keyboard_key_is_up_winleft                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_WinLeft));               }
    inline const IFBB8 keyboard_key_is_up_winright                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_WinRight));              }
    inline const IFBB8 keyboard_key_is_up_apps                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Apps));                  }
    inline const IFBB8 keyboard_key_is_up_numpad0                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad0));               }
    inline const IFBB8 keyboard_key_is_up_numpad1                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad1));               }
    inline const IFBB8 keyboard_key_is_up_numpad2                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad2));               }
    inline const IFBB8 keyboard_key_is_up_numpad3                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad3));               }
    inline const IFBB8 keyboard_key_is_up_numpad4                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad4));               }
    inline const IFBB8 keyboard_key_is_up_numpad5                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad5));               }
    inline const IFBB8 keyboard_key_is_up_numpad6                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad6));               }
    inline const IFBB8 keyboard_key_is_up_numpad7                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad7));               }
    inline const IFBB8 keyboard_key_is_up_numpad8                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad8));               }
    inline const IFBB8 keyboard_key_is_up_numpad9                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numpad9));               }
    inline const IFBB8 keyboard_key_is_up_multiply                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Multiply));              }
    inline const IFBB8 keyboard_key_is_up_add                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Add));                   }
    inline const IFBB8 keyboard_key_is_up_separator               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Separator));             }
    inline const IFBB8 keyboard_key_is_up_subtract                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Subtract));              }
    inline const IFBB8 keyboard_key_is_up_decimal                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Decimal));               }
    inline const IFBB8 keyboard_key_is_up_divide                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Divide));                }
    inline const IFBB8 keyboard_key_is_up_f1                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F1));                    }
    inline const IFBB8 keyboard_key_is_up_f2                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F2));                    }
    inline const IFBB8 keyboard_key_is_up_f3                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F3));                    }
    inline const IFBB8 keyboard_key_is_up_f4                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F4));                    }
    inline const IFBB8 keyboard_key_is_up_f5                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F5));                    }
    inline const IFBB8 keyboard_key_is_up_f6                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F6));                    }
    inline const IFBB8 keyboard_key_is_up_f7                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F7));                    }
    inline const IFBB8 keyboard_key_is_up_f8                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F8));                    }
    inline const IFBB8 keyboard_key_is_up_f9                      (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F9));                    }
    inline const IFBB8 keyboard_key_is_up_f10                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F10));                   }
    inline const IFBB8 keyboard_key_is_up_f11                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F11));                   }
    inline const IFBB8 keyboard_key_is_up_f12                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_F12));                   }
    inline const IFBB8 keyboard_key_is_up_numlock                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Numlock));               }
    inline const IFBB8 keyboard_key_is_up_shiftleft               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_ShiftLeft));             }
    inline const IFBB8 keyboard_key_is_up_shiftright              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_ShiftRight));            }
    inline const IFBB8 keyboard_key_is_up_controlleft             (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_ControlLeft));           }
    inline const IFBB8 keyboard_key_is_up_controlright            (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_ControlRight));          }
    inline const IFBB8 keyboard_key_is_up_menuleft                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_MenuLeft));              }
    inline const IFBB8 keyboard_key_is_up_menuright               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_MenuRight));             }
    inline const IFBB8 keyboard_key_is_up_volumemute              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_VolumeMute));            }
    inline const IFBB8 keyboard_key_is_up_volumedown              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_VolumeDown));            }
    inline const IFBB8 keyboard_key_is_up_volumeup                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_VolumeUp));              }
    inline const IFBB8 keyboard_key_is_up_plus                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Plus));                  }
    inline const IFBB8 keyboard_key_is_up_comma                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Comma));                 }
    inline const IFBB8 keyboard_key_is_up_minus                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Minus));                 }
    inline const IFBB8 keyboard_key_is_up_period                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Period));                }
    inline const IFBB8 keyboard_key_is_up_slashforward_question   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_SlashForward_Question)); }
    inline const IFBB8 keyboard_key_is_up_tilde                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Tilde));                 }
    inline const IFBB8 keyboard_key_is_up_bracketopen             (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_BracketOpen));           }
    inline const IFBB8 keyboard_key_is_up_slashback_pipe          (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_SlashBack_Pipe));        }
    inline const IFBB8 keyboard_key_is_up_bracketclose            (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_BracketClose));          }
    inline const IFBB8 keyboard_key_is_up_quote                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Quote));                 }
    inline const IFBB8 keyboard_key_is_up_count                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_up(keyboard,IFBKeyCode_Count));                 }

    inline const IFBB8 keyboard_key_is_down_back                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Back));                  }
    inline const IFBB8 keyboard_key_is_down_tab                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Tab));                   }
    inline const IFBB8 keyboard_key_is_down_clear                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Clear));                 }
    inline const IFBB8 keyboard_key_is_down_return                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Return));                }
    inline const IFBB8 keyboard_key_is_down_shift                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Shift));                 }
    inline const IFBB8 keyboard_key_is_down_control               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Control));               }
    inline const IFBB8 keyboard_key_is_down_menu                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Menu));                  }
    inline const IFBB8 keyboard_key_is_down_pause                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Pause));                 }
    inline const IFBB8 keyboard_key_is_down_capital               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Capital));               }
    inline const IFBB8 keyboard_key_is_down_escape                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Escape));                }
    inline const IFBB8 keyboard_key_is_down_space                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Space));                 }
    inline const IFBB8 keyboard_key_is_down_prior                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Prior));                 }
    inline const IFBB8 keyboard_key_is_down_next                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Next));                  }
    inline const IFBB8 keyboard_key_is_down_end                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_End));                   }
    inline const IFBB8 keyboard_key_is_down_home                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Home));                  }
    inline const IFBB8 keyboard_key_is_down_left                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Left));                  }
    inline const IFBB8 keyboard_key_is_down_up                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Up));                    }
    inline const IFBB8 keyboard_key_is_down_right                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Right));                 }
    inline const IFBB8 keyboard_key_is_down_down                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Down));                  }
    inline const IFBB8 keyboard_key_is_down_select                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Select));                }
    inline const IFBB8 keyboard_key_is_down_print                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Print));                 }
    inline const IFBB8 keyboard_key_is_down_snapshot              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Snapshot));              }
    inline const IFBB8 keyboard_key_is_down_insert                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Insert));                }
    inline const IFBB8 keyboard_key_is_down_delete                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Delete));                }
    inline const IFBB8 keyboard_key_is_down_help                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Help));                  }
    inline const IFBB8 keyboard_key_is_down_0                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_0));                     }
    inline const IFBB8 keyboard_key_is_down_1                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_1));                     }
    inline const IFBB8 keyboard_key_is_down_2                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_2));                     }
    inline const IFBB8 keyboard_key_is_down_3                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_3));                     }
    inline const IFBB8 keyboard_key_is_down_4                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_4));                     }
    inline const IFBB8 keyboard_key_is_down_5                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_5));                     }
    inline const IFBB8 keyboard_key_is_down_6                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_6));                     }
    inline const IFBB8 keyboard_key_is_down_7                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_7));                     }
    inline const IFBB8 keyboard_key_is_down_8                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_8));                     }
    inline const IFBB8 keyboard_key_is_down_9                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_9));                     }
    inline const IFBB8 keyboard_key_is_down_a                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_A));                     }
    inline const IFBB8 keyboard_key_is_down_b                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_B));                     }
    inline const IFBB8 keyboard_key_is_down_c                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_C));                     }
    inline const IFBB8 keyboard_key_is_down_d                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_D));                     }
    inline const IFBB8 keyboard_key_is_down_e                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_E));                     }
    inline const IFBB8 keyboard_key_is_down_f                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F));                     }
    inline const IFBB8 keyboard_key_is_down_g                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_G));                     }
    inline const IFBB8 keyboard_key_is_down_h                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_H));                     }
    inline const IFBB8 keyboard_key_is_down_i                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_I));                     }
    inline const IFBB8 keyboard_key_is_down_j                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_J));                     }
    inline const IFBB8 keyboard_key_is_down_k                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_K));                     }
    inline const IFBB8 keyboard_key_is_down_l                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_L));                     }
    inline const IFBB8 keyboard_key_is_down_m                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_M));                     }
    inline const IFBB8 keyboard_key_is_down_n                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_N));                     }
    inline const IFBB8 keyboard_key_is_down_o                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_O));                     }
    inline const IFBB8 keyboard_key_is_down_p                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_P));                     }
    inline const IFBB8 keyboard_key_is_down_q                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Q));                     }
    inline const IFBB8 keyboard_key_is_down_r                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_R));                     }
    inline const IFBB8 keyboard_key_is_down_s                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_S));                     }
    inline const IFBB8 keyboard_key_is_down_t                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_T));                     }
    inline const IFBB8 keyboard_key_is_down_u                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_U));                     }
    inline const IFBB8 keyboard_key_is_down_v                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_V));                     }
    inline const IFBB8 keyboard_key_is_down_w                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_W));                     }
    inline const IFBB8 keyboard_key_is_down_x                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_X));                     }
    inline const IFBB8 keyboard_key_is_down_y                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Y));                     }
    inline const IFBB8 keyboard_key_is_down_z                     (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Z));                     }
    inline const IFBB8 keyboard_key_is_down_winleft               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_WinLeft));               }
    inline const IFBB8 keyboard_key_is_down_winright              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_WinRight));              }
    inline const IFBB8 keyboard_key_is_down_apps                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Apps));                  }
    inline const IFBB8 keyboard_key_is_down_numpad0               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad0));               }
    inline const IFBB8 keyboard_key_is_down_numpad1               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad1));               }
    inline const IFBB8 keyboard_key_is_down_numpad2               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad2));               }
    inline const IFBB8 keyboard_key_is_down_numpad3               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad3));               }
    inline const IFBB8 keyboard_key_is_down_numpad4               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad4));               }
    inline const IFBB8 keyboard_key_is_down_numpad5               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad5));               }
    inline const IFBB8 keyboard_key_is_down_numpad6               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad6));               }
    inline const IFBB8 keyboard_key_is_down_numpad7               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad7));               }
    inline const IFBB8 keyboard_key_is_down_numpad8               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad8));               }
    inline const IFBB8 keyboard_key_is_down_numpad9               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numpad9));               }
    inline const IFBB8 keyboard_key_is_down_multiply              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Multiply));              }
    inline const IFBB8 keyboard_key_is_down_add                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Add));                   }
    inline const IFBB8 keyboard_key_is_down_separator             (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Separator));             }
    inline const IFBB8 keyboard_key_is_down_subtract              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Subtract));              }
    inline const IFBB8 keyboard_key_is_down_decimal               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Decimal));               }
    inline const IFBB8 keyboard_key_is_down_divide                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Divide));                }
    inline const IFBB8 keyboard_key_is_down_f1                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F1));                    }
    inline const IFBB8 keyboard_key_is_down_f2                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F2));                    }
    inline const IFBB8 keyboard_key_is_down_f3                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F3));                    }
    inline const IFBB8 keyboard_key_is_down_f4                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F4));                    }
    inline const IFBB8 keyboard_key_is_down_f5                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F5));                    }
    inline const IFBB8 keyboard_key_is_down_f6                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F6));                    }
    inline const IFBB8 keyboard_key_is_down_f7                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F7));                    }
    inline const IFBB8 keyboard_key_is_down_f8                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F8));                    }
    inline const IFBB8 keyboard_key_is_down_f9                    (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F9));                    }
    inline const IFBB8 keyboard_key_is_down_f10                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F10));                   }
    inline const IFBB8 keyboard_key_is_down_f11                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F11));                   }
    inline const IFBB8 keyboard_key_is_down_f12                   (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_F12));                   }
    inline const IFBB8 keyboard_key_is_down_numlock               (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Numlock));               }
    inline const IFBB8 keyboard_key_is_down_shiftleft             (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_ShiftLeft));             }
    inline const IFBB8 keyboard_key_is_down_shiftright            (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_ShiftRight));            }
    inline const IFBB8 keyboard_key_is_down_controlleft           (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_ControlLeft));           }
    inline const IFBB8 keyboard_key_is_down_controlright          (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_ControlRight));          }
    inline const IFBB8 keyboard_key_is_down_menuleft              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_MenuLeft));              }
    inline const IFBB8 keyboard_key_is_down_menuright             (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_MenuRight));             }
    inline const IFBB8 keyboard_key_is_down_volumemute            (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_VolumeMute));            }
    inline const IFBB8 keyboard_key_is_down_volumedown            (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_VolumeDown));            }
    inline const IFBB8 keyboard_key_is_down_volumeup              (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_VolumeUp));              }
    inline const IFBB8 keyboard_key_is_down_plus                  (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Plus));                  }
    inline const IFBB8 keyboard_key_is_down_comma                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Comma));                 }
    inline const IFBB8 keyboard_key_is_down_minus                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Minus));                 }
    inline const IFBB8 keyboard_key_is_down_period                (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Period));                }
    inline const IFBB8 keyboard_key_is_down_slashforward_question (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_SlashForward_Question)); }
    inline const IFBB8 keyboard_key_is_down_tilde                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Tilde));                 }
    inline const IFBB8 keyboard_key_is_down_bracketopen           (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_BracketOpen));           }
    inline const IFBB8 keyboard_key_is_down_slashback_pipe        (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_SlashBack_Pipe));        }
    inline const IFBB8 keyboard_key_is_down_bracketclose          (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_BracketClose));          }
    inline const IFBB8 keyboard_key_is_down_quote                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Quote));                 }
    inline const IFBB8 keyboard_key_is_down_count                 (IFBKeyboard& keyboard) { return(ifb_input::keyboard_key_is_down(keyboard,IFBKeyCode_Count));                 }
};

/**********************************************************************************/
/* MOUSE                                                                          */
/**********************************************************************************/

struct IFBMousePosition {
    IFBS32 x;
    IFBS32 y;
};

struct IFBMouse {
    struct {
        IFBMousePosition current;
        IFBMousePosition delta;
    } position;
    IFBS32 wheel;
    IFBB8  button_left;
    IFBB8  button_right;
};

/**********************************************************************************/
/* GAMEPAD                                                                        */
/**********************************************************************************/

enum IFBGamepadButtonCode_ {
    IFBGamepadButtonCode_DpadUp      = 0x00, 
    IFBGamepadButtonCode_DpadDown    = 0x01, 
    IFBGamepadButtonCode_DpadLeft    = 0x02, 
    IFBGamepadButtonCode_DpadRight   = 0x03, 
    IFBGamepadButtonCode_Start       = 0x04, 
    IFBGamepadButtonCode_Select      = 0x05, 
    IFBGamepadButtonCode_StickLeft   = 0x06, 
    IFBGamepadButtonCode_StickRight  = 0x07, 
    IFBGamepadButtonCode_BumberLeft  = 0x08, 
    IFBGamepadButtonCode_BumberRight = 0x09, 
    IFBGamepadButtonCode_BpadA       = 0x0C, 
    IFBGamepadButtonCode_BpadB       = 0x0D, 
    IFBGamepadButtonCode_BpadX       = 0x0E, 
    IFBGamepadButtonCode_BpadY       = 0x0F, 
};

struct IFBGamepad {
    IFBGamepadButtonCode button_codes;
    struct {
        IFBF32 left;
        IFBF32 right;
    } triggers;
};

inline IFBVoid
ifb_input::gamepad_button_down(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {

    ifb_macro_bit_set(
        button_code,
        gamepad.button_codes);                
}

inline IFBVoid
ifb_input::gamepad_button_up(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {
    
    ifb_macro_bit_clear(            
        button_code,
        gamepad.button_codes);                
}

inline const IFBB8
ifb_input::gamepad_button_is_down(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {

    const IFBB8 key_is_down = ifb_macro_bit_test(
        button_code,
        gamepad.button_codes);                        

    return(key_is_down);
}

/**********************************************************************************/
/* INPUT                                                                          */
/**********************************************************************************/

struct IFBInput {
    IFBKeyboard keyboard;
    IFBMouse    mouse;
    IFBGamepad  gamepad;
};

inline IFBVoid
ifb_input::clear(
    IFBInput& input_ref) {
    
    input_ref = {0};
}

#endif //IFB_USER_INPUT_HPP