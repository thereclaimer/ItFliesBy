#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

#define IFB_ENGINE_GRAPHICS_MEMORY_SIZE_KB 4

struct IFBEngineGraphicsMemory {
    IFBHNDMemoryArenaLinear linear_arena;
};

struct IFBEngineGraphicsHandles {
    IFBU32 window;
};

struct IFBEngineGraphicsManager {
    IFBEngineGraphicsMemory  memory;    
    IFBEngineGraphicsHandles handles;
};

namespace ifb_engine {

    //initialize
    const IFBB8 graphics_manager_initialize   (IFBEngineGraphicsManager* ptr_graphics_manager);
    

    //pointers
};



#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP