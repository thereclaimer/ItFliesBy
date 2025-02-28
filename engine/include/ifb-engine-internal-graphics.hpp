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
        IFBU32 monitor_table;
        IFBU32 monitor_primary;
    } handles;
};

namespace ifb_engine {

    IFBEngineGraphicsMemory* graphics_memory_commit               (IFBEngineCore* core_ptr);
    IFBWindow*               graphics_memory_load_window          (IFBEngineGraphicsMemory* graphics_memory_ptr);
    IFBMonitorTable*         graphics_memory_load_monitor_table   (IFBEngineGraphicsMemory* graphics_memory_ptr);
    IFBMonitor*              graphics_memory_load_monitor_primary (IFBEngineGraphicsMemory* graphics_memory_ptr);
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

/**********************************************************************************/
/* MONITORS                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_monitors_update_all                          (IFBEngineGraphicsManager* ptr_graphics_manager);
    const IFBB8 graphics_monitors_get_primary_dimensions_and_position (IFBEngineGraphicsManager* ptr_graphics_manager, IFBDimensionsAndPosition* ptr_monitor_position_and_dimensions);
    const IFBB8 graphics_monitors_get_primary_refresh_rate            (IFBEngineGraphicsManager* ptr_graphics_manager, IFBU32*                   ptr_refresh_hz);
};

#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP