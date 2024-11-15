#ifndef IFB_ENGINE_HPP
#define IFB_ENGINE_HPP

#include <r-libs.hpp>

#include "ifb-engine-types.hpp"
#include "ifb-engine-macros.hpp"
#include "ifb-engine-math.hpp"
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
    IFBEngineState_Fatal       = 1,
    IFBEngineState_Startup     = 2,
    IFBEngineState_Shutdown    = 3,
    IFBEngineState_Idle        = 4,
    IFBEngineState_FrameStart  = 5,
    IFBEngineState_FrameReady  = 6,
    IFBEngineState_FrameRender = 7
};

typedef ifb_u32 IFBEngineState;

struct IFBEngineMemory { 
    ifb_u32 page_size;
    ifb_u32 page_count_total;
    ifb_u32 page_count_used;
};

#define IFB_ENGINE_CORE_STACK_SIZE                   ifb_engine_macro_size_kilobytes(64)
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME    "CORE FRAME STACK"
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM "CORE PLATFORM STACK"
#define IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW   "CORE WINDOW STACK"

struct IFBEngineCore {

    struct {
        ifb_u32 handle_memory;
        ifb_u32 handle_tag;
        ifb_u32 handle_allocators;
        ifb_u32 handle_assets;
    } managers;

    struct {
        ifb_u32 frame;
        ifb_u32 platform; 
        ifb_u32 window; 
    } stack_allocators;
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
        IFBEnginePlatformInfo& platform_info_ref,
        IFBEnginePlatformApi&  platform_api_ref);

    ifb_api const ifb_b8 engine_startup         (ifb_void);
    ifb_api const ifb_b8 engine_frame_start     (ifb_void);
    ifb_api const ifb_b8 engine_frame_render    (ifb_void);
    ifb_api const ifb_b8 engine_shutdown        (ifb_void);
    ifb_api const ifb_b8 engine_destroy_context (ifb_void);

    ifb_api const ifb_memory engine_platform_alloc (const ifb_u32 size);
    ifb_api const ifb_memory engine_frame_alloc    (const ifb_u32 size);
};

#endif //IFB_ENGINE_HPP