#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>
#include "Generation.h"
#include "Image.h"

class FileUtils {
public:
    static bool read(std::string fileName, Generation &generation);
    static bool write(std::string fileName, Generation &generation);
    static void exportImage(Image &image, const char *path);
};

#endif