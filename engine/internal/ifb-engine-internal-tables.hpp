#ifndef IFB_ENGINE_INTERNAL_TABLES_HPP
#define IFB_ENGINE_INTERNAL_TABLES_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"

struct IFBEngineTableTag;
struct IFBEngineTableStackAllocator;
struct IFBEngineTableBlockAllocator;
struct IFBEngineTableArena;
struct IFBEngineTableShaderProgram;

struct IFBEngineTableHandleTag   : IFBEngineMemoryHandle { };
struct IFBEngineTableHandleArena : IFBEngineMemoryHandle { };

/**********************************************************************************/
/* TAG TABLE                                                                      */
/**********************************************************************************/

#define IFB_ENGINE_TABLE_TAG_ROW_COUNT    1024
#define IFB_ENGINE_TABLE_TAG_VALUE_LENGTH 32

struct IFBEngineTableTag {
    ifb_u32           row_count;
    struct {
        ifb_char*     tag_buffer;
        IFBHashValue* hash_value;
    } column_ptrs;
};

namespace ifb_engine {

    const ifb_b8 table_tag_read(
        const IFBEngineTableHandleTag tag_table_handle,
        const ifb_u32                 tag_table_read_count
        const IFBEngineTableIndexTag* tag_indexes, 
              ifb_char*               tag_table_column_ptr_tag_value,
              IFBHashValue*           tag_table_column_ptr_hash_value);
    
    const ifb_b8 table_tag_delete          (const IFBEngineTableHandleTag tag_table_handle, const IFBEngineTableIndexTag tag_index);

    const ifb_b8       table_tag_insert          (const IFBEngineTableHandleTag in_tag_table_handle, const ifb_cstr in_tag_value, IFBEngineTagId& out_tag_id);
    const ifb_b8       table_tag_search          (const IFBEngineTableHandleTag in_tag_table_handle, const ifb_cstr in_tag_value, IFBEngineTagId& out_tag_id);
};


/**********************************************************************************/
/* ARENA TABLE                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_TABLE_ARENA_ROW_COUNT 4096

struct IFBEngineTableArena {
    ifb_u32           row_count;
    struct {
        ifb_u32*                page_start;
        ifb_u32*                page_count;
        IFBEngineTableIndexTag* tag_index;
    } column_ptrs;
};

namespace ifb_engine {

    const ifb_u32                table_arena_read_page_start (const IFBEngineTableHandleArena arena_table_handle, const IFBEngineTableIndexArena arena_index);
    const ifb_u32                table_arena_read_page_count (const IFBEngineTableHandleArena arena_table_handle, const IFBEngineTableIndexArena arena_index);
    const IFBEngineTableIndexTag table_arena_read_tag_index  (const IFBEngineTableHandleArena arena_table_handle, const IFBEngineTableIndexArena arena_index);

};

/**********************************************************************************/
/* TABLES                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const ifb_b8 table_create_tag   (const IFBEngineTableAllocatorHandle in_table_allocator_handle, IFBEngineTableHandleTag&   out_table_handle_tag_ref);
    const ifb_b8 table_create_arena (const IFBEngineTableAllocatorHandle in_table_allocator_handle, IFBEngineTableHandleArena& out_table_handle_arena_ref);

    IFBEngineTableTag*   table_tag   (const IFBEngineTableHandleTag   table_handle_tag);
    IFBEngineTableArena* table_arena (const IFBEngineTableHandleArena table_handle_arena);
};

#endif //IFB_ENGINE_INTERNAL_TABLES_HPP