#ifndef BIN_IMG_IO_H
#define BIN_IMG_IO_H

#include "models.h"
// ImageChanneled
#include <string>
// std::string

ImageChanneled readImageFromFile(const std::string & filePath);
void writeImage(const std::string & outPath, const ImageChanneled & image);

#endif
