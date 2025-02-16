#include "ifb-engine-internal-context.hpp"

#pragma once

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline IFBEngineContextSingletons*
ifb_engine::context_singletons_commit_all(
    ifb_void) {

    //get the core
    IFBEngineCore* ptr_core = ifb_engine::context_get_core();

    //commit all singletons
    const IFBEngineSingletonHandle singleton_struct  = ifb_engine_macro_core_memory_singleton_commit_type(ptr_core, IFBEngineContextSingletons);
    const IFBEngineSingletonHandle singleton_config  = ifb_engine_macro_core_memory_singleton_commit_type(ptr_core, IFBEngineConfig);
    const IFBEngineSingletonHandle singleton_input   = ifb_engine_macro_core_memory_singleton_commit_type(ptr_core, IFBInput);

    //ensure singletons are committed
    ifb_b8 all_singletons_committed = true;
    all_singletons_committed &= (singleton_struct.value != NULL);
    all_singletons_committed &= (singleton_config.value != NULL);
    all_singletons_committed &= (singleton_input.value  != NULL);
    if (!all_singletons_committed) return(NULL);

    //get the singletons pointer
    IFBEngineContextSingletons* ptr_singletons = ifb_engine_macro_core_memory_singleton_load_type(ptr_core,singleton_struct,IFBEngineContextSingletons);
    ifb_macro_assert(ptr_singletons);

    //initialize the singletons struct
    ptr_singletons->singletons = singleton_struct;
    ptr_singletons->config     = singleton_config;
    ptr_singletons->input      = singleton_input;

    //we're done
    return(ptr_singletons);
}

/**********************************************************************************/
/* LOAD                                                                           */
/**********************************************************************************/

inline IFBEngineConfig*
ifb_engine::context_singletons_get_config(
    ifb_void) {

    //get the singletons
    const IFBEngineContextSingletons& singletons_ref = ifb_engine::context_get_singletons();

    //load the config
    IFBEngineConfig* config_ptr = (IFBEngineConfig*)ifb_engine::context_memory_singleton_load(singletons_ref.config);

    //we're done
    return(config_ptr);
}

inline IFBInput*
ifb_engine::context_singletons_load_input(
    ifb_void) {

    //get the singletons
    const IFBEngineContextSingletons& singletons_ref = ifb_engine::context_get_singletons();

    //load the input
    IFBInput* ptr_input = 
}