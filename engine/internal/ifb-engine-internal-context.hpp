#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

namespace ifb_engine {

    const IFBPlatformApi&  context_get_platform_api (ifb_void);
    const IFBEngineConfig& context_get_config       (ifb_void);
    IFBEngineMemory&       context_get_memory       (ifb_void); 

};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8          context_memory_reserve                (const IFBPlatformApi& platform_api_ref);
    const ifb_b8          context_memory_release                (ifb_void);

    ifb_void              context_memory_get_info               (IFBEngineMemoryInfo* memory_info_ptr);
    
    IFBMemoryArena*       context_memory_commit_arena_unmanaged (const ifb_u32 size_minimum);
    IFBMemoryLinearArena* context_memory_commit_arena_linear    (const ifb_u32 size_minimum);
    IFBMemoryBlockArena*  context_memory_commit_arena_block     (const ifb_u32 block_size_minimum, const ifb_u32 block_count);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP