#pragma once

#include "ifb-engine-internal.hpp"
#include "ifb-engine-core-startup-routine.cpp"

inline const ifb_b8 
ifb_engine::core_create_managers(
    IFBEngineCore& engine_core_ref) {

    //create the managers
    engine_core_ref.managers.handle_memory     = ifb_engine::memory_manager_startup();
    engine_core_ref.managers.handle_tag        = ifb_engine::tag_manager_create();
    engine_core_ref.managers.handle_allocators = ifb_engine::allocator_manager_start_up();

    //sanity check
    ifb_b8 result = true;
    result &= ifb_engine::memory_handle_valid(engine_core_ref.managers.handle_memory);
    result &= ifb_engine::memory_handle_valid(engine_core_ref.managers.handle_tag);
    result &= ifb_engine::memory_handle_valid(engine_core_ref.managers.handle_allocators);

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_create_allocators(
    IFBEngineCore& engine_core_ref) {

    //create the stack allocators
    engine_core_ref.stack_allocators.frame    = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME,   IFB_ENGINE_CORE_STACK_SIZE);
    engine_core_ref.stack_allocators.platform = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM,IFB_ENGINE_CORE_STACK_SIZE);
    engine_core_ref.stack_allocators.window   = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW,  IFB_ENGINE_CORE_STACK_SIZE);

    //sanity check
    ifb_b8 result = true;
    result &= ifb_engine::stack_allocator_valid(engine_core_ref.stack_allocators.frame);
    result &= ifb_engine::stack_allocator_valid(engine_core_ref.stack_allocators.platform);
    result &= ifb_engine::stack_allocator_valid(engine_core_ref.stack_allocators.window);

    //we're done
    return(result);
}