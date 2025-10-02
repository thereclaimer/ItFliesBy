#pragma once

#include "ifb-engine-gui-internal.hpp"
#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    static eng_asset_config_t* _asset_config;

    IFB_ENG_FUNC eng_void
    eng_gui_asset_config(
        eng_void) {

        constexpr eng_cchar window_name_cstr[] = "Asset Config";
        bool is_open = eng_gui_assets_window_is_open(eng_gui_e32_flag_assets_config);

        if (is_open && ImGui::Begin(window_name_cstr, &is_open)) {

            if (!_asset_config) {
                _asset_config = eng_asset_config_create();
                assert(_asset_config);
            }

            ImGui::End();
        }

        if (!is_open) {
            eng_gui_assets_window_close(eng_gui_e32_flag_assets_config);
            if (_asset_config) {
                eng_asset_config_destroy(_asset_config);
                _asset_config = NULL;
            } 
        }
    }
};