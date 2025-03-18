#ifndef IFB_UTILITIES_HPP
#define IFB_UTILITIES_HPP

#include "ifb-types.hpp"

struct IFBPointerOffset {
    IFBAddr address;
    IFBU64  offset;
};

namespace ifb_utilities {

    IFBPtr pointer_advance (IFBPointerOffset& pointer_offset_ref, const IFBU32 size);
};

inline IFBPtr
ifb_utilities::pointer_advance(
          IFBPointerOffset& pointer_offset_ref,
    const IFBU32            size) {

    //get the next pointer
    IFBPtr next_pointer = (IFBPtr)(pointer_offset_ref.address + pointer_offset_ref.offset);

    //update the offset
    pointer_offset_ref.offset += size;

    //we're done
    return(next_pointer);
}

// #define ifb_utilities_macro_pointer_advance_and_cast(pointer_offset_ref,size,type) (type*)ifb_utilities::pointer_advance(pointer_offset_ref,size)

#endif //IFB_UTILITIES_HPP