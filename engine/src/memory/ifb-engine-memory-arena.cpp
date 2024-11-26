#pragma once

#include "ifb-engine-internal-tables.hpp"
#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::memory_arena_commit(
    const ifb_cstr           in_arena_tag,
    const ifb_u32            in_arena_size_minimum,
          IFBEngineArenaId& out_arena_id_ref) {

    const ifb_b8 result = ifb_engine::controller_arena_commit(
        in_arena_tag,
        in_arena_size_minimum,
        out_arena_id_ref);

    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::memory_arena_valid(
    const IFBEngineArenaId arena_id) {

    return(arena_id.table_indexes.arena.index.value < IFB_ENGINE_MEMORY_ARENA_COUNT_MAX);
}

ifb_api const IFBEngineMemoryHandle
ifb_engine::memory_arena_handle(
    const IFBEngineArenaId arena_id,
    const ifb_u32          offset) {

    const IFBEngineMemoryHandle arena_memory = ifb_engine::controller_arena_handle(
        arena_id,
        offset);

    //we're done
    return(arena_memory);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_start(
    const IFBEngineArenaId arena_id) {

    const ifb_u32 page_start = ifb_engine::controller_arena_page_start(arena_id);

    return(page_start);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_count(
    const IFBEngineArenaId arena_id) {

    const ifb_u32 page_count = ifb_engine::controller_arena_page_count(arena_id); 

    return(page_count);
}

ifb_api const ifb_cstr 
ifb_engine::memory_arena_tag_value(
    const IFBEngineArenaId arena_id) {

    const ifb_cstr tag_value = ifb_engine::controller_arena_tag_value(arena_id);

    //we're done
    return(tag_value);
}