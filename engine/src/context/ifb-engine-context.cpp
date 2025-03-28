#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"
#include "ifb-engine-context-internal.cpp"


// create/destroy
ifb_engine_api const IFBENG64Context
ifb_engine::context_initialize(
    const IFBEngineContextArgs& args) {

    IFBENG64Context context_handle;
    context_handle.h64 = 0;

    //set the platform api
    ifb_macro_assert(ifb_platform::set_api(args.platform_api));

    //create the global stack
    IFBMEMStack global_stack_handle = ifb_memory::stack_create(args.global_stack_memory);

    //allocate the context
    IFBEngineContext* engine_context = ifb_engine::context_initialize(global_stack_handle);
    engine_context->memory_manager   = ifb_engine::context_allocate_engine_memory(global_stack_handle); 


    context_handle.h64 = (IFBAddr)engine_context;
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