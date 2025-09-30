#ifndef IFB_ENGINE_GUI_INTERNAL_HPP
#define IFB_ENGINE_GUI_INTERNAL_HPP

#include "ifb-engine.hpp"

namespace ifb {

    struct eng_gui_t;
    struct eng_gui_u32_flags_imgui_t : eng_u32_t { };

    enum eng_gui_e32_flag_imgui_ {
        eng_gui_e32_flag_imgui_none = 0,
        eng_gui_e32_flag_imgui_demo = sld::bit_value(0)
    };

    eng_void eng_gui_init   (eng_void);
    eng_void eng_gui_render (eng_void);

    struct eng_gui_t {
        eng_gui_u32_flags_imgui_t imgui_flags;
    };

    static eng_gui_t _eng_gui;
};

#endif //IFB_ENGINE_GUI_INTERNAL_HPP