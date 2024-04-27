#pragma once

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-memory.cpp"
#include "itfliesby-engine-assets.cpp"
#include "itfliesby-engine-rendering.cpp"
#include "itfliesby-engine-physics.cpp"

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

    //TEST QUAD RENDERING
    
    ItfliesbyQuadId quad_id_0 = itfliesby_renderer_quad_solid_quads_create_instance(engine->renderer,{235,219,178,255});
    ItfliesbyQuadId quad_id_1 = itfliesby_renderer_quad_solid_quads_create_instance(engine->renderer,{235,219,178,255});
    ItfliesbyQuadId quad_id_2 = itfliesby_renderer_quad_solid_quads_create_instance(engine->renderer,{235,219,178,255});
    
    //TEST QUAD RENDERING


    return(engine);
}

external void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine) {

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

    itfliesby_engine_assets_update(assets);
    itfliesby_renderer_update_and_render(renderer);
}