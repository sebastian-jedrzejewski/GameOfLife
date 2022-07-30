#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>
#include "Generation.h"

class FileUtils {
public:
    static bool read(std::string fileName, Generation &generation);
    static void write(std::string fileName, const Generation &generation);
};

#endif