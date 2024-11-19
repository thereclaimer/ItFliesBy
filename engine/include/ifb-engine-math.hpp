#ifndef IFB_ENGINE_MATH_HPP
#define IFB_ENGINE_MATH_HPP

#include <ifb-common.hpp>

namespace ifb_engine {

    inline const ifb_size math_size_kilobytes(const ifb_size n) { return(n * 1024);              }
    inline const ifb_size math_size_megabytes(const ifb_size n) { return(n * 1024 * 1024);       }
    inline const ifb_size math_size_gigabytes(const ifb_size n) { return(n * 1024 * 1024* 1024); }
};

#endif //IFB_ENGINE_MATH_HPP