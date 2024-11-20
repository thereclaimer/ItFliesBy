#ifndef IFB_ENGINE_TAG_HPP
#define IFB_ENGINE_TAG_HPP

#include <ifb-common.hpp>

#include "ifb-engine-algorithms.hpp"

#define IFB_ENGINE_TAG_LENGTH    32
#define IFB_ENGINE_TAG_COUNT_MAX 1024

struct IFBEngineTag {
    ifb_table_index_tag tag_index;
    ifb_cstr            tag_value;
    IFBHashValue        tag_hash;
};

namespace ifb_engine {

    ifb_api const ifb_b8   tag_create  (const ifb_cstr in_tag_value, ifb_index_tag_t& out_tag_index_ref); 
    ifb_api const ifb_b8   tag_index   (const ifb_cstr in_tag_value, ifb_index_tag_t& out_tag_index_ref);
    
    ifb_api const ifb_b8   tag_destroy (const ifb_index_tag_t tag_index);
    ifb_api const ifb_cstr tag_value   (const ifb_index_tag_t tag_index);
};

#endif //IFB_ENGINE_TAG_HPP