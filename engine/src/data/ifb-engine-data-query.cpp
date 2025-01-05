#pragma once

#include "ifb-engine-internal-data.hpp"

/**********************************************************************************/
/* REQUEST ADD PROPERTY                                                           */
/**********************************************************************************/

//tag
inline ifb_void ifb_engine::data_query_request_add_tag_char_buffer               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.tag       |= IFBEngineDataPropertiesTag_CharBuffer;              ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_tag_hash_array                (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.tag       |= IFBEngineDataPropertiesTag_HashArray;               ++data_query_ptr->result.property_count; }

//arena
inline ifb_void ifb_engine::data_query_request_add_arena_commit_id               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.arena     |= IFBEngineDataPropertiesArena_CommitId;              ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_arena_tag_id                  (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.arena     |= IFBEngineDataPropertiesArena_TagId;                 ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_arena_start                   (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.arena     |= IFBEngineDataPropertiesArena_ArenaStart;            ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_arena_size                    (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.arena     |= IFBEngineDataPropertiesArena_ArenaSize;             ++data_query_ptr->result.property_count; }

//graphics
inline ifb_void ifb_engine::data_query_request_add_graphics_window               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.graphics  |= IFBEngineDataPropertiesGraphics_Window;             ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_graphics_viewport             (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.graphics  |= IFBEngineDataPropertiesGraphics_Viewport;           ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_graphics_monitors             (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.graphics  |= IFBEngineDataPropertiesGraphics_Monitors;           ++data_query_ptr->result.property_count; }

//shader
inline ifb_void ifb_engine::data_query_request_add_shader_arena_id               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_ArenaId;              ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_gl_shader_program_id   (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_GLIDShaderProgram;    ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_gl_vertex_id           (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_GLIDVertex;           ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_vertex_size            (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_VertexSize;           ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_vertex_buffer_start    (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_VertexBufferStart;    ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_vertex_buffer_size     (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_VertexBufferSize;     ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_shader_vertex_buffer_position (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.shader    |= IFBEngineDataPropertiesShader_VertexBufferPosition; ++data_query_ptr->result.property_count; }

//transform
inline ifb_void ifb_engine::data_query_request_add_transform_translation         (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.transform |= IFBEngineDataPropertiesTransform_Translation;       ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_transform_scale               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.transform |= IFBEngineDataPropertiesTransform_Scale;             ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_transform_rotation            (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.transform |= IFBEngineDataPropertiesTransform_Rotation;          ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_transform_flags               (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.transform |= IFBEngineDataPropertiesTransform_Flags;             ++data_query_ptr->result.property_count; }

//sprite
inline ifb_void ifb_engine::data_query_request_add_sprite_tag_id                 (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.sprite    |= IFBEngineDataPropertiesSprite_TagId;                ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_sprite_transform_id           (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.sprite    |= IFBEngineDataPropertiesSprite_TransformId;          ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_sprite_color_table_index      (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.sprite    |= IFBEngineDataPropertiesSprite_ColorTableIndex;      ++data_query_ptr->result.property_count; }
inline ifb_void ifb_engine::data_query_request_add_sprite_flags                  (IFBEngineDataQueryRequest& data_query_request_ref) { data_query_request_ref.property_flags.sprite    |= IFBEngineDataPropertiesSprite_Flags;                ++data_query_ptr->result.property_count; }


/**********************************************************************************/
/* REQUEST HAS PROPERTY                                                           */
/**********************************************************************************/

//property types
inline const ifb_b8 ifb_engine::data_query_request_has_properties_tag                (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.tag       != IFBEngineDataPropertiesTag_None));       }
inline const ifb_b8 ifb_engine::data_query_request_has_properties_arena              (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.arena     != IFBEngineDataPropertiesArena_None));     }
inline const ifb_b8 ifb_engine::data_query_request_has_properties_graphics           (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.graphics  != IFBEngineDataPropertiesGraphics_None));  }
inline const ifb_b8 ifb_engine::data_query_request_has_properties_shader             (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.shader    != IFBEngineDataPropertiesShader_None));    }
inline const ifb_b8 ifb_engine::data_query_request_has_properties_transform          (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.transform != IFBEngineDataPropertiesTransform_None)); }
inline const ifb_b8 ifb_engine::data_query_request_has_properties_sprite             (const IFBEngineDataQueryRequest& data_query_request_ref) { return((data_query_request_ref.property_flags.sprite    != IFBEngineDataPropertiesSprite_None));    }

//tag
inline const ifb_b8 ifb_engine::data_query_request_has_tag_char_buffer               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.tag       & IFBEngineDataPropertiesTag_CharBuffer;);              }
inline const ifb_b8 ifb_engine::data_query_request_has_tag_hash_array                (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.tag       & IFBEngineDataPropertiesTag_HashArray;);               }

//arena
inline const ifb_b8 ifb_engine::data_query_request_has_arena_commit_id               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.arena     & IFBEngineDataPropertiesArena_CommitId;);              }
inline const ifb_b8 ifb_engine::data_query_request_has_arena_tag_id                  (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.arena     & IFBEngineDataPropertiesArena_TagId;);                 }
inline const ifb_b8 ifb_engine::data_query_request_has_arena_start                   (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.arena     & IFBEngineDataPropertiesArena_ArenaStart;);            }
inline const ifb_b8 ifb_engine::data_query_request_has_arena_size                    (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.arena     & IFBEngineDataPropertiesArena_ArenaSize;);             }

//graphics
inline const ifb_b8 ifb_engine::data_query_request_has_graphics_window               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.graphics  & IFBEngineDataPropertiesGraphics_Window;);             }
inline const ifb_b8 ifb_engine::data_query_request_has_graphics_viewport             (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.graphics  & IFBEngineDataPropertiesGraphics_Viewport;);           }
inline const ifb_b8 ifb_engine::data_query_request_has_graphics_monitors             (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.graphics  & IFBEngineDataPropertiesGraphics_Monitors;);           }

//shader
inline const ifb_b8 ifb_engine::data_query_request_has_shader_arena_id               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_ArenaId;);              }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_gl_shader_program_id   (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_GLIDShaderProgram;);    }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_gl_vertex_id           (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_GLIDVertex;);           }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_vertex_size            (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_VertexSize;);           }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_vertex_buffer_start    (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_VertexBufferStart;);    }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_vertex_buffer_size     (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_VertexBufferSize;);     }
inline const ifb_b8 ifb_engine::data_query_request_has_shader_vertex_buffer_position (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.shader    & IFBEngineDataPropertiesShader_VertexBufferPosition;); }

//transform
inline const ifb_b8 ifb_engine::data_query_request_has_transform_translation         (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.transform & IFBEngineDataPropertiesTransform_Translation;);       }
inline const ifb_b8 ifb_engine::data_query_request_has_transform_scale               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.transform & IFBEngineDataPropertiesTransform_Scale;);             }
inline const ifb_b8 ifb_engine::data_query_request_has_transform_rotation            (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.transform & IFBEngineDataPropertiesTransform_Rotation;);          }
inline const ifb_b8 ifb_engine::data_query_request_has_transform_flags               (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.transform & IFBEngineDataPropertiesTransform_Flags;);             }

//sprite
inline const ifb_b8 ifb_engine::data_query_request_has_sprite_tag_id                 (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.sprite    & IFBEngineDataPropertiesSprite_TagId;);                }
inline const ifb_b8 ifb_engine::data_query_request_has_sprite_transform_id           (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.sprite    & IFBEngineDataPropertiesSprite_TransformId;);          }
inline const ifb_b8 ifb_engine::data_query_request_has_sprite_color_table_index      (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.sprite    & IFBEngineDataPropertiesSprite_ColorTableIndex;);      }
inline const ifb_b8 ifb_engine::data_query_request_has_sprite_flags                  (const IFBEngineDataQueryRequest& data_query_request_ref) { return(data_query_request_ref.property_flags.sprite    & IFBEngineDataPropertiesSprite_Flags;);                }

/**********************************************************************************/
/* RESPONSE ADD PROPERTY                                                          */
/**********************************************************************************/

//tag
inline const ifb_b8 data_query_result_add_tag_char_buffer                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_tag_char_buffer                (data_store_ptr->memory, data_store_ptr->offsets.tag);       ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_tag_hash_array                 (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_tag_hash_array                 (data_store_ptr->memory, data_store_ptr->offsets.tag);       ++data_query_result_ref.property_count; }

//arena
inline const ifb_b8 data_query_result_add_arena_commit_id                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_arena_commit_id                (data_store_ptr->memory, data_store_ptr->offsets.arena);     ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_arena_tag_id                   (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_arena_tag_id                   (data_store_ptr->memory, data_store_ptr->offsets.arena);     ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_arena_start                    (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_arena_start                    (data_store_ptr->memory, data_store_ptr->offsets.arena);     ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_arena_size                     (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_arena_size                     (data_store_ptr->memory, data_store_ptr->offsets.arena);     ++data_query_result_ref.property_count; }

//graphics
inline const ifb_b8 data_query_result_add_graphics_window                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_graphics_window                (data_store_ptr->memory, data_store_ptr->offsets.graphics);  ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_graphics_viewport              (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_graphics_viewport              (data_store_ptr->memory, data_store_ptr->offsets.graphics);  ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_graphics_monitors              (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_graphics_monitors              (data_store_ptr->memory, data_store_ptr->offsets.graphics);  ++data_query_result_ref.property_count; }

//shader
inline const ifb_b8 data_query_result_add_shader_arena_id                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_arena_id                (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_gl_shader_program_id    (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_gl_shader_program_id    (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_gl_vertex_id            (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_gl_vertex_id            (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_vertex_size             (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_vertex_size             (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_vertex_buffer_start     (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_vertex_buffer_start     (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_vertex_buffer_size      (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_vertex_buffer_size      (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_shader_vertex_buffer_position  (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_shader_vertex_buffer_position  (data_store_ptr->memory, data_store_ptr->offsets.shader);    ++data_query_result_ref.property_count; }

//transform
inline const ifb_b8 data_query_result_add_transform_translation          (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_transform_translation          (data_store_ptr->memory, data_store_ptr->offsets.transform); ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_transform_scale                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_transform_scale                (data_store_ptr->memory, data_store_ptr->offsets.transform); ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_transform_rotation             (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_transform_rotation             (data_store_ptr->memory, data_store_ptr->offsets.transform); ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_transform_flags                (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_transform_flags                (data_store_ptr->memory, data_store_ptr->offsets.transform); ++data_query_result_ref.property_count; }

//sprite
inline const ifb_b8 data_query_result_add_sprite_tag_id                  (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_sprite_tag_id                  (data_store_ptr->memory, data_store_ptr->offsets.sprite);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_sprite_transform_id            (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_sprite_transform_id            (data_store_ptr->memory, data_store_ptr->offsets.sprite);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_sprite_color_table_index       (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_sprite_color_table_index       (data_store_ptr->memory, data_store_ptr->offsets.sprite);    ++data_query_result_ref.property_count; }
inline const ifb_b8 data_query_result_add_sprite_flags                   (const IFBEngineDataQueryResult& data_query_result_ref, const IFBEngineDataStore* data_store_ptr) { data_query_result_ref.properties[data_query_result_ref.property_count] = (ifb_ptr)ifb_engine::data_memory_get_pointer_sprite_flags                   (data_store_ptr->memory, data_store_ptr->offsets.sprite);    ++data_query_result_ref.property_count; }