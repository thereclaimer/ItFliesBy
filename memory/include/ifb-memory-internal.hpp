#ifndef IFB_MEMORY_INTERNAL_HPP
#define IFB_MEMORY_INTERNAL_HPP

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryContext;
struct IFBMemoryReservation;
struct IFBMemoryStack;
struct IFBMemoryArena;
struct IFBMemoryArenaLinear;
struct IFBMemoryArenaBlock;
struct IFBMemoryBlock;

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

#define IFB_MEMORY_HANDLE_MINIMUM sizeof(IFBMemoryContext)

struct IFBMemoryStack {
    IFBAddr start;
    IFBAddr end;
    IFBU32     size;
    IFBU32     position;
};

/**********************************************************************************/
/* ARENA BASE                                                                     */
/**********************************************************************************/

struct IFBMemoryArena {
    IFBAddr           start;
    IFBMemoryReservation* reservation;
    IFBMemoryArena*       next;
    IFBMemoryArenaType    type;    
    IFBU32               page_start;
    IFBU32               page_count;
    IFBU32               size_total;
    IFBU32               stack_position;
};

struct IFBMemoryArenaList {
    IFBMemoryArena* first;    
    IFBMemoryArena* last;    
    IFBU32         count;
};

/**********************************************************************************/
/* ARENA LINEAR                                                                   */
/**********************************************************************************/

struct IFBMemoryArenaLinear : IFBMemoryArena {
    IFBU32 position;
    IFBU32 save_point;
};

/**********************************************************************************/
/* ARENA BLOCK                                                                    */
/**********************************************************************************/

struct IFBMemoryArenaBlock : IFBMemoryArena  {
    IFBAddr* block_address_array;
    IFBU32      block_count;
    IFBU32      block_size;
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

struct IFBMemoryReservation {
    IFBMemoryReservation* next;
    IFBAddr           start;
    IFBU32               stack_offset;
    IFBU32               page_count_total;
    IFBU32               page_count_committed;
    IFBMemoryArenaList    arena_list;
};

struct IFBMemoryReservationList {
    IFBMemoryReservation* first;
    IFBMemoryReservation* last;
    IFBU32               count;
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

    inline IFBMemoryContext*         context                         (IFBVoid);
    inline IFBMemoryStack&           context_get_stack               (IFBVoid);            
    inline IFBMemorySystemInfo&      context_get_system_info         (IFBVoid);      
    inline IFBMemoryReservationList& context_get_reservation_list    (IFBVoid); 
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

    inline IFBB8
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
        IFBB8 result = true;
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