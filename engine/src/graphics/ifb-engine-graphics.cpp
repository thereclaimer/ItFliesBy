#pragma once

#include "ifb-engine-internal-graphics.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    const IFBB8 graphics_manager_commit_memory   (IFBEngineGraphicsManager* ptr_graphics_manager);
    const IFBB8 graphics_manager_reserve_handles (IFBEngineGraphicsManager* ptr_graphics_manager);
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

inline IFBB8 
ifb_engine::graphics_manager_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    ifb_macro_assert(graphics_ptr);

    IFBB8 result = true;
    result &= ifb_engine::graphics_manager_commit_memory   (ptr_graphics_manager);
    result &= ifb_engine::graphics_manager_reserve_handles (ptr_graphics_manager);

    return(result);
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

inline IFBWindow*
ifb_engine::graphics_manager_get_ptr_window(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    ifb_macro_assert(ptr_graphics_manager);

    IFBEngineGraphicsMemory&  ref_memory  = ptr_graphics_manager->memory;
    IFBEngineGraphicsHandles& ref_handles = ptr_graphics_manager->handles;

    ifb_macro_assert(ref_memory.linear_arena.offset);
 
    IFBWindow* ptr_window = (IFBWindow*)ifb_memory::linear_arena_get_pointer_at_offset(
        ref_memory.linear_arena,
        ref_handles.window);

    ifb_macro_assert(ptr_window);

    return(ptr_window);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBB8
ifb_engine::graphics_manager_commit_memory(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //cache the memory
    IFBEngineGraphicsMemory& memory = ptr_graphics_manager->memory;

    //get the core reference
    IFBEngineCore* ptr_core = ifb_engine::context_get_ptr_core();

    //calculate the commit size
    const IFBU32 arena_size = ifb_macro_size_kilobytes(IFB_ENGINE_GRAPHICS_MEMORY_SIZE_KB);

    //commit a linear arena
    memory.linear_arena = ifb_engine::core_memory_arena_commit_linear(
        ptr_core,
        arena_size);

    //check the handle
    const IFBB8 result = ifb_memory_macro_handle_valid(memory.linear_arena);

    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::graphics_manager_reserve_handles(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    if (!ptr_graphics_manager) return(false);

    //cache the properties
    IFBEngineGraphicsMemory&  ref_memory  = ptr_graphics_manager->memory; 
    IFBEngineGraphicsHandles& ref_handles = ptr_graphics_manager->handles;

    //get the arena handle
    const IFBHNDLinearAllocator linear_arena_handle = ref_memory.linear_arena;
    if (!ifb_memory_macro_handle_valid(linear_arena_handle)) return(false);

    //size array
    const IFBU32 size_array[] = {
        ifb_macro_align_size_struct(IFBWindow)
    };

    //size array count
    const IFBU32 handle_count = ifb_macro_array_count(IFBU32,size_array); 

    //handles array
    IFBU32* handle_array = (IFBU32*)&ref_handles;

    //reserve the handles
    const IFBU32 bytes_reserved = ifb_memory::linear_arena_reserve_bytes_relative(
        linear_arena_handle,
        handle_count,
        size_array,
        handle_array);

    //we're done
    return(bytes_reserved > 0);
}