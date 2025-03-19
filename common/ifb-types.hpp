#ifndef IFB_TYPES_HPP
#define IFB_TYPES_HPP

#include <cstdint>
#include <xmmintrin.h>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//handles
struct IFBHND8;
struct IFBHND16;
struct IFBHND32;
struct IFBHND64;
struct IFBHNDPTR;

//system
struct IFBSystemInfo;
struct IFBSystemMemory;
struct IFBSystemCPU;

//memory
struct IFBHNDMemoryContext;
struct IFBHNDMemoryReservation;
struct IFBHNDMemoryArena;
struct IFBMemoryContext;
struct IFBMemoryArena;
struct IFBMemoryReservation;

//math
struct IFBVec2;
struct IFBVec3;
struct IFBMat3;
struct IFBPoint;
struct IFBLine;
struct IFBTransform;
struct IFBDimensions;
struct IFBPosition;

//colors
struct IFBColorNormalized;
struct IFBColorHex;
struct IFBColor32;

//files
struct IFBHNDFile;
struct IFBHNDFileTable;
struct IFBFile;
struct IFBFileBuffer;
struct IFBFileContext;
struct IFBFileTableArgs;
struct IFBFileReadOnlyTable;
struct IFBFileReadOnlyRequest;
struct IFBFileReadWriteTable;
struct IFBFileReadWriteRequest;

//memory

/**********************************************************************************/
/* PRIMITIVES                                                                     */
/**********************************************************************************/

//signed integers
typedef int8_t   IFBS8;
typedef int16_t  IFBS16;
typedef int32_t  IFBS32;
typedef int64_t  IFBS64;

//unsigned integ 
typedef uint8_t  IFBU8;
typedef uint16_t IFBU16;
typedef uint32_t IFBU32;
typedef uint64_t IFBU64;

//floats
typedef float    IFBF32;
typedef double   IFBF64;

//booleans
typedef int8_t   IFBB8;
typedef int16_t  IFBB16;
typedef int32_t  IFBB32;
typedef int64_t  IFBB64;

//characters
typedef char     IFBChar;
typedef wchar_t  IFBWChar;

//memory
typedef void     IFBVoid;
typedef void*    IFBPtr;
typedef uint8_t  IFBByte;
typedef size_t   IFBSize;
typedef IFBU32   IFBIndex;
typedef IFBPtr   IFBHandle;
typedef intptr_t IFBAddr;

//time
typedef uint64_t IFBTimems;

/**********************************************************************************/
/* HANDLES                                                                        */
/**********************************************************************************/

struct IFBHND8   { IFBU8  offset;  };
struct IFBHND16  { IFBU16 offset;  };
struct IFBHND32  { IFBU32 offset;  };
struct IFBHND64  { IFBU64 offset;  };
struct IFBHNDPTR { IFBPtr pointer; };

#define IFB_HANDLE_INVALID_U8  0xFF
#define IFB_HANDLE_INVALID_U16 0xFFFF 
#define IFB_HANDLE_INVALID_U32 0xFFFFFFFF 
#define IFB_HANDLE_INVALID_U64 0xFFFFFFFFFFFFFFFF

/**********************************************************************************/
/* SYSTEM                                                                         */
/**********************************************************************************/

struct IFBSystemMemoryInfo {
    IFBU32 page_size;
    IFBU32 allocation_granularity;
};

struct IFBSystemCPUCacheInfo {
    IFBU32 size_total;
    IFBU32 size_line;
};

struct IFBSystemCPUInfo {
    IFBU32                parent_core_number;
    IFBU32                speed_mhz;
    IFBU32                core_count_physical;
    IFBU32                core_count_logical;
    IFBSystemCPUCacheInfo cache_l1;
    IFBSystemCPUCacheInfo cache_l2;
    IFBSystemCPUCacheInfo cache_l3;
};

struct IFBSystemInfo {
    IFBSystemCPUInfo    cpu;
    IFBSystemMemoryInfo memory;
};


/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBHNDMemoryContext     : IFBHNDPTR { };
struct IFBHNDMemoryReservation : IFBHNDPTR { };
struct IFBHNDMemoryArena       : IFBHNDPTR { };

struct IFBMemoryContext {
    IFBMemoryReservation* ptr_reservation_first;
    IFBMemoryReservation* ptr_reservation_last;
    IFBMemoryArena*       ptr_arena_first;
    IFBMemoryArena*       ptr_arena_last;
    IFBAddr               stack_start;
    IFBU32                stack_size;
    IFBU32                stack_position;
    IFBU32                count_reservations;
    IFBU32                count_arenas;
    IFBU32                system_page_size;
    IFBU32                system_granularity;
};

struct IFBMemoryReservation {
    IFBMemoryContext*     ptr_context;
    IFBMemoryReservation* ptr_next;
    IFBAddr               start;
    IFBU32                page_count_total;
    IFBU32                page_count_committed;
};

struct IFBMemoryArena {
    IFBMemoryReservation* ptr_reservation;
    IFBMemoryArena*       ptr_next;
    IFBAddr               start;
    IFBU32                size;
    IFBU32                position_committed;
    IFBU32                position_reserved;
};

/**********************************************************************************/
/* SIMD                                                                           */
/**********************************************************************************/

#if _MSC_VER
    #if !defined(__clang__)
        #define INSTRUCTION_REORDER_BARRIER _ReadWriteBarrier()
    #endif //!defined(__clang__)
    #include <intrin.h>
#else //_MSC_VER
    #include <x86intrin.h>
#endif //_MSC_VER

typedef __m128 IFBXMMF128;

/**********************************************************************************/
/* MATH                                                                           */
/**********************************************************************************/

struct IFBVec2 {
    union {
        struct {
            IFBF32 x;
            IFBF32 y;
        };
        IFBF32 xy[2];
    };
};

struct IFBVec3 {
    union {
        struct {
            IFBF32 x;
            IFBF32 y;
            IFBF32 z;
        };
        IFBF32 xyz[3];
    };
};

struct IFBMat3 {
    union {
        struct {
            IFBF32 r0c0;
            IFBF32 r0c1;
            IFBF32 r0c2;
            IFBF32 r1c0;
            IFBF32 r1c1;
            IFBF32 r1c2;
            IFBF32 r2c0;
            IFBF32 r2c1;
            IFBF32 r2c2;
        };
        struct {
            IFBVec3 row_vec_0;
            IFBVec3 row_vec_1;
            IFBVec3 row_vec_2;
        };
        IFBF32 array[9];        
    };
};

struct IFBTransform {
    IFBVec2 translation;
    IFBVec2 scale;
    IFBF32 rotation_radians;
};

struct IFBPoint {
    IFBF32 x;
    IFBF32 y;
};

struct IFBLine {
    IFBPoint point_a;
    IFBPoint point_b;
};

/**********************************************************************************/
/* DATA STRUCTURES                                                                */
/**********************************************************************************/

struct IFBMemoryBlock {
    IFBAddr start;
    IFBU64  size;
};

struct IFBArray : IFBMemoryBlock {
    IFBU32 element_size;
    IFBU32 element_count;
};

struct IFBStack : IFBMemoryBlock {
    IFBU64 position;
};

struct IFBArrayList : IFBMemoryBlock {
    IFBU64 element_size;
    IFBU32 element_count_total;
    IFBU32 element_count_current;
};


struct IFBQueue : IFBMemoryBlock {
    IFBU32 position;
};

struct IFBHashTable : IFBMemoryBlock {
    IFBU32 element_array_start;
    IFBU32 element_size;
    IFBU32 element_count_max;
    IFBU32 key_length_max;
};


/**********************************************************************************/
/* GRAPHICS                                                                       */
/**********************************************************************************/

struct IFBDimensions {
    IFBU32 width;
    IFBU32 height;
};

struct IFBPosition {
    IFBU32 x;
    IFBU32 y;
};

struct IFBDimensionsAndPosition {
    IFBDimensions dimensions;
    IFBPosition   position;    
};

struct IFBColorNormalized {
    IFBF32 red;
    IFBF32 blue;
    IFBF32 green;
    IFBF32 alpha;
};

struct IFBColorHex {
    IFBU8 red;
    IFBU8 blue;
    IFBU8 green;
    IFBU8 alpha;
};

struct IFBColor32 {
    IFBU32 value;
};

enum IFBColorFormat : IFBU32 {
     IFBColorFormat_RGBA = 0,
     IFBColorFormat_ARGB = 1,
     IFBColorFormat_ABGR = 2,
     IFBColorFormat_BGRA = 3
};

#define IFB_WINDOW_TITLE_LENGTH_MAX 255

typedef IFBPtr IFBGLContext;
typedef IFBPtr IFBImGuiContext;

struct IFBGraphicsContexts {
    IFBGLContext    opengl;
    IFBImGuiContext imgui;
};

struct IFBWindow {
    IFBPosition         position;
    IFBDimensions       dimensions;
    IFBGraphicsContexts graphics_contexts;
    IFBB32              visible;
    IFBB32              quit_received;
    IFBChar*            title;
};

struct IFBMonitor {
    IFBDimensions dimensions;
    IFBPosition   position;
    IFBU32        refresh_hz;
    IFBU32        index;
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

//callback
typedef IFBU32 (*IFBFileAsyncCallback) (IFBFileContext* file_context);

//handles
struct IFBHNDFile      : IFBHND16 { };
struct IFBHNDFileTable : IFBHND32 { };

struct IFBFile {
    IFBHNDFileTable file_table;
    IFBU32          size;
    IFBU16          table_index;
    IFBB16          read_only;
};

struct IFBFileBuffer {
    IFBPtr start;
    IFBU64 size;
};

struct IFBFileContext {
    IFBAddr              memory_start;
    IFBFileAsyncCallback callback_read;
    IFBFileAsyncCallback callback_write;
    IFBU32               context_data_size;
    IFBU32               bytes_transferred;
    IFBHND32             handle_context_data;
};

struct IFBFileTableArgs {
    IFBMemoryArena*      arena;
    IFBFileAsyncCallback file_callback_read;
    IFBFileAsyncCallback file_callback_write;
    IFBChar*             file_path_buffer;
    IFBU32               file_path_stride; 
    IFBU32               file_count;
};

struct IFBFileReadOnlyTable {
    struct {
        IFBAddr              start;
        IFBU64               size;
        IFBU16               file_count;
        IFBU16               file_path_stride;
        IFBFileAsyncCallback callback;
    } header;

    struct {
        IFBHND16 file_path_buffer;
        IFBHND16 array_file_context;
        IFBHND16 array_last_bytes_read;
        IFBHND16 array_list_files_open;
        IFBHND16 array_list_files_closed;
        IFBHND16 array_list_files_locked;
        IFBHND16 context_data;
    } handles;
};

struct IFBFileReadOnlyRequest {
    IFBAddr memory_start;
    IFBU64  memory_size;
    IFBU32  file_count;
    IFBU32  file_path_stride;
    struct {
        IFBHND16 context;
        IFBHND16 buffer;
        IFBHND16 file_path;
        IFBHND16 file_handle;
    } handles;
};

// namespace ifb_file_ro {

//     const IFBFileContext* request_load_array_file_context     (const IFBFileReadOnlyRequest* request);
//     const IFBFileBuffer*  request_load_array_file_buffer      (const IFBFileReadOnlyRequest* request);
//     const IFBChar*        request_load_array_file_path        (const IFBFileReadOnlyRequest* request);
//     const IFBHND16*       request_load_array_file_table_index (const IFBFileReadOnlyRequest* request);
//     const IFBChar*        request_load_file_path              (const IFBFileReadOnlyRequest* request, const IFBChar* file_path_buffer, const IFBU32 file_index);
// };

// #define IFB_HANDLE_INVALID_U16 0xFFFF

// inline const IFBFileContext*
// ifb_file_ro::request_load_array_file_context(
//     IFBFileReadOnlyRequest* request) {

//     ifb_macro_assert(request);

//     //calculate the address
//     const IFBAddr start       = request->memory_start;
//     const IFBU32  offset      = request->handles.context;
//     const IFBAddr result_addr = start + offset;

//     //make sure its valid
//     ifb_macro_assert(start  != 0);
//     ifb_macro_assert(offset != IFB_HANDLE_INVALID_U16);

//     //if the address is valid, cast it
//     IFBFileContext* result_ptr = (IFBFileContext*)result_addr;

//     //we're done
//     return(result_ptr); 
// }

// inline const IFBFileBuffer*
// ifb_file_ro::request_load_array_file_buffer(
//     IFBFileReadOnlyRequest* request) {

//     ifb_macro_assert(request);

//     //calculate the address
//     const IFBAddr start       = request->memory_start;
//     const IFBU32  offset      = request->handles.buffer;
//     const IFBAddr result_addr = start + offset;

//     //make sure its valid
//     ifb_macro_assert(start  != 0);
//     ifb_macro_assert(offset != IFB_HANDLE_INVALID_U16);

//     //if the address is valid, cast it
//     IFBFileBuffer* result_ptr = (IFBFileBuffer*)result_addr;

//     //we're done
//     return(result_ptr); 
// }

// inline const IFBChar*
// ifb_file_ro::request_load_array_file_path(
//     IFBFileReadOnlyRequest* request) {

//     ifb_macro_assert(request);

//     //calculate the address
//     const IFBAddr start       = request->memory_start;
//     const IFBU32  offset      = request->handles.file_path;
//     const IFBAddr result_addr = start + offset;
    
//     //make sure its valid
//     ifb_macro_assert(start  != 0);
//     ifb_macro_assert(offset != IFB_HANDLE_INVALID_U16);

//     //if the address is valid, cast it
//     IFBChar* result_ptr = (IFBChar*)result_addr;

//     //we're done
//     return(result_ptr); 
// }

// inline const IFBHND16*
// ifb_file_ro::request_load_array_file_table_index(
//     IFBFileReadOnlyRequest* request) {

//     ifb_macro_assert(request);

//     //calculate the address
//     const IFBAddr start       = request->memory_start;
//     const IFBU32  offset      = request->handles.file_table_index;
//     const IFBAddr result_addr = start + offset;

//     //make sure its valid
//     ifb_macro_assert(start  != 0);
//     ifb_macro_assert(offset != IFB_HANDLE_INVALID_U16);

//     //if the address is valid, cast it
//     IFBHND16* result_ptr = (IFBHND16*)result_addr;

//     //we're done
//     return(result_ptr); 
// }

// inline const IFBChar*
// ifb_file_ro::request_load_file_path(
//     const IFBFileReadOnlyRequest* request,
//     const IFBChar*                file_path_buffer,
//     const IFBU32                  file_index) {

//     //ensure the pointers are valid
//     ifb_macro_assert(request);
//     ifb_macro_assert(file_path_buffer);
//     ifb_macro_assert(file_index);

//     //calculate the offset
//     const IFBU32 file_count       = request->file_count;
//     const IFBU32 file_path_stride = request->file_path_stride;
//     const IFBU32 file_path_offset = file_count * file_path_stride;

//     //make sure the index is valid
//     ifb_macro_assert(file_index < file_count);

//     //calculate the file path
//     IFBChar* file_path = &file_path_buffer[file_path_offset];

//     //we're done
//     return(file_path);
// }


#endif //IFB_TYPES_HPP