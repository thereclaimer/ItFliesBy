#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP


#include <common/itfliesby-types.hpp>
#include <common/itfliesby-platform-api.hpp>
#include <common/itfliesby-memory.hpp>

#include "itfliesby-renderer-opengl.hpp"
#include "itfliesby-renderer-shader.hpp"
#include "itfliesby-renderer-quad.hpp"
#include "itfliesby-renderer-memory.hpp"

global ItfliesbyPlatformApi platform;

struct ItfliesbyRendererBatches{
    ItfliesbyRendererTestBatch test;
};

struct ItfliesbyRenderer {
    handle                       gl_context;
    ItfliesbyRendererShaderStore shader_store;
    ItfliesbyRendererQuadManager quad_manager;
    ItfliesbyRendererBatches     batches;
};

#endif //ITFLIESBY_RENDERER_HPP