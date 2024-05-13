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

internal void
itfliesby_engine_sprites_active(
    const ItfliesbyEngineSprites*          sprites,
          ItfliesbyEngineSpriteCollection* sprite_collection) {

    *sprite_collection = {0};
    
    const b8* sprites_active = sprites->sprite_used;
    ItfliesbyEngineSpriteId* sprite_collection_ids = sprite_collection->sprite_ids;
    size_t sprite_collection_count = 0;

    for (
        u32 sprite_index = 0;
        sprite_index < ITFLIESBY_ENGINE_SPRITE_COUNT_MAX;
        ++sprite_index) {

        if (sprites_active[sprite_index]) {
            sprite_collection_ids[sprite_collection_count] = sprite_index;
            ++sprite_collection_count;
        }
    }
    
    sprite_collection->sprite_count = sprite_collection_count;
}

internal void
itfliesby_engine_sprites_physics(
    const ItfliesbyEngineSprites*           sprites,
    const ItfliesbyEngineSpriteCollection*  sprite_collection,
    ItfliesbyEnginePhysicsCollection*       physics_collection) {

    const ItfliesbyEnginePhysicsId* sprite_physics_ids          = sprites->sprite_physics;
    const ItfliesbyEnginePhysicsId* sprite_collection_ids       = sprite_collection->sprite_ids;
    const u32                       sprite_collection_ids_count = sprite_collection->sprite_count; 
    
    ItfliesbyEnginePhysicsId* physics_collection_ids      = physics_collection->physics_ids;
    ItfliesbyEngineSpriteId   current_sprite_id = 0;

    for (
        size_t sprite_collection_index = 0;
        sprite_collection_index < sprite_collection_ids_count;
        ++sprite_collection_index) {

        current_sprite_id = sprite_collection_ids[sprite_collection_index];

        physics_collection_ids[sprite_collection_index] = sprite_physics_ids[current_sprite_id];
    }

    physics_collection->physics_ids_count = sprite_collection_ids_count;
}

internal void
itfliesby_engine_sprite_textures(
    const ItfliesbyEngineSprites*                sprites,
    const ItfliesbyEngineSpriteCollection*       sprite_collection,
         ItfliesbyEngineSpriteTextureCollection* texture_collection) {

    const ItfliesbyEngineAssetsImage* sprites_asset_image = sprites->sprite_textures;
    const ItfliesbyRendererTextureId* sprites_texture_id  = sprites->renderer_textures;

    const ItfliesbyEnginePhysicsId* sprite_collection_ids       = sprite_collection->sprite_ids;
    const u32                       sprite_collection_ids_count = sprite_collection->sprite_count; 

    ItfliesbyEngineAssetsImage* texture_collection_assets   = texture_collection->textures;
    ItfliesbyRendererTextureId* texture_collection_textures = texture_collection->renderer_textures;

    ItfliesbyEngineSpriteId  current_sprite_id = 0;


    for (
        size_t sprite_collection_index = 0;
        sprite_collection_index < sprite_collection_ids_count;
        ++sprite_collection_index) {

        current_sprite_id = sprite_collection_ids[sprite_collection_index];
        texture_collection_assets[sprite_collection_index]   = sprites_asset_image[current_sprite_id];
        texture_collection_textures[sprite_collection_index] = sprites_texture_id[current_sprite_id];
    }
}

internal void
itfliesby_engine_sprite_colors(
    const ItfliesbyEngineSprites*                sprites,
    const ItfliesbyEngineSpriteCollection*       sprite_collection,
          ItfliesbyEngineSpriteColorCollection*  color_collection) {

    const ItfliesbyRendererColorHex* sprite_colors = sprites->sprite_colors;
    
    const ItfliesbyEnginePhysicsId* sprite_collection_ids       = sprite_collection->sprite_ids;
    const u32                       sprite_collection_ids_count = sprite_collection->sprite_count; 

    ItfliesbyEngineSpriteId  current_sprite_id = 0;

    ItfliesbyRendererColorHex* color_collection_colors = color_collection->colors;

    for (
        size_t sprite_collection_index = 0;
        sprite_collection_index < sprite_collection_ids_count;
        ++sprite_collection_index) {

        current_sprite_id = sprite_collection_ids[sprite_collection_index];
        color_collection_colors[sprite_collection_index] = sprite_colors[current_sprite_id];
    }
}

internal void
itfliesby_engine_sprites_transforms(
    const ItfliesbyEngineSprites*                   sprites,
    const ItfliesbyEnginePhysics*                   physics,
          ItfliesbyEngineSpriteRenderingContext*    sprite_rendering_context) {

    //get our active sprites
    ItfliesbyEngineSpriteCollection active_sprites = {0};
    itfliesby_engine_sprites_active(sprites,&active_sprites);

    //get our physics ids
    ItfliesbyEnginePhysicsCollection physics_collection = {0};
    itfliesby_engine_sprites_physics(
        sprites,
        &active_sprites,
        &physics_collection);

    //get the physics transforms
    ItfliesbyEnginePhysicsTransformCollection physics_transforms = {0};
    itfliesby_engine_physics_transforms(
        physics,
        &physics_collection,
        &physics_transforms);

    //get textures
    ItfliesbyEngineSpriteTextureCollection texture_collection = {0};
    itfliesby_engine_sprite_textures(
        sprites,
        &active_sprites,
        &texture_collection);

    //get colors
    ItfliesbyEngineSpriteColorCollection color_collection = {0};
    itfliesby_engine_sprite_colors(
        sprites,
        &active_sprites,
        &color_collection
    );

    //write our output
    sprite_rendering_context->count = active_sprites.sprite_count;
    memmove(
        sprite_rendering_context->sprite_ids,
        active_sprites.sprite_ids,
        sizeof(ItfliesbyEngineSpriteId) * active_sprites.sprite_count);
    memmove(
        sprite_rendering_context->transforms,
        physics_transforms.transforms,
        sizeof(ItfliesbyMathMat3) * active_sprites.sprite_count);
    memmove(
        sprite_rendering_context->renderer_texture,
        texture_collection.renderer_textures,
        sizeof(ItfliesbyRendererTextureId) & active_sprites.sprite_count);
    memmove(
        sprite_rendering_context->colors,
        color_collection.colors,
        sizeof(ItfliesbyRendererColorHex) & active_sprites.sprite_count);
}