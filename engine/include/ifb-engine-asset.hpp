#ifndef IFB_ENGINE_ASSET_HPP
#define IFB_ENGINE_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

#define IFB_ENGINE_ASSET_FILE_PATH_SHADERS "ItFliesBy.Assets.Shaders.ifb"
#define IFB_ENGINE_ASSET_FILE_PATH_IMAGES  "ItFliesBy.Assets.Images.ifb"

enum IFBEngineAssetFileId_ {
    IFBEngineAssetFileId_Shaders = 0,
    IFBEngineAssetFileId_Images  = 1,
    IFBEngineAssetFileId_Count   = 2
};

typedef ifb_index  IFBEngineAssetFileId;
typedef ifb_index  IFBEngineAssetId;
typedef ifb_handle IFBEngineAssetHandle;


enum IFBEngineAssetId_ {
    
    //----------------
    // shaders
    //----------------
    IFBEngineAssetId_Shader_SolidQuadStageVertex      = 0x00000000, 
    IFBEngineAssetId_Shader_SolidQuadStageFragment    = 0x00000001,
    IFBEngineAssetId_Shader_TexturedQuadStageVertex   = 0x00000002, 
    IFBEngineAssetId_Shader_TexturedQuadStageFragment = 0x00000003,
    
    //----------------
    // images
    //----------------
    IFBEngineAssetId_Image_CalibrationConnor          = 0x00010004,
    IFBEngineAssetId_Image_CalibrationJig             = 0x00010005,

    //count
    IFBEngineAssetId_Count                            = 6
};

struct IFBEngineAssetSystemInfo {

    struct {
        ifb_size size_total;
        ifb_size size_used;
        ifb_size block_size;
        ifb_size blocks_committed;
    } data_region;

    struct {
        ifb_size row_count_file;
        ifb_size row_count_index;
        ifb_size row_count_data;
    } tables;
};

namespace ifb_engine {

    r_external const IFBEngineAssetHandle asset_load   (const IFBEngineAssetId     asset_id);
    r_external const ifb_b8               asset_unload (const IFBEngineAssetHandle asset_handle);

    r_external const ifb_void asset_system_info (IFBEngineAssetSystemInfo& asset_system_info_ref);
};



#endif //IFB_ENGINE_ASSET_HPP