#ifndef ITFLIESBY_RENDERER_TYPES_HPP
#define ITFLIESBY_RENDERER_TYPES_HPP

struct ItfliesbyRendererColorHex {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};


//the normalizing factor is (1/255) as a decimal
#define ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR 0.00392157

struct ItfliesbyRendererColorNormalized {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

inline ItfliesbyRendererColorNormalized
itfliesby_renderer_color_normalize(
    ItfliesbyRendererColorHex color_hex) {

    ItfliesbyRendererColorNormalized color_normalized = {0};
    
    color_normalized.r = color_hex.r * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;  
    color_normalized.g = color_hex.g * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.b = color_hex.b * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR; 
    color_normalized.a = color_hex.a * ITFLIESBY_RENDERER_QUAD_COLOR_NORMALIZING_FACTOR;

    return(color_normalized);
}

#endif //ITFLIESBY_RENDERER_TYPES_HPP