#ifndef IFB_ENGINE_INTERNAL_TABLES_HPP
#define IFB_ENGINE_INTERNAL_TABLES_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"

struct IFBEngineTableTag;
struct IFBEngineTableStackAllocator;
struct IFBEngineTableBlockAllocator;
struct IFBEngineTableArena;
struct IFBEngineTableShaderProgram;

struct IFBEngineTableHandleTag;
struct IFBEngineTableHandleStackAllocator;
struct IFBEngineTableHandleBlockAllocator;
struct IFBEngineTableHandleArena;
struct IFBEngineTableHandleShaderProgram;

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

struct IFBEngineTableHandleTag {
    ifb_handle_memory table_handle;
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

struct IFBEngineTableHandleArena {
    ifb_handle_memory table_handle;
};

/**********************************************************************************/
/* TABLE MANAGER                                                                  */
/**********************************************************************************/

struct IFBEngineTableManager {
    struct {
        ifb_u32 page_start;
        ifb_u32 page_count;
        ifb_u32 used;
    } header_memory;
};

struct IFBEngineTable {
    ifb_handle_memory  header;
    ifb_handle_memory* column_ptr;
    ifb_u32            column_count;
};

namespace ifb_engine {

    const ifb_handle_memory  table_manager_create (ifb_void);

    IFBEngineTableManager* table_manager_from_handle  (const ifb_handle_memory handle);
    IFBEngineTableManager* table_manager_from_context (ifb_void);
    
    const ifb_b8
    table_manager_create_table(
              IFBEngineTableManager* in_table_manager_ptr,
        const ifb_u32                in_table_header_size,
        const ifb_u32                in_table_row_count,
        const ifb_u32                in_table_column_count,
        const ifb_u32*               in_table_column_sizes,
              IFBEngineTable&       out_table_ref);

};

/**********************************************************************************/
/* TABLES                                                                         */
/**********************************************************************************/

namespace ifb_engine {

    const IFBEngineTableHandleTag            table_create_tag             (IFBEngineTableManager* table_manager_ptr);
    const IFBEngineTableHandleStackAllocator table_create_stack_allocator (IFBEngineTableManager* table_manager_ptr);
    const IFBEngineTableHandleBlockAllocator table_create_block_allocator (IFBEngineTableManager* table_manager_ptr);
    const IFBEngineTableHandleArena          table_create_arena           (IFBEngineTableManager* table_manager_ptr);
    const IFBEngineTableHandleShaderProgram  table_create_shader_program  (IFBEngineTableManager* table_manager_ptr);


    IFBEngineTableTag*            table_tag             (IFBEngineTableTag&            tag_table);
    IFBEngineTableArena*          table_arena           (IFBEngineTableArena&          arena_table);
    IFBEngineTableStackAllocator* table_stack_allocator (IFBEngineTableStackAllocator& stack_allocator_table);
};

#endif //IFB_ENGINE_INTERNAL_TABLES_HPP