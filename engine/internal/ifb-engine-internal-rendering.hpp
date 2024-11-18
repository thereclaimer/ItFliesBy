#ifndef IFB_ENGINE_INTERNAL_RENDERING_HPP
#define IFB_ENGINE_INTERNAL_RENDERING_HPP

#include "ifb-engine.hpp"

struct IFBEngineRenderingSystem {
    ifb_color_32_format_t color_format;
    ifb_color_32_t        color_clear;
};

namespace ifb_engine {

    const ifb_b8 rendering_routine_system_startup  (ifb_void);
    const ifb_b8 rendering_routine_system_shutdown (ifb_void);
    const ifb_b8 rendering_routine_new_frame       (ifb_void);
    const ifb_b8 rendering_routine_render_frame    (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_RENDERING_HPP