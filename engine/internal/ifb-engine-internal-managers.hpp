#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* TAG MANAGER                                                                    */
/**********************************************************************************/

struct IFBEngineTagManager {
    ifb_u32     tag_c_str_length;
    ifb_u32     tag_count_max;
    struct {
        ifb_address start;
        ifb_u32     offset_char_buffer; // ifb_char
        ifb_u32     offset_hash_array;  // IFBHash
        IFBIDCommit id;
    } commit;
};

namespace ifb_engine {

    ifb_void
    tag_manager_initialize(
              IFBEngineTagManager* tag_manager_ptr,
        const ifb_u32              tag_c_str_length,
        const ifb_u32              tag_count_max);

    const IFBTagId  tag_manager_reserve_tag             (IFBEngineTagManager* tag_manager_ptr, const ifb_cstr tag_c_str);
          ifb_void  tag_manager_release_tag             (IFBEngineTagManager* tag_manager_ptr, const IFBTagId tag_id);
    const ifb_cstr  tag_manager_get_tag_c_str           (IFBEngineTagManager* tag_manager_ptr, const IFBTagId tag_id);
    const IFBHash   tag_manager_get_hash                (IFBEngineTagManager* tag_manager_ptr, const IFBTagId tag_id);
          ifb_char* tag_manager_get_pointer_char_buffer (IFBEngineTagManager* tag_manager_ptr);
          IFBHash*  tag_manager_get_pointer_hash_array  (IFBEngineTagManager* tag_manager_ptr);
};

/**********************************************************************************/
/* ARENA MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineArenaManager {
    ifb_u32     arena_minimum_size;
    ifb_u32     arena_minimum_pages;
    ifb_u32     arena_count_max;
    ifb_u32     arena_count_committed;
    struct {
        ifb_address start;
        ifb_u32     offset_commit_id_array; // IFBCommitId
        ifb_u32     offset_tag_id_array;    // IFBTagId
        IFBIDCommit id;
    } commit;
};

namespace ifb_engine {

    ifb_void 
    arena_manager_initialize(
              IFBEngineArenaManager* arena_manager_ptr,
        const ifb_u32                arena_minimum_size,
        const ifb_u32                arena_count_max);

    const IFBIDArena 
    arena_manager_commit_arena(
              IFBEngineArenaManager* arena_manager_ptr, 
        const IFBIDTag               arena_tag_id,
        const ifb_u32                arena_commit_size_minimum);

    const ifb_u32      arena_manager_align_size_to_arena         (IFBEngineArenaManager* arena_manager_ptr, const ifb_u32 size);
    const IFBIDCommit  arena_manager_get_arena_commit_id         (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id);
    const IFBIDTag     arena_manager_get_arena_tag_id            (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_u32      arena_manager_get_arena_size              (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_u32      arena_manager_get_arena_start             (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_u32      arena_manager_get_arena_pointer           (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_u32      arena_manager_get_arena_pointer           (IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena arena_id, const ifb_u32 offset);
          IFBIDCommit* arena_manager_get_pointer_commit_id_array (IFBEngineArenaManager* arena_manager_ptr);
          IFBIDTag*    arena_manager_get_pointer_tag_id_array    (IFBEngineArenaManager* arena_manager_ptr);
};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP