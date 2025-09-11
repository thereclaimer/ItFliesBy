#pragma once

#include "ifb-engine-id.hpp"

namespace ifb {

    IFB_ENG_API eng_void
    eng_id_generate(
        const eng_u32    in_count,
        const eng_u32    in_stride,
        const eng_byte*  in_data,
        eng_id_u128_t*  out_id) {

        const bool is_valid = (
            in_count  != 0    &&
            in_stride != 0    &&
            in_data   != NULL &&
            out_id    != NULL
        );
        if (!is_valid) return;

        (eng_void)sld::hash_data_batch(
            in_count,
            in_data,
            in_stride,
            out_id
        );
    }
    
    IFB_ENG_API eng_bool
    eng_id_search(
        const eng_u32        in_count,
        const eng_id_u128_t  in_id,
        const eng_id_u128_t* in_search,
        eng_u32&             out_index) {

        const eng_bool is_found = sld::hash_search(
            in_count,
            in_id,
            in_search,
            out_index
        );

        return(is_found);
    }
};