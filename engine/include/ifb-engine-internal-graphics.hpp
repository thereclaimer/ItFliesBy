#ifndef IFB_ENGINE_INTERNAL_GRAPHICS_HPP
#define IFB_ENGINE_INTERNAL_GRAPHICS_HPP

#include <ifb-graphics.hpp>
#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineGraphics;
struct IFBEngineGraphicsHandles;

/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/

struct IFBEngineGraphicsHandles {
    IFBU32 window;
    IFBU32 monitor_table;
    IFBU32 monitor_primary;
};

struct IFBEngineGraphics {
    IFBHNDArena              arena;
    IFBEngineGraphicsHandles handles;
    IFBColorFormat           color_format;
};

namespace ifb_engine {

    //initialization
    const IFBB8 
    graphics_initialize(
              IFBEngineGraphics* ptr_graphics,
        const IFBHNDArena        arena_handle,
        const IFBColorFormat     color_format);

    //frame start/render
    const IFBB8      graphics_frame_start          (IFBEngineGraphics* ptr_graphics);
    const IFBB8      graphics_frame_render         (IFBEngineGraphics* ptr_graphics);

    //pointers
    IFBWindow*       graphics_load_pointer_to_window          (const IFBEngineGraphics* ptr_graphics);
    IFBMonitorTable* graphics_load_pointer_to_monitor_table   (const IFBEngineGraphics* ptr_graphics);
    IFBMonitor*      graphics_load_pointer_to_monitor_primary (const IFBEngineGraphics* ptr_graphics);
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

    const IFBB8 graphics_window_initialize     (IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_window_frame_start    (IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_window_frame_render   (IFBEngineGraphics* ptr_graphics);

    IFBVoid graphics_window_get_dimensions     (const IFBEngineGraphics* ptr_graphics, IFBDimensions* ptr_window_dimensions);
    IFBVoid graphics_window_get_position       (const IFBEngineGraphics* ptr_graphics, IFBPosition*   ptr_window_position);

    IFBVoid
    graphics_window_update(
        IFBEngineGraphics* ptr_graphics,        
        IFBDimensions*     ptr_window_dimensions,
        IFBPosition*       ptr_window_position);
};

/**********************************************************************************/
/* MONITORS                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_monitors_update_all                          (IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_monitors_get_primary_dimensions_and_position (IFBEngineGraphics* ptr_graphics, IFBDimensionsAndPosition* ptr_monitor_position_and_dimensions);
    const IFBB8 graphics_monitors_get_primary_refresh_rate            (IFBEngineGraphics* ptr_graphics, IFBU32*                   ptr_refresh_hz);
};

#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP