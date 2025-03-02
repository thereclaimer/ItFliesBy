#pragma once

#include "ifb-engine-internal-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {
    
    const IFBB8 graphics_monitors_initialize(IFBEngineGraphics* ptr_graphics);
};

/**********************************************************************************/
/* MONITORS                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_engine::graphics_monitors_update_all(
    const IFBEngineGraphics* ptr_graphics) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //load pointers
    IFBMonitorTable* ptr_monitor_table   = ifb_engine::graphics_load_pointer_to_monitor_table   (ptr_graphics);
    IFBMonitor*      ptr_monitor_primary = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);

    //reload the monitor table and  get primary monitor info
    result &= ifb_graphics::monitor_table_update              (ptr_monitor_table);
    result &= ifb_graphics::monitor_table_get_monitor_primary (ptr_monitor_table,ptr_monitor_primary);

    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::graphics_monitors_get_active_dimensions(
    const IFBEngineGraphics* ptr_graphics,
          IFBDimensions*     ptr_dimensions) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_dimensions) return(false);

    //get the dimensions
    IFBMonitor* ptr_monitor = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);
    *ptr_dimensions = ptr_monitor->dimensions;

    //the dimensions should never be zero
    result &= ptr_dimensions->height != 0;
    result &= ptr_dimensions->width  != 0;

    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::graphics_monitors_get_active_position(
    const IFBEngineGraphics* ptr_graphics,
          IFBPosition*       ptr_position) {
        
    IFBB8 result = true;
    
    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_position) return(false);

    //get the position
    IFBMonitor* ptr_monitor = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);
    *ptr_position = ptr_monitor->position;

    //we're done
    return(result);
    
}

inline const IFBB8
ifb_engine::graphics_monitors_get_active_refresh_rate_hz(
    const IFBEngineGraphics* ptr_graphics,
          IFBU32*            ptr_refresh_hz) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(ptr_graphics);
    if (!ptr_refresh_hz) return(false);

    //get the refresh rate
    IFBMonitor* ptr_monitor = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);
    *ptr_refresh_hz = ptr_monitor->refresh_hz;

    //the refresh rate should never be zero
    result &= *ptr_refresh_hz != 0;

    //we're done
    return(result);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_engine::graphics_monitors_initialize(
    IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //intialize the table and get the primary monitor
    IFBB8 result = true;
    result &= ifb_graphics::monitor_table_initialize          (ptr_monitor_table, graphics_arena);
    result &= ifb_graphics::monitor_table_get_monitor_primary (ptr_monitor_table, ptr_monitor_primary);

    //we're done
    return(result);
}