#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-config.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineConfig config;
    IFBPlatformApi  platform_api;
    IFBEngineMemory memory;
};

namespace ifb_engine {

    const IFBPlatformApi&  context_get_platform_api (ifb_void);
    const IFBEngineConfig& context_get_config       (ifb_void);
    IFBEngineMemory&       context_get_memory       (ifb_void); 
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP