#version 330 core

layout (location = 0) in vec2 in_vertex_position; 

layout (std140) uniform solid_quad_update {
    mat3 model;
    vec4 color;
};

out vec4 out_vertex_color; 

void main()
{
    gl_Position = model * vec4(in_vertex_position, 0.0, 1.0); 
    
    out_vertex_color = color;
}