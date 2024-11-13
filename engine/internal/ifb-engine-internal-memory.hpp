#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_memory
    memory_get_current_page_pointer(ifb_void);


    const ifb_memory
    memory_commit_pages(
        const ifb_u32          in_page_count,                
              ifb_u32&        out_page_start_ref);

    const ifb_b8
    memory_commit_size(
        const ifb_size                in_memory_size,
              IFBEngineMemoryCommit& out_memory_page_commit);

    const ifb_memory
    memory_commit_immediate(
        const ifb_size         memory_size);
};

#define ifb_engine_memory_commit_struct_immediate(                  \
    memory,                                                         \
    type)                                                           \
                                                                    \
    (type*)ifb_engine::memory_commit_immediate(memory,sizeof(type)) \


#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP