#ifndef IFB_ENGINE_CONTEXT_HPP
#define IFB_ENGINE_CONTEXT_HPP

#include <ifb.hpp>

namespace ifb_engine {

    // create/destroy
    ifb_engine_api const ifb_b8 
    context_create(
        const IFBPlatformApi& platform_api_ref,
        const ifb_byte*       stack_memory_ptr,
        const ifb_u32         stack_memory_size);
    
    
    ifb_engine_api const ifb_b8 context_destroy      (ifb_void);
    
    // startup/shutdown
    ifb_engine_api const ifb_b8 context_startup      (ifb_void);
    ifb_engine_api const ifb_b8 context_shutdown     (ifb_void);
    
    // rendering
    ifb_engine_api const ifb_b8 context_render_frame (ifb_void);
};

#endif //IFB_ENGINE_CONTEXT_HPP