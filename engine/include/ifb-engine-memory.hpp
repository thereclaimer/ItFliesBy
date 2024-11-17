#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-tag.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

typedef ifb_u32 ifb_handle_memory_t;

#define IFB_ENGINE_MEMORY_HANDLE_INVALID 0

namespace ifb_engine {

    ifb_api const ifb_memory memory_pointer_from_page_offset (const ifb_u32 page_number, const ifb_u32 page_offset);
    ifb_api const ifb_memory memory_pointer_from_page        (const ifb_u32 page_number);
    ifb_api const ifb_memory memory_pointer_from_handle      (const ifb_u32 handle);

    ifb_api const ifb_handle_memory_t memory_handle            (const ifb_u32 page_number,const ifb_u32 page_offset);
    ifb_api const ifb_b8              memory_handle_valid      (const ifb_handle_memory_t memory_handle);
    ifb_api const ifb_u32             memory_size_page_aligned (const ifb_u32 size);
    ifb_api const ifb_u32             memory_page_count        (const ifb_u32 size);
    ifb_api const ifb_u32             memory_page_size         (const ifb_u32 page_count);
    ifb_api const ifb_u32             memory_page_commit       (const ifb_u32 page_count);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

typedef ifb_index ifb_index_arena_t;

struct IFBEngineMemoryArena {
    ifb_index_arena_t arena_index;
    ifb_index_tag_t   tag_index;
    ifb_u32           page_start;
    ifb_u32           page_count;
};

namespace ifb_engine {

    ifb_api const ifb_index_arena_t
    memory_arena_commit(
        const ifb_cstr arena_tag,
        const ifb_u32  arena_size_minimum); 

    ifb_api const ifb_handle_memory_t  memory_arena_handle     (const ifb_index_arena_t arena_index, const ifb_u32 offset);
    ifb_api const ifb_b8               memory_arena_valid      (const ifb_index_arena_t arena_index);
    ifb_api const ifb_u32              memory_arena_page_start (const ifb_index_arena_t arena_index);
    ifb_api const ifb_u32              memory_arena_page_count (const ifb_index_arena_t arena_index);
    ifb_api const ifb_u32              memory_arena_tag_index  (const ifb_index_arena_t arena_index);
    ifb_api const ifb_cstr             memory_arena_tag_value  (const ifb_index_arena_t arena_index);

};

#endif //IFB_ENGINE_MEMORY_HPP