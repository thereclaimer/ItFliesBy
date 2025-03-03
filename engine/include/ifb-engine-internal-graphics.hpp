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
    IFBU32 color_table_allocator;
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

    //pointers
    IFBWindow*       graphics_load_pointer_to_window          (const IFBEngineGraphics* ptr_graphics);
    IFBMonitorTable* graphics_load_pointer_to_monitor_table   (const IFBEngineGraphics* ptr_graphics);
    IFBMonitor*      graphics_load_pointer_to_monitor_primary (const IFBEngineGraphics* ptr_graphics);
};


/**********************************************************************************/
/* MONITORS                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_monitors_update_all                 (const IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_monitors_get_active_dimensions      (const IFBEngineGraphics* ptr_graphics, IFBDimensions* ptr_dimensions);
    const IFBB8 graphics_monitors_get_active_position        (const IFBEngineGraphics* ptr_graphics, IFBPosition*   ptr_position);
    const IFBB8 graphics_monitors_get_active_refresh_rate_hz (const IFBEngineGraphics* ptr_graphics, IFBU32*        ptr_refresh_hz);
};

/**********************************************************************************/
/* COLORS                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8
    graphics_get_color_normalized(
        const IFBColorHex*        ptr_color_hex,
              IFBColorNormalized* ptr_color_normalized);
              
    const IFBColorTable*
    graphics_reserve_color_table(
        const IFBEngineGraphics* ptr_graphics,
        const IFBColorHex*       ptr_color_hex_array,
        const IFBChar**          ptr_color_key_array,
        const IFBU32             color_count);

    const IFBB8
    graphics_release_color_table(
        const IFBEngineGraphics* ptr_graphics,
        const IFBColorTable*     ptr_color_table);
};

/**********************************************************************************/
/* WINDOW                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_window_frame_start       (const IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_window_frame_render      (const IFBEngineGraphics* ptr_graphics);
    const IFBB8 graphics_window_get_dimensions    (const IFBEngineGraphics* ptr_graphics, IFBDimensions*       ptr_dimensions);
    const IFBB8 graphics_window_get_position      (const IFBEngineGraphics* ptr_graphics, IFBPosition*         ptr_position);
    const IFBB8 graphics_window_update_dimensions (const IFBEngineGraphics* ptr_graphics, const IFBDimensions* ptr_dimensions);
    const IFBB8 graphics_window_update_position   (const IFBEngineGraphics* ptr_graphics, const IFBPosition*   ptr_position);
};

#endif //IFB_ENGINE_INTERNAL_GRAPHICS_HPP