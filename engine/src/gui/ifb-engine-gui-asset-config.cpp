#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr eng_cchar label_text_cstr  [] = "Text";
    constexpr eng_cchar label_image_cstr [] = "Images";
    constexpr eng_cchar label_sound_cstr [] = "Sounds";
    constexpr eng_cchar label_font_cstr  [] = "Fonts";


    static eng_asset_config_t* _asset_config;

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config(
        eng_void) {

        constexpr eng_cchar window_name_cstr[] = "Asset Config";
        bool is_open = eng_gui_assets_window_is_open(eng_gui_e32_flag_assets_config);

        if (is_open) {
            if (ImGui::Begin(window_name_cstr, &is_open)) {

                eng_gui_asset_config_text  ();
                eng_gui_asset_config_image ();
                eng_gui_asset_config_sound ();
                eng_gui_asset_config_font  ();
            }
            ImGui::End();
        }

        if (!is_open) {

            eng_gui_assets_window_close(eng_gui_e32_flag_assets_config);
        }
    }

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config_text(
        eng_void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(label_text_cstr)) {

        }
    }

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config_image(
        eng_void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(label_image_cstr)) {

        }
    }

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config_sound(
        eng_void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(label_sound_cstr)) {

        }
    }

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config_font(
        eng_void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(label_font_cstr)) {

        }
    }

};