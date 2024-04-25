#ifndef ITFLIESBY_ENGINE_HPP
#define ITFLIESBY_ENGINE_HPP

#include <itfliesby.hpp>
#include "itfliesby-engine-globals.hpp"
#include "itfliesby-engine-assets.hpp"
#include "itfliesby-engine-memory.hpp"

struct ItfliesbyEngineShaderStore {
    union {
        struct {
            ItfliesbyRendererShaderIndex textured_quad_shader_index;
            ItfliesbyRendererShaderIndex solid_quad_shader_index;
        } instances;
        
        ItfliesbyRendererShaderIndex array[sizeof(instances) / sizeof(ItfliesbyRendererShaderIndex)];
    };
};

struct ItfliesbyEngineRendererMemory {
    itfliesby_memory_partition        partition;
    itfliesby_memory_partition        rendering_context_partition;
    itfliesby_memory_allocator_linear shader_asset_data_allocator;
};

#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_SIZE             ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_RENDERER_MEMORY_PARTITION_CONTEXT_SIZE     ITFLIESBY_MATH_MEGABYTES(64)
#define ITFLIESBY_ENGINE_RENDERER_MEMORY_ALLOCATOR_SIZE_SHADER_DATA ITFLIESBY_MATH_MEGABYTES(4)

struct ItfliesbyEngine {
    ItfliesbyEngineAssets      assets;
    ItfliesbyEngineShaderStore shaders;
    ItfliesbyRendererHandle    renderer;
};

api ItfliesbyEngine*
itfliesby_engine_create(
    ItfliesbyPlatformApi platform,
    memory               mem,
    u64                  mem_size
);

api void
itfliesby_engine_destroy(
    ItfliesbyEngine* engine
);


api void
itfliesby_engine_update_and_render(
    ItfliesbyEngine* engine
);


#endif //ITFLIESBY_ENGINE_HPP