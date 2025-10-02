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

        _eng_gui_menu_bar_state.imgui.val = eng_gui_e32_flag_imgui_none;
    }

    IFB_ENG_FUNC eng_void
    eng_gui_render(
        eng_void) {
 
        eng_gui_main_window();
        eng_gui_imgui();
    }

    IFB_ENG_FUNC eng_void
    eng_gui_main_window(
        eng_void) {

        constexpr ImGuiWindowFlags main_window_flags        = ImGuiWindowFlags_MenuBar;
        constexpr eng_cchar        main_window_name_cstr [] = "IFB Dev Console";

        if (ImGui::Begin(main_window_name_cstr, NULL, main_window_flags)) {

            if (ImGui::BeginMenuBar()) {

                constexpr eng_cchar cstr_menu_imgui [] = "ImGui";

                if (ImGui::BeginMenu(cstr_menu_imgui)) {

                    constexpr eng_cchar cstr_menu_item_imgui_base_demo [] = "ImGui Base Demo";
                    constexpr eng_cchar cstr_menu_item_imgui_plot_demo [] = "ImGui Plot Demo";

                    bool open_imgui_base_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_base_demo);
                    bool open_imgui_plot_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_plot_demo);
                    eng_gui_imgui_window_close(eng_gui_e32_flag_imgui_base_demo);
                    eng_gui_imgui_window_close(eng_gui_e32_flag_imgui_plot_demo);

                    ImGui::MenuItem(cstr_menu_item_imgui_base_demo, NULL, &open_imgui_base_demo);
                    ImGui::MenuItem(cstr_menu_item_imgui_plot_demo, NULL, &open_imgui_plot_demo);
                    
                    if (open_imgui_base_demo) eng_gui_imgui_window_open  (eng_gui_e32_flag_imgui_base_demo);
                    if (open_imgui_plot_demo) eng_gui_imgui_window_open  (eng_gui_e32_flag_imgui_plot_demo);

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
        }
        ImGui::End();
    }
};