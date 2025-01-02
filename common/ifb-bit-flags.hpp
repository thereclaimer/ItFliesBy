#ifndef IFB_BIT_FLAGS_HPP
#define IFB_BIT_FLAGS_HPP

#include "ifb-types.hpp"
#include "ifb-macros.hpp"

#define IFB_BIT_FLAG_0  (1 << 0)
#define IFB_BIT_FLAG_1  (1 << 1)
#define IFB_BIT_FLAG_2  (1 << 2)
#define IFB_BIT_FLAG_3  (1 << 3)
#define IFB_BIT_FLAG_4  (1 << 4)
#define IFB_BIT_FLAG_5  (1 << 5)
#define IFB_BIT_FLAG_6  (1 << 6)
#define IFB_BIT_FLAG_7  (1 << 7)
#define IFB_BIT_FLAG_8  (1 << 8)
#define IFB_BIT_FLAG_9  (1 << 9)
#define IFB_BIT_FLAG_10 (1 << 10)
#define IFB_BIT_FLAG_11 (1 << 11)
#define IFB_BIT_FLAG_12 (1 << 12)
#define IFB_BIT_FLAG_13 (1 << 13)
#define IFB_BIT_FLAG_14 (1 << 14)
#define IFB_BIT_FLAG_15 (1 << 15)
#define IFB_BIT_FLAG_16 (1 << 16)
#define IFB_BIT_FLAG_17 (1 << 17)
#define IFB_BIT_FLAG_18 (1 << 18)
#define IFB_BIT_FLAG_19 (1 << 19)
#define IFB_BIT_FLAG_20 (1 << 20)
#define IFB_BIT_FLAG_21 (1 << 21)
#define IFB_BIT_FLAG_22 (1 << 22)
#define IFB_BIT_FLAG_23 (1 << 23)
#define IFB_BIT_FLAG_24 (1 << 24)
#define IFB_BIT_FLAG_25 (1 << 25)
#define IFB_BIT_FLAG_26 (1 << 26)
#define IFB_BIT_FLAG_27 (1 << 27)
#define IFB_BIT_FLAG_28 (1 << 28)
#define IFB_BIT_FLAG_29 (1 << 29)
#define IFB_BIT_FLAG_30 (1 << 30)
#define IFB_BIT_FLAG_31 (1 << 31)
#define IFB_BIT_FLAG_32 (1 << 32)
#define IFB_BIT_FLAG_33 (1 << 33)
#define IFB_BIT_FLAG_34 (1 << 34)
#define IFB_BIT_FLAG_35 (1 << 35)
#define IFB_BIT_FLAG_36 (1 << 36)
#define IFB_BIT_FLAG_37 (1 << 37)
#define IFB_BIT_FLAG_38 (1 << 38)
#define IFB_BIT_FLAG_39 (1 << 39)
#define IFB_BIT_FLAG_40 (1 << 40)
#define IFB_BIT_FLAG_41 (1 << 41)
#define IFB_BIT_FLAG_42 (1 << 42)
#define IFB_BIT_FLAG_43 (1 << 43)
#define IFB_BIT_FLAG_44 (1 << 44)
#define IFB_BIT_FLAG_45 (1 << 45)
#define IFB_BIT_FLAG_46 (1 << 46)
#define IFB_BIT_FLAG_47 (1 << 47)
#define IFB_BIT_FLAG_48 (1 << 48)
#define IFB_BIT_FLAG_49 (1 << 49)
#define IFB_BIT_FLAG_50 (1 << 50)
#define IFB_BIT_FLAG_51 (1 << 51)
#define IFB_BIT_FLAG_52 (1 << 52)
#define IFB_BIT_FLAG_53 (1 << 53)
#define IFB_BIT_FLAG_54 (1 << 54)
#define IFB_BIT_FLAG_55 (1 << 55)
#define IFB_BIT_FLAG_56 (1 << 56)
#define IFB_BIT_FLAG_57 (1 << 57)
#define IFB_BIT_FLAG_58 (1 << 58)
#define IFB_BIT_FLAG_59 (1 << 59)
#define IFB_BIT_FLAG_60 (1 << 60)
#define IFB_BIT_FLAG_61 (1 << 61)
#define IFB_BIT_FLAG_62 (1 << 62)
#define IFB_BIT_FLAG_63 (1 << 63)

#define IFB_BIT_FLAG_GROUP_SIZE        8
#define IFB_BIT_FLAG_GROUP_UNAVAILABLE 0xFF

namespace ifb_bitwise {

    const ifb_u32
    flags_find_bits_clear(
        const ifb_u32   flag_group_count,
        const ifb_u32   flag_index_count,
        const ifb_byte* flag_group_array,
              ifb_u32*  flag_index_array);

    ifb_void flags_set   (const ifb_u32 flag_group_count, const ifb_u32 flag_index_count, ifb_byte* flag_group_array, const ifb_u32*  flag_index_array);
    ifb_void flags_clear (const ifb_u32 flag_group_count, const ifb_u32 flag_index_count, ifb_byte* flag_group_array, const ifb_u32*  flag_index_array);
};

inline const ifb_u32
ifb_bitwise::flags_find_bits_clear(
    const ifb_u32   flag_group_count,
    const ifb_u32   flag_index_count,
    const ifb_byte* flag_group_array,
          ifb_u32*  flag_index_array) {

    ifb_macro_assert(flag_group_count);
    ifb_macro_assert(flag_index_count);
    ifb_macro_assert(flag_group_array);
    ifb_macro_assert(flag_index_array);

    const ifb_u32  flag_group_size        = IFB_BIT_FLAG_GROUP_SIZE;
    const ifb_byte flag_group_unavailable = IFB_BIT_FLAG_GROUP_UNAVAILABLE; 
    
    ifb_u32 flags_found = 0;

    for (
        ifb_u32 flag_group_index = 0;
        flag_group_index < flag_group_count;
        ++flag_group_index) {

        const ifb_byte flag_group           = flag_group_array[flag_group_index];
        const ifb_u32  flag_index_start     = flag_group_count * flag_group_size;  
        const ifb_b8   flag_group_available = flag_group != flag_group_unavailable; 

        for (
            ifb_u32 flag_index = 0;
            flag_group_available && (flag_index < flag_group_size) && (flags_found < flag_index_count);
            ++flag_index) {

            if (ifb_macro_bit_is_clear(flag_index,flag_group)) {

                flag_index_array[flags_found] = flag_index_start + flag_index; 
                ++flags_found;
            }
        }
    }

    return(flags_found);
}

inline ifb_void
ifb_bitwise::flags_clear(
    const ifb_u32   flag_group_count,
    const ifb_u32   flag_index_count,
          ifb_byte* flag_group_array,
    const ifb_u32*  flag_index_array) {

    ifb_macro_assert(flag_group_count);
    ifb_macro_assert(flag_index_count);
    ifb_macro_assert(flag_group_array);
    ifb_macro_assert(flag_index_array);

    const ifb_u32 flag_group_size = IFB_BIT_FLAG_GROUP_SIZE;

    for (
        ifb_u32 flag_index = 0;
        flag_index_count < flag_index_count;
        ++flag_index) {

        //get the flag group and flag indexes
        const ifb_u32 flag             = flag_index_array[flag_index]; 
        const ifb_u32 flag_group_index = (ifb_u32)((ifb_f32)flag / (ifb_f32)flag_group_size);
        const ifb_u32 bit              = flag - (flag_group_index * flag_group_size);  

        ifb_macro_assert(flag_group_index < flag_group_count);

        //get the flag group 
        ifb_byte& flag_group_ref = flag_group_array[flag_group_index];

        //set the flag
        ifb_macro_bit_clear(bit,flag_group_ref);
    }  
}

inline ifb_void
ifb_bitwise::flags_set(
    const ifb_u32   flag_group_count,
    const ifb_u32   flag_index_count,
          ifb_byte* flag_group_array,
    const ifb_u32*  flag_index_array) {

    ifb_macro_assert(flag_group_count);
    ifb_macro_assert(flag_index_count);
    ifb_macro_assert(flag_group_array);
    ifb_macro_assert(flag_index_array);

    const ifb_u32 flag_group_size = IFB_BIT_FLAG_GROUP_SIZE;

    for (
        ifb_u32 flag_index = 0;
        flag_index_count < flag_index_count;
        ++flag_index) {

        //get the flag group and flag indexes
        const ifb_u32 flag             = flag_index_array[flag_index]; 
        const ifb_u32 flag_group_index = (ifb_u32)((ifb_f32)flag / (ifb_f32)flag_group_size);
        const ifb_u32 bit              = flag - (flag_group_index * flag_group_size);  

        ifb_macro_assert(flag_group_index < flag_group_count);

        //get the flag group 
        ifb_byte& flag_group_ref = flag_group_array[flag_group_index];

        //set the flag
        ifb_macro_bit_set(bit,flag_group_ref);
    }  
}

#endif //IFB_BIT_FLAGS_HPP