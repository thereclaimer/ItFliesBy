#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-font-opensans.hpp"
namespace ifb {

    IFB_ENG_FUNC void
    eng_gui_init(
        void) {

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontFromMemoryCompressedBase85TTF(
            ENG_OPENSANS_COMPRESSED_BASE85, 16.0f
        );

        _eng_gui_menu_bar_state.imgui.val  = eng_gui_e32_flag_imgui_none;
        _eng_gui_menu_bar_state.assets.val = eng_gui_e32_flag_assets_none;
    }

    IFB_ENG_FUNC void
    eng_gui_render(
        void) {
 
        eng_gui_main_window();
        eng_gui_imgui();
        eng_gui_asset_config();
    }

    IFB_ENG_FUNC void
    eng_gui_main_window(
        void) {

        constexpr ImGuiWindowFlags main_window_flags        = ImGuiWindowFlags_MenuBar;
        constexpr cchar        main_window_name_cstr [] = "IFB Dev Console";

        if (ImGui::Begin(main_window_name_cstr, NULL, main_window_flags)) {

            if (ImGui::BeginMenuBar()) {

                constexpr cchar cstr_menu_imgui  [] = "ImGui";
                constexpr cchar cstr_menu_assets [] = "Assets";

                if (ImGui::BeginMenu(cstr_menu_imgui)) {

                    constexpr cchar cstr_menu_item_imgui_base_demo [] = "ImGui Base Demo";
                    constexpr cchar cstr_menu_item_imgui_plot_demo [] = "ImGui Plot Demo";

                    bool open_imgui_base_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_base_demo);
                    bool open_imgui_plot_demo = eng_gui_imgui_window_is_open(eng_gui_e32_flag_imgui_plot_demo);
                    eng_gui_imgui_window_reset_all();

                    ImGui::MenuItem(cstr_menu_item_imgui_base_demo, NULL, &open_imgui_base_demo);
                    ImGui::MenuItem(cstr_menu_item_imgui_plot_demo, NULL, &open_imgui_plot_demo);
                    ImGui::EndMenu();
                    
                    if (open_imgui_base_demo) eng_gui_imgui_window_open  (eng_gui_e32_flag_imgui_base_demo);
                    if (open_imgui_plot_demo) eng_gui_imgui_window_open  (eng_gui_e32_flag_imgui_plot_demo);
                }
                
                if (ImGui::BeginMenu(cstr_menu_assets)) {
                    
                    constexpr cchar cstr_menu_assets_open_file     [] = "Open File";                
                    constexpr cchar cstr_menu_item_assets_database [] = "Database";
                    constexpr cchar cstr_menu_item_assets_config   [] = "Config";
                    constexpr cchar cstr_menu_item_assets_text     [] = "Text";
                    constexpr cchar cstr_menu_item_assets_image    [] = "Image";
                    constexpr cchar cstr_menu_item_assets_sound    [] = "sound";
                    constexpr cchar cstr_menu_item_assets_font     [] = "font";

                    bool open_text     = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_open_text);
                    bool open_image    = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_open_image);
                    bool open_sound    = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_open_sound);
                    bool open_font     = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_open_font);
                    bool open_config   = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_config);
                    bool open_database = eng_gui_assets_window_is_open (eng_gui_e32_flag_assets_database);
                    eng_gui_assets_window_reset_all();

                    if (ImGui::BeginMenu(cstr_menu_assets_open_file)) {

                        ImGui::MenuItem(cstr_menu_item_assets_text,  NULL, &open_text);
                        ImGui::MenuItem(cstr_menu_item_assets_image, NULL, &open_image);
                        ImGui::MenuItem(cstr_menu_item_assets_sound, NULL, &open_sound);
                        ImGui::MenuItem(cstr_menu_item_assets_font,  NULL, &open_font);
                        ImGui::EndMenu();
                    }

                    ImGui::MenuItem(cstr_menu_item_assets_config, NULL,   &open_config);
                    ImGui::MenuItem(cstr_menu_item_assets_database, NULL, &open_database);
                    ImGui::EndMenu();

                    if (open_text)     eng_gui_assets_window_open(eng_gui_e32_flag_assets_open_text);
                    if (open_image)    eng_gui_assets_window_open(eng_gui_e32_flag_assets_open_image);
                    if (open_sound)    eng_gui_assets_window_open(eng_gui_e32_flag_assets_open_sound);
                    if (open_font)     eng_gui_assets_window_open(eng_gui_e32_flag_assets_open_font);
                    if (open_config)   eng_gui_assets_window_open(eng_gui_e32_flag_assets_config);
                    if (open_database) eng_gui_assets_window_open(eng_gui_e32_flag_assets_database);
                }
                ImGui::EndMenuBar();
            }
        }
        ImGui::End();
    }
};