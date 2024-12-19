#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-platform.hpp"

inline ifb_void 
ifb_engine::graphics_manger_initialize(
    IFBEngineGraphicsManager* graphics_manager_ptr,
    IFBEngineMemory*          memory_ptr) {

    //sanity check
    ifb_macro_assert(graphics_manager_ptr);
    ifb_macro_assert(memory_ptr);

    //first, we need to get the number of monitors the platform has available
    const ifb_u32 montitor_count = ifb_engine::platform_monitor_count();
    ifb_macro_assert(montitor_count > 0);

    //calculate the size of the monitor array and other structures
    const ifb_u32 monitor_array_size = ifb_macro_size_array(IFBMonitor, montitor_count);
    const ifb_u32 window_size        = ifb_macro_align_size_struct(IFBWindow); 
    const ifb_u32 commit_size        = monitor_array_size + window_size;

    //commit memory
    const IFBIDCommit commit_id            = ifb_engine::memory_commit(memory_ptr,commit_size);
    const ifb_address commit_start         = ifb_engine::memory_get_commit_address(memory_ptr,commit_id);
    const ifb_u32     offset_window        = 0;
    const ifb_u32     offset_monitor_array = window_size;

    //set memory properties
    IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref = graphics_manager_ptr->memory;
    graphics_manager_memory_ref.start                = commit_start;
    graphics_manager_memory_ref.offset_window        = offset_window;
    graphics_manager_memory_ref.offset_monitor_array = offset_monitor_array;
    graphics_manager_memory_ref.commit_id            = commit_id;

    //get the monitor array
    IFBMonitor* monitor_array_pointer = ifb_engine::graphics_manager_get_monitor_array_pointer(graphics_manager_memory_ref);
    ifb_macro_assert(monitor_array_pointer);

    //get the monitor information from the platform
    ifb_engine::platform_monitor_info(montitor_count,monitor_array_pointer);

    //set the other properties and we're done, for now its just the monitor count
    graphics_manager_ptr->monitor_count = montitor_count;
}

inline ifb_void 
ifb_engine::graphics_manager_create_window (
          IFBEngineGraphicsManager* graphics_manager_ptr,
    const ifb_cstr                  window_title,
    const IFBWindowFlags            window_flags) {

    //get the active monitor
    const ifb_u32 monitor_index = ifb_engine::platform_monitor_active_index();

    //get the monitor and window
    const IFBMonitor* monitor_ptr = ifb_engine::graphics_manager_get_monitor(graphics_manager_ptr, monitor_index);
          IFBWindow*  window_ptr  = ifb_engine::graphics_manager_get_window_pointer(graphics_manager_ptr->memory);

    //set the flags and monitor id
    window_ptr->flags            = window_flags;
    window_ptr->monitor_id.index = monitor_index;

    //set window properties based on the monitor
    ifb_common::window_set_resolution_based_on_monitor_aspect_ratio(window_ptr, monitor_ptr);
    ifb_common::window_set_position_to_monitor_center              (window_ptr, monitor_ptr);

    //result of platform window initialization
    ifb_b8 result = true;

    //instruct the platform to create a window handle
    result &= ifb_engine::platform_window_create(
        window_title,
        window_ptr->resolution.width,
        window_ptr->resolution.height,
        window_ptr->position.x,        
        window_ptr->position.y);
    
    //process flags
    result &= ifb_common::window_flags_use_opengl(window_flags) ? ifb_engine::platform_window_opengl_init() : true;
    result &= ifb_common::window_flags_use_imgui (window_flags) ? ifb_engine::platform_window_imgui_init()  : true;
    result &= ifb_common::window_flags_is_visible(window_flags) ? ifb_engine::platform_window_show()        : true;

    //sanity check, and we're done
    ifb_macro_assert(result);
}

inline ifb_void 
ifb_engine::graphics_manager_frame_start(
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    ifb_macro_panic();
}

inline ifb_void 
ifb_engine::graphics_manager_frame_render(
    IFBEngineGraphicsManager* graphics_manager_ptr) {

    ifb_macro_panic();
}

inline const IFBMonitor*
ifb_engine::graphics_manager_get_monitor(
    const IFBEngineGraphicsManager* graphics_manager_ptr, 
    const ifb_u32                   monitor_index) {

    //sanity check
    ifb_macro_assert(monitor_index < graphics_manager_ptr->monitor_count);

    //get the monitor array
    const IFBMonitor* monitor_array_ptr = ifb_engine::graphics_manager_get_monitor_array_pointer(graphics_manager_ptr->memory);

    //get the monitor info at the index
    const IFBMonitor* monitor_ptr = &monitor_array_ptr[monitor_index];

    //we're done
    return(monitor_ptr);
}

inline IFBWindow*  
ifb_engine::graphics_manager_get_window_pointer(
    const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref) {

    //get the address
    const ifb_address memory_start   = graphics_manager_memory_ref.start;
    const ifb_address window_address = memory_start + graphics_manager_memory_ref.offset_window;

    //cast to a pointer
    IFBWindow* window_pointer = (IFBWindow*)window_address;

    //we're done
    return(window_pointer);
}

inline IFBMonitor*
ifb_engine::graphics_manager_get_monitor_array_pointer(
    const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref) {

    //get the address
    const ifb_address memory_start          = graphics_manager_memory_ref.start;
    const ifb_address monitor_array_address = memory_start + graphics_manager_memory_ref.offset_monitor_array;

    //cast to a pointer
    IFBMonitor* monitor_array_pointer = (IFBMonitor*)monitor_array_address;

    //we're done
    return(monitor_array_pointer);
}
