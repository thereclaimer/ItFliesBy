#ifndef IFB_ENGINE_INTERNAL_MANAGERS_HPP
#define IFB_ENGINE_INTERNAL_MANAGERS_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//global handles
struct IFBGHNDEngineManagerTag       : IFBGHND { };
struct IFBGHNDEngineManagerArena     : IFBGHND { };
struct IFBGHNDEngineManagerGraphics  : IFBGHND { };
struct IFBGHNDEngineManagerShader    : IFBGHND { };
struct IFBGHNDEngineManagerTransform : IFBGHND { };
struct IFBGHNDEngineManagerSprite    : IFBGHND { };

struct IFBEngineManagerHandles {
    IFBGHNDEngineManagerTag       tag;
    IFBGHNDEngineManagerArena     arena;
    IFBGHNDEngineManagerGraphics  graphics;
    IFBGHNDEngineManagerShader    shader;
    IFBGHNDEngineManagerTransform transform;
    IFBGHNDEngineManagerSprite    sprite;
};

struct IFBEngineManagers {
    IFBEngineManagerHandles handles;
    IFBIDCommit             commit_id;
    ifb_address             commit_start;
};


//managers
struct IFBEngineManagerTag;
struct IFBEngineManagerArena;
struct IFBEngineManagerGraphics;
struct IFBEngineManagerShader;
struct IFBEngineManagerTransform;
struct IFBEngineManagerSprite;

//manager data
struct IFBEngineManagerDataTag;
struct IFBEngineManagerDataArena;
struct IFBEngineManagerDataGraphics;
struct IFBEngineManagerDataShader;
struct IFBEngineManagerDataTransform;
struct IFBEngineManagerDataSprite;

//queries
typedef ifb_enum IFBEngineManagerDataFlagsTag;
typedef ifb_enum IFBEngineManagerDataFlagsArena;
typedef ifb_enum IFBEngineManagerDataFlagsGraphics;
typedef ifb_enum IFBEngineManagerDataFlagsShader;
typedef ifb_enum IFBEngineManagerDataFlagsTransform;
typedef ifb_enum IFBEngineManagerDataFlagsSprite;

/**********************************************************************************/
/* MANAGER MEMORY                                                                   */
/**********************************************************************************/

struct IFBEngineManagerMemory {
    IFBIDCommit commit_id;
    ifb_address commit_start;
    struct {
        ifb_u16 arena_commit_id;
        ifb_u16 arena_tag_id;
        ifb_u16 arena_start;
        ifb_u16 arena_size;
        ifb_u16 graphics_window;
        ifb_u16 graphics_viewport;
        ifb_u16 graphics_monitors;
        ifb_u16 shader_arena_id;
        ifb_u16 shader_gl_shader_program_id;
        ifb_u16 shader_gl_vertex_id;
        ifb_u16 transform_translation;
        ifb_u16 transform_scale;
        ifb_u16 transform_rotation;
        ifb_u16 transform_flags;
        ifb_u16 sprite_tag_id;
        ifb_u16 sprite_transform_id;
        ifb_u16 sprite_color_table_index;
        ifb_u16 sprite_flags;
    } offsets;
};

/**********************************************************************************/
/* MANAGER DATA                                                                   */
/**********************************************************************************/

enum IFBEngineManagerDataTag_ {
    IFBEngineManagerDataTag_None           = 0,
    IFBEngineManagerDataTag_CharBuffer     = IFB_BIT_FLAG_0,
    IFBEngineManagerDataTag_HashArray      = IFB_BIT_FLAG_1,
    IFBEngineManagerDataTag_All            = 
        IFBEngineManagerDataTag_CharBuffer |
        IFBEngineManagerDataTag_HashArray
};

enum IFBEngineManagerDataArena_ {
    IFBEngineManagerDataArena_None           = 0,
    IFBEngineManagerDataArena_CommitId       = IFB_BIT_FLAG_0, 
    IFBEngineManagerDataArena_TagId          = IFB_BIT_FLAG_1,
    IFBEngineManagerDataArena_ArenaStart     = IFB_BIT_FLAG_2,
    IFBEngineManagerDataArena_ArenaSize      = IFB_BIT_FLAG_3,
    IFBEngineManagerDataArena_ArenaData      = 
        IFBEngineManagerDataArena_CommitId   |
        IFBEngineManagerDataArena_TagId      |
        IFBEngineManagerDataArena_ArenaStart |
        IFBEngineManagerDataArena_ArenaSize
};

enum IFBEngineManagerDataGraphics_ {
    IFBEngineManagerDataGraphics_None         = 0, 
    IFBEngineManagerDataGraphics_Window       = IFB_BIT_FLAG_0,
    IFBEngineManagerDataGraphics_Viewport     = IFB_BIT_FLAG_1,
    IFBEngineManagerDataGraphics_Monitors     = IFB_BIT_FLAG_2,
    IFBEngineManagerDataGraphics_GraphicsData = 
        IFBEngineManagerDataGraphics_Window   |
        IFBEngineManagerDataGraphics_Viewport |
        IFBEngineManagerDataGraphics_Monitors
};

enum IFBEngineManagerDataShader_ {
    IFBEngineManagerDataShader_None                  = 0,
    IFBEngineManagerDataShader_ArenaId               = IFB_BIT_FLAG_0,
    IFBEngineManagerDataShader_GLIDShaderProgram     = IFB_BIT_FLAG_1,
    IFBEngineManagerDataShader_GLIDVertex            = IFB_BIT_FLAG_2,
    IFBEngineManagerDataShader_ShaderData            = ,
        IFBEngineManagerDataShader_ArenaId           |
        IFBEngineManagerDataShader_GLIDShaderProgram |
        IFBEngineManagerDataShader_GLIDVertex
};

enum IFBEngineManagerDataTransform_ {
    IFBEngineManagerDataTransform_None           = 0,
    IFBEngineManagerDataTransform_Translation    = IFB_BIT_FLAG_0,
    IFBEngineManagerDataTransform_Scale          = IFB_BIT_FLAG_1,
    IFBEngineManagerDataTransform_Rotation       = IFB_BIT_FLAG_2,
    IFBEngineManagerDataTransform_Flags          = IFB_BIT_FLAG_3,
    IFBEngineManagerDataTransform_TransformData  =
       IFBEngineManagerDataTransform_Translation |
       IFBEngineManagerDataTransform_Scale       |
       IFBEngineManagerDataTransform_Rotation,
    IFBEngineManagerDataTransform_All            = 
       IFBEngineManagerDataTransform_Translation |
       IFBEngineManagerDataTransform_Scale       |
       IFBEngineManagerDataTransform_Rotation    |
       IFBEngineManagerDataTransform_Flags
};

enum IFBEngineManagerDataSprite_ {
    IFBEngineManagerDataSprite_None               = 0,
    IFBEngineManagerDataSprite_TagId              = IFB_BIT_FLAG_0,
    IFBEngineManagerDataSprite_TransformId        = IFB_BIT_FLAG_1,
    IFBEngineManagerDataSprite_ColorTableIndex    = IFB_BIT_FLAG_2,
    IFBEngineManagerDataSprite_Flags              = IFB_BIT_FLAG_3,
    IFBEngineManagerDataSprite_SpriteData         = 
       IFBEngineManagerDataSprite_TagId           |
       IFBEngineManagerDataSprite_TransformId     |
       IFBEngineManagerDataSprite_ColorTableIndex,
    IFBEngineManagerDataSprite_All                = 
       IFBEngineManagerDataSprite_TagId           |
       IFBEngineManagerDataSprite_TransformId     |
       IFBEngineManagerDataSprite_ColorTableIndex |
       IFBEngineManagerDataSprite_Flags
};

struct IFBEngineManagerDataTableTag {
    ifb_char* char_buffer;
    IFBHash*  hash_array;
};

struct IFBEngineManageraDataTableArena {
    IFBIDCommit* commit_id;
    IFBIDTag*    tag_id;
    ifb_address* start;
    ifb_u32*     size;
};

struct IFBEngineManagerDataTableGraphics {
    IFBWindow*     window;
    IFBGLViewport* viewport;
    IFBMonitor*    monitors;
};

struct IFBEngineManagerDataTableShader {
    IFBIDArena*           arena_id;
    IFBGLIDShaderProgram* gl_shader_program_id;
    IFBGLIDVertex*        gl_vertex_id;
};

struct IFBEngineManagerDataTableTransform {
    IFBVec2*  translation; 
    IFBVec2*  scale;
    ifb_f32*  rotation;
    ifb_byte* flags;
};

struct IFBEngineManagerDataTableSprite {
    IFBIDTag*           tag_id;
    IFBIDTransform*     transform_id;
    IFBColorTableIndex* color_table_index;
    ifb_byte*           flags;
};

struct IFBEngineManagerDataTables {
    IFBEngineManagerDataTableTag       tag;
    IFBEngineManagerDataTableArena     arena; 
    IFBEngineManagerDataTableGraphics  graphics; 
    IFBEngineManagerDataTableShader    shader; 
    IFBEngineManagerDataTableTransform transform; 
    IFBEngineManagerDataTableSprite    sprite; 
};

#define IFB_ENGINE_MANAGER_DATA_PROPERTIES_COUNT (sizeof(IFBEngineManagerDataTables) / sizeof(ifb_ptr))

struct IFBEngineManagerDataQuery {
    ifb_u32 data_request_count;
    struct {
        IFBEngineManagerDataFlagsTag       tag;
        IFBEngineManagerDataFlagsArena     arena;
        IFBEngineManagerDataFlagsGraphics  graphics;
        IFBEngineManagerDataFlagsShader    shader;
        IFBEngineManagerDataFlagsTransform transform;
        IFBEngineManagerDataFlagsSprite    sprite;
    } data_flags;
    ifb_ptr data_pointers[IFB_ENGINE_MANAGER_DATA_PROPERTIES_COUNT];
};

namespace ifb_engine {

    ifb_void manager_data_query_execute();

    ifb_void manger_data_query_add_tag_char_buffer             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_tag_hash_array              (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_arena_commit_id             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_arena_tag_id                (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_arena_start                 (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_arena_size                  (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_graphics_window             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_graphics_viewport           (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_graphics_monitors           (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_shader_arena_id             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_shader_gl_shader_program_id (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_shader_gl_vertex_id         (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_transform_translation       (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_transform_scale             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_transform_rotation          (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_transform_flags             (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_sprite_tag_id               (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_sprite_transform_id         (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_sprite_color_table_index    (IFBEngineManagerDataQuery& data_query_ref);
    ifb_void manger_data_query_add_sprite_flags                (IFBEngineManagerDataQuery& data_query_ref);

};

/**********************************************************************************/
/* TAG MANAGER                                                                    */
/**********************************************************************************/

struct IFBEngineManagerTag {
    ifb_address memory_start;
    ifb_u16     offset_char_buffer;
    ifb_u16     offset_hash_array;
    ifb_u16     tag_c_str_length;
    ifb_u16     tag_count_max;
};

namespace ifb_engine {

    const IFBIDTag  tag_manager_reserve_tag      (const IFBEngineManagerTag* tag_manager_ptr, const ifb_cstr  tag_c_str);
          ifb_void  tag_manager_release_tag      (const IFBEngineManagerTag* tag_manager_ptr, const IFBIDTag& tag_id_ref);
    const ifb_cstr  tag_manager_get_tag_c_str    (const IFBEngineManagerTag* tag_manager_ptr, const IFBIDTag& tag_id_ref);
    const IFBHash   tag_manager_get_hash         (const IFBEngineManagerTag* tag_manager_ptr, const IFBIDTag& tag_id_ref);
};

/**********************************************************************************/
/* ARENA MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineManagerArena {
    ifb_address start;
    ifb_u16     offset_commit_id_array;
    ifb_u16     offset_tag_id_array;
    ifb_u16     offset_arena_start;
    ifb_u16     offset_arena_size;
    ifb_u16     arena_minimum_size;
    ifb_u16     arena_minimum_pages;
    ifb_u16     arena_count_max;
    ifb_u16     arena_count_committed;
};

namespace ifb_engine {

    const IFBIDArena 
    arena_manager_commit_arena(
              IFBEngineManagerArena* arena_manager_ptr, 
              IFBEngineMemory*       memory_ptr,
        const IFBIDTag               arena_tag_id,
        const ifb_u32                arena_commit_size_minimum);

    const ifb_u32      arena_manager_align_size_to_arena (const IFBEngineManagerArena* arena_manager_ptr, const ifb_u32 size);
    const IFBIDCommit  arena_manager_get_arena_commit_id (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id);
    const IFBIDTag     arena_manager_get_arena_tag_id    (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_u32      arena_manager_get_arena_size      (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_address  arena_manager_get_arena_start     (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_ptr      arena_manager_get_arena_pointer   (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id);
    const ifb_ptr      arena_manager_get_arena_pointer   (const IFBEngineManagerArena* arena_manager_ptr, const IFBIDArena arena_id, const ifb_u32 offset);
};

/**********************************************************************************/
/* GRAPHICS MANAGER                                                               */
/**********************************************************************************/

struct IFBEngineManagerGraphics {
    ifb_address memory_start;
    ifb_u16     offset_window;
    ifb_u16     offset_viewport;
    ifb_u16     offset_monitor_array;
    ifb_u16     monitor_count;
    ifb_u16     monitor_primary_index;
};

namespace ifb_engine {

    ifb_void 
    graphics_manager_create_window (
              IFBEngineManagerGraphics* graphics_manager_ptr,
        const ifb_cstr                  window_title,
        const IFBWindowFlags            window_flags);

    ifb_void graphics_manager_create_viewport (IFBEngineManagerGraphics* graphics_manager_ptr);
    ifb_void graphics_manager_style_imgui     (IFBEngineManagerGraphics* graphics_manager_ptr);
    ifb_void graphics_manager_frame_start     (IFBEngineManagerGraphics* graphics_manager_ptr);
    ifb_void graphics_manager_frame_render    (IFBEngineManagerGraphics* graphics_manager_ptr);

    const ifb_u32     grahpics_manager_find_primary_monitor_index (const IFBMonitor* monitor_array_ptr);
    const IFBMonitor* graphics_manager_get_monitor                (const IFBEngineManagerGraphics* graphics_manager_ptr, const ifb_u32 monitor_index);
};

/**********************************************************************************/
/* SHADER MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineManagerShader {
    ifb_address memory_start;
    ifb_u16     offset_arena_id;
    ifb_u16     offset_gl_program_id;
    ifb_u16     offset_gl_vertex_id;
    ifb_u16     shader_count_total;
    ifb_u16     shader_count_committed;
};

namespace ifb_engine { 

    ifb_void 
    shader_manager_commit_shaders(
              IFBEngineManagerShader* shader_manager_ptr,
        const ifb_u32                 shader_count,
        const IFBIDArena*             shader_arena_id_array,
        const IFBGLIDShaderProgram*   shader_gl_program_id_array,
        const IFBGLIDVertex*          shader_gl_vertex_id_array,
              IFBIDShader*            shader_ids_committed);

    ifb_void shader_manager_get_arena_ids      (const IFBEngineManagerShader* shader_manager_ptr, const ifb_u32 shader_id_count, const IFBIDShader* shader_ids, IFBIDArena*           shader_arena_id_array);
    ifb_void shader_manager_get_gl_program_ids (const IFBEngineManagerShader* shader_manager_ptr, const ifb_u32 shader_id_count, const IFBIDShader* shader_ids, IFBGLIDShaderProgram* shader_gl_program_array);
    ifb_void shader_manager_get_gl_vertex_ids  (const IFBEngineManagerShader* shader_manager_ptr, const ifb_u32 shader_id_count, const IFBIDShader* shader_ids, IFBGLIDVertex*        shader_gl_vertex_array);
    ifb_void shader_manager_get_shaders        (const IFBEngineManagerShader* shader_manager_ptr, const ifb_u32 shader_id_count, const IFBIDShader* shader_ids, IFBShader*            shader_array)
};

/**********************************************************************************/
/* TRANSFORM MANAGER                                                              */
/**********************************************************************************/

struct IFBEngineManagerTransform {
    ifb_address memory_start;
    ifb_u16     offset_array_translation;
    ifb_u16     offset_array_scale;
    ifb_u16     offset_array_rotation_radians;
    ifb_u16     offset_array_flags;
    ifb_u16     transform_count_max;
    ifb_u16     transform_flag_group_count;
};

namespace ifb_engine {

    ifb_void transform_manager_reserve_transforms (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count,       IFBIDTransform* transform_ids);
    ifb_void transform_manager_release_transforms (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count, const IFBIDTransform* transform_ids);
    ifb_void transform_manager_update_translation (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count, const IFBIDTransform* transform_ids, const IFBVec2*      transform_translations);
    ifb_void transform_manager_update_scale       (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count, const IFBIDTransform* transform_ids, const IFBVec2*      transform_scales);
    ifb_void transform_manager_update_rotation    (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count, const IFBIDTransform* transform_ids, const ifb_f32*      transform_radians);
    ifb_void transform_manager_get_transforms     (const IFBEngineManagerTransform* transform_manager_ptr, const ifb_u32 transform_count, const IFBIDTransform* transform_ids,       IFBTransform* transforms);
};

/**********************************************************************************/
/* SPRITE MANAGER                                                                 */
/**********************************************************************************/

struct IFBEngineManagerSprite {
    ifb_address memory_start;
    ifb_u16     offset_array_tag_id;
    ifb_u16     offset_array_transform_id;
    ifb_u16     offset_array_color_table_index;
    ifb_u16     offset_array_flags;
    ifb_u16     sprite_count_max;
    ifb_u16     flag_group_count;
};

namespace ifb_engine {

    ifb_void
    sprite_manager_reserve_sprites(
              IFBEngineManagerSprite* sprite_manager_ptr,
        const ifb_u32                 sprite_count,
        const IFBIDTag*               sprite_tag_ids,
        const IFBIDTransform*         sprite_transform_ids,
        const IFBColorTableIndex*     sprite_color_table_indexes,
              IFBIDSprite*            sprite_ids);

    ifb_void
    sprite_manager_release_sprites(
              IFBEngineManagerSprite* sprite_manager_ptr,
        const ifb_u32                 sprite_count,
        const IFBIDSprite*            sprite_ids);

    ifb_void
    sprite_manager_get_sprites(
              IFBEngineManagerSprite* sprite_manager_ptr,
        const ifb_u32                 sprite_count,
        const IFBIDSprite*            sprite_ids,
              IFBSprite*              sprites);
};

/**********************************************************************************/
/* MANAGERS                                                                       */
/**********************************************************************************/

namespace ifb_engine {

    ifb_void 
    managers_initialize(
        IFBEngineManagers* managers_ptr,
        IFBEngineMemory*   engine_memory_ptr,
        IFBEngineConfig*   engine_config);

    IFBEngineManagerTag*       managers_get_manager_tag       (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    IFBEngineManagerArena*     managers_get_manager_arena     (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    IFBEngineManagerGraphics*  managers_get_manager_graphics  (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    IFBEngineManagerShader*    managers_get_manager_shader    (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    IFBEngineManagerTransform* managers_get_manager_transform (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    IFBEngineManagerSprite*    managers_get_manager_sprite    (const IFBEngineManagerHandles* manager_handles_ptr, const IFBEngineMemory* engine_memory_ptr);
    
    const ifb_u32 managers_calculate_size_and_offsets_tag       (IFBEngineManagerTag*       tag_manager_ptr);
    const ifb_u32 managers_calculate_size_and_offsets_arena     (IFBEngineManagerArena*     arena_manager_ptr);
    const ifb_u32 managers_calculate_size_and_offsets_graphics  (IFBEngineManagerGraphics*  graphics_manager_ptr);
    const ifb_u32 managers_calculate_size_and_offsets_shader    (IFBEngineManagerShader*    shader_manager_ptr);
    const ifb_u32 managers_calculate_size_and_offsets_transform (IFBEngineManagerTransform* transform_manager_ptr);
    const ifb_u32 managers_calculate_size_and_offsets_sprite    (IFBEngineManagerSprite*    sprite_manager_ptr);

};

#endif //IFB_ENGINE_INTERNAL_MANAGERS_HPP  