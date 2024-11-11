#ifndef IFB_ENGINE_USER_INPUT_HPP
#define IFB_ENGINE_USER_INPUT_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

/**********************************************************************************/
/* KEYBOARD                                                                       */
/**********************************************************************************/

enum IFBEngineUserInputKeyCode_ {
    IFBEngineUserInputKeyCode_Back                  = 0x0000,
    IFBEngineUserInputKeyCode_Tab                   = 0x0100,
    IFBEngineUserInputKeyCode_Clear                 = 0x0200,
    IFBEngineUserInputKeyCode_Return                = 0x0300,
    IFBEngineUserInputKeyCode_Shift                 = 0x0400,
    IFBEngineUserInputKeyCode_Control               = 0x0500,
    IFBEngineUserInputKeyCode_Menu                  = 0x0600,
    IFBEngineUserInputKeyCode_Pause                 = 0x0700,
    IFBEngineUserInputKeyCode_Capital               = 0x0001,
    IFBEngineUserInputKeyCode_Escape                = 0x0101,
    IFBEngineUserInputKeyCode_Space                 = 0x0201,
    IFBEngineUserInputKeyCode_Prior                 = 0x0301,
    IFBEngineUserInputKeyCode_Next                  = 0x0401,
    IFBEngineUserInputKeyCode_End                   = 0x0501,
    IFBEngineUserInputKeyCode_Home                  = 0x0601,
    IFBEngineUserInputKeyCode_Left                  = 0x0701,
    IFBEngineUserInputKeyCode_Up                    = 0x0002, 
    IFBEngineUserInputKeyCode_Right                 = 0x0102, 
    IFBEngineUserInputKeyCode_Down                  = 0x0202, 
    IFBEngineUserInputKeyCode_Select                = 0x0302, 
    IFBEngineUserInputKeyCode_Print                 = 0x0402, 
    IFBEngineUserInputKeyCode_Snapshot              = 0x0502,  
    IFBEngineUserInputKeyCode_Insert                = 0x0602,  
    IFBEngineUserInputKeyCode_Delete                = 0x0702, 
    IFBEngineUserInputKeyCode_Help                  = 0x0003,
    IFBEngineUserInputKeyCode_0                     = 0x0103,
    IFBEngineUserInputKeyCode_1                     = 0x0203,
    IFBEngineUserInputKeyCode_2                     = 0x0303,
    IFBEngineUserInputKeyCode_3                     = 0x0403,
    IFBEngineUserInputKeyCode_4                     = 0x0503,
    IFBEngineUserInputKeyCode_5                     = 0x0603,
    IFBEngineUserInputKeyCode_6                     = 0x0703,
    IFBEngineUserInputKeyCode_7                     = 0x0004,
    IFBEngineUserInputKeyCode_8                     = 0x0104,
    IFBEngineUserInputKeyCode_9                     = 0x0204,
    IFBEngineUserInputKeyCode_A                     = 0x0304,
    IFBEngineUserInputKeyCode_B                     = 0x0404,
    IFBEngineUserInputKeyCode_C                     = 0x0504,
    IFBEngineUserInputKeyCode_D                     = 0x0604,
    IFBEngineUserInputKeyCode_E                     = 0x0704,
    IFBEngineUserInputKeyCode_F                     = 0x0005,
    IFBEngineUserInputKeyCode_G                     = 0x0105,
    IFBEngineUserInputKeyCode_H                     = 0x0205,
    IFBEngineUserInputKeyCode_I                     = 0x0305,
    IFBEngineUserInputKeyCode_J                     = 0x0405,
    IFBEngineUserInputKeyCode_K                     = 0x0505,
    IFBEngineUserInputKeyCode_L                     = 0x0605,
    IFBEngineUserInputKeyCode_M                     = 0x0705,
    IFBEngineUserInputKeyCode_N                     = 0x0006,
    IFBEngineUserInputKeyCode_O                     = 0x0106,
    IFBEngineUserInputKeyCode_P                     = 0x0206,
    IFBEngineUserInputKeyCode_Q                     = 0x0306,
    IFBEngineUserInputKeyCode_R                     = 0x0406,
    IFBEngineUserInputKeyCode_S                     = 0x0506,
    IFBEngineUserInputKeyCode_T                     = 0x0606,
    IFBEngineUserInputKeyCode_U                     = 0x0706,
    IFBEngineUserInputKeyCode_V                     = 0x0007,
    IFBEngineUserInputKeyCode_W                     = 0x0107,
    IFBEngineUserInputKeyCode_X                     = 0x0207,
    IFBEngineUserInputKeyCode_Y                     = 0x0307,
    IFBEngineUserInputKeyCode_Z                     = 0x0407,
    IFBEngineUserInputKeyCode_WinLeft               = 0x0507,
    IFBEngineUserInputKeyCode_WinRight              = 0x0607,
    IFBEngineUserInputKeyCode_Apps                  = 0x0707,
    IFBEngineUserInputKeyCode_Numpad0               = 0x0008,
    IFBEngineUserInputKeyCode_Numpad1               = 0x0108,
    IFBEngineUserInputKeyCode_Numpad2               = 0x0208,
    IFBEngineUserInputKeyCode_Numpad3               = 0x0308,
    IFBEngineUserInputKeyCode_Numpad4               = 0x0408,
    IFBEngineUserInputKeyCode_Numpad5               = 0x0508,
    IFBEngineUserInputKeyCode_Numpad6               = 0x0608,
    IFBEngineUserInputKeyCode_Numpad7               = 0x0708,
    IFBEngineUserInputKeyCode_Numpad8               = 0x0009,
    IFBEngineUserInputKeyCode_Numpad9               = 0x0109,
    IFBEngineUserInputKeyCode_Multiply              = 0x0209,
    IFBEngineUserInputKeyCode_Add                   = 0x0309,
    IFBEngineUserInputKeyCode_Separator             = 0x0409,
    IFBEngineUserInputKeyCode_Subtract              = 0x0509,
    IFBEngineUserInputKeyCode_Decimal               = 0x0609,
    IFBEngineUserInputKeyCode_Divide                = 0x0709,
    IFBEngineUserInputKeyCode_F1                    = 0x000A,
    IFBEngineUserInputKeyCode_F2                    = 0x010A,
    IFBEngineUserInputKeyCode_F3                    = 0x020A,
    IFBEngineUserInputKeyCode_F4                    = 0x030A,
    IFBEngineUserInputKeyCode_F5                    = 0x040A,
    IFBEngineUserInputKeyCode_F6                    = 0x050A,
    IFBEngineUserInputKeyCode_F7                    = 0x060A,
    IFBEngineUserInputKeyCode_F8                    = 0x070A,
    IFBEngineUserInputKeyCode_F9                    = 0x000B,
    IFBEngineUserInputKeyCode_F10                   = 0x010B,
    IFBEngineUserInputKeyCode_F11                   = 0x020B,
    IFBEngineUserInputKeyCode_F12                   = 0x030B,
    IFBEngineUserInputKeyCode_Numlock               = 0x040B,
    IFBEngineUserInputKeyCode_ShiftLeft             = 0x050B,
    IFBEngineUserInputKeyCode_ShiftRight            = 0x060B,
    IFBEngineUserInputKeyCode_ControlLeft           = 0x070B,
    IFBEngineUserInputKeyCode_ControlRight          = 0x000C,
    IFBEngineUserInputKeyCode_MenuLeft              = 0x010C,
    IFBEngineUserInputKeyCode_MenuRight             = 0x020C,
    IFBEngineUserInputKeyCode_VolumeMute            = 0x030C,
    IFBEngineUserInputKeyCode_VolumeDown            = 0x040C,
    IFBEngineUserInputKeyCode_VolumeUp              = 0x050C,
    IFBEngineUserInputKeyCode_Plus                  = 0x060C,
    IFBEngineUserInputKeyCode_Comma                 = 0x070C,
    IFBEngineUserInputKeyCode_Minus                 = 0x000D,
    IFBEngineUserInputKeyCode_Period                = 0x010D,
    IFBEngineUserInputKeyCode_SlashForward_Question = 0x020D,
    IFBEngineUserInputKeyCode_Tilde                 = 0x030D,
    IFBEngineUserInputKeyCode_BracketOpen           = 0x040D,
    IFBEngineUserInputKeyCode_SlashBack_Pipe        = 0x050D,
    IFBEngineUserInputKeyCode_BracketClose          = 0x060D,
    IFBEngineUserInputKeyCode_Quote                 = 0x070D
};

typedef ifb_u16 IFBEngineUserInputKeyCode;

union IFBEngineUserInputKeyCodeComposite {
    struct {
        ifb_u8 index;
        ifb_u8 group;
    };
    IFBEngineUserInputKeyCode key_code;    
};

#define IFB_ENGINE_USER_INPUT_KEYCODE_GROUP_COUNT 14

union IFBEngineUserInputKeyboard {
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

namespace ifb_engine {

    inline ifb_void
    user_input_keyboard_key_down(
        IFBEngineUserInputKeyboard& keyboard,
        IFBEngineUserInputKeyCode   key_code) {

        IFBEngineUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;

        ifb_engine_macro_bit_set(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                
    }

    inline ifb_void
    user_input_keyboard_key_up(
        IFBEngineUserInputKeyboard& keyboard,
        IFBEngineUserInputKeyCode   key_code) {

        IFBEngineUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;
        
        ifb_engine_macro_bit_clear(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                
    }

    inline const ifb_b8
    user_input_keyboard_key_is_down(
        IFBEngineUserInputKeyboard& keyboard,
        IFBEngineUserInputKeyCode   key_code) {

        IFBEngineUserInputKeyCodeComposite key_code_composite;
        key_code_composite.key_code = key_code;

        const ifb_b8 key_is_down = ifb_engine_macro_bit_test(
            key_code_composite.index,
            keyboard.array[key_code_composite.group]);                        

        return(key_is_down);
    }
};

/**********************************************************************************/
/* MOUSE                                                                          */
/**********************************************************************************/

struct IFBEngineUserInputMousePosition {
    ifb_s32 x;
    ifb_s32 y;
};

struct IFBEngineUserInputMouse {
    struct {
        IFBEngineUserInputMousePosition current;
        IFBEngineUserInputMousePosition delta;
    } position;
    ifb_s32 wheel;
    ifb_b8  button_left;
    ifb_b8  button_right;
};

/**********************************************************************************/
/* GAMEPAD                                                                        */
/**********************************************************************************/

enum IFBEngineUserInputGamepadButtonCode_ {
    IFBEngineUserInputGamepadButtonCode_DpadUp      = 0x00, 
    IFBEngineUserInputGamepadButtonCode_DpadDown    = 0x01, 
    IFBEngineUserInputGamepadButtonCode_DpadLeft    = 0x02, 
    IFBEngineUserInputGamepadButtonCode_DpadRight   = 0x03, 
    IFBEngineUserInputGamepadButtonCode_Start       = 0x04, 
    IFBEngineUserInputGamepadButtonCode_Select      = 0x05, 
    IFBEngineUserInputGamepadButtonCode_StickLeft   = 0x06, 
    IFBEngineUserInputGamepadButtonCode_StickRight  = 0x07, 
    IFBEngineUserInputGamepadButtonCode_BumberLeft  = 0x08, 
    IFBEngineUserInputGamepadButtonCode_BumberRight = 0x09, 
    IFBEngineUserInputGamepadButtonCode_BpadA       = 0x0C, 
    IFBEngineUserInputGamepadButtonCode_BpadB       = 0x0D, 
    IFBEngineUserInputGamepadButtonCode_BpadX       = 0x0E, 
    IFBEngineUserInputGamepadButtonCode_BpadY       = 0x0F, 
};

typedef ifb_u16 IFBEngineUserInputGamepadButtonCode; 

struct IFBEngineUserInputGamepad {
    IFBEngineUserInputGamepadButtonCode button_codes;
    struct {
        ifb_f32 left;
        ifb_f32 right;
    } triggers;
};

namespace ifb_engine {

    inline ifb_void
    user_input_gamepad_button_down(
        IFBEngineUserInputGamepad&          gamepad,
        IFBEngineUserInputGamepadButtonCode button_code) {

        ifb_engine_macro_bit_set(
            button_code,
            gamepad.button_codes);                
    }

    inline ifb_void
    user_input_gamepad_button_up(
        IFBEngineUserInputGamepad&          gamepad,
        IFBEngineUserInputGamepadButtonCode button_code) {
        
        ifb_engine_macro_bit_clear(            
            button_code,
            gamepad.button_codes);                
    }

    inline const ifb_b8
    user_input_gamepad_button_is_down(
        IFBEngineUserInputGamepad&          gamepad,
        IFBEngineUserInputGamepadButtonCode button_code) {

        const ifb_b8 key_is_down = ifb_engine_macro_bit_test(
            button_code,
            gamepad.button_codes);                        

        return(key_is_down);
    }
}

/**********************************************************************************/
/* USER INPUT                                                                     */
/**********************************************************************************/

struct IFBEngineUserInput {
    IFBEngineUserInputKeyboard keyboard;
    IFBEngineUserInputMouse    mouse;
    IFBEngineUserInputGamepad  gamepad;
};

namespace ifb_engine {

    inline ifb_void
    user_input_clear(
        IFBEngineUserInput& user_input_ref) {
        
        user_input_ref = {0};
    }
};

#endif //IFB_ENGINE_USER_INPUT_HPP