#ifndef IFB_ENGINE_CORE_HPP
#define IFB_ENGINE_CORE_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

struct IFBEngineCoreMemory {
    RHNDMemoryReservation rhnd_reservation_ifb;
    RHNDMemoryRegion      rhnd_region_engine_core;
    RHNDMemoryArena       rhnd_arena_system;
    RHNDMemoryArena       rhnd_arena_frame;
};

struct IFBEngineCore {
    IFBEngineCoreMemory memory;
};

namespace ifb_engine {

    ifb_internal const r_b8 
    core_initialize(
        const RHNDMemoryReservation in_rhnd_reservation_ifb,
        const RHNDMemoryRegion      in_rhnd_region_engine_core,
        const RHNDMemoryArena       in_rhnd_arena_system,
        const RHNDMemoryArena       in_rhnd_arena_frame,
              IFBEngineCore&       out_engine_core_ref);

};

#endif //IFB_ENGINE_CORE_HPP