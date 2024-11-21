#pragma once

#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_u32 
ifb_engine::memory_manager_startup(
    ifb_void) {

    //determine the size of all the systems
    const ifb_u32 size_aligned_memory_manager = ifb_macro_align_size_struct(IFBEngineMemoryManager); 

    //commit pages
    const ifb_u32 memory_manager_page_count = ifb_engine::memory_page_count(size_aligned_memory_manager);
    const ifb_u32 memory_manager_page_start = ifb_engine::memory_page_commit(memory_manager_page_count);

    //if that didn't work, return 0
    if (!memory_manager_page_start) {
        return(0);
    }

    //calculate offsets
    const ifb_u32 page_offset_arena_table = size_aligned_memory_manager; //the arena table is at the end of the memory manager struct 

    //create handles
    const ifb_u32 handle_arena_table    = ifb_engine::memory_handle(memory_manager_page_start,page_offset_arena_table); 
    const ifb_u32 handle_memory_manager = ifb_engine::memory_handle(memory_manager_page_start,0);

    //initialize the memory manager
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_handle(handle_memory_manager);
    memory_manager_ptr->page_start         = memory_manager_page_start;
    memory_manager_ptr->page_count         = memory_manager_page_count;
    memory_manager_ptr->arena_size_minimum = IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM;
    memory_manager_ptr->arena_count_used   = 0;
    memory_manager_ptr->arena_count_total  = IFB_ENGINE_MEMORY_ARENA_COUNT_MAX;

    //we're done, return the page start
    return(handle_memory_manager);
}

inline IFBEngineMemoryManager* 
ifb_engine::memory_manager_pointer_from_handle(
    const ifb_u32 memory_manager_handle) {

    IFBEngineMemoryManager* memory_manager_ptr = (IFBEngineMemoryManager*)ifb_engine::memory_pointer_from_handle(memory_manager_handle);

    return(memory_manager_ptr); 
}

inline IFBEngineMemoryManager* 
ifb_engine::memory_manager_pointer_from_context(
    ifb_void) {
    
    IFBEngineCore*          engine_core_ptr    = ifb_engine::core_pointer_from_context();
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_handle(engine_core_ptr->managers.memory);

    return(memory_manager_ptr);
}