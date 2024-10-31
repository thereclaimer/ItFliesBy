#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

typedef ifb_u8  IFBEngineMemoryArenaHeaderIndex;
typedef ifb_u32 IFBEngineMemoryArenaDetailIndex;

struct IFBEngineMemoryArena {
    IFBEngineMemoryArenaHeaderIndex header_index;
    IFBEngineMemoryArenaDetailIndex detail_index;
};

#define IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX             128
#define IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH            32
#define IFB_ENGINE_MEMORY_ARENA_HEADER_TABLE_TAG_BUFFER_SIZE IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX * IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH
#define IFB_ENGINE_MEMORY_ARENA_HEADER_INDEX_INVALID         256

#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX     4096
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM  4096
#define IFB_ENGINE_MEMORY_ARENA_INDEX_INVALID 4096

#define ifb_engine_memory_size_kilobytes(size) size * 1024
#define ifb_engine_memory_size_megabytes(size) size * ifb_engine_memory_size_kilobytes(1024)
#define ifb_engine_memory_size_gigabytes(size) size * ifb_engine_memory_size_megabytes(1024)

#define ifb_engine_memory_align_to_arena(size) ifb_engine_macro_align_a_to_b(size,IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM)

namespace ifb_engine {

    inline const ifb_size memory_size_kilobytes(const ifb_size size) { return(size * 1024);               }
    inline const ifb_size memory_size_megabytes(const ifb_size size) { return(size * 1024 * 1024);        }
    inline const ifb_size memory_size_gigabytes(const ifb_size size) { return(size * 1024 * 1024 * 1024); }

    inline const ifb_size 
    memory_arena_align(const ifb_size size) { 
        
        const ifb_size size_aligned = ifb_engine_macro_align_a_to_b(
            size,
            IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM);
    
        return(size_aligned);
    }

    ifb_external const ifb_b8
    memory_arena_create_pool(
        const ifb_cstr                     in_arena_tag,
        const ifb_size                     in_arena_size,
        const ifb_size                     in_arena_count,
              IFBEngineMemoryArena&       out_arena_start_ref);

    ifb_external const ifb_memory memory_arena_commit(IFBEngineMemoryArena& arena_ref);
    
    ifb_external const ifb_memory memory_arena_push(IFBEngineMemoryArena& arena_ref, const ifb_size size);
    ifb_external const ifb_memory memory_arena_pull(IFBEngineMemoryArena& arena_ref, const ifb_size size);
    
    ifb_external const ifb_memory memory_arena_push_aligned(IFBEngineMemoryArena& arena_ref, const ifb_size size, const ifb_size alignment);
    ifb_external const ifb_memory memory_arena_pull_aligned(IFBEngineMemoryArena& arena_ref, const ifb_size size, const ifb_size alignment);
};

#endif //IFB_ENGINE_MEMORY_HPP