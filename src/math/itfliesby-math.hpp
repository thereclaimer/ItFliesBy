#ifndef ITFLIESBY_MATH_HPP
#define ITFLIESBY_MATH_HPP

#include "itfliesby-math-vec2.hpp"
#include "itfliesby-math-mat2.hpp"
#include "itfliesby-math-mat3.hpp"
#include "itfliesby-math-trig.hpp"

#define ITFLIESBY_MATH_KILOBYTES(value) ((long long)(value * 1024))
#define ITFLIESBY_MATH_MEGABYTES(value) ((long long)(ITFLIESBY_MATH_KILOBYTES(value) * 1024))
#define ITFLIESBY_MATH_GIGABYTES(value) ((long long)(ITFLIESBY_MATH_MEGABYTES(value) * 1024))

#endif //ITFLIESBY_MATH_HPP