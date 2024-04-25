#version 330 core

layout (location = 0) in vec2 in_vertex_position; 
layout (location = 1) in vec4 in_vertex_color;    

uniform mat4 model; 

out vec4 out_vertex_color; 

void main()
{
    gl_Position = model * vec4(in_vertex_position, 0.0, 1.0); 
    
    out_vertex_color = in_vertex_color;
}