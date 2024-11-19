#ifndef IFB_COMMON_USER_INPUT_HPP
#define IFB_COMMON_USER_INPUT_HPP

#include "ifb-common-types.hpp"
#include "ifb-common-scopes.hpp"
#include "ifb-common-macros.hpp"

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum IFBUserInputKeyCode_ {
    IFBUserInputKeyCode_Back                  = 0x0000,
    IFBUserInputKeyCode_Tab                   = 0x0100,
    IFBUserInputKeyCode_Clear                 = 0x0200,
    IFBUserInputKeyCode_Return                = 0x0300,
    IFBUserInputKeyCode_Shift                 = 0x0400,
    IFBUserInputKeyCode_Control               = 0x0500,
    IFBUserInputKeyCode_Menu                  = 0x0600,
    IFBUserInputKeyCode_Pause                 = 0x0700,
    IFBUserInputKeyCode_Capital               = 0x0001,
    IFBUserInputKeyCode_Escape                = 0x0101,
    IFBUserInputKeyCode_Space                 = 0x0201,
    IFBUserInputKeyCode_Prior                 = 0x0301,
    IFBUserInputKeyCode_Next                  = 0x0401,
    IFBUserInputKeyCode_End                   = 0x0501,
    IFBUserInputKeyCode_Home                  = 0x0601,
    IFBUserInputKeyCode_Left                  = 0x0701,
    IFBUserInputKeyCode_Up                    = 0x0002, 
    IFBUserInputKeyCode_Right                 = 0x0102, 
    IFBUserInputKeyCode_Down                  = 0x0202, 
    IFBUserInputKeyCode_Select                = 0x0302, 
    IFBUserInputKeyCode_Print                 = 0x0402, 
    IFBUserInputKeyCode_Snapshot              = 0x0502,  
    IFBUserInputKeyCode_Insert                = 0x0602,  
    IFBUserInputKeyCode_Delete                = 0x0702, 
    IFBUserInputKeyCode_Help                  = 0x0003,
    IFBUserInputKeyCode_0                     = 0x0103,
    IFBUserInputKeyCode_1                     = 0x0203,
    IFBUserInputKeyCode_2                     = 0x0303,
    IFBUserInputKeyCode_3                     = 0x0403,
    IFBUserInputKeyCode_4                     = 0x0503,
    IFBUserInputKeyCode_5                     = 0x0603,
    IFBUserInputKeyCode_6                     = 0x0703,
    IFBUserInputKeyCode_7                     = 0x0004,
    IFBUserInputKeyCode_8                     = 0x0104,
    IFBUserInputKeyCode_9                     = 0x0204,
    IFBUserInputKeyCode_A                     = 0x0304,
    IFBUserInputKeyCode_B                     = 0x0404,
    IFBUserInputKeyCode_C                     = 0x0504,
    IFBUserInputKeyCode_D                     = 0x0604,
    IFBUserInputKeyCode_E                     = 0x0704,
    IFBUserInputKeyCode_F                     = 0x0005,
    IFBUserInputKeyCode_G                     = 0x0105,
    IFBUserInputKeyCode_H                     = 0x0205,
    IFBUserInputKeyCode_I                     = 0x0305,
    IFBUserInputKeyCode_J                     = 0x0405,
    IFBUserInputKeyCode_K                     = 0x0505,
    IFBUserInputKeyCode_L                     = 0x0605,
    IFBUserInputKeyCode_M                     = 0x0705,
    IFBUserInputKeyCode_N                     = 0x0006,
    IFBUserInputKeyCode_O                     = 0x0106,
    IFBUserInputKeyCode_P                     = 0x0206,
    IFBUserInputKeyCode_Q                     = 0x0306,
    IFBUserInputKeyCode_R                     = 0x0406,
    IFBUserInputKeyCode_S                     = 0x0506,
    IFBUserInputKeyCode_T                     = 0x0606,
    IFBUserInputKeyCode_U                     = 0x0706,
    IFBUserInputKeyCode_V                     = 0x0007,
    IFBUserInputKeyCode_W                     = 0x0107,
    IFBUserInputKeyCode_X                     = 0x0207,
    IFBUserInputKeyCode_Y                     = 0x0307,
    IFBUserInputKeyCode_Z                     = 0x0407,
    IFBUserInputKeyCode_WinLeft               = 0x0507,
    IFBUserInputKeyCode_WinRight              = 0x0607,
    IFBUserInputKeyCode_Apps                  = 0x0707,
    IFBUserInputKeyCode_Numpad0               = 0x0008,
    IFBUserInputKeyCode_Numpad1               = 0x0108,
    IFBUserInputKeyCode_Numpad2               = 0x0208,
    IFBUserInputKeyCode_Numpad3               = 0x0308,
    IFBUserInputKeyCode_Numpad4               = 0x0408,
    IFBUserInputKeyCode_Numpad5               = 0x0508,
    IFBUserInputKeyCode_Numpad6               = 0x0608,
    IFBUserInputKeyCode_Numpad7               = 0x0708,
    IFBUserInputKeyCode_Numpad8               = 0x0009,
    IFBUserInputKeyCode_Numpad9               = 0x0109,
    IFBUserInputKeyCode_Multiply              = 0x0209,
    IFBUserInputKeyCode_Add                   = 0x0309,
    IFBUserInputKeyCode_Separator             = 0x0409,
    IFBUserInputKeyCode_Subtract              = 0x0509,
    IFBUserInputKeyCode_Decimal               = 0x0609,
    IFBUserInputKeyCode_Divide                = 0x0709,
    IFBUserInputKeyCode_F1                    = 0x000A,
    IFBUserInputKeyCode_F2                    = 0x010A,
    IFBUserInputKeyCode_F3                    = 0x020A,
    IFBUserInputKeyCode_F4                    = 0x030A,
    IFBUserInputKeyCode_F5                    = 0x040A,
    IFBUserInputKeyCode_F6                    = 0x050A,
    IFBUserInputKeyCode_F7                    = 0x060A,
    IFBUserInputKeyCode_F8                    = 0x070A,
    IFBUserInputKeyCode_F9                    = 0x000B,
    IFBUserInputKeyCode_F10                   = 0x010B,
    IFBUserInputKeyCode_F11                   = 0x020B,
    IFBUserInputKeyCode_F12                   = 0x030B,
    IFBUserInputKeyCode_Numlock               = 0x040B,
    IFBUserInputKeyCode_ShiftLeft             = 0x050B,
    IFBUserInputKeyCode_ShiftRight            = 0x060B,
    IFBUserInputKeyCode_ControlLeft           = 0x070B,
    IFBUserInputKeyCode_ControlRight          = 0x000C,
    IFBUserInputKeyCode_MenuLeft              = 0x010C,
    IFBUserInputKeyCode_MenuRight             = 0x020C,
    IFBUserInputKeyCode_VolumeMute            = 0x030C,
    IFBUserInputKeyCode_VolumeDown            = 0x040C,
    IFBUserInputKeyCode_VolumeUp              = 0x050C,
    IFBUserInputKeyCode_Plus                  = 0x060C,
    IFBUserInputKeyCode_Comma                 = 0x070C,
    IFBUserInputKeyCode_Minus                 = 0x000D,
    IFBUserInputKeyCode_Period                = 0x010D,
    IFBUserInputKeyCode_SlashForward_Question = 0x020D,
    IFBUserInputKeyCode_Tilde                 = 0x030D,
    IFBUserInputKeyCode_BracketOpen           = 0x040D,
    IFBUserInputKeyCode_SlashBack_Pipe        = 0x050D,
    IFBUserInputKeyCode_BracketClose          = 0x060D,
    IFBUserInputKeyCode_Quote                 = 0x070D
};

typedef ifb_u16 IFBUserInputKeyCode;

union IFBUserInputKeyCodeComposite {
    struct {
        ifb_u8 index;
        ifb_u8 group;
    };
    IFBUserInputKeyCode key_code;    
};

#define IFB_ENGINE_USER_INPUT_KEYCODE_GROUP_COUNT 14

union IFBUserInputKeyboard {
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

namespace ifb_common {

    inline ifb_void
    user_input_keyboard_key_down(
        IFBUserInputKeyboard& keyboard,
        IFBUserInputKeyCode   key_code) {

        IFBUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;

        ifb_macro_bit_set(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                
    }

    inline ifb_void
    user_input_keyboard_key_up(
        IFBUserInputKeyboard& keyboard,
        IFBUserInputKeyCode   key_code) {

        IFBUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;
        
        ifb_macro_bit_clear(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                
    }

    inline const ifb_b8
    user_input_keyboard_key_is_down(
        IFBUserInputKeyboard& keyboard,
        IFBUserInputKeyCode   key_code) {

        IFBUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;

        const ifb_b8 key_is_down = ifb_macro_bit_test(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                        

        return(key_is_down);
    }
};

/**********************************************************************************/
/* MOUSE                                                                          */
/**********************************************************************************/

struct IFBUserInputMousePosition {
    ifb_s32 x;
    ifb_s32 y;
};

struct IFBUserInputMouse {
    struct {
        IFBUserInputMousePosition current;
        IFBUserInputMousePosition delta;
    } position;
    ifb_s32 wheel;
    ifb_b8  button_left;
    ifb_b8  button_right;
};

/**********************************************************************************/
/* GAMEPAD                                                                        */
/**********************************************************************************/

enum IFBUserInputGamepadButtonCode_ {
    IFBUserInputGamepadButtonCode_DpadUp      = 0x00, 
    IFBUserInputGamepadButtonCode_DpadDown    = 0x01, 
    IFBUserInputGamepadButtonCode_DpadLeft    = 0x02, 
    IFBUserInputGamepadButtonCode_DpadRight   = 0x03, 
    IFBUserInputGamepadButtonCode_Start       = 0x04, 
    IFBUserInputGamepadButtonCode_Select      = 0x05, 
    IFBUserInputGamepadButtonCode_StickLeft   = 0x06, 
    IFBUserInputGamepadButtonCode_StickRight  = 0x07, 
    IFBUserInputGamepadButtonCode_BumberLeft  = 0x08, 
    IFBUserInputGamepadButtonCode_BumberRight = 0x09, 
    IFBUserInputGamepadButtonCode_BpadA       = 0x0C, 
    IFBUserInputGamepadButtonCode_BpadB       = 0x0D, 
    IFBUserInputGamepadButtonCode_BpadX       = 0x0E, 
    IFBUserInputGamepadButtonCode_BpadY       = 0x0F, 
};

typedef ifb_u16 IFBUserInputGamepadButtonCode; 

struct IFBUserInputGamepad {
    IFBUserInputGamepadButtonCode button_codes;
    struct {
        ifb_f32 left;
        ifb_f32 right;
    } triggers;
};

namespace ifb_common {

    inline ifb_void
    user_input_gamepad_button_down(
        IFBUserInputGamepad&          gamepad,
        IFBUserInputGamepadButtonCode button_code) {

        ifb_macro_bit_set(
            button_code,
            gamepad.button_codes);                
    }

    inline ifb_void
    user_input_gamepad_button_up(
        IFBUserInputGamepad&          gamepad,
        IFBUserInputGamepadButtonCode button_code) {
        
        ifb_macro_bit_clear(            
            button_code,
            gamepad.button_codes);                
    }

    inline const ifb_b8
    user_input_gamepad_button_is_down(
        IFBUserInputGamepad&          gamepad,
        IFBUserInputGamepadButtonCode button_code) {

        const ifb_b8 key_is_down = ifb_macro_bit_test(
            button_code,
            gamepad.button_codes);                        

        return(key_is_down);
    }
}

/**********************************************************************************/
/* USER INPUT                                                                     */
/**********************************************************************************/

struct IFBUserInput {
    IFBUserInputKeyboard keyboard;
    IFBUserInputMouse    mouse;
    IFBUserInputGamepad  gamepad;
};

namespace ifb_common {

    inline ifb_void
    user_input_clear(
        IFBUserInput& user_input_ref) {
        
        user_input_ref = {0};
    }
};

#endif //IFB_COMMON_USER_INPUT_HPP