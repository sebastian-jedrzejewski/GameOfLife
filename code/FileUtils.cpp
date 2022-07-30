#include <iostream>
#include <fstream>

#include "FileUtils.h"

bool FileUtils::read(std::string fileName, Generation &generation) {
    std::ifstream in {fileName};
    if(!in) {
        std::cerr << "Problem opening file: " << fileName << std::endl;
        return false;
    }

    int width{}, height{};
    int number{};
    if(in >> width && in >> height) {
        if(width > 0 && height > 0) {
            generation.setBoard(Board{width, height});
        } else {
            std::cerr << "Invalid format of the file! (width and height must be positive integers)" << std::endl;
            return false;
        }
        
        Cell *cell {nullptr};
        while(in >> number) {
            if(number >= 0 && number < width*height) {
                cell = generation.getCell(number);
                cell->setState(true);
            }
            else {
                std::cerr << "Invalid format of the file! (all numbers must describe cells)" << std::endl;
                return false;
            }
        }
    }
    else {
        std::cerr << "Invalid format of the file! (width and height must be integers)" << std::endl;
        return false;
    }

    in.close();
    return true;
}