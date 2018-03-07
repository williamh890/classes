#include "headers/models.h"
#include "headers/bin-img-io.h"

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::max;
using std::min;
#include <string>
using std::string;
#include <chrono>
#include <ctime>

uint inline clamp(uint x) {
    return max((uint)0, min(x, (uint)255));
}

uint inline mutate(uint channel, float width, float max_width, float diff) {
    return clamp(channel + (uint)(diff * (width / max_width)));
}

void process(Image & pixels) {
    # pragma omp parallel for num_threads(7)
    for (size_t x = 0; x < pixels.size(); ++x) {
        for (size_t y = 0; y < pixels[x].size(); ++y) {
            auto max_size = pixels.size();
            pixels[x][y].r = mutate(pixels[x][y].b, x, max_size, 100);
            pixels[x][y].g = mutate(pixels[x][y].g, x, max_size, 50);
            pixels[x][y].b = mutate(pixels[x][y].r, x, max_size, -50);
        }
    }
}

double getTime() {
    return 1.0e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count();
}


int main(int argc, char** argv) {
    auto inputBinary = string(argv[1]);
    auto outputBinary = string(argv[2]);


    cout << "- Reading bin image data from " << inputBinary << endl;
    auto img = readImageFromFile(inputBinary);

    auto start = getTime();
    process(img);
    auto end = getTime();
    cout << "c++ calculation time: " << end - start << endl;

    writeImage(outputBinary, img);

    return 0;
}
