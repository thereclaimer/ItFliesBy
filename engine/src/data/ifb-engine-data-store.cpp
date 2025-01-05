#pragma once

#include "ifb-engine-internal-data.hpp"

inline ifb_void
ifb_engine::data_store_initialize(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineMemory*    engine_memory_ptr,
    IFBEngineConfig*    engine_config_ptr) {

}

inline ifb_void
ifb_engine::data_store_commit_memory(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineDataQuery* data_query_ptr) {

}


inline ifb_void
ifb_engine::data_store_execute_query(
    IFBEngineDataStore* data_store_ptr,
    IFBEngineDataQuery* data_query_ptr) {

    IFBEngineDataQueryRequest& request = data_query_ptr->request;
    IFBEngineDataQueryResult&  result  = data_query_ptr->result;

    if (ifb_engine::data_query_request_has_properties_tag(request)) {
        if (ifb_engine::data_query_request_has_tag_char_buffer (request)) ifb_engine::data_query_result_add_tag_char_buffer (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_tag_hash_array  (request)) ifb_engine::data_query_result_add_tag_hash_array  (result, data_store_ptr);
    }
    
    if (ifb_engine::data_query_request_has_properties_arena(request)) {
        if (ifb_engine::data_query_request_has_arena_commit_id (request)) ifb_engine::data_query_result_add_arena_commit_id (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_arena_tag_id    (request)) ifb_engine::data_query_result_add_arena_tag_id    (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_arena_start     (request)) ifb_engine::data_query_result_add_arena_start     (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_arena_size      (request)) ifb_engine::data_query_result_add_arena_size      (result, data_store_ptr);
    }
    
    if (ifb_engine::data_query_request_has_properties_graphics(request)) {
        if (ifb_engine::data_query_request_has_graphics_window   (request)) ifb_engine::data_query_result_add_graphics_window   (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_graphics_viewport (request)) ifb_engine::data_query_result_add_graphics_viewport (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_graphics_monitors (request)) ifb_engine::data_query_result_add_graphics_monitors (result, data_store_ptr);
    }

    if (ifb_engine::data_query_request_has_properties_shader(request)) {
        if (ifb_engine::data_query_request_has_shader_arena_id               (request)) ifb_engine::data_query_result_add_shader_arena_id               (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_gl_shader_program_id   (request)) ifb_engine::data_query_result_add_shader_gl_shader_program_id   (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_gl_vertex_id           (request)) ifb_engine::data_query_result_add_shader_gl_vertex_id           (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_vertex_size            (request)) ifb_engine::data_query_result_add_shader_vertex_size            (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_vertex_buffer_start    (request)) ifb_engine::data_query_result_add_shader_vertex_buffer_start    (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_vertex_buffer_size     (request)) ifb_engine::data_query_result_add_shader_vertex_buffer_size     (result, data_store_ptr);
        if (ifb_engine::data_query_request_has_shader_vertex_buffer_position (request)) ifb_engine::data_query_result_add_shader_vertex_buffer_position (result, data_store_ptr);
    }

    if (ifb_engine::data_query_request_has_properties_transform(request)) {
        if (data_query_request_has_transform_translation (request)) ifb_engine::data_query_result_add_transform_translation (result, data_store_ptr);
        if (data_query_request_has_transform_scale       (request)) ifb_engine::data_query_result_add_transform_scale       (result, data_store_ptr);
        if (data_query_request_has_transform_rotation    (request)) ifb_engine::data_query_result_add_transform_rotation    (result, data_store_ptr);
        if (data_query_request_has_transform_flags       (request)) ifb_engine::data_query_result_add_transform_flags       (result, data_store_ptr);
    }

    if (ifb_engine::data_query_request_has_properties_sprite(request)) {
        if (data_query_request_has_sprite_tag_id            (request)) ifb_engine::data_query_result_add_sprite_tag_id            (result, data_store_ptr);
        if (data_query_request_has_sprite_transform_id      (request)) ifb_engine::data_query_result_add_sprite_transform_id      (result, data_store_ptr);
        if (data_query_request_has_sprite_color_table_index (request)) ifb_engine::data_query_result_add_sprite_color_table_index (result, data_store_ptr);
        if (data_query_request_has_sprite_flags             (request)) ifb_engine::data_query_result_add_sprite_flags             (result, data_store_ptr);
    }

}