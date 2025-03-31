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

    typedef mem_stack_t*       mem_stack_h;       
    typedef mem_reservation_t* mem_reservation_h;
    typedef mem_arena_t*       mem_arena_h; 
};

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/
namespace ifb::memory {

    mem_stack_h stack_create                      (const memory_t& stack_memory);
    const u32   stack_push_bytes_relative         (mem_stack_h stack, const u32 size);
    const ptr   stack_push_bytes_absolute_pointer (mem_stack_h stack, const u32 size);
    const addr  stack_push_bytes_absolute_address (mem_stack_h stack, const u32 size);
    const b8    stack_pull_bytes                  (mem_stack_h stack, const u32 size);
    const ptr   stack_get_pointer                 (mem_stack_h stack, const u32 offset);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/
namespace ifb::memory {

    mem_reservation_h
    reserve_system_memory(
        mem_stack_h stack,
        const u64   size_reservation,
        const u32   size_arena);


    const b8 release_system_memory (mem_reservation_h reservation);
};

/**********************************************************************************/
/* ARENA                                                                          */
/**********************************************************************************/
namespace ifb::memory {

    mem_arena_h arena_commit                      (mem_reservation_h reservation);
    const b8    arena_decommit                    (mem_arena_h arena);
    const b8    arena_reset                       (mem_arena_h arena);
    const u32   arena_push_bytes_relative         (mem_arena_h arena, const u32 size);
    const ptr   arena_push_bytes_absolute_pointer (mem_arena_h arena, const u32 size);
    const addr  arena_push_bytes_absolute_address (mem_arena_h arena, const u32 size);
    const b8    arena_pull_bytes                  (mem_arena_h arena, const u32 size);
    const ptr   arena_get_pointer                 (mem_arena_h arena, const u32 offset);
};

/**********************************************************************************/
/* UTILITIES                                                                      */
/**********************************************************************************/
namespace ifb::memory {

    const ptr get_pointer (const addr      start,  const u32 offset);
    const ptr get_pointer (const memory_t& memory, const u32 offset);
    void      zero_buffer (const memory_t& memory);

};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

using namespace ifb;

inline const ptr
memory::get_pointer(
    const addr start,
    const u32  offset) {

    const addr address = start + offset;
    const ptr  pointer = (address != 0) ? (ptr)address : NULL;

    return(pointer);
}

inline const ifb::ptr 
memory::get_pointer(
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
memory::zero_buffer(
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

/**********************************************************************************/
/* MACROS                                                                         */
/**********************************************************************************/

#define ifb_memory_macro_stack_push_struct_absolute(stack,struct) (struct*)ifb::memory::stack_push_bytes_absolute_pointer(stack,ifb_macro_align_size_struct(struct))
#define ifb_memory_macro_stack_push_struct_relative(stack,struct)          ifb::memory::stack_push_bytes_relative        (stack,ifb_macro_align_size_struct(struct))

#endif //IFB_MEMORY_HPP