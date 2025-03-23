
#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager-internal.cpp"

const IFBMemoryArenaIndex
ifb_memory::arena_commit(
    IFBMemoryManager* memory_manager) {
    
    //set the manager cache values
    IFBMemoryManagerArenaCommit commit;
    commit.manager_cache.start_memory          = (IFBAddr)memory_manager;
    commit.manager_cache.start_reservation     = memory_manager->reserved_memory_start;
    commit.manager_cache.arena_count           = memory_manager->count_arenas;
    commit.manager_cache.arena_size            = memory_manager->size_arena;
    commit.manager_cache.offset_arena_start    = memory_manager->arena_array_offsets.start;
    commit.manager_cache.offset_arena_position = memory_manager->arena_array_offsets.position;

    //commit steps
    ifb_memory::manager_arena_commit_step_0_validate_args             (commit);
    ifb_memory::manager_arena_commit_step_1_load_arena_start_array    (commit);
    ifb_memory::manager_arena_commit_step_2_find_free_arena           (commit);
    ifb_memory::manager_arena_commit_step_3_calculate_arena_start     (commit);
    ifb_memory::manager_arena_commit_step_4_commit_memory             (commit);
    ifb_memory::manager_arena_commit_step_5_load_arena_position_array (commit);
    ifb_memory::manager_arena_commit_step_6_update_arrays             (commit);

    //get the result
    const IFBMemoryArenaIndex arena_index = commit.result
        ? commit.arena.index
        : IFB_MEMORY_ARENA_INDEX_INVALID;

    //we're done
    return(arena_index);
}

const IFBB8
ifb_memory::arena_decommit(
          IFBMemoryManager*   memory_manager,
    const IFBMemoryArenaIndex arena_index) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}

const IFBB8
ifb_memory::arena_reset(
          IFBMemoryManager*   memory_manager,
    const IFBMemoryArenaIndex arena_index,
    const IFBU32              size,
    const IFBU32              alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
          IFBMemoryManager*   memory_manager,
    const IFBMemoryArenaIndex arena_index,
    const IFBU32              size,
    const IFBU32              alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(0);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
          IFBMemoryManager*   memory_manager,
    const IFBMemoryArenaIndex arena_index,
    const IFBU32              size,
    const IFBU32              alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(NULL);
}

const IFBB8
ifb_memory::arena_pull_bytes(
          IFBMemoryManager*   memory_manager,
    const IFBMemoryArenaIndex arena_index,
    const IFBU32              size,
    const IFBU32              alignment) {

    //validate the memory manager
    ifb_memory::manager_assert_valid(memory_manager);

    return(false);
}
