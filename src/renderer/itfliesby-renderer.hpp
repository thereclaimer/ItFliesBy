#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP

#include <itfliesby.hpp>
#include "itfliesby-renderer-gl.hpp"
#include "itfliesby-renderer-shader.hpp"

#define ITFLIESBY_RENDERER_MEMORY_SIZE_ARENA           ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_RENDERER_MEMORY_SIZE_PARTITION_CORE  ITFLIESBY_MATH_KILOBYTES(8)
#define ITFLIESBY_RENDERER_MEMORY_SIZE_ALLLOCATOR_CORE ITFLIESBY_MATH_KILOBYTES(2)

#define ITFLIESBY_RENDERER_MAX_SHADER_STAGES   128
#define ITFLIESBY_RENDERER_MAX_SHADER_PROGRAMS 128

struct ItfliesbyRendererShaderStages {
    s32 vertex_shader_gl_ids[ITFLIESBY_RENDERER_MAX_SHADER_STAGES];
    s32 fragment_shader_gl_ids[ITFLIESBY_RENDERER_MAX_SHADER_STAGES];
    u32 vertex_shader_count;
    u32 fragment_shader_count;
};

struct ItfliesbyRendererAllocators {
    itfliesby_memory_allocator_linear core_system_allocator;
};

struct ItfliesbyRendererPartitions {
    itfliesby_memory_partition core;
};

struct ItfliesbyRendererMemory {
    itfliesby_memory_arena      arena;
    ItfliesbyRendererPartitions partitions;
    ItfliesbyRendererAllocators allocators;
};

struct ItfliesbyRenderer {
    ItfliesbyRendererMemory  memory;
    handle                   gl_context;
    ItfliesbyPlatformApi     platform;
    ItfliesbyRendererShaders shaders;
};

api ItfliesbyRenderer*
itfliesby_renderer_create(
    ItfliesbyPlatformApi platform,
    memory               memory,
    u64                  memory_size
);

api void
itfliesby_renderer_destroy(
    ItfliesbyRenderer* renderer
);

api void
itfliesby_renderer_update_and_render(
    ItfliesbyRenderer* renderer
);

#endif //ITFLIESBY_RENDERER_HPP