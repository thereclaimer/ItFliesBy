#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tools.hpp"

ifb_global IFBEngineContext* _engine_context;



namespace ifb_engine {

      inline const ifb_b8     context_initialized  (ifb_void) { return(_engine_context != NULL);     }
      inline const ifb_memory context_base_pointer (ifb_void) { return((ifb_memory)_engine_context); }

      inline IFBEngineMemory&    context_memory       (ifb_void) { return(_engine_context->memory);     }
      inline IFBEngineUserInput& context_user_input   (ifb_void) { return(_engine_context->user_input); }
      inline IFBEngineCore&      context_core         (ifb_void) { return(_engine_context->core);       }
};

#endif //IFB_ENGINE_INTERNAL_HPP