#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"
#include "ifb-engine-context-internal.cpp"

// create/destroy
ifb_engine_api IFBENGContext
ifb_engine::context_create(
    const IFBEngineContextArgs& args) {

    //set the platform api
    ifb_macro_assert(ifb_platform::set_api(args.platform_api));

    //allocate memory
    IFBEngineMemory* engine_memory = ifb_engine::memory_allocate(args.global_stack_memory);

    //initialize the context
    IFBEngineContext* engine_context = ifb_engine::memory_stack_get_context(engine_memory);
    engine_context->memory = engine_memory;

    //we're done
    return(engine_context);
}

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    IFBEngineContext* engine_context) {


    return(false);
}
    
// startup/shutdown
ifb_engine_api const IFBB8
ifb_engine::context_startup(
    IFBEngineContext* engine_context){

    //result
    IFBB8 result = true;

    //get a new core reference
    IFBEngineCore* core = ifb_engine::context_frame_alloc_core(engine_context);

    //start core systems
    result &= ifb_engine::core_startup(core);

    //we're done
    return(result);
}

ifb_engine_api const IFBB8
ifb_engine::context_shutdown(
    IFBEngineContext* engine_context){

    return(false);
}

// rendering
ifb_engine_api const IFBB8 
ifb_engine::context_main_loop (
    IFBEngineContext* engine_context) {

    return(false);
}