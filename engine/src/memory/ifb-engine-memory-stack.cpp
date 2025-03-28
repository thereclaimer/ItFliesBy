#pragma once

#include "ifb-engine-memory.hpp"

inline IFBEngineGraphicsManager*
ifb_engine::memory_stack_get_manager_graphics(
    const IFBEngineMemoryStack* stack) {

    IFBEngineGraphicsManager* pointer = (IFBEngineGraphicsManager*)(
        stack->start + 
        stack->offsets.core_manager_graphics);

    return(pointer);
}

inline IFBEngineFileManager*
ifb_engine::memory_stack_get_manager_files(
    const IFBEngineMemoryStack* stack) {


    IFBEngineFileManager* pointer = (IFBEngineFileManager*)(
        stack->start + 
        stack->offsets.core_manager_files);

    return(pointer);
}

inline IFBEngineThreadManager*
ifb_engine::memory_stack_get_manager_threads(
    const IFBEngineMemoryStack* stack) {


    IFBEngineThreadManager* pointer = (IFBEngineThreadManager*)(
        stack->start + 
        stack->offsets.core_manager_threads);

    return(pointer);
}

inline IFBVoid 
ifb_engine::memory_stack_get_core(
    const IFBEngineMemoryStack* stack,
          IFBEngineCore&        core) {

    ifb_macro_assert(stack);
    core.graphics = ifb_engine::memory_stack_get_manager_graphics (stack);
    core.files    = ifb_engine::memory_stack_get_manager_files    (stack);
    core.threads  = ifb_engine::memory_stack_get_manager_threads  (stack);
}