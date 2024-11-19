#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM ifb_macro_size_kilobytes(4)
#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_INVALID      4096

struct IFBEngineArenaTable {
    ifb_u32             arena_count_total;
    ifb_u32             arena_count_used;
    ifb_u32             arena_size_minimum;
    ifb_handle_memory_t column_handle_page_start;
    ifb_handle_memory_t column_handle_page_count;
    ifb_handle_memory_t column_handle_tag;
};

struct IFBEngineArenaTableColumnMemory {
    ifb_u32* page_start_ptr;
    ifb_u32* page_count_ptr;
    ifb_u32* tag_index_ptr;
};

namespace ifb_engine {

    IFBEngineArenaTable* arena_table_pointer_from_handle(const ifb_u32 arena_table_handle);

    const ifb_b8 arena_table_initialize(const ifb_u32 arena_table_handle); 

    const ifb_void
    arena_table_memory(
        IFBEngineArenaTable*              in_arena_table_ptr,
        IFBEngineArenaTableColumnMemory& out_arena_table_column_memory_ref);

    const ifb_void
    arena_table_update_arena(
              IFBEngineArenaTable* arena_table_ptr,
        const ifb_u32              arena_index,
        const ifb_u32              arena_tag_index,
        const ifb_u32              arena_page_start,
        const ifb_u32              arena_page_count);

    const ifb_u32* arena_table_column_memory_page_start (IFBEngineArenaTable* arena_table_ptr);
    const ifb_u32* arena_table_column_memory_page_count (IFBEngineArenaTable* arena_table_ptr);
    const ifb_u32* arena_table_column_memory_tag        (IFBEngineArenaTable* arena_table_ptr);
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

    IFBEngineMemoryManager* memory_manager_pointer_from_handle    (const ifb_u32 memory_manager_handle);
    IFBEngineArenaTable*    memory_manager_get_arena_table (ifb_void);
};



#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP