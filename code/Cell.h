#ifndef _CELL_H_
#define _CELL_H_

class Cell {
private:
    int number;
    bool isAlive;

public:
    Cell();
    Cell(int number, bool isAlive=false);
    int getNumber() const;
    bool getIsAlive() const;
    void setState(bool isAlive);
};

#endif