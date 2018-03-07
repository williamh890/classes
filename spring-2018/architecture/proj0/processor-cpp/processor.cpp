#include "headers/models.h"
#include "headers/bin-img-io.h"
#include "osl/floats.h"

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

floats MIN_VAL = 0.;
floats MAX_VAL = 255.;

floats inline clamp(floats x) {
    return max(MIN_VAL, min(x, MAX_VAL));
}

floats inline mutate(floats channel, floats width, floats max_width, floats diff) {
    floats calc = channel + (diff * (width / max_width));

    return calc;
}

void process(FloatsVec & rChannel, FloatsVec & bChannel, FloatsVec & gChannel) {
    const floats max_size = rChannel.size();
    const floats R_DIFF = 100.;
    const floats G_DIFF = 50.;
    const floats B_DIFF = -50.;

    for (size_t x = 0; x < rChannel.size(); ++x) {
        for (size_t y = 0; y < rChannel[x].size(); y+=8) {
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
