#pragma once

#include "ifb-rendering-gl.hpp"

inline const IFBB8
ifb_gl::vertex_create(
    const IFBU32        vertex_count,
          IFBGLIDVertex* vertex_array) {

    //forward declarations
    IFBB8 result   = true;
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

inline const IFBB8
ifb_gl::vertex_enable_attributes(
    const IFBGLIDVertex             vertex,
    const IFBU32                   vertex_size,
    const IFBGLIDBuffer             vertex_buffer,
    const IFBAddr               vertex_buffer_offset,
    const IFBU32                   vertex_attribute_count,
    const IFBGLVertexAttributeType* vertex_attribute_types_array,
    const IFBU32*                  vertex_attribute_base_offset_array) {

    //sanity check
    ifb_macro_assert(vertex_size                        != 0);
    ifb_macro_assert(vertex_attribute_count             != 0);
    ifb_macro_assert(vertex_attribute_types_array       != NULL);
    ifb_macro_assert(vertex_attribute_base_offset_array != NULL);

    //forward declarations
    IFBB8 result   = true;
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
        IFBU32 vertex_attribute_index = 0;
        vertex_attribute_index < vertex_attribute_count;
        ++vertex_attribute_index) {

        //get the current attribute
        const IFBGLVertexAttributeType vertex_attribute_type = vertex_attribute_types_array[vertex_attribute_index];

        //get the gl type, attribute size, and offset
        const GLenum    vertex_attribute_gl_type = ifb_gl::vertex_attribute_type_get_gl_type (vertex_attribute_type);
        const IFBU32   vertex_attribute_size    = ifb_gl::vertex_attribute_type_get_size    (vertex_attribute_type);
        const IFBU32   vertex_attribute_offset  = vertex_attribute_base_offset_array[vertex_attribute_index];
        const IFBVoid* vertex_attribute_ptr     = (IFBVoid*)(vertex_buffer_offset + vertex_attribute_offset); 

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
ifb_gl::vertex_attribute_type_get_gl_type(
    const IFBGLVertexAttributeType vertex_attribute_type) {

    return(IFB_GL_VERTEX_ATTRIBUTE_GL_TYPES[vertex_attribute_type]);
}

inline const IFBU32 
ifb_gl::vertex_attribute_type_get_size(
    const IFBGLVertexAttributeType vertex_attribute_type) {

    return(IFB_GL_VERTEX_ATTRIBUTE_SIZES[vertex_attribute_type]);
}