#ifndef IFB_ENGINE_TAG_HPP
#define IFB_ENGINE_TAG_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-algorithms.hpp"

#define IFB_ENGINE_TAG_LENGTH    32
#define IFB_ENGINE_TAG_COUNT_MAX 1024

struct IFBEngineTag {
    ifb_u32            tag_index;
    ifb_cstr           tag_value;
    IFBEngineHashValue tag_hash;
};

namespace ifb_engine {

    ifb_api const ifb_b8   tag_create  (const ifb_cstr in_tag_value, ifb_u32& out_tag_index_ref); 
    ifb_api const ifb_b8   tag_index   (const ifb_cstr in_tag_value, ifb_u32& out_tag_index_ref);
    ifb_api const ifb_b8   tag_destroy (const ifb_u32  tag_index);
    ifb_api const ifb_cstr tag_value   (const ifb_u32  tag_index);
};

#endif //IFB_ENGINE_TAG_HPP