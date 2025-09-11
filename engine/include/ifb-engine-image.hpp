#ifndef IFB_ENG_IMAGE_HPP
#define IFB_ENG_IMAGE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"

namespace ifb {

    typedef eng_byte eng_img_data_t;
    typedef eng_u32  eng_img_size_u32_t;

    struct eng_img_t;
    struct eng_img_info_t;
    struct eng_img_buffer_t;

    IFB_ENG_API bool eng_img_get_info (const eng_file_h32_t file_h, eng_img_info_t&   img_info);
    IFB_ENG_API bool eng_img_load     (const eng_file_h32_t file_h, eng_img_buffer_t& img_buffer);

    struct eng_img_buffer_t {
        eng_img_data_t*    data;
        eng_img_size_u32_t size;
        eng_img_size_u32_t channels;
    };

    struct eng_img_info_t {
        eng_u32 pixel_width;
        eng_u32 pixel_height;
        eng_u32 channel_count;
        eng_u32 mem_size;
    };
};

#endif //IFB_ENG_IMAGE_HPP
