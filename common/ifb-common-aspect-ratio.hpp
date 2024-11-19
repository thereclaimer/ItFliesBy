#ifndef IFB_COMMON_ASPECT_RATIO_HPP
#define IFB_COMMON_ASPECT_RATIO_HPP

#include "ifb-common-types.hpp"

enum IFBAspectRatioType_ {
    IFBAspectRatioType_16_x_9  = 0,
    IFBAspectRatioType_16_x_10 = 1,
    IFBAspectRatioType_21_x_9  = 2,
    IFBAspectRatioType_4_x_3   = 3,
    IFBAspectRatioType_Count   = 4
};

#define IFB_ASPECT_RATIO_TYPE_DEFAULT IFBAspectRatioType_16_x_9

const ifb_f32_t IFB_ASPECT_RATIO_VALUE_LOOKUP[] = {
    16.0f /  9.0f, // IFBAspectRatioType_16_x_9
    16.0f / 10.0f, // IFBAspectRatioType_16_x_10
    21.0f /  9.0f, // IFBAspectRatioType_21_x_9
     4.0f /  3.0f, // IFBAspectRatioType_4_x_3
};

const ifb_cstr_p IFB_ASPECT_RATIO_DESCRIPTION_LOOKUP[] = {
    "16:9", // IFBAspectRatio_16_x_9
    "16:10",// IFBAspectRatio_16_x_10
    "21:9", // IFBAspectRatio_21_x_9
    "4:3"   // IFBAspectRatio_4_x_3
};

typedef ifb_u32_t ifb_aspect_ratio_type_u32_t;

namespace ifb_engine {

    inline const ifb_aspect_ratio_type_u32_t
    aspect_ratio_lookup(
        const ifb_u32_t width,
        const ifb_u32_t height) {

        const ifb_f32_t aspect_ratio_value = (ifb_f32_t)width / (ifb_f32_t)height;

        for (
            ifb_aspect_ratio_type_u32_t ratio_index = 0;
            ratio_index < IFBAspectRatioType_Count;
            ++ratio_index) {

            const ifb_f32_t lookup = IFB_ASPECT_RATIO_VALUE_LOOKUP[ratio_index]; 

            if (aspect_ratio_value == lookup) {
                return(ratio_index);
            }                    
        }

        return(IFB_ASPECT_RATIO_TYPE_DEFAULT);
    }
};



#endif //IFB_COMMON_ASPECT_RATIO_HPP