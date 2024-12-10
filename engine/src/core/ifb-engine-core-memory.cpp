#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"

inline const ifb_ptr 
ifb_engine::core_memory_get_pointer(
    const IFBEngineCore* ptr_core, 
    const ifb_u32        offset) {

    const IFBEngineMemory* ptr_engine_memory = ifb_engine::core_get_pointer_memory(ptr_core);
    
    const ifb_address reservation_start = ptr_engine_memory->reservation_start;
    const ifb_address offset_start      = reservation_start + offset;
    const ifb_ptr     offset_ptr        = (ifb_ptr)offset_start; 

    return(offset_ptr);
}