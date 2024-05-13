#ifndef ITFLIESBY_RENDERER_HPP
#define ITFLIESBY_RENDERER_HPP


#include <common/itfliesby-types.hpp>
#include <common/itfliesby-platform-api.hpp>
#include <common/itfliesby-memory.hpp>

#include "itfliesby-renderer-opengl.hpp"
#include "itfliesby-renderer-shader.hpp"
#include "itfliesby-renderer-quad.hpp"
#include "itfliesby-renderer-memory.hpp"
#include "itfliesby-renderer-texture.hpp"

global ItfliesbyPlatformApi platform;

struct ItfliesbyRendererBatches{
    ItfliesbyRendererBatchSimpleQuad simple_quad;
};

struct ItfliesbyRendererBuffers {
    ItfliesbyRendererShaderBuffersSimpleQuad simple_quad;
};

struct ItfliesbyRendererPerspective {
    ItfliesbyMathMat3 transform;
    f32               width_pixels;
    f32               height_pixels;
};

struct ItfliesbyRenderer {
    handle                        gl_context;
    ItfliesbyRendererShaderStore  shader_store;
    ItfliesbyRendererQuadManager  quad_manager;
    ItfliesbyRendererBatches      batches;
    ItfliesbyRendererBuffers      buffers;
    ItfliesbyRendererTextureStore textures;
    ItfliesbyRendererPerspective  perspective;
};

#endif //ITFLIESBY_RENDERER_HPP