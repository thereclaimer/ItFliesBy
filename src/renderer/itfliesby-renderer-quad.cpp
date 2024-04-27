#pragma once

#include "itfliesby-renderer.hpp"

internal void
itfliesby_renderer_quad_index_buffer_create(
    GLuint vbo,
    const u32 quad_vertices[6]) {
    
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        vbo);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        sizeof(u32) * 6, 
        quad_vertices, 
        GL_STATIC_DRAW);

}

internal void
itfliesby_renderer_quad_vertex_buffer_create(
    GLuint vbo,
    const f32 quad_vertices[8]) {
    
    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo);

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(f32) * 8, 
        quad_vertices, 
        GL_STATIC_DRAW);

}

internal ItfliesbyRendererQuadBuffers
itfliesby_renderer_quad_buffers_init() {

    ItfliesbyRendererQuadBuffers quad_buffers = {0};

    glGenBuffers(
        ITFLIESBY_RENDERER_QUAD_BUFFERS_COUNT,
        quad_buffers.array
    );

    itfliesby_renderer_quad_index_buffer_create(
        quad_buffers.instances.indices,
        ITFLIESBY_RENDERER_INDICES_QUAD
    );

    itfliesby_renderer_quad_vertex_buffer_create(
        quad_buffers.instances.square_quad_vertices,
        ITFLIESBY_RENDERER_VERTICES_SQUARE_QUAD
    );

    return(quad_buffers);
};

internal ItfliesbyRendererSolidQuads
itfliesby_renderer_quad_solid_quads_init() {
    
    ItfliesbyRendererSolidQuads solid_quads = {0};

    return(solid_quads);
}

internal ItfliesbyRendererQuadManager
itfliesby_renderer_quad_manager_init() {

    ItfliesbyRendererQuadManager quad_manager = {0};
    quad_manager.quad_buffers = itfliesby_renderer_quad_buffers_init(); 
    quad_manager.solid_quads  = itfliesby_renderer_quad_solid_quads_init();

    ItfliesbyRendererSolidQuadInstances solid_quad_instances = {0};

    for (
        u8 instance_group_index = 0;
           instance_group_index < ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUPS_COUNT;
         ++instance_group_index) {

        solid_quad_instances.instance_groups[instance_group_index] = ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUP_EMPTY;
    }

    quad_manager.solid_quads.instances = solid_quad_instances;

    return(quad_manager);
}

internal ItfliesbyRendererSolidQuadId
itfliesby_renderer_quad_solid_quads_find_next_instance(
    ItfliesbyRendererSolidQuadInstances* instances) {
    

    ItfliesbyRendererSolidQuadInstanceGroup* groups = instances->instance_groups;
    ItfliesbyRendererSolidQuadInstanceGroup group = 0;
    b8 group_available = false;
    u32 group_index = 0;

    for (
        group_index = 0;
        group_index < ITFLIESBY_RENDERER_SOLID_QUAD_INSTANCE_GROUPS_COUNT;
        ++group_index) {

        group = groups[group_index];

        group_available = itfliesby_renderer_solid_quad_instance_group_available(group);
        if (group_available) {
            break;
        }
    }

    if (!group_available) {
        return (ITFLIESBY_RENDERER_SOLID_QUAD_ID_INVALID);
    }
    
    ItfliesbyRendererSolidQuadId next_id = 0;

    for (
        u8 instance_index = 0;
        instance_index < 8;
        ++instance_index) {

        u8 bit_index = 7 - instance_index;

        if (!(group & (1 << bit_index))) {
            
            groups[group_index] = group ^ (1 << bit_index);
            next_id = (8 * group_index) + instance_index;
            break;
        }
    }

    return(next_id);
}

external ItfliesbyRendererSolidQuadId
itfliesby_renderer_quad_solid_quads_create_instance(
    ItfliesbyRenderer*        renderer,
    ItfliesbyRendererColorHex color_hex) {

    ItfliesbyRendererSolidQuads*         solid_quads          = &renderer->quad_manager.solid_quads;
    ItfliesbyRendererSolidQuadInstances* solid_quad_instances = &solid_quads->instances;

    ItfliesbyRendererSolidQuadId solid_quad_id = 
        itfliesby_renderer_quad_solid_quads_find_next_instance(
            solid_quad_instances
        );

    if (!itfliesby_renderer_solid_quad_id_valid(solid_quad_id)) {
        return(solid_quad_id);
    }

    solid_quads->colors[solid_quad_id]           = itfliesby_renderer_color_normalize(color_hex);
    solid_quads->model_transforms[solid_quad_id] = itfliesby_math_mat3_identity();

    return(solid_quad_id);
}