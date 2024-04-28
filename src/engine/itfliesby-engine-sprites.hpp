#ifndef ITFLIESBY_ENGINE_SPRITES_HPP
#define ITFLIESBY_ENGINE_SPRITES_HPP

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"

#define ITFLIESBY_ENGINE_SPRITE_ID_INVALID -1

typedef s8 ItfliesbyEngineSpriteId;

struct ItfliesbyEngineSprite {
    ItfliesbyQuadId          render_quad_id;
    ItfliesbyEnginePhysicsId physics_id;
};

#define ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX 64
#define ITFLIESBY_ENGINE_SPRITE_COUNT_MAX       128

struct ItfliesbyEngineSprites {

    union {
        struct {
            b8 solid_used[ITFLIESBY_ENGINE_SPRITE_COUNT_MAX];
            b8 textured_used[ITFLIESBY_ENGINE_SPRITE_COUNT_MAX];
        } used_tables;
        b8 all_used[ITFLIESBY_ENGINE_SPRITE_COUNT_MAX];
    };

    union {
        struct {
            ItfliesbyEngineSprite sprites_solid[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
            ItfliesbyEngineSprite sprites_textured[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
        } sprite_tables;
        ItfliesbyEngineSprite all_sprites[ITFLIESBY_ENGINE_SPRITE_COUNT_MAX];
    };

    ItfliesbyRendererColorHex solid_sprite_colors[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
};

#endif //ITFLIESBY_ENGINE_SPRITES_HPP