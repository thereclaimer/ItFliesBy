#ifndef IFB_ENGINE_CONTEXT_HPP
#define IFB_ENGINE_CONTEXT_HPP

#include <ifb.hpp>

namespace ifb_engine {

    // create/destroy
    ifb_engine_api const IFBB8 
    context_create(
        const IFBPlatformApi* ptr_platform_api,
        const IFBByte*       ptr_stack_memory,
        const IFBU32         stack_memory_size);
    
    
    ifb_engine_api const IFBB8 context_destroy      (IFBVoid);
    
    // startup/shutdown
    ifb_engine_api const IFBB8 context_startup      (IFBVoid);
    ifb_engine_api const IFBB8 context_shutdown     (IFBVoid);
    
    // rendering
    ifb_engine_api const IFBB8 context_render_frame (IFBVoid);
};

#endif //IFB_ENGINE_CONTEXT_HPP