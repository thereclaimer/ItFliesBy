#ifndef IFB_ENGINE_ASPECT_RATIO_HPP
#define IFB_ENGINE_ASPECT_RATIO_HPP

#include "ifb-engine-types.hpp"

enum IFBEngineAspectRatioType_ {
    IFBEngineAspectRatioType_16_x_9  = 0,
    IFBEngineAspectRatioType_16_x_10 = 1,
    IFBEngineAspectRatioType_21_x_9  = 2,
    IFBEngineAspectRatioType_4_x_3   = 3,
    IFBEngineAspectRatioType_Count   = 4
};

typedef ifb_u32 ifb_aspect_ratio_type_u32t;

const ifb_f32 IFB_ENGINE_ASPECT_RATIO_LOOKUP[] = {
    16.0f /  9.0f,
    16.0f / 10.0f,
    21.0f /  9.0f,
     4.0f /  3.0f,
};

const ifb_cstr IFB_ENGINE_ASPECT_RATIO_DESCRIPTION_LOOKUP[] = {
    "16:9", // IFBEngineAspectRatio_16_x_9
    "16:10",// IFBEngineAspectRatio_16_x_10
    "21:9", // IFBEngineAspectRatio_21_x_9
    "4:3"   // IFBEngineAspectRatio_4_x_3
};



#endif //IFB_ENGINE_ASPECT_RATIO_HPP