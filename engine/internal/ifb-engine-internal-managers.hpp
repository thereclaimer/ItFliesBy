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
        IFBHND char_buffer; // ifb_char
        IFBHND hash_array;  // IFBHash
    } handles;
    IFBIDCommit commit_id;
};

namespace ifb_engine {

    ifb_void
    tag_manager_initialize(
              IFBEngineTagManager* tag_manager_ptr,
              IFBEngineMemory*     memory_ptr,
        const ifb_u32              tag_c_str_length,
        const ifb_u32              tag_count_max);

    const IFBIDTag  tag_manager_reserve_tag             (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr, const ifb_cstr tag_c_str);
          ifb_void  tag_manager_release_tag             (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDTag& tag_id_ref);
    const ifb_cstr  tag_manager_get_tag_c_str           (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDTag& tag_id_ref);
    const IFBHash   tag_manager_get_hash                (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDTag& tag_id_ref);
          ifb_char* tag_manager_get_pointer_char_buffer (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr);
          IFBHash*  tag_manager_get_pointer_hash_array  (const IFBEngineTagManager* tag_manager_ptr, const IFBEngineMemory* memory_ptr);
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
        IFBHND commit_id_array; // IFBIDCommit
        IFBHND tag_id_array;    // IFBTagId
    } handles;
    IFBIDCommit commit_id;
};

namespace ifb_engine {

    ifb_void 
    arena_manager_initialize(
              IFBEngineArenaManager* arena_manager_ptr,
              IFBEngineMemory*       memory_ptr,
        const ifb_u32                arena_minimum_size,
        const ifb_u32                arena_count_max);

    const IFBIDArena 
    arena_manager_commit_arena(
              IFBEngineArenaManager* arena_manager_ptr, 
              IFBEngineMemory*       memory_ptr,
        const IFBIDTag               arena_tag_id,
        const ifb_u32                arena_commit_size_minimum);

    const ifb_u32      arena_manager_align_size_to_arena         (const IFBEngineArenaManager* arena_manager_ptr, const ifb_u32 size);
    const IFBIDCommit  arena_manager_get_arena_commit_id         (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref);
    const IFBIDTag     arena_manager_get_arena_tag_id            (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref);
    const ifb_u32      arena_manager_get_arena_size              (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref);
    const ifb_u32      arena_manager_get_arena_start             (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref);
    const ifb_ptr      arena_manager_get_arena_pointer           (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref);
    const ifb_ptr      arena_manager_get_arena_pointer           (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr, const IFBIDArena& arena_id_ref, const ifb_u32 offset);
          IFBIDCommit* arena_manager_get_pointer_commit_id_array (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr);
          IFBIDTag*    arena_manager_get_pointer_tag_id_array    (const IFBEngineArenaManager* arena_manager_ptr, const IFBEngineMemory* memory_ptr);
};

/**********************************************************************************/ 
/* WINDOW MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineWindowManager {
    IFBResolution      window_resolution;
    IFBPosition        window_position;
    IFBAspectRatioType window_aspect_ratio;
    IFBResolutionType  window_resolution_type_default;
    IFBResolutionType  window_resolution_type_current;
    ifb_b8             window_visible;
    ifb_b8             window_created;
    ifb_b8             window_has_imgui;
    ifb_b8             window_has_opengl;
};

namespace ifb_engine {

    ifb_void 
    window_manger_initialize(
        IFBEngineWindowManager* window_manager_ptr,
        IFBEngineMemory*        memory_ptr);

    ifb_void window_manager_create_window (
              IFBEngineWindowManager* window_manager_ptr,
        const ifb_cstr                window_title,
        const ifb_b8                  use_opengl,
        const ifb_b8                  use_imgui);

    ifb_void window_manager_set_visibility(
              IFBEngineWindowManager* window_manager_ptr,
        const ifb_b8                  visible);

    ifb_void window_manager_frame_start  (IFBEngineWindowManager* window_manager_ptr);
    ifb_void window_manager_frame_render (IFBEngineWindowManager* window_manager_ptr);
};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP