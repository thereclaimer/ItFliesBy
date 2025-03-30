#pragma once

#include "ifb-graphics.hpp"

const ifb::b8
ifb_graphics::color_normalize(
    const IFBColorHex*        ptr_color_hex,
          IFBColorNormalized* ptr_color_normalized) {
    
    //sanity check
    ifb::b8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //cache float values
    const ifb::f32 color_const         = (1.0f / 0xFF);
    const ifb::f32 color_hex_f32_red   = (ifb::f32)ptr_color_hex->red;
    const ifb::f32 color_hex_f32_blue  = (ifb::f32)ptr_color_hex->blue;
    const ifb::f32 color_hex_f32_green = (ifb::f32)ptr_color_hex->green;
    const ifb::f32 color_hex_f32_alpha = (ifb::f32)ptr_color_hex->alpha;

    //normalize the colors
    ptr_color_normalized->red   = color_const * color_hex_f32_red;
    ptr_color_normalized->blue  = color_const * color_hex_f32_blue;
    ptr_color_normalized->green = color_const * color_hex_f32_green;
    ptr_color_normalized->alpha = color_const * color_hex_f32_alpha;

    //we're done
    return(true);
}

const ifb::b8
ifb_graphics::color_denormalize(
    const IFBColorNormalized* ptr_color_normalized,
          IFBColorHex*        ptr_color_hex) {
    
    //sanity check
    ifb::b8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //normalize the colors
    const ifb::f32 color_const = (0xFF);
    ptr_color_hex->red       = (ifb::u32)(color_const * ptr_color_normalized->red);
    ptr_color_hex->blue      = (ifb::u32)(color_const * ptr_color_normalized->blue);
    ptr_color_hex->green     = (ifb::u32)(color_const * ptr_color_normalized->green);
    ptr_color_hex->alpha     = (ifb::u32)(color_const * ptr_color_normalized->alpha);

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
    const ifb::u8 u8_r = (ifb::u32)color_hex_ptr->red;
    const ifb::u8 u8_b = (ifb::u32)color_hex_ptr->blue;
    const ifb::u8 u8_g = (ifb::u32)color_hex_ptr->green;
    const ifb::u8 u8_a = (ifb::u32)color_hex_ptr->alpha;
    
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
    const ifb::b8 result = ifb_graphics::color_denormalize(ptr_color_normalized,&color_hex);
    if (!result) return(color); 
    
    //pack it
    color = ifb_graphics::color_pack_hex_to_32(color_format,&color_hex);

    //we're done
    return(color);
}