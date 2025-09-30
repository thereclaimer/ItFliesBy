#pragma once

#include "ifb-engine-gui-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC eng_void
    eng_gui_init(
        eng_void) {

        _eng_gui.imgui_flags.val = eng_gui_e32_flag_imgui_none;
    }

    IFB_ENG_FUNC eng_void
    eng_gui_render(
        eng_void) {

        ImGui::ShowDemoWindow();
    }
};