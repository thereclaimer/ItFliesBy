#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <r-libs.hpp>

#include "ifb-engine-types.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-user-input.hpp"
#include "ifb-engine-memory.hpp"
#include "ifb-engine-scopes.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-font-ui.hpp"
#include "ifb-engine-platform.hpp"

enum IFBEngineState_ {
    IFBEngineState_NotRunning  = 0,
    IFBEngineState_Startup     = 1,
    IFBEngineState_Shutdown    = 2,
    IFBEngineState_Idle        = 3,
    IFBEngineState_FrameStart  = 4,
    IFBEngineState_FrameRender = 5,
};

typedef ifb_u32 IFBEngineState;

struct IFBEngineMemory {
    ifb_memory start;
    ifb_u32    page_size;
    ifb_u32    page_count_total;
    ifb_u32    page_count_used;
};

struct IFBEnginePages {
    ifb_u32 memory_manager;
    ifb_u32 asset_manager;
    ifb_u32 tools;
};

struct IFBEngineContext {
    IFBEngineMemory    memory;
    IFBEngineUserInput user_input;
    IFBEnginePages     pages;
    IFBEngineState     state;
    ifb_timems         time_initialized;
};

#define IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB ifb_engine_macro_size_gigabytes(4)

namespace ifb_engine {

    ifb_external const ifb_b8
    engine_create_context(
              IFBEnginePlatformApi& in_platform_api,
        const ifb_memory            in_platform_memory_reservation_start,
        const ifb_size              in_platform_memory_reservation_size,
              IFBEngineContext&     out_engine_context_ref);

    ifb_external const IFBEngineState engine_state           (IFBEngineContext* engine_context);
    ifb_external const ifb_b8         engine_startup         (IFBEngineContext* engine_context);
    ifb_external const ifb_b8         engine_frame_start     (IFBEngineContext* engine_context);
    ifb_external const ifb_b8         engine_frame_render    (IFBEngineContext* engine_context);
    ifb_external const ifb_b8         engine_shutdown        (IFBEngineContext* engine_context);
    ifb_external const ifb_b8         engine_destroy_context (IFBEngineContext* engine_context);
};

#endif //IFB_ENGINE_HPP