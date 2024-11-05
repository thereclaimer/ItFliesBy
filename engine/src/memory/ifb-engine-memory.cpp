#pragma once

#include "ifb-engine-internal-memory.hpp"

#include "ifb-engine-memory-manager.cpp"
#include "ifb-engine-memory-reservation.cpp"
#include "ifb-engine-memory-arena-header.cpp"
#include "ifb-engine-memory-arena-detail.cpp"
#include "ifb-engine-memory-arena.cpp"

ifb_external const ifb_memory 
ifb_engine::memory_pointer(
    IFBEngineMemoryHandle& memory_handle_ref) {

    IFBEngineMemoryManager& memory_manager_ref = ifb_engine::memory_manager_ref();

    IFBEngineMemoryArenaHandle arena_handle;
    arena_handle.memory_table_index_detail = memory_handle_ref.memory_table_index_detail;

    const ifb_memory memory_pointer = ifb_engine::memory_reservation_get_pointer(
        memory_manager_ref.reservation,
        memory_handle_ref.page_number,
        memory_handle_ref.page_offset);

    return(memory_pointer);
}