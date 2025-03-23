
#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-internal.cpp"
#include "ifb-memory-arena-commit.cpp"
#include "ifb-memory-arena-decommit.cpp"
#include "ifb-memory-arena-push.cpp"

const IFBB8
ifb_memory::arena_commit(
    IFBMemoryArena* arena) {
    
    //sanity check
    ifb_macro_assert(arena);

    //set the arena values
    IFBMemoryArenaCommit commit;
    commit.arena.start_stack = arena->stack;
    commit.arena.id_manager  = arena->ids.manager;

    //commit steps
    ifb_memory::arena_commit_step_0_validate_args            (commit);
    ifb_memory::arena_commit_step_1_cache_manager_properties (commit);
    ifb_memory::arena_commit_step_2_find_free_arena          (commit);
    ifb_memory::arena_commit_step_3_calculate_arena_start    (commit);
    ifb_memory::arena_commit_step_4_commit_memory            (commit);
    ifb_memory::arena_commit_step_5_update_arrays            (commit);

    //update the arena
    arena->ids.arena = commit.arena.id_arena;

    //we're done
    return(commit.result ? true : false);
}

const IFBB8
ifb_memory::arena_decommit(
    IFBMemoryArena* arena) {
  
    //sanity check
    ifb_macro_assert(arena);

    //set the args
    IFBMemoryArenaDecommit decommit;
    decommit.args.handle_stack   = arena->stack;
    decommit.args.handle_manager = arena->ids.manager; 
    decommit.args.handle_arena   = arena->ids.arena;

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
    const IFBMemoryArena* arena) {


    return(false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
    const IFBMemoryArena* arena,
    const IFBU32          size,
    const IFBU32          alignment) {

    //sanity check
    ifb_macro_assert(arena);

    //set the args
    IFBMemoryArenaPushBytes push;
    push.args.handle_stack   = arena->stack;
    push.args.handle_manager = arena->ids.manager; 
    push.args.handle_arena   = arena->ids.arena;
    push.args.size           = size;
    push.args.alignment      = alignment;

    //do the push
    ifb_memory::arena_push_step_0_validate_args            (push);
    ifb_memory::arena_push_step_1_cache_manager_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_relative      (push);

    //get the result
    const IFBU32 result = push.result
        ? push.arena_memory.relative_offset
        : IFB_MEMORY_ARENA_OFFSET_INVALID;

    //we're done
    return(result);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
    const IFBMemoryArena* arena,
    const IFBU32          size,
    const IFBU32          alignment) {

    //sanity check
    ifb_macro_assert(arena);

    //set the args
    IFBMemoryArenaPushBytes push;
    push.args.handle_stack   = arena->stack;
    push.args.handle_manager = arena->ids.manager; 
    push.args.handle_arena   = arena->ids.arena;
    push.args.size           = size;
    push.args.alignment      = alignment;

    //do the push
    ifb_memory::arena_push_step_0_validate_args            (push);
    ifb_memory::arena_push_step_1_cache_manager_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_absolute      (push);

    //get the result
    const IFBPtr result = push.result
        ? push.arena_memory.absolute_pointer
        : NULL;

    //we're done
    return(result);
}

const IFBB8
ifb_memory::arena_pull_bytes(
    const IFBMemoryArena* arena,
    const IFBU32          size,
    const IFBU32          alignment) {


    return(false);
}
