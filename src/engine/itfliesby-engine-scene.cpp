#pragma once

#include "itfliesby-engine-scene.hpp"

void
itfliesby_engine_scene_manager_create(
    ItfliesbyEngineSceneManager* scene_manager) {

    *scene_manager = {0};
    scene_manager->active_scene = ITFLIESBY_ENGINE_SCENE_INVALID;
}

external ItfliesbyEngineSceneId
itfliesby_engine_scene_create(
    ItfliesbyEngine* engine) {
    
    ItfliesbyEngineSceneManager* scene_manager             = &engine->scenes;    
    ItfliesbyEngineScene*        scene_manager_scenes      = scene_manager->scenes;
    b8*                          scene_manager_used_scenes = scene_manager->used_scenes;

    ItfliesbyEngineSceneId new_scene_id = ITFLIESBY_ENGINE_SCENE_INVALID;

    //find the next available scene id
    for (
        ItfliesbyEngineSceneId scene_id = 0;
        scene_id < ITFLIESBY_ENGINE_SCENE_COUNT_MAX;
        ++scene_id) {

        if (!scene_manager_used_scenes[scene_id]) {
            new_scene_id = scene_id;
            break;
        }
    }

    //activate the scene
    ItfliesbyEngineScene new_scene = {0};
    new_scene.sprite_id_connor = ITFLIESBY_ENGINE_SPRITE_ID_INVALID;

    scene_manager_used_scenes[new_scene_id] = true;
    scene_manager_scenes[new_scene_id]      = itfliesby_engine_scene_reset();

    return(new_scene_id);
}

external void
itfliesby_engine_scene_destroy(
    ItfliesbyEngine*       engine,
    ItfliesbyEngineSceneId scene_id) {

    engine->scenes.used_scenes[scene_id] = false;

    if (engine->scenes.active_scene == scene_id) {
        engine->scenes.active_scene = ITFLIESBY_ENGINE_SCENE_INVALID;
    }
}

external void
itfliesby_engine_scene_set_active(
    ItfliesbyEngine*       engine,
    ItfliesbyEngineSceneId scene_id) {

    engine->scenes.active_scene = scene_id;
}


external void
itfliesby_engine_scene_connor_test(
    ItfliesbyEngine*       engine,
    ItfliesbyEngineSceneId scene_id) {

}