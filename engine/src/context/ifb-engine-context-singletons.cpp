#include "ifb-engine-internal-context.hpp"

#pragma once

/**********************************************************************************/
/* COMMIT                                                                         */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::context_singletons_commit_all(
    ifb_void) {

    //get the singletons
    IFBEngineContextSingletons& singletons_ref = ifb_engine::context_get_singletons();

    //assemble the size and alignment array
    const IFBEngineSizeAndAlignment singleton_size_and_alignment_array[] = {
        { sizeof(IFBEngineConfig), alignof(IFBEngineConfig) }
    };

    //get the count
    const ifb_u32 singleton_count = 
        sizeof(singleton_size_and_alignment_array) / 
        sizeof(IFBEngineSizeAndAlignment);

    //assemble the handle array
    IFBEngineContextSingletonHandle singleton_handle_array[singleton_count];

    //commit the singletons
    const ifb_b8 result = ifb_engine::context_memory_singleton_commit(
        singleton_count,
        singleton_size_and_alignment_array,
        singleton_handle_array);

    //we're done
    return(result);
}

/**********************************************************************************/
/* INSTANCES                                                                      */
/**********************************************************************************/

inline const IFBEngineConfig*
ifb_engine::context_singletons_get_config(
    ifb_void) {

    //get the singletons
    IFBEngineContextSingletons& singletons_ref = ifb_engine::context_get_singletons();

    //load the config
    IFBEngineConfig* config_ptr = ifb_engine::context_memory_singleton_load(singletons_ref.config);

    //we're done
    return(config_ptr);
}