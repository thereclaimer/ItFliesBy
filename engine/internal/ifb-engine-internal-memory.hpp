#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemory {
    ifb_address reservation_start;
    ifb_u32     system_allocation_granularity;
    ifb_u32     system_page_size;
    ifb_u32     page_count_total;
    ifb_u32     page_count_committed;
    ifb_u32     commit_count_max;
    ifb_u32     commit_count_current;
    IFBHND      commit_array_handle; // IFBCommit
};

namespace ifb_engine {

          ifb_void    memory_reserve (IFBEngineMemory* memory_ptr, const ifb_size reservation_size_minimum, const ifb_u32 commit_count_max);
    const IFBIDCommit memory_commit  (IFBEngineMemory* memory_ptr, const ifb_u32  commit_size_minimum);
    
    const ifb_u32     memory_get_commit_page_number (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_u32     memory_get_commit_page_count  (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_u32     memory_get_commit_size        (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_u32     memory_get_commit_offset      (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_address memory_get_commit_address     (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_ptr     memory_get_commit_pointer     (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id);
    const ifb_ptr     memory_get_commit_pointer     (const IFBEngineMemory* memory_ptr, const IFBIDCommit commit_id, const ifb_u32 commit_offset);
    
    const ifb_u32     memory_align_size_to_page              (const IFBEngineMemory* memory_ptr, const ifb_u32  size);
    const ifb_u32     memory_align_size_to_granularity       (const IFBEngineMemory* memory_ptr, const ifb_u32  size);
    const ifb_size    memory_align_large_size_to_page        (const IFBEngineMemory* memory_ptr, const ifb_size size);
    const ifb_size    memory_align_large_size_to_granularity (const IFBEngineMemory* memory_ptr, const ifb_size size);

    ifb_void memory_get_handle(
        const IFBEngineMemory* memory_ptr, 
        const IFBIDCommit      commit_id, 
        const ifb_u32          commit_offset, 
              IFBHND&          handle_ref);

    const ifb_ptr     memory_get_pointer(const IFBEngineMemory* memory_ptr, const ifb_u32 offset);
    const ifb_ptr     memory_get_pointer(const IFBEngineMemory* memory_ptr, const IFBHND& handle_ref);

          IFBCommit*  memory_get_commit_array_pointer (const IFBEngineMemory* memory_ptr);
    const ifb_size    memory_get_size_committed       (const IFBEngineMemory* memory_ptr);

};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP