#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void
ifb_engine::devtools_window_render_all(
    IFBEngineDevTools* devtools_ptr) {

    const ifb_u32 window_count = 2;
    
    ifb_u32 window_flags[window_count] = {
        devtools_ptr->flags.context,
        devtools_ptr->flags.memory
    };

    const ifb_char* window_titles[window_count] = {
        IFB_ENGINE_DEVTOOLS_WINDOW_NAME_ENGINE_CONTEXT,
        IFB_ENGINE_DEVTOOLS_WINDOW_NAME_MEMORY
    };

    const funcptr_devtools_window_render_callback window_callbacks[window_count] = {
        ifb_engine::devtools_window_render_callback_context,
        ifb_engine::devtools_window_render_callback_memory
    };

    for (
        ifb_u32 window_index = 0;
        window_index < window_count;
        ++window_index) {

        ifb_engine::devtools_window_render(
            window_flags    [window_index],
            window_titles   [window_index],
            window_callbacks[window_index]);
    }

    devtools_ptr->flags.context = window_flags[0];
    devtools_ptr->flags.memory  = window_flags[1];
}

inline ifb_void
ifb_engine::devtools_window_render(
          ifb_u32&                                 window_flags_ref,
    const ifb_char*                                window_title,
    const funcptr_devtools_window_render_callback  window_callback) {

    //sanity check
    ifb_macro_assert(window_title);
    ifb_macro_assert(window_callback);    

    bool window_enabled = false;

    //render the window if its enabled
    window_enabled = window_flags_ref > 0;
    if (!window_enabled || !ImGui::Begin(window_title,&window_enabled)) {
        return;
    }

    //render the window data
    window_callback(window_flags_ref);

    //clear the flags if the window was closed
    if (!window_enabled) {
        window_flags_ref = 0;
    }

    //window end
    ImGui::End();
}

inline ifb_void 
ifb_engine::devtools_window_render_callback_context(
    IFBEngineDevToolsFlagsContext& flags_ref_context) {

    IFBEngineContext& engine_context = ifb_engine::context();

    ifb_engine::devtools_tab_bar_render_context(
        flags_ref_context,
        &engine_context);    
}

inline ifb_void 
ifb_engine::devtools_window_render_callback_memory(
    IFBEngineDevToolsFlagsMemory&  flags_ref_memory) {

    //get the memory reference
    IFBEngineMemory* context_memory_ptr = ifb_engine::context_get_memory();

    //render the tab bar
    ifb_engine::devtools_tab_bar_render_memory(
        flags_ref_memory,
        context_memory_ptr);
}