#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"
#include "ifb-engine-internal-tables.hpp"

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_ARENA_SIZE_MINIMUM ifb_macro_size_kilobytes(4)
#define IFB_ENGINE_MEMORY_ARENA_COUNT_MAX    4096
#define IFB_ENGINE_MEMORY_ARENA_INVALID      4096

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineMemoryManager {
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 arena_size_minimum;
    ifb_u32 arena_count_used;
    ifb_u32 arena_count_total;
};

namespace ifb_engine {

    const ifb_u32 memory_manager_startup(ifb_void);
    
    IFBEngineMemoryManager* memory_manager_pointer_from_handle  (const ifb_u32 memory_manager_handle);
    IFBEngineMemoryManager* memory_manager_pointer_from_context (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP