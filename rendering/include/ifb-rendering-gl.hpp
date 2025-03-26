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

struct IFBGLViewport;

struct IFBGLID { GLuint gl_id; };

struct IFBGLIDShaderStage         : IFBGLID            { };
struct IFBGLIDShaderProgram       : IFBGLID            { };
struct IFBGLIDUniform             : IFBGLID            { };
struct IFBGLIDVertex              : IFBGLID            { };
struct IFBGLIDBuffer              : IFBGLID            { };

struct IFBGLIDShaderStageVertex   : IFBGLIDShaderStage { };   
struct IFBGLIDShaderStageFragment : IFBGLIDShaderStage { }; 

struct IFBGLIDUniformU32          : IFBGLIDUniform     { };
struct IFBGLIDUniformF32          : IFBGLIDUniform     { };
struct IFBGLIDUniformVec2         : IFBGLIDUniform     { };
struct IFBGLIDUniformVec3         : IFBGLIDUniform     { };
struct IFBGLIDUniformMat3         : IFBGLIDUniform     { };
struct IFBGLIDUniformMat4         : IFBGLIDUniform     { };

struct IFBGLIDBufferVertex        : IFBGLIDBuffer      { };
struct IFBGLIDBufferElement       : IFBGLIDBuffer      { };

#define IFB_GL_INVALID_UNIFORM_LOCATION -1

struct IFBGLShaderContext {
    IFBGLIDShaderProgram gl_shader_program;
    IFBGLIDVertex        gl_vertex_object;
};

/**********************************************************************************/
/* VIEWPORT                                                                       */
/**********************************************************************************/

enum IFBGLViewportUpdateFlags_ {
    IFBGLViewportUpdateFlags_None                  = IFB_BIT_FLAG_0,
    IFBGLViewportUpdateFlags_PositionAndDimensions = IFB_BIT_FLAG_1,
    IFBGLViewportUpdateFlags_ClearColor            = IFB_BIT_FLAG_2
};

typedef IFBU32 IFBGLViewportUpdateFlags;

struct IFBGLViewport {
    IFBGLViewportUpdateFlags flags;
    IFBPosition              position;
    IFBDimensions            dimensions;
    IFBColorNormalized       clear_color;
};

struct IFBGLViewportArgs {
    IFBMemory           memory;
    IFBPosition         position;
    IFBDimensions       dimensions;
    IFBColorNormalized  clear_color;
};
namespace ifb_gl {

    const IFBU32       viewport_memory_size                              (IFBVoid);
    IFBGLViewport*     viewport_memory_initialize                        (const IFBGLViewportArgs& args);

    IFBVoid            viewport_clear                                    (IFBGLViewport* viewport);
    IFBVoid            viewport_update                                   (IFBGLViewport* viewport);

    inline IFBVoid     viewport_update_flags_set_position_and_dimensions (IFBGLViewportUpdateFlags& flags)       { ifb_macro_bit_set(IFBGLViewportUpdateFlags_PositionAndDimensions, flags); }
    inline IFBVoid     viewport_update_flags_set_clear_color             (IFBGLViewportUpdateFlags& flags)       { ifb_macro_bit_set(IFBGLViewportUpdateFlags_ClearColor,            flags); }

    inline const IFBB8 viewport_update_flags_get_position_and_dimensions (const IFBGLViewportUpdateFlags& flags) { return(ifb_macro_bit_test(IFBGLViewportUpdateFlags_PositionAndDimensions, flags)); }
    inline const IFBB8 viewport_update_flags_get_clear_color             (const IFBGLViewportUpdateFlags& flags) { return(ifb_macro_bit_test(IFBGLViewportUpdateFlags_ClearColor,            flags)); }
};

/**********************************************************************************/
/* SHADER STAGE                                                                   */
/**********************************************************************************/

namespace ifb_gl {

    const IFBB8
    shader_stage_compile(
        const GLuint              shader_stage_type,
        const IFBU32              shader_stage_count,
        const IFBChar**           shader_stage_buffers,
              IFBGLIDShaderStage* shader_stage_array); 
    
    const IFBB8 shader_stage_compile_vertex   (const IFBU32 shader_stage_vertex_count,   const IFBChar** shader_stage_vertex_buffers,   IFBGLIDShaderStageVertex*   shader_stage_vertex_array); 
    const IFBB8 shader_stage_compile_fragment (const IFBU32 shader_stage_fragment_count, const IFBChar** shader_stage_fragment_buffers, IFBGLIDShaderStageFragment* shader_stage_fragment_array); 
    
    const IFBB8
    shader_stage_delete(
        const IFBU32              shader_stage_count,
        const IFBGLIDShaderStage* shader_stage_array);
};

/**********************************************************************************/
/* SHADER PROGRAM                                                                 */
/**********************************************************************************/

namespace ifb_gl {

    const IFBB8
    shader_program_create(
        const IFBU32                     shader_program_count,
        const IFBGLIDShaderStageVertex*   shader_stage_array_vertex,
        const IFBGLIDShaderStageFragment* shader_stage_array_fragment,
              IFBGLIDShaderProgram*       shader_program_array);

    const IFBB8
    shader_program_delete(
        const IFBU32               shader_program_count,
        const IFBGLIDShaderProgram* shader_program_array);

    const IFBB8 
    shader_program_set_active(const IFBGLIDShaderProgram shader_program);
};

/**********************************************************************************/
/* UNIFORMS                                                                       */
/**********************************************************************************/

namespace ifb_gl {

    const IFBB8 
    uniform_get_locations_in_shader_program(
        const IFBGLIDShaderProgram program,
        const IFBU32               uniform_count,
        const IFBChar**            uniform_names,
              IFBGLIDUniform*      uniform_array);

    const IFBB8 uniform_update_u32  (const IFBGLIDUniformU32  uniform, const IFBU32 count, const IFBU32*  u32);
    const IFBB8 uniform_update_f32  (const IFBGLIDUniformF32  uniform, const IFBU32 count, const IFBF32*  f32);
    const IFBB8 uniform_update_vec2 (const IFBGLIDUniformVec2 uniform, const IFBU32 count, const IFBVec2* vec2);
    const IFBB8 uniform_update_vec3 (const IFBGLIDUniformVec3 uniform, const IFBU32 count, const IFBVec3* vec3);
    const IFBB8 uniform_update_mat3 (const IFBGLIDUniformMat3 uniform, const IFBU32 count, const IFBMat3* mat3);
};

/**********************************************************************************/
/* BUFFERS                                                                        */
/**********************************************************************************/

namespace ifb_gl {

    const IFBB8 buffer_create(const IFBU32 buffer_count, IFBGLIDBuffer* buffer_array);

    const IFBB8 buffer_create_vertex  (const IFBU32 vertex_buffer_count,  IFBGLIDBufferVertex*  vertex_buffer_array);
    const IFBB8 buffer_create_element (const IFBU32 element_buffer_count, IFBGLIDBufferElement* element_buffer_array);

    const IFBB8
    buffer_data_upload_vertex(
        const IFBU32               vertex_buffer_count,
        const IFBGLIDBufferVertex* vertex_buffer_array,
        const IFBU32*              vertex_buffer_size_array,
        const IFBVoid*             vertex_buffer_data);

    const IFBB8
    buffer_data_upload_element(
        const IFBU32                element_buffer_count,
        const IFBGLIDBufferElement* element_buffer_array,
        const IFBU32*               element_buffer_size_array,
        const IFBVoid*              element_buffer_data);
};

/**********************************************************************************/
/* VERTEX                                                                         */
/**********************************************************************************/

enum IFBGLVertexAttributeType : IFBU32 {
    IFBGLVertexAttributeType_S8  = 0,
    IFBGLVertexAttributeType_U8  = 1,
    IFBGLVertexAttributeType_S16 = 2,
    IFBGLVertexAttributeType_U16 = 3,
    IFBGLVertexAttributeType_S32 = 4,
    IFBGLVertexAttributeType_U32 = 5,
    IFBGLVertexAttributeType_F32 = 6
};

ifb_global const IFBU32 IFB_GL_VERTEX_ATTRIBUTE_GL_TYPES[] = {
    GL_BYTE,
    GL_UNSIGNED_BYTE,
    GL_SHORT,
    GL_UNSIGNED_SHORT,
    GL_INT,
    GL_UNSIGNED_INT,
    GL_FLOAT
};

ifb_global const IFBU32 IFB_GL_VERTEX_ATTRIBUTE_SIZES[] = {
    sizeof(IFBS8),  // GL_BYTE
    sizeof(IFBU8),  // GL_UNSIGNED_BYTE
    sizeof(IFBS16), // GL_SHORT
    sizeof(IFBU16), // GL_UNSIGNED_SHORT
    sizeof(IFBS32), // GL_INT
    sizeof(IFBU32), // GL_UNSIGNED_INT
    sizeof(IFBF32)  // GL_FLOAT
};

namespace ifb_gl {

    const IFBB8
    vertex_create(
        const IFBU32        vertex_count,
              IFBGLIDVertex* vertex_array);

    const IFBB8
    vertex_enable_attributes(
        const IFBGLIDVertex             vertex_ref,
        const IFBU32                   vertex_size,
        const IFBGLIDBuffer             vertex_buffer,
        const IFBAddr               vertex_buffer_offset,
        const IFBU32                   vertex_attribute_count,
        const IFBGLVertexAttributeType* vertex_attribute_types_array,
        const IFBU32*                  vertex_attribute_base_offset_array);

    const GLenum vertex_attribute_type_get_gl_type (const IFBGLVertexAttributeType vertex_attribute_type);
    const IFBU32 vertex_attribute_type_get_size    (const IFBGLVertexAttributeType vertex_attribute_type);
};

#endif //IFB_RENDERING_GL_HPP