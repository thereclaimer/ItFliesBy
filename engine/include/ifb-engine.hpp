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
#include "ifb-engine-algorithms.hpp"
#include "ifb-engine-tag.hpp"
#include "ifb-engine-allocators.hpp"


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
    ifb_u32 page_size;
    ifb_u32 page_count_total;
    ifb_u32 page_count_used;
};

struct IFBEngineCore {
    ifb_u32 handle_memory_manager;
    ifb_u32 handle_tag_table;
    ifb_u32 handle_allocator_manager;
    ifb_u32 handle_asset_manager;
};

struct IFBEngineContext {
    IFBEngineMemory    memory;
    IFBEngineUserInput user_input;
    IFBEngineState     state;
    IFBEngineCore      core;
    ifb_timems         time_initialized;
};

#define IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB ifb_engine_macro_size_gigabytes(4)

namespace ifb_engine {

    ifb_api const ifb_b8
    engine_create_context(
              IFBEnginePlatformApi& platform_api_ref,
        const ifb_memory            memory_reservation_start,
        const ifb_size              memory_page_size,
        const ifb_size              memory_page_count);

    ifb_api const IFBEngineState engine_state           (IFBEngineContext* engine_context);
    ifb_api const ifb_b8         engine_startup         (IFBEngineContext* engine_context);
    ifb_api const ifb_b8         engine_frame_start     (IFBEngineContext* engine_context);
    ifb_api const ifb_b8         engine_frame_render    (IFBEngineContext* engine_context);
    ifb_api const ifb_b8         engine_shutdown        (IFBEngineContext* engine_context);
    ifb_api const ifb_b8         engine_destroy_context (IFBEngineContext* engine_context);
};

#endif //IFB_ENGINE_HPP