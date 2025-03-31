#ifndef IFB_MEMORY_HPP
#define IFB_MEMORY_HPP

#include <ifb.hpp>
#include <ifb-platform.hpp>

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb::memory {

    struct mem_stack_t;
    struct mem_reservation_t;
    struct mem_arena_t;

    typedef mem_stack_t*       hnd_mem_stack_t;       
    typedef mem_reservation_t* hnd_mem_reservation_t;
    typedef mem_arena_t*       hnd_mem_arena_t; 
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

namespace ifb::memory {

    hnd_mem_stack_t stack_create                      (const memory_t& stack_memory);
    const u32       stack_push_bytes_relative         (hnd_mem_stack_t stack_handle, const u32 size);
    const ptr       stack_push_bytes_absolute_pointer (hnd_mem_stack_t stack_handle, const u32 size);
    const addr      stack_push_bytes_absolute_address (hnd_mem_stack_t stack_handle, const u32 size);
    const b8        stack_pull_bytes                  (hnd_mem_stack_t stack_handle, const u32 size);
    const ptr       stack_get_pointer                 (hnd_mem_stack_t stack_handle, const u32 offset);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

namespace ifb::memory {

    hnd_mem_reservation_t
    reserve_system_memory(
              hnd_mem_stack_t stack_handle,
        const u64         size_reservation,
        const u32         size_arena);


    const b8 release_system_memory (hnd_mem_reservation_t reservation_handle);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/

namespace ifb::memory {

    hnd_mem_arena_t arena_commit                      (hnd_mem_reservation_t reservation_handle);
    const b8        arena_decommit                    (hnd_mem_arena_t arena_handle);
    const b8        arena_reset                       (hnd_mem_arena_t arena_handle);
    const u32       arena_push_bytes_relative         (hnd_mem_arena_t arena_handle, const u32 size);
    const ptr       arena_push_bytes_absolute_pointer (hnd_mem_arena_t arena_handle, const u32 size);
    const addr      arena_push_bytes_absolute_address (hnd_mem_arena_t arena_handle, const u32 size);
    const b8        arena_pull_bytes                  (hnd_mem_arena_t arena_handle, const u32 size);
    const ptr       arena_get_pointer                 (hnd_mem_arena_t arena_handle, const u32 offset);
};

/**********************************************************************************/
/* UTILITIES                                                                      */
/**********************************************************************************/

namespace ifb::memory {

    const ptr  get_pointer (const addr      start,  const u32 offset);
    const ptr  get_pointer (const memory_t& memory, const u32 offset);
          void zero_buffer (const memory_t& memory);
};

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_stack_push_struct_absolute(stack,struct) (struct*)ifb::memory::stack_push_bytes_absolute_pointer(stack,ifb_macro_align_size_struct(struct))
#define ifb_memory_macro_stack_push_struct_relative(stack,struct)          ifb::memory::stack_push_bytes_relative        (stack,ifb_macro_align_size_struct(struct))

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

using namespace ifb;
using namespace ifb::memory;

namespace ifb_memory=ifb::memory;

inline const ptr
ifb_memory::get_pointer(
    const addr start,
    const u32  offset) {

    const addr address = start + offset;
    const ptr  pointer = (address != 0) ? (ptr)address : NULL;

    return(pointer);
}

inline const ifb::ptr 
ifb_memory::get_pointer(
    const memory_t& memory,
    const u32       offset) {

    b8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size   >  offset);

    const addr address = memory.start + offset;
    const ptr  pointer = is_valid ? (ptr)address : NULL;

    return(pointer);
}

inline void
ifb_memory::zero_buffer(
    const memory_t& memory) {

    b8 is_valid = true;
    is_valid &= (memory.start != 0);
    is_valid &= (memory.size  != 0);
    ifb_macro_assert(is_valid);

    byte* buffer = (byte*)memory.start;

    for (
        u32 index = 0;
            index < memory.size;
          ++index) {
        
        buffer[index] = 0;
    }
}

#endif //IFB_MEMORY_HPP