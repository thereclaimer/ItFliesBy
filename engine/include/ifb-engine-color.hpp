#ifndef IFB_ENGINE_COLOR_HPP
#define IFB_ENGINE_COLOR_HPP

#include "ifb-engine-types.hpp"

typedef ifb_u32 ifb_color_32_t;
typedef ifb_u32 ifb_color_32_format_t;

enum IFBEngineColor32Format_ {
    IFBEngineColorFormat_RGBA,
    IFBEngineColorFormat_ARGB,
    IFBEngineColorFormat_ABGR,
    IFBEngineColorFormat_BGRA
};

typedef ifb_u32 IFBEngineColor32Format;

struct IFBEngineColor32 {
    ifb_b8 red;
    ifb_b8 green;
    ifb_b8 blue;
    ifb_b8 alpha;
};

struct IFBEngineColor32Normalized {
    ifb_f32 red;
    ifb_f32 green;
    ifb_f32 blue;
    ifb_f32 alpha;
};

namespace ifb_engine {

    inline ifb_void
    color_32_normalize(
        IFBEngineColor32&            in_color_32_ref,
        IFBEngineColor32Normalized& out_color_32_normalized_ref) {

        out_color_32_normalized_ref.red   = in_color_32_ref.red;
        out_color_32_normalized_ref.green = in_color_32_ref.green;
        out_color_32_normalized_ref.blue  = in_color_32_ref.blue;
        out_color_32_normalized_ref.alpha = in_color_32_ref.alpha;
    }

    const ifb_color_32_t 
    color_32_value(
        const ifb_color_32_format_t color_32_format, 
              IFBEngineColor32&     color_32_ref) {

        ifb_color_32_t color_32;
        
        switch (color_32_format) {

            case IFBEngineColorFormat_RGBA: color_32 = (color_32_ref.red   << 24) | (color_32_ref.green << 16) | (color_32_ref.blue  << 8) | (color_32_ref.alpha); break;
            case IFBEngineColorFormat_ARGB: color_32 = (color_32_ref.alpha << 24) | (color_32_ref.red   << 16) | (color_32_ref.green << 8) | (color_32_ref.blue);  break;
            case IFBEngineColorFormat_ABGR: color_32 = (color_32_ref.alpha << 24) | (color_32_ref.blue  << 16) | (color_32_ref.green << 8) | (color_32_ref.red);   break;
            case IFBEngineColorFormat_BGRA: color_32 = (color_32_ref.blue  << 24) | (color_32_ref.green << 16) | (color_32_ref.red   << 8) | (color_32_ref.alpha); break;
        }
    
        return(color_32);
    }
};

#endif //IFB_ENGINE_COLOR_HPP     
