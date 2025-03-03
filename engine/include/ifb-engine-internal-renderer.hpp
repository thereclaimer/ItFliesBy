#ifndef IFB_ENGING_INTERNAL_RENDERER_HPP
#define IFB_ENGING_INTERNAL_RENDERER_HPP

#include "ifb-engine.hpp"

#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineRenderer;

/**********************************************************************************/
/* RENDERER                                                                       */
/**********************************************************************************/

struct IFBEngineRendererHandles {
    IFBU32 viewport;
};

struct IFBEngineRenderer {
    IFBHNDArena              arena;
    IFBEngineRendererHandles handles;
};

namespace ifb_engine {

    //initialization
    const IFBB8
    renderer_initialize(
              IFBEngineRenderer*  ptr_renderer,
        const IFBHNDArena         arena_handle,
        const IFBDimensions*      ptr_viewport_dimensions,
        const IFBColorNormalized* ptr_viewport_clear_color);

    //pointers
    IFBGLViewport* renderer_load_pointer_to_viewport (const IFBEngineRenderer* ptr_renderer);
};

/**********************************************************************************/
/* VIEWPORT                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 renderer_viewport_clear              (const IFBEngineRenderer* ptr_renderer);
    const IFBB8 renderer_viewport_update_dimensions  (const IFBEngineRenderer* ptr_renderer, const IFBDimensions*      ptr_viewport_dimensions);
    const IFBB8 renderer_viewport_update_clear_color (const IFBEngineRenderer* ptr_renderer, const IFBColorNormalized* ptr_viewport_clear_color);
};

#endif //IFB_ENGING_INTERNAL_RENDERER_HPP