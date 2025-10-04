#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr cchar CSTR_HEADER_LABEL_TEXT                     [] = "Text";
    constexpr cchar CSTR_HEADER_LABEL_IMAGE                    [] = "Images";
    constexpr cchar CSTR_HEADER_LABEL_SOUND                    [] = "Sounds";
    constexpr cchar CSTR_HEADER_LABEL_FONT                     [] = "Fonts";
    constexpr cchar CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT     [] = "Config File:";
    constexpr cchar CSTR_PATH_INPUT_CONFIG_FILE_INPUT_NAME     [] = "##config-input-path";
    constexpr cchar CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT [] = "Asset Directory:";
    constexpr cchar CSTR_PATH_INPUT_ASSET_DIR_INPUT_NAME       [] = "##config-input-asset-dir";
    constexpr cchar CSTR_INPUT_LABEL_BUTTON [] = "Submit";
    constexpr u32   SIZE_INPUT_TEXT            = 128;
    
    IFB_ENG_FUNC void
    eng_gui_asset_config(
        void) {

        constexpr cchar window_name_cstr[] = "Asset Config";
        bool is_open = eng_gui_assets_window_is_open(eng_gui_e32_flag_assets_config);

        if (is_open) {
            if (ImGui::Begin(window_name_cstr, &is_open)) {

                eng_gui_asset_config_path_input ();
                eng_gui_asset_config_text       ();
                eng_gui_asset_config_image      ();
                eng_gui_asset_config_sound      ();
                eng_gui_asset_config_font       ();
            }
            ImGui::End();
        }

        if (!is_open) {
            eng_gui_assets_window_close(eng_gui_e32_flag_assets_config);
        }
    }

    IFB_ENG_FUNC void
    eng_gui_asset_config_path_input(
        void) {

        constexpr u32 path_input_file            = 0; 
        constexpr u32 path_input_asset_directory = 1; 
        constexpr u32 path_input_count           = 2; 

        static eng_gui_text_input_t path_text_input_array [path_input_count];
        static cchar                path_buffer_file      [SIZE_INPUT_TEXT];
        static cchar                path_buffer_asset_dir [SIZE_INPUT_TEXT];
        static cstr_t               path_cstr_file;
        static cstr_t               path_cstr_asset_dir;

        path_text_input_array[path_input_file].label_button                = CSTR_INPUT_LABEL_BUTTON;
        path_text_input_array[path_input_file].label_text_box              = CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT;
        path_text_input_array[path_input_file].input_name                  = CSTR_PATH_INPUT_CONFIG_FILE_INPUT_NAME; 
        path_text_input_array[path_input_file].input_cstr.chars            = path_buffer_file;
        path_text_input_array[path_input_file].input_cstr.size             = SIZE_INPUT_TEXT;

        path_text_input_array[path_input_asset_directory].label_button     = CSTR_INPUT_LABEL_BUTTON;
        path_text_input_array[path_input_asset_directory].label_text_box   = CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT;
        path_text_input_array[path_input_asset_directory].input_name       = CSTR_PATH_INPUT_ASSET_DIR_INPUT_NAME; 
        path_text_input_array[path_input_asset_directory].input_cstr.chars = path_buffer_asset_dir;
        path_text_input_array[path_input_asset_directory].input_cstr.size  = SIZE_INPUT_TEXT;

        eng_gui_text_input(path_text_input_array, path_input_count);
    }

    IFB_ENG_FUNC void
    eng_gui_asset_config_text(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_TEXT)) {

        }
    }

    IFB_ENG_FUNC void
    eng_gui_asset_config_image(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_IMAGE)) {

        }
    }

    IFB_ENG_FUNC void
    eng_gui_asset_config_sound(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_SOUND)) {

        }
    }

    IFB_ENG_FUNC void
    eng_gui_asset_config_font(
        void) {

        const ImGuiTreeNodeFlags header_flags = ImGuiTreeNodeFlags_None;
        if (ImGui::CollapsingHeader(CSTR_HEADER_LABEL_FONT)) {

        }
    }

};