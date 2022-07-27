#include <iostream>

#include "Board.h"

Board::Board() : Board(10, 10) {
}

Board::Board(int width, int height) : width{width}, height{height} {
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

int Board::getSize() const {
    return width*height;
}