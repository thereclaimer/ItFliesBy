#ifndef IFB_ENGINE_INTERNAL_HPP
#define IFB_ENGINE_INTERNAL_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-asset.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"
#include "ifb-engine-internal-tools.hpp"
#include "ifb-engine-internal-tag.hpp"
#include "ifb-engine-internal-allocators.hpp"

ifb_global IFBEngineContext* _engine_context;

namespace ifb_engine {

      inline const ifb_b8              context_initialized  (ifb_void) { return(_engine_context != NULL);      }
      inline const ifb_memory          context_base_pointer (ifb_void) { return((ifb_memory)_engine_context);  }
      inline const ifb_handle_memory_t context_core_handle  (ifb_void) { return(_engine_context->core_handle); }

      inline const ifb_u32 context_platform_page_size       (ifb_void) { return(_engine_context->platform.page_size);        }
      inline const ifb_u32 context_platform_page_count_total(ifb_void) { return(_engine_context->platform.page_count_total); }
      inline const ifb_u32 context_platform_page_count_used (ifb_void) { return(_engine_context->platform.page_count_used);  }

      inline ifb_void context_platform_page_count_used_update(const ifb_u32 page_count_used) { _engine_context->platform.page_count_used = page_count_used; }
};

#endif //IFB_ENGINE_INTERNAL_HPP