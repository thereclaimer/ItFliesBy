#pragma once

#include "ifb-engine-asset.hpp"

namespace ifb {

    IFB_ENG_FUNC void
    eng_asset_generate_id(
        const eng_u32                in_count,
        const eng_asset_name_str8_t* in_name,
        eng_asset_id_u128_t*         out_id) {

        static const eng_u32 stride = sizeof(eng_asset_name_str8_t); 

        eng_id_generate(
            in_count,
            stride,
            (eng_byte*)in_name,
            out_id
        );

    }
};