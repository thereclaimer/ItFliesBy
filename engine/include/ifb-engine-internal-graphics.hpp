#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-graphics.hpp>
#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineGraphicsManager {
    IFBEngineCore* ptr_core;
    IFBWindowArgs* ptr_default_window_args;
    IFBHNDArena    arena;
    IFBHNDWindow   window;
};

namespace ifb_engine {

    //initialize
    const IFBB8 
    graphics_manager_initialize(
        IFBEngineGraphicsManager* ptr_graphics_manager,
        IFBEngineCore*            ptr_core);

};


#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP