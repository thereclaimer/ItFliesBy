#ifndef IFB_COMMON_RESOLUTION_HPP
#define IFB_COMMON_RESOLUTION_HPP

#include "ifb-common-types.hpp"
#include "ifb-common-aspect-ratio.hpp"

enum IFBResolutionType_ {
	IFBResolutionType_16_x_9_HD_720p_1280_x_720             = 0,
	IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080      = 1,
	IFBResolutionType_16_x_9_Quad_HD_1440p_2560_x_1440      = 2,
	IFBResolutionType_16_x_9_Ultra_HD_4K_3840_x_2160        = 3,
	IFBResolutionType_16_x_9_Ultra_HD_8K_7680_x_4320        = 4,
	IFBResolutionType_16_x_9_HD_Variant_0_1600_x_900        = 5,
	IFBResolutionType_16_x_9_HD_Variant_1_1366_x_768        = 6,
    IFBResolutionType_16_x_10_WXGA_1280_x_800               = 7,
    IFBResolutionType_16_x_10_WSXGA_plus_1680_x_1050        = 8,
    IFBResolutionType_16_x_10_WUXGA_1920_x_1200             = 9,
    IFBResolutionType_16_x_10_WQXGA_2560_x_1600             = 10,
    IFBResolutionType_16_x_10_4K_UW_3840_x_2400             = 11,
    IFBResolutionType_21_x_9_Ultrawide_Full_HD_2560_x_1080  = 12,
    IFBResolutionType_21_x_9_Ultrawide_Quad_HD_3440_x_1440  = 13,
    IFBResolutionType_21_x_9_Ultrawide_Variants_3840_x_1600 = 14,
    IFBResolutionType_21_x_9_Ultrawide_4K_5120_x_2160       = 15,
    IFBResolutionType_4_x_3_VGA_640_x_480                   = 16,	
    IFBResolutionType_4_x_3_SVGA_800_x_600                  = 17,	
    IFBResolutionType_4_x_3_XGA_1024_x_768                  = 18,	
    IFBResolutionType_4_x_3_SXGA_1280_x_960                 = 19,	
    IFBResolutionType_4_x_3_UXGA_1600_x_1200                = 20,	
    IFBResolutionType_Count                                 = 21,	
};

#define IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_16_x_9   IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080
#define IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_16_x_10  IFBResolutionType_16_x_10_WUXGA_1920_x_1200
#define IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_21_x_9   IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080
#define IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_4_x_3    IFBResolutionType_4_x_3_XGA_1024_x_768
#define IFB_RESOLUTION_TYPE_DEFAULT                           IFBResolutionType_4_x_3_XGA_1024_x_768

const IFBResolutionType_ IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_LOOKUP[] = {
    IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_16_x_9,  // IFBAspectRatioType_16_x_9
    IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_16_x_10, // IFBAspectRatioType_16_x_10
    IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_21_x_9,  // IFBAspectRatioType_21_x_9
    IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_4_x_3    // IFBAspectRatioType_4_x_3
};

const ifb_cstr IFB_RESOLUTION_DESCRIPTION_LOOKUP[] = {
    "HD (720p)",                  // IFBResolutionType_16_x_9_HD_720p_1280_x_720
    "Full HD (1080p)",            // IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080
    "Quad HD (QHD, 1440p)",       // IFBResolutionType_16_x_9_Quad_HD_1440p_2560_x_1440
    "Ultra HD (4K)",              // IFBResolutionType_16_x_9_Ultra_HD_4K_3840_x_2160
    "8K UHD",                     // IFBResolutionType_16_x_9_Ultra_HD_8K_7680_x_4320
    "HD Variant 0",               // IFBResolutionType_16_x_9_HD_Variant_0_1600_x_900
    "HD Variant 1",               // IFBResolutionType_16_x_9_HD_Variant_1_1366_x_768
    "WXGA",                       // IFBResolutionType_16_x_10_WXGA_1280_x_800
    "WSXGA+",                     // IFBResolutionType_16_x_10_WSXGA_plus_1680_x_1050
    "WUXGA",                      // IFBResolutionType_16_x_10_WUXGA_1920_x_1200
    "WQXGA",                      // IFBResolutionType_16_x_10_WQXGA_2560_x_1600
    "4K UW (Ultra-Wide)",         // IFBResolutionType_16_x_10_4K_UW_3840_x_2400
    "Ultrawide Full HD (UW-FHD)", // IFBResolutionType_21_x_9_Ultrawide_Full_HD_2560_x_1080
    "Ultrawide Quad HD (UW-QHD)", // IFBResolutionType_21_x_9_Ultrawide_Quad_HD_3440_x_1440
    "Ultrawide Variants",         // IFBResolutionType_21_x_9_Ultrawide_Variants_3840_x_1600
    "Ultrawide 4K",               // IFBResolutionType_21_x_9_Ultrawide_4K_5120_x_2160
    "VGA",                        // IFBResolutionType_4_x_3_VGA_640_x_480
    "SVGA",                       // IFBResolutionType_4_x_3_SVGA_800_x_600
    "XGA",                        // IFBResolutionType_4_x_3_XGA_1024_x_768
    "SXGA (Standard)",            // IFBResolutionType_4_x_3_SXGA_1280_x_960
    "UXGA"                        // IFBResolutionType_4_x_3_UXGA_1600_x_1200
};

struct IFBResolution {
    ifb_u32 width;
    ifb_u32 height;
};

const IFBResolution IFB_RESOLUTION_LOOKUP[] = {
    {1280, 720},  // IFBResolutionType_16_x_9_HD_720p_1280_x_720
    {1920, 1080}, // IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080
    {2560, 1440}, // IFBResolutionType_16_x_9_Quad_HD_1440p_2560_x_1440
    {3840, 2160}, // IFBResolutionType_16_x_9_Ultra_HD_4K_3840_x_2160
    {7680, 4320}, // IFBResolutionType_16_x_9_Ultra_HD_8K_7680_x_4320
    {1600, 900},  // IFBResolutionType_16_x_9_HD_Variant_0_1600_x_900
    {1366, 768},  // IFBResolutionType_16_x_9_HD_Variant_1_1366_x_768
    {1280, 800},  // IFBResolutionType_16_x_10_WXGA_1280_x_800
    {1680, 1050}, // IFBResolutionType_16_x_10_WSXGA_plus_1680_x_1050
    {1920, 1200}, // IFBResolutionType_16_x_10_WUXGA_1920_x_1200
    {2560, 1600}, // IFBResolutionType_16_x_10_WQXGA_2560_x_1600
    {3840, 2400}, // IFBResolutionType_16_x_10_4K_UW_3840_x_2400
    {2560, 1080}, // IFBResolutionType_21_x_9_Ultrawide_Full_HD_2560_x_1080
    {3440, 1440}, // IFBResolutionType_21_x_9_Ultrawide_Quad_HD_3440_x_1440
    {3840, 1600}, // IFBResolutionType_21_x_9_Ultrawide_Variants_3840_x_1600
    {5120, 2160}, // IFBResolutionType_21_x_9_Ultrawide_4K_5120_x_2160
    {640,  480},  // IFBResolutionType_4_x_3_VGA_640_x_480
    {800,  600},  // IFBResolutionType_4_x_3_SVGA_800_x_600
    {1024, 768},  // IFBResolutionType_4_x_3_XGA_1024_x_768
    {1280, 960},  // IFBResolutionType_4_x_3_SXGA_1280_x_960
    {1600, 1200}  // IFBResolutionType_4_x_3_UXGA_1600_x_1200
};

typedef ifb_u32 IFBResolutionType;

namespace ifb_common {

    inline const ifb_cstr
    resolution_description(
        const IFBResolutionType resolution_type) {

        const ifb_cstr resolution_description = (resolution_type >= IFBResolutionType_Count) 
            ? IFB_RESOLUTION_DESCRIPTION_LOOKUP[IFB_RESOLUTION_TYPE_DEFAULT] 
            : IFB_RESOLUTION_DESCRIPTION_LOOKUP[resolution_type];

        return(resolution_description);
    }

    inline const IFBResolutionType
    resolution_default_type_from_aspect_ratio(
        const IFBAspectRatioType aspect_ratio_type) {

        const IFBResolutionType resolution_type = (aspect_ratio_type >= IFBAspectRatioType_Count)
            ? IFB_RESOLUTION_TYPE_DEFAULT
            : IFB_RESOLUTION_TYPE_DEFAULT_FOR_ASPECT_RATIO_LOOKUP[aspect_ratio_type];      

        return(resolution_type);
    }
  
    inline ifb_void
    resolution_dimensions(
        const IFBResolutionType in_resolution_type,
              IFBResolution&   out_resolution_ref) {

        out_resolution_ref = (in_resolution_type >= IFBResolutionType_Count)
            ? IFB_RESOLUTION_LOOKUP[IFB_RESOLUTION_TYPE_DEFAULT]
            : IFB_RESOLUTION_LOOKUP[in_resolution_type];
    }
};

#endif //IFB_COMMON_RESOLUTION_HPP