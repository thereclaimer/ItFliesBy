#ifndef IFB_RENDERING_GL_HPP
#define IFB_RENDERING_GL_HPP

#include <ifb-memory.hpp>

#include "ifb-dependencies.hpp"
#include "ifb-types.hpp"
#include "ifb-graphics.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define ifb_gl_macro_check_error(b8_no_error,gl_error) b8_no_error &= ((gl_error = glGetError()) == GL_NO_ERROR) 

struct gl_viewport_t;

struct gl_id_t { GLuint gl_id; };

struct gl_id_shader_stage_t          : gl_id_t              { };
struct gl_id_shader_program_t        : gl_id_t              { };
struct gl_id_uniform                 : gl_id_t              { };
struct gl_id_tVertex                 : gl_id_t              { };
struct gl_id_tBuffer                 : gl_id_t              { };

struct gl_id_shader_stage_vertex_t   : gl_id_shader_stage_t { };   
struct gl_id_shader_stage_fragment_t : gl_id_shader_stage_t { }; 

struct gl_id_uniform_u32_t           : gl_id_uniform        { };
struct gl_id_uniform_f32_t           : gl_id_uniform        { };
struct gl_id_uniform_vec2_t          : gl_id_uniform        { };
struct gl_id_uniform_vec3_t          : gl_id_uniform        { };
struct gl_id_uniform_mat3_t          : gl_id_uniform        { };
struct gl_id_uniform_mat4_t          : gl_id_uniform        { };

struct gl_id_buffer_vertex_t         : gl_id_tBuffer        { };
struct gl_id_buffer_element_t        : gl_id_tBuffer        { };

#define IFB_GL_INVALID_UNIFORM_LOCATION -1

struct gl_shader_context_t {
    gl_id_shader_program_t gl_shader_program;
    gl_id_tVertex        gl_vertex_object;
};

/**********************************************************************************/
/* VIEWPORT                                                                       */
/**********************************************************************************/

enum gl_viewport_update_flags_e_ {
    gl_viewport_update_flags_e_none                    = IFB_BIT_FLAG_0,
    gl_viewport_update_flags_e_position_and_dimensions = IFB_BIT_FLAG_1,
    gl_viewport_update_flags_e_clear_color             = IFB_BIT_FLAG_2
};

typedef u32 gl_viewport_update_flags_t;

struct gl_viewport_t {
    gl_viewport_update_flags_t   flags;
    position_t                   position;
    dimensions_t                 dimensions;
    graphics::color_normalized_t clear_color;
};

struct gl_viewport_args_t {
    memory_t                     memory;
    position_t                   position;
    dimensions_t                 dimensions;
    graphics::color_normalized_t clear_color;
};
namespace ifb::gl {

    const u32       viewport_memory_size                              (void);
    gl_viewport_t*  viewport_memory_initialize                        (const gl_viewport_args_t& args);

    void            viewport_clear                                    (gl_viewport_t* viewport);
    void            viewport_update                                   (gl_viewport_t* viewport);

    inline void     viewport_update_flags_set_position_and_dimensions (gl_viewport_update_flags_t& flags)       { ifb_macro_bit_set(gl_viewport_update_flags_e_position_and_dimensions, flags); }
    inline void     viewport_update_flags_set_clear_color             (gl_viewport_update_flags_t& flags)       { ifb_macro_bit_set(gl_viewport_update_flags_e_clear_color,             flags); }

    inline const b8 viewport_update_flags_get_position_and_dimensions (const gl_viewport_update_flags_t& flags) { return(ifb_macro_bit_test(gl_viewport_update_flags_e_position_and_dimensions, flags)); }
    inline const b8 viewport_update_flags_get_clear_color             (const gl_viewport_update_flags_t& flags) { return(ifb_macro_bit_test(gl_viewport_update_flags_e_clear_color,             flags)); }
};

/**********************************************************************************/
/* SHADER STAGE                                                                   */
/**********************************************************************************/

namespace ifb::gl {

    const b8
    shader_stage_compile(
        const GLuint                shader_stage_type,
        const u32                   shader_stage_count,
        const utf8**                shader_stage_buffers,
              gl_id_shader_stage_t* shader_stage_array); 
    
    const b8 shader_stage_compile_vertex   (const u32 shader_stage_vertex_count,   const utf8** shader_stage_vertex_buffers,   gl_id_shader_stage_vertex_t*   shader_stage_vertex_array); 
    const b8 shader_stage_compile_fragment (const u32 shader_stage_fragment_count, const utf8** shader_stage_fragment_buffers, gl_id_shader_stage_fragment_t* shader_stage_fragment_array); 
    
    const b8
    shader_stage_delete(
        const u32              shader_stage_count,
        const gl_id_shader_stage_t* shader_stage_array);
};

/**********************************************************************************/
/* SHADER PROGRAM                                                                 */
/**********************************************************************************/

namespace ifb::gl {

    const b8
    shader_program_create(
        const u32                            shader_program_count,
        const gl_id_shader_stage_vertex_t*   shader_stage_array_vertex,
        const gl_id_shader_stage_fragment_t* shader_stage_array_fragment,
              gl_id_shader_program_t*        shader_program_array);

    const b8
    shader_program_delete(
        const u32                     shader_program_count,
        const gl_id_shader_program_t* shader_program_array);

    const b8 
    shader_program_set_active(const gl_id_shader_program_t shader_program);
};

/**********************************************************************************/
/* UNIFORMS                                                                       */
/**********************************************************************************/

namespace ifb::gl {

    const b8 
    uniform_get_locations_in_shader_program(
        const gl_id_shader_program_t program,
        const u32                    uniform_count,
        const utf8**                 uniform_names,
              gl_id_uniform*         uniform_array);

    const b8 uniform_update_u32  (const gl_id_uniform_u32_t  uniform, const u32 count, const u32*  u32);
    const b8 uniform_update_f32  (const gl_id_uniform_f32_t  uniform, const u32 count, const f32*  f32);
    const b8 uniform_update_vec2 (const gl_id_uniform_vec2_t uniform, const u32 count, const vec2_t* vec2);
    const b8 uniform_update_vec3 (const gl_id_uniform_vec3_t uniform, const u32 count, const vec3_t* vec3);
    const b8 uniform_update_mat3 (const gl_id_uniform_mat3_t uniform, const u32 count, const mat3_t* mat3);
};

/**********************************************************************************/
/* BUFFERS                                                                        */
/**********************************************************************************/

namespace ifb::gl {

    const b8 buffer_create(const u32 buffer_count, gl_id_tBuffer* buffer_array);

    const b8 buffer_create_vertex  (const u32 vertex_buffer_count,  gl_id_buffer_vertex_t*  vertex_buffer_array);
    const b8 buffer_create_element (const u32 element_buffer_count, gl_id_buffer_element_t* element_buffer_array);

    const b8
    buffer_data_upload_vertex(
        const u32                    vertex_buffer_count,
        const gl_id_buffer_vertex_t* vertex_buffer_array,
        const u32*                   vertex_buffer_size_array,
        const void*                  vertex_buffer_data);

    const b8
    buffer_data_upload_element(
        const u32                     element_buffer_count,
        const gl_id_buffer_element_t* element_buffer_array,
        const u32*                    element_buffer_size_array,
        const void*                   element_buffer_data);
};

/**********************************************************************************/
/* VERTEX                                                                         */
/**********************************************************************************/

enum gl_vertex_attribute_type_e : u32 {
    gl_vertex_attribute_type_e_s8  = 0,
    gl_vertex_attribute_type_e_u8  = 1,
    gl_vertex_attribute_type_e_s16 = 2,
    gl_vertex_attribute_type_e_u16 = 3,
    gl_vertex_attribute_type_e_s32 = 4,
    gl_vertex_attribute_type_e_u32 = 5,
    gl_vertex_attribute_type_e_f32 = 6
};

ifb_global const u32 IFB_GL_VERTEX_ATTRIBUTE_GL_TYPES[] = {
    GL_BYTE,
    GL_UNSIGNED_BYTE,
    GL_SHORT,
    GL_UNSIGNED_SHORT,
    GL_INT,
    GL_UNSIGNED_INT,
    GL_FLOAT
};

ifb_global const u32 IFB_GL_VERTEX_ATTRIBUTE_SIZES[] = {
    sizeof(s8),  // GL_BYTE
    sizeof(u8),  // GL_UNSIGNED_BYTE
    sizeof(s16), // GL_SHORT
    sizeof(u16), // GL_UNSIGNED_SHORT
    sizeof(s32), // GL_INT
    sizeof(u32), // GL_UNSIGNED_INT
    sizeof(f32)  // GL_FLOAT
};

namespace ifb::gl {

    const b8
    vertex_create(
        const u32            vertex_count,
              gl_id_tVertex* vertex_array);

    const b8
    vertex_enable_attributes(
        const gl_id_tVertex               vertex_ref,
        const u32                         vertex_size,
        const gl_id_tBuffer               vertex_buffer,
        const addr                        vertex_buffer_offset,
        const u32                         vertex_attribute_count,
        const gl_vertex_attribute_type_e* vertex_attribute_types_array,
        const u32*                        vertex_attribute_base_offset_array);

    const GLenum vertex_attribute_type_get_gl_type (const gl_vertex_attribute_type_e vertex_attribute_type);
    const u32    vertex_attribute_type_get_size    (const gl_vertex_attribute_type_e vertex_attribute_type);
};

#endif //IFB_RENDERING_GL_HPP