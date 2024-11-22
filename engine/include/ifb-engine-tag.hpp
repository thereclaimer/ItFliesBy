#ifndef IFB_ENGINE_TAG_HPP
#define IFB_ENGINE_TAG_HPP

#include <ifb-common.hpp>

#include "ifb-engine-tables.hpp"
#include "ifb-engine-algorithms.hpp"

#define IFB_ENGINE_TAG_LENGTH    32
#define IFB_ENGINE_TAG_COUNT_MAX 1024

struct IFBEngineTag {
    IFBEngineTagId tag_id;
    ifb_cstr       tag_value;
    IFBHashValue   tag_hash;
};

namespace ifb_engine {

    ifb_api const ifb_b8   tag_create (const ifb_cstr in_tag_value, IFBEngineTagId& out_tag_id_ref); 
    ifb_api const ifb_b8   tag_id     (const ifb_cstr in_tag_value, IFBEngineTagId& out_tag_id_ref);
    
    ifb_api const ifb_b8   tag_destroy (const IFBEngineTagId tag_id);
    ifb_api const ifb_cstr tag_value   (const IFBEngineTagId tag_id);
};

#endif //IFB_ENGINE_TAG_HPP