#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <r-libs.hpp>

#include "ifb-engine-types.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-memory.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-font-ui.hpp"
#include "ifb-engine-platform.hpp"

typedef ifb_handle IFBEngineHandle;

namespace ifb_engine {

    ifb_external const IFBEngineHandle 
    engine_startup(
        const RMemoryReservationHandle r_memory_reservation_handle,
              ImGuiContext*            imgui_context,
              IFBEnginePlatformApi     platform_api);
	
    ifb_external const ifb_b8
    engine_update(const IFBEngineHandle ifb_engine_handle);

    ifb_external const ifb_b8
    engine_shutdown(
        const IFBEngineHandle ifb_engine_handle);
};

#endif //IFB_ENGINE_HPP