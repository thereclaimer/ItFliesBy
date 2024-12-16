#ifndef IFB_ENGINE_INTERNAL_MEMORY_HPP
#define IFB_ENGINE_INTERNAL_MEMORY_HPP

#include "ifb-engine.hpp"

/**********************************************************************************/
/* SYSTEM INFO                                                                    */
/**********************************************************************************/

struct IFBEngineMemorySystemInfo {
    ifb_u32 allocation_granularity;
    ifb_u32 page_size;
};

/**********************************************************************************/
/* GLOBAL STACK                                                                   */
/**********************************************************************************/

#ifndef IFB_ENGINE_CONFIG_GLOBAL_MEMORY_STACK_SIZE
    #define IFB_ENGINE_CONFIG_GLOBAL_MEMORY_STACK_SIZE ifb_macro_size_kilobytes(64)
#endif


struct IFBEngineMemoryGlobalStack {
    ifb_u32  size;
    ifb_u32  position;
    ifb_byte memory[IFB_ENGINE_CONFIG_GLOBAL_MEMORY_STACK_SIZE];
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBEngineMemoryReservation {
    ifb_address start;
    ifb_u32     page_count_total;
    ifb_u32     page_count_committed;
    ifb_u32     commit_count_max;
    ifb_u32     commit_count_current;
    IFBGHND     commit_array_handle; // IFBCommit
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineMemory {
    IFBEngineMemoryGlobalStack global_stack;
    IFBEngineMemorySystemInfo  system_info;
    IFBEngineMemoryReservation reservation;
};

namespace ifb_engine {

          ifb_void    memory_reserve (IFBEngineMemory* memory_ptr, const ifb_size reservation_size_minimum, const ifb_u32 commit_count_max);
    const IFBIDCommit memory_commit  (IFBEngineMemory* memory_ptr, const ifb_u32  commit_size_minimum);

    const ifb_u32     memory_get_page_count (const IFBEngineMemory* memory_ptr, const ifb_u32 size);

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

    const ifb_ptr     memory_get_pointer (const IFBEngineMemory* memory_ptr, const ifb_u32  offset);
    const ifb_ptr     memory_get_pointer (const IFBEngineMemory* memory_ptr, const IFBHND&  handle_ref);
    const ifb_ptr     memory_get_pointer (const IFBEngineMemory* memory_ptr, const IFBGHND& global_handle_ref);

          IFBCommit*  memory_get_commit_array_pointer (const IFBEngineMemory* memory_ptr);
    const ifb_size    memory_get_size_committed       (const IFBEngineMemory* memory_ptr);

    const ifb_void memory_global_push         (IFBEngineMemory* memory_ptr, IFBGHND& global_handle_ref, const ifb_u32 size);
    const ifb_void memory_global_push_aligned (IFBEngineMemory* memory_ptr, IFBGHND& global_handle_ref, const ifb_u32 size, const ifb_u32 alignment);
};

#define ifb_engine_memory_global_push_struct(memory_ptr,handle,type) ifb_engine::memory_global_push_aligned(memory_ptr,handle,sizeof(type),alignof(type))

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP