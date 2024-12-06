#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tools.hpp"
#include "ifb-engine-internal-allocators.hpp"
#include "ifb-engine-internal-global.hpp"

struct IFBEngineContext {
    struct {
        IFBEngineGlobalHandle core;       // IFBEngineCore
        IFBEngineGlobalHandle user_input; // IFBEngineUserInput
    } global_handles;
    IFBEngineState state;
    ifb_timems     time_initialized;
};

namespace ifb_engine {

    IFBEngineCore* context_get_core_pointer       (IFBEngineContext* ptr_engine_context);
    IFBUserInput*  context_get_user_input_pointer (IFBEngineContext* ptr_engine_context);
};

#endif //IFB_ENGINE_INTERNAL_HPP