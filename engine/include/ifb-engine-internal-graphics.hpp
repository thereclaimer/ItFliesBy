#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-graphics.hpp>
#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* GRAPHICS MEMORY                                                                */
/**********************************************************************************/

struct IFBEngineGraphicsMemory {
    IFBHNDArena arena;
    struct {
        IFBU32 window;
    } handles;
};

namespace ifb_engine {

    IFBEngineGraphicsMemory* graphics_memory_commit       (IFBEngineCore* core_ptr);
    IFBWindow*               graphics_memory_load_window  (IFBEngineGraphicsMemory* graphics_memory_ptr);
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineGraphicsManager {
    IFBEngineCore*           ptr_core;
    IFBEngineGraphicsMemory* ptr_memory;
};

namespace ifb_engine {

    //initialize
    const IFBB8 
    graphics_manager_initialize(
        IFBEngineGraphicsManager* ptr_graphics_manager,
        IFBEngineCore*            ptr_core);

    //frame start/render
    const IFBB8 graphics_manager_frame_start   (IFBEngineGraphicsManager* ptr_graphics_manager);
    const IFBB8 graphics_manager_frame_render  (IFBEngineGraphicsManager* ptr_graphics_manager);
    
};

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8
    graphics_get_color_normalized(
        const IFBColorHex*        ptr_color_hex,
              IFBColorNormalized* ptr_color_normalized);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_window_initialize     (IFBEngineGraphicsManager* ptr_graphics_manager);
    const IFBB8 graphics_window_frame_start    (IFBEngineGraphicsManager* ptr_graphics_manager);
    const IFBB8 graphics_window_frame_render   (IFBEngineGraphicsManager* ptr_graphics_manager);

    IFBVoid graphics_window_get_dimensions     (IFBEngineGraphicsManager* ptr_graphics_manager, IFBDimensions* ptr_window_dimensions);
    IFBVoid graphics_window_get_position       (IFBEngineGraphicsManager* ptr_graphics_manager, IFBPosition*   ptr_window_position);

    IFBVoid
    graphics_window_update(
        IFBEngineGraphicsManager* ptr_graphics_manager,        
        IFBDimensions*            ptr_window_dimensions,
        IFBPosition*              ptr_window_position);
};

#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP