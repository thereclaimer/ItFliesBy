#ifndef IFB_USER_INPUT_HPP
#define IFB_USER_INPUT_HPP

#include "ifb-types.hpp"
#include "ifb-scopes.hpp"
#include "ifb-macros.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef ifb_u16 IFBKeyCode;
typedef ifb_u16 IFBGamepadButtonCode; 

struct IFBKeyCodeComposite;
struct IFBKeyboard;
struct IFBMousePosition;
struct IFBMouse;
struct IFBGamepad;
struct IFBInput;

namespace ifb_input {

          ifb_void keyboard_key_down      (IFBKeyboard& keyboard, IFBKeyCode key_code);
          ifb_void keyboard_key_up        (IFBKeyboard& keyboard, IFBKeyCode key_code);
    const ifb_b8   keyboard_key_is_down   (IFBKeyboard& keyboard, IFBKeyCode key_code);
    const ifb_b8   keyboard_key_is_up     (IFBKeyboard& keyboard, IFBKeyCode key_code);

          ifb_void gamepad_button_down    (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);
          ifb_void gamepad_button_up      (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);
    const ifb_b8   gamepad_button_is_down (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);

          ifb_void clear                  (IFBInput& input_ref);
};

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum IFBKeyCode_ {
    IFBKeyCode_Back                  = (1 << 0),
    IFBKeyCode_Tab                   = (1 << 1),
    IFBKeyCode_Clear                 = (1 << 2),
    IFBKeyCode_Return                = (1 << 3),
    IFBKeyCode_Shift                 = (1 << 4),
    IFBKeyCode_Control               = (1 << 5),
    IFBKeyCode_Menu                  = (1 << 6),
    IFBKeyCode_Pause                 = (1 << 7),
    IFBKeyCode_Capital               = (1 << 8),
    IFBKeyCode_Escape                = (1 << 9),
    IFBKeyCode_Space                 = (1 << 10),
    IFBKeyCode_Prior                 = (1 << 11),
    IFBKeyCode_Next                  = (1 << 12),
    IFBKeyCode_End                   = (1 << 13),
    IFBKeyCode_Home                  = (1 << 14),
    IFBKeyCode_Left                  = (1 << 15),
    IFBKeyCode_Up                    = (1 << 16), 
    IFBKeyCode_Right                 = (1 << 17), 
    IFBKeyCode_Down                  = (1 << 18), 
    IFBKeyCode_Select                = (1 << 19), 
    IFBKeyCode_Print                 = (1 << 20), 
    IFBKeyCode_Snapshot              = (1 << 21),  
    IFBKeyCode_Insert                = (1 << 22),  
    IFBKeyCode_Delete                = (1 << 23), 
    IFBKeyCode_Help                  = (1 << 24),
    IFBKeyCode_0                     = (1 << 25),
    IFBKeyCode_1                     = (1 << 26),
    IFBKeyCode_2                     = (1 << 27),
    IFBKeyCode_3                     = (1 << 28),
    IFBKeyCode_4                     = (1 << 29),
    IFBKeyCode_5                     = (1 << 30),
    IFBKeyCode_6                     = (1 << 31),
    IFBKeyCode_7                     = (1 << 32),
    IFBKeyCode_8                     = (1 << 33),
    IFBKeyCode_9                     = (1 << 34),
    IFBKeyCode_A                     = (1 << 35),
    IFBKeyCode_B                     = (1 << 36),
    IFBKeyCode_C                     = (1 << 37),
    IFBKeyCode_D                     = (1 << 38),
    IFBKeyCode_E                     = (1 << 39),
    IFBKeyCode_F                     = (1 << 40),
    IFBKeyCode_G                     = (1 << 41),
    IFBKeyCode_H                     = (1 << 42),
    IFBKeyCode_I                     = (1 << 43),
    IFBKeyCode_J                     = (1 << 44),
    IFBKeyCode_K                     = (1 << 45),
    IFBKeyCode_L                     = (1 << 46),
    IFBKeyCode_M                     = (1 << 47),
    IFBKeyCode_N                     = (1 << 48),
    IFBKeyCode_O                     = (1 << 49),
    IFBKeyCode_P                     = (1 << 50),
    IFBKeyCode_Q                     = (1 << 51),
    IFBKeyCode_R                     = (1 << 52),
    IFBKeyCode_S                     = (1 << 53),
    IFBKeyCode_T                     = (1 << 54),
    IFBKeyCode_U                     = (1 << 55),
    IFBKeyCode_V                     = (1 << 56),
    IFBKeyCode_W                     = (1 << 57),
    IFBKeyCode_X                     = (1 << 58),
    IFBKeyCode_Y                     = (1 << 59),
    IFBKeyCode_Z                     = (1 << 60),
    IFBKeyCode_WinLeft               = (1 << 61),
    IFBKeyCode_WinRight              = (1 << 62),
    IFBKeyCode_Apps                  = (1 << 63),
    IFBKeyCode_Numpad0               = (1 << 64),
    IFBKeyCode_Numpad1               = (1 << 65),
    IFBKeyCode_Numpad2               = (1 << 66),
    IFBKeyCode_Numpad3               = (1 << 67),
    IFBKeyCode_Numpad4               = (1 << 68),
    IFBKeyCode_Numpad5               = (1 << 69),
    IFBKeyCode_Numpad6               = (1 << 70),
    IFBKeyCode_Numpad7               = (1 << 71),
    IFBKeyCode_Numpad8               = (1 << 72),
    IFBKeyCode_Numpad9               = (1 << 73),
    IFBKeyCode_Multiply              = (1 << 74),
    IFBKeyCode_Add                   = (1 << 75),
    IFBKeyCode_Separator             = (1 << 76),
    IFBKeyCode_Subtract              = (1 << 77),
    IFBKeyCode_Decimal               = (1 << 78),
    IFBKeyCode_Divide                = (1 << 79),
    IFBKeyCode_F1                    = (1 << 80),
    IFBKeyCode_F2                    = (1 << 81),
    IFBKeyCode_F3                    = (1 << 82),
    IFBKeyCode_F4                    = (1 << 83),
    IFBKeyCode_F5                    = (1 << 84),
    IFBKeyCode_F6                    = (1 << 85),
    IFBKeyCode_F7                    = (1 << 86),
    IFBKeyCode_F8                    = (1 << 87),
    IFBKeyCode_F9                    = (1 << 88),
    IFBKeyCode_F10                   = (1 << 89),
    IFBKeyCode_F11                   = (1 << 90),
    IFBKeyCode_F12                   = (1 << 91),
    IFBKeyCode_Numlock               = (1 << 92),
    IFBKeyCode_ShiftLeft             = (1 << 93),
    IFBKeyCode_ShiftRight            = (1 << 94),
    IFBKeyCode_ControlLeft           = (1 << 95),
    IFBKeyCode_ControlRight          = (1 << 96),
    IFBKeyCode_MenuLeft              = (1 << 97),
    IFBKeyCode_MenuRight             = (1 << 98),
    IFBKeyCode_VolumeMute            = (1 << 99),
    IFBKeyCode_VolumeDown            = (1 << 100),
    IFBKeyCode_VolumeUp              = (1 << 101),
    IFBKeyCode_Plus                  = (1 << 102),
    IFBKeyCode_Comma                 = (1 << 103),
    IFBKeyCode_Minus                 = (1 << 104),
    IFBKeyCode_Period                = (1 << 105),
    IFBKeyCode_SlashForward_Question = (1 << 106),
    IFBKeyCode_Tilde                 = (1 << 107),
    IFBKeyCode_BracketOpen           = (1 << 108),
    IFBKeyCode_SlashBack_Pipe        = (1 << 109),
    IFBKeyCode_BracketClose          = (1 << 110),
    IFBKeyCode_Quote                 = (1 << 111)
};

struct IFBKeyCodeComposite {
    union {
        struct {
            ifb_u8 index;
            ifb_u8 group;
        };
        IFBKeyCode key_code;    
    };
};

#define IFB_ENGINE_USER_INPUT_KEYCODE_GROUP_COUNT 14

struct IFBKeyboard {
    union {
        struct {
            ifb_u8 group_0;
            ifb_u8 group_1;
            ifb_u8 group_2;
            ifb_u8 group_3;
            ifb_u8 group_4;
            ifb_u8 group_5;
            ifb_u8 group_6;
            ifb_u8 group_7;
            ifb_u8 group_8;
            ifb_u8 group_9;
            ifb_u8 group_10;
            ifb_u8 group_11;
            ifb_u8 group_12;
            ifb_u8 group_13;
        } groups;
        ifb_u8 array[IFB_ENGINE_USER_INPUT_KEYCODE_GROUP_COUNT];
    };
};

inline ifb_void
ifb_input::keyboard_key_down(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    IFBKeyCodeComposite key_code_composite;
    key_code_composite.key_code = key_code;

    ifb_macro_bit_set(
        key_code_composite.index,
        keyboard.array[key_code_composite.group]);                
}

inline ifb_void
ifb_input::keyboard_key_up(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    IFBKeyCodeComposite key_code_composite;
    key_code_composite.key_code = key_code;
    
    ifb_macro_bit_clear(
        key_code_composite.index,
        keyboard.array[key_code_composite.group]);                
}

inline const ifb_b8
ifb_input::keyboard_key_is_down(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    IFBKeyCodeComposite key_code_composite;
    key_code_composite.key_code = key_code;

    const ifb_b8 key_is_down = ifb_macro_bit_test(
        key_code_composite.index,
        keyboard.array[key_code_composite.group]);                        

    return(key_is_down);
}

inline const ifb_b8
ifb_input::keyboard_key_is_up(
    IFBKeyboard& keyboard,
    IFBKeyCode   key_code) {

    IFBKeyCodeComposite key_code_composite;
    key_code_composite.key_code = key_code;

    const ifb_b8 key_is_up = !ifb_macro_bit_test(
        key_code_composite.index,
        keyboard.array[key_code_composite.group]);                        

    return(key_is_up);
}

/**********************************************************************************/
/* MOUSE                                                                          */
/**********************************************************************************/

struct IFBMousePosition {
    ifb_s32 x;
    ifb_s32 y;
};

struct IFBMouse {
    struct {
        IFBMousePosition current;
        IFBMousePosition delta;
    } position;
    ifb_s32 wheel;
    ifb_b8  button_left;
    ifb_b8  button_right;
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
        ifb_f32 left;
        ifb_f32 right;
    } triggers;
};

inline ifb_void
ifb_input::gamepad_button_down(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {

    ifb_macro_bit_set(
        button_code,
        gamepad.button_codes);                
}

inline ifb_void
ifb_input::gamepad_button_up(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {
    
    ifb_macro_bit_clear(            
        button_code,
        gamepad.button_codes);                
}

inline const ifb_b8
ifb_input::gamepad_button_is_down(
    IFBGamepad&          gamepad,
    IFBGamepadButtonCode button_code) {

    const ifb_b8 key_is_down = ifb_macro_bit_test(
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

inline ifb_void
ifb_input::clear(
    IFBInput& input_ref) {
    
    input_ref = {0};
}

#endif //IFB_USER_INPUT_HPP