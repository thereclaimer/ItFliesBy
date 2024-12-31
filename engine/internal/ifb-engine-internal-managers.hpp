#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* TAG MANAGER                                                                    */
/**********************************************************************************/

struct IFBEngineTagManagerMemory {
    ifb_address commit_address;
    ifb_u16     offset_char_buffer;
    ifb_u16     offset_hash_array;
    IFBIDCommit commit_id;
};

struct IFBEngineTagManager {
    IFBEngineTagManagerMemory memory;
    ifb_u32                   tag_c_str_length;
    ifb_u32                   tag_count_max;
};

namespace ifb_engine {

    ifb_void
    tag_manager_initialize(
              IFBEngineTagManager* tag_manager_ptr,
              IFBEngineMemory*     memory_ptr,
        const ifb_u32              tag_c_str_length,
        const ifb_u32              tag_count_max);

    const IFBIDTag  tag_manager_reserve_tag             (const IFBEngineTagManager* tag_manager_ptr, const ifb_cstr  tag_c_str);
          ifb_void  tag_manager_release_tag             (const IFBEngineTagManager* tag_manager_ptr, const IFBIDTag& tag_id_ref);
    const ifb_cstr  tag_manager_get_tag_c_str           (const IFBEngineTagManager* tag_manager_ptr, const IFBIDTag& tag_id_ref);
    const IFBHash   tag_manager_get_hash                (const IFBEngineTagManager* tag_manager_ptr, const IFBIDTag& tag_id_ref);

          ifb_char* tag_manager_get_pointer_char_buffer (const IFBEngineTagManagerMemory& tag_manager_memory_ref);
          IFBHash*  tag_manager_get_pointer_hash_array  (const IFBEngineTagManagerMemory& tag_manager_memory_ref);
};

/**********************************************************************************/
/* ARENA MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineArenaManagerMemory {
    ifb_address start;
    ifb_u16     offset_commit_id_array; // IFBIDCommit
    ifb_u16     offset_tag_id_array;    // IFBIDTag
    ifb_u16     offset_arena_start;     // ifb_address
    ifb_u16     offset_arena_size;      // ifb_u32
    IFBIDCommit commit_id;
};

struct IFBEngineArenaManager {
    IFBEngineArenaManagerMemory memory;
    ifb_u32                     arena_minimum_size;
    ifb_u32                     arena_minimum_pages;
    ifb_u32                     arena_count_max;
    ifb_u32                     arena_count_committed;
};

namespace ifb_engine {

    ifb_void 
    arena_manager_initialize(
              IFBEngineArenaManager* arena_manager_ptr,
              IFBEngineMemory*       memory_ptr,
        const ifb_u32                arena_minimum_size,
        const ifb_u32                arena_count_max);

    const IFBIDArena 
    arena_manager_commit_arena(
              IFBEngineArenaManager* arena_manager_ptr, 
              IFBEngineMemory*       memory_ptr,
        const IFBIDTag               arena_tag_id,
        const ifb_u32                arena_commit_size_minimum);

    const ifb_u32      arena_manager_align_size_to_arena (const IFBEngineArenaManager* arena_manager_ptr, const ifb_u32 size);
    const IFBIDCommit  arena_manager_get_arena_commit_id (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref);
    const IFBIDTag     arena_manager_get_arena_tag_id    (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref);
    const ifb_u32      arena_manager_get_arena_size      (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref);
    const ifb_u32      arena_manager_get_arena_start     (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref);
    const ifb_ptr      arena_manager_get_arena_pointer   (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref);
    const ifb_ptr      arena_manager_get_arena_pointer   (const IFBEngineArenaManager* arena_manager_ptr, const IFBIDArena& arena_id_ref, const ifb_u32 offset);
          
    IFBIDCommit* arena_manager_get_pointer_commit_id_array   (const IFBEngineArenaManagerMemory& arena_manager_memory_ref);
    IFBIDTag*    arena_manager_get_pointer_tag_id_array      (const IFBEngineArenaManagerMemory& arena_manager_memory_ref);
    ifb_address* arena_manager_get_pointer_arena_start_array (const IFBEngineArenaManagerMemory& arena_manager_memory_ref);
    ifb_u32*     arena_manager_get_pointer_arena_size_array  (const IFBEngineArenaManagerMemory& arena_manager_memory_ref);
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineGraphicsManagerMemory {
    ifb_address start;
    ifb_u16     offset_window;
    ifb_u16     offset_viewport;
    ifb_u16     offset_monitor_array;
    IFBIDCommit commit_id;
};

struct IFBEngineGraphicsManager {
    IFBEngineGraphicsManagerMemory memory;
    ifb_u32                        monitor_count;
    ifb_u32                        monitor_primary_index;
};

namespace ifb_engine {

    ifb_void 
    graphics_manger_initialize(
        IFBEngineGraphicsManager* graphics_manager_ptr,
        IFBEngineMemory*          memory_ptr);

    ifb_void
    graphics_manager_commit_memory(
              IFBEngineGraphicsManagerMemory& graphics_manager_memory,
              IFBEngineMemory*                memory_ptr,
        const ifb_u32                         monitor_count);

    ifb_void 
    graphics_manager_create_window (
              IFBEngineGraphicsManager* graphics_manager_ptr,
        const ifb_cstr                  window_title,
        const IFBWindowFlags            window_flags);

    ifb_void graphics_manager_create_viewport (IFBEngineGraphicsManager* graphics_manager_ptr);
    ifb_void graphics_manager_style_imgui     (IFBEngineGraphicsManager* graphics_manager_ptr);
    ifb_void graphics_manager_frame_start     (IFBEngineGraphicsManager* graphics_manager_ptr);
    ifb_void graphics_manager_frame_render    (IFBEngineGraphicsManager* graphics_manager_ptr);

    const ifb_u32     grahpics_manager_find_primary_monitor_index (const IFBMonitor* monitor_array_ptr);
    const IFBMonitor* graphics_manager_get_monitor                (const IFBEngineGraphicsManager* graphics_manager_ptr, const ifb_u32 monitor_index);

    IFBWindow*     graphics_manager_get_window_pointer        (const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref);
    IFBMonitor*    graphics_manager_get_monitor_array_pointer (const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref);
    IFBGLViewport* graphics_manager_get_viewport              (const IFBEngineGraphicsManagerMemory& graphics_manager_memory_ref);
};

/**********************************************************************************/
/* SHADER MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineShaderManagerMemory {
    ifb_address start;
    ifb_u32     offset_shader_program_array;
    ifb_u32     offset_shader_program_tag;
    IFBIDCommit commit_id;
};

struct IFBEngineShaderManager {
    IFBEngineShaderManagerMemory memory;
    ifb_u32                      shader_program_count_total;
    ifb_u32                      shader_program_count_committed;
};

namespace ifb_engine { 

    ifb_void
    shader_manager_initialize(
              IFBEngineShaderManager* shader_manager,
              IFBEngineMemory*        memory,
        const ifb_u32                 shader_count_max);

    ifb_void
    shader_manager_commit_shaders(
              IFBEngineShaderManager*   shader_manager,
        const ifb_u32                   shader_count,
        const IFBGLShaderStageVertex*   shader_stage_array_vertex,
        const IFBGLShaderStageFragment* shader_stage_array_fragment,
        const IFBIDTag*                 shader_tag_array,
              IFBIDShader*              shader_id_array);

    const ifb_b8              shader_manager_use_program        (const IFBEngineShaderManager* shader_manager_ptr, const IFBIDShader shader_id);
    const IFBIDTag            shader_manager_get_tag_id         (const IFBEngineShaderManager* shader_manager_ptr, const IFBIDShader shader_id);
    const IFBGLShaderProgram  shader_manager_get_shader_program (const IFBEngineShaderManager* shader_manager_ptr, const IFBIDShader shader_id);

    IFBIDTag*                 shader_manager_get_array_tag_id         (IFBEngineShaderManagerMemory& shader_manager_memory_ref);
    IFBGLShaderProgram*       shader_manager_get_array_shader_program (IFBEngineShaderManagerMemory& shader_manager_memory_ref);

};

/**********************************************************************************/
/* UNIFORM MANAGER                                                                */
/**********************************************************************************/

#define IFB_ENGINE_UNIFORM_MANAGER_VALUE_SIZE_VEC2 2
#define IFB_ENGINE_UNIFORM_MANAGER_VALUE_SIZE_VEC3 3
#define IFB_ENGINE_UNIFORM_MANAGER_VALUE_SIZE_MAT3 9
#define IFB_ENGINE_UNIFORM_MANAGER_VALUE_SIZE_MAT4 16

struct IFBEngineUniformManagerMemory {
    ifb_address start;
    ifb_u32     offset_uniform_u32;
    ifb_u32     offset_uniform_f32;
    ifb_u32     offset_uniform_vec2;
    ifb_u32     offset_uniform_vec3;
    ifb_u32     offset_uniform_mat3;
    ifb_u32     offset_uniform_mat4;
    IFBIDCommit commit;
};  

struct IFBEngineUniformManager {
    IFBEngineUniformManagerMemory memory;
    ifb_u32                       count_uniform_u32;
    ifb_u32                       count_uniform_f32;
    ifb_u32                       count_uniform_vec2;
    ifb_u32                       count_uniform_vec3;
    ifb_u32                       count_uniform_mat3;
    ifb_u32                       count_uniform_mat4;
};
     
struct IFBEngineUniformManagerDataU32 {
    IFBGLUniformU32 gl_uniform_u32;    
    IFBIDShader     shader;
    IFBIDTag        tag;
    ifb_u32         value;
};

struct IFBEngineUniformManagerDataF32 {
    IFBGLUniformF32 gl_uniform_f32;
    IFBIDShader     shader;
    IFBIDTag        tag;
    ifb_f32         value;
};

struct IFBEngineUniformManagerDataVec2 {
    IFBGLUniformVec2F32 gl_uniform_vec2;    
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[2];
};

struct IFBEngineUniformManagerDataVec3 {
    IFBGLUniformVec3F32 gl_uniform_vec3;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[3];
};

struct IFBEngineUniformManagerDataMat3 {
    IFBGLUniformMat3F32 gl_uniform_mat3;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[9];
};

struct IFBEngineUniformManagerDataMat4 {
    IFBGLUniformMat4F32 gl_uniform_mat4;
    IFBIDShader         shader;
    IFBIDTag            tag;
    ifb_f32             value[16];
};

namespace ifb_engine {

    void
    uniform_manager_initialize(
              IFBEngineUniformManager* uniform_manager_ptr,
              IFBEngineMemory*         engine_memory_ptr,
        const ifb_u32                  count_uniform_u32,
        const ifb_u32                  count_uniform_f32,
        const ifb_u32                  count_uniform_vec2,
        const ifb_u32                  count_uniform_vec3,
        const ifb_u32                  count_uniform_mat3,
        const ifb_u32                  count_uniform_mat4);

    void
    uniform_manager_commit_memory(
              IFBEngineUniformManagerMemory& uniform_manager_memory_ref,
              IFBEngineMemory*               engine_memory_ptr,
        const ifb_u32                        count_uniform_u32,
        const ifb_u32                        count_uniform_f32,
        const ifb_u32                        count_uniform_vec2,
        const ifb_u32                        count_uniform_vec3,
        const ifb_u32                        count_uniform_mat3,
        const ifb_u32                        count_uniform_mat4);
     
    const IFBIDUniformU32  uniform_manger_reserve_u32  (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);
    const IFBIDUniformF32  uniform_manger_reserve_f32  (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);
    const IFBIDUniformVec2 uniform_manger_reserve_vec2 (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);
    const IFBIDUniformVec3 uniform_manger_reserve_vec3 (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);
    const IFBIDUniformMat3 uniform_manger_reserve_mat3 (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);
    const IFBIDUniformMat4 uniform_manger_reserve_mat4 (const IFBEngineUniformManager* uniform_manager_ptr, const ifb_cstr uniform_name, const IFBIDShader shader_id);

    const ifb_u32             uniform_manager_get_value_u32        (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformU32  uniform_id);
    const ifb_f32             uniform_manager_get_value_f32        (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformF32  uniform_id);
    const ifb_f32*            uniform_manager_get_value_vec2       (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec2 uniform_id);
    const ifb_f32*            uniform_manager_get_value_vec3       (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec3 uniform_id);
    const ifb_f32*            uniform_manager_get_value_mat3       (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat3 uniform_id);
    const ifb_f32*            uniform_manager_get_value_mat4       (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat4 uniform_id);

    const IFBIDTag            uniform_manager_get_tag_u32          (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformU32  uniform_id);
    const IFBIDTag            uniform_manager_get_tag_f32          (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformF32  uniform_id);
    const IFBIDTag            uniform_manager_get_tag_vec2         (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec2 uniform_id);
    const IFBIDTag            uniform_manager_get_tag_vec3         (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec3 uniform_id);
    const IFBIDTag            uniform_manager_get_tag_mat3         (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat3 uniform_id);
    const IFBIDTag            uniform_manager_get_tag_mat4         (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat4 uniform_id);

    const IFBIDShader         uniform_manager_get_shader_id_u32    (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformU32  uniform_id);
    const IFBIDShader         uniform_manager_get_shader_id_f32    (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformF32  uniform_id);
    const IFBIDShader         uniform_manager_get_shader_id_vec2   (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec2 uniform_id);
    const IFBIDShader         uniform_manager_get_shader_id_vec3   (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec3 uniform_id);
    const IFBIDShader         uniform_manager_get_shader_id_mat3   (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat3 uniform_id);
    const IFBIDShader         uniform_manager_get_shader_id_mat4   (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat4 uniform_id);

    const IFBGLUniformU32     uniform_manager_get_gl_location_u32  (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformU32  uniform_id);
    const IFBGLUniformF32     uniform_manager_get_gl_location_f32  (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformF32  uniform_id);
    const IFBGLUniformVec2F32 uniform_manager_get_gl_location_vec2 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec2 uniform_id);
    const IFBGLUniformVec3F32 uniform_manager_get_gl_location_vec3 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec3 uniform_id);
    const IFBGLUniformMat3F32 uniform_manager_get_gl_location_mat3 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat3 uniform_id);
    const IFBGLUniformMat4F32 uniform_manager_get_gl_location_mat4 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat4 uniform_id);

    ifb_void uniform_manager_set_value_u32  (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformU32  uniform_id, const ifb_u32  uniform_value);
    ifb_void uniform_manager_set_value_f32  (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformF32  uniform_id, const ifb_f32  uniform_value);
    ifb_void uniform_manager_set_value_vec2 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec2 uniform_id, const ifb_f32* uniform_value);
    ifb_void uniform_manager_set_value_vec3 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformVec3 uniform_id, const ifb_f32* uniform_value);
    ifb_void uniform_manager_set_value_mat3 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat3 uniform_id, const ifb_f32* uniform_value);
    ifb_void uniform_manager_set_value_mat4 (const IFBEngineUniformManager* uniform_manager_ptr, const IFBIDUniformMat4 uniform_id, const ifb_f32* uniform_value);

    IFBEngineUniformManagerDataU32*  uniform_manager_get_array_u32  (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
    IFBEngineUniformManagerDataF32*  uniform_manager_get_array_f32  (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
    IFBEngineUniformManagerDataVec2* uniform_manager_get_array_vec2 (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
    IFBEngineUniformManagerDataVec3* uniform_manager_get_array_vec3 (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
    IFBEngineUniformManagerDataMat3* uniform_manager_get_array_mat3 (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
    IFBEngineUniformManagerDataMat4* uniform_manager_get_array_mat4 (const IFBEngineUniformManagerMemory& uniform_manager_memory_ref);
};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP