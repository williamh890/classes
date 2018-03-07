#ifndef MODELS_H
#define MODELS_H

#include <vector>
// std::vector
#include "../osl/floats.h"

using uint = unsigned int;
using FloatsVec = std::vector<float>;

struct Pixel {
    uint r, g, b;
    Pixel(uint r, uint b, uint g) : r(r), g(g), b(b) {
    }
};

struct PixelSimd {
    floats r, g, b;

    PixelSimd(floats r, floats b, floats g) : r(r), g(g), b(b) {
    }
};

using Image = std::vector<std::vector<Pixel> >;
using ImageSimd = std::vector<std::vector<PixelSimd> >;


#endif
