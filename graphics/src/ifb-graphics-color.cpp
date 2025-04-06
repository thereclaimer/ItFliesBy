#pragma once

#include "ifb-graphics.hpp"

using namespace ifb;

const b8
graphics::color_normalize(
    const graphics_color_hex_t*  ptr_color_hex,
    graphics_color_normalized_t* ptr_color_normalized) {
    
    //sanity check
    b8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //cache float values
    const f32 color_const         = (1.0f / 0xFF);
    const f32 color_hex_f32_red   = (f32)ptr_color_hex->red;
    const f32 color_hex_f32_blue  = (f32)ptr_color_hex->blue;
    const f32 color_hex_f32_green = (f32)ptr_color_hex->green;
    const f32 color_hex_f32_alpha = (f32)ptr_color_hex->alpha;

    //normalize the colors
    ptr_color_normalized->red   = color_const * color_hex_f32_red;
    ptr_color_normalized->blue  = color_const * color_hex_f32_blue;
    ptr_color_normalized->green = color_const * color_hex_f32_green;
    ptr_color_normalized->alpha = color_const * color_hex_f32_alpha;

    //we're done
    return(true);
}

const b8
graphics::color_denormalize(
    const graphics_color_normalized_t* ptr_color_normalized,
    graphics_color_hex_t*              ptr_color_hex) {
    
    //sanity check
    b8 result = true;
    result &= (ptr_color_hex        != NULL);
    result &= (ptr_color_normalized != NULL);    
    if (!result) return(false);

    //normalize the colors
    const f32 color_const = (0xFF);
    ptr_color_hex->red   = (u32)(color_const * ptr_color_normalized->red);
    ptr_color_hex->blue  = (u32)(color_const * ptr_color_normalized->blue);
    ptr_color_hex->green = (u32)(color_const * ptr_color_normalized->green);
    ptr_color_hex->alpha = (u32)(color_const * ptr_color_normalized->alpha);

    //we're done
    return(true);
}



const graphics_color_32_t
graphics::color_pack_hex_to_32(
    const graphics_color_format_e color_format,    
    const graphics_color_hex_t*   color_hex_ptr) {

    graphics_color_32_t color;
    color.value = 0;

    //sanity check
    if (!color_hex_ptr) return(color);

    //cache the values
    const u8 u8_r = (u32)color_hex_ptr->red;
    const u8 u8_b = (u32)color_hex_ptr->blue;
    const u8 u8_g = (u32)color_hex_ptr->green;
    const u8 u8_a = (u32)color_hex_ptr->alpha;
    
    //pack the color value based on the format
    switch(color_format) {
        case (graphics_color_format_e_rgba): color.value = ifb_macro_pack_u8_to_u32(u8_r, u8_b, u8_g, u8_a); break;
        case (graphics_color_format_e_argb): color.value = ifb_macro_pack_u8_to_u32(u8_a, u8_b, u8_g, u8_r); break;
        case (graphics_color_format_e_abgr): color.value = ifb_macro_pack_u8_to_u32(u8_a, u8_g, u8_b, u8_r); break;
        case (graphics_color_format_e_bgra): color.value = ifb_macro_pack_u8_to_u32(u8_r, u8_g, u8_b, u8_a); break;
        default: break;    
    }

    //we're done
    return(color);
}

const graphics_color_32_t
graphics::color_pack_normalized_to_32(
    const graphics_color_format_e      color_format,    
    const graphics_color_normalized_t* ptr_color_normalized) {

    graphics_color_32_t color;
    color.value = 0;

    //sanity check
    if (!ptr_color_normalized) return(color);

    //denormalize the color
    graphics_color_hex_t color_hex;
    const b8 result = graphics::color_denormalize(ptr_color_normalized,&color_hex);
    if (!result) return(color); 
    
    //pack it
    color = graphics::color_pack_hex_to_32(color_format,&color_hex);

    //we're done
    return(color);
}