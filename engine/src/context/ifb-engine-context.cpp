#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"
#include "ifb-engine-context-internal.cpp"

using namespace ifb;

// create/destroy
ifb_engine_api engine_context_h
engine::context_create(
    const engine_context_args_t& args) {

    //set the platform api
    ifb_macro_assert(platform::set_api(args.platform_api));

    //allocate memory
    engine_memory_t* engine_memory = engine::memory_allocate(args.global_stack_memory);

    //initialize the context
    engine_context_t* engine_context = engine::memory_stack_get_context(engine_memory);
    engine_context->memory = engine_memory;

    //initialize the core
    engine_core_t* core = engine::context_memory_push_core(engine_context);
    engine::core_initialize(core);

    //reset context memory
    engine::context_memory_reset(engine_context);

    //we're done
    return(engine_context);
}

ifb_engine_api const b8
engine::context_destroy(
    engine_context_t* engine_context) {


    return(false);
}
    
// startup/shutdown
ifb_engine_api const b8
engine::context_startup(
    engine_context_t* engine_context){

    //result
    b8 result = true;

    //get a new core reference
    engine_core_t* core = engine::context_memory_push_core(engine_context);

    //start core systems
    result &= engine::core_startup(core);

    //free memory
    engine::context_memory_reset(engine_context);

    //we're done
    return(result);
}

ifb_engine_api const b8
engine::context_shutdown(
    engine_context_t* engine_context){

    return(false);
}

// rendering
ifb_engine_api const b8 
engine::context_main_loop (
    engine_context_t* engine_context) {

    //get a new core reference
    engine_core_t* core = engine::context_memory_push_core(engine_context);

    b8 result  = true;
    b8 running = true;
    while (result && running) {

        result &= engine::core_frame_start  (core);
        result &= engine::core_frame_render (core);

        running &= !engine::core_should_quit(core);
    }

    //free memory
    engine::context_memory_reset(engine_context);

    //we're done
    return(result);
}