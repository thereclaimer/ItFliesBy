#ifndef ITFLIESBY_RENDERER_QUAD_HPP
#define ITFLIESBY_RENDERER_QUAD_HPP

#include <common/itfliesby-types.hpp>
#include <common/itfliesby-platform-api.hpp>
#include <common/itfliesby-memory.hpp>
#include <math/itfliesby-math.hpp>

#include "itfliesby-renderer-opengl.hpp"
#include "itfliesby-renderer-types.hpp"

struct ItfliesbyRendererQuadBuffers {
    union {
    
        struct {
            GLuint indices; 
            GLuint square_quad_vertices; 
        } instances;
        
        GLuint array[sizeof(instances) / sizeof(GLuint)];
    };
};

#define ITFLIESBY_RENDERER_QUAD_BUFFERS_COUNT (sizeof(ItfliesbyRendererQuadBuffers::instances) / sizeof(GLuint))
#define ITFLIESBY_RENDERER_SOLID_QUADS_MAX 128

#define ITFLIESBY_RENDERER_SOLID_QUAD_ID_INVALID -1

typedef s8                ItfliesbyRendererSolidQuadId;
typedef u8                ItfliesbyRendererSolidQuadInstanceGroup;
typedef s32               ItfliesbyQuadId;



struct ItfliesbyRendererSolidQuadInstanceKey {
    
    union {

        struct {
            ItfliesbyRendererSolidQuadId             solid_quad_id;
            ItfliesbyRendererSolidQuadInstanceGroup  group;
            u8                                       instance_index;
        } members;

        ItfliesbyQuadId value;
    };
};

inline b8 
itfliesby_renderer_solid_quad_id_valid(
    ItfliesbyRendererSolidQuadId solid_quad_id) {
    return (solid_quad_id > ITFLIESBY_RENDERER_SOLID_QUAD_ID_INVALID);
}

#define ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_SIZE   8
#define ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUPS_COUNT (ITFLIESBY_RENDERER_SOLID_QUADS_MAX / ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_SIZE)
#define ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_FULL   0xFF
#define ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_EMPTY  0x00

inline b8
itfliesby_renderer_solid_quad_instance_group_available(
    ItfliesbyRendererSolidQuadInstanceGroup group) {

    return (group < ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_FULL);
}

struct ItfliesbyRendererSolidQuadInstances {
    ItfliesbyRendererSolidQuadInstanceGroup instance_groups[ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUPS_COUNT];
};

inline ItfliesbyRendererSolidQuadId
itfliesby_renderer_solid_quad_id_find_next(
    ItfliesbyRendererSolidQuadInstances solid_quad_instances) {
    
    ItfliesbyRendererSolidQuadId next_solid_quad_id = ITFLIESBY_RENDERER_SOLID_QUAD_ID_INVALID;

    return(next_solid_quad_id);
}


struct ItfliesbyRendererSolidQuads {
    ItfliesbyMathMat3                   model_transforms[ITFLIESBY_RENDERER_SOLID_QUADS_MAX];
    ItfliesbyRendererColorNormalized    colors[ITFLIESBY_RENDERER_SOLID_QUADS_MAX];
    ItfliesbyRendererSolidQuadInstances instances;
};

struct ItfliesbyRendererQuadManager {
    ItfliesbyRendererQuadBuffers quad_buffers;
    ItfliesbyRendererSolidQuads  solid_quads;
    
};


const f32 ITFLIESBY_RENDERER_VERTICES_SQUARE_QUAD[] = {
    -0.5f,  0.5f,
     0.5f, -0.5f,
    -0.5f, -0.5f,
     0.5f,  0.5f
};

const u32 ITFLIESBY_RENDERER_INDICES_QUAD[] = {
    0, 1, 2, 
    0, 3, 1  
};


struct ItfliesbyRendererSolidQuadUpdate {
    ItfliesbyRendererModelTransform transform;
    ItfliesbyRendererColorHex       color;
};

#define ITFLIESBY_RENDERER_SOLID_QUAD_UPDATE_SIZE() sizeof(ItfliesbyRendererSolidQuadUpdate)

struct ItfliesbyRendererSolidQuadUpdateBatch {
    ItfliesbyRendererSolidQuadUpdate batch[ITFLIESBY_RENDERER_SOLID_QUADS_MAX];
    u8                               count;
};


#endif //ITFLIESBY_RENDERER_QUAD_HPP