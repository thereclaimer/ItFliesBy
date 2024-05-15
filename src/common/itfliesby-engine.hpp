#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include "itfliesby-types.hpp"

typedef void             ItfliesbyEngine;
typedef ItfliesbyEngine* ItfliesbyEngineHandle;

//----------------------------------------------------------------
// ENGINE
//----------------------------------------------------------------

api ItfliesbyEngineHandle
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size);

api void
itfliesby_engine_destroy(
    ItfliesbyEngineHandle engine);

api void
itfliesby_engine_render_scene(
          ItfliesbyEngineHandle engine,
          ItfliesbyUserInput*   user_input,
    const u64                   delta_time_ticks,
    const f32                   window_width,
    const f32                   window_height,
    const f32                   screen_width,
    const f32                   screen_height);

//----------------------------------------------------------------
// SPRITES
//----------------------------------------------------------------

typedef s8 ItfliesbyEngineSpriteId;

#define ITFLIESBY_ENGINE_SPRITE_ID_INVALID -1

//----------------------------------------------------------------
// SCENES
//----------------------------------------------------------------

typedef s8 ItfliesbyEngineSceneId; 

#define ITFLIESBY_ENGINE_SCENE_INVALID -1
#define ITFLIESBY_ENGINE_SCENE_COUNT_MAX 8

api ItfliesbyEngineSceneId
itfliesby_engine_scene_create(
    ItfliesbyEngineHandle engine);

api void
itfliesby_engine_scene_destroy(
    ItfliesbyEngineHandle  engine,
    ItfliesbyEngineSceneId scene_id);

api void
itfliesby_engine_scene_set_active(
    ItfliesbyEngineHandle  engine,
    ItfliesbyEngineSceneId scene_id);

api ItfliesbyEngineSpriteId
itfliesby_engine_scene_connor_test(
    ItfliesbyEngineHandle  engine,
    ItfliesbyEngineSceneId scene_id);

api ItfliesbyEngineSpriteId
itfliesby_engine_scene_jig(
    ItfliesbyEngine*       engine,
    ItfliesbyEngineSceneId scene_id)

#endif //ITFLIESBY_ENGINE_HPP