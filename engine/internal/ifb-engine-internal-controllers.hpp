#ifndef IFB_ENGINE_INTERNAL_CONTROLLERS_HPP
#define IFB_ENGINE_INTERNAL_CONTROLLERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* TAG CONTROLLER                                                                 */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHashValue controller_tag_hash_value       (const IFBEngineTagId tag_id);
    const ifb_cstr     controller_tag_cstr_value       (const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_collision_check  (const IFBHashValue   hash_value);
    const ifb_b8       controller_tag_destroy          (const IFBEngineTagId tag_id);
    const ifb_b8       controller_tag_create           (const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
    const ifb_b8       controller_tag_search           (const ifb_cstr       in_tag_value, IFBEngineTagId& out_tag_id);
};

/**********************************************************************************/
/* MEMORY CONTROLLER                                                              */
/**********************************************************************************/

namespace ifb_engine {
       
    const ifb_u32        controller_memory_arena_page_start (const IFBEngineArenaId arena_id);
    const ifb_u32        controller_memory_arena_page_count (const IFBEngineArenaId arena_id);
    const IFBEngineTagId controller_memory_arena_tag_id     (const IFBEngineArenaId arena_id);

    const ifb_b8 
    controller_memory_arena_create(
        const ifb_cstr           in_arena_tag_value,
        const ifb_u32            in_arena_size_minimum,
              IFBEngineArenaId& out_arena_id);
};

#endif //IFB_ENGINE_INTERNAL_CONTROLLERS_HPP