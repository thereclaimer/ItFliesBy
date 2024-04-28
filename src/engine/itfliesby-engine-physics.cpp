#pragma once

#include "itfliesby-engine-physics.hpp"

internal void
itfliesby_engine_physics_dynamics(
    ItfliesbyEnginePhysicsDynamicProperties*   in_dynamic_properties,
    ItfliesbyEnginePhysicsTransformProperties* out_transform_properties) {

    ItfliesbyEnginePhysicsVelocity* dynamic_property_velocity   = in_dynamic_properties->velocity;
    ItfliesbyEnginePhysicsPosition* transform_property_position = out_transform_properties->positions;

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX;
        ++index) {

        //update positions
        transform_property_position[index].x += dynamic_property_velocity[index].x; 
        transform_property_position[index].y += dynamic_property_velocity[index].y; 
        
        dynamic_property_velocity[index].x = 0.0f;
        dynamic_property_velocity[index].y = 0.0f;
    }
}

internal void
itfliesby_engine_physics_transforms(
    ItfliesbyEnginePhysicsTransformProperties*  in_transform_properties,
    ItfliesbyEnginePhysicsTransformPayload*     out_transform_payload) {

    ItfliesbyEnginePhysicsPosition*        positions = in_transform_properties->positions;
    ItfliesbyEnginePhysicsScale*           scale     = in_transform_properties->scale;
    ItfliesbyEnginePhysicsRotationDegrees* rotation  = in_transform_properties->rotation;
    ItfliesbyEnginePhysicsTransform*       transform = out_transform_payload->transforms;

    ItfliesbyEnginePhysicsTransform transform_translation[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX] = {0};
    ItfliesbyEnginePhysicsTransform transform_scale[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX]       = {0};
    ItfliesbyEnginePhysicsTransform transform_rotation[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX]    = {0};

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX;
        ++index) {

        transform_translation[index] = itfliesby_math_mat3_translation(positions[index].x, positions[index].y);
        transform_scale[index]       = itfliesby_math_mat3_scaling(scale[index].x, scale[index].y);
        transform_rotation[index]    = itfliesby_math_mat3_rotation_degrees(rotation[index]);
    }

    itfliesby_math_mat3_transform_trs(
        ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX,
        transform_translation,
        transform_scale,
        transform_rotation,
        transform);
}

internal void
itfliesby_engine_physics_update(
    ItfliesbyEnginePhysics*                 physics,
    ItfliesbyEnginePhysicsTransformPayload* payload) {

    ItfliesbyEnginePhysicsDynamicProperties*   dynamic_properties   = &physics->dynamics;
    ItfliesbyEnginePhysicsTransformProperties* transform_properties = &physics->transforms;

    itfliesby_engine_physics_dynamics(
        dynamic_properties,
        transform_properties
    );

    itfliesby_engine_physics_transforms(
        transform_properties,
        payload
    );
}

internal ItfliesbyEnginePhysicsId
itfliesby_engine_physics_id_get_next(
    ItfliesbyEnginePhysics* physics) {

    ItfliesbyEnginePhysicsId next_physics_id = ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID;
    b8* objects_used = physics->object_used;

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX;
        ++index) {

        if (!objects_used[index]) {
            next_physics_id = index;
            objects_used[index] = true;
            break;
        }
    }

    return(next_physics_id);
}

internal ItfliesbyEnginePhysics
itfliesby_engine_physics_create_and_init() {

    ItfliesbyEnginePhysics physics = {0};

    return(physics);
}

internal void
itfliesby_engine_physics_update_position(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    ItfliesbyEnginePhysicsPosition position) {

    physics->transforms.positions[physics_id] = position;
}