#pragma once

#include "itfliesby-renderer.hpp"

external ItfliesbyRenderer*
itfliesby_renderer_api_create(
    ItfliesbyPlatformApi platform,
    memory               memory,
    u64                  memory_size) {

    ItfliesbyRenderer* renderer = 
        itfliesby_core_renderer_create(
            platform,
            memory,
            memory_size
    );

    return(renderer);
}

external void
itfliesby_renderer_api_destroy(
    ItfliesbyRenderer* renderer) {

    itfliesby_core_renderer_destroy(renderer);
}

external void
itfliesby_renderer_api_update_and_render(
    ItfliesbyRenderer* renderer) {

    itfliesby_core_renderer_update_and_render(renderer);
}

external void
itfliesby_renderer_api_shader_compile_vertex_shaders(
    ItfliesbyRenderer* renderer,
    const char*        shader_buffer,
    const u64*         shader_offsets,
    const u8           shader_count,
    u8*                shader_results) {

    ITFLIESBY_ASSERT(renderer);

    itfliesby_renderer_shader_compile_vertex_shaders(
        &renderer->shaders.shader_stage_store,
        shader_buffer,
        shader_offsets,
        shader_count,
        shader_results
    );
}

external void
itfliesby_renderer_api_shader_compile_fragment_shaders(
    ItfliesbyRenderer* renderer,
    const char*        shader_buffer,
    const u64*         shader_offsets,
    const u8           shader_count,
    u8*                shader_results) {

    ITFLIESBY_ASSERT(renderer);

    itfliesby_renderer_shader_compile_fragment_shaders(
        &renderer->shaders.shader_stage_store,
        shader_buffer,
        shader_offsets,
        shader_count,
        shader_results
    );
}

external void
itfliesby_renderer_api_shader_programs_create(
    ItfliesbyRenderer* renderer,
    const u8*          vertex_stages,
    const u8*          fragment_stages,
    u8                 count_programs,
    u8*                program_results) {

    ITFLIESBY_ASSERT(renderer);

    itfliesby_renderer_shader_programs_create(
        &renderer->shaders.shader_program_store,
        (const ItfliesbyRendererShaderStageStore*)&renderer->shaders.shader_stage_store,
        vertex_stages,
        fragment_stages,
        count_programs,
        program_results
    );
}