#ifndef IFB_ENGINE_ALGORITHMS_HPP
#define IFB_ENGINE_ALGORITHMS_HPP

#include "ifb-engine-types.hpp"
#include "ifb-engine-scopes.hpp"

/**********************************************************************************/
/* HASH                                                                           */
/**********************************************************************************/

union IFBEngineHashValue {
    struct {
        ifb_u32 h1;
        ifb_u32 h2;
        ifb_u32 h3;
        ifb_u32 h4;
    };
    ifb_u32 h[4];
};

namespace ifb_engine {

    ifb_api const ifb_u32 
    hash_cstr(
        const ifb_cstr             in_cstr,
        const ifb_u32              in_cstr_length_max,
              IFBEngineHashValue& out_cstr_hash_value_ref);

    ifb_api const ifb_b8
    hash_collision_check(
              IFBEngineHashValue& hash_value_ref,
        const IFBEngineHashValue* hash_value_array_ptr,
        const ifb_u32             hash_value_array_count);

    ifb_api const ifb_b8
    hash_next_clear_value(
        const IFBEngineHashValue* in_hash_value_array_ptr,
        const ifb_u32             in_hash_value_array_count,
              ifb_u32&           out_hash_index_ref);

    ifb_api const ifb_b8
    hash_search(
              IFBEngineHashValue& in_hash_value_ref,
        const IFBEngineHashValue* in_hash_value_array_ptr,
        const ifb_u32             in_hash_value_array_count,
              ifb_u32&           out_hash_index_ref);
};

#endif //IFB_ENGINE_ALGORITHMS_HPP