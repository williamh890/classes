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

ImageChanneled readImageFromFile(const string & filePath) {
    ifstream imageFile(filePath, ios::binary);
    if (!imageFile) {
        cout << "Error opening file (" << filePath << ") ..." << endl;
        exit(-1);
    }

    uint width, height;
    imageFile.read(( char * )(&height), sizeof(uint));
    imageFile.read(( char * )(&width), sizeof(uint));

    ImageChanneled img;
    for (uint x = 0; x < width; ++x) {
        vector<float> rs, gs, bs;
        for (uint y = 0; y < height; ++y) {
            uint r, g, b;
            imageFile.read(( char * )(&r), sizeof(uint));
            imageFile.read(( char * )(&b), sizeof(uint));
            imageFile.read(( char * )(&g), sizeof(uint));

            rs.push_back((float)r);
            gs.push_back((float)g);
            bs.push_back((float)b);
        }

        img.r.push_back(rs);
        img.g.push_back(gs);
        img.b.push_back(bs);
    }

    return img;
}

void writeImage(const string & outPath, const ImageChanneled & img) {
    ofstream imageFile(outPath, ios::binary);
    if (!imageFile) {
        cout << "Error opening file (" << outPath << ") ..." << endl;
        exit(-1);
    }
    uint width = img.r.size();
    uint height = img.r.at(0).size();

    imageFile.write(( char * )(&height), sizeof(uint));
    imageFile.write(( char * )(&width), sizeof(uint));

    cout << "Writing image to path " << outPath << endl;
    for (uint x = 0; x < width; ++x) {
        for (uint y = 0; y < height; ++y) {
            auto r = img.r[x][y];
            auto g = img.g[x][y];
            auto b = img.b[x][y];

            imageFile.write(( char * )(&r), sizeof(uint));
            imageFile.write(( char * )(&g), sizeof(uint));
            imageFile.write(( char * )(&b), sizeof(uint));
        }
    }

    cout << "Done writing file" << endl;
}
