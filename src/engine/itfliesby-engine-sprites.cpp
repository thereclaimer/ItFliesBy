#pragma once

#include "itfliesby-engine-sprites.hpp"
#include "itfliesby-engine-rendering.cpp"

internal ItfliesbyEngineSpriteId
itfliesby_engine_sprites_create(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsPosition position,
    ItfliesbyRendererHandle        renderer,
    ItfliesbyRendererColorHex      color) {

    ItfliesbyEngineSpriteId new_sprite = ITFLIESBY_ENGINE_SPRITE_ID_INVALID;

    //find the next sprite
    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_COUNT_MAX;
        ++index) {

        if (!sprites->sprite_used[index]) {
            new_sprite = index;
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

    //activate the new sprite        
    sprites->sprite_used[new_sprite]    = true;
    sprites->sprite_colors[new_sprite]  = color;
    sprites->sprite_physics[new_sprite] = physics_id;
    

    //sanity check
    ITFLIESBY_ASSERT(
        new_sprite       >= 0 &&
        physics_id       >= 0);

    return(new_sprite);
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
    ItfliesbyEngineAssets*         assets,
    ItfliesbyRendererHandle        renderer) {

    ItfliesbyEngineSpriteId connor_sprite_id = ITFLIESBY_ENGINE_SPRITE_ID_INVALID;
    ItfliesbyEngineSprite*  connor_sprite    = NULL;

    //find the next sprite
    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_SPRITE_COUNT_MAX;
        ++index) {

        if (!sprites->sprite_used[index]) {
            connor_sprite_id = index;
            break;
        }
    }

    if (connor_sprite_id == ITFLIESBY_ENGINE_SPRITE_ID_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    //create the physics transforms
    ItfliesbyEnginePhysicsId physics_id = 
        itfliesby_engine_physics_transforms_create(
            physics,       // physics
            position,      // position
            {0.25f,0.25f}, // scale
            0.0f);         // rotation degrees

    if (physics_id == ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }

    //send the sprite to the renderer
    ItfliesbyRendererTextureId texture_id = 
        itfliesby_engine_rendering_push_texture_sprite_character(
            renderer,
            ITFLIESBY_ENGINE_ASSETS_IMAGE_CALIBRATION_CONNOR,
            assets);

    //activate the new sprite        
    sprites->sprite_used[connor_sprite_id]       = true;
    sprites->sprite_colors[connor_sprite_id]     = ITFLIESBY_ENGINE_SPRITE_COLOR_CONOR;
    sprites->sprite_physics[connor_sprite_id]    = physics_id;
    sprites->sprite_textures[connor_sprite_id]   = ITFLIESBY_ENGINE_ASSETS_IMAGE_CALIBRATION_CONNOR;
    sprites->renderer_textures[connor_sprite_id] = texture_id; 

    //sanity check
    ITFLIESBY_ASSERT(
        connor_sprite_id >= 0 &&
        physics_id       >= 0);

    return(connor_sprite_id);
}


internal ItfliesbyEnginePhysicsId
itfliesby_engine_sprites_physics_id_get(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEngineSpriteId        sprite_id) {

    ItfliesbyEnginePhysicsId physics_id = sprites->sprite_physics[sprite_id];

    return(physics_id);
}

ItfliesbyEngineSprite
itfliesby_engine_sprites_get(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEngineSpriteId        sprite_id) {

    ItfliesbyEngineSprite sprite = {0};

    sprite.sprite_id        = sprite_id;
    sprite.color            = sprites->sprite_colors[sprite_id];
    sprite.physics_id       = sprites->sprite_physics[sprite_id];
    sprite.texture          = sprites->sprite_textures[sprite_id];
    sprite.renderer_texture = sprites->renderer_textures[sprite_id]; 

    return(sprite);
}