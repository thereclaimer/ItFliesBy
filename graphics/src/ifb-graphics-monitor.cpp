#pragma once

#include "ifb-graphics.hpp"

using namespace ifb;

const u32
graphics::monitor_table_memory_size(
    void) {

    const u32 count_monitors     = platform::monitor_count();
    const u32 size_table         = ifb_macro_align_size_struct(graphics_monitor_table_t);
    const u32 size_monitor       = ifb_macro_align_size_struct(graphics_monitor_t);
    const u32 size_monitor_array = size_monitor * count_monitors;

    const ifb::u32 size_total = 
         size_table + 
         size_monitor_array;

    return(size_total);
}

graphics_monitor_table_t*
graphics::monitor_table_memory_initialize(
    const ptr memory) {

    ifb_macro_assert(memory);

    //size/count
    const u32 count_monitors       = platform::monitor_count();
    const u32 size_table           = ifb_macro_align_size_struct(graphics_monitor_table_t);

    //addresses
    const addr start_monitor_table = (addr)memory;
    const addr start_monitor_array = start_monitor_table + start_monitor_table;

    //cast the pointer
    graphics_monitor_table_t* monitor_table    = (graphics_monitor_table_t*)memory;
    
    //initialize the table
    monitor_table->monitor_count      = count_monitors;
    monitor_table->monitor_primary    = 0;
    monitor_table->monitor_array      = (graphics_monitor_t*)start_monitor_array;

    //update the table
    (void)graphics::monitor_table_update(monitor_table);

    //we're done
    return(monitor_table);
}

const ifb::b8
graphics::monitor_table_update(
    graphics_monitor_table_t* monitor_table_ptr) {
        
    //sanity check
    ifb_macro_assert(monitor_table_ptr);
    ifb_macro_assert(monitor_table_ptr->monitor_count);
    ifb_macro_assert(monitor_table_ptr->monitor_array);

    //cache properties
    const u32 monitor_count = monitor_table_ptr->monitor_count;
    graphics_monitor_t*  monitor_array = monitor_table_ptr->monitor_array;

    //get the monitor info from the platform
    const b8 result = platform::monitor_info(
        monitor_count,
        monitor_array);

    //if that failed, we're done
    if (!result) return(false);

    //check for the primary monitor
    //the primary monitor will have a position of (0,0)
    b8 primary_monitor_found = false;
    for (
        u32 monitor_index = 0;
               monitor_index < monitor_count;
             ++monitor_index) {

        //check for primary monitor
        position_t monitor_position_ref = monitor_array[monitor_index].position;
        primary_monitor_found = (monitor_position_ref.x == 0 && monitor_position_ref.y == 0);
        
        //if we found the primary monitor, set the index and break
        if (primary_monitor_found) {
            monitor_table_ptr->monitor_primary = monitor_index;
            break;
        }
    }

    //we should ALWAYS have a primary monitor
    ifb_macro_assert(primary_monitor_found);

    //we're done
    return(result);
}

const b8
graphics::monitor_table_get_monitor(
    const graphics_monitor_table_t* monitor_table_ptr,
    graphics_monitor_t*             monitor_ptr) {

    //sanity check
    ifb_macro_assert(monitor_table_ptr);

    //we can proceed if our monitor pointer is valid, and the index 
    //is within the table
    b8 result = true;
    result &= (monitor_ptr != NULL);
    result &= (monitor_ptr->index < monitor_table_ptr->monitor_count);
    if (!result) return(false);

    //get the monitor info
    const u32 monitor_index = monitor_ptr->index;
    *monitor_ptr = monitor_table_ptr->monitor_array[monitor_index];

    //this is valid if the dimensions and
    //refresh rate are non-zero
    result &= (monitor_ptr->refresh_hz        != 0);
    result &= (monitor_ptr->dimensions.width  != 0);
    result &= (monitor_ptr->dimensions.height != 0);

    //we're done
    return(false);
}

const ifb::b8
graphics::monitor_table_get_monitor_primary(
    const graphics_monitor_table_t* monitor_table_ptr,
    graphics_monitor_t*             monitor_ptr) {
        
    //sanity check
    ifb_macro_assert(monitor_table_ptr);
    if (!monitor_ptr) return(false);

    //make sure the primary monitor is valid
    //it should NEVER be greater than the monitor count
    const ifb::u32 monitor_index = monitor_table_ptr->monitor_primary;
    const ifb::u32 monitor_count = monitor_table_ptr->monitor_count;
    ifb_macro_assert(monitor_index < monitor_count);
    
    //get the monitor info
    *monitor_ptr = monitor_table_ptr->monitor_array[monitor_index];

    //this is valid if the dimensions and
    //refresh rate are non-zero
    ifb::b8 result = true;
    result &= (monitor_ptr->refresh_hz        != 0);
    result &= (monitor_ptr->dimensions.width  != 0);
    result &= (monitor_ptr->dimensions.height != 0);

    //we're done
    return(result);
}

const b8
graphics::monitor_get_center(
    const graphics_monitor_t* monitor_ptr,
    position_t*               center_position_ptr) {

    //sanity check
    ifb_macro_assert(monitor_ptr);
    if (!center_position_ptr) return(false);

    //a valid monitor should always have non-zero dimensions
    ifb::b8 result = true;
    result &= monitor_ptr->dimensions.width  != 0;
    result &= monitor_ptr->dimensions.height != 0;

    //calculate center position
    center_position_ptr->x = monitor_ptr->dimensions.width  / 2;
    center_position_ptr->y = monitor_ptr->dimensions.height / 2;

    //the center of a monitor should never be zero
    result &= center_position_ptr->x != 0;
    result &= center_position_ptr->y != 0;

    //we're done
    return(result);
}