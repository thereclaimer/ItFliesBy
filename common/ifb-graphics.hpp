#ifndef IFB_GRAPHICS_HPP
#define IFB_GRAPHICS_HPP

#include "ifb-types.hpp"
#include "ifb-macros.hpp"

struct IFBDimensions {
    ifb_u32 width;
    ifb_u32 height;
};

struct IFBPosition {
    ifb_u32 x;
    ifb_u32 y;
};

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

typedef ifb_u32 IFBResolutionType;

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
    IFBResolutionType type;
    ifb_u32           width;
    ifb_u32           height;
};

const IFBResolution IFB_RESOLUTION_LOOKUP[] = {
    { IFBResolutionType_16_x_9_HD_720p_1280_x_720,             1280, 720  },
    { IFBResolutionType_16_x_9_Full_HD_1080p_1920_x_1080,      1920, 1080 },
    { IFBResolutionType_16_x_9_Quad_HD_1440p_2560_x_1440,      2560, 1440 },
    { IFBResolutionType_16_x_9_Ultra_HD_4K_3840_x_2160,        3840, 2160 },
    { IFBResolutionType_16_x_9_Ultra_HD_8K_7680_x_4320,        7680, 4320 },
    { IFBResolutionType_16_x_9_HD_Variant_0_1600_x_900,        1600, 900  },
    { IFBResolutionType_16_x_9_HD_Variant_1_1366_x_768,        1366, 768  },
    { IFBResolutionType_16_x_10_WXGA_1280_x_800,               1280, 800  },
    { IFBResolutionType_16_x_10_WSXGA_plus_1680_x_1050,        1680, 1050 },
    { IFBResolutionType_16_x_10_WUXGA_1920_x_1200,             1920, 1200 },
    { IFBResolutionType_16_x_10_WQXGA_2560_x_1600,             2560, 1600 },
    { IFBResolutionType_16_x_10_4K_UW_3840_x_2400,             3840, 2400 },
    { IFBResolutionType_21_x_9_Ultrawide_Full_HD_2560_x_1080,  2560, 1080 },
    { IFBResolutionType_21_x_9_Ultrawide_Quad_HD_3440_x_1440,  3440, 1440 },
    { IFBResolutionType_21_x_9_Ultrawide_Variants_3840_x_1600, 3840, 1600 },
    { IFBResolutionType_21_x_9_Ultrawide_4K_5120_x_2160,       5120, 2160 },
    { IFBResolutionType_4_x_3_VGA_640_x_480,                   640,  480  },
    { IFBResolutionType_4_x_3_SVGA_800_x_600,                  800,  600  },
    { IFBResolutionType_4_x_3_XGA_1024_x_768,                  1024, 768  },
    { IFBResolutionType_4_x_3_SXGA_1280_x_960,                 1280, 960  },
    { IFBResolutionType_4_x_3_UXGA_1600_x_1200,                1600, 1200 }
};


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

    inline ifb_void
    resolution_default_from_aspect_ratio(
        const IFBAspectRatioType  in_aspect_ratio_type,        
              IFBResolution&     out_resolution_ref) {

        const IFBResolutionType resolution_type = ifb_common::resolution_default_type_from_aspect_ratio(in_aspect_ratio_type);

        out_resolution_ref = (resolution_type >= IFBResolutionType_Count)
            ? IFB_RESOLUTION_LOOKUP[IFB_RESOLUTION_TYPE_DEFAULT]
            : IFB_RESOLUTION_LOOKUP[resolution_type];
    }
};

struct IFBMonitor {
    IFBPosition        desktop_origin;
    IFBDimensions      dimensions;
    IFBAspectRatioType aspect_ratio;
    ifb_u32            refresh_hz;
    ifb_handle         platform_handle;
    IFBIDMonitor       id;
};

namespace ifb_common {

    inline const ifb_b8
    monitor_has_primary_origin(
        const IFBMonitor* monitor_ptr) {

        // we have found the primary origin if the coordinates are (0,0)
        const ifb_b8 result = (
            monitor_ptr->desktop_origin.x == 0 &&
            monitor_ptr->desktop_origin.y == 0);
    
        return(result);
    }

    inline const IFBMonitor*
    monitor_find_primary(
        const ifb_u32     monitor_count,
        const IFBMonitor* monitor_array_ptr) {

        //sanity check
        if (
            monitor_count     == 0 ||
            monitor_array_ptr == NULL) {

            return(NULL);
        }

        ifb_b8  primary_monitor_found = false;
        ifb_u32 primary_monitor_index = 0;

        //iterate through the monitor array and find the primary
        for (
            ifb_u32 monitor_index = 0;
                    monitor_index < monitor_count;
                  ++monitor_index) {
                
            if (ifb_common::monitor_has_primary_origin(&monitor_array_ptr[monitor_index])) {
                
                // there should only be one, or something was set up incorrectly
                if (primary_monitor_found) {
                    return(NULL);
                }

                primary_monitor_found = true;
                primary_monitor_index = monitor_index;
            }
        }

        const IFBMonitor* primary_monitor_ptr = primary_monitor_found
            ? &monitor_array_ptr[primary_monitor_index]
            : NULL;

        return(primary_monitor_ptr);
    }
};

enum IFBWindowFlags_ {
    IFBWindowFlags_None    = 0,
    IFBWindowFlags_Visible = (1 << 0),
    IFBWindowFlags_ImGui   = (1 << 1),
    IFBWindowFlags_OpenGL  = (1 << 2)
};

typedef ifb_u32 IFBWindowFlags;

struct IFBWindow {
    IFBResolution      resolution;
    IFBWindowFlags     flags;
    IFBPosition        position;
    IFBAspectRatioType aspect_ratio;
    IFBIDMonitor       monitor_id;
};

namespace ifb_common {

    inline ifb_void
    window_set_resolution_based_on_monitor_aspect_ratio(
              IFBWindow*  window_ptr,
        const IFBMonitor* monitor_ptr) {

        ifb_common::resolution_default_from_aspect_ratio(
            monitor_ptr->aspect_ratio,
            window_ptr->resolution);
    }

    inline ifb_void 
    window_set_position_to_monitor_center(
              IFBWindow*  window_ptr,
        const IFBMonitor* monitor_ptr) {

        //calculate the position for centering the window
        window_ptr->position.x = (monitor_ptr->dimensions.width  - window_ptr->resolution.width)  / 2;
        window_ptr->position.y = (monitor_ptr->dimensions.height - window_ptr->resolution.height) / 2;
    }

    inline const ifb_b8 window_flags_is_visible (const IFBWindowFlags window_flags) { return(window_flags & IFBWindowFlags_Visible); }
    inline const ifb_b8 window_flags_use_imgui  (const IFBWindowFlags window_flags) { return(window_flags & IFBWindowFlags_ImGui);   }
    inline const ifb_b8 window_flags_use_opengl (const IFBWindowFlags window_flags) { return(window_flags & IFBWindowFlags_OpenGL);  }
};


#endif //IFB_GRAPHICS_HPP