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
    Board getBoard() const;
    void setBoard(Board board);
    Cell* getCell(const int &number);
    int getNumberOfLiveNeighbours(const int &number);
    int getNumberOfLiveCells() const;
    void copyOf(Generation &generation);
};

#endif