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
    u64                  mem_size
);

api void
itfliesby_engine_destroy(
    ItfliesbyEngineHandle engine
);

api void
itfliesby_engine_update_and_render(
          ItfliesbyEngineHandle engine,
    const ItfliesbyUserInput*   user_input
);

//----------------------------------------------------------------
// SCENES
//----------------------------------------------------------------

typedef s8 ItfliesbyEngineSceneId; 

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

api void
itfliesby_engine_scene_connor_test(
    ItfliesbyEngineHandle  engine,
    ItfliesbyEngineSceneId scene_id);

#endif //ITFLIESBY_ENGINE_HPP