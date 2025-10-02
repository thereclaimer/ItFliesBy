#pragma once

#include "ifb-engine-gui-internal.hpp"

namespace ifb {

    IFB_ENG_FUNC eng_void
    eng_gui_imgui(
        eng_void) {

        bool is_open_base_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_base_demo);
        bool is_open_plot_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_plot_demo);

        if (is_open_base_demo) {
            ImGui::ShowDemoWindow(&is_open_base_demo);
        }
        if (is_open_plot_demo) {
            //TODO
        }

        if (!is_open_base_demo) eng_gui_imgui_window_close(eng_gui_e32_flag_imgui_base_demo);
        if (!is_open_plot_demo) eng_gui_imgui_window_close(eng_gui_e32_flag_imgui_plot_demo);
    }
};