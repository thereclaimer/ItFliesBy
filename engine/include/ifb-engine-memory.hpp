#ifndef IFB_ENGINE_MEMORY_HPP
#define IFB_ENGINE_MEMORY_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-macros.hpp"

struct IFBEngineMemoryReservation {
    ifb_u32    page_size;
    ifb_u32    page_count_total;
    ifB_u32    page_count_used;
};

struct IFBEngineMemoryPageCommit {
    ifb_u32 page_start;
    ifb_u32 page_count;
};

struct IFBEngineMemory {
    ifb_u32 page_start;
    ifb_u32 page_offset;
};

namespace ifb_engine {

    const ifb_b8
    memory_reservation_commit_pages(
              IFBEngineMemoryReservation& in_reservation_ref,
        const ifb_u32                     in_page_count,
              ifb_u32&                   out_page_start_ref);
};

struct IFBEngineMemoryArena {
    ifb_u32 arena_id;
    ifb_u32 page_start;
    ifb_u32 page_count;
    ifb_u32 page_stride;
};

namespace ifb_engine {

    const ifb_b8
    memory_arena_create(
        IFBEngineMemoryReservation& reservation_ref,
        const ifb_u32 page_stride,
        const ifb_u32 page_count;        
    );
};

struct IFBEngineMemoryManager {
    IFBEngineMemoryReservation reservation;
};

#endif //IFB_ENGINE_MEMORY_HPP