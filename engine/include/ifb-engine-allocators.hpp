#ifndef IFB_ENGINE_ALLOCATORS_HPP
#define IFB_ENGINE_ALLOCATORS_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-arena.hpp"

/**********************************************************************************/
/* STACK ALLOCATOR                                                                */
/**********************************************************************************/

struct IFBEngineAllocatorStack {
    IFBEngineArena arena;
    ifb_u32        stack_pointer;
};

namespace ifb_engine {

    const ifb_b8 
    allocator_stack_create(
        const ifb_u32                   in_stack_allocator_size_minimumm,
              IFBEngineAllocatorStack& out_stack_allocator_ref);

    const ifb_b8 
    allocator_stack_push(
        IFBEngineAllocatorStack& in_stack_allocator_ref,
        IFBEngineMemoryHandle&  out_stack_memory_ref);
};


#endif //IFB_ENGINE_ALLOCATORS_HPP