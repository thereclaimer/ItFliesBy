#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr cchar CSTR_HEADER_LABEL_TEXT                     [] = "Text";
    constexpr cchar CSTR_HEADER_LABEL_IMAGE                    [] = "Images";
    constexpr cchar CSTR_HEADER_LABEL_SOUND                    [] = "Sounds";
    constexpr cchar CSTR_HEADER_LABEL_FONT                     [] = "Fonts";
    constexpr cchar CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT     [] = "Config File:";
    constexpr cchar CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT [] = "Asset Directory:";
    constexpr cchar CSTR_INPUT_BUTTON_SUBMIT_FILE              [] = "Submit File";
    constexpr cchar CSTR_INPUT_BUTTON_SUBMIT_DIR               [] = "Submit Dir";
    
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

        constexpr u32 path_input_file  = 0; 
        constexpr u32 path_input_dir   = 1; 
        constexpr u32 path_input_count = 2; 

        static eng_gui_text_input_t path_text_input_array [path_input_count] = {
            eng_gui_text_input_init(CSTR_INPUT_BUTTON_SUBMIT_FILE, CSTR_PATH_INPUT_CONFIG_FILE_LABEL_TEXT),    // path_input_file
            eng_gui_text_input_init(CSTR_INPUT_BUTTON_SUBMIT_DIR,  CSTR_PATH_INPUT_ASSET_DIR_INPUT_LABEL_TEXT) // path_input_asset_directory
        };
        eng_gui_text_input(path_text_input_array, path_input_count);

        const u32  input_size = sizeof(eng_gui_input_cstr_t);

        if (path_text_input_array[path_input_file].button_clicked) {

            FileDialog::file_dialog_open      = true;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::OpenFile;
            cchar* input_buffer               = path_text_input_array[path_input_file].input_string.buffer; 

            if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(
                    &FileDialog::file_dialog_open,
                    input_buffer,
                    input_size
                );
            }
        }

        if (path_text_input_array[path_input_dir].button_clicked) {

            FileDialog::file_dialog_open      = true;
            FileDialog::file_dialog_open_type = FileDialog::FileDialogType::SelectFolder;
            cchar*      input_buffer          = path_text_input_array[path_input_dir].input_string.buffer; 

            if (FileDialog::file_dialog_open) {
                FileDialog::ShowFileDialog(
                    &FileDialog::file_dialog_open,
                    input_buffer,
                    input_size
                );
            }
        }
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