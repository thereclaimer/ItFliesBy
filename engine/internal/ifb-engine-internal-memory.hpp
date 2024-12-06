#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* GLOBAL STACK                                                                   */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_STACK_SIZE ifb_macro_size_kilobytes(64) 

struct IFBEngineMemoryGlobalStack {
    ifb_u32  size;
    ifb_u32  position;
    ifb_byte memory[IFB_ENGINE_MEMORY_STACK_SIZE];
};

namespace ifb_engine {
    
    ifb_global IFBEngineMemoryGlobalStack _global_stack;

    const ifb_handle memory_global_push                   (const ifb_u32 size);
    const ifb_handle memory_global_push_aligned           (const ifb_u32 size, const ifb_u32 alignment);
    const ifb_memory memory_global_push_immediate         (const ifb_u32 size);
    const ifb_memory memory_global_push_aligned_immediate (const ifb_u32 size, const ifb_u32 alignment);
    const ifb_memory memory_global_pointer                (const ifb_handle handle);
};


#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP