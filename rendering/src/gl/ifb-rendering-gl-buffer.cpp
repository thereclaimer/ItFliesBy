#pragma once

#include "ifb-rendering-gl.hpp"

inline const ifb::b8 
ifb::gl::buffer_create(
    const ifb::u32        buffer_count, 
          gl_id_tBuffer* buffer_array) {

    //sanity check
    ifb_macro_assert(buffer_count != 0);
    ifb_macro_assert(buffer_array != NULL);

    //forward declarations
    ifb::b8 result   = true;
    GLenum gl_error = 0;

    //generate the buffers
    glGenBuffers(buffer_count,(GLuint*)buffer_array);

    //check errors
    ifb_gl_macro_check_error(result,gl_error);

    //we're done
    return(result);
}

inline const ifb::b8 
ifb::gl::buffer_create_vertex(
    const ifb::u32              vertex_buffer_count,
          gl_id_buffer_vertex_t* vertex_buffer_array) {

    const ifb::b8 result = ifb::gl::buffer_create(
        vertex_buffer_count,
        vertex_buffer_array);

    return(result);
}

inline const ifb::b8 
ifb::gl::buffer_create_element(
    const ifb::u32               element_buffer_count,
          gl_id_buffer_element_t* element_buffer_array) {
    
    const ifb::b8 result = ifb::gl::buffer_create(
        element_buffer_count,
        element_buffer_array);

    return(result);
}

inline const ifb::b8
ifb::gl::buffer_data_upload_vertex(
    const ifb::u32              vertex_buffer_count,
    const gl_id_buffer_vertex_t* vertex_buffer_array,
    const ifb::u32*             vertex_buffer_size_array,
    const void*            vertex_buffer_data) {

    //sanity check
    ifb_macro_assert(vertex_buffer_count      != 0);
    ifb_macro_assert(vertex_buffer_array      != NULL);
    ifb_macro_assert(vertex_buffer_size_array != NULL);
    ifb_macro_assert(vertex_buffer_data       != NULL);

    //forward declarations
    ifb::u32 buffer_offset = 0;
    ifb::b8  result        = true;
    GLenum  gl_error      = 0;

    for (
        ifb::u32 vertex_buffer_index = 0;
        vertex_buffer_index < vertex_buffer_count;
        ++vertex_buffer_index) {

        //get the buffer id, size, and data
        const GLuint    buffer_id   = vertex_buffer_array     [vertex_buffer_index].gl_id;
        const ifb::u32   buffer_size = vertex_buffer_size_array[vertex_buffer_index];
        const void* buffer_data = (ifb::byte*)vertex_buffer_data + buffer_offset;

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

inline const ifb::b8
ifb::gl::buffer_data_upload_element(
    const ifb::u32               element_buffer_count,
    const gl_id_buffer_element_t* element_buffer_array,
    const ifb::u32*              element_buffer_size_array,
    const void*             element_buffer_data) {

    //sanity check
    ifb_macro_assert(element_buffer_count      != 0);
    ifb_macro_assert(element_buffer_array      != NULL);
    ifb_macro_assert(element_buffer_size_array != NULL);
    ifb_macro_assert(element_buffer_data       != NULL);

    //forward declarations
    ifb::u32 buffer_offset = 0;
    ifb::b8  result        = true;
    GLenum  gl_error      = 0;

    for (
        ifb::u32 element_buffer_index = 0;
        element_buffer_index < element_buffer_index;
        ++element_buffer_index) {

        //get the buffer id, size, and data
        const GLuint    buffer_id   = element_buffer_array     [element_buffer_index].gl_id;
        const ifb::u32   buffer_size = element_buffer_size_array[element_buffer_index];
        const void* buffer_data = (ifb::byte*)element_buffer_data + buffer_offset;

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