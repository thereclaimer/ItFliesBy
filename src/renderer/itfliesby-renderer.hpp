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
#define ITFLIESBY_RENDERER_MEMORY_PARTITION_CORE_SIZE_BYTES        ITFLIESBY_MATH_KILOBYTES(2)
#define ITFLIESBY_RENDERER_MEMORY_ALLOCATOR_CORE_SYSTEM_SIZE_BYTES ITFLIESBY_MATH_KILOBYTES(1)

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

struct ItfliesbyRenderer {
    handle                       gl_context;
    ItfliesbyRendererShaderStore shader_store;
    ItfliesbyRendererQuadBuffers quad_buffers;
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