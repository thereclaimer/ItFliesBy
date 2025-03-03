#pragma once

#include "ifb-engine-internal-graphics.hpp"

inline const IFBB8
ifb_engine::graphics_get_color_normalized(
    const IFBColorHex*        ptr_color_hex,
          IFBColorNormalized* ptr_color_normalized) {

    IFBB8 result = true;
    result &= ptr_color_hex        != NULL;
    result &= ptr_color_normalized != NULL;
    if (!result) return(false);

    result = ifb_graphics::color_normalize(
        ptr_color_hex,
        ptr_color_normalized);

    return(result);
}