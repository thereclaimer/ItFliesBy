#version 330 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_uv;

uniform mat3 transform;

out vec2 fragment_uv;

void main()
{
    gl_Position = transform * vec3(vertex_position, 1.0);

    fragment_uv = vertex_uv;
}