#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <r-libs.hpp>

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-asset.hpp"

typedef ifb_handle IFBEngineHandle;

namespace ifb_engine {

    ifb_external const IFBEngineHandle 
    engine_startup(
        const RHNDMemoryReservation r_memory_reservation_handle);
	
    ifb_external const ifb_b8
    engine_shutdown(
        const IFBEngineHandle ifb_engine_handle);
};

#endif //IFB_ENGINE_HPP