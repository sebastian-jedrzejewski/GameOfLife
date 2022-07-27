#ifndef _GENERATION_H_
#define _GENERATION_H_

#include <vector>

#include "Board.h"
#include "Cell.h"

class Generation {
private:
    Board board;
    std::vector<Cell> cells;

public:
    Generation(Board board);
    Board getBoard();
    Cell getCell(int number);
    std::vector<int> getCellNeighbours(int number);
};

#endif