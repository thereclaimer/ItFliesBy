#ifndef ITFLIESBY_ENGINE_SPRITES_HPP
#define ITFLIESBY_ENGINE_SPRITES_HPP

#include "itfliesby-engine.hpp"
#include "itfliesby-engine-globals.hpp"

typedef s8 ItfliesbyEngineSpriteId;

#define ITFLIESBY_ENGINE_SPRITE_ID_INVALID -1



struct ItfliesbyEngineSprite {
    ItfliesbyEngineSpriteId    sprite_id;
    ItfliesbyEnginePhysicsId   physics_id;
    ItfliesbyRendererColorHex  color;
    ItfliesbyEngineAssetsImage texture;
};

#define ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX 64
#define ITFLIESBY_ENGINE_SPRITE_COUNT_MAX       128

struct ItfliesbyEngineSprites {
    b8                         sprite_used[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
    ItfliesbyRendererColorHex  sprite_colors[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
    ItfliesbyEngineAssetsImage sprite_textures[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
    ItfliesbyEnginePhysicsId   sprite_physics[ITFLIESBY_ENGINE_SPRITE_TABLE_COUNT_MAX];
};

#define ITFLIESBY_ENGINE_SPRITE_COLOR_CONOR {111,149,98 ,255}
#define ITFLIESBY_ENGINE_SPRITE_COLOR_NONE  {0  ,0  ,0  ,0  }

ItfliesbyEngineSpriteId
itfliesby_engine_sprites_connor_test(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsPosition position);

ItfliesbyEnginePhysicsId
itfliesby_engine_sprites_physics_id_get(
    ItfliesbyEngineSprites*        sprites,
    ItfliesbyEngineSpriteId        sprite_id);


#endif //ITFLIESBY_ENGINE_SPRITES_HPP