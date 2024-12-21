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
    IFBEngineDevToolsFlags_None         = 0,
    IFBEngineDevToolsFlags_Active       = (1 << 0),
    IFBEngineDevToolsFlags_QuitReceived = (1 << 1)
};

namespace ifb_engine {

    //get flags
    const ifb_b8 devtools_flags_get_active        (IFBEngineDevTools* devtools_ptr);
    const ifb_b8 devtools_flags_get_quit_received (IFBEngineDevTools* devtools_ptr);

    //set flags
    ifb_void devtools_flags_set_active            (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_flags_set_quit_received     (IFBEngineDevTools* devtools_ptr);

    //clear flags
    ifb_void devtools_flags_clear_active          (IFBEngineDevTools* devtools_ptr);
    ifb_void devtools_flags_clear_quit_received   (IFBEngineDevTools* devtools_ptr);
};

/**********************************************************************************/
/* DEVTOOLS                                                                       */
/**********************************************************************************/

struct IFBEngineDevTools {
    IFBEngineDevToolsFlags flags;
};

namespace ifb_engine {

    ifb_void devtools_initialize(IFBEngineDevTools* devtools_ptr);
};

#endif //IFB_ENGINE_INTERNAL_DEVTOOLS_HPP