#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineArenaTable* 
ifb_engine::arena_table_pointer_from_handle(
    const ifb_u32 arena_table_handle) {

    IFBEngineArenaTable* arena_table_ptr = (IFBEngineArenaTable*)ifb_engine::memory_pointer_from_handle(arena_table_handle);

    return(arena_table_ptr);
}

inline const ifb_b8 
ifb_engine::arena_table_initialize(
    const ifb_u32 arena_table_handle) {

    //get the table pointer
    IFBEngineArenaTable* arena_table_ptr = ifb_engine::arena_table_pointer_from_handle(arena_table_handle);

    //calculate sizes
    const ifb_u32 arena_count       = IFB_ENGINE_MEMORY_ARENA_COUNT_MAX;
    const ifb_u32 column_size       = ifb_engine_macro_size_array(ifb_u32,arena_count);
    const ifb_u32 column_page_count = ifb_engine::memory_page_count(column_size);

    //commit column pages
    const ifb_u32 page_number_page_start = ifb_engine::memory_page_commit(column_page_count);
    const ifb_u32 page_number_page_count = ifb_engine::memory_page_commit(column_page_count);
    const ifb_u32 page_number_tag_index  = ifb_engine::memory_page_commit(column_page_count);

    //create handles
    const ifb_u32 column_handle_page_start = ifb_engine::memory_handle(page_number_page_start, 0);
    const ifb_u32 column_handle_page_count = ifb_engine::memory_handle(page_number_page_count, 0);
    const ifb_u32 column_handle_tag        = ifb_engine::memory_handle(page_number_tag_index,  0);

    //initialize the struct 
    arena_table_ptr->arena_count_total         = arena_count;
    arena_table_ptr->arena_count_used          = 0;
    arena_table_ptr->arena_size_minimum        = IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM;
    arena_table_ptr->column_handle_page_start  = column_handle_page_start; 
    arena_table_ptr->column_handle_page_count  = column_handle_page_count; 
    arena_table_ptr->column_handle_tag         = column_handle_tag; 

    //sanity check
    const ifb_b8 result = (
        arena_table_ptr->column_handle_page_start != 0 &&
        arena_table_ptr->column_handle_page_count != 0 &&
        arena_table_ptr->column_handle_tag        != 0);

    //we're done
    return(result);
}

inline const ifb_void 
ifb_engine::arena_table_memory(
    IFBEngineArenaTable*              in_arena_table_ptr,
    IFBEngineArenaTableColumnMemory& out_arena_table_column_memory_ref) {

    out_arena_table_column_memory_ref.page_start_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(in_arena_table_ptr->column_handle_page_start);
    out_arena_table_column_memory_ref.page_count_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(in_arena_table_ptr->column_handle_page_count);
    out_arena_table_column_memory_ref.tag_index_ptr  = (ifb_u32*)ifb_engine::memory_pointer_from_handle(in_arena_table_ptr->column_handle_tag);
}

inline const ifb_void
ifb_engine::arena_table_update_arena(
          IFBEngineArenaTable* arena_table_ptr,
    const ifb_u32              arena_index,
    const ifb_u32              arena_tag_index,
    const ifb_u32              arena_page_start,
    const ifb_u32              arena_page_count) {
    
    //get the table memory
    IFBEngineArenaTableColumnMemory arena_table_memory;
    ifb_engine::arena_table_memory(
        arena_table_ptr,
        arena_table_memory);

    //update the table
    arena_table_memory.page_start_ptr [arena_index] = arena_page_start;    
    arena_table_memory.page_count_ptr [arena_index] = arena_page_count;   
    arena_table_memory.tag_index_ptr  [arena_index] = arena_tag_index;
}

inline const ifb_u32* 
ifb_engine::arena_table_column_memory_page_start(
    IFBEngineArenaTable* arena_table_ptr) {

    const ifb_u32* page_start_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(arena_table_ptr->column_handle_page_start);

    return(page_start_ptr);
}

inline const ifb_u32* 
ifb_engine::arena_table_column_memory_page_count(
    IFBEngineArenaTable* arena_table_ptr) {

    const ifb_u32* page_count_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(arena_table_ptr->column_handle_page_count);

    return(page_count_ptr);
}

inline const ifb_u32* 
ifb_engine::arena_table_column_memory_tag(
    IFBEngineArenaTable* arena_table_ptr) {

    const ifb_u32* tag_ptr = (ifb_u32*)ifb_engine::memory_pointer_from_handle(arena_table_ptr->column_handle_tag);

    return(tag_ptr);
}

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_u32 
ifb_engine::memory_arena_commit(
    const ifb_cstr arena_tag,
    const ifb_u32  arena_size_minimum) {

    //get the arena table
    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    //make sure we can commit
    if (arena_table_ptr->arena_count_used == arena_table_ptr->arena_count_total) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //get the arena index
    const ifb_u32 arena_index = arena_table_ptr->arena_count_used;
    
    //create the tag
    ifb_u32 arena_tag_index;
    if (!ifb_engine::tag_create(arena_tag,arena_tag_index)) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    } 

    //do the commit
    const ifb_u32 arena_page_count = ifb_engine::memory_page_count(arena_size_minimum);
    const ifb_u32 arena_page_start = ifb_engine::memory_page_commit(arena_page_count);


    //sanity check
    if (arena_page_start == 0) {
        return(IFB_ENGINE_MEMORY_ARENA_INVALID);
    }

    //update the table
    ifb_engine::arena_table_update_arena(
        arena_table_ptr,
        arena_index,
        arena_tag_index,
        arena_page_start,
        arena_page_count);

    //we're done
    return(arena_index);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_start(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    const ifb_u32* page_start_ptr = ifb_engine::arena_table_column_memory_page_start(arena_table_ptr);
    const ifb_u32  page_start     = page_start_ptr[arena_index]; 

    return(page_start);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_count(
    const ifb_u32 arena_index) {

    IFBEngineArenaTable* arena_table_ptr = ifb_engine::memory_manager_get_arena_table();

    const ifb_u32* page_count_ptr = ifb_engine::arena_table_column_memory_page_count(arena_table_ptr);
    const ifb_u32  page_count     = page_count_ptr[arena_index]; 

    return(page_count);
}
