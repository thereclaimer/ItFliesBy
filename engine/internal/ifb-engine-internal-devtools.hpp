#ifndef IFB_ENGINE_INTERNAL_DEVTOOLS_HPP
#define IFB_ENGINE_INTERNAL_DEVTOOLS_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineDevTools;

typedef ifb_u32 IFBEngineDevToolsFlags;

/**********************************************************************************/
/* FLAGS                                                                          */
/**********************************************************************************/

enum IFBEngineDevToolsFlags_ {
    IFBEngineDevToolsFlags_None          = 0,
    IFBEngineDevToolsFlags_HotKeyPressed = (1 << 0),
    IFBEngineDevToolsFlags_Active        = (1 << 1),
    IFBEngineDevToolsFlags_QuitReceived  = (1 << 2)
};

namespace ifb_engine {

    //set flags
    inline ifb_void devtools_flags_set_hotkey_pressed     (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags |= IFBEngineDevToolsFlags_HotKeyPressed;   }
    inline ifb_void devtools_flags_set_active             (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags |= IFBEngineDevToolsFlags_Active;       }
    inline ifb_void devtools_flags_set_quit_received      (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags |= IFBEngineDevToolsFlags_QuitReceived; }

    //clear flags
    inline ifb_void devtools_flags_clear_hotkey_pressed   (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags &= ~(IFBEngineDevToolsFlags_HotKeyPressed);   }
    inline ifb_void devtools_flags_clear_active           (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags &= ~(IFBEngineDevToolsFlags_Active);       }
    inline ifb_void devtools_flags_clear_quit_received    (IFBEngineDevToolsFlags& devtools_flags) { devtools_flags &= ~(IFBEngineDevToolsFlags_QuitReceived); }

    //get flags
    inline const ifb_b8 devtools_flags_get_hotkey_pressed (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_HotKeyPressed);   }
    inline const ifb_b8 devtools_flags_get_active         (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_Active);       }
    inline const ifb_b8 devtools_flags_get_quit_received  (const IFBEngineDevToolsFlags devtools_flags) { return(devtools_flags & IFBEngineDevToolsFlags_QuitReceived); }

};

/**********************************************************************************/
/* DEVTOOLS                                                                       */
/**********************************************************************************/

struct IFBEngineDevTools {
    IFBEngineDevToolsFlags flags;
};

namespace ifb_engine {

    ifb_void devtools_initialize (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_update     (IFBEngineDevTools* devtools_ptr, IFBInput& input_ref);
};

#endif //IFB_ENGINE_INTERNAL_DEVTOOLS_HPP