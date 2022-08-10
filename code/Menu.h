#ifndef _MENU_H_
#define _MENU_H_

#include "AppRunner.h"

class Menu {
private:
    char selection;
    AppRunner appRunner;

    static int askForDimension(std::string dimension);
    static std::string askForFileName();
    void runGenerations();
    void loadFileName();
    void clearFileName();
    void switchGeneratingFiles();
    void switchGeneratingImages();
    void switchStepByStep();
    static void removeFolders(bool printMessages);

public:
    const static char QUIT = '8';

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