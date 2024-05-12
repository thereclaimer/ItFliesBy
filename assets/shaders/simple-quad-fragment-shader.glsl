#version 330 core

in vec4 fragment_color; 
in vec2 fragment_uv;

uniform sampler2D texture_sampler;

out vec4 out_frag_color; 

void main() {

    vec4 texture_color = texture(texture_sampler,fragment_uv);

    out_frag_color = fragment_color.a > 0.0
        ? fragment_color
        : texture_color;

    // out_frag_color = texture_color; 
}
