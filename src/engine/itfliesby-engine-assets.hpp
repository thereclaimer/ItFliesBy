#ifndef ITFLIESBY_ENGINE_ASSETS_HPP
#define ITFLIESBY_ENGINE_ASSETS_HPP

#include "itfliesby-engine.hpp"

struct ItfliesbyAssetsFileHandles {
    handle shader_asset_file;
};

struct ItfliesbyAssets {
    ItfliesbyAssetsFileHandles file_handles;
};

void
itfliesby_engine_assets_load_files(
    ItfliesbyAssets* assets
);

#endif //ITFLIESBY_ENGINE_ASSETS_HPP
