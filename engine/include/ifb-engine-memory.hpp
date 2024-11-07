#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

typedef ifb_u32 IFBEngineMemoryTableIndexArenaHeader;
typedef ifb_u32 IFBEngineMemoryTableIndexArenaDetail;
typedef ifb_u32 IFBEngineMemoryTableIndexArenaPool;

struct IFBEngineMemoryArenaPoolHandle {
    ifb_u32 header_index;    
    ifb_u32 detail_start_index;
};

struct IFBEngineMemoryArenaHandle {
    ifb_u32 detail_index;
};

struct IFBEngineMemoryHandle {
    ifb_u32 detail_index;
    ifb_u32 page_number;
    ifb_u32 page_offset;
    ifb_u32 size;
};

#define IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX             128
#define IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH            32
#define IFB_ENGINE_MEMORY_ARENA_HEADER_TABLE_TAG_BUFFER_SIZE IFB_ENGINE_MEMORY_ARENA_HEADER_COUNT_MAX * IFB_ENGINE_MEMORY_ARENA_HEADER_TAG_LENGTH
#define IFB_ENGINE_MEMORY_ARENA_HEADER_INDEX_INVALID         256

#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX            4096
#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM         4096
#define IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID 4096

namespace ifb_engine {

    inline const ifb_size memory_size_kilobytes(const ifb_size size) { return(size * 1024);               }
    inline const ifb_size memory_size_megabytes(const ifb_size size) { return(size * 1024 * 1024);        }
    inline const ifb_size memory_size_gigabytes(const ifb_size size) { return(size * 1024 * 1024 * 1024); }

    inline const ifb_b8 memory_arena_detail_valid(IFBEngineMemoryArenaHandle& arena_handle_ref) { return(arena_handle_ref.detail_index < IFB_ENGINE_MEMORY_ARENA_DETAIL_INDEX_INVALID); }

    inline const ifb_size 
    memory_arena_align(const ifb_size size) { 
        
        const ifb_size size_aligned = ifb_engine_macro_align_a_to_b(
            size,
            IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM);
    
        return(size_aligned);
    }

    //arena pool
    ifb_external const ifb_b8
    memory_arena_create_pool(
        const ifb_cstr                           in_arena_tag,
        const ifb_size                           in_arena_size,
        const ifb_size                           in_arena_count,
              IFBEngineMemoryArenaPoolHandle&   out_arena_pool_handle_ref);

    //arena control
    ifb_external const ifb_b8     memory_arena_commit                 (IFBEngineMemoryArenaPoolHandle& in_arena_pool_handle_ref, IFBEngineMemoryArenaHandle&    out_arena_handle_ref);
    ifb_external const ifb_b8     memory_arena_decommit               (IFBEngineMemoryArenaHandle& arena_handle_ref);
    ifb_external const ifb_b8     memory_arena_reset                  (IFBEngineMemoryArenaHandle& arena_handle_ref);
    
    //arena push
    ifb_external const ifb_b8     memory_arena_push                   (IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, const ifb_size in_memory_size, IFBEngineMemoryHandle& out_memory_handle_ref);
    ifb_external const ifb_memory memory_arena_push_immediate         (IFBEngineMemoryArenaHandle& memory_arena_handle_ref,    const ifb_size memory_size);
    ifb_external const ifb_b8     memory_arena_push_aligned           (IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, const ifb_size in_memory_size, const ifb_size in_memory_alignment,IFBEngineMemoryHandle& out_memory_handle_ref);
    ifb_external const ifb_memory memory_arena_push_aligned_immediate (IFBEngineMemoryArenaHandle& memory_arena_handle_ref,    const ifb_size memory_size,    const ifb_size memory_alignment);

    //arena pull    
    ifb_external const ifb_b8     memory_arena_pull                   (IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, const ifb_size in_memory_size, IFBEngineMemoryHandle& out_memory_handle_ref);
    ifb_external const ifb_memory memory_arena_pull_immediate         (IFBEngineMemoryArenaHandle& memory_arena_handle_ref,    const ifb_size memory_size);
    ifb_external const ifb_b8     memory_arena_pull_aligned           (IFBEngineMemoryArenaHandle& in_memory_arena_handle_ref, const ifb_size in_memory_size, const ifb_size in_memory_alignment,IFBEngineMemoryHandle& out_memory_handle_ref);
    ifb_external const ifb_memory memory_arena_pull_aligned_immediate (IFBEngineMemoryArenaHandle& memory_arena_handle_ref,    const ifb_size memory_size,    const ifb_size memory_alignment);

    //pointers    
    ifb_external const ifb_memory memory_pointer(IFBEngineMemoryHandle& memory_handle_ref);
};

#define ifb_engine_memory_arena_push_array( \
     in_arena_handle_ref,                   \
     in_count,                              \
     in_type,                               \
    out_memory_handle_ref)                  \
                                            \
    ifb_engine::memory_arena_push(          \
        in_arena_handle_ref,                \
        sizeof(in_type) * in_count,         \
        out_memory_handle_ref)              \

#define ifb_engine_memory_arena_push_array_immediate( \
    arena_handle_ref,                                 \
    count,                                            \
    type)                                             \
                                                      \
    (type*)ifb_engine::memory_arena_push_immediate(   \
        arena_handle_ref,                             \
        sizeof(type) * count)                         \

#endif //IFB_ENGINE_MEMORY_HPP