#pragma once

#include "ifb-engine-internal-rendering.hpp"


inline ifb_void
ifb_engine::rendering_vertex_encode_sprite_to_buffer(
    const ifb_u32                    sprite_vertex_count,
    const IFBEngineSpriteVertexData* sprite_vertex_array,
          ifb_memory                 sprite_vertex_buffer) {
    
    //sanity check
    ifb_macro_assert(sprite_vertex_array);
    ifb_macro_assert(sprite_vertex_buffer);

    const ifb_u32 sprite_vertex_size = sizeof(IFBEngineSpriteVertexData);

    for (
        ifb_u32 sprite_index = 0;
        sprite_index < sprite_vertex_count; 
        ++sprite_index) {

        //calculate the buffer offset
        const ifb_u32 sprite_vertex_buffer_offset = sprite_vertex_size * sprite_index;
        
        //get the vertex data
        const IFBEngineSpriteVertexData& sprite_vertex_data_ref = sprite_vertex_array[sprite_index];

        //copy the data array into the buffer
        sprite_vertex_buffer[sprite_vertex_buffer_offset]      = sprite_vertex_data_ref.array[0];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 1]  = sprite_vertex_data_ref.array[1];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 2]  = sprite_vertex_data_ref.array[2];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 3]  = sprite_vertex_data_ref.array[3];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 4]  = sprite_vertex_data_ref.array[4];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 5]  = sprite_vertex_data_ref.array[5];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 6]  = sprite_vertex_data_ref.array[6];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 7]  = sprite_vertex_data_ref.array[7];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 8]  = sprite_vertex_data_ref.array[8];
        sprite_vertex_buffer[sprite_vertex_buffer_offset + 9]  = sprite_vertex_data_ref.array[9];
    }
}