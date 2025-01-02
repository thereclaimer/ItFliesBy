#ifndef IFB_ENGINE_INTERNAL_SYSTEMS_HPP
#define IFB_ENGINE_INTERNAL_SYSTEMS_HPP

#include <ifb-engine.hpp>

/**********************************************************************************/
/* TRANSFORMS                                                                     */
/**********************************************************************************/

namespace ifb_engine {

    ifb_void 
    transform_to_matrix(
        const ifb_u32       transform_count,
        const IFBTransform* transform_array,
              IFBMat3*      matrix_array);

    ifb_void
    transform_to_matrix_buffer(
        const IFBTransform* transform_array,
        const ifb_u32       transform_count,
        const ifb_u32       matrix_stride,
        const ifb_u32       matrix_buffer_size, 
              ifb_memory    matrix_buffer);
};


#endif //IFB_ENGINE_INTERNAL_SYSTEMS_HPP