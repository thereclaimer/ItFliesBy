#ifndef IFB_ENGINE_INTERNAL_CORE_HPP
#define IFB_ENGINE_INTERNAL_CORE_HPP

#include <ifb-memory.hpp>
#include <ifb-io.hpp>

#include "ifb-engine.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//core
struct IFBEngineCore;

//memory
struct IFBEngineCoreMemoryStack;
struct IFBEngineCoreMemorySubStack;
struct IFBEngineCoreMemoryReservation;
struct IFBEngineCoreMemory;

//files
struct IFBEngineCoreFiles;

#define IFB_ENGINE_CORE_MEMORY_ARENA_SIZE ifb_macro_size_kilobytes(64)

/**********************************************************************************/
/* MEMORY                                                                         */
/**********************************************************************************/

struct IFBEngineCoreMemory {
    IFBMemoryContext*     ptr_context;
    IFBMemoryReservation* ptr_reservation;
    IFBU32                arena_size;
};

namespace ifb_engine {

    //reservation
    const IFBB8     core_memory_reserve_platform_memory (IFBEngineCore* core_ptr, const IFBU64 size);
    const IFBB8     core_memory_release_platform_memory (IFBEngineCore* core_ptr);

    //stack
    const IFBPtr    core_memory_commit_bytes_absolute   (IFBEngineCore* core_ptr, const IFBU32 size, const IFBU32 alignment = 0);
    const IFBU32    core_memory_commit_bytes_relative   (IFBEngineCore* core_ptr, const IFBU32 size, const IFBU32 alignment = 0);

    //arenas
    IFBMemoryArena* core_memory_commit_arena            (IFBEngineCore* core_ptr);           
};

/**********************************************************************************/
/* FILES                                                                          */
/**********************************************************************************/

struct IFBEngineCoreFiles {
    IFBMemoryArena* arena;
    struct  {
        IFBHNDFileTable read_only;
        IFBHNDFileTable read_write;
    } table_handles;
};

namespace ifb_engine {

    const IFBB8 core_files_commit_tables(IFBEngineCore* core_ptr);
};

/**********************************************************************************/
/* CORE                                                                           */
/**********************************************************************************/

struct IFBEngineCore {
    IFBSystemInfo        system_info;
    IFBEngineCoreMemory memory; 
    IFBEngineCoreFiles  files;
};

namespace ifb_engine {

    IFBEngineCore*
    core_create(
        const IFBByte* core_stack_memory_ptr,
        const IFBU32   core_stack_memory_size,
        const IFBU64   core_reserved_memory_size);
    
    const IFBB8
    core_destroy(
        IFBEngineCore* core_ptr);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/


#endif //IFB_ENGINE_INTERNAL_CORE_HPP