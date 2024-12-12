#ifndef IFB_ASPECT_RATIO_HPP
#define IFB_ASPECT_RATIO_HPP

#include "ifb-types.hpp"

enum IFBAspectRatioType_ {
    IFBAspectRatioType_16_x_9  = 0,
    IFBAspectRatioType_16_x_10 = 1,
    IFBAspectRatioType_21_x_9  = 2,
    IFBAspectRatioType_4_x_3   = 3,
    IFBAspectRatioType_Count   = 4
};

#define IFB_ASPECT_RATIO_TYPE_DEFAULT IFBAspectRatioType_16_x_9

const ifb_f32 IFB_ASPECT_RATIO_VALUE_LOOKUP[] = {
    16.0f /  9.0f, // IFBAspectRatioType_16_x_9
    16.0f / 10.0f, // IFBAspectRatioType_16_x_10
    21.0f /  9.0f, // IFBAspectRatioType_21_x_9
     4.0f /  3.0f, // IFBAspectRatioType_4_x_3
};

const ifb_cstr IFB_ASPECT_RATIO_DESCRIPTION_LOOKUP[] = {
    "16:9",  // IFBAspectRatio_16_x_9
    "16:10", // IFBAspectRatio_16_x_10
    "21:9",  // IFBAspectRatio_21_x_9
    "4:3"    // IFBAspectRatio_4_x_3
};

typedef ifb_u32 IFBAspectRatioType;

namespace ifb_common {

    inline const IFBAspectRatioType
    aspect_ratio_lookup(
        const ifb_u32 width,
        const ifb_u32 height) {

        const ifb_f32 aspect_ratio_value = (ifb_f32)width / (ifb_f32)height;

        for (
            IFBAspectRatioType ratio_index = 0;
            ratio_index < IFBAspectRatioType_Count;
            ++ratio_index) {

            const ifb_f32 lookup = IFB_ASPECT_RATIO_VALUE_LOOKUP[ratio_index]; 

            if (aspect_ratio_value == lookup) {
                return(ratio_index);
            }                    
        }

        return(IFB_ASPECT_RATIO_TYPE_DEFAULT);
    }

    inline const ifb_cstr
    aspect_ratio_description(
        const IFBAspectRatioType aspect_ratio_type) {

        const ifb_cstr aspect_ratio_description = (aspect_ratio_type >= IFBAspectRatioType_Count)
            ? IFB_ASPECT_RATIO_DESCRIPTION_LOOKUP[IFB_ASPECT_RATIO_TYPE_DEFAULT]
            : IFB_ASPECT_RATIO_DESCRIPTION_LOOKUP[aspect_ratio_type];

        return(aspect_ratio_description);
    }
};



#endif //IFB_ASPECT_RATIO_HPP