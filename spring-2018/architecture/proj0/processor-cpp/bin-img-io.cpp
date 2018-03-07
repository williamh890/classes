#include "headers/bin-img-io.h"
#include "headers/models.h"

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

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
