#include "Utils.h"

#include <cctype>

bool Utils::isNumber(std::string str) {
    for(size_t i=0; i < str.length(); i++) {
        if(isdigit(str.at(i)) == false)
            return false;
    }
    return true;
}