#ifndef IFB_COLOR_HPP
#define IFB_COLOR_HPP

#include "ifb-types.hpp" 

/**********************************************************************************/
/* COLOR 32                                                                       */
/**********************************************************************************/

enum IFBColor32FormatType_ {
    IFBColor32FormatType_RGBA = 0,
    IFBColor32FormatType_ARGB = 1,
    IFBColor32FormatType_ABGR = 2,
    IFBColor32FormatType_BGRA = 3
};

struct IFBColor32 {
    ifb_u8 red;
    ifb_u8 green;
    ifb_u8 blue;
    ifb_u8 alpha;
};

struct IFBColor32Normalized {
    ifb_f32 red;
    ifb_f32 green;
    ifb_f32 blue;
    ifb_f32 alpha;
};

typedef ifb_u32 IFBColor32FormatType;
typedef ifb_u32 ifb_color_32_hex_t;

namespace ifb_common {

    inline ifb_void
    color_32_normalize(
        IFBColor32&            in_color_32_ref,
        IFBColor32Normalized& out_color_32_normalized_ref) {

        out_color_32_normalized_ref.red   = in_color_32_ref.red;
        out_color_32_normalized_ref.green = in_color_32_ref.green;
        out_color_32_normalized_ref.blue  = in_color_32_ref.blue;
        out_color_32_normalized_ref.alpha = in_color_32_ref.alpha;
    }

    inline const ifb_color_32_hex_t 
    color_32_hex_value(
        const IFBColor32FormatType color_32_format, 
              IFBColor32&          color_32_ref) {

        ifb_color_32_hex_t color_32_hex;
        
        switch (color_32_format) {

            case IFBColor32FormatType_RGBA: color_32_hex = (color_32_ref.red   << 24) | (color_32_ref.green << 16) | (color_32_ref.blue  << 8) | (color_32_ref.alpha); break;
            case IFBColor32FormatType_ARGB: color_32_hex = (color_32_ref.alpha << 24) | (color_32_ref.red   << 16) | (color_32_ref.green << 8) | (color_32_ref.blue);  break;
            case IFBColor32FormatType_ABGR: color_32_hex = (color_32_ref.alpha << 24) | (color_32_ref.blue  << 16) | (color_32_ref.green << 8) | (color_32_ref.red);   break;
            case IFBColor32FormatType_BGRA: color_32_hex = (color_32_ref.blue  << 24) | (color_32_ref.green << 16) | (color_32_ref.red   << 8) | (color_32_ref.alpha); break;
        }
    
        return(color_32_hex);
    }
};


#endif //IFB_COLOR_HPP