#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "AppRunner.h"
#include "Utils.h"
#include "Menu.h"
#include "FileUtils.h"

AppRunner::AppRunner() : AppRunner("", true) {
}

AppRunner::AppRunner(std::string initFile, bool stepByStep) 
    : initFile{initFile}, stepByStep{stepByStep}, initGeneration{Board{0, 0}}, currentGeneration{Board{0,0}},
      numberOfGenerations{0} {
}

void AppRunner::setInitFile(std::string name) {
    initFile = name;
}

void AppRunner::setStepByStep(bool mode) {
    stepByStep = mode;
}

void AppRunner::run() {
    // Ask user for number of generations
    numberOfGenerations = Menu::askForNumberOfGenerations();

    // Generate an initital generation (from a file or random)
    if(initFile != "") {
        // read a file and create an initial generation
        if(!(FileUtils::read(initFile, initGeneration))) {
            return;
        }
    } else {
        // generate a random generation
        randomGeneration();
    }

    currentGeneration = initGeneration;
    
    
}

void AppRunner::randomGeneration() {
    int width{}, height{};

    width = Menu::askForWidth();
    height = Menu::askForHeight();

    initGeneration.setBoard(Board{width, height});
    Board board = initGeneration.getBoard();

    int randInt{};
    srand(time(0));
    Cell *cell {nullptr};
    for(int i=0; i < board.getSize(); i++) {
        randInt = rand();
        if(randInt % 2 == 0) {
            cell = initGeneration.getCell(i);
            cell->setState(true);
        }
    }
}