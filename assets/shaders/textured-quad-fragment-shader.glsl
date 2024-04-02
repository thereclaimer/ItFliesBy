#version 330 core

in vec2 fragment_uv;
in vec4 fragment_color;

uniform sampler2D texture_sampler;

out vec4 fragment_color;  

void main()
{
    fragment_color = texture(texture_sampler, fragment_uv).rgba;
}   