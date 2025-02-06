#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBEngineMemorySingletonId;
struct IFBEngineMemoryBlockAllocator;  
struct IFBEngineMemoryLinearAllocator; 

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
/* SINGLETONS                                                                     */
/**********************************************************************************/

struct IFBEngineMemorySingletonId {
    ifb_u16 stack_offset;
};

namespace ifb_engine {

    const IFBEngineMemorySingletonId
    memory_singleton_commit(
        const ifb_u32 size,
        const ifb_u32 alignment);
    
    const ifb_ptr
    memory_singleton_get_pointer(const IFBEngineMemorySingletonId singleton_id);
};

#define ifb_engine_macro_memory_singleton_commit(struct)                  ifb_engine::memory_singleton_commit(sizeof(struct),alignof(struct))
#define ifb_engine_macro_memory_singleton_get_pointer(struct,id) (struct*)ifb_engine::memory_singleton_get_pointer(id)

/**********************************************************************************/
/* BLOCK ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_engine {

    const IFBEngineMemoryBlockAllocator*
    memory_commit_block_allocator(
        const ifb_u32 block_size_minimum,
        const ifb_u32 block_count);

    const ifb_ptr memory_block_reserve(const IFBEngineMemoryBlockAllocator* blocks);
    const ifb_b8  memory_block_release(const IFBEngineMemoryBlockAllocator* blocks, const ifb_ptr block_memory);


};

/**********************************************************************************/
/* LINEAR ALLOCATOR                                                                */
/**********************************************************************************/

namespace ifb_engine {

    const IFBEngineMemoryLinearAllocator*
    memory_commit_linear_allocator(
        const ifb_u32 size_minumum);

};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP