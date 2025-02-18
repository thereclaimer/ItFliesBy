#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include <ifb-memory.hpp>

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-singletons.hpp"

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineCore*              ptr_core;
    IFBEngineSingletons*        ptr_singletons;
};

namespace ifb_engine {
    
    IFBEngineContext&    context_ref                  (IFBVoid);
    IFBEngineCore*       context_get_ptr_core         (IFBVoid); 
    IFBEngineSingletons* context_get_ptr_singletons   (IFBVoid);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP