#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_initialize(
    IFBEngineDevTools* devtools_ptr) {

    devtools_ptr->flags.control  = IFBEngineDevToolsFlagsControl_None;
    devtools_ptr->flags.context  = IFBEngineDevToolsFlagsContext_None;
    devtools_ptr->flags.memory   = IFBEngineDevToolsFlagsMemory_None;
    devtools_ptr->flags.managers = IFBEngineDevToolsFlagsManagers_None;
}

inline ifb_void 
ifb_engine::devtools_render(
    IFBEngineDevTools* devtools_ptr,
    IFBInput&          input_ref) {

    //check if the devtools are active
    const ifb_b8 devtools_active = ifb_engine::devtools_control_check_active_status(
        devtools_ptr->flags.control,
        input_ref.keyboard);

    //if not, we're done
    if (!devtools_active) return;

    //render the controls
    ifb_engine::devtools_menu_bar_render(devtools_ptr);
    ifb_engine::devtools_window_render_all(devtools_ptr);
    ifb_engine::devtools_tools_render(devtools_ptr->flags.tools);
}
