#pragma once

#include "ifb-engine-internal-core.hpp"

inline const ifb_b8 
ifb_engine::core_task_create_core_handle(
    ifb_handle_memory_t& engine_core_handle_ref) {

    //get page
    const ifb_u32 core_size       = ifb_engine_macro_align_size_struct(IFBEngineCore);
    const ifb_u32 core_page_count = ifb_engine::memory_page_count(core_size);
    const ifb_u32 core_page_start = ifb_engine::memory_page_commit(core_page_count);
    
    //get handle
    engine_core_handle_ref = ifb_engine::memory_handle(core_page_start,0);

    //sanity check
    const ifb_b8 result = ifb_engine::memory_handle_valid(engine_core_handle_ref);
    
    //we're done
    return(result);
}


inline const ifb_b8 
ifb_engine::core_task_create_managers(
    IFBEngineCoreManagers& engine_core_managers_ref) {

    //create the managers
    engine_core_managers_ref.handle_memory     = ifb_engine::memory_manager_startup();
    engine_core_managers_ref.handle_tag        = ifb_engine::tag_manager_create();
    engine_core_managers_ref.handle_allocators = ifb_engine::allocator_manager_start_up();

    //sanity check
    ifb_b8 result = true;
    result &= ifb_engine::memory_handle_valid(engine_core_managers_ref.handle_memory);
    result &= ifb_engine::memory_handle_valid(engine_core_managers_ref.handle_tag);
    result &= ifb_engine::memory_handle_valid(engine_core_managers_ref.handle_allocators);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_task_create_stack_allocators(
    IFBEngineCoreStackAllocators& engine_core_stack_allocators_ref) {

    //create the stack allocators
    engine_core_stack_allocators_ref.frame    = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME,   IFB_ENGINE_CORE_STACK_SIZE);
    engine_core_stack_allocators_ref.platform = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM,IFB_ENGINE_CORE_STACK_SIZE);
    engine_core_stack_allocators_ref.window   = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW,  IFB_ENGINE_CORE_STACK_SIZE);

    //sanity check
    ifb_b8 result = true;
    result &= ifb_engine::stack_allocator_valid(engine_core_stack_allocators_ref.frame);
    result &= ifb_engine::stack_allocator_valid(engine_core_stack_allocators_ref.platform);
    result &= ifb_engine::stack_allocator_valid(engine_core_stack_allocators_ref.window);

    //we're done
    return(result);
}