#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-platform.hpp"
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

#define ifb_engine_platform_file_open_read_only  _ifb_engine_ptr->platform.open_read_only
#define ifb_engine_platform_file_open_read_write _ifb_engine_ptr->platform.open_read_write
#define ifb_engine_platform_file_close           _ifb_engine_ptr->platform.close
#define ifb_engine_platform_file_size            _ifb_engine_ptr->platform.size
#define ifb_engine_platform_file_read            _ifb_engine_ptr->platform.read
#define ifb_engine_platform_file_write           _ifb_engine_ptr->platform.write

#endif //IFB_ENGINE_INTERNAL_HPP