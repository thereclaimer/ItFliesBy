#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

#define IFB_ENGINE_GRAPHICS_MEMORY_SIZE_KB 4

struct IFBEngineGraphicsMemory {
    IFBMemoryLinearArenaHandle linear_arena;
};

struct IFBEngineGraphicsHandles {
    ifb_u32 window;
};

struct IFBEngineGraphicsManager {
    IFBEngineGraphicsMemory  memory;    
    IFBEngineGraphicsHandles handles;
};

namespace ifb_engine {

    //initialize
    const ifb_b8 graphics_manager_initialize   (IFBEngineGraphicsManager* ptr_graphics_manager);
    

    //pointers
    IFBWindow* graphics_manager_get_ptr_window (IFBEngineGraphicsManager* ptr_graphics_manager);
};



#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP