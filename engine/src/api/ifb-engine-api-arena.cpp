#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-controllers.hpp"

ifb_api const ifb_u32
ifb_engine::arena_page_start(
    const IFBArenaId arena_id) {

    //get core reference
    IFBEngineCore* core_ptr = ifb_engine::context_core();

    //get the page start
    const ifb_u32 page_start = ifb_engine::arena_controller_get_page_start(
        core_ptr,
        arena_id
    );

    //we're done
    return(page_start);
}

ifb_api const ifb_u32
ifb_engine::arena_page_count(
    const IFBArenaId arena_id) {

    //get core reference
    IFBEngineCore* core_ptr = ifb_engine::context_core();

    //get the page count
    const ifb_u32 page_count = ifb_engine::arena_controller_get_page_count(
        core_ptr,
        arena_id);

    //we're done
    return(page_count);
}

ifb_api const ifb_memory
ifb_engine::arena_memory_start(
    const IFBArenaId arena_id) {

    //get core reference
    IFBEngineCore* core_ptr = ifb_engine::context_core();

    //get the arena starting memory
    const ifb_memory arena_start = ifb_engine::arena_controller_get_memory_start(
        core_ptr,
        arena_id
    );

    //we're done
    return(arena_start);
}

ifb_api const ifb_memory
ifb_engine::arena_memory_offset(
    const IFBArenaId arena_id,
    const ifb_u32    offset) {

    //get core reference
    IFBEngineCore* core_ptr = ifb_engine::context_core();


    //get the arena starting memory
    const ifb_memory arena_start = ifb_engine::arena_controller_get_memory_start(
        core_ptr,
        arena_id
    );


    return(NULL);
}

ifb_api const ifb_cstr
ifb_engine::arena_tag(
    const IFBArenaId arena_id) {

    //get core reference
    IFBEngineCore* core_ptr = ifb_engine::context_core();


    return(NULL);
}
