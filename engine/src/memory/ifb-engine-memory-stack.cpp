#pragma once

#include "ifb-engine-memory.hpp"

#define macro_calculate_stack_pointer(memory,singleton,type) (type*)&memory->stack.singleton_buffer[singleton]

inline IFBEngineContext*
ifb_engine::memory_stack_get_context(
    const IFBEngineMemory* memory) {

    IFBEngineContext* pointer = macro_calculate_stack_pointer(
        memory, 
        IFBEngineSingleton_Context,
        IFBEngineContext);

    return(pointer);
}

inline IFBEngineGraphicsManager*
ifb_engine::memory_stack_get_manager_graphics(
    const IFBEngineMemory* memory) {

    IFBEngineGraphicsManager* pointer = macro_calculate_stack_pointer(
        memory,
        IFBEngineSingleton_Core_ManagerGraphics,
        IFBEngineGraphicsManager);
    
    return(pointer);
}

inline IFBEngineFileManager*
ifb_engine::memory_stack_get_manager_files(
    const IFBEngineMemory* memory) {

    IFBEngineFileManager* pointer = macro_calculate_stack_pointer(
        memory,
        IFBEngineSingleton_Core_ManagerFiles,
        IFBEngineFileManager);
    
    return(pointer);
}

inline IFBEngineThreadManager*
ifb_engine::memory_stack_get_manager_threads(
    const IFBEngineMemory* memory) {

    IFBEngineThreadManager* pointer = macro_calculate_stack_pointer(
        memory,
        IFBEngineSingleton_Core_ManagerThreads,
        IFBEngineThreadManager);

    return(pointer);
}