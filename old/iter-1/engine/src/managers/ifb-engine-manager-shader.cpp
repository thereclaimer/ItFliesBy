#pragma once

#include "ifb-engine-internal-managers.hpp"

inline ifb_void
ifb_engine::shader_manager_initialize(
          IFBEngineManagerShader* shader_manager,
          IFBEngineMemory*        memory,
    const ifb_u32                 shader_count_max) {

    //sanity check
    ifb_macro_assert(shader_manager);
    ifb_macro_assert(memory);
    ifb_macro_assert(shader_count_max > 0);

    //calculate array sizes
    const ifb_u32 array_size_shader_program = ifb_macro_size_array(IFBGLIDShaderProgram,shader_count_max);
    const ifb_u32 array_size_shader_tag     = ifb_macro_size_array(IFBIDTag,            shader_count_max);

    //calculate offsets
    const ifb_u32 offset_array_shader_program = 0;
    const ifb_u32 offset_array_shader_tag     = array_size_shader_program;

    //calculate commit size
    const ifb_u32 commit_size = 
        array_size_shader_program +
        array_size_shader_tag;

    //do the commit
    const IFBIDCommit commit_id = ifb_engine::memory_commit(
        memory,
        commit_size);

    //get the commit start
    const ifb_address commit_start = ifb_engine::memory_get_commit_address(
        memory,
        commit_id);

    //initialize memory
    IFBEngineManagerMemoryShader& shader_manager_memory = shader_manager->memory;
    shader_manager_memory.start                       = commit_start;
    shader_manager_memory.offset_shader_program_array = offset_array_shader_program;
    shader_manager_memory.offset_shader_program_tag   = offset_array_shader_tag;
    shader_manager_memory.commit_id                   = commit_id;

    //get the data
    IFBIDTag*             array_shader_tag     = ifb_engine::shader_manager_get_array_tag_id        (shader_manager_memory);
    IFBGLIDShaderProgram* array_shader_program = ifb_engine::shader_manager_get_array_shader_program(shader_manager_memory); 

    //clear the data
    for (
        ifb_u32 shader_index = 0;
        shader_index < shader_count_max;
        ++shader_index) {

        array_shader_tag    [shader_index].index = 0;
        array_shader_program[shader_index].gl_id = 0;
    }

    //set the manager properties
    shader_manager->shader_program_count_total     = shader_count_max;
    shader_manager->shader_program_count_committed = 0;
}

inline ifb_void
ifb_engine::shader_manager_commit_shaders(
          IFBEngineManagerShader*   shader_manager,
    const ifb_u32                   shader_count,
    const IFBGLIDShaderStageVertex*   shader_stage_array_vertex,
    const IFBGLIDShaderStageFragment* shader_stage_array_fragment,
    const IFBIDTag*                 shader_tag_array,
          IFBIDShader*              shader_id_array) {

    //sanity check
    ifb_macro_assert(shader_count > 0);
    ifb_macro_assert(shader_stage_array_vertex);
    ifb_macro_assert(shader_stage_array_fragment);
    ifb_macro_assert(shader_tag_array);
    ifb_macro_assert(shader_id_array);   

    //make sure we can do the commit
    const ifb_u32 shader_commit_start    = shader_manager->shader_program_count_committed; 
    const ifb_u32 shader_count_available = shader_manager->shader_program_count_total - shader_commit_start; 

    const ifb_b8 can_commit = shader_count <= shader_count_available;
    ifb_macro_assert(can_commit);

    //get the shader and tag array
    IFBGLIDShaderProgram* shader_program_array = ifb_engine::shader_manager_get_array_shader_program(shader_manager->memory);
    IFBIDTag*             shader_tag_id_array  = ifb_engine::shader_manager_get_array_tag_id(shader_manager->memory);

    //update the pointer with our commit start
    shader_program_array += shader_commit_start;

    //create the shader programs
    const ifb_b8 result = ifb_gl::shader_program_create(
        shader_count,
        shader_stage_array_vertex,
        shader_stage_array_fragment,
        shader_program_array);

    //make sure that worked
    ifb_macro_assert(result);

    //update the tags and shader ids
    for (
        ifb_u32 shader_index = 0;
        shader_index < shader_count;
        ++shader_index) {

        const ifb_u32 shader_id = shader_commit_start + shader_index;

        //update the shader id array
        shader_id_array[shader_index].index = shader_id;

        //update the tag
        shader_tag_id_array[shader_id] = shader_tag_array[shader_index];
    }
}

inline const ifb_b8
ifb_engine::shader_manager_use_program(
    const IFBEngineManagerShader* shader_manager_ptr,
    const IFBIDShader             shader_id) {

    const IFBGLIDShaderProgram shader_program = ifb_engine::shader_manager_get_shader_program(
        shader_manager_ptr,
        shader_id);

    const ifb_b8 result = ifb_gl::shader_program_set_active(shader_program);

    return(result);
}

inline const IFBIDTag
ifb_engine::shader_manager_get_tag_id(
    const IFBEngineManagerShader* shader_manager_ptr,
    const IFBIDShader             shader_id) {

    IFBIDTag* shader_tag_id_array = ifb_engine::shader_manager_get_array_tag_id(shader_manager_ptr->memory);

    const IFBIDTag tag_id = shader_tag_id_array[shader_id.index];

    return(tag_id);
}

inline const IFBGLIDShaderProgram
ifb_engine::shader_manager_get_shader_program(
    const IFBEngineManagerShader* shader_manager_ptr,
    const IFBIDShader             shader_id) {

    IFBGLIDShaderProgram* shader_program_array = ifb_engine::shader_manager_get_array_shader_program(shader_manager_ptr->memory);

    const IFBGLIDShaderProgram shader_program = shader_program_array[shader_id.index];

    return(shader_program); 
}

inline IFBIDTag*
ifb_engine::shader_manager_get_array_tag_id(
    const IFBEngineManagerMemoryShader& shader_manager_memory_ref) {

    //get the starting address
    const ifb_address memory_start    = shader_manager_memory_ref.start;
    const ifb_address tag_array_start = memory_start + shader_manager_memory_ref.offset_shader_program_tag;

    //cast the array to a pointer
    IFBIDTag* tag_array_pointer = (IFBIDTag*)tag_array_start;

    //we're done
    return(tag_array_pointer);
}

inline IFBGLIDShaderProgram*
ifb_engine::shader_manager_get_array_shader_program(
    const IFBEngineManagerMemoryShader& shader_manager_memory_ref) {

    //get the starting address
    const ifb_address memory_start       = shader_manager_memory_ref.start;
    const ifb_address shader_array_start = memory_start + shader_manager_memory_ref.offset_shader_program_array;

    //cast the array to a pointer
    IFBGLIDShaderProgram* shader_array_pointer = (IFBGLIDShaderProgram*)shader_array_start;

    //we're done
    return(shader_array_pointer);
}

