#pragma once

#include "ifb-graphics.hpp"

const IFBB8
ifb_graphics::color_normalize(
    const IFBColorHex*        ptr_color_hex,
          IFBColorNormalized* ptr_color_normalized) {
    
    //sanity check
    IFBB8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //cache float values
    const IFBF32 color_const         = (1.0f / 0xFF);
    const IFBF32 color_hex_f32_red   = (IFBF32)ptr_color_hex->red;
    const IFBF32 color_hex_f32_blue  = (IFBF32)ptr_color_hex->blue;
    const IFBF32 color_hex_f32_green = (IFBF32)ptr_color_hex->green;
    const IFBF32 color_hex_f32_alpha = (IFBF32)ptr_color_hex->alpha;

    //normalize the colors
    ptr_color_normalized->red   = color_const * color_hex_f32_red;
    ptr_color_normalized->blue  = color_const * color_hex_f32_blue;
    ptr_color_normalized->green = color_const * color_hex_f32_green;
    ptr_color_normalized->alpha = color_const * color_hex_f32_alpha;

    //we're done
    return(true);
}

const IFBB8
ifb_graphics::color_denormalize(
    const IFBColorNormalized* ptr_color_normalized,
          IFBColorHex*        ptr_color_hex) {
    
    //sanity check
    IFBB8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //normalize the colors
    const IFBF32 color_const = (0xFF);
    ptr_color_hex->red       = (IFBU32)(color_const * ptr_color_normalized->red);
    ptr_color_hex->blue      = (IFBU32)(color_const * ptr_color_normalized->blue);
    ptr_color_hex->green     = (IFBU32)(color_const * ptr_color_normalized->green);
    ptr_color_hex->alpha     = (IFBU32)(color_const * ptr_color_normalized->alpha);

    //we're done
    return(true);
}

const IFBColor32
ifb_graphics::color_pack_hex_to_32(
    const IFBColorFormat color_format,    
    const IFBColorHex*   color_hex_ptr) {

    IFBColor32 color;
    color.value = 0;

    //sanity check
    if (!color_hex_ptr) return(color);

    //cache the values
    const IFBU8 u8_r = (IFBU32)color_hex_ptr->red;
    const IFBU8 u8_b = (IFBU32)color_hex_ptr->blue;
    const IFBU8 u8_g = (IFBU32)color_hex_ptr->green;
    const IFBU8 u8_a = (IFBU32)color_hex_ptr->alpha;
    
    //pack the color value based on the format
    switch(color_format) {
        case (IFBColorFormat_RGBA): color.value = ifb_macro_pack_u8_to_u32(u8_r, u8_b, u8_g, u8_a); break;
        case (IFBColorFormat_ARGB): color.value = ifb_macro_pack_u8_to_u32(u8_a, u8_b, u8_g, u8_r); break;
        case (IFBColorFormat_ABGR): color.value = ifb_macro_pack_u8_to_u32(u8_a, u8_g, u8_b, u8_r); break;
        case (IFBColorFormat_BGRA): color.value = ifb_macro_pack_u8_to_u32(u8_r, u8_g, u8_b, u8_a); break;
        default: break;    
    }

    //we're done
    return(color);
}

const IFBColor32
ifb_graphics::color_pack_normalized_to_32(
    const IFBColorFormat      color_format,    
    const IFBColorNormalized* ptr_color_normalized) {

    IFBColor32 color;
    color.value = 0;

    //sanity check
    if (!ptr_color_normalized) return(color);

    //denormalize the color
    IFBColorHex color_hex;
    const IFBB8 result = ifb_graphics::color_denormalize(ptr_color_normalized,&color_hex);
    if (!result) return(color); 
    
    //pack it
    color = ifb_graphics::color_pack_hex_to_32(color_format,&color_hex);

    //we're done
    return(color);
}