#pragma once

#include "ifb-engine-internal-devtools.hpp"

inline ifb_void 
ifb_engine::devtools_tools_render(
    IFBEngineDevToolsFlagsTools& tools_flags_ref) {

    ifb_engine::devtools_tools_render_imgui(tools_flags_ref);
}

inline ifb_void 
ifb_engine::devtools_tools_render_imgui(
    IFBEngineDevToolsFlagsTools& tools_flags_ref) {

    bool show_demo = ifb_engine::devtools_tools_flags_get_imgui_demo(tools_flags_ref);
    if (show_demo) {
        ImGui::ShowDemoWindow(&show_demo);
        ifb_engine::devtools_tools_flags_set_imgui_demo(tools_flags_ref, show_demo);
    }
}