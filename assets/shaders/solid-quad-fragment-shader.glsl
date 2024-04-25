#version 330 core

in vec4 out_vertex_color; 

out vec4 out_frag_color; 

void main()
{
    out_frag_color = out_vertex_color; 
}