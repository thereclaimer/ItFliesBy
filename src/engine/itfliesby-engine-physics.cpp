#pragma once

#include "itfliesby-engine-physics.hpp"

internal void
itfliesby_engine_physics_dynamics(
    ItfliesbyEnginePhysicsTablesTransforms* tables_transforms,
    ItfliesbyEnginePhysicsTablesDynamics*   tables_dynamics) {

    ItfliesbyEnginePhysicsTablePosition* table_transforms_position = &tables_transforms->position;
    ItfliesbyEnginePhysicsTableVelocity* table_dynamics_velocity   = &tables_dynamics->velocity;

    f32* position_x = table_transforms_position->x;
    f32* position_y = table_transforms_position->y;

    f32* velocity_x = table_dynamics_velocity->x;
    f32* velocity_y = table_dynamics_velocity->y;

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX;
        ++index) {

        //update positions
        position_x[index] += velocity_x[index];
        position_y[index] += velocity_y[index];

        velocity_x[index] = 0.0f;
        velocity_y[index] = 0.0f;
    }
}

internal void
itfliesby_engine_physics_transforms(
    ItfliesbyEnginePhysicsTablesTransforms*  in_tables_properties,
    ItfliesbyEnginePhysicsTransformPayload*  out_transform_payload) {

    ItfliesbyEnginePhysicsTablePosition* table_transforms_position = &in_tables_properties->position;
    ItfliesbyEnginePhysicsTableScale*    table_transforms_scale    = &in_tables_properties->scale;
    ItfliesbyEnginePhysicsTableRotation* table_transforms_rotation = &in_tables_properties->rotation;
    
    f32* table_position_x       = table_transforms_position->x;
    f32* table_position_y       = table_transforms_position->y;
    f32* table_scale_x          = table_transforms_scale->x;
    f32* table_scale_y          = table_transforms_scale->y;
    f32* table_rotation_radians = table_transforms_rotation->radians;

    ItfliesbyEnginePhysicsTransform*     transform                 = out_transform_payload->transforms;

    ItfliesbyEnginePhysicsTransform transform_translation[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX] = {0};
    ItfliesbyEnginePhysicsTransform transform_scale[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX]       = {0};
    ItfliesbyEnginePhysicsTransform transform_rotation[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX]    = {0};

    for (
        u32 index = 0;
        index < ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX;
        ++index) {

        //translation
        transform_translation[index] = 
            itfliesby_math_mat3_translation(
                table_position_x[index],
                table_position_y[index]);
        
        //scale
        transform_scale[index] = 
            itfliesby_math_mat3_scaling(
                table_scale_x[index], 
                table_scale_y[index]);
        
        //rotation
        transform_rotation[index] = 
            itfliesby_math_mat3_rotation_radians(
                table_rotation_radians[index]);
    }

    //put the transforms together
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

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms = &physics->tables.transforms;
    ItfliesbyEnginePhysicsTablesDynamics*   physics_table_dynamics   = &physics->tables.dynamics;

    itfliesby_engine_physics_dynamics(
        physics_table_transforms,
        physics_table_dynamics
    );

    itfliesby_engine_physics_transforms(
        physics_table_transforms,
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

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms          = &physics->tables.transforms;
    ItfliesbyEnginePhysicsTablePosition*    physics_table_transforms_position = &physics_table_transforms->position;

    f32* position_x = physics_table_transforms_position->x;
    f32* position_y = physics_table_transforms_position->y;

    position_x[physics_id] = position.x;
    position_y[physics_id] = position.y;
}


internal void
itfliesby_engine_physics_update_scale(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    ItfliesbyEnginePhysicsScale    scale) {

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms       = &physics->tables.transforms;
    ItfliesbyEnginePhysicsTableScale*       physics_table_transforms_scale = &physics_table_transforms->scale;

    f32* scale_x = physics_table_transforms_scale->x;
    f32* scale_y = physics_table_transforms_scale->y;

    scale_x[physics_id] = scale.x;    
    scale_y[physics_id] = scale.y;
}


internal void
itfliesby_engine_physics_update_rotation_degrees(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    f32                            rotation_degrees) {

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms          = &physics->tables.transforms;
    ItfliesbyEnginePhysicsTableRotation*    physics_table_transforms_rotation = &physics_table_transforms->rotation;

    f32* table_rotation_radians = physics_table_transforms_rotation->radians;

    f32 rotation_radians = itfliesby_math_trig_degrees_to_radians(rotation_degrees);

    table_rotation_radians[physics_id] = rotation_radians; 
}

internal void
itfliesby_engine_physics_update_rotation_radians(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    f32                            rotation_radians) {

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms          = &physics->tables.transforms;
    ItfliesbyEnginePhysicsTableRotation*    physics_table_transforms_rotation = &physics_table_transforms->rotation;

    f32* table_rotation_radians = physics_table_transforms_rotation->radians;

    table_rotation_radians[physics_id] = rotation_radians; 
}
internal void
itfliesby_engine_physics_update_id(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    ItfliesbyEnginePhysicsPosition position,
    ItfliesbyEnginePhysicsScale    scale,
    f32                            rotation_radians) {

    ItfliesbyEnginePhysicsTablesTransforms* physics_table_transforms          = &physics->tables.transforms;
    
    ItfliesbyEnginePhysicsTablePosition*    physics_table_transforms_position = &physics_table_transforms->position;
    ItfliesbyEnginePhysicsTableScale*       physics_table_transforms_scale    = &physics_table_transforms->scale;
    ItfliesbyEnginePhysicsTableRotation*    physics_table_transforms_rotation = &physics_table_transforms->rotation;

    f32* position_x = physics_table_transforms_position->x;
    f32* position_y = physics_table_transforms_position->y;
    f32* scale_x    = physics_table_transforms_scale->x;
    f32* scale_y    = physics_table_transforms_scale->y;
    f32* radians    = physics_table_transforms_rotation->radians;

    position_x[physics_id] = position.x;
    position_y[physics_id] = position.y;
    scale_x[physics_id]    = scale.x;    
    scale_y[physics_id]    = scale.y;
    radians[physics_id]    = rotation_radians; 
}