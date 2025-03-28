#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"

namespace ifb_engine {

    IFBEngineContext*       context_initialize             (IFBMEMStack stack);
    IFBEngineMemoryManager* context_allocate_engine_memory (IFBMEMStack stack);
};

inline IFBEngineContext* 
ifb_engine::context_initialize(
    IFBMEMStack stack) {

    IFBEngineContext* context = ifb_memory_macro_stack_push_struct_absolute(stack,IFBEngineContext); 
    ifb_macro_assert(context);
    return(context);    
}

inline IFBEngineMemoryManager*
ifb_engine::context_allocate_engine_memory(
    IFBMEMStack stack) {

    //create the memory manager
    IFBEngineMemoryManager* memory_manager = ifb_engine::memory_manager_create(global_stack_handle);

    //allocate engine memory
    ifb_engine::memory_manager_allocate_core_systems(memory_manager);


}
