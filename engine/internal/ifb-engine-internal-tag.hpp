#ifndef IFB_ENGINE_INTERNAL_TAG_HPP
#define IFB_ENGINE_INTERNAL_TAG_HPP

#include "ifb-engine.hpp"

struct IFBEngineTagManager {
    ifb_u32 tag_count_max;
    ifb_u32 handle_tag_buffer;
    ifb_u32 handle_hash_values;
};

namespace ifb_engine {

    IFBEngineTagManager* tag_manager_from_handle  (const ifb_u32 tag_manager_handle);
    IFBEngineTagManager* tag_manager_from_context (ifb_void);

    const ifb_u32 tag_manager_create(ifb_void);

    ifb_char*     tag_manager_memory_values (IFBEngineTagManager* tag_manager_ptr);
    IFBHashValue* tag_manager_memory_hashes (IFBEngineTagManager* tag_manager_ptr);
}

#endif //IFB_ENGINE_INTERNAL_TAG_HPP