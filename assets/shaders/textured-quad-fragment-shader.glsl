#version 330 core

in vec2 fragment_uv;

uniform sampler2D texture_sampler;

out vec4 fragment_color;  

void main()
{
    fragment_color = texture(texture_sampler, fragment_uv).rgba;
}   