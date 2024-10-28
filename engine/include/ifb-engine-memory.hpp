#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"

typedef ifb_index IFBEngineMemoryArenaTableIndex;
typedef ifb_index IFBEngineMemoryArenaIndex;

#define IFB_ENGINE_MEMORY_TAG_SIZE_MAX       32
#define IFB_ENGINE_MEMORY_INDEX_INVALID      SIZE_MAX
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM 4096

namespace ifb_engine {

    ifb_external const IFBEngineMemoryArenaTableIndex
    memory_arena_table_create(
        const ifb_cstr arena_table_tag,
        const ifb_size arena_size_minimum,
        const ifb_size arena_count);

    ifb_external const IFBEngineMemoryArenaIndex 
    memory_arena_commit(const IFBEngineMemoryArenaTableIndex arena_table_index);
    
    ifb_external const ifb_memory memory_arena_push(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    ifb_external const ifb_memory memory_arena_pull(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size);
    
    ifb_external const ifb_memory memory_arena_push_aligned(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size, const ifb_size alignment);
    ifb_external const ifb_memory memory_arena_pull_aligned(const IFBEngineMemoryArenaIndex arena_index, const ifb_size size, const ifb_size alignment);
};

#endif //IFB_ENGINE_MEMORY_HPP