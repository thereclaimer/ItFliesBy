#pragma once

#include "ifb-win32.hpp"

inline const IFBKeyCode 
ifb_win32::user_input_keycode(
    const ifb::u32 win32_keycode) {
        
    IFBKeyCode ifb_keycode = 0;

    switch (win32_keycode) {

        case VK_BACK:        { ifb_keycode = IFBKeyCode_Back;                  } break;
        case VK_TAB:         { ifb_keycode = IFBKeyCode_Tab;                   } break;
        case VK_CLEAR:       { ifb_keycode = IFBKeyCode_Clear;                 } break;
        case VK_RETURN:      { ifb_keycode = IFBKeyCode_Return;                } break;
        case VK_SHIFT:       { ifb_keycode = IFBKeyCode_Shift;                 } break;
        case VK_CONTROL:     { ifb_keycode = IFBKeyCode_Control;               } break;
        case VK_MENU:        { ifb_keycode = IFBKeyCode_Menu;                  } break;
        case VK_PAUSE:       { ifb_keycode = IFBKeyCode_Pause;                 } break;
        case VK_CAPITAL:     { ifb_keycode = IFBKeyCode_Capital;               } break;
        case VK_ESCAPE:      { ifb_keycode = IFBKeyCode_Escape;                } break;
        case VK_SPACE:       { ifb_keycode = IFBKeyCode_Space;                 } break;
        case VK_PRIOR:       { ifb_keycode = IFBKeyCode_Prior;                 } break;
        case VK_NEXT:        { ifb_keycode = IFBKeyCode_Next;                  } break;
        case VK_END:         { ifb_keycode = IFBKeyCode_End;                   } break;
        case VK_HOME:        { ifb_keycode = IFBKeyCode_Home;                  } break;
        case VK_LEFT:        { ifb_keycode = IFBKeyCode_Left;                  } break;
        case VK_UP:          { ifb_keycode = IFBKeyCode_Up;                    } break;
        case VK_RIGHT:       { ifb_keycode = IFBKeyCode_Right;                 } break;
        case VK_DOWN:        { ifb_keycode = IFBKeyCode_Down;                  } break;
        case VK_SELECT:      { ifb_keycode = IFBKeyCode_Select;                } break;
        case VK_PRINT:       { ifb_keycode = IFBKeyCode_Print;                 } break;
        case VK_SNAPSHOT:    { ifb_keycode = IFBKeyCode_Snapshot;              } break;
        case VK_INSERT:      { ifb_keycode = IFBKeyCode_Insert;                } break;
        case VK_DELETE:      { ifb_keycode = IFBKeyCode_Delete;                } break;
        case VK_HELP:        { ifb_keycode = IFBKeyCode_Help;                  } break;
        case 0x30:           { ifb_keycode = IFBKeyCode_0;                     } break;
        case 0x31:           { ifb_keycode = IFBKeyCode_1;                     } break;
        case 0x32:           { ifb_keycode = IFBKeyCode_2;                     } break;
        case 0x33:           { ifb_keycode = IFBKeyCode_3;                     } break;
        case 0x34:           { ifb_keycode = IFBKeyCode_4;                     } break;
        case 0x35:           { ifb_keycode = IFBKeyCode_5;                     } break;
        case 0x36:           { ifb_keycode = IFBKeyCode_6;                     } break;
        case 0x37:           { ifb_keycode = IFBKeyCode_7;                     } break;
        case 0x38:           { ifb_keycode = IFBKeyCode_8;                     } break;
        case 0x39:           { ifb_keycode = IFBKeyCode_9;                     } break;
        case 0x41:           { ifb_keycode = IFBKeyCode_A;                     } break;
        case 0x42:           { ifb_keycode = IFBKeyCode_B;                     } break;
        case 0x43:           { ifb_keycode = IFBKeyCode_C;                     } break;
        case 0x44:           { ifb_keycode = IFBKeyCode_D;                     } break;
        case 0x45:           { ifb_keycode = IFBKeyCode_E;                     } break;
        case 0x46:           { ifb_keycode = IFBKeyCode_F;                     } break;
        case 0x47:           { ifb_keycode = IFBKeyCode_G;                     } break;
        case 0x48:           { ifb_keycode = IFBKeyCode_H;                     } break;
        case 0x49:           { ifb_keycode = IFBKeyCode_I;                     } break;
        case 0x4A:           { ifb_keycode = IFBKeyCode_J;                     } break;
        case 0x4B:           { ifb_keycode = IFBKeyCode_K;                     } break;
        case 0x4C:           { ifb_keycode = IFBKeyCode_L;                     } break;
        case 0x4D:           { ifb_keycode = IFBKeyCode_M;                     } break;
        case 0x4E:           { ifb_keycode = IFBKeyCode_N;                     } break;
        case 0x4F:           { ifb_keycode = IFBKeyCode_O;                     } break;
        case 0x50:           { ifb_keycode = IFBKeyCode_P;                     } break;
        case 0x51:           { ifb_keycode = IFBKeyCode_Q;                     } break;
        case 0x52:           { ifb_keycode = IFBKeyCode_R;                     } break;
        case 0x53:           { ifb_keycode = IFBKeyCode_S;                     } break;
        case 0x54:           { ifb_keycode = IFBKeyCode_T;                     } break;
        case 0x55:           { ifb_keycode = IFBKeyCode_U;                     } break;
        case 0x56:           { ifb_keycode = IFBKeyCode_V;                     } break;
        case 0x57:           { ifb_keycode = IFBKeyCode_W;                     } break;
        case 0x58:           { ifb_keycode = IFBKeyCode_X;                     } break;
        case 0x59:           { ifb_keycode = IFBKeyCode_Y;                     } break;
        case 0x5A:           { ifb_keycode = IFBKeyCode_Z;                     } break;
        case VK_LWIN:        { ifb_keycode = IFBKeyCode_WinLeft;               } break;
        case VK_RWIN:        { ifb_keycode = IFBKeyCode_WinRight;              } break;
        case VK_APPS:        { ifb_keycode = IFBKeyCode_Apps;                  } break;
        case VK_NUMPAD0:     { ifb_keycode = IFBKeyCode_Numpad0;               } break;
        case VK_NUMPAD1:     { ifb_keycode = IFBKeyCode_Numpad1;               } break;
        case VK_NUMPAD2:     { ifb_keycode = IFBKeyCode_Numpad2;               } break;
        case VK_NUMPAD3:     { ifb_keycode = IFBKeyCode_Numpad3;               } break;
        case VK_NUMPAD4:     { ifb_keycode = IFBKeyCode_Numpad4;               } break;
        case VK_NUMPAD5:     { ifb_keycode = IFBKeyCode_Numpad5;               } break;
        case VK_NUMPAD6:     { ifb_keycode = IFBKeyCode_Numpad6;               } break;
        case VK_NUMPAD7:     { ifb_keycode = IFBKeyCode_Numpad7;               } break;
        case VK_NUMPAD8:     { ifb_keycode = IFBKeyCode_Numpad8;               } break;
        case VK_NUMPAD9:     { ifb_keycode = IFBKeyCode_Numpad9;               } break;
        case VK_MULTIPLY:    { ifb_keycode = IFBKeyCode_Multiply;              } break;
        case VK_ADD:         { ifb_keycode = IFBKeyCode_Add;                   } break;
        case VK_SEPARATOR:   { ifb_keycode = IFBKeyCode_Separator;             } break;
        case VK_SUBTRACT:    { ifb_keycode = IFBKeyCode_Subtract;              } break;
        case VK_DECIMAL:     { ifb_keycode = IFBKeyCode_Decimal;               } break;
        case VK_DIVIDE:      { ifb_keycode = IFBKeyCode_Divide;                } break;
        case VK_F1:          { ifb_keycode = IFBKeyCode_F1;                    } break;
        case VK_F2:          { ifb_keycode = IFBKeyCode_F2;                    } break;
        case VK_F3:          { ifb_keycode = IFBKeyCode_F3;                    } break;
        case VK_F4:          { ifb_keycode = IFBKeyCode_F4;                    } break;
        case VK_F5:          { ifb_keycode = IFBKeyCode_F5;                    } break;
        case VK_F6:          { ifb_keycode = IFBKeyCode_F6;                    } break;
        case VK_F7:          { ifb_keycode = IFBKeyCode_F7;                    } break;
        case VK_F8:          { ifb_keycode = IFBKeyCode_F8;                    } break;
        case VK_F9:          { ifb_keycode = IFBKeyCode_F9;                    } break;
        case VK_F10:         { ifb_keycode = IFBKeyCode_F10;                   } break;
        case VK_F11:         { ifb_keycode = IFBKeyCode_F11;                   } break;
        case VK_F12:         { ifb_keycode = IFBKeyCode_F12;                   } break;
        case VK_NUMLOCK:     { ifb_keycode = IFBKeyCode_Numlock;               } break;
        case VK_LSHIFT:      { ifb_keycode = IFBKeyCode_ShiftLeft;             } break;
        case VK_RSHIFT:      { ifb_keycode = IFBKeyCode_ShiftRight;            } break;
        case VK_LCONTROL:    { ifb_keycode = IFBKeyCode_ControlLeft;           } break;
        case VK_RCONTROL:    { ifb_keycode = IFBKeyCode_ControlRight;          } break;
        case VK_LMENU:       { ifb_keycode = IFBKeyCode_MenuLeft;              } break;
        case VK_RMENU:       { ifb_keycode = IFBKeyCode_MenuRight;             } break;
        case VK_VOLUME_MUTE: { ifb_keycode = IFBKeyCode_VolumeMute;            } break;
        case VK_VOLUME_DOWN: { ifb_keycode = IFBKeyCode_VolumeDown;            } break;
        case VK_VOLUME_UP:   { ifb_keycode = IFBKeyCode_VolumeUp;              } break;
        case VK_OEM_PLUS:    { ifb_keycode = IFBKeyCode_Plus;                  } break;
        case VK_OEM_COMMA:   { ifb_keycode = IFBKeyCode_Comma;                 } break;
        case VK_OEM_MINUS:   { ifb_keycode = IFBKeyCode_Minus;                 } break;
        case VK_OEM_PERIOD:  { ifb_keycode = IFBKeyCode_Period;                } break;
        case VK_OEM_2:       { ifb_keycode = IFBKeyCode_SlashForward_Question; } break;
        case VK_OEM_3:       { ifb_keycode = IFBKeyCode_Tilde;                 } break;
        case VK_OEM_4:       { ifb_keycode = IFBKeyCode_BracketOpen;           } break;
        case VK_OEM_5:       { ifb_keycode = IFBKeyCode_SlashBack_Pipe;        } break;
        case VK_OEM_6:       { ifb_keycode = IFBKeyCode_BracketClose;          } break;
        case VK_OEM_7:       { ifb_keycode = IFBKeyCode_Quote;                 } break;
        default: break;
    }

    return(ifb_keycode);
}