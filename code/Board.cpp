#include <iostream>

#include "Board.h"

Board::Board() : Board(10, 10) {
}

Board::Board(int width, int height) : width{width}, height{height} {
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

int Board::getSize() {
    return width*height;
}