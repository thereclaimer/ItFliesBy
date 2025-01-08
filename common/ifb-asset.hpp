#ifndef IFB_ASSET_HPP
#ifndef IFB_ASSET_HPP

#include "ifb-types.hpp"
#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

typedef ifb_enum IFBAssetType;

struct IFBAsset;

#define IFB_ASSET_FILE_PATH_TEXT   "ItFliesBy.Asset.Text.ifb"
#define IFB_ASSET_FILE_PATH_SHADER "ItFliesBy.Asset.Shader.ifb"
#define IFB_ASSET_FILE_PATH_IMAGE  "ItFliesBy.Asset.Image.ifb"
#define IFB_ASSET_FILE_PATH_SOUND  "ItFliesBy.Asset.Sound.ifb"

#define IFB_ASSET_TEXT_HELLO_WORLD "TXT-HELLO-WORLD"

#define IFB_ASSET_SHADER_SPRITE_VERTEX   "SHD-SPRITE-VERT"
#define IFB_ASSET_SHADER_SPRITE_FRAGMENT "SHD-SPRITE-FRAG"

#define IFB_ASSET_IMAGE_CONNOR_IDLE_LEFT  "IMG-CNR-IDL-LFT"
#define IFB_ASSET_IMAGE_CONNOR_IDLE_RIGHT "IMG-CNR-IDL-RGT"
#define IFB_ASSET_IMAGE_CONNOR_IDLE_UP    "IMG-CNR-IDL-UP"
#define IFB_ASSET_IMAGE_CONNOR_IDLE_DOWN  "IMG-CNR-IDL-DWN"

#define IFB_ASSET_IMAGE_JIG_IDLE_LEFT     "IMG-JIG-IDL-LFT"
#define IFB_ASSET_IMAGE_JIG_IDLE_RIGHT    "IMG-JIG-IDL-RGT"
#define IFB_ASSET_IMAGE_JIG_IDLE_UP       "IMG-JIG-IDL-UP"
#define IFB_ASSET_IMAGE_JIG_IDLE_DOWN     "IMG-JIG-IDL-DWN"

/**********************************************************************************/
/* ASSET                                                                          */
/**********************************************************************************/

enum IFBAssetType_ {
    IFBAssetType_Text   = 0,
    IFBAssetType_Shader = 1,
    IFBAssetType_Image  = 2,
    IFBAssetType_Sound  = 3,
};

struct IFBAsset78  {
    IFBHash      hash;
    IFBAssetType type;
    ifb_u32      size;
};

struct IFBAssetTable {
    IFBAssetType type;
    ifb_u32      count;
};

struct IFBAssetTableText : IFBAssetTable {

};

#ifndef //IFB_ASSET_HPP