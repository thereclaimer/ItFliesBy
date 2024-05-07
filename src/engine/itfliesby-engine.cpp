#pragma once

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-memory.cpp"
#include "itfliesby-engine-assets.cpp"
#include "itfliesby-engine-rendering.cpp"
#include "itfliesby-engine-physics.cpp"
#include "itfliesby-engine-sprites.cpp"
#include "itfliesby-engine-scene.cpp"

external ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               core_memory,
    u64                  core_memory_size_bytes) {

    ITFLIESBY_ASSERT(core_memory_size_bytes == ITFLIESBY_ENGINE_MEMORY_SIZE);

    platform_api = platform;

    //initialize engine memory
    itfliesby_engine_memory_create(
        core_memory,
        core_memory_size_bytes);

    //allocate our core engine structure
    ItfliesbyEngine* engine = itfliesby_engine_memory_allocate_core();

    //initialize assets
    itfliesby_engine_assets_init(&engine->assets);
    engine->renderer = itfliesby_engine_rendering_init(
        &engine->assets,
        &engine->shaders
    );

    engine->physics = itfliesby_engine_physics_create_and_init();
    engine->sprites = itfliesby_engine_sprites_create_and_init();
    
    //TEST QUAD RENDERING
    
    ItfliesbyEngineSpriteId test_sprite_0 = 
        itfliesby_engine_sprites_solid_create(
            &engine->sprites,
            &engine->physics,
            {0.0,0.0},
            engine->renderer,
            {235,219,178,255});

    //TEST QUAD RENDERING


    return(engine);
}

external void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine) {

}

internal void
itfliesby_engine_fetch_graphics_information(
    ItfliesbyEngine*                        engine,
    ItfliesbyEnginePhysicsTransformPayload* physics_payload) {

    ItfliesbyEngineSprites*     sprites     = &engine->sprites;
    ItfliesbyRendererHandle     renderer    = engine->renderer;
    ItfliesbyRendererSimpleQuad simple_quad = {0};

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX;
        ++index) {

        if (sprites->used_tables.solid_used[index]) {

            ItfliesbyEnginePhysicsTransform current_transform = physics_payload->transforms[index]; 
            ItfliesbyRendererColorHex       current_color     = sprites->solid_sprite_colors[index];
            
            itfliesby_math_mat3_transpose(&current_transform);

            simple_quad.color     = itfliesby_renderer_color_normalize(current_color);
            simple_quad.transform = current_transform; 

            itfliesby_renderer_simple_quad_push(
                renderer,
                simple_quad
            );
        }
    }

}

internal void
itfliesby_engine_test_render(
    ItfliesbyRendererHandle renderer,
    b8                      run) {

    if (!run) {
        return;
    }

    ItfliesbyRendererColorHex        color     = {0};
    ItfliesbyEnginePhysicsTransform  transform = itfliesby_math_mat3_identity();    

    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    itfliesby_math_mat3_transpose(&transform);
    
    ItfliesbyRendererSimpleQuad simple_quad = {0};
    simple_quad.transform = transform;
    simple_quad.color     = itfliesby_renderer_color_normalize(color);

    itfliesby_renderer_simple_quad_push(
        renderer,
        simple_quad
    );
}

external void
itfliesby_engine_update_and_render(
          ItfliesbyEngine*    engine,
    const ItfliesbyUserInput* user_input) {

    ItfliesbyEngineAssets*  assets   = &engine->assets;
    ItfliesbyRendererHandle renderer = engine->renderer;

    ItfliesbyEnginePhysicsTransformPayload physics_payload = {0};

    itfliesby_engine_physics_update(
        &engine->physics,
        &physics_payload
    );

    //now we need to zip up the payload we are sending to the GPU
    itfliesby_engine_fetch_graphics_information(
        engine,
        &physics_payload
    );

    itfliesby_engine_assets_update(assets);
    
    itfliesby_renderer_render(renderer);
}