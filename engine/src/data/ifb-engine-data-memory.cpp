#pragma once

#include "ifb-engine-internal-data.hpp"

inline ifb_ptr
ifb_engine::data_memory_get_pointer(
    const IFBEngineDataMemory& data_memory_ref,
    const ifb_u16              data_offset) {

    //get the data address
    const ifb_address data_address = data_memory_ref.commit_start + data_offset;

    //cast the address to a pointer
    ifb_ptr data_pointer = (ifb_ptr)data_address;

    //we're done
    return(data_pointer);
}

inline ifb_char*
ifb_engine::data_memory_get_pointer_tag_char_buffer(
    const IFBEngineDataMemory&     data_memory_ref,
    const IFBEngineDataOffsetsTag& data_offsets_tag_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_tag_ref.char_buffer);

    //cast it to the requested type
    ifb_char* tag_char_buffer = (ifb_char*)data_pointer;

    //we're done
    return(tag_char_buffer); 
}

inline IFBHash*
ifb_engine::data_memory_get_pointer_tag_hash_array(
    const IFBEngineDataMemory&     data_memory_ref,
    const IFBEngineDataOffsetsTag& data_offsets_tag_ref) {
    
    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_tag_ref.hash_array);

    //cast it to the requested type
    IFBHash* tag_hash_array = (IFBHash*)data_pointer;

    //we're done
    return(tag_hash_array); 
}

inline IFBIDCommit*
ifb_engine::data_memory_get_pointer_arena_commit_id(
    const IFBEngineDataMemory&       data_memory_ref,
    const IFBEngineDataOffsetsArena& data_offsets_arena_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_arena_ref.commit_id);

    //cast it to the requested type
    IFBIDCommit* commit_id_ptr = (IFBIDCommit*)data_pointer;

    //we're done
    return(commit_id_ptr); 
}

inline IFBIDTag*
ifb_engine::data_memory_get_pointer_arena_tag_id(
    const IFBEngineDataMemory&       data_memory_ref,
    const IFBEngineDataOffsetsArena& data_offsets_arena_ref) {
    
    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_arena_ref.tag_id);

    //cast it to the requested type
    IFBIDTag* tag_id_ptr = (IFBIDTag*)data_pointer;

    //we're done
    return(tag_id_ptr); 
}

inline ifb_address*
ifb_engine::data_memory_get_pointer_arena_start(
    const IFBEngineDataMemory&       data_memory_ref,
    const IFBEngineDataOffsetsArena& data_offsets_arena_ref) {
    
    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_arena_ref.start);

    //cast it to the requested type
    ifb_address* arena_start_pointer = (ifb_address*)data_pointer;

    //we're done
    return(arena_start_pointer); 
}

inline ifb_u32*
ifb_engine::data_memory_get_pointer_arena_size(
    const IFBEngineDataMemory&       data_memory_ref,
    const IFBEngineDataOffsetsArena& data_offsets_arena_ref) {
    
    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_arena_ref.size);

    //cast it to the requested type
    ifb_u32* arena_size_pointer = (ifb_u32*)data_pointer;

    //we're done
    return(arena_size_pointer); 
}

inline IFBWindow*
ifb_engine::data_memory_get_pointer_graphics_window(
    const IFBEngineDataMemory&          data_memory_ref,
    const IFBEngineDataOffsetsGraphics& data_offsets_graphics_ref) {
    
    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_graphics_ref.window);

    //cast it to the requested type
    IFBWindow* window_pointer = (IFBWindow*)data_pointer;

    //we're done
    return(window_pointer); 
}

inline IFBGLViewport*
ifb_engine::data_memory_get_pointer_graphics_viewport(
    const IFBEngineDataMemory&          data_memory_ref,
    const IFBEngineDataOffsetsGraphics& data_offsets_graphics_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_graphics_ref.viewport);

    //cast it to the requested type
    IFBGLViewport* viewport_pointer = (IFBGLViewport*)data_pointer;

    //we're done
    return(viewport_pointer); 
}

inline IFBMonitor*
ifb_engine::data_memory_get_pointer_graphics_monitors(
    const IFBEngineDataMemory&          data_memory_ref,
    const IFBEngineDataOffsetsGraphics& data_offsets_graphics_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_graphics_ref.monitors);

    //cast it to the requested type
    IFBMonitor* monitor_array = (IFBMonitor*)data_pointer;

    //we're done
    return(monitor_array);
}

inline IFBIDArena*
ifb_engine::data_memory_get_pointer_shader_arena_id(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.arena_id);

    //cast it to the requested type
    IFBIDArena* arena_id_ptr = (IFBIDArena*)data_pointer;

    //we're done
    return(arena_id_ptr);
};

inline IFBGLIDShaderProgram*
ifb_engine::data_memory_get_pointer_shader_gl_shader_program_id(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.gl_shader_program_id);

    //cast it to the requested type
    IFBGLIDShaderProgram* shader_program_ptr = (IFBGLIDShaderProgram*)data_pointer;

    //we're done
    return(shader_program_ptr);
}

inline IFBGLIDVertex*
ifb_engine::data_memory_get_pointer_shader_gl_vertex_id(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.gl_vertex_id);

    //cast it to the requested type
    IFBGLIDVertex* vertex_ptr = (IFBGLIDVertex*)data_pointer;

    //we're done
    return(vertex_ptr);
}

inline ifb_u32*
ifb_engine::data_memory_get_pointer_shader_vertex_size(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.vertex_size);

    //cast it to the requested type
    ifb_u32* vertex_size_ptr = (ifb_u32*)data_pointer;

    //we're done
    return(vertex_size_ptr);
}

inline ifb_address*
ifb_engine::data_memory_get_pointer_shader_vertex_buffer_start(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.vertex_buffer_start);

    //cast it to the requested type
    ifb_address* vertex_start_ptr  = (ifb_address*)data_pointer;

    //we're done
    return(vertex_start_ptr);
}

inline ifb_u32*
ifb_engine::data_memory_get_pointer_shader_vertex_buffer_size(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.vertex_buffer_size);

    //cast it to the requested type
    ifb_u32* vertex_buffer_size_ptr  = (ifb_u32*)data_pointer;

    //we're done
    return(vertex_buffer_size_ptr);
}

inline ifb_u32*
ifb_engine::data_memory_get_pointer_shader_vertex_buffer_position(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsShader& data_offsets_shader_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_shader_ref.vertex_buffer_position);

    //cast it to the requested type
    ifb_u32* vertex_buffer_size_ptr  = (ifb_u32*)data_pointer;

    //we're done
    return(vertex_buffer_size_ptr);
}

inline IFBVec2*
ifb_engine::data_memory_get_pointer_transform_translation(
    const IFBEngineDataMemory&           data_memory_ref,
    const IFBEngineDataOffsetsTransform& data_offsets_transform_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_transform_ref.translation);

    //cast it to the requested type
    IFBVec2* translation_ptr  = (IFBVec2*)data_pointer;

    //we're done
    return(translation_ptr);
}

inline IFBVec2*
ifb_engine::data_memory_get_pointer_transform_scale(
    const IFBEngineDataMemory&           data_memory_ref,
    const IFBEngineDataOffsetsTransform& data_offsets_transform_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_transform_ref.scale);

    //cast it to the requested type
    IFBVec2* scale_ptr  = (IFBVec2*)data_pointer;

    //we're done
    return(scale_ptr);
}

inline ifb_f32*
ifb_engine::data_memory_get_pointer_transform_rotation(
    const IFBEngineDataMemory&           data_memory_ref,
    const IFBEngineDataOffsetsTransform& data_offsets_transform_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_transform_ref.rotation);

    //cast it to the requested type
    ifb_f32* rotation_ptr  = (ifb_f32*)data_pointer;

    //we're done
    return(rotation_ptr);
}

inline ifb_byte*
ifb_engine::data_memory_get_pointer_transform_flags(
    const IFBEngineDataMemory&           data_memory_ref,
    const IFBEngineDataOffsetsTransform& data_offsets_transform_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_transform_ref.rotation);

    //cast it to the requested type
    ifb_byte* flags_ptr  = (ifb_byte*)data_pointer;

    //we're done
    return(flags_ptr);
}

inline IFBIDTag*
ifb_engine::data_memory_get_pointer_sprite_tag_id(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsSprite& data_offsets_sprite_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_sprite_ref.tag_id);

    //cast it to the requested type
    IFBIDTag* tag_id_ptr  = (IFBIDTag*)data_pointer;

    //we're done
    return(tag_id_ptr);
}

inline IFBIDTransform*
ifb_engine::data_memory_get_pointer_sprite_transform_id(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsSprite& data_offsets_sprite_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_sprite_ref.transform_id);

    //cast it to the requested type
    IFBIDTransform* transform_id_ptr  = (IFBIDTag*)data_pointer;

    //we're done
    return(transform_id_ptr);
}

inline IFBColorTableIndex*
ifb_engine::data_memory_get_pointer_sprite_color_table_index(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsSprite& data_offsets_sprite_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_sprite_ref.color_table_index);

    //cast it to the requested type
    IFBColorTableIndex* color_table_index_ptr  = (IFBColorTableIndex*)data_pointer;

    //we're done
    return(color_table_index_ptr);
}

inline ifb_byte*
ifb_engine::data_memory_get_pointer_sprite_flags(
    const IFBEngineDataMemory&        data_memory_ref,
    const IFBEngineDataOffsetsSprite& data_offsets_sprite_ref) {

    //get the data pointer
    const ifb_ptr data_pointer = ifb_engine::data_memory_get_pointer(
        data_memory_ref,
        data_offsets_sprite_ref.flags);

    //cast it to the requested type
    ifb_byte* flags_ptr  = (ifb_byte*)data_pointer;

    //we're done
    return(flags_ptr);
}