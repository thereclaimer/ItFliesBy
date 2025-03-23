
#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager-internal.cpp"
#include "ifb-memory-arena-commit.cpp"
#include "ifb-memory-arena-decommit.cpp"

const IFBB8
ifb_memory::arena_commit(
    IFBMemoryArena* arena) {
    
    //sanity check
    ifb_macro_assert(arena);

    //set the handle values
    IFBMemoryArenaCommit commit;
    commit.handles.stack   = arena->handle_stack;
    commit.handles.manager = arena->handle_manager; 
 
    //commit steps
    ifb_memory::arena_commit_step_0_validate_args            (commit);
    ifb_memory::arena_commit_step_1_cache_manager_properties (commit);
    ifb_memory::arena_commit_step_2_find_free_arena          (commit);
    ifb_memory::arena_commit_step_3_calculate_arena_start    (commit);
    ifb_memory::arena_commit_step_4_commit_memory            (commit);
    ifb_memory::arena_commit_step_5_update_arrays            (commit);

    //update the arena
    arena->handle_arena = commit.arena.index;

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
    decommit.args.handle_stack   = arena->handle_stack;
    decommit.args.handle_manager = arena->handle_manager; 
    decommit.args.handle_arena   = arena->handle_arena;

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

    return(0);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
    const IFBMemoryArena* arena,
    const IFBU32          size,
    const IFBU32          alignment) {

    return(NULL);
}

const IFBB8
ifb_memory::arena_pull_bytes(
    const IFBMemoryArena* arena,
    const IFBU32          size,
    const IFBU32          alignment) {


    return(false);
}
