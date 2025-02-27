#pragma once

#include "ifb-graphics.hpp"

const IFBB8
ifb_graphics::color_normalize(
    const IFBColorHex*        ptr_color_hex,
          IFBColorNormalized* ptr_color_normalized) {
    
    IFBB8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    const IFBF32 color_const = (1.0f / 0xFF);

    ptr_color_normalized->red   = color_const * ((IFBF32)ptr_color_hex->red);
    ptr_color_normalized->blue  = color_const * ((IFBF32)ptr_color_hex->blue);
    ptr_color_normalized->green = color_const * ((IFBF32)ptr_color_hex->green);
    ptr_color_normalized->alpha = color_const * ((IFBF32)ptr_color_hex->alpha);

    return(true);
}

const IFBColor32
ifb_graphics::color32(
    const IFBColorHex*   color_hex_ptr) {

    IFBColor32 color;
    color.value = 0;

    if (!color_hex_ptr) return(color);

    

    return(color);
}

const IFBColor32
ifb_graphics::color32(
    const IFBColorNormalized* ptr_color_normalized) {

    IFBColor32 color;
    color.value = 0;
    return(color);
}