#pragma once

#include "ifb-engine-internal-memory.hpp"

ifb_external const ifb_b8
ifb_engine::memory_arena_create_pool(
    const ifb_cstr                     in_arena_tag,
    const ifb_size                     in_arena_size,
    const ifb_size                     in_arena_count,
          IFBEngineMemoryArena&       out_arena_start_ref) {

    ifb_b8 result = true;
    
    //get the memory manager
    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    //create the header
    const IFBEngineMemoryArenaHeaderIndex arena_header_index = ifb_engine::memory_arena_header_create(
        in_arena_tag,
        in_arena_size,
        in_arena_count,
        memory_manager_ref.reservation,
        memory_manager_ref.arena_tables.header);

    //create the batch of arenas
    const IFBEngineMemoryArenaDetailIndex starting_arena_detail_index = 
    ifb_engine::memory_arena_detail_table_insert(
        in_arena_count,
        arena_header_index,
        memory_manager_ref.arena_tables.detail);

    //initialize the struct
    out_arena_start_ref.header_index = arena_header_index;
    out_arena_start_ref.detail_index = starting_arena_detail_index;

    return(true);

}