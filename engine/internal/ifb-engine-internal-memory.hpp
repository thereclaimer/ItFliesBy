#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBEngineMemoryReservation {
    ifb_size   platform_allocation_granularity;
    ifb_size   platform_page_size;
    ifb_size   size_total;
    ifb_size   size_used;
    ifb_memory start;
};

namespace ifb_engine {

    ifb_internal const ifb_b8 memory_reserve (IFBEngineMemoryReservation& reservation_ref);
    ifb_internal const ifb_b8 memory_release (IFBEngineMemoryReservation& reservation_ref);
};

/**********************************************************************************/
/* ARENA BLOCK                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_BLOCK_COUNT_MAX             128
#define IFB_ENGINE_MEMORY_ARENA_BLOCK_TAG_LENGTH            32
#define IFB_ENGINE_MEMORY_ARENA_BLOCK_TABLE_TAG_BUFFER_SIZE IFB_ENGINE_MEMORY_ARENA_BLOCK_COUNT_MAX * IFB_ENGINE_MEMORY_ARENA_BLOCK_TAG_LENGTH
#define IFB_ENGINE_MEMORY_ARENA_BLOCK_INDEX_INVALID         256

typedef ifb_b8 IFBEngineMemoryArenaBlockIndex;

struct IFBEngineMemoryArenaBlock {
    ifb_size arena_starting_offset;
    ifb_size arena_page_count;
    ifb_size arena_count;
    ifb_cstr tag;
};

struct IFBEngineMemoryArenaBlockTable {
    ifb_u8   block_count;
    ifb_char tag_buffer[IFB_ENGINE_MEMORY_ARENA_BLOCK_TABLE_TAG_BUFFER_SIZE];
    struct {
        ifb_size array_arena_page_count      [IFB_ENGINE_MEMORY_ARENA_BLOCK_COUNT_MAX];
        ifb_size array_arena_count           [IFB_ENGINE_MEMORY_ARENA_BLOCK_COUNT_MAX];
        ifb_size array_arena_starting_offset [IFB_ENGINE_MEMORY_ARENA_BLOCK_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    const IFBEngineMemoryArenaBlockIndex 
    memory_arena_block_create(
        const ifb_cstr tag, 
        const ifb_size arena_size,
        const ifb_size arena_count);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM 4096

typedef ifb_u64 IFBEngineMemoryArenaHandle;

union IFBEngineMemoryArenaId {
    struct {
        ifb_index arena_index;
        ifb_index block_index;        
    };
    IFBEngineMemoryArenaHandle handle;
};

struct IFBEngineMemoryArena {
    IFBEngineMemoryArenaId id;
    ifb_size               size_used;
    ifb_b8                 committed;
};

struct IFBEngineMemoryArenaTable {
    ifb_u32 arena_count;
    ifb_u32 arena_minimum_size;
    struct {
        ifb_b8  array_committed   [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 array_block_index [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
        ifb_u32 array_size_used   [IFB_ENGINE_MEMORY_ARENA_COUNT_MAX];
    } columns;
};

namespace ifb_engine {

    r_internal const IFBEngineMemoryArenaHandle memory_arena_commit   (const IFBEngineMemoryArenaBlockIndex arena_block_index);    
    r_internal const ifb_b8                     memory_arena_decommit (const IFBEngineMemoryArenaHandle arena_handle);    

    r_internal r_memory memory_arena_push(const IFBEngineMemoryArenaHandle arena_handle, const ifb_size size);
    r_internal r_memory memory_arena_pull(const IFBEngineMemoryArenaHandle arena_handle, const ifb_size size);
    
    r_internal r_memory memory_arena_start(const IFBEngineMemoryArenaHandle arena_handle);
};

/**********************************************************************************/
/* ENGINE MEMORY                                                                  */
/**********************************************************************************/

struct IFBEngineMemory {
    IFBEngineMemoryReservation reservation;
    struct {
        IFBEngineMemoryArenaBlockTable arena_block;
        IFBEngineMemoryArenaTable      arena;
    } tables;
};


#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP