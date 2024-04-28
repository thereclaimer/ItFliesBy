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

    //find the next physics id
    ItfliesbyEnginePhysicsId physics_id = itfliesby_engine_physics_id_get_next(physics);
    if (physics_id == ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }
    itfliesby_engine_physics_update_position(physics, physics_id, position);
    

    //find the next renderer id
    ItfliesbyQuadId render_quad_id = 
        itfliesby_renderer_quad_solid_quads_create_instance(
            renderer,
            color);
    //TODO: error code
    if (render_quad_id == -1) {
        return(ITFLIESBY_ENGINE_SPRITE_ID_INVALID);
    }


    new_sprite->physics_id     = physics_id;
    new_sprite->render_quad_id = render_quad_id;

    //sanity check
    ITFLIESBY_ASSERT(
        new_solid_sprite >= 0 &&
        physics_id >= 0 &&
        render_quad_id >= 0
    );

    return(new_solid_sprite);
}

internal ItfliesbyEngineSprites
itfliesby_engine_sprites_create_and_init() {

    ItfliesbyEngineSprites sprites = {0};

    return(sprites);
}