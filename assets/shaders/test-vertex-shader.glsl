#version 330 core

layout(location = 0) in vec2 vertex;

uniform mat3 transform;
uniform vec4 color;

out vec4 fragment_color;

void main() {

    gl_Position = vec4(transform * vec3(vertex, 1.0), 1.0);

    fragment_color = color;
}
