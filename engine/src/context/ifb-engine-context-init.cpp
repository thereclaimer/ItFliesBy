#pragma once

#include "ifb-engine-api.hpp"
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    IFBVoid context_init_step_0_validate_args     (IFBEngineInit& ref_init);
    IFBVoid context_init_step_1_set_platform_api  (IFBEngineInit& ref_init);
    IFBVoid context_init_step_2_create_core       (IFBEngineInit& ref_init);
    IFBVoid context_init_step_3_create_singletons (IFBEngineInit& ref_init);
    IFBVoid context_init_step_4_commit_arenas     (IFBEngineInit& ref_init);
};

/**********************************************************************************/
/* INITIALIZATION STEPS                                                           */
/**********************************************************************************/

inline IFBVoid
ifb_engine::context_init_step_0_validate_args(
    IFBEngineInit& ref_init) {

    //init result
    if (ref_init.result) {
        ref_init.result &= (ref_init.args    != NULL);
        ref_init.result &= (ref_init.context != NULL);
    }
    
    //arg pointers
    if (ref_init.result) {
        ref_init.result &= (ref_init.args->platform_api   != NULL);
        ref_init.result &= (ref_init.args->memory_context != NULL);
    }
}

inline IFBVoid
ifb_engine::context_init_step_1_set_platform_api(
    IFBEngineInit& ref_init) {

    if (ref_init.result) {
        ref_init.result &= ifb_platform::set_api(ref_init.args->platform_api);
    } 
}

inline IFBVoid 
ifb_engine::context_init_step_2_create_core(
    IFBEngineInit& ref_init) {

    if (ref_init.result) {

        //create the core
        ref_init.context->ptr_core = ifb_engine::core_create(ref_init.args->memory_context);
        
        //make sure its valid
        ref_init.result &= (ref_init.context->ptr_core != NULL);
    }
}

inline IFBVoid 
ifb_engine::context_init_step_3_create_singletons(
    IFBEngineInit& ref_init) {

    if (ref_init.result) {
    
        //commit the singletons
        ref_init.context->ptr_singletons = ifb_engine::singletons_create(ref_init.context->ptr_core);

        //make sure that worked
        ref_init.result &= (ref_init.context->ptr_singletons != NULL);
    }
}

inline IFBVoid 
ifb_engine::context_init_step_4_commit_arenas(
    IFBEngineInit& ref_init) {

    if (ref_init.result) {

        //load the arena singletons
        IFBEngineArenas* ptr_arenas = ifb_engine::singletons_load_arenas(ref_init.context->ptr_singletons);
        
        //commit the arenas
        ptr_arenas->platform  = ifb_engine::core_memory_commit_arena(ref_init.context->ptr_core);
        ptr_arenas->graphics  = ifb_engine::core_memory_commit_arena(ref_init.context->ptr_core);
        ptr_arenas->rendering = ifb_engine::core_memory_commit_arena(ref_init.context->ptr_core);

        //sanity check        
        ref_init.result &= (ptr_arenas->platform  != NULL); 
        ref_init.result &= (ptr_arenas->graphics  != NULL); 
        ref_init.result &= (ptr_arenas->rendering != NULL); 
    }
}