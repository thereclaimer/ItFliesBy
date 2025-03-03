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


const IFBColorTable*
ifb_graphics::color_table_commit_to_arena_absolute(
    const IFBHNDArena    arena_handle,
    const IFBColorFormat color_format,
    const IFBU32         color_count,
    const IFBChar**      color_key_array,
    const IFBColorHex*   color_hex_array) {

    //sanity check
    IFBB8 result = true;
    result &= ifb_memory_macro_handle_valid(arena_handle);
    result &= (color_count     != 0);
    result &= (color_key_array != NULL);
    result &= (color_hex_array != NULL);
    if (!result) return(false);

    //commit the color table
    const IFBU32   color_table_size = ifb_macro_align_size_struct(IFBColorTable); 
    IFBColorTable* color_table_ptr  = (IFBColorTable*)ifb_memory::arena_commit_bytes_absolute(
        arena_handle,
        color_table_size);

    //commit the hash table
    const IFBU32  color_hex_size   = sizeof(IFBColorHex);
    const IFBU32  color_key_length = 32;
    IFBHashTable* hash_table_ptr   = ifb_hash_table::commit_to_arena_absolute(
        arena_handle,
        color_count,
        color_hex_size,
        color_key_length);

    //make sure we have the pointers
    ifb_macro_assert(color_table_ptr);
    ifb_macro_assert(hash_table_ptr);

    //add the values
    for (
        IFBU32 color_index = 0;
               color_index < color_count;
             ++color_index) {

        //get the key and the color as a pointer to a byte
        const IFBChar* ptr_color_key     = color_key_array[color_index];
        const IFBByte* ptr_color_element = (IFBByte*)(&color_hex_array[color_index]);
    
        //add the color to the table
        result &= ifb_hash_table::insert(
            hash_table_ptr,
            ptr_color_key,
            ptr_color_element);
    }

    //update the table
    color_table_ptr->color_format   = color_format;
    color_table_ptr->ptr_hash_table = hash_table_ptr;
    
    //we're done
    return(color_table_ptr);
}

const IFBU32
ifb_graphics::color_table_commit_to_arena_relative(
    const IFBHNDArena    arena_handle,
    const IFBColorFormat color_format,
    const IFBU32         color_count,
    const IFBChar**      color_key_array,
    const IFBColorHex*   color_hex_array) {

        //sanity check
    IFBB8 result = true;
    result &= ifb_memory_macro_handle_valid(arena_handle);
    result &= (color_count     != 0);
    result &= (color_key_array != NULL);
    result &= (color_hex_array != NULL);
    if (!result) return(false);

    //commit the color table
    const IFBU32 color_table_size   = ifb_macro_align_size_struct(IFBColorTable); 
    const IFBU32 color_table_offset = ifb_memory::arena_commit_bytes_relative(
        arena_handle,
        color_table_size);

    //load the pointer
    IFBColorTable* color_table_ptr = (IFBColorTable*)ifb_memory::arena_get_pointer(arena_handle,color_table_offset);

    //commit the hash table
    const IFBU32  color_hex_size   = sizeof(IFBColorHex);
    const IFBU32  color_key_length = 32;
    IFBHashTable* hash_table_ptr   = ifb_hash_table::commit_to_arena_absolute(
        arena_handle,
        color_count,
        color_hex_size,
        color_key_length);

    //make sure we have the pointers
    ifb_macro_assert(color_table_ptr);
    ifb_macro_assert(hash_table_ptr);

    //add the values
    for (
        IFBU32 color_index = 0;
               color_index < color_count;
             ++color_index) {

        //get the key and the color as a pointer to a byte
        const IFBChar* ptr_color_key     = color_key_array[color_index];
        const IFBByte* ptr_color_element = (IFBByte*)(&color_hex_array[color_index]);
    
        //add the color to the table
        result &= ifb_hash_table::insert(
            hash_table_ptr,
            ptr_color_key,
            ptr_color_element);
    }

    //update the table
    color_table_ptr->color_format   = color_format;
    color_table_ptr->ptr_hash_table = hash_table_ptr;

    //we're done
    return(color_table_offset);
}

const IFBColorTable*
ifb_graphics::color_table_load_from_arena(
    const IFBHNDArena arena_handle,
    const IFBU32      color_table_offset) {

    //get the pointer
    const IFBColorTable* ptr_color_table = (IFBColorTable*)ifb_memory::arena_get_pointer(
        arena_handle,
        color_table_offset);

    //it should be valid
    ifb_macro_assert(ptr_color_table);

    //we're done
    return(ptr_color_table);
}

const IFBB8 
ifb_graphics::color_table_lookup_hex(
    const IFBColorTable* ptr_color_table,
    const IFBChar*       ptr_color_key,
          IFBColorHex*   ptr_color_hex) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_key != NULL);
    result &= (ptr_color_hex != NULL);
    if (!result) return(false);

    //look up the color
    ptr_color_hex = (IFBColorHex*)ifb_hash_table::lookup(
        ptr_color_table->ptr_hash_table,
        ptr_color_key);

    //check if we got a value back
    result &= ptr_color_hex != NULL;

    //we're done
    return(result);
}

const IFBB8 
ifb_graphics::color_table_lookup_normalized(
    const IFBColorTable*      ptr_color_table,
    const IFBChar*            ptr_color_key,
          IFBColorNormalized* ptr_color_normalized) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_key        != NULL);
    result &= (ptr_color_normalized != NULL);
    if (!result) return(false);

    //look up the color
    const IFBColorHex* ptr_color_hex = (IFBColorHex*)ifb_hash_table::lookup(
        ptr_color_table->ptr_hash_table,
        ptr_color_key);

    //if we don't have a color, we're done
    if (!ptr_color_hex) return(false);

    //normalize the color
    result &= ifb_graphics::color_normalize(
        ptr_color_hex,
        ptr_color_normalized);

    //we're done
    return(result);
}

const IFBB8 
ifb_graphics::color_table_lookup_packed_32(
    const IFBColorTable* ptr_color_table,
    const IFBChar*       ptr_color_key,
          IFBColor32*    ptr_color_32) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_key != NULL);
    result &= (ptr_color_32  != NULL);
    if (!result) return(false);

    //look up the color
    const IFBColorHex* ptr_color_hex = (IFBColorHex*)ifb_hash_table::lookup(
        ptr_color_table->ptr_hash_table,
        ptr_color_key);

    //if we don't have a color, we're done
    if (!ptr_color_hex) return(false);
    
    //pack the color
    *ptr_color_32 = ifb_graphics::color_pack_hex_to_32(
        ptr_color_table->color_format,
        ptr_color_hex);

    //we're done
    return(true);
}

const IFBB8 
ifb_graphics::color_table_get_hex(
    const IFBColorTable* ptr_color_table,
    const IFBU32         color_index,
    IFBColorHex*         ptr_color_hex) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_hex != NULL);
    if (!result) return(false);

    //get the color at the index
    const IFBHashTable* ptr_hash_table         = ptr_color_table->ptr_hash_table; 
    const IFBColorHex*  ptr_color_hex_internal = (IFBColorHex*)ifb_hash_table::get_element_at_index(
        ptr_hash_table,
        color_index);

    //if that failed, we're done
    if (!ptr_color_hex_internal) return(false);

    //otherwise, set the values
    ptr_color_hex->red   = ptr_color_hex_internal->red;
    ptr_color_hex->blue  = ptr_color_hex_internal->blue;
    ptr_color_hex->green = ptr_color_hex_internal->green;
    ptr_color_hex->alpha = ptr_color_hex_internal->alpha; 
    
    //we're done
    return(true);
}

const IFBB8 
ifb_graphics::color_table_get_normalized(
    const IFBColorTable* ptr_color_table,
    const IFBU32         color_index,
    IFBColorNormalized*  ptr_color_normalized) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_normalized != NULL);
    if (!result) return(false);

    //get the color at the index
    const IFBHashTable* ptr_hash_table         = ptr_color_table->ptr_hash_table; 
    const IFBColorHex*  ptr_color_hex_internal = (IFBColorHex*)ifb_hash_table::get_element_at_index(
        ptr_hash_table,
        color_index);

    //if that failed, we're done
    if (!ptr_color_hex_internal) return(false);

    //normalize the color
    result &= ifb_graphics::color_normalize(
        ptr_color_hex_internal,
        ptr_color_normalized);

    //we're done
    return(result);
}

const IFBB8 
ifb_graphics::color_table_get_packed_32(
    const IFBColorTable* ptr_color_table,
    const IFBU32         color_index,
    IFBColor32*          ptr_color_32) {

    //sanity check
    ifb_macro_assert(ptr_color_table);
    IFBB8 result = true;
    result &= (ptr_color_32 != NULL);
    if (!result) return(false);

    //get the color at the index
    const IFBHashTable* ptr_hash_table         = ptr_color_table->ptr_hash_table; 
    const IFBColorHex*  ptr_color_hex_internal = (IFBColorHex*)ifb_hash_table::get_element_at_index(
        ptr_hash_table,
        color_index);

    //if that failed, we're done
    if (!ptr_color_hex_internal) return(false);
    
    //pack the color
    *ptr_color_32 = ifb_graphics::color_pack_hex_to_32(
        ptr_color_table->color_format,
        ptr_color_hex_internal);

    //we're done
    return(true);
}