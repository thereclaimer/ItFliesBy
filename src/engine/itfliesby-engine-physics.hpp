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


struct ItfliesbyEnginePhysicsTransformProperties {
    ItfliesbyEnginePhysicsPosition        positions[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    ItfliesbyEnginePhysicsScale           scale[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    ItfliesbyEnginePhysicsRotationDegrees rotation[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsDynamicProperties {
    ItfliesbyEnginePhysicsVelocity velocity[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysics {
    //TODO: this is really lazy, we'll fix later
    b8 object_used[ITFLIESBY_ENGINE_PHYSICS_OBJECTS_MAX];
    ItfliesbyEnginePhysicsMemory              memory;
    ItfliesbyEnginePhysicsTransformProperties transforms;
    ItfliesbyEnginePhysicsDynamicProperties   dynamics;
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