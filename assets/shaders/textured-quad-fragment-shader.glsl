#version 330 core

in vec2 fragment_uv;
in vec4 fragment_color_in;

uniform sampler2D texture_sampler;

out vec4 fragment_color_out;  

void main()
{
    fragment_color_out = texture(texture_sampler, fragment_uv).rgba;
}   