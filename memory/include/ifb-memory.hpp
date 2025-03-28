#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryStack;
struct IFBMemoryReservation;
struct IFBMemoryArena;

typedef IFBMemoryStack*       IFBMEMStack;       
typedef IFBMemoryReservation* IFBMEMReservation;
typedef IFBMemoryArena*       IFBMEMArena; 

struct IFBMemory {
    IFBAddr start;
    IFBU64  size;
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMStack       stack_create                      (const IFBMemory& stack_memory);
    const IFBU32      stack_push_bytes_relative         (IFBMEMStack stack_handle, const IFBU32 size);
    const IFBPtr      stack_push_bytes_absolute_pointer (IFBMEMStack stack_handle, const IFBU32 size);
    const IFBAddr     stack_push_bytes_absolute_address (IFBMEMStack stack_handle, const IFBU32 size);
    const IFBB8       stack_pull_bytes                  (IFBMEMStack stack_handle, const IFBU32 size);
    const IFBPtr      stack_get_pointer                 (IFBMEMStack stack_handle, const IFBU32 offset);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMReservation
    reserve_system_memory(
              IFBMEMStack stack_handle,
        const IFBU64      size_reservation,
        const IFBU32      size_arena);


    const IFBB8 release_system_memory (IFBMEMReservation reservation_handle);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMArena   arena_commit              (IFBMEMReservation reservation_handle);

    const IFBB8   arena_decommit                    (IFBMEMArena arena_handle);
    const IFBB8   arena_reset                       (IFBMEMArena arena_handle);
    const IFBU32  arena_push_bytes_relative         (IFBMEMArena arena_handle, const IFBU32 size);
    const IFBPtr  arena_push_bytes_absolute_pointer (IFBMEMArena arena_handle, const IFBU32 size);
    const IFBAddr arena_push_bytes_absolute_address (IFBMEMArena arena_handle, const IFBU32 size);
    const IFBB8   arena_pull_bytes                  (IFBMEMArena arena_handle, const IFBU32 size);
    const IFBPtr  arena_get_pointer                 (IFBMEMArena arena_handle, const IFBU32 offset);
};

/**********************************************************************************/
/* UTILITIES                                                                      */
/**********************************************************************************/

namespace ifb_memory {

    const IFBPtr  get_pointer (const IFBAddr    start,  const IFBU32 offset);
    const IFBPtr  get_pointer (const IFBMemory& memory, const IFBU32 offset);
          IFBVoid zero_buffer (const IFBMemory& memory);
};

inline const IFBPtr
ifb_memory::get_pointer(
    const IFBAddr start,
    const IFBU32  offset) {

    const IFBAddr address = start + offset;
    const IFBPtr  pointer = (address != 0) ? (IFBPtr)address : NULL;

    return(pointer);
}

inline const IFBPtr 
ifb_memory::get_pointer(
    const IFBMemory& memory,
    const IFBU32     offset) {

    IFBB8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size   >  offset);

    const IFBAddr address = memory.start + offset;
    const IFBPtr  pointer = is_valid ? (IFBPtr)address : NULL;

    return(pointer);
}

inline IFBVoid
ifb_memory::zero_buffer(
    const IFBMemory& memory) {

    IFBB8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size  != 0);
    ifb_macro_assert(is_valid);

    IFBByte* buffer = (IFBByte*)memory.start;

    for (
        IFBU32 index = 0;
               index < memory.size;
             ++index) {
        
        buffer[index] = 0;
    }
}

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_stack_push_struct_absolute(stack,struct) (struct*)ifb_memory::stack_push_bytes_absolute_pointer(stack,ifb_macro_align_size_struct(struct))
#define ifb_memory_macro_stack_push_struct_relative(stack,struct)          ifb_memory::stack_push_bytes_relative        (stack,ifb_macro_align_size_struct(struct))

#endif //IFB_MEMORY_HPP
