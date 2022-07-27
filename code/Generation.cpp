#include <iostream>

#include "Generation.h"

Generation::Generation(Board board) : board{board} {
    for(int i=0; i < board.getSize(); i++) {
        cells.emplace_back(i);
    }
}

Board Generation::getBoard() {
    return board;
}

Cell Generation::getCell(int number) {
    if(number >= 0 && number < board.getSize()) {
        return cells.at(number);
    }
    return Cell{-1};
}

std::vector<int> Generation::getCellNeighbours(int number) {
    int row = number / board.getWidth();
    int column = number - board.getWidth() * row;
    std::vector<int> neighbours{};

    int left = number - 1;
    int right = number + 1;
    int top = number - board.getWidth();
    int bottom = number + board.getWidth();
    int topLeft = top - 1;
    int topRight = top + 1;
    int bottomLeft = bottom - 1;
    int bottomRight = bottom + 1;

    if(row != 0 && column != 0)
        neighbours.push_back(topLeft);
    if(row != 0)
        neighbours.push_back(top);
    if(row != 0 && column != (board.getWidth()-1))
        neighbours.push_back(topRight);
    if(column != 0)
        neighbours.push_back(left);
    if(column != (board.getWidth()-1))
        neighbours.push_back(right);
    if(column != 0 && row != (board.getHeight()-1))
        neighbours.push_back(bottomLeft);
    if(row != (board.getHeight()-1))
        neighbours.push_back(bottom);
    if(row != (board.getHeight()-1) && column != (board.getWidth()-1))
        neighbours.push_back(bottomRight);
    
    return neighbours;
}