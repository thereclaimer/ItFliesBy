#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* PLATFORM INFO                                                                  */
/**********************************************************************************/

struct IFBEngineMemoryPlatformInfo {
    ifb_size allocation_granularity;
    ifb_size page_size;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES 4

struct IFBEngineMemoryReservation {
    ifb_size   size_total;
    ifb_size   size_used;
    ifb_memory start;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_reserve (IFBEngineMemoryReservation& reservation_ref);
    ifb_internal const ifb_b8 memory_release (IFBEngineMemoryReservation& reservation_ref);
};

/**********************************************************************************/
/* ARENA POOL                                                                     */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX             128
#define IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH            32
#define IFB_ENGINE_MEMORY_ARENA_POOL_TABLE_TAG_BUFFER_SIZE IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX * IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH
#define IFB_ENGINE_MEMORY_ARENA_POOL_INDEX_INVALID         256

typedef ifb_u8 IFBEngineMemoryArenaPoolIndex;

struct IFBEngineMemoryArenaPool {
    ifb_size reservation_offset;
    ifb_size arena_size;
    ifb_size arena_count;
    ifb_cstr tag;
};

struct IFBEngineMemoryArenaPoolTable {
    ifb_u8   pool_count_current;
    ifb_u8   pool_count_max;
    ifb_char tag_buffer[IFB_ENGINE_MEMORY_ARENA_POOL_TABLE_TAG_BUFFER_SIZE];
    struct {
        ifb_size array_arena_size [IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX];
        ifb_size array_arena_count[IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX];
        ifb_size array_offset     [IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    ifb_internal inline const ifb_b8
    memory_arena_pool_is_valid(
        const IFBEngineMemoryArenaPoolIndex arena_pool_index) {

        return(arena_pool_index != IFB_ENGINE_MEMORY_ARENA_POOL_INDEX_INVALID);
    }

    ifb_internal const ifb_b8 
    memory_arena_pool_table_create(IFBEngineMemoryArenaPoolTable& arena_pool_table_ref);

    ifb_internal const IFBEngineMemoryArenaPoolIndex 
    memory_arena_pool_create(
        const ifb_cstr tag, 
        const ifb_size arena_size,
        const ifb_size arena_count);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM 4096

typedef ifb_u32 IFBEngineMemoryArenaIndex;

struct IFBEngineMemoryArena {
    IFBEngineMemoryArenaIndex index;
    ifb_size                  size_used;
    ifb_b8                    committed;
};

struct IFBEngineMemoryArenaTable {
    ifb_u32 arena_count_current;
    ifb_u32 arena_count_max;
    ifb_u32 arena_minimum_size;
    struct {
        ifb_b8  array_committed [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 array_pool_index[IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 array_size_used [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    r_internal const IFBEngineMemoryArenaIndex memory_arena_commit   (const IFBEngineMemoryArenaPoolIndex arena_pool_index);    
    r_internal const ifb_b8                    memory_arena_decommit (const IFBEngineMemoryArenaIndex     arena_index);    

    r_internal const r_memory memory_arena_push  (const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    r_internal const r_memory memory_arena_pull  (const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    r_internal const r_memory memory_arena_start (const IFBEngineMemoryArenaIndex arena_index);
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    struct {
        IFBEngineMemoryArenaPoolTable arena_pool;
        IFBEngineMemoryArenaTable     arena;
    } tables;
    IFBEngineMemoryReservation  reservation;
    IFBEngineMemoryPlatformInfo platform_info;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_manager_start_up  (IFBEngineMemoryManager& memory_manager_ref);
    ifb_internal const ifb_b8 memory_manager_shut_down (IFBEngineMemoryManager& memory_manager_ref);

};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP