#pragma once

#include "ifb-rendering-gl.hpp"

inline const ifb::b8
ifb::gl::vertex_create(
    const ifb::u32        vertex_count,
          gl_id_tVertex* vertex_array) {

    //forward declarations
    ifb::b8 result   = true;
    GLenum gl_error = 0;  
    
    //sanity check
    ifb_macro_assert(vertex_count != 0);
    ifb_macro_assert(vertex_array != NULL);    

    //create the vertex arrays
    glCreateVertexArrays(vertex_count,(GLuint*)vertex_array);

    //check errors
    ifb_gl_macro_check_error(result,gl_error);

    //unbind any vertex arrays
    glBindVertexArray(0);
    
    //final error check
    ifb_gl_macro_check_error(result,gl_error);

    //we're done
    return(result);
}

inline const ifb::b8
ifb::gl::vertex_enable_attributes(
    const gl_id_tVertex             vertex,
    const ifb::u32                   vertex_size,
    const gl_id_tBuffer             vertex_buffer,
    const ifb::addr               vertex_buffer_offset,
    const ifb::u32                   vertex_attribute_count,
    const gl_vertex_attribute_type_e* vertex_attribute_types_array,
    const ifb::u32*                  vertex_attribute_base_offset_array) {

    //sanity check
    ifb_macro_assert(vertex_size                        != 0);
    ifb_macro_assert(vertex_attribute_count             != 0);
    ifb_macro_assert(vertex_attribute_types_array       != NULL);
    ifb_macro_assert(vertex_attribute_base_offset_array != NULL);

    //forward declarations
    ifb::b8 result   = true;
    GLenum gl_error = 0;

    //bind the vertex array
    glBindVertexArray(vertex.gl_id);
    ifb_gl_macro_check_error(result,gl_error);

    //bind the vertex buffer
    glBindVertexBuffer(
        0,
        vertex_buffer.gl_id,
        vertex_buffer_offset,
        vertex_size);

    //loop through the attributes and enable them
    for (
        ifb::u32 vertex_attribute_index = 0;
        vertex_attribute_index < vertex_attribute_count;
        ++vertex_attribute_index) {

        //get the current attribute
        const gl_vertex_attribute_type_e vertex_attribute_type = vertex_attribute_types_array[vertex_attribute_index];

        //get the gl type, attribute size, and offset
        const GLenum    vertex_attribute_gl_type = ifb::gl::vertex_attribute_type_get_gl_type (vertex_attribute_type);
        const ifb::u32   vertex_attribute_size    = ifb::gl::vertex_attribute_type_get_size    (vertex_attribute_type);
        const ifb::u32   vertex_attribute_offset  = vertex_attribute_base_offset_array[vertex_attribute_index];
        const void* vertex_attribute_ptr     = (void*)(vertex_buffer_offset + vertex_attribute_offset); 

        //enable the attribute
        glEnableVertexAttribArray(vertex_attribute_index);
        glVertexAttribPointer(
            vertex_attribute_index,
            vertex_attribute_size,
            vertex_attribute_gl_type,
            GL_FALSE,
            vertex_size,
            vertex_attribute_ptr);

        //check errors
        ifb_gl_macro_check_error(result,gl_error);
    }

    //unbind the vertex array
    glBindVertexArray(0);

    //last error check
    ifb_gl_macro_check_error(result,gl_error);

    //we're done
    return(result);
}

inline const GLenum 
ifb::gl::vertex_attribute_type_get_gl_type(
    const gl_vertex_attribute_type_e vertex_attribute_type) {

    return(IFB_GL_VERTEX_ATTRIBUTE_GL_TYPES[vertex_attribute_type]);
}

inline const ifb::u32 
ifb::gl::vertex_attribute_type_get_size(
    const gl_vertex_attribute_type_e vertex_attribute_type) {

    return(IFB_GL_VERTEX_ATTRIBUTE_SIZES[vertex_attribute_type]);
}