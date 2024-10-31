#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

typedef ifb_u8  IFBEngineMemoryArenaPoolIndex;
typedef ifb_u32 IFBEngineMemoryArenaIndex;

#define IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX             128
#define IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH            32
#define IFB_ENGINE_MEMORY_ARENA_POOL_TABLE_TAG_BUFFER_SIZE IFB_ENGINE_MEMORY_ARENA_POOL_COUNT_MAX * IFB_ENGINE_MEMORY_ARENA_POOL_TAG_LENGTH
#define IFB_ENGINE_MEMORY_ARENA_POOL_INDEX_INVALID         256

#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX     4096
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM  4096
#define IFB_ENGINE_MEMORY_ARENA_INDEX_INVALID 4096

#define ifb_engine_memory_size_kilobytes(size) size * 1024
#define ifb_engine_memory_size_megabytes(size) size * ifb_engine_memory_size_kilobytes(1024)
#define ifb_engine_memory_size_gigabytes(size) size * ifb_engine_memory_size_megabytes(1024)

#define ifb_engine_memory_align_to_arena(size) ifb_engine_macro_align_a_to_b(size,IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM)

struct IFBEngineMemoryArenaPool {
    IFBEngineMemoryArenaPoolIndex index;
    IFBEngineMemoryArenaIndex     starting_arena_index;
    ifb_size                      reservation_offset;
    ifb_size                      arena_size;
    ifb_size                      arena_count;
    ifb_cstr                      tag;
};

namespace ifb_engine {

    inline const ifb_size memory_size_kilobytes(const ifb_size size) { return(size * 1024);               }
    inline const ifb_size memory_size_megabytes(const ifb_size size) { return(size * 1024 * 1024);        }
    inline const ifb_size memory_size_gigabytes(const ifb_size size) { return(size * 1024 * 1024 * 1024); }

    inline const ifb_b8
    memory_arena_pool_is_valid(
        const IFBEngineMemoryArenaPoolIndex arena_pool_index) {

        return(arena_pool_index != IFB_ENGINE_MEMORY_ARENA_POOL_INDEX_INVALID);
    }

    ifb_external const ifb_b8 
    memory_arena_pool_create(IFBEngineMemoryArenaPool& arena_pool_ref);

    ifb_external const IFBEngineMemoryArenaIndex 
    memory_arena_commit(const IFBEngineMemoryArenaPoolIndex arena_pool_index);
    
    ifb_external const ifb_memory memory_arena_push(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    ifb_external const ifb_memory memory_arena_pull(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    
    ifb_external const ifb_memory memory_arena_push_aligned(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size, const ifb_size alignment);
    ifb_external const ifb_memory memory_arena_pull_aligned(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size, const ifb_size alignment);
};

#endif //IFB_ENGINE_MEMORY_HPP