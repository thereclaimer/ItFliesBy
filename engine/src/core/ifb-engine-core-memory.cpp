#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

inline const IFBMemoryCommitId
ifb_engine::core_memory_commit(
    const IFBEngineCore* ptr_core,
    const ifb_u32        size) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_managers); 

    //do the commit
    const IFBMemoryCommitId commit_id = ifb_engine::memory_manager_commit(ptr_memory_manager,size);

    //we're done
    return(commit_id);
}

inline ifb_ptr
ifb_engine::core_memory_get_pointer(
    const IFBEngineCore*    ptr_core,
    const IFBMemoryCommitId commit_id) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_managers); 
        
    //get the pointer
    ifb_ptr commit_pointer = ifb_engine::memory_manager_get_commit_pointer(
        ptr_memory_manager,
        commit_id);

    //we're done
    return(commit_pointer);
}

inline ifb_ptr
ifb_engine::core_memory_get_pointer(
    const IFBEngineCore*    ptr_core,
    const IFBMemoryCommitId commit_id, 
    const ifb_u32           offset) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_managers); 

    //get the pointer
    ifb_ptr commit_pointer = ifb_engine::memory_manager_get_commit_pointer(
        ptr_memory_manager,
        commit_id,
        offset);

    //we're done
    return(commit_pointer);
}

inline ifb_ptr
ifb_engine::core_memory_get_pointer(
    const IFBEngineCore* ptr_core,
    const ifb_handle     handle) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_managers); 

    //get the pointer
    ifb_ptr pointer = ifb_engine::memory_manager_get_pointer(
        ptr_memory_manager,
        handle);

    //we're done
    return(pointer);
}

inline const ifb_u32
ifb_engine::core_memory_get_commit_size(
    const IFBEngineCore*    ptr_core,
    const IFBMemoryCommitId commit_id) {

    //get the managers
    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::core_managers_get_pointer_memory_manager(ptr_managers); 

    //get the size
    const ifb_u32 commit_size = ifb_engine::memory_manager_get_commit_size(
        ptr_memory_manager,
        commit_id);    

    //we're done
    return(commit_size);
}