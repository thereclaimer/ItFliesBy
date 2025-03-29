#pragma once

#include "ifb-engine-memory.hpp"

#define macro_calculate_stack_pointer(memory,offset) ( \
    memory->stack.stack_memory_64k.start +                                    \
    (offset * memory->stack.stack_memory_64k.stride))

#define macro_calculate_stack_pointer_context(memory)                       (IFBEngineContext*)macro_calculate_stack_pointer(memory, IFBEngineStackOffset_Context)
#define macro_calculate_stack_pointer_core_manager_graphics(memory) (IFBEngineGraphicsManager*)macro_calculate_stack_pointer(memory, IFBEngineStackOffset_Core_ManagerGraphics)
#define macro_calculate_stack_pointer_core_manager_files(memory)        (IFBEngineFileManager*)macro_calculate_stack_pointer(memory, IFBEngineStackOffset_Core_ManagerFiles)
#define macro_calculate_stack_pointer_core_manager_threads(memory)    (IFBEngineThreadManager*)macro_calculate_stack_pointer(memory, IFBEngineStackOffset_Core_ManagerThreads)

inline IFBEngineContext*
ifb_engine::memory_stack_get_context(
    const IFBEngineMemory* memory) {

    IFBEngineContext* pointer = macro_calculate_stack_pointer_context(memory);
    return(pointer);
}

inline IFBEngineGraphicsManager*
ifb_engine::memory_stack_get_manager_graphics(
    const IFBEngineMemory* memory) {

    IFBEngineGraphicsManager* pointer = macro_calculate_stack_pointer_core_manager_graphics(memory);
    return(pointer);
}

inline IFBEngineFileManager*
ifb_engine::memory_stack_get_manager_files(
    const IFBEngineMemory* memory) {

    IFBEngineFileManager* pointer = macro_calculate_stack_pointer_core_manager_files(memory);
    return(pointer);
}

inline IFBEngineThreadManager*
ifb_engine::memory_stack_get_manager_threads(
    const IFBEngineMemory* memory) {

    IFBEngineThreadManager* pointer =  macro_calculate_stack_pointer_core_manager_threads(memory);
    return(pointer);
}

inline IFBVoid 
ifb_engine::memory_stack_get_core(
    const IFBEngineMemory* memory,
          IFBEngineCore*   core) {

    ifb_macro_assert(memory);
    ifb_macro_assert(core);
    core->graphics = ifb_engine::memory_stack_get_manager_graphics (memory);
    core->files    = ifb_engine::memory_stack_get_manager_files    (memory);
    core->threads  = ifb_engine::memory_stack_get_manager_threads  (memory);
}