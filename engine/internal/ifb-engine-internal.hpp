#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tools.hpp"

struct IFBEngineCore;
struct IFBEngineAssetManager;
struct IFBEngineMemoryManager;

struct IFBEngine {
    IFBEngineCore          core;
    IFBEngineMemoryManager memory_manager;
    IFBEngineAssetManager  asset_manager;
    IFBEngineTools         tools;
};

ifb_global IFBEngine _ifb_engine;

namespace ifb_engine {

    inline IFBEngineCore&          core_ref           (ifb_void) { return(_ifb_engine.core);           }
    inline IFBEngineMemoryManager& memory_manager_ref (ifb_void) { return(_ifb_engine.memory_manager); }
    inline IFBEngineAssetManager&  asset_manager_ref  (ifb_void) { return(_ifb_engine.asset_manager);  }
};

#endif //IFB_ENGINE_INTERNAL_HPP