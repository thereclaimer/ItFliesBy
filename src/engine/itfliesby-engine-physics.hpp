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

#define ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX 128

typedef s8 ItfliesbyEnginePhysicsObjectId; 

struct ItfliesbyEnginePhysicsTransformPayload {
    ItfliesbyEnginePhysicsTransform transforms[ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX];
};


struct ItfliesbyEnginePhysicsTransformProperties {
    ItfliesbyEnginePhysicsPosition        positions[ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX];
    ItfliesbyEnginePhysicsScale           scale[ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX];
    ItfliesbyEnginePhysicsRotationDegrees rotation[ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysicsDynamicProperties {
    ItfliesbyEnginePhysicsVelocity velocity[ITFLIESBY_ENGINE_PHYSICS_DYNAMIC_OBJECTS_MAX];
};

struct ItfliesbyEnginePhysics {
    ItfliesbyEnginePhysicsMemory              memory;
    ItfliesbyEnginePhysicsTransformProperties transforms;
    ItfliesbyEnginePhysicsDynamicProperties   dynamics;
};

#endif //ITFLIESBY_ENGINE_PHYSICS_HPP