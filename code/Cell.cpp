#include <iostream>

#include "Cell.h"

Cell::Cell() : Cell(0, false) {
}

Cell::Cell(int number, bool isAlive) : number{number}, isAlive{isAlive} {
}

int Cell::getNumber() {
    return number;
}

bool Cell::getIsAlive() {
    return isAlive;
}

void Cell::setState(bool state) {
    isAlive = state;
}
