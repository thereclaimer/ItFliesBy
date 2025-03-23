
#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-internal.cpp"
#include "ifb-memory-arena-commit.cpp"
#include "ifb-memory-arena-decommit.cpp"
#include "ifb-memory-arena-push.cpp"

const IFBB8
ifb_memory::arena_commit(
    IFBMemoryArenaContext* arena_context) {
    
    //set the context
    IFBMemoryArenaCommit commit;
    commit.context = arena_context;

    //commit steps
    ifb_memory::arena_commit_step_0_validate_args            (commit);
    ifb_memory::arena_commit_step_1_cache_manager_properties (commit);
    ifb_memory::arena_commit_step_2_find_free_arena          (commit);
    ifb_memory::arena_commit_step_3_commit_memory            (commit);
    ifb_memory::arena_commit_step_4_update_arrays            (commit);

    //we're done
    return(commit.result ? true : false);
}

const IFBB8
ifb_memory::arena_decommit(
    IFBMemoryArenaContext* arena_context) {
  
    //set the args
    IFBMemoryArenaDecommit decommit;
    decommit.context = arena_context;

    //do the decommit
    ifb_memory::arena_decommit_step_0_validate_args            (decommit);
    ifb_memory::arena_decommit_step_1_cache_manager_properties (decommit);
    ifb_memory::arena_decommit_step_2_load_arena_start_array   (decommit);
    ifb_memory::arena_decommit_step_3_decommit_memory          (decommit);
    ifb_memory::arena_decommit_step_4_update_arena_start_array (decommit);

    //we're done
    return(decommit.result ? true : false);
}

const IFBB8
ifb_memory::arena_reset(
    IFBMemoryArenaContext* arena_context) {


    return(false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
    IFBMemoryArenaContext* arena_context) {

    //set the args
    IFBMemoryArenaPushBytes push;
    push.context = arena_context;

    //do the push
    ifb_memory::arena_push_step_0_validate_args            (push);
    ifb_memory::arena_push_step_1_cache_manager_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_relative      (push);

    //get the offset
    const IFBU32 offset = push.result
        ? push.context->memory.relative_offset
        : IFB_MEMORY_INVALID_VALUE;

    //we're done
    return(offset);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
    IFBMemoryArenaContext* arena_context) {

    //set the args
    IFBMemoryArenaPushBytes push;
    push.context = arena_context;

    //do the push
    ifb_memory::arena_push_step_0_validate_args            (push);
    ifb_memory::arena_push_step_1_cache_manager_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_absolute      (push);

    //get the pointer
    const IFBPtr pointer = push.result
        ? push.context->memory.absolute_pointer
        : NULL;

    //we're done
    return(pointer);
}

const IFBB8
ifb_memory::arena_pull_bytes(
    IFBMemoryArenaContext* arena_context) {

    return(false);
}
