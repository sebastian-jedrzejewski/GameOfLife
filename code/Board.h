#ifndef _BOARD_H_
#define _BOARD_H_

class Board {
private:
    int width;
    int height;

public:
    Board();
    Board(int width, int height);
    int getWidth() const;
    int getHeight() const;
    int getSize() const;
};

#endif