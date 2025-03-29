#pragma once

#include "ifb-engine-memory.hpp"

#define macro_calculate_stack_pointer(stack,offset) ( \
    stack->start +                                    \
    (offset * ifb_engine::_memory_manager_sizes.stack_offset_stride))

inline IFBEngineGraphicsManager*
ifb_engine::memory_stack_get_manager_graphics(
    const IFBEngineMemoryStack* stack) {

    IFBEngineGraphicsManager* pointer = (IFBEngineGraphicsManager*)macro_calculate_stack_pointer(
        stack,
        IFBEngineMemoryStackOffset_Core_ManagerGraphics);

    return(pointer);
}

inline IFBEngineFileManager*
ifb_engine::memory_stack_get_manager_files(
    const IFBEngineMemoryStack* stack) {

    IFBEngineFileManager* pointer = (IFBEngineFileManager*)macro_calculate_stack_pointer(
        stack,
        IFBEngineMemoryStackOffset_Core_ManagerFiles);

    return(pointer);
}

inline IFBEngineThreadManager*
ifb_engine::memory_stack_get_manager_threads(
    const IFBEngineMemoryStack* stack) {

    IFBEngineThreadManager* pointer = (IFBEngineThreadManager*)macro_calculate_stack_pointer(
        stack,
        IFBEngineMemoryStackOffset_Core_ManagerThreads);

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