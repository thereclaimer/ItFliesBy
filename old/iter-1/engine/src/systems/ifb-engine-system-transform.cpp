#pragma once

#include "ifb-engine-internal-systems.hpp"

inline ifb_void 
ifb_engine::transform_to_matrix(
    const ifb_u32       transform_count,
    const IFBTransform* transform_array,
          IFBMat3*      matrix_array) {

    ifb_math::mat3_batch_transform(
        matrix_array,
        trasnform_count,
        transform_array);
}

inline ifb_void
ifb_engine::transform_to_matrix_buffer(
    const IFBTransform* transform_array,
    const ifb_u32       transform_count,
    const ifb_u32       matrix_stride,
    const ifb_u32       matrix_buffer_size, 
          ifb_memory    matrix_buffer) {

    const ifb_u32 matrix_size  = ifb_macro_align_size_struct(IFBMat3) + matrix_stride;
    const ifb_u32 size_to_copy = matrix_size * transform_count; 

    ifb_macro_assert(transform_array);
    ifb_macro_assert(transform_count);
    ifb_macro_assert(matrix_buffer_size);
    ifb_macro_assert(matrix_buffer);
    ifb_macro_assert(size_to_copy <= matrix_buffer_size);

    IFBMat3 matrix;

    for (
        ifb_u32 transform_index = 0;
        transform_index < transform_count;
        ++transform_index += matrix_size) {

        const ifb_u32       matrix_buffer_offset = transform_index * matrix_size; 
        const IFBTransform& transform_ref        = transform_array[transform_count];
        
        ifb_math::mat3_transform(matrix,transform_ref);

        matrix_buffer[matrix_buffer_offset]     = matrix.array[0];
        matrix_buffer[matrix_buffer_offset + 1] = matrix.array[1];
        matrix_buffer[matrix_buffer_offset + 2] = matrix.array[2];
        matrix_buffer[matrix_buffer_offset + 3] = matrix.array[3];
        matrix_buffer[matrix_buffer_offset + 4] = matrix.array[4];
        matrix_buffer[matrix_buffer_offset + 5] = matrix.array[5];
        matrix_buffer[matrix_buffer_offset + 6] = matrix.array[6];
        matrix_buffer[matrix_buffer_offset + 7] = matrix.array[7];
        matrix_buffer[matrix_buffer_offset + 8] = matrix.array[8];
    }
}