#ifndef ITFLIESBY_ENGINE_PHYSICS_HPP
#define ITFLIESBY_ENGINE_PHYSICS_HPP

#include <itfliesby.hpp>
#include <math/itfliesby-math.hpp>

typedef ItfliesbyMathMat3 ItfliesbyEnginePhysicsTransform;
typedef ItfliesbyMathVec2 ItfliesbyEnginePhysicsPosition;
typedef ItfliesbyMathVec2 ItfliesbyEnginePhysicsVelocity;
typedef ItfliesbyMathVec2 ItfliesbyEnginePhysicsScale;
typedef f32               ItfliesbyEnginePhysicsRotationDegrees;

struct ItfliesbyEnginePhysicsMemory {
    itfliesby_memory_partition physics;
};

#define ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX     128
#define ITFLIESBY_ENGINE_PHYSICS_OBJECT_INVALID -1

typedef s8 ItfliesbyEnginePhysicsId; 

struct ItfliesbyEnginePhysicsTransformPayload {
    ItfliesbyEnginePhysicsTransform transforms[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsTablePosition {
    f32 x[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    f32 y[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsTableScale {
    f32 x[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    f32 y[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsTableRotation {
    f32 radians[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsTablesTransforms {
    ItfliesbyEnginePhysicsTablePosition position;
    ItfliesbyEnginePhysicsTableScale    scale;
    ItfliesbyEnginePhysicsTableRotation rotation;
};

struct ItfliesbyEnginePhysicsTableVelocity {
    f32 x[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    f32 y[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsTablesDynamics {
    ItfliesbyEnginePhysicsTableVelocity velocity;
};

struct ItfliesbyEnginePhysicsTables {
    ItfliesbyEnginePhysicsTablesTransforms transforms;
    ItfliesbyEnginePhysicsTablesDynamics   dynamics;
};


struct ItfliesbyEnginePhysics {
    //TODO: this is really lazy, we'll fix later
    b8 object_used[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    ItfliesbyEnginePhysicsMemory              memory;
    ItfliesbyEnginePhysicsTables              tables;
};

ItfliesbyEnginePhysicsId
itfliesby_engine_physics_id_get_next(
    ItfliesbyEnginePhysics* physics
);

void
itfliesby_engine_physics_update_position(
    ItfliesbyEnginePhysics*        physics,
    ItfliesbyEnginePhysicsId       physics_id,
    ItfliesbyEnginePhysicsPosition position);

#endif //ITFLIESBY_ENGINE_PHYSICS_HPP