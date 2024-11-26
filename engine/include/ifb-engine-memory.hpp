#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include <ifb-common.hpp>

#include "ifb-engine-tag.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemoryHandle {
    ifb_u32 value;
};

struct IFBEngineMemoryCommit {
    ifb_u32               page_start;
    ifb_u32               page_count;
    IFBEngineMemoryHandle handle;
    ifb_memory            pointer;
};

#define IFB_ENGINE_MEMORY_HANDLE_INVALID 0

namespace ifb_engine {

    ifb_api const ifb_memory memory_pointer_from_page_offset (const ifb_u32 page_number, const ifb_u32 page_offset);
    ifb_api const ifb_memory memory_pointer_from_page        (const ifb_u32 page_number);
    ifb_api const ifb_memory memory_pointer_from_handle      (const IFBEngineMemoryHandle memory_handle);

    ifb_api ifb_void
    memory_pointer_from_handle_count(
        const ifb_u32                in_handles_count,
        const IFBEngineMemoryHandle* in_handles_ptr,
              ifb_memory*           out_memory_ptr);


    ifb_api const IFBEngineMemoryHandle memory_handle            (const ifb_u32 page_number,const ifb_u32 page_offset);
    ifb_api const ifb_b8                memory_handle_valid      (const IFBEngineMemoryHandle memory_handle);
    ifb_api const ifb_u32               memory_size_page_aligned (const ifb_u32 size);
    ifb_api const ifb_u32               memory_page_count        (const ifb_u32 size);
    ifb_api const ifb_u32               memory_page_size         (const ifb_u32 page_count);
    ifb_api const IFBEngineMemoryCommit memory_commit            (const ifb_u32 commit_size_minimum);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM ifb_macro_size_kilobytes(4)
#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_INVALID      4096

struct IFBEngineArenaId {
    struct  {
        IFBEngineTableIndexTag   tag;
        IFBEngineTableIndexArena arena;
    } table_indexes;
};

struct IFBEngineArena {
    IFBEngineArenaId      arena_id;
    ifb_cstr              tag_value;
    ifb_u32               page_start;
    ifb_u32               page_count;
    ifb_u32               memory_size;
    IFBEngineMemoryHandle memory_handle;          
};

namespace ifb_engine {

    ifb_api const ifb_b8
    memory_arena_commit(
        const ifb_cstr           in_arena_tag,
        const ifb_u32            in_arena_size_minimum,
              IFBEngineArenaId& out_arena_id_ref); 

    ifb_api const IFBEngineMemoryHandle memory_arena_handle     (const IFBEngineArenaId arena_id, const ifb_u32 offset);
    ifb_api const ifb_b8                memory_arena_valid      (const IFBEngineArenaId arena_id);
    ifb_api const ifb_u32               memory_arena_page_start (const IFBEngineArenaId arena_id);
    ifb_api const ifb_u32               memory_arena_page_count (const IFBEngineArenaId arena_id);
    ifb_api const IFBEngineTagId        memory_arena_tag_id     (const IFBEngineArenaId arena_id);
    ifb_api const ifb_cstr              memory_arena_tag_value  (const IFBEngineArenaId arena_id);

};

/**********************************************************************************/
/* BLOCK                                                                          */
/**********************************************************************************/

#endif //IFB_ENGINE_MEMORY_HPP