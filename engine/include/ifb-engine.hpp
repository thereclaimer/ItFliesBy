#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <ifb-common.hpp>

#include "ifb-engine-math.hpp"
#include "ifb-engine-memory.hpp"
#include "ifb-engine-asset.hpp"
#include "ifb-engine-font-ui.hpp"
#include "ifb-engine-platform.hpp"
#include "ifb-engine-algorithms.hpp"
#include "ifb-engine-tag.hpp"
#include "ifb-engine-allocators.hpp"
#include "ifb-engine-rendering.hpp"
#include "ifb-engine-tables.hpp"

enum IFBEngineState_ {
    IFBEngineState_NotRunning   = 0,
    IFBEngineState_Fatal        = 1,
    IFBEngineState_Startup      = 2,
    IFBEngineState_Shutdown     = 3,
    IFBEngineState_Idle         = 4,
    IFBEngineState_FrameExecute = 5,
};

typedef ifb_u32 ifb_engine_state_t;

#define IFB_ENGINE_CORE_STACK_SIZE                   ifb_macro_size_kilobytes(64)
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME    "CORE FRAME STACK"
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM "CORE PLATFORM STACK"
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW   "CORE WINDOW STACK"

struct IFBEngineContext {
    IFBEnginePlatform  platform;
    IFBUserInput       user_input;
    ifb_engine_state_t state;
    ifb_timems         time_initialized;
    ifb_u32            core_handle;
};

#define IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB ifb_macro_size_gigabytes(4)

namespace ifb_engine {

    ifb_api const ifb_b8
    engine_create_context(
        IFBEnginePlatformInfo& platform_info_ref,
        IFBEnginePlatformApi&  platform_api_ref);

    ifb_api const ifb_b8 engine_startup         (ifb_void);
    ifb_api const ifb_b8 engine_frame_execute   (ifb_void);
    ifb_api const ifb_b8 engine_shutdown        (ifb_void);
    ifb_api const ifb_b8 engine_destroy_context (ifb_void);

    ifb_api const ifb_memory engine_platform_alloc (const ifb_u32 size);
    ifb_api const ifb_memory engine_frame_alloc    (const ifb_u32 size);
};

#endif //IFB_ENGINE_HPP