#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_context_render_window(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

    ifb_engine::devtools_context_render_imgui_demo(devtools_context_flags);
}

inline ifb_void 
ifb_engine::devtools_context_render_tab_bar(
    IFBEngineDevToolsFlagsContext& devtools_context_flags, 
    IFBEngineContext*              engine_context) {

}


inline ifb_void 
ifb_engine::devtools_context_render_tab_data_context(
    IFBEngineContext* engine_context) {

} 

inline ifb_void 
ifb_engine::devtools_context_render_tab_data_system_info(
    IFBEngineContext* engine_context) {

}

inline ifb_void 
ifb_engine::devtools_context_render_tab_data_user_input(
    IFBEngineContext* engine_context) {

}

inline ifb_void 
ifb_engine::devtools_context_render_imgui_demo(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

    bool show_demo = ifb_engine::devtools_context_flags_get_imgui_demo(devtools_context_flags);
    if (show_demo) {
        ImGui::ShowDemoWindow(&show_demo);
        ifb_engine::devtools_context_flags_set_imgui_demo(devtools_context_flags, show_demo);
    }
}

