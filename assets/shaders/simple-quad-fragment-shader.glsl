#version 330 core

in vec4 fragment_color; 

out vec4 out_frag_color; 

void main() {

    out_frag_color = fragment_color; 
}
