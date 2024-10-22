#pragma once

#include "ifb-engine-internal-tools.hpp"
#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-platform.hpp"

ifb_internal const ifb_b8 
ifb_engine::tools_asset_file_builder_render(
    IFBEngineToolsAssetFileBuilder& asset_file_builder_ref) {

    //if the window isn't open, we're done
    if (!asset_file_builder_ref.open) {
        return(true);
    }

    //window start
    if (!ImGui::Begin("Asset File Builder",(bool*)&asset_file_builder_ref.open)) {
        return(false);
    }


    const ifb_cstr asset_file_names[] = {
        "Shaders",
        "Images",
        "Sounds",
        "Dialog"
    };

    const ifb_cstr combo_preview = asset_file_builder_ref.selected_file
        ? asset_file_names[asset_file_builder_ref.selected_file_id]
        : "Select Asset File";

    if (ImGui::BeginCombo("Asset File Type",combo_preview)) {

        for (
            IFBEngineAssetFileId file_id = 0;
            file_id < IFBEngineAssetFileId_Count;
            ++file_id) {

            const ifb_cstr current_file_name = asset_file_names[file_id]; 

            if (ImGui::Selectable(current_file_name)) {
                asset_file_builder_ref.selected_file    = true;
                asset_file_builder_ref.selected_file_id = file_id;
            }

            if (
                asset_file_builder_ref.selected_file && 
                asset_file_builder_ref.selected_file_id == file_id) {
                
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    //if we don't have a selected file, we're done
    if (!asset_file_builder_ref.selected_file) {

        //window end
        ImGui::End();
        return(true);
    }
    
    //otherwise, get the info for the selected file
    IFBEngineToolsAssetFileBuilderCsv asset_csv_file;
    ifb_b8 result = ifb_engine::tools_asset_file_builder_get_csv(
        asset_file_builder_ref,
        asset_csv_file);

    if (!result) {
        return(false);
    }

    //window end
    ImGui::End();

    //we're done
    return(true);
}

ifb_internal const ifb_b8
ifb_engine::tools_asset_file_builder_get_csv(
    IFBEngineToolsAssetFileBuilder&     in_asset_file_builder_ref,
    IFBEngineToolsAssetFileBuilderCsv& out_asset_file_builder_csv) {

    //cache the file id, which is also the asset file id
    const IFBEngineAssetFileId selected_file_id = in_asset_file_builder_ref.selected_file_id; 
    out_asset_file_builder_csv.asset_file_id    = selected_file_id;

    //otherwise, make sure we have a region
    if (!in_asset_file_builder_ref.file_table.region) {

        in_asset_file_builder_ref.file_table.region = 
            ifb_engine::core_memory_create_arena_pool(
                IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_FILE_REGION_NAME,
                IFB_ENGINE_TOOLS_ASSET_FILE_BUILDER_FILE_REGION_ARENA_SIZE,
                IFBEngineAssetFileId_Count);

        if (!in_asset_file_builder_ref.file_table.region) {
            return(false);
        }
    }

    //make sure that we have an arena for the file
    if (in_asset_file_builder_ref.file_table.file_arena[selected_file_id]) {
        
        //we have an arena, we know the file is also open
        out_asset_file_builder_csv.csv_file_arena = in_asset_file_builder_ref.file_table.file_arena[selected_file_id];
        out_asset_file_builder_csv.csv_file_index = in_asset_file_builder_ref.file_table.file_index[selected_file_id];
    }
    //otherwise, we need to commit one
    else {

        //commit the arena
        const RMemoryArenaHandle arena_handle = r_mem::arena_commit(in_asset_file_builder_ref.file_table.region);
        if (!arena_handle) {
            return(false);
        }

        //if we didn't have an arena, we know its not open
        const ifb_cstr path = ifb_engine::tools_asset_file_builder_lookup_path(selected_file_id);
        if (!path) {
            return(false);
        }

        //attempt to open the file
        IFBEnginePlatformFileIndex file_index;
        ifb_b8 file_open = ifb_engine::platform_file_open_read_write(path, file_index);
        if (!file_open) {
            return(false);
        }

        //read the file into the arena
        const ifb_size file_size = ifb_engine::platform_file_size(file_index);
        ifb_memory file_memory   = r_mem::arena_push(arena_handle,file_size);
        ifb_b8 file_read = ifb_engine::platform_file_read(
            file_index,
            0,
            file_size,
            file_memory);

        if (!file_read) {
            return(false);
        }

        //set the csv file arena and index
        out_asset_file_builder_csv.csv_file_arena = arena_handle;
        out_asset_file_builder_csv.csv_file_index = file_index;
        
        //update the table
        in_asset_file_builder_ref.file_table.file_arena[selected_file_id] = arena_handle;
        in_asset_file_builder_ref.file_table.file_index[selected_file_id] = file_index;
    }
    
    //we're done
    return(true);
}