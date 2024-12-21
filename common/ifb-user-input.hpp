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

          ifb_void gamepad_button_down    (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);
          ifb_void gamepad_button_up      (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);
    const ifb_b8   gamepad_button_is_down (IFBGamepad& gamepad, IFBGamepadButtonCode button_code);

          ifb_void clear                  (IFBInput& input_ref);
};

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum IFBKeyCode_ {
    IFBKeyCode_Back                  = 0x0000,
    IFBKeyCode_Tab                   = 0x0100,
    IFBKeyCode_Clear                 = 0x0200,
    IFBKeyCode_Return                = 0x0300,
    IFBKeyCode_Shift                 = 0x0400,
    IFBKeyCode_Control               = 0x0500,
    IFBKeyCode_Menu                  = 0x0600,
    IFBKeyCode_Pause                 = 0x0700,
    IFBKeyCode_Capital               = 0x0001,
    IFBKeyCode_Escape                = 0x0101,
    IFBKeyCode_Space                 = 0x0201,
    IFBKeyCode_Prior                 = 0x0301,
    IFBKeyCode_Next                  = 0x0401,
    IFBKeyCode_End                   = 0x0501,
    IFBKeyCode_Home                  = 0x0601,
    IFBKeyCode_Left                  = 0x0701,
    IFBKeyCode_Up                    = 0x0002, 
    IFBKeyCode_Right                 = 0x0102, 
    IFBKeyCode_Down                  = 0x0202, 
    IFBKeyCode_Select                = 0x0302, 
    IFBKeyCode_Print                 = 0x0402, 
    IFBKeyCode_Snapshot              = 0x0502,  
    IFBKeyCode_Insert                = 0x0602,  
    IFBKeyCode_Delete                = 0x0702, 
    IFBKeyCode_Help                  = 0x0003,
    IFBKeyCode_0                     = 0x0103,
    IFBKeyCode_1                     = 0x0203,
    IFBKeyCode_2                     = 0x0303,
    IFBKeyCode_3                     = 0x0403,
    IFBKeyCode_4                     = 0x0503,
    IFBKeyCode_5                     = 0x0603,
    IFBKeyCode_6                     = 0x0703,
    IFBKeyCode_7                     = 0x0004,
    IFBKeyCode_8                     = 0x0104,
    IFBKeyCode_9                     = 0x0204,
    IFBKeyCode_A                     = 0x0304,
    IFBKeyCode_B                     = 0x0404,
    IFBKeyCode_C                     = 0x0504,
    IFBKeyCode_D                     = 0x0604,
    IFBKeyCode_E                     = 0x0704,
    IFBKeyCode_F                     = 0x0005,
    IFBKeyCode_G                     = 0x0105,
    IFBKeyCode_H                     = 0x0205,
    IFBKeyCode_I                     = 0x0305,
    IFBKeyCode_J                     = 0x0405,
    IFBKeyCode_K                     = 0x0505,
    IFBKeyCode_L                     = 0x0605,
    IFBKeyCode_M                     = 0x0705,
    IFBKeyCode_N                     = 0x0006,
    IFBKeyCode_O                     = 0x0106,
    IFBKeyCode_P                     = 0x0206,
    IFBKeyCode_Q                     = 0x0306,
    IFBKeyCode_R                     = 0x0406,
    IFBKeyCode_S                     = 0x0506,
    IFBKeyCode_T                     = 0x0606,
    IFBKeyCode_U                     = 0x0706,
    IFBKeyCode_V                     = 0x0007,
    IFBKeyCode_W                     = 0x0107,
    IFBKeyCode_X                     = 0x0207,
    IFBKeyCode_Y                     = 0x0307,
    IFBKeyCode_Z                     = 0x0407,
    IFBKeyCode_WinLeft               = 0x0507,
    IFBKeyCode_WinRight              = 0x0607,
    IFBKeyCode_Apps                  = 0x0707,
    IFBKeyCode_Numpad0               = 0x0008,
    IFBKeyCode_Numpad1               = 0x0108,
    IFBKeyCode_Numpad2               = 0x0208,
    IFBKeyCode_Numpad3               = 0x0308,
    IFBKeyCode_Numpad4               = 0x0408,
    IFBKeyCode_Numpad5               = 0x0508,
    IFBKeyCode_Numpad6               = 0x0608,
    IFBKeyCode_Numpad7               = 0x0708,
    IFBKeyCode_Numpad8               = 0x0009,
    IFBKeyCode_Numpad9               = 0x0109,
    IFBKeyCode_Multiply              = 0x0209,
    IFBKeyCode_Add                   = 0x0309,
    IFBKeyCode_Separator             = 0x0409,
    IFBKeyCode_Subtract              = 0x0509,
    IFBKeyCode_Decimal               = 0x0609,
    IFBKeyCode_Divide                = 0x0709,
    IFBKeyCode_F1                    = 0x000A,
    IFBKeyCode_F2                    = 0x010A,
    IFBKeyCode_F3                    = 0x020A,
    IFBKeyCode_F4                    = 0x030A,
    IFBKeyCode_F5                    = 0x040A,
    IFBKeyCode_F6                    = 0x050A,
    IFBKeyCode_F7                    = 0x060A,
    IFBKeyCode_F8                    = 0x070A,
    IFBKeyCode_F9                    = 0x000B,
    IFBKeyCode_F10                   = 0x010B,
    IFBKeyCode_F11                   = 0x020B,
    IFBKeyCode_F12                   = 0x030B,
    IFBKeyCode_Numlock               = 0x040B,
    IFBKeyCode_ShiftLeft             = 0x050B,
    IFBKeyCode_ShiftRight            = 0x060B,
    IFBKeyCode_ControlLeft           = 0x070B,
    IFBKeyCode_ControlRight          = 0x000C,
    IFBKeyCode_MenuLeft              = 0x010C,
    IFBKeyCode_MenuRight             = 0x020C,
    IFBKeyCode_VolumeMute            = 0x030C,
    IFBKeyCode_VolumeDown            = 0x040C,
    IFBKeyCode_VolumeUp              = 0x050C,
    IFBKeyCode_Plus                  = 0x060C,
    IFBKeyCode_Comma                 = 0x070C,
    IFBKeyCode_Minus                 = 0x000D,
    IFBKeyCode_Period                = 0x010D,
    IFBKeyCode_SlashForward_Question = 0x020D,
    IFBKeyCode_Tilde                 = 0x030D,
    IFBKeyCode_BracketOpen           = 0x040D,
    IFBKeyCode_SlashBack_Pipe        = 0x050D,
    IFBKeyCode_BracketClose          = 0x060D,
    IFBKeyCode_Quote                 = 0x070D
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