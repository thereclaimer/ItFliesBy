#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline IFBEngineGraphicsMemory*
ifb_engine::graphics_memory_commit(
    IFBEngineCore* core_ptr) {
    
    ifb_macro_assert(core_ptr);

    //commit arena
    const IFBHNDArena graphics_arena = ifb_engine::core_memory_commit_arena(core_ptr);
    
    //commit memory
    IFBEngineGraphicsMemory* graphics_memory_ptr = ifb_memory_macro_commit_struct_to_arena_absolute(graphics_arena,IFBEngineGraphicsMemory); 
    ifb_macro_assert(graphics_memory_ptr);

    //set the handle
    graphics_memory_ptr->arena = graphics_arena;

    //commit handles
    graphics_memory_ptr->handles.window          = ifb_graphics_macro_commit_relative_window        (graphics_arena); 
    graphics_memory_ptr->handles.monitor_table   = ifb_graphics_macro_commit_relative_monitor       (graphics_arena); 
    graphics_memory_ptr->handles.monitor_primary = ifb_graphics_macro_commit_relative_monitor_table (graphics_arena); 

    //initialize the table
    IFBMonitorTable* ptr_monitor_table = ifb_engine::graphics_memory_load_monitor_table(graphics_memory_ptr);
    const IFBB8 result = ifb_graphics::monitor_table_initialize(ptr_monitor_table,graphics_arena);
    
    //if we get here and this happens, we're fucked
    ifb_macro_assert(result);

    //we're done
    return(graphics_memory_ptr);
}

inline IFBWindow*
ifb_engine::graphics_memory_load_window(
    IFBEngineGraphicsMemory* graphics_memory_ptr) {
        
    ifb_macro_assert(graphics_memory_ptr);
    
    IFBWindow* ptr_window = ifb_grahpics_macro_get_pointer_to_window(
        graphics_memory_ptr->arena,
        graphics_memory_ptr->handles.window); 
    
    ifb_macro_assert(ptr_window);
    
    return(ptr_window);
}


inline IFBMonitorTable* 
ifb_engine::graphics_memory_load_monitor_table(
    IFBEngineGraphicsMemory* graphics_memory_ptr) {
        
    ifb_macro_assert(graphics_memory_ptr);
    
    IFBMonitorTable* ptr_monitor_table = ifb_grahpics_macro_get_pointer_to_monitor_table(
        graphics_memory_ptr->arena,
        graphics_memory_ptr->handles.monitor_table); 
    
    ifb_macro_assert(ptr_monitor_table);
    
    return(ptr_monitor_table);
}

inline IFBMonitor*      
ifb_engine::graphics_memory_load_monitor_primary(
    IFBEngineGraphicsMemory* graphics_memory_ptr) {
        
    ifb_macro_assert(graphics_memory_ptr);
    
    IFBMonitor* ptr_monitor_primary = ifb_grahpics_macro_get_pointer_to_monitor(
        graphics_memory_ptr->arena,
        graphics_memory_ptr->handles.monitor_primary); 
    
    ifb_macro_assert(ptr_monitor_primary);
    
    return(ptr_monitor_primary);
}
