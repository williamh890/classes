#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::max;
using std::min;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;
#include <chrono>
#include <ctime>

struct Pixel {
    uint r, g, b;
    Pixel(uint r, uint b, uint g) : r(r), g(g), b(b) {
    }
};

using uint = unsigned int;
using Image = vector<vector<Pixel>>;
/*
def clamp(x):
    return max(0, min(x, 255))
*/
uint inline clamp(uint x) {
    return max((uint)0, min(x, (uint)255));
}

/*
def mutate(channel, height, max_height, diff):
    return int(clamp(channel + diff * (height / max_height)))
*/
uint inline mutate(uint channel, float width, float max_width, float diff) {
    return clamp(channel + (uint)(diff * (width / max_width)));
}
/*
def process(pixels, widht, height):
    for x in range(width):
        if x % 100 == 0:
            print(f"{(x / width) * 100:2.1f} %")
        for y in range(height):
            colors[x][y][0] = mutate(colors[x][y][2], x, width, 100)
            colors[x][y][1] = mutate(colors[x][y][1], x, width, 50)
            colors[x][y][2] = mutate(colors[x][y][0], x, width, -50)
*/
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

Image readImageFromFile(const string & filePath) {
    ifstream imageFile(filePath, ios::binary);
    if (!imageFile) {
        cout << "Error opening file (" << filePath << ") ..." << endl;
        exit(-1);
    }

    uint width, height;

    imageFile.read(( char * )(&height), sizeof(uint));
    imageFile.read(( char * )(&width), sizeof(uint));

    Image img;
    for (uint x = 0; x < width; ++x) {
        vector<Pixel> col;
        for (uint y = 0; y < height; ++y) {
            uint r,g,b;
            imageFile.read(( char * )(&r), sizeof(uint));
            imageFile.read(( char * )(&b), sizeof(uint));
            imageFile.read(( char * )(&g), sizeof(uint));

            col.push_back({ r, g, b });
        }

        img.push_back(col);
    }

    return img;
}

void writeImage(const string & outPath, const Image & image) {
    ofstream imageFile(outPath, ios::binary);
    if (!imageFile) {
        cout << "Error opening file (" << outPath << ") ..." << endl;
        exit(-1);
    }
    uint width = image.size();
    uint height = image.at(0).size();

    imageFile.write(( char * )(&height), sizeof(uint));
    imageFile.write(( char * )(&width), sizeof(uint));

    cout << "Writing image to path " << outPath << endl;
    for (uint x = 0; x < width; ++x) {
        for (uint y = 0; y < height; ++y) {
            auto pixel = image[x][y];

            imageFile.write(( char * )(&pixel.r), sizeof(uint));
            imageFile.write(( char * )(&pixel.g), sizeof(uint));
            imageFile.write(( char * )(&pixel.b), sizeof(uint));
        }
    }

    cout << "Done writing file" << endl;
}

double getTime() {
    return 1.0e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count();
}


int main(int argc, char** argv) {
    auto filePath = string(argv[1]);

    cout << "- Reading bin image data from " << filePath << endl;
    auto img = readImageFromFile(filePath);

    auto start = getTime();
    process(img);
    auto end = getTime();
    cout << "c++ calculation time: " << end - start << endl;

    writeImage("from-cpp.bin", img);

    return 0;
}
