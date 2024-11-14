#pragma once

#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_u32 
ifb_engine::memory_manager_startup(
    ifb_void) {

    //determine the size of all the systems
    const ifb_u32 size_aligned_memory_manager = ifb_engine_macro_align_size_struct(IFBEngineMemoryManager); 
    const ifb_u32 size_aligned_arena_table    = ifb_engine_macro_align_size_struct(IFBEngineArenaTable);

    //add all the sizes to get our total allocation size
    const ifb_u32 allocation_size =
        size_aligned_memory_manager +
        size_aligned_arena_table;

    //commit pages
    const ifb_u32 memory_manager_page_count = ifb_engine::memory_page_count(allocation_size);
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

    //initialize asset systems
    ifb_b8 result = true;
    result &= ifb_engine::arena_table_initialize(handle_arena_table);

    //initialize the memory manager
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_handle(handle_memory_manager);
    memory_manager_ptr->page_start         = memory_manager_page_start;
    memory_manager_ptr->page_count         = memory_manager_page_count;
    memory_manager_ptr->handle_arena_table = handle_arena_table; 

    //we're done, return the page start
    return(handle_memory_manager);
}

inline IFBEngineMemoryManager* 
ifb_engine::memory_manager_pointer_from_handle(
    const ifb_u32 memory_manager_handle) {

    IFBEngineMemoryManager* memory_manager_ptr = (IFBEngineMemoryManager*)ifb_engine::memory_pointer_from_handle(memory_manager_handle);

    return(memory_manager_ptr); 
}

inline IFBEngineArenaTable* 
ifb_engine::memory_manager_get_arena_table(
    ifb_void) {

    //get the memory manager_handle
    const ifb_u32 memory_manager_handle = ifb_engine::context_core_handle_memory_manager();

    //cast it to the pointer
    IFBEngineMemoryManager* memory_manager_ptr = ifb_engine::memory_manager_pointer_from_handle(memory_manager_handle);     

    //get the arena table pointer
    IFBEngineArenaTable* arena_table_ptr = ifb_engine::arena_table_pointer_from_handle(memory_manager_ptr->handle_arena_table);        

    //we're done
    return(arena_table_ptr);
}