#ifndef ITFLIESBY_ASSET_FILE_BUILDER_HPP
#define ITFLIESBY_ASSET_FILE_BUILDER_HPP

#include <Windows.h>

#include <itfliesby.hpp>
#include <math/itfliesby-math.hpp>

#define ITFLIESBY_ASSET_FILE_BUILDER_MEMORY_SIZE ITFLIESBY_MATH_GIGABYTES(2)

#define itfliesby_asset_file_builder_main WINAPI wWinMain

typedef void* asset_handle;
typedef void* file_handle;
typedef byte* mem_data;


#define ITFLIESBY_ASSET_FILE_VERIFICATION_STR "IFB"
#define ITFLIESBY_ASSET_FILE_EXTENSION        "ifb"


enum ItfliesbyAssetFileBuilderReturnCode {
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_SUCCESS                   = 0x00000000,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_MEMORY_ALLOCATION_ERROR   = 0x80000000,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_INVALID_ARGUMENTS         = 0x80000001,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_INVALID_INPUT_FILE        = 0x80000002,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_OUT_OF_MEMORY             = 0x80000003,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_CSV_READ_FAILURE          = 0x80000004,
    ITFLIESBY_ASSET_FILE_BUILDER_RETURN_CODE_ASSET_FILE_CREATE_FAILURE = 0x80000005,
};

enum ItfliesbyAssetFileBuilderAssetFileType : s32 {
    ITFLIESBY_ASSET_FILE_BUILDER_ASSET_FILE_TYPE_TEXT  = 0,
    ITFLIESBY_ASSET_FILE_BUILDER_ASSET_FILE_TYPE_IMAGE = 1,
    ITFLIESBY_ASSET_FILE_BUILDER_ASSET_FILE_TYPE_MODEL = 2,
};

struct ItfliesbyAssetFileBuilderArguments {
    char path_to_csv[128];
    char path_to_asset_file[128];
};

struct ItfliesbyAssetFileBuilderMemoryBlock {
    u64      allocation_size;
    u64      data_size;
    mem_data data;
    ItfliesbyAssetFileBuilderMemoryBlock* next;
};

struct ItfliesbyAssetFileBuilderCsvEntry {
    char                                   asset_path[128];
    char                                   asset_tag[32];
    ItfliesbyAssetFileBuilderAssetFileType asset_type;
};

struct ItfliesbyAssetFileBuilderCsvFile {
    asset_handle                          file_handle;   
    u32                                   num_entries;
    u64                                   file_size;
    str                                   buffer;
    ItfliesbyAssetFileBuilderMemoryBlock* memory;
    ItfliesbyAssetFileBuilderCsvEntry*    entries;
};

struct ItfliesbyAssetFileindex {
    char tag[32];         // plaintext identifier for the entity the asset belongs to
    u32  file_size;       // size of the data is stored in the file
    u32  allocation_size; // the size of the space we need to allocate when storing the asset data in memory
    u32  offset;          // the index of the first byte of asset data in the file
};

struct ItfliesbyAssetFileHeader {
    char                     verfication[3];
    u16                      num_indexs;
    ItfliesbyAssetFileindex* indexes;
};

struct ItfliesbyAssetsGameAssetFile {
    file_handle              file_handle;
    ItfliesbyAssetFileHeader file_header;
};


struct ItfliesbyAssetFileBuilder {
    HANDLE                                console_handle;
    mem_data                              memory;
    ItfliesbyAssetFileBuilderArguments    arguments;
    ItfliesbyAssetFileBuilderCsvFile      csv_file;
    ItfliesbyAssetsGameAssetFile          asset_file;
    ItfliesbyAssetFileBuilderMemoryBlock* allocated_memory;
    ItfliesbyAssetFileBuilderMemoryBlock* index_memory;
    mem_data                              header_data;
};

#endif //ITFLIESBY_ASSET_FILE_BUILDER_HPP