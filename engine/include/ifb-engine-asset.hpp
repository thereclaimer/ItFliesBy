#ifndef IFB_ENGINE_ASSET_HPP
#define IFB_ENGINE_ASSET_HPP

#include <r-libs.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef ifb_index IFBEngineAssetId;
typedef ifb_index IFBEngineAssetFileId;

typedef ifb_index IFBEngineAssetTableIndexFile;
typedef ifb_index IFBEngineAssetTableIndexHeader;
typedef ifb_index IFBEngineAssetTableIndexDataBlock;

struct IFBEngineAsset;

/**********************************************************************************/
/* ASSET FILES                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_ASSET_FILE_PATH_SHADERS "ItFliesBy.Assets.Shaders.ifb"
#define IFB_ENGINE_ASSET_FILE_PATH_IMAGES  "ItFliesBy.Assets.Images.ifb"
#define IFB_ENGINE_ASSET_FILE_PATH_SOUNDS  "ItFliesBy.Assets.Sounds.ifb"
#define IFB_ENGINE_ASSET_FILE_PATH_DIALOG  "ItFliesBy.Assets.Dialog.ifb"

enum IFBEngineAssetFileId_ {
    IFBEngineAssetFileId_Shaders = 0,
    IFBEngineAssetFileId_Images  = 1,
    IFBEngineAssetFileId_Sounds  = 2,
    IFBEngineAssetFileId_Dialog  = 3,
    IFBEngineAssetFileId_Count   = 4
};

/**********************************************************************************/
/* ASSET FILES                                                                    */
/**********************************************************************************/

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

enum IFBEngineAssetShaderId_ {
    IFBEngineAssetShaderId_SolidQuadStageVertex      = 0,
    IFBEngineAssetShaderId_SolidQuadStageFragment    = 1,
    IFBEngineAssetShaderId_TexturedQuadStageVertex   = 2,
    IFBEngineAssetShaderId_TexturedQuadStageFragment = 3,
    IFBEngineAssetShaderId_Count                     = 4,
};

/**********************************************************************************/
/* ASSET                                                                          */
/**********************************************************************************/

struct IFBEngineAsset {
    ifb_u32 header_index;
    ifb_u32 file_index;
    ifb_u32 data_index;
};

namespace ifb_engine {

    ifb_api const ifb_b8     asset_is_valid                   (const IFBEngineAssetId asset_id);
    ifb_api const ifb_b8     asset_data_is_loaded             (const IFBEngineAssetId asset_id);
    ifb_api const ifb_size   asset_data_size                  (const IFBEngineAssetId asset_id);
    ifb_api const ifb_memory asset_data_load                  (const IFBEngineAssetId asset_id);
    ifb_api const ifb_memory asset_data_unload                (const IFBEngineAssetId asset_id);
    ifb_api const ifb_timems asset_data_time_ms_last_accessed (const IFBEngineAssetId asset_id);
    ifb_api const ifb_timems asset_data_time_ms_loaded        (const IFBEngineAssetId asset_id);
};

#endif //IFB_ENGINE_ASSET_HPP