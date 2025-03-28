#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"

// create/destroy
ifb_engine_api const IFBENG64Context
ifb_engine::context_create(
    const IFBEngineContextArgs& args) {

    IFBENG64Context context_handle;
    context_handle.h64 = 0;

    //set the platform api
    ifb_macro_assert(ifb_platform::set_api(args.platform_api));

    //create the global stack
    IFBMEMStack global_stack_handle = ifb_memory::stack_create(args.global_stack_memory);

    //allocate the context
    IFBEngineContext* engine_context = ifb_memory_macro_stack_push_struct_absolute(global_stack_handle,IFBEngineContext); 
    ifb_macro_assert(engine_context);
    context_handle.h64 = (IFBAddr)engine_context;

    //create the memory manager
    engine_context->memory_manager = ifb_engine::memory_manager_create(global_stack_handle);

    return(context_handle);
}

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    const IFBENG64Context engine_context_handle) {

    return(false);
}
    
// startup/shutdown
ifb_engine_api const IFBB8
ifb_engine::context_startup(
    const IFBENG64Context engine_context_handle){

    return(false);

}

ifb_engine_api const IFBB8
ifb_engine::context_shutdown(
    const IFBENG64Context engine_context_handle){

    return(false);

}

// rendering
ifb_engine_api const IFBB8 
ifb_engine::context_render_frame (
    const IFBENG64Context engine_context_handle) {

    return(false);

}