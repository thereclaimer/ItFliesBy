#ifndef IFB_ENGINE_INTERNAL_TABLES_HPP
#define IFB_ENGINE_INTERNAL_TABLES_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"

struct IFBEngineTableTag;
struct IFBEngineTableStackAllocator;
struct IFBEngineTableBlockAllocator;
struct IFBEngineTableArena;
struct IFBEngineTableShaderProgram;

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

/**********************************************************************************/
/* STACK ALLOCATOR TABLE                                                          */
/**********************************************************************************/

#define IFB_ENGINE_TABLE_STACK_ALLOCATOR_ROW_COUNT 1024

struct IFBEngineTableStackAllocator {
    ifb_u32           row_count;
    struct {
        IFBEngineArenaId* arena_id;
        ifb_u32*          used;
    } column_ptrs;
};

/**********************************************************************************/
/* ARENA TABLE                                                                    */
/**********************************************************************************/

#define IFB_ENGINE_TABLE_ARENA_ROW_COUNT 4096

struct IFBEngineTableArena {
    ifb_u32           row_count;
    struct {
        ifb_u32*        page_start;
        ifb_u32*        page_count;
        IFBEngineTagId* tag_id;
    } column_ptrs;
};

/**********************************************************************************/
/* TABLE MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineTable {
    ifb_u32             row_count;
    ifb_u32             column_handle_start;
    ifb_u32             column_handle_count;
};

#define IFB_ENGINE_TABLE_MANAGER_COLUMN_COUNT_MAX 1024

union IFBEngineTables {
    struct {
        IFBEngineTable tag;
        IFBEngineTable stack_allocator;
        IFBEngineTable block_allocator;
        IFBEngineTable arena;
        IFBEngineTable shader_program;
    };
    IFBEngineTable array[IFBEngineTableId_Count];
};

struct IFBEngineTableColumns {
    ifb_u32             column_count_max;
    ifb_u32             column_count_used;
    ifb_handle_memory   column_handles[IFB_ENGINE_TABLE_MANAGER_COLUMN_COUNT_MAX];
};

struct IFBEngineTableManager {
    IFBEngineTables       tables;
    IFBEngineTableColumns columns;
};

namespace ifb_engine {

    const ifb_handle_memory  table_manager_create (ifb_void);

    IFBEngineTableManager* table_manager_from_handle  (const ifb_handle_memory handle);
    IFBEngineTableManager* table_manager_from_context (ifb_void);
    
    IFBEngineTable& 
    table_manager_get_table_ref(
              IFBEngineTableManager* table_manager_ptr,
        const IFBEngineTableId       table_id);

    
    const ifb_b8
    table_manager_create_table(
              IFBEngineTableManager* table_manager_ptr,
        const IFBEngineTableId       table_id,
        const ifb_u32                table_row_count,
        const ifb_u32                table_column_count,
        const ifb_u32*               table_column_sizes);

    const ifb_b8 table_manager_create_table_tag             (IFBEngineTableManager* table_manager_ptr);
    const ifb_b8 table_manager_create_table_stack_allocator (IFBEngineTableManager* table_manager_ptr);
    const ifb_b8 table_manager_create_table_block_allocator (IFBEngineTableManager* table_manager_ptr);
    const ifb_b8 table_manager_create_table_arena           (IFBEngineTableManager* table_manager_ptr);
    const ifb_b8 table_manager_create_table_shader_program  (IFBEngineTableManager* table_manager_ptr);

    ifb_void table_tag             (IFBEngineTableTag&            tag_table);
    ifb_void table_arena           (IFBEngineTableArena&          arena_table);
    ifb_void table_stack_allocator (IFBEngineTableStackAllocator& stack_allocator_table);
};

#endif //IFB_ENGINE_INTERNAL_TABLES_HPP