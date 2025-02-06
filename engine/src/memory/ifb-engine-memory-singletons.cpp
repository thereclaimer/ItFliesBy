#pragma once

#include <ifb-memory.hpp>

#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE 0xFFFF

namespace ifb_engine {

    ifb_global IFBStack _memory_singleton_stack;

    const ifb_b8 memory_singleton_stack_commit(const IFBMemoryHandle memory_handle);
};


/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::memory_singleton_stack_commit(
    const IFBMemoryHandle memory_handle) {

    ifb_macro_assert(memory_handle);

    const ifb_u32 singleton_stack_size = IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE;

    ifb_memory::stack_push(memory_handle,singleton_stack_size);
}
