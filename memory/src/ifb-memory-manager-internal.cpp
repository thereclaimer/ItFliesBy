#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManagerArrays;
struct IFBMemoryManagerInit;
struct IFBMemoryManagerArenaPushBytes;

namespace ifb_memory {


    //validation
    IFBVoid manager_assert_valid                                   (IFBMemoryManagerInternal* memory_manager);

    //arena push bytes
    IFBVoid manager_arena_push_step_0_validate_args                (IFBMemoryManagerArenaPushBytes& push_ref);
    IFBVoid manager_arena_push_step_1_cache_manager_properties     (IFBMemoryManagerArenaPushBytes& push_ref);
    IFBVoid manager_arena_push_step_2_load_arrays                  (IFBMemoryManagerArenaPushBytes& push_ref);
    IFBVoid manager_arena_push_step_3_push_bytes_relative          (IFBMemoryManagerArenaPushBytes& push_ref);
    IFBVoid manager_arena_push_step_3_push_bytes_absolute          (IFBMemoryManagerArenaPushBytes& push_ref);

};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/


struct IFBMemoryManagerArenaPushBytes {
    struct {
        IFBAddr handle_stack;
        IFBU32  handle_manager;
        IFBU32  handle_arena;
        IFBU32  size;
        IFBU32  alignment;
    } args;
    struct {
        IFBAddr start_memory;
        IFBU32  arena_size;
        IFBU32  arena_count;
        IFBU32  offset_array_arena_start;
        IFBU32  offset_array_arena_position;
    } manager_cache;
    struct {
        IFBAddr* start;
        IFBU32*  position;
    } arena_arrays;
    union {
        IFBU32 relative_offset;
        IFBPtr absolute_pointer;
    } arena_memory;
};


/**********************************************************************************/
/* VALIDATION                                                                     */
/**********************************************************************************/

inline IFBVoid
ifb_memory::manager_assert_valid(
    IFBMemoryManagerInternal* memory_manager) {

    ifb_macro_assert(memory_manager);
    ifb_macro_assert(memory_manager->reserved_memory_start        != 0);
    ifb_macro_assert(memory_manager->count_arenas                 != 0);
    ifb_macro_assert(memory_manager->size_arena                   != 0);
    ifb_macro_assert(memory_manager->size_page                    != 0);
    ifb_macro_assert(memory_manager->size_granularity             != 0);
    ifb_macro_assert(memory_manager->offset_arena_array_start     != 0);
    ifb_macro_assert(memory_manager->offset_arena_array_position  != 0);
}