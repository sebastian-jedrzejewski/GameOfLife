#ifndef _MENU_H_
#define _MENU_H_

class Menu {
private:
    char selection;

public:
    Menu();
    char getSelection();
    void show();
    void loadInput();
};

#endif