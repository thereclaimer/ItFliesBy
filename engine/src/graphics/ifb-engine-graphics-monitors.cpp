#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8
ifb_engine::graphics_monitors_update_all(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    IFBB8 result = true;

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);

    //load pointers
    IFBEngineGraphicsMemory* ptr_graphics_memory = ptr_graphics_manager->ptr_memory;
    IFBMonitorTable*         ptr_monitor_table   = ifb_engine::graphics_memory_load_monitor_table   (ptr_graphics_memory);
    IFBMonitor*              ptr_monitor_primary = ifb_engine::graphics_memory_load_monitor_primary (ptr_graphics_memory);

    //reload the monitor table and  get primary monitor info
    result &= ifb_graphics::monitor_table_update              (ptr_monitor_table);
    result &= ifb_graphics::monitor_table_get_monitor_primary (ptr_monitor_table,ptr_monitor_primary);

    //we're done
    return(result);
}
    
inline const IFBB8
ifb_engine::graphics_monitors_get_primary_dimensions_and_position(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBDimensionsAndPosition* ptr_monitor_position_and_dimensions) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    if (!ptr_monitor_position_and_dimensions) return(false);

    //load pointers
    IFBEngineGraphicsMemory* ptr_graphics_memory = ptr_graphics_manager->ptr_memory;
    IFBMonitor*              ptr_monitor_primary = ifb_engine::graphics_memory_load_monitor_primary(ptr_graphics_memory);

    //cache properties
    IFBDimensions& ref_monitor_dimensions = ptr_monitor_position_and_dimensions->dimensions; 
    IFBPosition&   ref_monitor_position   = ptr_monitor_position_and_dimensions->position;

    //set values
    ref_monitor_dimensions.width  = ptr_monitor_primary->dimensions.width; 
    ref_monitor_dimensions.height = ptr_monitor_primary->dimensions.height; 
    ref_monitor_position.x        = ptr_monitor_primary->position.x; 
    ref_monitor_position.y        = ptr_monitor_primary->position.y; 

    //everything is good as long as the dimensions are non-zero
    //but a position can be zero
    IFBB8 result = true;
    result &= ref_monitor_dimensions.width  != 0; 
    result &= ref_monitor_dimensions.height != 0;
    
    //we're done
    return(result);
}
    
inline const IFBB8
ifb_engine::graphics_monitors_get_primary_refresh_rate(
    IFBEngineGraphicsManager* ptr_graphics_manager,
    IFBU32*                   ptr_refresh_hz) {

    //sanity check
    ifb_macro_assert(ptr_graphics_manager);
    if (!ptr_refresh_hz) return(false);

    //load pointers
    IFBEngineGraphicsMemory* ptr_graphics_memory = ptr_graphics_manager->ptr_memory;
    IFBMonitor*              ptr_monitor_primary = ifb_engine::graphics_memory_load_monitor_primary(ptr_graphics_memory);

    //get the refresh rate
    *ptr_refresh_hz = ptr_monitor_primary->refresh_hz;

    //we're good as long as the refresh rate is non-zero
    const IFBB8 result = *ptr_refresh_hz != 0;
    
    //we're done
    return(result);
}