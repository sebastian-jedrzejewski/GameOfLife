#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

class Utils {
public:
    static bool isNumber(std::string str);
    static bool doesDirectoryExist(const std::string &s);
};

#endif