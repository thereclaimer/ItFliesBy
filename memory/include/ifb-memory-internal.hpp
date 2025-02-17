#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryContext;
struct IFBMemoryReservation;
struct IFBMemoryArena;
struct IFBMemoryStack;
struct IFBMemoryLinearArena;
struct IFBMemoryBlockArena;
struct IFBMemoryBlock;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_HANDLE_MINIMUM sizeof(IFBMemoryContext)

struct IFBMemoryStack {
    ifb_address start;
    ifb_address end;
    ifb_u32     size;
    ifb_u32     position;
};

/**********************************************************************************/
/* ARENA BASE                                                                     */
/**********************************************************************************/

struct IFBMemoryArena {
    ifb_address           start;
    IFBMemoryReservation* reservation;
    IFBMemoryArena*       next;
    IFBMemoryArenaType    type;    
    ifb_u32               page_start;
    ifb_u32               page_count;
    ifb_u32               size_total;
    ifb_u32               stack_position;
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;    
    IFBMemoryArena* last;    
    ifb_u32         count;
};

/**********************************************************************************/
/* ARENA LINEAR                                                                   */
/**********************************************************************************/

struct IFBMemoryLinearArena : IFBMemoryArena {
    ifb_u32 position;
    ifb_u32 save_point;
};

/**********************************************************************************/
/* ARENA BLOCK                                                                    */
/**********************************************************************************/

struct IFBMemoryBlockArena : IFBMemoryArena  {
    ifb_address* block_address_array;
    ifb_u32      block_count;
    ifb_u32      block_size;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBMemoryReservation* next;
    ifb_address           start;
    ifb_u32               stack_offset;
    ifb_u32               page_count_total;
    ifb_u32               page_count_committed;
    IFBMemoryArenaList    arena_list;
};

struct IFBMemoryReservationList {
    IFBMemoryReservation* first;
    IFBMemoryReservation* last;
    ifb_u32               count;
};

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBMemoryContext {
    IFBMemoryStack           stack;
    IFBMemorySystemInfo      system_info;
    IFBMemoryReservationList reservation_list;
};

namespace ifb_memory {

    inline IFBMemoryContext*         context                         (ifb_void);
    inline IFBMemoryStack&           context_get_stack               (ifb_void);            
    inline IFBMemorySystemInfo&      context_get_system_info         (ifb_void);      
    inline IFBMemoryReservationList& context_get_reservation_list    (ifb_void); 
};

/**********************************************************************************/
/* PLATFORM                                                                       */
/**********************************************************************************/

namespace ifb_memory {

    //system
    ifb_global funcptr_ifb_platform_system_page_size              platform_system_page_size;
    ifb_global funcptr_ifb_platform_system_allocation_granularity platform_system_allocation_granularity;

    //memory
    ifb_global funcptr_ifb_platform_memory_reserve                platform_memory_reserve;
    ifb_global funcptr_ifb_platform_memory_release                platform_memory_release;
    ifb_global funcptr_ifb_platform_memory_commit                 platform_memory_commit;

    inline ifb_b8
    platform_set_api(
        const IFBPlatformApi* ptr_platform_api) {

        //sanity check
        if (!ptr_platform_api) return(false);

        //system
        const IFBPlatformSystemApi& system_api_ref   = ptr_platform_api->system; 
        platform_system_page_size              = system_api_ref.page_size; 
        platform_system_allocation_granularity = system_api_ref.allocation_granularity; 

        //memory
        const IFBPlatformMemoryApi& memory_api_ref = ptr_platform_api->memory;
        platform_memory_reserve = memory_api_ref.reserve;
        platform_memory_release = memory_api_ref.release;
        platform_memory_commit  = memory_api_ref.commit;

        //make sure the methods are defined
        ifb_b8 result = true;
        result &= (platform_system_page_size              != NULL); 
        result &= (platform_system_allocation_granularity != NULL); 
        result &= (platform_memory_reserve                != NULL); 
        result &= (platform_memory_release                != NULL); 
        result &= (platform_memory_commit                 != NULL); 

        //we're done
        return(result);
    }
};

#endif //IFB_MEMORY_INTERNAL_HPP