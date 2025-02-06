#pragma once

#include <ifb-memory.hpp>

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-config.hpp"

#include "ifb-engine-memory-singletons.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_CORE_SIZE_STACK       ifb_macro_size_kilobytes(IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB)
#define IFB_ENGINE_MEMORY_CORE_SIZE_RESERVATION ifb_macro_size_gigabytes(IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB)

namespace ifb_engine {

    ifb_global ifb_byte        _memory_core_stack_buffer[IFB_ENGINE_MEMORY_CORE_SIZE_STACK]; 
    ifb_global IFBMemoryHandle _memory_core_handle;
};

/**********************************************************************************/
/* RESERVE / RELEASE                                                              */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::memory_core_reserve(
    const IFBPlatformApi& platform_api_ref) {

    ifb_b8 result = true;

    //sizes
    const ifb_u32 core_size_stack       = IFB_ENGINE_MEMORY_CORE_SIZE_STACK;
    const ifb_u64 core_size_reservation = IFB_ENGINE_MEMORY_CORE_SIZE_RESERVATION; 

    //create the memory handle
    _memory_core_handle = ifb_memory::create(
        platform_api_ref,
        _memory_core_stack_buffer,
        core_stack_size);
    ifb_macro_assert(_memory_core_handle);

    //reserve the memory    
    result = ifb_memory::reserve(_memory_core_handle,core_size_reservation);
    ifb_macro_assert(result);

    //create the singleton stack
    result = ifb_engine::memory_singleton_stack_commit(_memory_core_handle);
    ifb_macro_assert(result);

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::memory_core_release(
    ifb_void) {

}

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/


inline const ifb_u64
ifb_engine::memory_core_get_reservation_size_total(
    ifb_void) {

}

inline const ifb_u64
ifb_engine::memory_core_get_reservation_size_free(
    ifb_void) {

}

inline const ifb_u64
ifb_engine::memory_core_get_reservation_size_used(
    ifb_void) {

}

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

inline const ifb_u32
ifb_engine::memory_core_get_stack_size_total(
    ifb_void) {

}

inline const ifb_u32
ifb_engine::memory_core_get_stack_size_free(
    ifb_void) {

}

inline const ifb_u32
ifb_engine::memory_core_get_stack_size_used(
    ifb_void) {

}