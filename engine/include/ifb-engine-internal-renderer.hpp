#ifndef IFB_ENGING_INTERNAL_RENDERER_HPP
#define IFB_ENGING_INTERNAL_RENDERER_HPP

#include "ifb-engine.hpp"

#include "ifb-engine-internal-core.hpp"

struct IFBEngineRenderer {
    IFBHNDArena    arena_handle;
    IFBGLViewport  viewport;
};

namespace ifb_engine {

    const IFBB8
    renderer_initialize(
              IFBEngineRenderer*  ptr_renderer,
        const IFBHNDArena         arena_handle,
        const IFBDimensions*      ptr_viewport_dimensions,
        const IFBColorNormalized* ptr_viewport_color);

    const IFBB8
    renderer_update_viewport(
              IFBEngineRenderer*  ptr_renderer,
        const IFBDimensions*      ptr_viewport_dimensions,
        const IFBColorNormalized* ptr_viewport_color);

    const IFBB8
    renderer_clear_viewport(
        IFBEngineRenderer* ptr_renderer);
};

#endif //IFB_ENGING_INTERNAL_RENDERER_HPP