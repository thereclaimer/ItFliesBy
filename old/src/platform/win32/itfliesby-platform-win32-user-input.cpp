#pragma once

#include "itfliesby-platform-win32.hpp"

#define WIN32_GAMEPAD_STICK_DEADZONE_SQUARED 5000
#define WIN32_GAMEPAD_STICK_MAX_NEGATIVE     0.000030517578125f
#define WIN32_GAMEPAD_STICK_MAX_POSITIVE     0.000030518509475f
#define WIN32_GAMEPAD_TRIGGER_MAX            255.0f

internal b8
itfliesby_platform_win32_get_xinput_state(ItfliesbyGamepadInput* gamepad) {

    local XINPUT_STATE xinput_state = {0};

    if (XInputGetState(0,&xinput_state) == ERROR_SUCCESS) {
        
        //reset the input
        *gamepad = {0};

        //check if the sticks are in the deadzone
        s32 stick_left_x_corrected  = (xinput_state.Gamepad.sThumbLX ^ 2) > WIN32_GAMEPAD_STICK_DEADZONE_SQUARED || (xinput_state.Gamepad.sThumbLX ^ 2) < -WIN32_GAMEPAD_STICK_DEADZONE_SQUARED ? xinput_state.Gamepad.sThumbLX : 0;
        s32 stick_left_y_corrected  = (xinput_state.Gamepad.sThumbLY ^ 2) > WIN32_GAMEPAD_STICK_DEADZONE_SQUARED || (xinput_state.Gamepad.sThumbLY ^ 2) < -WIN32_GAMEPAD_STICK_DEADZONE_SQUARED ? xinput_state.Gamepad.sThumbLY : 0;
        s32 stick_right_x_corrected = (xinput_state.Gamepad.sThumbRX ^ 2) > WIN32_GAMEPAD_STICK_DEADZONE_SQUARED || (xinput_state.Gamepad.sThumbRX ^ 2) < -WIN32_GAMEPAD_STICK_DEADZONE_SQUARED ? xinput_state.Gamepad.sThumbRX : 0;
        s32 stick_right_y_corrected = (xinput_state.Gamepad.sThumbRY ^ 2) > WIN32_GAMEPAD_STICK_DEADZONE_SQUARED || (xinput_state.Gamepad.sThumbRY ^ 2) < -WIN32_GAMEPAD_STICK_DEADZONE_SQUARED ? xinput_state.Gamepad.sThumbRY : 0;

        //set the stick inputs
        gamepad->stick_left_x  = stick_left_x_corrected < 0 ? (stick_left_x_corrected * WIN32_GAMEPAD_STICK_MAX_NEGATIVE) : (stick_left_x_corrected * WIN32_GAMEPAD_STICK_MAX_POSITIVE);
        gamepad->stick_left_y  = stick_left_y_corrected < 0 ? (stick_left_y_corrected * WIN32_GAMEPAD_STICK_MAX_NEGATIVE) : (stick_left_y_corrected * WIN32_GAMEPAD_STICK_MAX_POSITIVE);
        gamepad->stick_right_x = stick_right_x_corrected < 0 ? (stick_right_x_corrected * WIN32_GAMEPAD_STICK_MAX_NEGATIVE) : (stick_right_x_corrected * WIN32_GAMEPAD_STICK_MAX_POSITIVE);
        gamepad->stick_right_y = stick_right_y_corrected < 0 ? (stick_right_y_corrected * WIN32_GAMEPAD_STICK_MAX_NEGATIVE) : (stick_right_y_corrected * WIN32_GAMEPAD_STICK_MAX_POSITIVE);
        
        gamepad->trigger_left  = xinput_state.Gamepad.bLeftTrigger /  WIN32_GAMEPAD_TRIGGER_MAX;
        gamepad->trigger_right = xinput_state.Gamepad.bRightTrigger / WIN32_GAMEPAD_TRIGGER_MAX;

        gamepad->buttons = xinput_state.Gamepad.wButtons;
        

        return(true);
    }
    return(false);
}


internal u32
itfliesby_platform_win32_translate_user_keycode(u32 keycode) {

    u32 itfliesby_keycode = 0;

    switch (keycode ) {

        case VK_BACK:        { itfliesby_keycode = ITFLIESBY_KEYCODE_BACK; } break;
        case VK_TAB:         { itfliesby_keycode = ITFLIESBY_KEYCODE_TAB; } break;
        case VK_CLEAR:       { itfliesby_keycode = ITFLIESBY_KEYCODE_CLEAR; } break;
        case VK_RETURN:      { itfliesby_keycode = ITFLIESBY_KEYCODE_RETURN; } break;
        case VK_SHIFT:       { itfliesby_keycode = ITFLIESBY_KEYCODE_SHIFT; } break;
        case VK_CONTROL:     { itfliesby_keycode = ITFLIESBY_KEYCODE_CONTROL; } break;
        case VK_MENU:        { itfliesby_keycode = ITFLIESBY_KEYCODE_MENU; } break;
        case VK_PAUSE:       { itfliesby_keycode = ITFLIESBY_KEYCODE_PAUSE; } break;
        case VK_CAPITAL:     { itfliesby_keycode = ITFLIESBY_KEYCODE_CAPITAL; } break;
        case VK_ESCAPE:      { itfliesby_keycode = ITFLIESBY_KEYCODE_ESCAPE; } break;
        case VK_SPACE:       { itfliesby_keycode = ITFLIESBY_KEYCODE_SPACE; } break;
        case VK_PRIOR:       { itfliesby_keycode = ITFLIESBY_KEYCODE_PRIOR; } break;
        case VK_NEXT:        { itfliesby_keycode = ITFLIESBY_KEYCODE_NEXT; } break;
        case VK_END:         { itfliesby_keycode = ITFLIESBY_KEYCODE_END; } break;
        case VK_HOME:        { itfliesby_keycode = ITFLIESBY_KEYCODE_HOME; } break;
        case VK_LEFT:        { itfliesby_keycode = ITFLIESBY_KEYCODE_LEFT; } break;
        case VK_UP:          { itfliesby_keycode = ITFLIESBY_KEYCODE_UP; } break;
        case VK_RIGHT:       { itfliesby_keycode = ITFLIESBY_KEYCODE_RIGHT; } break;
        case VK_DOWN:        { itfliesby_keycode = ITFLIESBY_KEYCODE_DOWN; } break;
        case VK_SELECT:      { itfliesby_keycode = ITFLIESBY_KEYCODE_SELECT; } break;
        case VK_PRINT:       { itfliesby_keycode = ITFLIESBY_KEYCODE_PRINT; } break;
        case VK_SNAPSHOT:    { itfliesby_keycode = ITFLIESBY_KEYCODE_SNAPSHOT; } break;
        case VK_INSERT:      { itfliesby_keycode = ITFLIESBY_KEYCODE_INSERT; } break;
        case VK_DELETE:      { itfliesby_keycode = ITFLIESBY_KEYCODE_DELETE; } break;
        case VK_HELP:        { itfliesby_keycode = ITFLIESBY_KEYCODE_HELP; } break;
        case 0x30:           { itfliesby_keycode = ITFLIESBY_KEYCODE_0; } break;
        case 0x31:           { itfliesby_keycode = ITFLIESBY_KEYCODE_1; } break;
        case 0x32:           { itfliesby_keycode = ITFLIESBY_KEYCODE_2; } break;
        case 0x33:           { itfliesby_keycode = ITFLIESBY_KEYCODE_3; } break;
        case 0x34:           { itfliesby_keycode = ITFLIESBY_KEYCODE_4; } break;
        case 0x35:           { itfliesby_keycode = ITFLIESBY_KEYCODE_5; } break;
        case 0x36:           { itfliesby_keycode = ITFLIESBY_KEYCODE_6; } break;
        case 0x37:           { itfliesby_keycode = ITFLIESBY_KEYCODE_7; } break;
        case 0x38:           { itfliesby_keycode = ITFLIESBY_KEYCODE_8; } break;
        case 0x39:           { itfliesby_keycode = ITFLIESBY_KEYCODE_9; } break;
        case 0x41:           { itfliesby_keycode = ITFLIESBY_KEYCODE_A; } break;
        case 0x42:           { itfliesby_keycode = ITFLIESBY_KEYCODE_B; } break;
        case 0x43:           { itfliesby_keycode = ITFLIESBY_KEYCODE_C; } break;
        case 0x44:           { itfliesby_keycode = ITFLIESBY_KEYCODE_D; } break;
        case 0x45:           { itfliesby_keycode = ITFLIESBY_KEYCODE_E; } break;
        case 0x46:           { itfliesby_keycode = ITFLIESBY_KEYCODE_F; } break;
        case 0x47:           { itfliesby_keycode = ITFLIESBY_KEYCODE_G; } break;
        case 0x48:           { itfliesby_keycode = ITFLIESBY_KEYCODE_H; } break;
        case 0x49:           { itfliesby_keycode = ITFLIESBY_KEYCODE_I; } break;
        case 0x4A:           { itfliesby_keycode = ITFLIESBY_KEYCODE_J; } break;
        case 0x4B:           { itfliesby_keycode = ITFLIESBY_KEYCODE_K; } break;
        case 0x4C:           { itfliesby_keycode = ITFLIESBY_KEYCODE_L; } break;
        case 0x4D:           { itfliesby_keycode = ITFLIESBY_KEYCODE_M; } break;
        case 0x4E:           { itfliesby_keycode = ITFLIESBY_KEYCODE_N; } break;
        case 0x4F:           { itfliesby_keycode = ITFLIESBY_KEYCODE_O; } break;
        case 0x50:           { itfliesby_keycode = ITFLIESBY_KEYCODE_P; } break;
        case 0x51:           { itfliesby_keycode = ITFLIESBY_KEYCODE_Q; } break;
        case 0x52:           { itfliesby_keycode = ITFLIESBY_KEYCODE_R; } break;
        case 0x53:           { itfliesby_keycode = ITFLIESBY_KEYCODE_S; } break;
        case 0x54:           { itfliesby_keycode = ITFLIESBY_KEYCODE_T; } break;
        case 0x55:           { itfliesby_keycode = ITFLIESBY_KEYCODE_U; } break;
        case 0x56:           { itfliesby_keycode = ITFLIESBY_KEYCODE_V; } break;
        case 0x57:           { itfliesby_keycode = ITFLIESBY_KEYCODE_W; } break;
        case 0x58:           { itfliesby_keycode = ITFLIESBY_KEYCODE_X; } break;
        case 0x59:           { itfliesby_keycode = ITFLIESBY_KEYCODE_Y; } break;
        case 0x5A:           { itfliesby_keycode = ITFLIESBY_KEYCODE_Z; } break;
        case VK_LWIN:        { itfliesby_keycode = ITFLIESBY_KEYCODE_LEFT_WIN; } break;
        case VK_RWIN:        { itfliesby_keycode = ITFLIESBY_KEYCODE_RIGHT_WIN; } break;
        case VK_APPS:        { itfliesby_keycode = ITFLIESBY_KEYCODE_APPS; } break;
        case VK_NUMPAD0:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_0; } break;
        case VK_NUMPAD1:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_1; } break;
        case VK_NUMPAD2:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_2; } break;
        case VK_NUMPAD3:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_3; } break;
        case VK_NUMPAD4:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_4; } break;
        case VK_NUMPAD5:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_5; } break;
        case VK_NUMPAD6:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_6; } break;
        case VK_NUMPAD7:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_7; } break;
        case VK_NUMPAD8:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_8; } break;
        case VK_NUMPAD9:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMPAD_9; } break;
        case VK_MULTIPLY:    { itfliesby_keycode = ITFLIESBY_KEYCODE_MULTIPLY; } break;
        case VK_ADD:         { itfliesby_keycode = ITFLIESBY_KEYCODE_ADD; } break;
        case VK_SEPARATOR:   { itfliesby_keycode = ITFLIESBY_KEYCODE_SEPARATOR; } break;
        case VK_SUBTRACT:    { itfliesby_keycode = ITFLIESBY_KEYCODE_SUBTRACT; } break;
        case VK_DECIMAL:     { itfliesby_keycode = ITFLIESBY_KEYCODE_DECIMAL; } break;
        case VK_DIVIDE:      { itfliesby_keycode = ITFLIESBY_KEYCODE_DIVIDE; } break;
        case VK_F1:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F1; } break;
        case VK_F2:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F2; } break;
        case VK_F3:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F3; } break;
        case VK_F4:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F4; } break;
        case VK_F5:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F5; } break;
        case VK_F6:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F6; } break;
        case VK_F7:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F7; } break;
        case VK_F8:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F8; } break;
        case VK_F9:          { itfliesby_keycode = ITFLIESBY_KEYCODE_F9; } break;
        case VK_F10:         { itfliesby_keycode = ITFLIESBY_KEYCODE_F10; } break;
        case VK_F11:         { itfliesby_keycode = ITFLIESBY_KEYCODE_F11; } break;
        case VK_F12:         { itfliesby_keycode = ITFLIESBY_KEYCODE_F12; } break;
        case VK_NUMLOCK:     { itfliesby_keycode = ITFLIESBY_KEYCODE_NUMLOCK; } break;
        case VK_LSHIFT:      { itfliesby_keycode = ITFLIESBY_KEYCODE_LSHIFT; } break;
        case VK_RSHIFT:      { itfliesby_keycode = ITFLIESBY_KEYCODE_RSHIFT; } break;
        case VK_LCONTROL:    { itfliesby_keycode = ITFLIESBY_KEYCODE_LEFT_CONTROL; } break;
        case VK_RCONTROL:    { itfliesby_keycode = ITFLIESBY_KEYCODE_RIGHT_CONTROL; } break;
        case VK_LMENU:       { itfliesby_keycode = ITFLIESBY_KEYCODE_LEFT_MENU; } break;
        case VK_RMENU:       { itfliesby_keycode = ITFLIESBY_KEYCODE_RIGHT_MENU; } break;
        case VK_VOLUME_MUTE: { itfliesby_keycode = ITFLIESBY_KEYCODE_VOLUME_MUTE; } break;
        case VK_VOLUME_DOWN: { itfliesby_keycode = ITFLIESBY_KEYCODE_VOLUME_DOWN; } break;
        case VK_VOLUME_UP:   { itfliesby_keycode = ITFLIESBY_KEYCODE_VOLUME_UP; } break;
        case VK_OEM_PLUS:    { itfliesby_keycode = ITFLIESBY_KEYCODE_PLUS; } break;
        case VK_OEM_COMMA:   { itfliesby_keycode = ITFLIESBY_KEYCODE_COMMA; } break;
        case VK_OEM_MINUS:   { itfliesby_keycode = ITFLIESBY_KEYCODE_MINUS; } break;
        case VK_OEM_PERIOD:  { itfliesby_keycode = ITFLIESBY_KEYCODE_PERIOD; } break;
        case VK_OEM_2:       { itfliesby_keycode = ITFLIESBY_KEYCODE_FORWARD_SLASH_QUESTION; } break;
        case VK_OEM_3:       { itfliesby_keycode = ITFLIESBY_KEYCODE_TILDE; } break;
        case VK_OEM_4:       { itfliesby_keycode = ITFLIESBY_KEYCODE_OPEN_BRACKETS; } break;
        case VK_OEM_5:       { itfliesby_keycode = ITFLIESBY_KEYCODE_BACK_SLASH_PIPE; } break;
        case VK_OEM_6:       { itfliesby_keycode = ITFLIESBY_KEYCODE_CLOSED_BRACKET; } break;
        case VK_OEM_7:       { itfliesby_keycode = ITFLIESBY_KEYCODE_SINGLE_DOUBLE_QUOTE; } break;
        default: break;
    }

    return(itfliesby_keycode);
}
