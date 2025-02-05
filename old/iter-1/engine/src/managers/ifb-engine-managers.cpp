#pragma once

#include "ifb-engine-internal-managers.hpp"
#include "ifb-engine-internal-memory.hpp"

inline ifb_void 
ifb_engine::managers_initialize(
    IFBEngineManagers* managers_ptr,
    IFBEngineMemory*   engine_memory_ptr,
    IFBEngineConfig*   engine_config) {

    //sanity check
    ifb_macro_assert(managers_ptr);
    ifb_macro_assert(engine_memory_ptr);
    ifb_macro_assert(engine_config);

    //allocate handles
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.tag,       IFBEngineManagerTag);
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.arena,     IFBEngineManagerArena);
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.graphics,  IFBEngineManagerGraphics);
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.shader,    IFBEngineManagerShader);
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.transform, IFBEngineManagerTransform);
    ifb_engine_macro_memory_global_push_struct(engine_memory_ptr, managers_ptr->handles.sprite,    IFBEngineManagerSprite);

    //sanity check
    ifb_macro_assert(manager_handles_ref.tag.offset       != 0);
    ifb_macro_assert(manager_handles_ref.arena.offset     != 0);
    ifb_macro_assert(manager_handles_ref.graphics.offset  != 0);
    ifb_macro_assert(manager_handles_ref.shader.offset    != 0);
    ifb_macro_assert(manager_handles_ref.transform.offset != 0);
    ifb_macro_assert(manager_handles_ref.sprite.offset    != 0);

    //get pointers
    IFBEngineManagerTag*       manager_ptr_tag       =  ifb_engine::managers_get_manager_tag       (managers_ptr,engine_memory_ptr);
    IFBEngineManagerArena*     manager_ptr_arena     =  ifb_engine::managers_get_manager_arena     (managers_ptr,engine_memory_ptr);
    IFBEngineManagerGraphics*  manager_ptr_graphics  =  ifb_engine::managers_get_manager_graphics  (managers_ptr,engine_memory_ptr);
    IFBEngineManagerShader*    manager_ptr_shader    =  ifb_engine::managers_get_manager_shader    (managers_ptr,engine_memory_ptr);
    IFBEngineManagerTransform* manager_ptr_transform =  ifb_engine::managers_get_manager_transform (managers_ptr,engine_memory_ptr);
    IFBEngineManagerSprite*    manager_ptr_sprite    =  ifb_engine::managers_get_manager_sprite    (managers_ptr,engine_memory_ptr);

    //sanity check
    ifb_macro_assert(manager_ptr_tag);
    ifb_macro_assert(manager_ptr_arena);
    ifb_macro_assert(manager_ptr_graphics);
    ifb_macro_assert(manager_ptr_shader);
    ifb_macro_assert(manager_ptr_transform);
    ifb_macro_assert(manager_ptr_sprite);

    //calculate sizes and offsets
    const ifb_u32 data_size_tag       = managers_calculate_size_and_offsets_tag       (manager_ptr_tag);
    const ifb_u32 data_size_arena     = managers_calculate_size_and_offsets_arena     (manager_ptr_arena);
    const ifb_u32 data_size_graphics  = managers_calculate_size_and_offsets_graphics  (manager_ptr_graphics);
    const ifb_u32 data_size_shader    = managers_calculate_size_and_offsets_shader    (manager_ptr_shader);
    const ifb_u32 data_size_transform = managers_calculate_size_and_offsets_transform (manager_ptr_transform);
    const ifb_u32 data_size_sprite    = managers_calculate_size_and_offsets_sprite    (manager_ptr_sprite);

    //sanity check
    ifb_macro_assert(data_size_tag       > 0);
    ifb_macro_assert(data_size_arena     > 0);
    ifb_macro_assert(data_size_graphics  > 0);
    ifb_macro_assert(data_size_shader    > 0);
    ifb_macro_assert(data_size_transform > 0);
    ifb_macro_assert(data_size_sprite    > 0);

    //calculate commit size
    const ifb_u32 commit_size = (
        data_size_tag       +
        data_size_arena     +
        data_size_graphics  +
        data_size_shader    +
        data_size_transform +
        data_size_sprite);

    //do the commit and get the starting address
    const IFBIDCommit commit_id    = ifb_engine::memory_commit             (engine_memory_ptr, commit_size);
    const ifb_address commit_start = ifb_engine::memory_get_commit_address (engine_memory_ptr, commit_id);
    managers_ptr->commit_id    = commit_id; 
    managers_ptr->commit_start = commit_start; 

    //update the starting address for the managers
    manager_ptr_tag->memory_start       = commit_start; 
    manager_ptr_arena->memory_start     = memory_start_tag       + data_size_tag; 
    manager_ptr_graphics->memory_start  = memory_start_arena     + data_size_arena; 
    manager_ptr_shader->memory_start    = memory_start_graphics  + data_size_graphics; 
    manager_ptr_transform->memory_start = memory_start_shader    + data_size_shader; 
    manager_ptr_sprite->memory_start    = memory_start_transform + data_size_transform;

    //do any remaining initialization on the managers
    tag_manager_initialize       (manager_ptr_tag);
    arena_manager_initialize     (manager_ptr_arena);
    graphics_manger_initialize   (manager_ptr_graphics);
    shader_manager_initialize    (manager_ptr_shader);
    transform_manager_initialize (manager_ptr_transform);
    sprite_manager_initialize    (manager_ptr_sprite);
}

inline IFBEngineManagerTag*
ifb_engine::managers_get_manager_tag(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerTag* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerTag);

    //we're done
    return(tag_manager_ptr);    
}

inline IFBEngineManagerArena*
ifb_engine::managers_get_manager_arena(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerArena* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerArena);

    //we're done
    return(tag_manager_ptr); 
}

inline IFBEngineManagerGraphics*
ifb_engine::managers_get_manager_graphics(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerGraphics* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerGraphics);

    //we're done
    return(tag_manager_ptr); 
}

inline IFBEngineManagerShader*
ifb_engine::managers_get_manager_shader(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerShader* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerShader);

    //we're done
    return(tag_manager_ptr); 
}

inline IFBEngineManagerTransform*
ifb_engine::managers_get_manager_transform(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerTransform* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerTransform);

    //we're done
    return(tag_manager_ptr); 
}

inline IFBEngineManagerSprite*
ifb_engine::managers_get_manager_sprite(
    const IFBEngineManagerHandles* manager_handles_ptr,
    const IFBEngineMemory*         engine_memory_ptr) {

    //sanity check
    ifb_macro_assert(manager_handles_ptr);
    ifb_macro_assert(engine_memory_ptr);

    //get the pointer
    IFBEngineManagerSprite* tag_manager_ptr = ifb_engine_macro_memory_get_pointer(
        engine_memory_ptr,
        manager_handles_ptr->tag,
        IFBEngineManagerSprite);

    //we're done
    return(tag_manager_ptr); 
}

inline const ifb_u32
ifb_engine::managers_calculate_size_and_offsets_tag(
    IFBEngineManagerTag* tag_manager_ptr) {

    const ifb_u16 tag_count              = tag_manager_ptr->tag_count_max;
    const ifb_u16 tag_length             = tag_manager_ptr->tag_c_str_length;
    const ifb_u16 tag_char_buffer_length = tag_count * tag_length;  

    const ifb_u16 char_buffer_size = ifb_macro_size_array(ifb_char, tag_char_buffer_length);
    const ifb_u16 hash_array_size  = ifb_macro_size_array(IFBHash,  tag_count_max);

    tag_manager_ptr->offset_char_buffer = 0;
    tag_manager_ptr->offset_hash_array  = char_buffer_size; 

    const ifb_u32 tag_manager_data_size = (
        char_buffer_size +
        hash_array_size);

    return(tag_manager_data_size);
}

inline const ifb_u32
ifb_engine::managers_calculate_size_and_offsets_arena(
    IFBEngineManagerArena* arena_manager_ptr) {

    const ifb_u16 arena_count = arena_manager_ptr->arena_count_max;

    //calculate the commit size
    const ifb_u32 size_commit_id_array = ifb_macro_size_array(IFBIDCommit, arena_count);
    const ifb_u32 size_tag_id_array    = ifb_macro_size_array(IFBIDTag,    arena_count);
    const ifb_u32 size_arena_start     = ifb_macro_size_array(ifb_address, arena_count);
    const ifb_u32 size_arena_size      = ifb_macro_size_array(ifb_u32,     arena_count); //lol
    
    //calculate offsets
    arena_manager_ptr->offset_commit_id_array = 0;
    arena_manager_ptr->offset_tag_id_array    = size_commit_id_array;
    arena_manager_ptr->offset_arena_start     = size_tag_id_array;
    arena_manager_ptr->offset_arena_size      = size_arena_start;

    //calculate total size
    const ifb_u32 arena_manager_data_size = (
        size_commit_id_array +
        size_tag_id_array    +
        size_arena_start     +
        size_arena_size);

    //we're done
    return(arena_manager_data_size);
}

inline const ifb_u32
ifb_engine::managers_calculate_size_and_offsets_graphics(
    IFBEngineManagerGraphics* graphics_manager_ptr) {

    //calculate sizes
    const ifb_u16 size_window        = ifb_macro_align_size_struct(IFBWindow); 
    const ifb_u16 size_viewport      = ifb_macro_align_size_struct(IFBGLViewport);
    const ifb_u16 size_monitor_array = ifb_macro_size_array(IFBMonitor, monitor_count);

    //update manager
    graphics_manager_ptr->offset_window        = 0;
    graphics_manager_ptr->offset_viewport      = size_window;
    graphics_manager_ptr->offset_monitor_array = size_viewport;

    //calculate total size
    const ifb_u32 graphics_manager_total_size = (
        size_window   +
        size_viewport +
        size_monitor_array);

    //we're done
    return(graphics_manager_total_size);
}

inline const ifb_u32
ifb_engine::managers_calculate_size_and_offsets_shader(
    IFBEngineManagerShader* shader_manager_ptr) {

    //calculate array sizes
    const ifb_u32 array_size_shader_program = ifb_macro_size_array(IFBGLIDShaderProgram,shader_count_max);
    const ifb_u32 array_size_shader_tag     = ifb_macro_size_array(IFBIDTag,            shader_count_max);

    //calculate offsets
    shader_manager_ptr->offset_shader_program_array = 0;
    shader_manager_ptr->offset_shader_program_tag   = array_size_shader_program;

    //calculate total size
    const ifb_u32 data_total_size = (
        array_size_shader_program +
        array_size_shader_tag);

    //we're done
    return(data_total_size);
}

inline const ifb_u326
ifb_engine::managers_calculate_size_and_offsets_transform(
    IFBEngineManagerTransform* transform_manager_ptr) {

    const ifb_u32 transform_count = transform_manager_ptr->transform_count_max;

    //calculate array sizes
    const ifb_u16 size_array_translation = ifb_macro_size_array(IFBVec2,  transform_count);
    const ifb_u16 size_array_scale       = ifb_macro_size_array(IFBVec2,  transform_count);
    const ifb_u16 size_array_rotation    = ifb_macro_size_array(ifb_f32,  transform_count);
    const ifb_u16 size_array_flags       = ifb_macro_size_array(ifb_byte, transform_count);

    //calculate offsets
    transform_manager_ptr->offset_array_translation      = 0;
    transform_manager_ptr->offset_array_scale            = size_array_translation;
    transform_manager_ptr->offset_array_rotation_radians = size_array_scale;
    transform_manager_ptr->offset_array_flags            = size_array_rotation;
    
    //calculate total size
    const ifb_u32 data_total_size = (
        size_array_translation +
        size_array_scale       +
        size_array_rotation    +
        size_array_flags);

    //we're done
    return(data_total_size)
}

inline const ifb_u32
ifb_engine::managers_calculate_size_and_offsets_sprite(
    IFBEngineManagerSprite* sprite_manager_ptr) {

    const ifb_u16 sprite_count = sprite_manager_ptr->sprite_count_max;

    //calculate array sizes
    const ifb_u32 size_array_tag_id            = ifb_macro_size_array(IFBIDTag,           sprite_count_max);
    const ifb_u32 size_array_transform_id      = ifb_macro_size_array(IFBIDTransform,     sprite_count_max);
    const ifb_u32 size_array_color_table_index = ifb_macro_size_array(IFBColorTableIndex, sprite_count_max);
    const ifb_u32 size_array_flags             = ifb_macro_size_array(ifb_byte,           sprite_count_max);

    //calculate offsets    
    sprite_manager_ptr->offset_array_tag_id            = 0 ;
    sprite_manager_ptr->offset_array_transform_id      = size_array_tag_id;
    sprite_manager_ptr->offset_array_color_table_index = size_array_transform_id;
    sprite_manager_ptr->offset_array_flags             = size_array_color_table_index;

    //calculate total size
    const ifb_u32 data_total_size = (
        size_array_tag_id            +
        size_array_transform_id      +
        size_array_color_table_index +
        size_array_flags);

    return(data_total_size);
}