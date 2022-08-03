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

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

AppRunner::AppRunner() : AppRunner("", false) {
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

bool AppRunner::getStepByStep() {
    return stepByStep;
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


    /* Local variables section */
    std::string generationFileName{};
    int liveNeighbours{};
    Cell *cell{nullptr};
    Rules rules{};
    bool flag{false};
    int liveCells{}, deadCells{};

    for(int i=0; i < numberOfGenerations; i++) {
        // Display information about the initial generation
        if(i == 0) {
            std::cout << std::endl << "---Initial generation---" << std::endl;
            std::cout << "Number of live cells: " << initGeneration.getNumberOfLiveCells() << std::endl;
            std::cout << "Number of dead cells: ";
            std::cout << (initGeneration.getBoard().getSize() - initGeneration.getNumberOfLiveCells());
            std::cout << std::endl << "Running..." << std::endl;
            std::cout << std::endl << std::endl;
        }

        liveCells = 0;
        deadCells = 0;

        // Writing the current generation to the file
        generationFileName = "./generations/gen" + std::to_string(i) + ".txt";
        if(!(FileUtils::write(generationFileName, currentGeneration))) {
            return;
        }

        // Check all the cells in initGeneration and set their state (according to the rules)
        // in currentGeneration (which was initially the same)
        for(int j=0; j < initGeneration.getBoard().getSize(); j++) {
            cell = initGeneration.getCell(j);
            liveNeighbours = initGeneration.getNumberOfLiveNeighbours(j);

            // If the cell was live, check the number of live neighbours
            // and decide if the cell should become dead in the next generation
            if(cell->getIsAlive()) {
                flag = false;
                for(int n: rules.NUMBER_OF_LIVE_NEIGHBOURS_FOR_LIVE_TO_SURVIVE) {
                    if(liveNeighbours == n) {
                        flag = true;
                    }
                }
                if(!flag) {
                    deadCells++;
                    currentGeneration.getCell(j)->setState(false);
                }
            }
            // If the cell was dead, check the number of live neighbours
            // and decide if the cell should become live in the next generation
            else {
                flag = false;
                for(int n: rules.NUMBER_OF_LIVE_NEIGHBOURS_FOR_DEAD_TO_LIVE) {
                    if(liveNeighbours == n) {
                        flag = true;
                    }
                }
                if(flag) {
                    liveCells++;
                    currentGeneration.getCell(j)->setState(true);
                }
            }
        }

        // Display more details about generations
        if(stepByStep) {
            Sleep(3000);
            std::cout << "---Generation nr " << i+1 << "---" << std::endl;
            std::cout << liveCells << " cells has become live and ";
            std::cout << deadCells << " cells died in this generation." << std::endl << std::endl;
            std::cout << std::endl << std::endl;
        }

        initGeneration.copyOf(currentGeneration);
    }

    int liveCellsAtEnd = currentGeneration.getNumberOfLiveCells();
    int deadCellsAtEnd = currentGeneration.getBoard().getSize() - liveCellsAtEnd;

    Sleep(3000);
    std::cout << std::endl <<  numberOfGenerations << " generations has been run." << std::endl;
    std::cout << "---Last generation---" << std::endl;
    std::cout << "Number of live cells: " << liveCellsAtEnd << std::endl;
    std::cout << "Number of dead cells: " << deadCellsAtEnd << std::endl << std::endl;
    
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