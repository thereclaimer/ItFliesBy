#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

struct IFBHNDEngineWindow : IFBHND32 { };

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

struct IFBEngineWindow {
    IFBHNDEngineWindow handle;
    IFBDimensions      dimensions;
    IFBPosition        position;
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineGraphicsManager {
    IFBHNDArena        arena;
    IFBHNDEngineWindow window;
};

namespace ifb_engine {

    //initialize
    const IFBB8 
    graphics_manager_initialize(
        IFBEngineGraphicsManager* ptr_graphics_manager,
        IFBEngineCore*            ptr_core);


    IFBEngineWindow* graphics_manager_get_window (IFBEngineGraphicsManager* ptr_graphics_manager);
};


#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP