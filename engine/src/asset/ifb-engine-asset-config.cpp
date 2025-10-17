#pragma once

#include "ifb-engine-asset-internal.hpp"

namespace ifb {

    constexpr cchar _xml_cstr_node_ifb_assets [] = "ifb-assets";
    constexpr cchar _xml_cstr_node_text       [] = "text";
    constexpr cchar _xml_cstr_node_image      [] = "image";
    constexpr cchar _xml_cstr_node_sound      [] = "sound";
    constexpr cchar _xml_cstr_node_font       [] = "font";
    constexpr cchar _xml_cstr_node_asset      [] = "asset";

    constexpr cchar _xml_cstr_attrib_name     [] = "name"; 
    constexpr cchar _xml_cstr_attrib_path     [] = "path"; 

    constexpr cchar _xml_cstr_default_config  [] = 
        "<ifb-assets>"
            "<text path=\"../assets/text\">"
            "</text>"
            "<image path=\"../assets/image\">"
            "</image>"
            "<sound path=\"../assets/sound\">"
            "</sound>"
            "<font path=\"../assets/font\">"
            "</font>"
        "</ifb-assets>";

};