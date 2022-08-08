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

bool FileUtils::write(std::string fileName, Generation &generation) {
    std::ofstream out {fileName};

    if(!out) {
        std::cerr << "Problem opening file: " << fileName << std::endl;
        return false;
    }

    int width = generation.getBoard().getWidth();
    int height = generation.getBoard().getHeight();

    out << width << " " << height << std::endl;

    const int numbers_in_line{10};
    Cell *cell;
    int aliveCells{};
    for(int i=0; i < width*height; i++) {
        cell = generation.getCell(i);
        if(cell->getIsAlive()) {
            aliveCells++;
            out << cell->getNumber() << " ";
            if(aliveCells % numbers_in_line == 0) {
                out << std::endl;
            }
        }
    }

    out.close();
    return true;
}

bool FileUtils::exportImage(Image &image, std::string path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if(!f.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return false;
    }

    int width = image.getWidth();
    int height = image.getHeight();

    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (width*3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + width*height*3 + paddingAmount*height;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 2 (not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header Size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // Image width
    informationHeader[4] = width;
    informationHeader[5] = width >> 8;
    informationHeader[6] = width >> 16;
    informationHeader[7] = width >> 24;
    // Image height
    informationHeader[8] = height;
    informationHeader[9] = height >> 8;
    informationHeader[10] = height >> 16;
    informationHeader[11] = height >> 24;
    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;
    // Compression (no compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    // Image size (no compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    // X pixels per meter (not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    // Y pixels per meter (not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    // Total colors (color pallete not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    // Important colors (generally ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for(int y=0; y < height; y++) {
        for(int x=0; x < width; x++) {
            unsigned char r = static_cast<unsigned char>(image.getColor(x, y).r * 255.0);
            unsigned char g = static_cast<unsigned char>(image.getColor(x, y).g * 255.0);
            unsigned char b = static_cast<unsigned char>(image.getColor(x, y).b * 255.0);

            unsigned char color[] = {b,g,r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();
    return true;
}
