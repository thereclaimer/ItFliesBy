#pragma once

#include "itfliesby-engine-sprites.hpp"

internal ItfliesbyEngineSpriteId
itfliesby_engine_sprites_solid_create(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsPosition position,
    ItfliesbyRendererHandle        renderer,
    ItfliesbyRendererColorHex      color) {

    ItfliesbyEngineSpriteId new_solid_sprite = ITFLIESBY_ENGINE_SPRITE_ID_INVALID;
    ItfliesbyEngineSprite*  new_sprite = NULL;

    //find the next sprite
    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX;
        ++index) {

        if (!sprites->used_tables.solid_used[index]) {
            sprites->used_tables.solid_used[index] = true;
            new_solid_sprite = index;
            new_sprite = &sprites->sprite_tables.sprites_solid[index];
            sprites->solid_sprite_colors[index] = color;
            break;
        }
    }

    if (new_sprite == NULL) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    //create the physics transforms
    ItfliesbyEnginePhysicsId physics_id = 
        itfliesby_engine_physics_transforms_create(
            physics,     // physics
            {0.0f,0.0f}, // position
            {1.0f,1.0f}, // scale
            0.0f);       // rotation degrees

    if (physics_id == ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    new_sprite->physics_id = physics_id;

    //sanity check
    ITFLIESBY_ASSERT(
        new_solid_sprite >= 0 &&
        physics_id       >= 0);

    return(new_solid_sprite);
}

internal ItfliesbyEngineSprites
itfliesby_engine_sprites_create_and_init() {

    ItfliesbyEngineSprites sprites = {0};

    return(sprites);
}

internal ItfliesbyEngineSpriteId
itfliesby_engine_sprites_connor_test(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsPosition position,
    ItfliesbyRendererHandle        renderer) {

    ItfliesbyEngineSpriteId connor_sprite_id = ITFLIESBY_ENGINE_SPRITE_ID_INVALID;
    ItfliesbyEngineSprite*  connor_sprite    = NULL;

    //find the next sprite
    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX;
        ++index) {

        if (!sprites->used_tables.solid_used[index]) {
            connor_sprite_id = index;
            break;
        }
    }

    if (connor_sprite_id == ITFLIESBY_ENGINE_SPRITE_ID_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    //activate the new sprite        
    sprites->used_tables.solid_used[connor_sprite_id] = true;
    connor_sprite    = &sprites->sprite_tables.sprites_solid[connor_sprite_id];
    sprites->solid_sprite_colors[connor_sprite_id] = ITFLIESBY_ENGINE_SPRITE_COLOR_CONOR;

    //create the physics transforms
    ItfliesbyEnginePhysicsId physics_id = 
        itfliesby_engine_physics_transforms_create(
            physics,     // physics
            {0.0f,0.0f}, // position
            {1.0f,1.0f}, // scale
            0.0f);       // rotation degrees

    if (physics_id == ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    connor_sprite->physics_id = physics_id;

    //sanity check
    ITFLIESBY_ASSERT(
        connor_sprite_id >= 0 &&
        physics_id       >= 0);

    return(connor_sprite_id);
}
