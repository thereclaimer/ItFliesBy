#pragma once

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-memory.cpp"
#include "itfliesby-engine-assets.cpp"
#include "itfliesby-engine-rendering.cpp"
#include "itfliesby-engine-physics.cpp"
#include "itfliesby-engine-sprites.cpp"

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

    ItfliesbyRendererSolidQuadUpdateBatch solid_quad_update_batch = {0};
    u8 solid_quad_count = 0;

    ItfliesbyEngineSprites* sprites = &engine->sprites;

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX;
        ++index) {

        if (sprites->used_tables.solid_used[index]) {

            ItfliesbyEnginePhysicsTransform current_transform = physics_payload->transforms[index]; 
            ItfliesbyRendererColorHex       current_color     = sprites->solid_sprite_colors[index];

            memmove(
                &solid_quad_update_batch.batch[solid_quad_count].transform[0],
                &current_transform.m[0],
                sizeof(f32) * 9
            );
            solid_quad_update_batch.batch[solid_quad_count].color     = current_color;
            ++solid_quad_count;
        }
    }

    solid_quad_update_batch.count = solid_quad_count;

    itfliesby_renderer_quad_solid_quads_batch_update(
        engine->renderer,
        &solid_quad_update_batch
    );
}

external void
itfliesby_engine_update_and_render(
    ItfliesbyEngine* engine) {

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