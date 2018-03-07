#ifndef BIN_IMG_IO_H
#define BIN_IMG_IO_H

#include "models.h"
// Image
#include <string>
// std::string

Image readImageFromFile(const std::string & filePath);
void writeImage(const std::string & outPath, const Image & image);

#endif
