#ifndef IFB_ENGINE_INTERNAL_CONTROLLERS_HPP
#define IFB_ENGINE_INTERNAL_CONTROLLERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* TAG CONTROLLER                                                                 */
/**********************************************************************************/

namespace ifb_engine {

    const IFBHashValue   tag_controller_hash_value       (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const ifb_cstr       tag_controller_cstr_value       (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const ifb_b8         tag_controller_collision_check  (IFBEngineCore* engine_core_ptr, const IFBHashValue   hash_value);
    const ifb_b8         tag_controller_destroy          (IFBEngineCore* engine_core_ptr, const IFBEngineTagId tag_id);
    const IFBEngineTagId tag_controller_create           (IFBEngineCore* engine_core_ptr, const ifb_cstr       tag_value);
    
    const ifb_b8 
    tag_controller_search(
          IFBEngineCore*   in_engine_core_ptr, 
    const ifb_cstr         in_tag_value,
          IFBEngineTagId& out_tag_id);
};

/**********************************************************************************/
/* ARENA CONTROLLER                                                              */
/**********************************************************************************/

namespace ifb_engine {
       
    const ifb_u32    arena_controller_get_page_start    (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id);
    const ifb_u32    arena_controller_get_page_count    (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id);
    const ifb_cstr   arena_controller_get_tag_value     (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id);
    const ifb_memory arena_controller_get_memory_start  (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id);
    const ifb_memory arena_controller_get_memory_offset (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id, const ifb_u32 offset);
    
    ifb_void arena_controller_get_info (IFBEngineCore* engine_core_ptr, IFBArena& arena_ref);

    const IFBArenaId
    arena_controller_commit(
              IFBEngineCore* engine_core_ptr,
        const ifb_cstr       arena_tag_value,
        const ifb_u32        arena_size_minimum);
};

/**********************************************************************************/
/* MEMORY CONTROLLER                                                              */
/**********************************************************************************/

namespace ifb_engine {

      const ifb_u32    memory_controller_align_size_to_page               (IFBEngineCore* engine_core_ptr, const ifb_u32    size);
      const ifb_u32    memory_controller_align_size_to_granularity        (IFBEngineCore* engine_core_ptr, const ifb_u32    size);
      const ifb_memory memory_controller_get_pointer                      (IFBEngineCore* engine_core_ptr, const IFBArenaId arena_id, const ifb_u32 arena_offset);
      const ifb_u32    memory_controller_get_reservation_page_count_total (IFBEngineCore* engine_core_ptr);
      const ifb_u32    memory_controller_get_reservation_page_count_used  (IFBEngineCore* engine_core_ptr);
      const ifb_u32    memory_controller_get_reservation_size_total       (IFBEngineCore* engine_core_ptr);
      const ifb_u32    memory_controller_get_reservation_size_used        (IFBEngineCore* engine_core_ptr);
};


#endif //IFB_ENGINE_INTERNAL_CONTROLLERS_HPP