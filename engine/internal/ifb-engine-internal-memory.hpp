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

#define ifb_engine_memory_global_push_struct(type)                       ifb_engine::memory_global_push_aligned(sizeof(type),alignof(type)) 
#define ifb_engine_memory_global_push_struct_immediate(type)      (type*)ifb_engine::memory_global_push_aligned(sizeof(type),alignof(type)) 
#define ifb_engine_memory_global_push_array(type,count)                  ifb_engine::memory_global_push(sizeof(type) * count) 
#define ifb_engine_memory_global_push_array_immediate(type,count) (type*)ifb_engine::memory_global_push(sizeof(type) * count) 
#define ifb_engine_memory_global_pointer_type(handle,type)        (type*)ifb_engine::memory_global_pointer(handle) 

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

struct IFBEngineMemoryCommit {
    ifb_u32 page_start;
    ifb_u32 page_count;
};

struct IFBEngineMemoryCommitId {
    ifb_u32 index;
};

/**********************************************************************************/
/* MEMORY MANAGER                                                                 */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_MANAGER_COMMIT_COUNT_MAX 128

struct IFBEngineMemoryManager {
    ifb_u32               page_size;
    ifb_u32               allocation_granularity;
    ifb_u32               count_pages_reserved;
    ifb_address           reservation_start;
    ifb_u32               commit_array_count_total;
    ifb_u32               commit_array_count_used;
    ifb_handle            commit_array_handle;
};

namespace ifb_engine {

    const ifb_handle              memory_manager_create  (const ifb_u32    memory_reservation_size);
          IFBEngineMemoryManager* memory_manager_pointer (const ifb_handle memory_reservation_handle);

    const ifb_ptr memory_manager_reservation_pointer       (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_reserved             (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_committed            (IFBEngineMemoryManager* ptr_memory_manager);
    const ifb_u32 memory_manager_size_to_page_count        (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);
    const ifb_u32 memory_manager_align_size_to_page        (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);
    const ifb_u32 memory_manager_align_size_to_granularity (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);

    const IFBEngineMemoryCommitId memory_manager_commit         (IFBEngineMemoryManager* ptr_memory_manager, const ifb_u32 size);
    const ifb_handle              memory_manager_commit_handle  (IFBEngineMemoryManager* ptr_memory_manager, const IFBEngineMemoryCommitId commit_id);
    const ifb_ptr                 memory_manager_commit_pointer (IFBEngineMemoryManager* ptr_memory_manager, const IFBEngineMemoryCommitId commit_id);
          IFBEngineMemoryCommit*  memory_manager_commit_array   (IFBEngineMemoryManager* ptr_memory_manager);
};

#endif //IFB_ENGINE_INTERNAL_MEMORY_HPP