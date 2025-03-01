#pragma once

#include "ifb-engine-graphics-monitors.cpp"
#include "ifb-engine-graphics-memory.cpp"
#include "ifb-engine-graphics-color.cpp"
#include "ifb-engine-graphics-window.cpp"


/**********************************************************************************/
/* INITIALIZATION                                                                 */
/**********************************************************************************/

inline const IFBB8 
ifb_engine::graphics_initialize(
          IFBEngineGraphics* ptr_graphics,
    const IFBHNDArena        arena_handle,
    const IFBColorFormat     color_format) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //set properties and commit memory
    ptr_graphics->arena                   = arena_handle;
    ptr_graphics->handles.window          = ifb_graphics_macro_commit_relative_window        (arena_handle); 
    ptr_graphics->handles.monitor_table   = ifb_graphics_macro_commit_relative_monitor       (arena_handle); 
    ptr_graphics->handles.monitor_primary = ifb_graphics_macro_commit_relative_monitor_table (arena_handle); 
    ptr_graphics->color_format            = color_format; 

    //make sure our pointers are valid
    IFBB8 result = true;
    result &= (ifb_engine::graphics_load_pointer_to_window          (ptr_graphics) != NULL);
    result &= (ifb_engine::graphics_load_pointer_to_monitor_table   (ptr_graphics) != NULL);
    result &= (ifb_engine::graphics_load_pointer_to_monitor_primary (ptr_graphics) != NULL);

    //we're done
    return(result);
}

/**********************************************************************************/
/* FRAME RENDERING                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_engine::graphics_frame_start(
    IFBEngineGraphics* ptr_graphics) {

}

inline const IFBB8
ifb_engine::graphics_frame_render(
    IFBEngineGraphics* ptr_graphics) {

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
    const IFBHNDArena arena  = ptr_graphics->arena;
    const IFBU32      offset = ptr_graphics->handles.window;

    //load the pointer
    IFBWindow* pointer = ifb_grahpics_macro_get_pointer_to_window(arena,offset);

    //we're done
    return(pointer);
}

inline IFBMonitorTable*
ifb_engine::graphics_load_pointer_to_monitor_table(
    const IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //get the arena and offset
    const IFBHNDArena arena  = ptr_graphics->arena;
    const IFBU32      offset = ptr_graphics->handles.monitor_table;

    //load the pointer
    IFBMonitorTable* pointer = ifb_grahpics_macro_get_pointer_to_monitor(arena,offset);

    //we're done
    return(pointer);
}

inline IFBMonitor*
ifb_engine::graphics_load_pointer_to_monitor_primary(
    const IFBEngineGraphics* ptr_graphics) {

    //sanity check
    ifb_macro_assert(ptr_graphics);

    //get the arena and offset
    const IFBHNDArena arena  = ptr_graphics->arena;
    const IFBU32      offset = ptr_graphics->handles.monitor_primary;

    //load the pointer
    IFBMonitor* pointer = ifb_grahpics_macro_get_pointer_to_monitor_table(arena,offset);

    //we're done
    return(pointer);
}
