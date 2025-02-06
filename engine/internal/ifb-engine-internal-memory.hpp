#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include <ifb-data-structures.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineMemorySingletonId;
struct IFBEngineMemoryUnmanaged;
struct IFBEngineMemoryBlocks;
struct IFBEngineMemoryLinear;


/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

namespace ifb_engine {

    //reserve/release
    const ifb_b8  memory_core_reserve                    (const IFBPlatformApi& platform_api_ref);
    const ifb_b8  memory_core_release                    (ifb_void);

    //reservation
    const ifb_u64 memory_core_get_reservation_size_total (ifb_void);
    const ifb_u64 memory_core_get_reservation_size_free  (ifb_void);
    const ifb_u64 memory_core_get_reservation_size_used  (ifb_void);

    //stack     
    const ifb_u32 memory_core_get_stack_size_total       (ifb_void);
    const ifb_u32 memory_core_get_stack_size_free        (ifb_void);
    const ifb_u32 memory_core_get_stack_size_used        (ifb_void);
};

/**********************************************************************************/
/* BLOCK MEMORY                                                                   */
/**********************************************************************************/

namespace ifb_engine {

    //commit
    IFBEngineMemoryBlocks*
    memory_commit_blocks(
        const ifb_u32 block_size_minimum,
        const ifb_u32 block_count);

    //reserve/release
    const ifb_b8  memory_block_reset                  (IFBEngineMemoryBlocks* blocks);
    const ifb_ptr memory_block_reserve                (IFBEngineMemoryBlocks* blocks);
    const ifb_b8  memory_block_release                (IFBEngineMemoryBlocks* blocks, const ifb_ptr block_memory);

    //size
    const ifb_u32 memory_blocks_get_size_total        (const IFBEngineMemoryBlocks* blocks);
    const ifb_u32 memory_blocks_get_size_free         (const IFBEngineMemoryBlocks* blocks);
    const ifb_u32 memory_blocks_get_size_used         (const IFBEngineMemoryBlocks* blocks);

    //count    
    const ifb_u32 memory_blocks_get_block_count_total (const IFBEngineMemoryBlocks* blocks);
    const ifb_u32 memory_blocks_get_block_count_free  (const IFBEngineMemoryBlocks* blocks);
    const ifb_u32 memory_blocks_get_block_count_used  (const IFBEngineMemoryBlocks* blocks);
};

/**********************************************************************************/
/* LINEAR MEMORY                                                                  */
/**********************************************************************************/

namespace ifb_engine {

    const IFBEngineMemoryLinear*
    memory_commit_linear(
        const ifb_u32 size_minumum);
    
    memory_linear_reserve(IFBEngineMemoryLinear*);
    memory_linear_release(IFBEngineMemoryLinear*);

};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP