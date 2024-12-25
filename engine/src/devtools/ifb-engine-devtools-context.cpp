#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_context_render(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

    ifb_engine::devtools_context_render_imgui_demo(devtools_context_flags);
}


inline ifb_void 
ifb_engine::devtools_context_render_context(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

}

inline ifb_void 
ifb_engine::devtools_context_render_system_info(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

}

inline ifb_void 
ifb_engine::devtools_context_render_user_input(
    IFBEngineDevToolsFlagsContext& devtools_context_flags) {

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

