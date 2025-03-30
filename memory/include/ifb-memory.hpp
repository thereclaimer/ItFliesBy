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
    ifb::addr start;
    ifb::u64  size;
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMStack       stack_create                      (const IFBMemory& stack_memory);
    const ifb::u32      stack_push_bytes_relative         (IFBMEMStack stack_handle, const ifb::u32 size);
    const ifb::ptr      stack_push_bytes_absolute_pointer (IFBMEMStack stack_handle, const ifb::u32 size);
    const ifb::addr     stack_push_bytes_absolute_address (IFBMEMStack stack_handle, const ifb::u32 size);
    const ifb::b8       stack_pull_bytes                  (IFBMEMStack stack_handle, const ifb::u32 size);
    const ifb::ptr      stack_get_pointer                 (IFBMEMStack stack_handle, const ifb::u32 offset);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMReservation
    reserve_system_memory(
              IFBMEMStack stack_handle,
        const ifb::u64      size_reservation,
        const ifb::u32      size_arena);


    const ifb::b8 release_system_memory (IFBMEMReservation reservation_handle);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

namespace ifb_memory {

    IFBMEMArena   arena_commit                      (IFBMEMReservation reservation_handle);

    const ifb::b8   arena_decommit                    (IFBMEMArena arena_handle);
    const ifb::b8   arena_reset                       (IFBMEMArena arena_handle);
    const ifb::u32  arena_push_bytes_relative         (IFBMEMArena arena_handle, const ifb::u32 size);
    const ifb::ptr  arena_push_bytes_absolute_pointer (IFBMEMArena arena_handle, const ifb::u32 size);
    const ifb::addr arena_push_bytes_absolute_address (IFBMEMArena arena_handle, const ifb::u32 size);
    const ifb::b8   arena_pull_bytes                  (IFBMEMArena arena_handle, const ifb::u32 size);
    const ifb::ptr  arena_get_pointer                 (IFBMEMArena arena_handle, const ifb::u32 offset);
};

/**********************************************************************************/
/* UTILITIES                                                                      */
/**********************************************************************************/

namespace ifb_memory {

    const ifb::ptr  get_pointer (const ifb::addr    start,  const ifb::u32 offset);
    const ifb::ptr  get_pointer (const IFBMemory& memory, const ifb::u32 offset);
          void zero_buffer (const IFBMemory& memory);
};

inline const ifb::ptr
ifb_memory::get_pointer(
    const ifb::addr start,
    const ifb::u32  offset) {

    const ifb::addr address = start + offset;
    const ifb::ptr  pointer = (address != 0) ? (ifb::ptr)address : NULL;

    return(pointer);
}

inline const ifb::ptr 
ifb_memory::get_pointer(
    const IFBMemory& memory,
    const ifb::u32     offset) {

    ifb::b8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size   >  offset);

    const ifb::addr address = memory.start + offset;
    const ifb::ptr  pointer = is_valid ? (ifb::ptr)address : NULL;

    return(pointer);
}

inline void
ifb_memory::zero_buffer(
    const IFBMemory& memory) {

    ifb::b8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size  != 0);
    ifb_macro_assert(is_valid);

    ifb::byte* buffer = (ifb::byte*)memory.start;

    for (
        ifb::u32 index = 0;
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
