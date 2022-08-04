#ifndef _MENU_H_
#define _MENU_H_

#include "AppRunner.h"

class Menu {
private:
    char selection;
    AppRunner appRunner;

    static int askForDimension(std::string dimension);
    static std::string askForFileName();
    void option1();
    void option2();
    void option3();
    void option5();
    static void option6(bool printMessages);

public:
    Menu();
    char getSelection() const;
    void show() const;
    void loadInput();
    void executeOption();
    static int askForWidth();
    static int askForHeight();
    static int askForNumberOfGenerations();
    static void deleteFoldersIfExist();
};

#endif