#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemoryPageCommit {
    ifb_u32    page_start;
    ifb_u32    page_count;
    ifb_memory memory_start;
};

namespace ifb_engine {

    const ifb_memory
    memory_get_pointer(
        IFBEngineContext* engine_context,
        const ifb_u32    page_number,
        const ifb_u32    page_offset);

    const ifb_memory
    memory_get_page_pointer(
              IFBEngineContext* engine_context,
        const ifb_u32          page_number);

    const ifb_memory
    memory_get_current_page_pointer(
        IFBEngineContext* engine_context);

    const ifb_u32
    memory_size_page_aligned(
              IFBEngineContext* engine_context,
        const ifb_u32          memory_size);

    const ifb_u32
    memory_page_count_aligned(
              IFBEngineContext* engine_context,
        const ifb_size         memory_size);

    const ifb_size
    memory_page_size(
              IFBEngineContext* engine_context,
        const ifb_u32          page_count);

    const ifb_memory
    memory_commit_pages(
              IFBEngineContext* engine_context,
        const ifb_u32          in_page_count,                
              ifb_u32&        out_page_start_ref);

    const ifb_b8
    memory_commit_size(
              IFBEngineContext* engine_context,
        const ifb_size                    in_memory_size,
              IFBEngineMemoryPageCommit& out_memory_page_commit);

    const ifb_memory
    memory_commit_immediate(
              IFBEngineContext* engine_context,
        const ifb_size         memory_size);
};

#define ifb_engine_memory_commit_struct_immediate(                  \
    memory,                                                         \
    type)                                                           \
                                                                    \
    (type*)ifb_engine::memory_commit_immediate(memory,sizeof(type)) \


#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP