#pragma once

#include "ifb-engine-memory.hpp"

#define macro_calculate_stack_pointer(stack,offset) ( \
    stack->start +                                    \
    (offset * ifb_engine::_memory_sizes.stack_offset_stride))

#define macro_calculate_stack_pointer_core_manager_graphics(stack) (IFBEngineGraphicsManager*)macro_calculate_stack_pointer(stack, IFBEngineMemoryStackOffset_Core_ManagerGraphics)
#define macro_calculate_stack_pointer_core_manager_files(stack)        (IFBEngineFileManager*)macro_calculate_stack_pointer(stack, IFBEngineMemoryStackOffset_Core_ManagerFiles)
#define macro_calculate_stack_pointer_core_manager_threads(stack)    (IFBEngineThreadManager*)macro_calculate_stack_pointer(stack, IFBEngineMemoryStackOffset_Core_ManagerThreads)

inline IFBEngineGraphicsManager*
ifb_engine::memory_stack_get_manager_graphics(
    const IFBEngineMemoryStack* stack) {

    IFBEngineGraphicsManager* pointer = macro_calculate_stack_pointer_core_manager_graphics(stack);

    return(pointer);
}

inline IFBEngineFileManager*
ifb_engine::memory_stack_get_manager_files(
    const IFBEngineMemoryStack* stack) {

    IFBEngineFileManager* pointer = macro_calculate_stack_pointer_core_manager_files(stack);

    return(pointer);
}

inline IFBEngineThreadManager*
ifb_engine::memory_stack_get_manager_threads(
    const IFBEngineMemoryStack* stack) {

    IFBEngineThreadManager* pointer =  macro_calculate_stack_pointer_core_manager_threads(stack);

    return(pointer);
}

inline IFBVoid 
ifb_engine::memory_stack_get_core(
    const IFBEngineMemoryStack* stack,
          IFBEngineCore*        core) {

    ifb_macro_assert(stack);
    ifb_macro_assert(core);
    core->graphics = ifb_engine::memory_stack_get_manager_graphics (stack);
    core->files    = ifb_engine::memory_stack_get_manager_files    (stack);
    core->threads  = ifb_engine::memory_stack_get_manager_threads  (stack);
}