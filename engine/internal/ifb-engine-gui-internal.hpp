#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include <imgui.h>

#include "ifb-engine.hpp"

namespace ifb {

    struct eng_gui_t;
    struct eng_gui_u32_flags_imgui_t : eng_u32_t { };

    enum eng_gui_e32_flag_imgui_ {
        eng_gui_e32_flag_imgui_none      = 0,
        eng_gui_e32_flag_imgui_base_demo = sld::bit_value(0),
        eng_gui_e32_flag_imgui_plot_demo = sld::bit_value(1)
    };

    struct eng_gui_menu_bar_state_t {
        eng_gui_u32_flags_imgui_t imgui;
    };

    IFB_ENG_FUNC eng_void eng_gui_init        (eng_void);
    IFB_ENG_FUNC eng_void eng_gui_render      (eng_void);
    IFB_ENG_FUNC eng_void eng_gui_main_window (eng_void);

    IFB_ENG_FUNC eng_void eng_gui_imgui       (eng_void);

    struct eng_gui_t {
        eng_gui_u32_flags_imgui_t imgui_flags;
    };

    static eng_gui_menu_bar_state_t _eng_gui_menu_bar_state;

    IFB_ENG_INLINE void eng_gui_imgui_window_open   (const eng_u32 imgui_window) { _eng_gui_menu_bar_state.imgui.val |=  imgui_window;       }
    IFB_ENG_INLINE void eng_gui_imgui_window_close  (const eng_u32 imgui_window) { _eng_gui_menu_bar_state.imgui.val &= ~imgui_window;       }
    IFB_ENG_INLINE bool eng_gui_imgui_window_is_open(const eng_u32 imgui_window) { return(_eng_gui_menu_bar_state.imgui.val & imgui_window); }

};


#endif //IFB_ENGINE_GUI_INTERNAL_HPP