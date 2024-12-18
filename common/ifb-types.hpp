#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

//signed integers
typedef int8_t  ifb_s8;
typedef int16_t ifb_s16;
typedef int32_t ifb_s32;
typedef int64_t ifb_s64;

//unsigned integers
typedef uint8_t  ifb_u8;
typedef uint16_t ifb_u16;
typedef uint32_t ifb_u32;
typedef uint64_t ifb_u64;

//floats
typedef float  ifb_f32;
typedef double ifb_f64;

//booleans
typedef int8_t  ifb_b8;
typedef int16_t ifb_b16;
typedef int32_t ifb_b32;
typedef int64_t ifb_b64;

//strings
typedef char     ifb_char;
typedef wchar_t  ifb_wchar;
typedef char*    ifb_cstr;
typedef wchar_t* ifb_wstr;

//memory
typedef void       ifb_void;
typedef void*      ifb_ptr;
typedef uint8_t    ifb_byte;
typedef uint8_t*   ifb_memory;
typedef size_t     ifb_size;
typedef ifb_u32    ifb_index;
typedef ifb_u32    ifb_handle;
typedef intptr_t   ifb_address;
typedef uint32_t   ifb_page;

//time
typedef uint64_t ifb_timems;


/**********************************************************************************/
/* IDENTIFIERS                                                                    */
/**********************************************************************************/

struct IFBID {
    ifb_index index;
};

struct IFBIDTag     : IFBID { };
struct IFBIDCommit  : IFBID { };
struct IFBIDArena   : IFBID { };
struct IFBIDMonitor : IFBID { };

//handle
struct IFBHND {
    ifb_u32 offset;
};

//global handle
struct IFBGHND {
    ifb_u32 offset;
};

struct IFBHNDLinearAllocator : IFBHND { };
struct IFBHNDBlockAllocator  : IFBHND { };

/**********************************************************************************/
/* STRINGS                                                                        */
/**********************************************************************************/

union IFBHash {
    struct {
        ifb_u32 h1;
        ifb_u32 h2;
        ifb_u32 h3;
        ifb_u32 h4;
    };
    ifb_u32 h[4];
};

/**********************************************************************************/
/* MISC                                                                           */
/**********************************************************************************/

struct IFBDimensions {
    ifb_u32 width;
    ifb_u32 height;
};

struct IFBPosition {
    ifb_u32 x;
    ifb_u32 y;
};

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBMemory {
    ifb_u32 reservation_offset;
};

struct IFBTag {
    IFBID    id;
    ifb_cstr value;
    IFBHash  hash;
};

struct IFBCommit {
    IFBIDCommit id;
    ifb_u32     page_start;
    ifb_u32     page_count;
};

struct IFBArena {
    IFBIDArena id;
    ifb_u32    size;
    ifb_u32    start;
    ifb_cstr   tag_c_str;
};

struct IFBLinearAllocator {
    IFBIDArena arena_id;
    ifb_u32    start;
    ifb_u32    size;
    ifb_u32    position;
    ifb_u32    save_point;
};

struct IFBBlockAllocator {
    IFBIDArena          arena_id;
    ifb_u32             block_size;
    ifb_u32             block_count;
};

/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/


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
    ifb_u32           width;
    ifb_u32           height;
    IFBResolutionType type;
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
};

struct IFBMonitor {
    IFBIDMonitor       id;
    ifb_u32            refresh_hz;
    IFBDimensions      dimensions;
    IFBAspectRatioType aspect_ratio;
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

#endif //IFB_TYPES_HPP
