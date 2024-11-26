#ifndef IFB_ENGINE_INTERNAL_CONTROLLERS_HPP
#define IFB_ENGINE_INTERNAL_CONTROLLERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* TAG CONTROLLER                                                                 */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHashValue controller_tag_hash_value       (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const ifb_cstr     controller_tag_cstr_value       (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_collision_check  (IFBEngineCore* engine_core_ptr, const IFBHashValue   hash_value);
    const ifb_b8       controller_tag_destroy          (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_create           (IFBEngineCore* engine_core_ptr, const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
    const ifb_b8       controller_tag_search           (IFBEngineCore* engine_core_ptr, const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
};

/**********************************************************************************/
/* ARENA CONTROLLER                                                              */
/**********************************************************************************/

namespace ifb_engine {
       
    const ifb_u32               controller_arena_page_start (IFBEngineCore* engine_core_ptr, const IFBEngineArenaId arena_id);
    const ifb_u32               controller_arena_page_count (IFBEngineCore* engine_core_ptr, const IFBEngineArenaId arena_id);
    const ifb_cstr              controller_arena_tag_value  (IFBEngineCore* engine_core_ptr, const IFBEngineArenaId arena_id);
    const IFBEngineMemoryHandle controller_arena_handle     (IFBEngineCore* engine_core_ptr, const IFBEngineArenaId arena_id, const ifb_u32 offset);
    
    ifb_void controller_arena            (IFBEngineArena& arena_ref);

    const ifb_b8 
    controller_arena_commit(
        const ifb_cstr           in_arena_tag_value,
        const ifb_u32            in_arena_size_minimum,
              IFBEngineArenaId& out_arena_id);
};

#endif //IFB_ENGINE_INTERNAL_CONTROLLERS_HPP