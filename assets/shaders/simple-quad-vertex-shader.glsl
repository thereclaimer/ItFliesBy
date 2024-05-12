#version 330 core

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 uv;

uniform mat3 transform;
uniform vec4 color;

out vec4 fragment_color;
out vec2 fragment_uv;

void main() {

    gl_Position = vec4(transform * vec3(vertex, 1.0), 1.0);

    fragment_color = color;
    fragment_uv    = uv;
}
