#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline IFBEngineGraphicsMemory*
ifb_engine::graphics_memory_commit(
    IFBEngineCore* core_ptr) {
    
    ifb_macro_assert(core_ptr);

    //commit arena
    const IFBHNDArena graphics_arena = ifb_engine::core_memory_commit_arena(core_ptr);
    
    //commit memory
    const IFBU32 size_graphics_memory = ifb_macro_align_size_struct(IFBEngineGraphicsMemory);
    IFBEngineGraphicsMemory* graphics_memory_ptr = (IFBEngineGraphicsMemory*)ifb_memory::arena_commit_bytes_absolute(
        graphics_arena,
        size_graphics_memory);
    ifb_macro_assert(graphics_memory_ptr);

    //set the handle
    graphics_memory_ptr->arena = graphics_arena;

    //commit handles
    graphics_memory_ptr->handles.window = ifb_graphics::window_commit_to_arena_relative(graphics_arena);


    //we're done
    return(graphics_memory_ptr);
}

inline IFBWindow*
ifb_engine::graphics_memory_load_window(
    IFBEngineGraphicsMemory* graphics_memory_ptr) {
        
    ifb_macro_assert(graphics_memory_ptr);
    
    IFBWindow* ptr_window = (IFBWindow*)ifb_memory::arena_get_pointer(
        graphics_memory_ptr->arena,
        graphics_memory_ptr->handles.window);
        
    ifb_macro_assert(ptr_window);
    
    return(ptr_window);
}