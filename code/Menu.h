#ifndef _MENU_H_
#define _MENU_H_

#include "AppRunner.h"

class Menu {
private:
    char selection;
    AppRunner appRunner;

    static int askForDimension(std::string dimension);
    void option1();

public:
    Menu();
    char getSelection() const;
    void show() const;
    void loadInput();
    void executeOption();
    static int askForWidth();
    static int askForHeight();
    static int askForNumberOfGenerations();
};

#endif