#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <sys/stat.h>

#include "AppRunner.h"
#include "Utils.h"
#include "Menu.h"
#include "FileUtils.h"
#include "Rules.h"

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

std::string AppRunner::getInitFile() {
    return initFile;
}

void AppRunner::run() {
    mkdir("./generations");

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

    currentGeneration.setBoard(Board{initGeneration.getBoard().getWidth(), initGeneration.getBoard().getHeight()});
    currentGeneration.copyOf(initGeneration);


    std::string generationFileName{};
    int liveNeighbours{};
    Cell *cell{nullptr};
    Rules rules{};
    bool flag{false};
    for(int i=0; i < numberOfGenerations; i++) {
        flag = false;
        generationFileName = "./generations/gen" + std::to_string(i) + ".txt";
        if(!(FileUtils::write(generationFileName, currentGeneration))) {
            return;
        }

        for(int j=0; j < initGeneration.getBoard().getSize(); j++) {
            cell = initGeneration.getCell(j);
            liveNeighbours = initGeneration.getNumberOfLiveNeighbours(j);

            if(cell->getIsAlive()) {
                flag = false;
                for(int n: rules.NUMBER_OF_LIVE_NEIGHBOURS_FOR_LIVE_TO_SURVIVE) {
                    if(liveNeighbours == n) {
                        flag = true;
                    }
                }
                if(!flag) {
                    currentGeneration.getCell(j)->setState(false);
                }
            } else if(!(cell->getIsAlive())) {
                flag = false;
                for(int n: rules.NUMBER_OF_LIVE_NEIGHBOURS_FOR_DEAD_TO_LIVE) {
                    if(liveNeighbours == n) {
                        flag = true;
                    }
                }
                if(flag) {
                    currentGeneration.getCell(j)->setState(true);
                }
            } else {
                currentGeneration.getCell(j)->setState(cell->getIsAlive());
            }
        }

        initGeneration.copyOf(currentGeneration);
    }
    
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