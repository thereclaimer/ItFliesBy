#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    inline const ifb_u32 context_memory_page_size        (ifb_void) { return(_engine_context->memory.page_size);        }
    inline const ifb_u32 context_memory_page_count_total (ifb_void) { return(_engine_context->memory.page_count_total); }
    inline const ifb_u32 context_memory_page_count_used  (ifb_void) { return(_engine_context->memory.page_count_used);  }

    inline ifb_void context_memory_page_count_used_update (const ifb_u32 page_count) { _engine_context->memory.page_count_used = page_count; }
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM ifb_engine_macro_size_kilobytes(4)
#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096


struct IFBEngineArenaTable {
    ifb_u32 arena_count_total;
    ifb_u32 arena_count_used;
    ifb_u32 arena_size_minimum;
    ifb_u32 page_id_column_page_start;
    ifb_u32 page_id_column_page_count;
};

struct IFBEngineArenaTableMemory {
    ifb_u32* page_start_ptr;
    ifb_u32* page_count_ptr;
};

namespace ifb_engine {

    IFBEngineArenaTable* arena_table_pointer_from_handle(const ifb_u32 arena_table_handle);

    const ifb_b8 arena_table_initialize(const ifb_u32 arena_table_handle); 

};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 handle_arena_table;
};


namespace ifb_engine {

    const ifb_u32 memory_manager_startup(ifb_void);

    IFBEngineMemoryManager* memory_manager_get_pointer     (const ifb_u32 memory_manager_handle);
    IFBEngineArenaTable*    memory_manager_get_arena_table (IFBEngineMemoryManager* memory_manager_ptr);
};


#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP