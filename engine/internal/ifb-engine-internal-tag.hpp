#ifndef IFB_ENGINE_INTERNAL_TAG_HPP
#define IFB_ENGINE_INTERNAL_TAG_HPP

#include "ifb-engine.hpp"

struct IFBEngineTagTable {
    ifb_u32 tag_count_max;
    ifb_u32 handle_tag_buffer;
    ifb_u32 handle_hash_values;
};

namespace ifb_engine {

    IFBEngineTagTable* tag_table_from_handle  (const ifb_u32 tag_table_handle);
    IFBEngineTagTable* tag_table_from_context (ifb_void);


    const ifb_u32 tag_table_create(ifb_void);

    ifb_char*           tag_table_memory_values (IFBEngineTagTable* tag_table_ptr);
    IFBEngineHashValue* tag_table_memory_hashes (IFBEngineTagTable* tag_table_ptr);
}

#endif //IFB_ENGINE_INTERNAL_TAG_HPP