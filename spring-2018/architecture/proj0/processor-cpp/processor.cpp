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

floats inline mutate(
        ImageChannel & channel,
        size_t x, size_t y,
        const floats & width,
        const floats & max_width,
        const floats & diff) {
    floats channelVals = &(channel[x][y]);
    floats calc = channelVals + (diff * (width / max_width));

    return calc;
}

void process(ImageChanneled & img) {
    const floats max_size = img.r.size();
    const floats R_DIFF = 100.;
    const floats G_DIFF = 50.;
    const floats B_DIFF = -50.;

    for (size_t x = 0; x < img.r.size(); ++x) {
        for (size_t y = 0; y < img.r[x].size(); y+=floats::n) {
            const floats currWidth = x;
            const floats rCalc = mutate(img.r, x, y, currWidth, max_size, R_DIFF);
            const floats bCalc = mutate(img.g, x, y, currWidth, max_size, G_DIFF);
            const floats gCalc = mutate(img.b, x, y, currWidth, max_size, B_DIFF);

            for (size_t lane = 0; lane < floats::n; ++lane) {
                img.r[x][y+lane] = rCalc[lane];
                img.g[x][y+lane] = bCalc[lane];
                img.b[x][y+lane] = gCalc[lane];
            }
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
    cout << "done writing file" << endl;

    return 0;
}
