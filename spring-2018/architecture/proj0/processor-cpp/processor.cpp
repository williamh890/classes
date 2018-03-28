#include "headers/models.h"
#include "headers/bin-img-io.h"

#include "cnpy.h"

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::max;
using std::min;
#include<vector>
using std::vector;
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

void processImageBinary(const string & inputBinary, const string & outputBinary) {
    cout << "- Reading bin image data from " << inputBinary << endl;
    auto img = readImageFromFile(inputBinary);
    auto iters = 200;
    auto start = getTime();
    for (auto i = 0; i < iters; ++i) {
        process(img);
    }
    auto end = getTime();
    cout << "c++ calculation time: " << (end - start) / iters << endl;

    writeImage(outputBinary, img);
}


int main(int argc, char** argv) {
    auto inputBinaryPath = string(argv[1]);
    auto outputBinaryPath = string(argv[2]);

    auto standard = readImageFromFile(outputBinaryPath);
    auto img = cnpy::npy_load(inputBinaryPath);

    cout << "Word size: " << img.word_size << endl;
    cout << "Dimensions: " << img.shape[0] << endl;
    auto len = img.shape[0];
    double* data = img.data<double>();

    auto firstPixel = standard[0][0];
    cout << "standard: " << firstPixel.r << " " <<firstPixel.g << " "<< firstPixel.b << endl

        << "cnpy: " << *(data + len - 3)
        << " " << *(data + len - 2)
        << " " << *(data + len - 1) << endl;

    return 0;
}
