#ifndef ITFLIESBY_USER_INPUT_HPP
#define ITFLIESBY_USER_INPUT_HPP

#include "itfliesby-types.hpp"

#define ITFLIESBY_KEYCODE_GROUPS                14
#define ITFLIESBY_KEYCODE_GROUP_SIZE             8

//keycode group 0
#define ITFLIESBY_KEYCODE_BACK                   0 
#define ITFLIESBY_KEYCODE_TAB                    1 
#define ITFLIESBY_KEYCODE_CLEAR                  2 
#define ITFLIESBY_KEYCODE_RETURN                 3 
#define ITFLIESBY_KEYCODE_SHIFT                  4 
#define ITFLIESBY_KEYCODE_CONTROL                5 
#define ITFLIESBY_KEYCODE_MENU                   6 
#define ITFLIESBY_KEYCODE_PAUSE                  7 

//keycode group 1
#define ITFLIESBY_KEYCODE_CAPITAL                8 
#define ITFLIESBY_KEYCODE_ESCAPE                 9 
#define ITFLIESBY_KEYCODE_SPACE                  10 
#define ITFLIESBY_KEYCODE_PRIOR                  11 
#define ITFLIESBY_KEYCODE_NEXT                   12 
#define ITFLIESBY_KEYCODE_END                    13 
#define ITFLIESBY_KEYCODE_HOME                   14 
#define ITFLIESBY_KEYCODE_LEFT                   15 

//keycode group 2
#define ITFLIESBY_KEYCODE_UP                     16 
#define ITFLIESBY_KEYCODE_RIGHT                  17 
#define ITFLIESBY_KEYCODE_DOWN                   18 
#define ITFLIESBY_KEYCODE_SELECT                 19 
#define ITFLIESBY_KEYCODE_PRINT                  20 
#define ITFLIESBY_KEYCODE_SNAPSHOT               21 
#define ITFLIESBY_KEYCODE_INSERT                 22 
#define ITFLIESBY_KEYCODE_DELETE                 23 

//keycode group 3
#define ITFLIESBY_KEYCODE_HELP                   24 
#define ITFLIESBY_KEYCODE_0                      25 
#define ITFLIESBY_KEYCODE_1                      26 
#define ITFLIESBY_KEYCODE_2                      27 
#define ITFLIESBY_KEYCODE_3                      28 
#define ITFLIESBY_KEYCODE_4                      29 
#define ITFLIESBY_KEYCODE_5                      30 
#define ITFLIESBY_KEYCODE_6                      31 

//keycode group 4
#define ITFLIESBY_KEYCODE_7                      32 
#define ITFLIESBY_KEYCODE_8                      33 
#define ITFLIESBY_KEYCODE_9                      34 
#define ITFLIESBY_KEYCODE_A                      35 
#define ITFLIESBY_KEYCODE_B                      36 
#define ITFLIESBY_KEYCODE_C                      37 
#define ITFLIESBY_KEYCODE_D                      38 
#define ITFLIESBY_KEYCODE_E                      39 

//keycode group 5
#define ITFLIESBY_KEYCODE_F                      40 
#define ITFLIESBY_KEYCODE_G                      41 
#define ITFLIESBY_KEYCODE_H                      42 
#define ITFLIESBY_KEYCODE_I                      43 
#define ITFLIESBY_KEYCODE_J                      44 
#define ITFLIESBY_KEYCODE_K                      45 
#define ITFLIESBY_KEYCODE_L                      46 
#define ITFLIESBY_KEYCODE_M                      47 

//keycode group 6
#define ITFLIESBY_KEYCODE_N                      48 
#define ITFLIESBY_KEYCODE_O                      49 
#define ITFLIESBY_KEYCODE_P                      50 
#define ITFLIESBY_KEYCODE_Q                      51 
#define ITFLIESBY_KEYCODE_R                      52 
#define ITFLIESBY_KEYCODE_S                      53 
#define ITFLIESBY_KEYCODE_T                      54 
#define ITFLIESBY_KEYCODE_U                      55 

//keycode group 7
#define ITFLIESBY_KEYCODE_V                      56 
#define ITFLIESBY_KEYCODE_W                      57 
#define ITFLIESBY_KEYCODE_X                      58 
#define ITFLIESBY_KEYCODE_Y                      59 
#define ITFLIESBY_KEYCODE_Z                      60 
#define ITFLIESBY_KEYCODE_LEFT_WIN               61 
#define ITFLIESBY_KEYCODE_RIGHT_WIN              62 
#define ITFLIESBY_KEYCODE_APPS                   63 

//keycode group 8
#define ITFLIESBY_KEYCODE_NUMPAD_0               64 
#define ITFLIESBY_KEYCODE_NUMPAD_1               65 
#define ITFLIESBY_KEYCODE_NUMPAD_2               66 
#define ITFLIESBY_KEYCODE_NUMPAD_3               67 
#define ITFLIESBY_KEYCODE_NUMPAD_4               68 
#define ITFLIESBY_KEYCODE_NUMPAD_5               69 
#define ITFLIESBY_KEYCODE_NUMPAD_6               70 
#define ITFLIESBY_KEYCODE_NUMPAD_7               71 

//keycode group 9
#define ITFLIESBY_KEYCODE_NUMPAD_8               72 
#define ITFLIESBY_KEYCODE_NUMPAD_9               73 
#define ITFLIESBY_KEYCODE_MULTIPLY               74 
#define ITFLIESBY_KEYCODE_ADD                    75 
#define ITFLIESBY_KEYCODE_SEPARATOR              76 
#define ITFLIESBY_KEYCODE_SUBTRACT               77 
#define ITFLIESBY_KEYCODE_DECIMAL                78 
#define ITFLIESBY_KEYCODE_DIVIDE                 79 

//keycode group 10
#define ITFLIESBY_KEYCODE_F1                     80 
#define ITFLIESBY_KEYCODE_F2                     81 
#define ITFLIESBY_KEYCODE_F3                     82 
#define ITFLIESBY_KEYCODE_F4                     83 
#define ITFLIESBY_KEYCODE_F5                     84 
#define ITFLIESBY_KEYCODE_F6                     85 
#define ITFLIESBY_KEYCODE_F7                     86 
#define ITFLIESBY_KEYCODE_F8                     87 

//keycode group 11
#define ITFLIESBY_KEYCODE_F9                     88 
#define ITFLIESBY_KEYCODE_F10                    89 
#define ITFLIESBY_KEYCODE_F11                    90 
#define ITFLIESBY_KEYCODE_F12                    91 
#define ITFLIESBY_KEYCODE_NUMLOCK                92 
#define ITFLIESBY_KEYCODE_LSHIFT                 93 
#define ITFLIESBY_KEYCODE_RSHIFT                 94 
#define ITFLIESBY_KEYCODE_LEFT_CONTROL           95 

//keycode group 12
#define ITFLIESBY_KEYCODE_RIGHT_CONTROL          96 
#define ITFLIESBY_KEYCODE_LEFT_MENU              97 
#define ITFLIESBY_KEYCODE_RIGHT_MENU             98 
#define ITFLIESBY_KEYCODE_VOLUME_MUTE            99 
#define ITFLIESBY_KEYCODE_VOLUME_DOWN            100 
#define ITFLIESBY_KEYCODE_VOLUME_UP              101 
#define ITFLIESBY_KEYCODE_PLUS                   102 
#define ITFLIESBY_KEYCODE_COMMA                  103 

//keycode group 13
#define ITFLIESBY_KEYCODE_MINUS                  104 
#define ITFLIESBY_KEYCODE_PERIOD                 105 
#define ITFLIESBY_KEYCODE_FORWARD_SLASH_QUESTION 106 
#define ITFLIESBY_KEYCODE_TILDE                  107 
#define ITFLIESBY_KEYCODE_OPEN_BRACKETS          108 
#define ITFLIESBY_KEYCODE_BACK_SLASH_PIPE        109 
#define ITFLIESBY_KEYCODE_CLOSED_BRACKET         110 
#define ITFLIESBY_KEYCODE_SINGLE_DOUBLE_QUOTE    111 

#define ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_UP      0
#define ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_DOWN    1 
#define ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_LEFT    2
#define ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_RIGHT   3
#define ITFLIESBY_GAMEPAD_BUTTONCODE_START        4
#define ITFLIESBY_GAMEPAD_BUTTONCODE_SELECT       5
#define ITFLIESBY_GAMEPAD_BUTTONCODE_STICK_LEFT   6
#define ITFLIESBY_GAMEPAD_BUTTONCODE_STICK_RIGHT  7
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BUMPER_LEFT  8
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BUMPER_RIGHT 9
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_A       12
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_B       13 
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_X       14
#define ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_Y       15

#define itfliesby_gamepad_button_state_dpad_up(user_input)      user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_UP) 
#define itfliesby_gamepad_button_state_dpad_down(user_input)    user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_DOWN) 
#define itfliesby_gamepad_button_state_dpad_left(user_input)    user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_LEFT) 
#define itfliesby_gamepad_button_state_dpad_right(user_input)   user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_DPAD_RIGHT) 
#define itfliesby_gamepad_button_state_start(user_input)        user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_START) 
#define itfliesby_gamepad_button_state_select(user_input)       user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_SELECT) 
#define itfliesby_gamepad_button_state_stick_left(user_input)   user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_STICK_LEFT) 
#define itfliesby_gamepad_button_state_stick_right(user_input)  user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_STICK_RIGHT) 
#define itfliesby_gamepad_button_state_bumper_left(user_input)  user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BUMPER_LEFT) 
#define itfliesby_gamepad_button_state_bumper_right(user_input) user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BUMPER_RIGHT) 
#define itfliesby_gamepad_button_state_bpad_a(user_input)       user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_A) 
#define itfliesby_gamepad_button_state_bpad_b(user_input)       user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_B) 
#define itfliesby_gamepad_button_state_bpad_x(user_input)       user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_X) 
#define itfliesby_gamepad_button_state_bpad_y(user_input)       user_input.game_pad != NULL && itfliesby_gamepad_button_state(user_input.game_pad->buttons, ITFLIESBY_GAMEPAD_BUTTONCODE_BPAD_Y) 

struct ItfliesbyGamepadInput {
    f32 trigger_right;
    f32 trigger_left;
    u16 buttons;
    f32 stick_right_x;
    f32 stick_right_y;
    f32 stick_left_x;
    f32 stick_left_y;
};

struct ItfliesbyUserInput {
    b8  mouse_button_left;
    b8  mouse_button_right;
    s32 mouse_x_current;
    s32 mouse_y_current;
    s32 mouse_x_delta;
    s32 mouse_y_delta;
    s32 mouse_wheel;
    //there are 112 keycodes, so if every keycode is represented by
    //a bit, we can store the data in a contiguous space created by
    //14 bytes
    u8 keycodes[ITFLIESBY_KEYCODE_GROUPS];
    ItfliesbyGamepadInput* game_pad;
};
typedef ItfliesbyUserInput user_input;

#define KEY_UP    1
#define KEY_DOWN -1

#define itfliesby_gamepad_button_state(buttons, button_code) ((buttons >> button_code) & 1) 

#define USER_INPUT_KEY_STATE(val_user_input, val_keycode) (val_user_input.keycodes[(val_keycode/ITFLIESBY_KEYCODE_GROUP_SIZE)] >> ((val_keycode % ITFLIESBY_KEYCODE_GROUP_SIZE)) & 1)
#define USER_INPUT_SET_KEY(val_user_input, val_keycode)   (val_user_input.keycodes[(val_keycode/ITFLIESBY_KEYCODE_GROUP_SIZE)] |= (1 << (val_keycode % ITFLIESBY_KEYCODE_GROUP_SIZE)))
#define USER_INPUT_CLEAR_KEY(val_user_input, val_keycode) (val_user_input.keycodes[(val_keycode/ITFLIESBY_KEYCODE_GROUP_SIZE)] &= ~(1 << (val_keycode % ITFLIESBY_KEYCODE_GROUP_SIZE)))

#define ITFLIESBY_KEYCODE_STATE_BACK(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_BACK)                   
#define ITFLIESBY_KEYCODE_STATE_TAB(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_TAB)                    
#define ITFLIESBY_KEYCODE_STATE_CLEAR(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_CLEAR)                  
#define ITFLIESBY_KEYCODE_STATE_RETURN(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RETURN)                 
#define ITFLIESBY_KEYCODE_STATE_SHIFT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SHIFT)                  
#define ITFLIESBY_KEYCODE_STATE_CONTROL(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_CONTROL)                
#define ITFLIESBY_KEYCODE_STATE_MENU(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_MENU)                   
#define ITFLIESBY_KEYCODE_STATE_PAUSE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_PAUSE)                  
#define ITFLIESBY_KEYCODE_STATE_CAPITAL(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_CAPITAL)                
#define ITFLIESBY_KEYCODE_STATE_ESCAPE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_ESCAPE)                 
#define ITFLIESBY_KEYCODE_STATE_SPACE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SPACE)                  
#define ITFLIESBY_KEYCODE_STATE_PRIOR(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_PRIOR)                  
#define ITFLIESBY_KEYCODE_STATE_NEXT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NEXT)                   
#define ITFLIESBY_KEYCODE_STATE_END(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_END)                    
#define ITFLIESBY_KEYCODE_STATE_HOME(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_HOME)                   
#define ITFLIESBY_KEYCODE_STATE_LEFT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_LEFT)                   
#define ITFLIESBY_KEYCODE_STATE_UP(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_UP)                     
#define ITFLIESBY_KEYCODE_STATE_RIGHT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RIGHT)                  
#define ITFLIESBY_KEYCODE_STATE_DOWN(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_DOWN)                   
#define ITFLIESBY_KEYCODE_STATE_SELECT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SELECT)                 
#define ITFLIESBY_KEYCODE_STATE_PRINT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_PRINT)                  
#define ITFLIESBY_KEYCODE_STATE_SNAPSHOT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SNAPSHOT)               
#define ITFLIESBY_KEYCODE_STATE_INSERT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_INSERT)                 
#define ITFLIESBY_KEYCODE_STATE_DELETE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_DELETE)                 
#define ITFLIESBY_KEYCODE_STATE_HELP(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_HELP)                   
#define ITFLIESBY_KEYCODE_STATE_0(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_0)                      
#define ITFLIESBY_KEYCODE_STATE_1(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_1)                      
#define ITFLIESBY_KEYCODE_STATE_2(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_2)                      
#define ITFLIESBY_KEYCODE_STATE_3(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_3)                      
#define ITFLIESBY_KEYCODE_STATE_4(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_4)                      
#define ITFLIESBY_KEYCODE_STATE_5(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_5)                      
#define ITFLIESBY_KEYCODE_STATE_6(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_6)                      
#define ITFLIESBY_KEYCODE_STATE_7(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_7)                      
#define ITFLIESBY_KEYCODE_STATE_8(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_8)                      
#define ITFLIESBY_KEYCODE_STATE_9(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_9)                      
#define ITFLIESBY_KEYCODE_STATE_A(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_A)                      
#define ITFLIESBY_KEYCODE_STATE_B(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_B)                      
#define ITFLIESBY_KEYCODE_STATE_C(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_C)                      
#define ITFLIESBY_KEYCODE_STATE_D(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_D)                      
#define ITFLIESBY_KEYCODE_STATE_E(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_E)                      
#define ITFLIESBY_KEYCODE_STATE_F(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F)                      
#define ITFLIESBY_KEYCODE_STATE_G(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_G)                      
#define ITFLIESBY_KEYCODE_STATE_H(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_H)                      
#define ITFLIESBY_KEYCODE_STATE_I(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_I)                      
#define ITFLIESBY_KEYCODE_STATE_J(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_J)                      
#define ITFLIESBY_KEYCODE_STATE_K(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_K)                      
#define ITFLIESBY_KEYCODE_STATE_L(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_L)                      
#define ITFLIESBY_KEYCODE_STATE_M(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_M)                      
#define ITFLIESBY_KEYCODE_STATE_N(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_N)                      
#define ITFLIESBY_KEYCODE_STATE_O(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_O)                      
#define ITFLIESBY_KEYCODE_STATE_P(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_P)                      
#define ITFLIESBY_KEYCODE_STATE_Q(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_Q)                      
#define ITFLIESBY_KEYCODE_STATE_R(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_R)                      
#define ITFLIESBY_KEYCODE_STATE_S(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_S)                      
#define ITFLIESBY_KEYCODE_STATE_T(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_T)                      
#define ITFLIESBY_KEYCODE_STATE_U(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_U)                      
#define ITFLIESBY_KEYCODE_STATE_V(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_V)                      
#define ITFLIESBY_KEYCODE_STATE_W(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_W)                      
#define ITFLIESBY_KEYCODE_STATE_X(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_X)                      
#define ITFLIESBY_KEYCODE_STATE_Y(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_Y)                      
#define ITFLIESBY_KEYCODE_STATE_Z(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_Z)                      
#define ITFLIESBY_KEYCODE_STATE_LEFT_WIN(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_LEFT_WIN)               
#define ITFLIESBY_KEYCODE_STATE_RIGHT_WIN(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RIGHT_WIN)              
#define ITFLIESBY_KEYCODE_STATE_APPS(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_APPS)                   
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_0(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_0)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_1(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_1)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_2(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_2)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_3(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_3)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_4(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_4)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_5(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_5)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_6(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_6)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_7(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_7)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_8(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_8)               
#define ITFLIESBY_KEYCODE_STATE_NUMPAD_9(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMPAD_9)               
#define ITFLIESBY_KEYCODE_STATE_MULTIPLY(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_MULTIPLY)               
#define ITFLIESBY_KEYCODE_STATE_ADD(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_ADD)                    
#define ITFLIESBY_KEYCODE_STATE_SEPARATOR(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SEPARATOR)              
#define ITFLIESBY_KEYCODE_STATE_SUBTRACT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SUBTRACT)               
#define ITFLIESBY_KEYCODE_STATE_DECIMAL(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_DECIMAL)                
#define ITFLIESBY_KEYCODE_STATE_DIVIDE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_DIVIDE)                 
#define ITFLIESBY_KEYCODE_STATE_F1(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F1)                     
#define ITFLIESBY_KEYCODE_STATE_F2(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F2)                     
#define ITFLIESBY_KEYCODE_STATE_F3(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F3)                     
#define ITFLIESBY_KEYCODE_STATE_F4(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F4)                     
#define ITFLIESBY_KEYCODE_STATE_F5(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F5)                     
#define ITFLIESBY_KEYCODE_STATE_F6(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F6)                     
#define ITFLIESBY_KEYCODE_STATE_F7(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F7)                     
#define ITFLIESBY_KEYCODE_STATE_F8(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F8)                     
#define ITFLIESBY_KEYCODE_STATE_F9(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F9)                     
#define ITFLIESBY_KEYCODE_STATE_F10(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F10)                    
#define ITFLIESBY_KEYCODE_STATE_F11(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F11)                    
#define ITFLIESBY_KEYCODE_STATE_F12(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_F12)                    
#define ITFLIESBY_KEYCODE_STATE_NUMLOCK(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_NUMLOCK)                
#define ITFLIESBY_KEYCODE_STATE_LSHIFT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_LSHIFT)                 
#define ITFLIESBY_KEYCODE_STATE_RSHIFT(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RSHIFT)                 
#define ITFLIESBY_KEYCODE_STATE_LEFT_CONTROL(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_LEFT_CONTROL)           
#define ITFLIESBY_KEYCODE_STATE_RIGHT_CONTROL(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RIGHT_CONTROL)          
#define ITFLIESBY_KEYCODE_STATE_LEFT_MENU(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_LEFT_MENU)              
#define ITFLIESBY_KEYCODE_STATE_RIGHT_MENU(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_RIGHT_MENU)             
#define ITFLIESBY_KEYCODE_STATE_VOLUME_MUTE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_VOLUME_MUTE)            
#define ITFLIESBY_KEYCODE_STATE_VOLUME_DOWN(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_VOLUME_DOWN)            
#define ITFLIESBY_KEYCODE_STATE_VOLUME_UP(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_VOLUME_UP)              
#define ITFLIESBY_KEYCODE_STATE_PLUS(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_PLUS)                   
#define ITFLIESBY_KEYCODE_STATE_COMMA(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_COMMA)                  
#define ITFLIESBY_KEYCODE_STATE_MINUS(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_MINUS)                  
#define ITFLIESBY_KEYCODE_STATE_PERIOD(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_PERIOD)                 
#define ITFLIESBY_KEYCODE_STATE_FORWARD_SLASH_QUESTION(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_FORWARD_SLASH_QUESTION) 
#define ITFLIESBY_KEYCODE_STATE_TILDE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_TILDE)                  
#define ITFLIESBY_KEYCODE_STATE_OPEN_BRACKETS(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_OPEN_BRACKETS)          
#define ITFLIESBY_KEYCODE_STATE_BACK_SLASH_PIPE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_BACK_SLASH_PIPE)        
#define ITFLIESBY_KEYCODE_STATE_CLOSED_BRACKET(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_CLOSED_BRACKET)         
#define ITFLIESBY_KEYCODE_STATE_SINGLE_DOUBLE_QUOTE(user_input) USER_INPUT_KEY_STATE(user_input,ITFLIESBY_KEYCODE_SINGLE_DOUBLE_QUOTE)    



#endif //ITFLIESBY_USER_INPUT_HPP