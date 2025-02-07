#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-data-structures.hpp>
#include <ifb-memory.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8          memory_reserve                (ifb_void);
    const ifb_b8          memory_release                (ifb_void);

    const ifb_b8          memory_get_info               (IFBEngineMemoryInfo* memory_info_ptr);
    
    IFBMemoryArena*       memory_commit_arena_unmanaged (const ifb_u32 size_minimum);
    IFBMemoryLinearArena* memory_commit_arena_linear    (const ifb_u32 size_minimum);
    IFBMemoryBlockArena*  memory_commit_arena_block     (const ifb_u32 block_size_minimum, const ifb_u32 block_count);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP