#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-config.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineContextMemoryStack {
    ifb_byte* data;
    ifb_u32   size;
};

struct IFBEngineContextMemoryReservation {
    ifb_u64                     size;
    IFBMemoryReservationHandle  handle; 
};

struct IFBEngineContextMemory {
    IFBEngineContextMemoryStack       stack;
    IFBEngineContextMemoryReservation reservation; 
};

struct IFBEngineContextSingletonHandle : IFBEngineHandle { }

namespace ifb_engine {

    const ifb_b8
    context_memory_reserve(
        const ifb_byte* stack_buffer,
        const ifb_u32   stack_size,
        const ifb_u64   reservation_size);

    const ifb_b8
    context_memory_singleton_commit(
        const ifb_u32                          count,                   
        const IFBEngineSizeAndAlignment*       size_and_alignment_array,
              IFBEngineContextSingletonHandle* singleton_handle_array);

    const ifb_ptr 
    context_memory_singleton_load(
        const IFBEngineContextSingletonHandle* singleton_handle);
};

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

struct IFBEngineContextSingletons {
    IFBEngineContextSingletonHandle config;
};

namespace ifb_engine {

    //commit
    const ifb_b8           context_singletons_commit_all (ifb_void);
    
    //instances
    const IFBEngineConfig* context_singletons_get_config (ifb_void);

};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineContextMemory     memory;
    IFBEngineContextSingletons singletons;
};

namespace ifb_engine {
    
    IFBEngineContext&           context                (ifb_void);
    IFBEngineContextMemory&     context_get_memory     (ifb_void); 
    IFBEngineContextSingletons& context_get_singletons (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP