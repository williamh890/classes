#ifndef MODELS_H
#define MODELS_H

#include <vector>
// std::vector

using uint = unsigned int;
struct Pixel {
    uint r, g, b;
    Pixel(uint r, uint b, uint g) : r(r), g(g), b(b) {
    }
};

using Image = std::vector<std::vector<Pixel> >;


#endif
