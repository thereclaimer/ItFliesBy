#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

typedef ifb_index IFBEngineMemoryArenaTableIndex;
typedef ifb_index IFBEngineMemoryArenaIndex;

#define IFB_ENGINE_MEMORY_TAG_SIZE_MAX       32
#define IFB_ENGINE_MEMORY_INDEX_INVALID      SIZE_MAX
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM 4096

#define ifb_engine_memory_size_kilobytes(size) size * 1024
#define ifb_engine_memory_size_megabytes(size) size * ifb_engine_memory_size_kilobytes(1024)
#define ifb_engine_memory_size_gigabytes(size) size * ifb_engine_memory_size_megabytes(1024)

#define ifb_engine_memory_align_to_arena(size) ifb_engine_macro_align_a_to_b(size,IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM)

namespace ifb_engine {

    inline const ifb_size memory_size_kilobytes(const ifb_size size) { return(size * 1024);               }
    inline const ifb_size memory_size_megabytes(const ifb_size size) { return(size * 1024 * 1024);        }
    inline const ifb_size memory_size_gigabytes(const ifb_size size) { return(size * 1024 * 1024 * 1024); }

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