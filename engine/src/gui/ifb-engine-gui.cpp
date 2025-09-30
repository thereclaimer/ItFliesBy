#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-font-opensans.hpp"
namespace ifb {

    IFB_ENG_FUNC eng_void
    eng_gui_init(
        eng_void) {

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            ENG_OPENSANS_COMPRESSED_BASE85, 16.0f
        );

        _eng_gui.imgui_flags.val = eng_gui_e32_flag_imgui_none;
    }

    IFB_ENG_FUNC eng_void
    eng_gui_render(
        eng_void) {

        ImGui::ShowDemoWindow();
    }
};