#ifndef IFB_COMMON_STACK_HPP
#define IFB_COMMON_STACK_HPP

#include "ifb-common-types.hpp"

struct IFBStack {
    ifb_u32 id;
    ifb_u32 start;
    ifb_u32 size;
    ifb_u32 position;
};

namespace ifb_common {

    const ifb_u32    stack_push    (IFBStack& stack_ref, const ifb_u32 size);
    const ifb_u32    stack_pull    (IFBStack& stack_ref, const ifb_u32 size);
    const ifb_memory stack_pointer (IFBStack& stack_ref, const ifb_memory base_memory);
};

inline const ifb_u32
ifb_common::stack_push(
          IFBStack& stack_ref, 
    const ifb_u32   size) {

    const ifb_u32 new_position = stack_ref.position + size;

    if (new_position > stack_ref.size) {
        return(0);
    }

    stack_ref.position = new_position;
    
    return(stack_ref.start + stack_ref.position);
}

inline const ifb_b8
ifb_common::stack_pull(
          IFBStack& stack_ref, 
    const ifb_u32   size) {

    if (size > stack_ref.position) {
        return(false);
    }

    stack_ref.position -= size;

    return(stack_ref.start + stack_ref.position);
}

inline const ifb_memory
ifb_common::stack_pointer(
          IFBStack&  stack_ref, 
    const ifb_memory base_memory) {

    const ifb_memory stack_pointer = 
        base_memory     + 
        stack_ref.start + 
        stack_ref.position;

    return(stack_pointer);
}

#endif //IFB_COMMON_STACK_HPP