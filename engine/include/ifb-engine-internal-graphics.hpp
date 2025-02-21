#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineGraphicsManager {
    IFBEngineCore* ptr_core;
    IFBHNDArena    arena;
};

namespace ifb_engine {

    //initialize
    const IFBB8 
    graphics_manager_initialize(
        IFBEngineGraphicsManager* ptr_graphics_manager,
        IFBEngineCore*            ptr_core);

};


#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP