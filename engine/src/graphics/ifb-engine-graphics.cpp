#pragma once

#include "ifb-engine-graphics-color.cpp"
#include "ifb-engine-graphics-monitors.cpp"
#include "ifb-engine-graphics-window.cpp"

/**********************************************************************************/
/* INITIALIZATION                                                                 */
/**********************************************************************************/

inline const IFBB8 
ifb_engine::graphics_initialize(
          IFBEngineGraphics* ptr_graphics,
          IFBMemoryArena*    ptr_arena,
    const IFBColorFormat     color_format) {
    
    IFBB8 result = true;
    
    //sanity check
    ifb_macro_assert(ptr_graphics);

    //set properties and commit memory
    ptr_graphics->arena                   = ptr_arena;
    ptr_graphics->handles.window          = ifb_graphics_macro_commit_relative_window        (ptr_arena); 
    ptr_graphics->handles.monitor_table   = ifb_graphics_macro_commit_relative_monitor       (ptr_arena); 
    ptr_graphics->handles.monitor_primary = ifb_graphics_macro_commit_relative_monitor_table (ptr_arena); 
    ptr_graphics->color_format            = color_format; 

    //load monitor pointers
    IFBMonitorTable* ptr_monitor_table = ifb_engine::graphics_load_pointer_to_monitor_table   (ptr_graphics);
    IFBMonitor*      ptr_monitor       = ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics);

    //initialize the monitors
    result &= ifb_engine::graphics_monitors_initialize (ptr_graphics);
    result &= ifb_engine::graphics_window_initialize   (ptr_graphics);

    //we're done
    return(result);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline IFBWindow*
ifb_engine::graphics_load_pointer_to_window(
    const IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //get the arena and offset
    IFBMemoryArena* arena  = ptr_graphics->arena;
    const IFBU32    offset = ptr_graphics->handles.window;

    //load the pointer
    IFBWindow* pointer = ifb_graphics_macro_get_pointer_to_window(arena,offset);
    ifb_macro_assert(pointer);

    //we're done
    return(pointer);
}

inline IFBMonitorTable*
ifb_engine::graphics_load_pointer_to_monitor_table(
    const IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);
    
    //get the arena and offset
    IFBMemoryArena* arena  = ptr_graphics->arena;
    const IFBU32    offset = ptr_graphics->handles.monitor_table;
    
    //load the pointer
    IFBMonitorTable* pointer = ifb_graphics_macro_get_pointer_to_monitor_table(arena,offset);
    ifb_macro_assert(pointer);

    //we're done
    return(pointer);
}

inline IFBMonitor*
ifb_engine::graphics_load_pointer_to_monitor_primary(
    const IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //get the arena and offset
    IFBMemoryArena* arena  = ptr_graphics->arena;
    const IFBU32    offset = ptr_graphics->handles.monitor_primary;

    //load the pointer
    IFBMonitor* pointer = ifb_graphics_macro_get_pointer_to_monitor(arena,offset);
    ifb_macro_assert(pointer);

    //we're done
    return(pointer);
}