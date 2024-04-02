#version 330 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec4 vertex_color;

uniform mat3 transform;

out vec2 fragment_uv;
out vec4 fragment_color;

void main()
{
    vec3 transformed_vertex_position = transform * vec3(vertex_position, 1.0);

    gl_Position = vec4(transformed_vertex_position.xy, 0.0, 1.0);

    fragment_uv    = vertex_uv;
    fragment_color = vertex_color;
}