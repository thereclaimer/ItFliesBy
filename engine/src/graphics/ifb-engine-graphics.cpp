#pragma once

#include "ifb-engine-internal-graphics.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 graphics_manager_commit_memory   (IFBEngineGraphicsManager* ptr_graphics_manager);
    const ifb_b8 graphics_manager_reserve_handles (IFBEngineGraphicsManager* ptr_graphics_manager);
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

inline ifb_b8 
ifb_engine::graphics_manager_initialize(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    ifb_macro_assert(graphics_ptr);

    ifb_b8 result = true;
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

inline const ifb_b8
ifb_engine::graphics_manager_commit_memory(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    //cache the memory
    IFBEngineGraphicsMemory& memory = ptr_graphics_manager->memory;

    //get the core reference
    IFBEngineCore* ptr_core = ifb_engine::context_get_ptr_core();

    //calculate the commit size
    const ifb_u32 arena_size = ifb_macro_size_kilobytes(IFB_ENGINE_GRAPHICS_MEMORY_SIZE_KB);

    //commit a linear arena
    memory.linear_arena = ifb_engine::core_memory_arena_commit_linear(
        ptr_core,
        arena_size);

    //check the handle
    const ifb_b8 result = ifb_memory_macro_handle_valid(memory.linear_arena);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::graphics_manager_reserve_handles(
    IFBEngineGraphicsManager* ptr_graphics_manager) {

    if (!ptr_graphics_manager) return(false);

    //cache the properties
    IFBEngineGraphicsMemory&  ref_memory  = ptr_graphics_manager->memory; 
    IFBEngineGraphicsHandles& ref_handles = ptr_graphics_manager->handles;

    //get the arena handle
    const IFBMemoryLinearArenaHandle linear_arena_handle = ref_memory.linear_arena;
    if (!ifb_memory_macro_handle_valid(linear_arena_handle)) return(false);

    //size array
    const ifb_u32 size_array[] = {
        ifb_macro_align_size_struct(IFBWindow)
    };

    //size array count
    const ifb_u32 handle_count = ifb_macro_array_count(ifb_u32,size_array); 

    //handles array
    ifb_u32* handle_array = (ifb_u32*)&ref_handles;

    //reserve the handles
    const ifb_u32 bytes_reserved = ifb_memory::linear_arena_reserve_bytes_relative(
        linear_arena_handle,
        handle_count,
        size_array,
        handle_array);

    //we're done
    return(bytes_reserved > 0);
}