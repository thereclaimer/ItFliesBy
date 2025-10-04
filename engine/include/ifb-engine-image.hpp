#ifndef IFB_ENG_IMAGE_HPP
#define IFB_ENG_IMAGE_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-file.hpp"

namespace ifb {

    typedef byte eng_img_data_t;

    struct eng_img_t;
    struct eng_img_info_t;
    struct eng_img_buffer_t;

    IFB_ENG_API bool eng_img_get_info (const eng_file_h32_t file_h, eng_img_info_t&   img_info);
    IFB_ENG_API bool eng_img_load     (const eng_file_h32_t file_h, eng_img_buffer_t& img_buffer);

    struct eng_img_buffer_t {
        eng_img_data_t* data;
        u32         size;
        u32         channels;
    };

    struct eng_img_info_t {
        u32 pixel_width;
        u32 pixel_height;
        u32 channel_count;
        u32 mem_size;
    };
};

#endif //IFB_ENG_IMAGE_HPP
