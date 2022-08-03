#include <iostream>

#include "Generation.h"

Generation::Generation(Board board) : board{board} {
    for(int i=0; i < board.getSize(); i++) {
        cells.emplace_back(i);
    }
}

Board Generation::getBoard() const {
    return board;
}

void Generation::setBoard(Board board) {
    this->board = board;
    cells.clear();
    for(int i=0; i < board.getSize(); i++) {
        cells.emplace_back(i);
    }
}

Cell* Generation::getCell(const int &number) {
    if(number >= 0 && number < board.getSize()) 
        return &(cells.at(number));
    else
        return nullptr;
}

int Generation::getNumberOfLiveNeighbours(const int &number) {
    int row = number / board.getWidth();
    int column = number - board.getWidth() * row;
    int liveNeighbours{};

    int left = number - 1;
    int right = number + 1;
    int top = number - board.getWidth();
    int bottom = number + board.getWidth();
    int topLeft = top - 1;
    int topRight = top + 1;
    int bottomLeft = bottom - 1;
    int bottomRight = bottom + 1;

    if(row != 0 && column != 0 && cells.at(topLeft).getIsAlive())
        liveNeighbours++;
    if(row != 0 && cells.at(top).getIsAlive())
        liveNeighbours++;
    if(row != 0 && column != (board.getWidth()-1) && cells.at(topRight).getIsAlive())
        liveNeighbours++;
    if(column != 0 && cells.at(left).getIsAlive())
        liveNeighbours++;
    if(column != (board.getWidth()-1) && cells.at(right).getIsAlive())
        liveNeighbours++;
    if(column != 0 && row != (board.getHeight()-1) && cells.at(bottomLeft).getIsAlive())
        liveNeighbours++;
    if(row != (board.getHeight()-1) && cells.at(bottom).getIsAlive())
        liveNeighbours++;
    if(row != (board.getHeight()-1) && column != (board.getWidth()-1) && cells.at(bottomRight).getIsAlive())
        liveNeighbours++;
    
    return liveNeighbours;
}

int Generation::getNumberOfLiveCells() const {
    int count{};
    for(int i=0; i < board.getSize(); i++) {
        if(cells.at(i).getIsAlive())
            count++;
    }
    return count;
}

void Generation::copyOf(Generation &generation) {
    try {
        if(this->board.getSize() != generation.board.getSize()) {
            throw 0;
        }
        cells.clear();
        for(int i=0; i < this->board.getSize(); i++) {
            cells.push_back(generation.cells.at(i));
        }
    } catch(const int &ex) {
        std::cerr << "Boards of both generations have different size." << std::endl;
        return;
    }
}