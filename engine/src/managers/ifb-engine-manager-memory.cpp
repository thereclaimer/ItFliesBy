#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

inline const ifb_handle              
ifb_engine::memory_manager_create(
    const ifb_u32 memory_reservation_size) {

    //allocate memory manager
    const ifb_handle        memory_manager_handle = ifb_engine_memory_global_push_struct(IFBEngineMemoryManager);
    IFBEngineMemoryManager* ptr_memory_manager    = ifb_engine::memory_global_pointer(memory_manager_handle);

    //calculate sizes and reserve memory
    const ifb_u32 system_page_size                = ifb_engine::platform_system_page_size();
    const ifb_u32 system_allocation_granularity   = ifb_engine::platform_system_allocation_granularity();
    const ifb_u32 memory_reservation_size_aligned = ifb_macro_align_a_to_b(memory_reservation_size,system_allocation_granularity); 
    const ifb_u32 memory_reservation_page_count   = memory_reservation_size_aligned / system_page_size; 
    const ifb_ptr ptr_memory_reservation          = ifb_engine::platform_memory_reserve(memory_reservation_size_aligned);

    //sanity check
    ifb_macro_assert(system_page_size                > 0);
    ifb_macro_assert(system_allocation_granularity   > 0);
    ifb_macro_assert(memory_reservation_size_aligned > 0);
    ifb_macro_assert(memory_reservation_page_count   > 0);
    ifb_macro_assert(ptr_memory_reservation          != NULL);
    
    //initialize memory manager
    ptr_memory_manager->page_size              = system_page_size; 
    ptr_memory_manager->allocation_granularity = system_allocation_granularity; 
    ptr_memory_manager->count_pages_reserved   = memory_reservation_page_count; 
    ptr_memory_manager->reservation_start      = ptr_memory_reservation; 
    ptr_memory_manager->commit_array_count     = IFB_ENGINE_MEMORY_MANAGER_COMMIT_COUNT_MAX; 
    ptr_memory_manager->commit_array_handle    = ifb_engine_memory_global_push_array(IFBEngineMemoryCommit, IFB_ENGINE_MEMORY_MANAGER_COMMIT_COUNT_MAX); 

    //we're done
    return(memory_manager_handle);
}

inline IFBEngineMemoryManager* 
ifb_engine::memory_manager_pointer(
    const ifb_handle memory_reservation_handle) {

    IFBEngineMemoryManager* ptr_memory_manager = (IFBEngineMemoryManager*)ifb_engine::memory_global_pointer(memory_reservation_handle);

    return(ptr_memory_manager);
}

inline const ifb_u32 
ifb_engine::memory_manager_size_reserved(
    IFBEngineMemoryManager* ptr_memory_manager) {

    const ifb_u32 page_size     = ptr_memory_manager->page_size;
    const ifb_u32 page_count    = ptr_memory_manager->count_pages_reserved;
    const ifb_u32 size_reserved = page_size * page_count;

    return(size_reserved);
}

inline const ifb_u32 
ifb_engine::memory_manager_size_committed(
    IFBEngineMemoryManager* ptr_memory_manager) {

    //get commit array
    const IFBEngineMemoryCommit* ptr_commit_array = ifb_engine::memory_manager_commit_array(ptr_memory_manager);
    
    //get sizes
    const ifb_u32 page_size         = ptr_memory_manager->page_size;
    const ifb_u32 commit_used_count = ptr_memory_manager->commit_array_count_used;
    
    //calculate total commit size
    ifb_u32 commit_pages_count = 0;
    for (
        ifb_u32 commit_index = 0;
                commit_index < commit_used_count; 
              ++commit_index) {

        //add the size of this commit
        commit_pages_count += ptr_commit_array[commit_index].page_count;
    }
    ifb_u32 size_committed = page_size * commit_pages_count;

    //we're done
    return(size_committed);
}

inline const ifb_ptr 
ifb_engine::memory_manager_reservation_pointer(
    IFBEngineMemoryManager* ptr_memory_manager) {
    
    const ifb_ptr reservation_ptr = (ifb_ptr)ptr_memory_manager->reservation_start;

    return(reservation_ptr);
}

inline const ifb_u32 
ifb_engine::memory_manager_align_size_to_page(
          IFBEngineMemoryManager* ptr_memory_manager,
    const ifb_u32                 size) {

    const ifb_u32 page_size    = ptr_memory_manager->page_size;
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size, page_size); 

    return(size_aligned);
}

inline const ifb_u32 
ifb_engine::memory_manager_align_size_to_granularity(
          IFBEngineMemoryManager* ptr_memory_manager,
    const ifb_u32                 size) {

    const ifb_u32 allocation_granularity = ptr_memory_manager->allocation_granularity;
    const ifb_u32 size_aligned           = ifb_macro_align_a_to_b(size, page_size); 

    return(size_aligned);
}

inline const ifb_u32 
ifb_engine::memory_manager_size_to_page_count(
          IFBEngineMemoryManager* ptr_memory_manager,
    const ifb_u32                 size) {

    const ifb_u32 page_size    = ptr_memory_manager->page_size;
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size, page_size); 
    const ifb_u32 page_count   = size_aligned / page_size;

    return(page_count);  
}

inline const IFBEngineMemoryCommitId 
ifb_engine::memory_manager_commit(
          IFBEngineMemoryManager* ptr_memory_manager, 
    const ifb_u32                 size) {

    ifb_macro_assert(ptr_memory_manager->commit_array_count_used < ptr_memory_manager->commit_array_count_total);

    //calculate sizes
    const ifb_u32 size_aligned   = ifb_engine::memory_manager_align_size_to_page(ptr_memory_manager,size);
    const ifb_u32 page_count     = ifb_engine::memory_manager_size_to_page_count(size_aligned);
    const ifb_u32 committed_size = ifb_engine::memory_manager_size_committed(ptr_memory_manager);

    //get the commit start
    const ifb_address reservation_start = ptr_memory_manager->reservation_start;
    const ifb_address commit_start      = (reservation_start + size_committed); 
    const ifb_ptr     ptr_commit_start  = (ifb_ptr)commit_start; 

    //do the commit
    const ifb_ptr ptr_commit_result = ifb_engine::platform_memory_commit(
        ptr_commit_start,
        size_aligned);

    ifb_macro_assert(ptr_commit_result == ptr_commit_start);

    //set the commit id
    const IFBEngineMemoryCommitId commit_id;
    commit_id.index = ptr_memory_manager->commit_array_count_used;

    //update the commit array
    ++ptr_memory_manager->commit_array_count_used;
    IFBEngineMemoryCommit* ptr_commit_array = ifb_engine::memory_manager_commit_array(ptr_memory_manager);
    IFBEngineMemoryCommit& ref_new_commit   = ptr_commit_array[commit_id.index]; 
    ref_new_commit.page_count = page_count;

    //TODO
    ifb_macro_panic();

    //we're done
    return(commit_id);
}

inline const ifb_handle              
ifb_engine::memory_manager_commit_handle(
          IFBEngineMemoryManager* ptr_memory_manager, 
    const IFBEngineMemoryCommitId commit_id) {

    //get the commit
    IFBEngineMemoryCommit* ptr_commit_array = ifb_engine::memory_manager_commit_array(ptr_memory_manager);
    IFBEngineMemoryCommit& ref_commit       = ptr_commit_array[commit_id.index]; 

    //calculate handle
    const ifb_u32    page_size     = ptr_memory_manager->page_size;
    const ifb_handle commit_handle = ref_commit.page_start * page_size;

    //we're done
    return(commit_handle);
}

inline const ifb_ptr                 
ifb_engine::memory_manager_commit_pointer(
          IFBEngineMemoryManager* ptr_memory_manager, 
    const IFBEngineMemoryCommitId commit_id) {

    const ifb_handle commit_handle = ifb_engine::memory_manager_commit_handle(ptr_memory_manager,commit_id);
    const ifb_ptr    commit_ptr    = (ifb_ptr)(ptr_memory_manager->reservation_start + commit_handle); 

    return(commit_ptr);
}

inline const ifb_ptr
ifb_engine::memory_manager_commit_array(
    IFBEngineMemoryManager* ptr_memory_manager) {

    IFBEngineMemoryCommit* ptr_commit_array = (IFBEngineMemoryCommit*)ifb_engine::memory_global_pointer(ptr_memory_manager->commit_array_handle);

    return(ptr_commit_array);
}
