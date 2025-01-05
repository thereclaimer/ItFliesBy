#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include "ifb-engine.hpp"

#include "ifb-engine-internal-managers.hpp"

/**********************************************************************************/
/* TAG                                                                            */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 tag_update_value (const IFBIDTag  tag_id,    const ifb_char* tag_value_array);
    const ifb_b8 tag_reserve      (const ifb_char* tag_value,       IFBIDTag& tag_id_ref);
    const ifb_b8 tag_find         (const ifb_char* tag_value,       IFBIDTag& tag_id_array_ref)
    const ifb_b8 tag_get          (const IFBIDTag  tag_id_array,    IFBTag&   tag_ref);
    const ifb_b8 tag_release      (const IFBIDTag  tag_id);

    const ifb_b8 tag_update_value (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array,    const ifb_char** tag_value_array);
    const ifb_b8 tag_reserve      (const ifb_u32 tag_count, const ifb_char** tag_value_array, IFBIDTag*        tag_id_array);
    const ifb_b8 tag_find         (const ifb_u32 tag_count, const ifb_char** tag_value_array, IFBIDTag*        tag_id_array)
    const ifb_b8 tag_get          (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array,    IFBTag*          tag_array);
    const ifb_b8 tag_release      (const ifb_u32 tag_count, const IFBIDTag*  tag_id_array);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8
    arena_commit(
        const ifb_u32     arena_minimum_size,
        const ifb_char*   arena_tag_value,
              IFBIDArena& arena_id_ref);
    
    const ifb_b8 arena_get                (const IFBIDArena arena_id, IFBArena&    arena_ref);
    const ifb_b8 arena_get_size           (const IFBIDArena arena_id, ifb_u32&     arena_size_ref);
    const ifb_b8 arena_get_tag            (const IFBIDArena arena_id, IFBTag&      arena_tag_ref);
    const ifb_b8 arena_get_address_start  (const IFBIDArena arena_id, ifb_address& address_start_ref);
    const ifb_b8 arena_get_pointer_start  (const IFBIDArena arena_id, ifb_ptr&     pointer_start_ref);

    const ifb_b8 arena_align_size         (const IFBIDArena arena_id, const ifb_u32   size,   ifb_u32&     size_aligned);
    const ifb_b8 arena_get_address_offset (const IFBIDArena arena_id, const ifb_u32   offset, ifb_address& address_start_ref);
    const ifb_b8 arena_get_pointer_offset (const IFBIDArena arena_id, const ifb_u32   offset, ifb_ptr&     pointer_start_ref);
    
    const ifb_b8 arena_update_tag         (const IFBIDArena arena_id, const ifb_char* arena_tag_value);

    const ifb_b8
    arena_commit(
        const ifb_u32*     arena_count,
        const ifb_u32*     arena_minimum_size_array,
        const ifb_char**   arena_tag_value_array,
              IFBIDArena*  arena_id_array);
    
    const ifb_b8 arena_get                (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, IFBArena*    arena_array);
    const ifb_b8 arena_get_size           (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, ifb_u32*     arena_size_array);
    const ifb_b8 arena_get_tag            (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, IFBTag*      arena_tag_array);
    const ifb_b8 arena_get_address_start  (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, ifb_address* address_start_array);
    const ifb_b8 arena_get_pointer_start  (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, ifb_ptr*     pointer_start_array);

    const ifb_b8 arena_align_size         (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, const ifb_u32* size_array,   ifb_u32*     size_aligned_array);
    const ifb_b8 arena_get_address_offset (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, const ifb_u32* offset_array, ifb_address* address_start_array);
    const ifb_b8 arena_get_pointer_offset (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, const ifb_u32* offset_array, ifb_ptr*     pointer_start_array);
    
    const ifb_b8 arena_update_tag         (const ifb_u32 arena_count, const IFBIDArena* arena_id_array, const ifb_char** arena_tag_value_array);
};

/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 
    graphics_create_window(
        const ifb_cstr       window_title,
        const IFBWindowFlags window_flags);

    const ifb_b8       graphics_create_viewport        (ifb_void);
    const ifb_b8       graphics_style_imgui            (ifb_void);
    const ifb_b8       graphics_frame_start            (ifb_void);
    const ifb_b8       graphics_frame_render           (ifb_void);
    const ifb_u32      graphics_monitor_count          (ifb_void);
    const IFBIDMonitor graphics_get_primary_monitor_id (ifb_void);
    const ifb_b8       graphics_get_monitor            (const IFBIDMonitor monitor_id);
};

/**********************************************************************************/
/* SHADERS                                                                        */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8
    shader_commit(
        const ifb_cstr     shader_tag_value,
        const ifb_cstr     shader_vertex_stage_buffer,
        const ifb_cstr     shader_fragment_stage_buffer,
        const ifb_u32      shader_vertex_buffer_size,
        const ifb_u32      shader_vertex_property_count,
        const ifb_u32*     shader_vertex_property_sizes,
              IFBIDShader& shader_id_ref);
    
    const ifb_b8 shader_set_active                 (const IFBIDShader shader_id);
    const ifb_b8 shader_set_inactive               (const IFBIDShader shader_id);
    
    const ifb_b8 shader_vertex_buffer_push         (const IFBIDShader shader_id, const ifb_u32 vertex_count, const ifb_ptr vertex_array);
    const ifb_b8 shader_vertex_buffer_render       (const IFBIDShader shader_id);
    const ifb_b8 shader_vertex_buffer_reset        (const IFBIDShader shader_id);

    const ifb_b8 shader_get                        (const IFBIDShader shader_id, IFBShader&            shader_ref);
    const ifb_b8 shader_get_tag                    (const IFBIDShader shader_id, IFBTag&               shader_tag_ref);
    const ifb_b8 shader_get_arena                  (const IFBIDShader shader_id, IFBArena&             shader_arena);
    const ifb_b8 shader_get_gl_program_id          (const IFBIDShader shader_id, IFBGLIDShaderProgram& shader_gl_program_id_ref;
    const ifb_b8 shader_get_gl_vertex_id           (const IFBIDShader shader_id, IFBGLIDVertex&        shader_gl_vertex_id_ref);
    const ifb_b8 shader_get_vertex_size            (const IFBIDShader shader_id, ifb_u32&              shader_vertex_size_ref);
    const ifb_b8 shader_get_vertex_buffer_start    (const IFBIDShader shader_id, ifb_address&          shader_vertex_buffer_start_ref);
    const ifb_b8 shader_get_vertex_buffer_size     (const IFBIDShader shader_id, ifb_u32&              shader_vertex_buffer_size_ref);
    const ifb_b8 shader_get_vertex_buffer_position (const IFBIDShader shader_id, ifb_u32&              shader_vertex_buffer_position_ref);
};

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_u32 transform_count_total        (ifb_void);
    const ifb_u32 transform_count_available    (ifb_void);
    const ifb_u32 transform_count_reserved     (ifb_void);

    const ifb_b8  transform_reserve            (IFBIDTransform& transform_id_ref);
    const ifb_b8  transform_release            (const IFBIDTransform transform_id);

    const ifb_b8  transform_update_translation (const IFBIDTransform transform_id, const IFBVec2& translation_ref);
    const ifb_b8  transform_update_scale       (const IFBIDTransform transform_id, const IFBVec2& scale_ref);
    const ifb_b8  transform_update_rotation    (const IFBIDTransform transform_id, const ifb_f32  radians);
    const ifb_b8  transform_update             (const IFBTransform&  transform_ref);
    
    const ifb_b8  transform_get                (const IFBIDTransform transform_id, IFBTransform& transform_ref);
    const ifb_b8  transform_get_translation    (const IFBIDTransform transform_id, IFBVec2&      translation_ref);
    const ifb_b8  transform_get_scale          (const IFBIDTransform transform_id, IFBVec2&      scale_ref);
    const ifb_b8  transform_get_rotation       (const IFBIDTransform transform_id, ifb_f32&      radians_ref);
    const ifb_b8  transform_get_matrix         (const IFBIDTransform transform_id, IFBMat3&      matrix_ref);

    const ifb_b8  transform_reserve            (const ifb_u32 transform_count, IFBIDTransform* transform_id_array);
    const ifb_b8  transform_release            (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array);
    
    const ifb_b8  transform_update_translation (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, const IFBVec2* translation_array);
    const ifb_b8  transform_update_scale       (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, const IFBVec2* scale_array);
    const ifb_b8  transform_update_rotation    (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, const ifb_f32* radians_array);
    const ifb_b8  transform_update             (const ifb_u32 transform_count, const IFBTransform*   transform_array);
    
    const ifb_b8  transform_get                (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, IFBTransform* transform_array);
    const ifb_b8  transform_get_translation    (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, IFBVec2*      translation_array);
    const ifb_b8  transform_get_scale          (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, IFBVec2*      scale_array);
    const ifb_b8  transform_get_rotation       (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, ifb_f32*      radians_array);
    const ifb_b8  transform_get_matrix         (const ifb_u32 transform_count, const IFBIDTransform* transform_id_array, IFBMat3*      matrix_array);

    const ifb_u32
    transform_encode_to_buffer(
        const ifb_u32         transform_count,
        const IFBIDTransform* transform_id_array,
        const ifb_u32         transform_buffer_size,
        const ifb_u32         transform_buffer_start,
        const ifb_u32         transform_buffer_stride,
              ifb_memory      transform_buffer);
};

/**********************************************************************************/
/* SPRITES                                                                        */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_u32 sprite_count_total     (ifb_void);
    const ifb_u32 sprite_count_available (ifb_void);
    const ifb_u32 sprite_count_reserved  (ifb_void);

    const ifb_b8
    sprite_reserve(
        const ifb_cstr           sprite_tag_value,
        const IFBColorTableIndex sprite_color_table_index,
              IFBIDSprite&       sprite_id_ref);

    const ifb_b8 sprite_release                      (const IFBIDSprite sprite_id);

    const ifb_b8 sprite_get                          (const IFBIDSprite sprite_id, IFBSprite&          sprite_ref);
    const ifb_b8 sprite_get_transform                (const IFBIDSprite sprite_id, IFBTransform&       transform_ref);
    const ifb_b8 sprite_get_transform_translation    (const IFBIDSprite sprite_id, IFBVec2&            translation_ref);
    const ifb_b8 sprite_get_transform_scale          (const IFBIDSprite sprite_id, IFBVec2&            scale_ref);
    const ifb_b8 sprite_get_transform_rotation       (const IFBIDSprite sprite_id, ifb_f32&            radians_ref);
    const ifb_b8 sprite_get_color_table_index        (const IFBIDSprite sprite_id, IFBColorTableIndex& color_table_index_ref);
    const ifb_b8 sprite_get_tag                      (const IFBIDSprite sprite_id, IFBTag&             tag_ref);

    const ifb_b8 sprite_update_transform             (const IFBIDSprite sprite_id, const IFBTransform&      transform_ref);
    const ifb_b8 sprite_update_transform_translation (const IFBIDSprite sprite_id, const IFBVec2&           translation_ref);
    const ifb_b8 sprite_update_transform_scale       (const IFBIDSprite sprite_id, const IFBVec2&           scale_ref);
    const ifb_b8 sprite_update_transform_rotation    (const IFBIDSprite sprite_id, const ifb_f32            radians);
    const ifb_b8 sprite_update_color_table_index     (const IFBIDSprite sprite_id, const IFBColorTableIndex color_table_index);
    const ifb_b8 sprite_update_tag                   (const IFBIDSprite sprite_id, const ifb_cstr           tag_value);

    const ifb_b8
    sprite_reserve(
        const ifb_u32             sprite_count,
        const ifb_cstr*           sprite_tag_value_array,
        const IFBColorTableIndex* sprite_color_table_index_array,
              IFBIDSprite*        sprite_id_array);

    const ifb_b8 sprite_release                      (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array);

    const ifb_b8 sprite_get                          (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBSprite*          sprite_array);
    const ifb_b8 sprite_get_transform                (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBTransform*       transform_array);
    const ifb_b8 sprite_get_transform_translation    (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBVec2*            translation_array);
    const ifb_b8 sprite_get_transform_scale          (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBVec2*            scale_array);
    const ifb_b8 sprite_get_transform_rotation       (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, ifb_f32*            radians_array);
    const ifb_b8 sprite_get_color_table_index        (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBColorTableIndex* color_table_index_array);
    const ifb_b8 sprite_get_tag                      (const ifb_u32 sprite_count, const IFBIDSprite* sprite_id_array, IFBTag*             tag_array);

    const ifb_b8 sprite_update_transform             (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const IFBTransform*       transform_array);
    const ifb_b8 sprite_update_transform_translation (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const IFBVec2*            translation_array);
    const ifb_b8 sprite_update_transform_scale       (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const IFBVec2*            scale_array);
    const ifb_b8 sprite_update_transform_rotation    (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const ifb_f32*            radians_array);
    const ifb_b8 sprite_update_color_table_index     (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const IFBColorTableIndex* color_table_index_array);
    const ifb_b8 sprite_update_tag                   (const ifb_u32 sprite_count, const IFBIDSprite sprite_id, const ifb_cstr*           tag_value_array);

    const ifb_b8
    sprite_encode_to_buffer(
        const ifb_u32      sprite_count,
        const IFBIDSprite* sprite_id_array,
        const ifb_u32      sprite_buffer_size,
        const ifb_u32      sprite_buffer_start,
        const ifb_u32      sprite_buffer_stride,
              ifb_memory   sprite_buffer);
};

#endif //IFB_ENGINE_INTERNAL_CORE_HPP