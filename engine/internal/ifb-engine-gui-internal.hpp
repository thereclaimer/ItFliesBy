#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>

#include "ifb-engine.hpp"

namespace ifb {

    struct eng_gui_t;
    struct eng_gui_u32_flags_imgui_t  : u32_t { };
    struct eng_gui_u32_flags_assets_t : u32_t { };

    enum eng_gui_e32_flag_imgui_ {
        eng_gui_e32_flag_imgui_none      = 0,
        eng_gui_e32_flag_imgui_base_demo = sld::bit_value(0),
        eng_gui_e32_flag_imgui_plot_demo = sld::bit_value(1)
    };

    enum eng_gui_e32_flag_assets_ {
        eng_gui_e32_flag_assets_none       = 0,
        eng_gui_e32_flag_assets_open_text  = sld::bit_value(1),
        eng_gui_e32_flag_assets_open_image = sld::bit_value(2),
        eng_gui_e32_flag_assets_open_sound = sld::bit_value(3),
        eng_gui_e32_flag_assets_open_font  = sld::bit_value(4),
        eng_gui_e32_flag_assets_config     = sld::bit_value(5),
        eng_gui_e32_flag_assets_database   = sld::bit_value(6)
    };

    struct eng_gui_menu_bar_state_t {
        eng_gui_u32_flags_imgui_t  imgui;
        eng_gui_u32_flags_assets_t assets;
    };

    IFB_ENG_FUNC void eng_gui_init               (void);
    IFB_ENG_FUNC void eng_gui_render             (void);
    IFB_ENG_FUNC void eng_gui_main_window        (void);

    IFB_ENG_FUNC void eng_gui_imgui                              (void);
    IFB_ENG_FUNC void eng_gui_asset_config                       (void);
    IFB_ENG_FUNC void eng_gui_asset_config_path_input            (void);
    IFB_ENG_FUNC void eng_gui_asset_config_asset_directory_input (void);
    IFB_ENG_FUNC void eng_gui_asset_config_text                  (void);
    IFB_ENG_FUNC void eng_gui_asset_config_image                 (void);
    IFB_ENG_FUNC void eng_gui_asset_config_sound                 (void);
    IFB_ENG_FUNC void eng_gui_asset_config_font                  (void);

    static eng_gui_menu_bar_state_t _eng_gui_menu_bar_state;

    IFB_ENG_INLINE void eng_gui_imgui_window_open      (const u32 imgui_window)   { _eng_gui_menu_bar_state.imgui.val |=  imgui_window;               }
    IFB_ENG_INLINE void eng_gui_imgui_window_close     (const u32 imgui_window)   { _eng_gui_menu_bar_state.imgui.val &= ~imgui_window;               }
    IFB_ENG_INLINE bool eng_gui_imgui_window_is_open   (const u32 imgui_window)   { return(_eng_gui_menu_bar_state.imgui.val & imgui_window);         }
    IFB_ENG_INLINE void eng_gui_imgui_window_reset_all (void)                     { _eng_gui_menu_bar_state.imgui.val = eng_gui_e32_flag_imgui_none;  }

    IFB_ENG_INLINE void eng_gui_assets_window_open      (const u32 assets_window) { _eng_gui_menu_bar_state.assets.val |=  assets_window;             }
    IFB_ENG_INLINE void eng_gui_assets_window_close     (const u32 assets_window) { _eng_gui_menu_bar_state.assets.val &= ~assets_window;             }
    IFB_ENG_INLINE bool eng_gui_assets_window_is_open   (const u32 assets_window) { return(_eng_gui_menu_bar_state.assets.val & assets_window);       }
    IFB_ENG_INLINE void eng_gui_assets_window_reset_all (void)                    { _eng_gui_menu_bar_state.assets.val = eng_gui_e32_flag_assets_none; }

    struct eng_gui_text_dims_t : dims_f32_size_t { };

    IFB_ENG_INLINE eng_gui_text_dims_t
    eng_gui_text_dims(
        void) {
        
        eng_gui_text_dims_t dims;
        dims.width  = ImGui::CalcTextSize("A").x;
        dims.height = ImGui::GetTextLineHeightWithSpacing();
        return(dims);
    }

    struct eng_gui_text_input_t {
        const cchar* label_button;
        const cchar* label_text_box;
        const cchar* input_name;
        cstr_t       input_cstr;
        bool         button_clicked;
    };

    IFB_ENG_INLINE void
    eng_gui_text_input(
        eng_gui_text_input_t* text_input,
        const u32             count = 1) {

        constexpr u32 col_index_label  = 0;
        constexpr u32 col_index_text   = 1;
        constexpr u32 col_index_button = 2;
        constexpr u32 col_count        = 3;

        static eng_gui_text_dims_t text_dims = eng_gui_text_dims();

        constexpr ImGuiTableFlags table_flags = (
            0
        );

        if (ImGui::BeginTable("input-table",col_count)) {


            for (
                u32 index = 0;
                index < count;
                ++index) {

                eng_gui_text_input_t& current_text_input = text_input[index];

                ImGui::TableNextRow();
                
                ImGui::TableSetColumnIndex(col_index_label);
                ImGui::Text(current_text_input.label_text_box);

                ImGui::TableSetColumnIndex(col_index_text);
                ImGui::InputText(current_text_input.input_name, current_text_input.input_cstr.chars, current_text_input.input_cstr.size);

                ImGui::TableSetColumnIndex(col_index_button);
                current_text_input.button_clicked = ImGui::Button(current_text_input.label_button);
            }

            ImGui::EndTable();
        }
    };

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP