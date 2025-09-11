#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ifb-engine-image.hpp"
namespace ifb {

    IFB_ENG_API bool
    eng_img_get_info(
        const eng_file_h32_t file_h,
        eng_img_info_t&      img_info) {

        return(false);
    }

    IFB_ENG_API bool
    eng_img_load(
        const eng_file_h32_t file_h,
        eng_img_buffer_t&    img_buffer) {

        return(false);
    }
};