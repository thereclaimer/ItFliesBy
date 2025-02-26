#pragma once

#include "ifb-rendering-gl.hpp"


inline const IFBB8 
ifb_gl::buffer_create(
    const IFBU32        buffer_count, 
          IFBGLIDBuffer* buffer_array) {

    //sanity check
    ifb_macro_assert(buffer_count != 0);
    ifb_macro_assert(buffer_array != NULL);

    //forward declarations
    IFBB8 result   = true;
    GLenum gl_error = 0;

    //generate the buffers
    glGenBuffers(buffer_count,(GLuint*)buffer_array);

    //check errors
    ifb_gl_macro_check_error(result,gl_error);

    //we're done
    return(result);
}

inline const IFBB8 
ifb_gl::buffer_create_vertex(
    const IFBU32              vertex_buffer_count,
          IFBGLIDBufferVertex* vertex_buffer_array) {

    const IFBB8 result = ifb_gl::buffer_create(
        vertex_buffer_count,
        vertex_buffer_array);

    return(result);
}

inline const IFBB8 
ifb_gl::buffer_create_element(
    const IFBU32               element_buffer_count,
          IFBGLIDBufferElement* element_buffer_array) {
    
    const IFBB8 result = ifb_gl::buffer_create(
        element_buffer_count,
        element_buffer_array);

    return(result);
}

inline const IFBB8
ifb_gl::buffer_data_upload_vertex(
    const IFBU32              vertex_buffer_count,
    const IFBGLIDBufferVertex* vertex_buffer_array,
    const IFBU32*             vertex_buffer_size_array,
    const IFBVoid*            vertex_buffer_data) {

    //sanity check
    ifb_macro_assert(vertex_buffer_count      != 0);
    ifb_macro_assert(vertex_buffer_array      != NULL);
    ifb_macro_assert(vertex_buffer_size_array != NULL);
    ifb_macro_assert(vertex_buffer_data       != NULL);

    //forward declarations
    IFBU32 buffer_offset = 0;
    IFBB8  result        = true;
    GLenum  gl_error      = 0;

    for (
        IFBU32 vertex_buffer_index = 0;
        vertex_buffer_index < vertex_buffer_count;
        ++vertex_buffer_index) {

        //get the buffer id, size, and data
        const GLuint    buffer_id   = vertex_buffer_array     [vertex_buffer_index].gl_id;
        const IFBU32   buffer_size = vertex_buffer_size_array[vertex_buffer_index];
        const IFBVoid* buffer_data = (IFBByte*)vertex_buffer_data + buffer_offset;

        //bind the buffer
        glBindBuffer(GL_ARRAY_BUFFER,buffer_id);

        //set the data
        glBufferData(
            GL_ARRAY_BUFFER,
            buffer_size,
            buffer_data,
            GL_STATIC_DRAW);

        //check errors
        ifb_gl_macro_check_error(result,gl_error);

        //update the offset
        buffer_offset += buffer_size;
    }

    //we're done
    return(result);
}

inline const IFBB8
ifb_gl::buffer_data_upload_element(
    const IFBU32               element_buffer_count,
    const IFBGLIDBufferElement* element_buffer_array,
    const IFBU32*              element_buffer_size_array,
    const IFBVoid*             element_buffer_data) {

    //sanity check
    ifb_macro_assert(element_buffer_count      != 0);
    ifb_macro_assert(element_buffer_array      != NULL);
    ifb_macro_assert(element_buffer_size_array != NULL);
    ifb_macro_assert(element_buffer_data       != NULL);

    //forward declarations
    IFBU32 buffer_offset = 0;
    IFBB8  result        = true;
    GLenum  gl_error      = 0;

    for (
        IFBU32 element_buffer_index = 0;
        element_buffer_index < element_buffer_index;
        ++element_buffer_index) {

        //get the buffer id, size, and data
        const GLuint    buffer_id   = element_buffer_array     [element_buffer_index].gl_id;
        const IFBU32   buffer_size = element_buffer_size_array[element_buffer_index];
        const IFBVoid* buffer_data = (IFBByte*)element_buffer_data + buffer_offset;

        //bind the buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer_id);

        //set the data
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            buffer_size,
            buffer_data,
            GL_STATIC_DRAW);

        //check errors
        ifb_gl_macro_check_error(result,gl_error);

        //update the offset
        buffer_offset += buffer_size;
    }

    //we're done
    return(result);
}