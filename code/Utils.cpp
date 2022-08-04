#include "Utils.h"

#include <cctype>
#include <sys/stat.h>

bool Utils::isNumber(std::string str) {
    for(size_t i=0; i < str.length(); i++) {
        if(isdigit(str.at(i)) == false)
            return false;
    }
    return true;
}

bool Utils::DoesDirectoryExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}