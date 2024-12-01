#pragma once

#include "ifb-engine-internal-tables.hpp"
#include "ifb-engine-internal-controllers.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const IFBEngineArenaId
ifb_engine::memory_arena_commit(
    const ifb_cstr arena_tag,
    const ifb_u32  arena_size_minimum) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //commit the arena
    const IFBEngineArenaId new_arena_id = ifb_engine::controller_arena_commit(
        engine_core,
        arena_tag,
        arena_size_minimum);

    //we're done
    return(new_arena_id);
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

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the arena memory
    const IFBEngineMemoryHandle arena_memory = ifb_engine::controller_arena_handle(
        engine_core,
        arena_id,
        offset);

    //we're done
    return(arena_memory);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_start(
    const IFBEngineArenaId arena_id) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the page start
    const ifb_u32 page_start = ifb_engine::controller_arena_page_start(
        engine_core,
        arena_id);

    //we're done
    return(page_start);
}

ifb_api const ifb_u32 
ifb_engine::memory_arena_page_count(
    const IFBEngineArenaId arena_id) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the page count
    const ifb_u32 page_count = ifb_engine::controller_arena_page_count(
        engine_core,
        arena_id); 

    //we're done
    return(page_count);
}

ifb_api const ifb_cstr 
ifb_engine::memory_arena_tag_value(
    const IFBEngineArenaId arena_id) {

    //get core reference
    IFBEngineCore* engine_core = ifb_engine::context_core();

    //get the tag value
    const ifb_cstr tag_value = ifb_engine::controller_arena_tag_value(
        engine_core,
        arena_id);

    //we're done
    return(tag_value);
}