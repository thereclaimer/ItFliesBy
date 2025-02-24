#ifndef IFB_ENGINE_CONTEXT_HPP
#define IFB_ENGINE_CONTEXT_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>

struct IFBEngineContextUpdate {
    IFBPosition   window_position;
    IFBDimensions window_dimensions;
    IFBInput      user_input;
};

namespace ifb_engine {

    // create/destroy
    ifb_engine_api const IFBStack 
    context_create(
        const IFBPlatformApi* ptr_platform_api,
        const IFBByte*        ptr_stack_memory,
        const IFBU32          size_stack_memory,
        const IFBU64          reservation_size );
    
    
    ifb_engine_api const IFBB8 context_destroy      (IFBVoid);
    
    // startup/shutdown
    ifb_engine_api  IFBEngineContextUpdate* context_startup  (IFBVoid);
    ifb_engine_api const IFBB8              context_shutdown (IFBVoid);
    
    // rendering
    ifb_engine_api const IFBB8 context_render_frame (IFBEngineContextUpdate* ptr_update);
};

#endif //IFB_ENGINE_CONTEXT_HPP