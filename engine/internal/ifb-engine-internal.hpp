#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-tools.hpp"

struct IFBEngineCore;
struct IFBEngineAssetManager;

struct IFBEngine {
    IFBEngineCore         core;
    IFBEngineAssetManager asset_manager;
    IFBEngineTools        tools;
};

ifb_global IFBEngine* _ifb_engine_ptr;

namespace ifb_engine {

    inline IFBEngineCore&         core_ref          (ifb_void) { return(_ifb_engine_ptr->core);          }
    inline IFBEngineAssetManager& asset_manager_ref (ifb_void) { return(_ifb_engine_ptr->asset_manager); }

};

#endif //IFB_ENGINE_INTERNAL_HPP