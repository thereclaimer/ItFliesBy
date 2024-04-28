#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#define GLEW_STATIC

#include <glew/glew.h>
#include <glew/wglew.h>
#include <glew/glew.c>

#include <common/itfliesby-types.hpp>
#include <common/itfliesby-platform-api.hpp>
#include <common/itfliesby-memory.hpp>
#include <math/itfliesby-math.hpp>

#define ITFLIESBY_RENDERER_MEMORY_SIZE_BYTES                       ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_RENDERER_MEMORY_PARTITION_CORE_SIZE_BYTES        ITFLIESBY_MATH_KILOBYTES(32)
#define ITFLIESBY_RENDERER_MEMORY_ALLOCATOR_CORE_SYSTEM_SIZE_BYTES ITFLIESBY_MATH_KILOBYTES(16)

global ItfliesbyPlatformApi platform;

struct ItfliesbyRendererShader {
    GLuint program_id;
    GLuint stage_id_vertex;
    GLuint stage_id_fragment;
};

#define ITFLIESBY_RENDERER_SHADER_COUNT 16

typedef s8 ItfliesbyRendererShaderIndex;

enum ItfliesbyRendererShaderError {
    ITFLIESBY_RENDERER_SHADER_ERROR_OKAY                             = 0x01,
    ITFLIESBY_RENDERER_SHADER_ERROR                                  = 0x80,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE                = 0x81,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_VERTEX   = 0x82,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_COMPILE_STAGE_FRAGMENT = 0x83,
    ITFLIESBY_RENDERER_SHADER_ERROR_FAILED_TO_LINK                   = 0x84,
    ITFLIESBY_RENDERER_SHADER_ERROR_MAX_SHADERS                      = 0x85
};
struct ItfliesbyRendererShaderStore {
    ItfliesbyRendererShader shaders[ITFLIESBY_RENDERER_SHADER_COUNT];
};

struct ItfliesbyRendererShaderStageBuffer {
    memory                       shader_stage_data;
    ItfliesbyRendererShaderError result;

};
struct ItfliesbyRendererMemory {

    itfliesby_memory_arena arena;
    
    struct {
        itfliesby_memory_partition core;
    } partitions;

    struct {
        itfliesby_memory_allocator_linear core_system_allocator;
    } allocators;
};



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


struct ItfliesbyRendererColorHex {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};


//the normalizing factor is (1/255) as a decimal
#define ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR 0.00392157

struct ItfliesbyRendererColorNormalized {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

inline ItfliesbyRendererColorNormalized
itfliesby_renderer_color_normalize(
    ItfliesbyRendererColorHex color_hex) {

    ItfliesbyRendererColorNormalized color_normalized = {0};
    
    color_normalized.r = color_hex.r * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;  
    color_normalized.g = color_hex.g * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.b = color_hex.b * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.a = color_hex.a * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;

    return(color_normalized);
}


#define ITFLIESBY_RENDERER_SOLID_QUADS_MAX 128

#define ITFLIESBY_RENDERER_SOLID_QUAD_ID_INVALID -1


typedef s8                ItfliesbyRendererSolidQuadId;
typedef u8                ItfliesbyRendererSolidQuadInstanceGroup;
typedef s32               ItfliesbyQuadId;
typedef ItfliesbyMathMat3 ItfliesbyRendererModelTransform;


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

struct ItfliesbyRenderer {
    handle                       gl_context;
    ItfliesbyRendererShaderStore shader_store;
    ItfliesbyRendererQuadManager quad_manager;
};

struct ItfliesbyRendererSolidQuadUpdate {
    ItfliesbyRendererModelTransform transform;
    ItfliesbyRendererColorHex       color;
};

struct ItfliesbyRendererSolidQuadUpdateBatch {
    ItfliesbyRendererSolidQuadUpdate batch[ITFLIESBY_RENDERER_SOLID_QUADS_MAX];
    u8                               count;
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


#endif //ITFLIESBY_RENDERER_HPP