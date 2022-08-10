#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <sys/stat.h>

#include "Menu.h"
#include "Utils.h"

Menu::Menu() :selection{'0'}, appRunner{} {
}

char Menu::getSelection() const {
    return selection;
}

void Menu::show() const {
    std::cout << "Conway's Game of Life" << std::endl << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << "0. Print all available actions" << std::endl;
    std::cout << "1. Run the chosen number of generations" << std::endl;
    std::cout << "2. Enter the file with initial generation" << std::endl;
    std::cout << "3. Clear the file with initial generation" << std::endl;
    std::cout << "4. Turn on/off generating files with generations" << std::endl;
    std::cout << "5. Turn on/off generating BMP images" << std::endl;
    std::cout << "6. Switch the step-by-step mode" << std::endl;
    std::cout << "7. Delete generations and images folders with their content" << std::endl;
    std::cout << "8. Quit" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl << std::endl;
}

void Menu::loadInput() {
    std::cout << "Enter your choice (0 to print options): ";
    std::cin >> selection;
}

void Menu::executeOption() {
    switch(selection) {
        case '0':
            show();
            break;
        case '1':
            runGenerations();
            break;
        case '2':
            loadFileName();
            break; 
        case '3':
            clearFileName();
            break; 
        case '4':
            switchGeneratingFiles();
            break; 
        case '5':
            switchGeneratingImages();
            break; 
        case '6':
            switchStepByStep();
            break;
        case '7':
            removeFolders(true);
            break;
        case '8':
            std::cout << "Option 8 chosen" << std::endl;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;  
    }
}

int Menu::askForWidth() {
    return askForDimension("width");
}

int Menu::askForHeight() {
    return askForDimension("height");
}

int Menu::askForNumberOfGenerations() {
    std::string input{};
    
    while(true) {
        std::cout << "Enter the number of generations: ";
        std::cin >> input;
        if(Utils::isNumber(input)) {
            return stoi(input);
        }
        else {
            std::cout << "The number of generations must be a positive integer!" << std::endl;
        }
    }
}

int Menu::askForDimension(std::string dimension) {
    std::string input{};

    while(true) {
        std::cout << "Enter a " << dimension << " of the board: ";
        std::cin >> input;
        if(Utils::isNumber(input)) {
            return std::stoi(input);
        }
        else {
            dimension[0] = std::toupper(dimension[0]);
            std::cout << dimension << " must be a positive integer!" << std::endl;
            dimension[0] = std::tolower(dimension[0]);
        }
    }
}

std::string Menu::askForFileName() {
    std::string input{};

    std::cout << "Enter a file path (or just a file name): ";
    std::cin >> input;

    std::ifstream in {input};
    if(!in) {
        std::cout << "This file has not been found. Make sure you entered the appropriate path." << std::endl;
        in.close();
        return "";
    }
    std::cout << "The file has been loaded sucessfully." << std::endl;
    in.close();
    return input;
}

void Menu::deleteFoldersIfExist() {
    removeFolders(false);
}

// Option 1
void Menu::runGenerations() {
    appRunner.run();
}

// Option 2
void Menu::loadFileName() {
    std::string fileName = askForFileName();
    if(fileName.length() > 0) {
        appRunner.setInitFile(fileName);
    }
}

// Option 3
void Menu::clearFileName() {
    if(appRunner.getInitFile() != "") {
        appRunner.setInitFile("");
        std::cout << "The file with initial generation cleared. Now you can draw initial generation."; 
        std::cout << std::endl;
    } else {
        std::cout << "The file with initial generation has not been loaded, ";
        std::cout << "so there's nothing to clear." << std::endl;
    }
}

// Option 4
void Menu::switchGeneratingFiles() {
    if(appRunner.getGenerateFiles()) {
        std::cout << "Generating files with generations has been switched off." << std::endl;
        appRunner.setGenerateFiles(false);
    } else {
        std::cout << "Generating files with generations has been switched on." << std::endl;
        appRunner.setGenerateFiles(true);
    }
}

// Option 5
void Menu::switchGeneratingImages() {
    if(appRunner.getGenerateImages()) {
        std::cout << "Generating BMP images has been switched off." << std::endl;
        appRunner.setGenerateImages(false);
    } else {
        std::cout << "Generating BMP images has been switched on." << std::endl;
        appRunner.setGenerateImages(true);
    }
}

// Option 6
void Menu::switchStepByStep() {
    if(appRunner.getStepByStep()) {
        std::cout << "Step-by-step mode has been switched off." << std::endl;
        appRunner.setStepByStep(false);
    } else {
        std::cout << "Step-by-step mode has been switched on." << std::endl;
        appRunner.setStepByStep(true);
    }
}

// Option 7
void Menu::removeFolders(bool printMessages) {
    std::string deleteGenerations{};
    std::string deleteImages{};

    #ifdef _WIN32
    deleteGenerations = "rd /s /q generations";
    deleteImages = "rd /s /q images";
    #else
    deleteGenerations = "rm -d generations";
    deleteImages = "rm -d images";
    #endif

    char deleteGenerationsInC[deleteGenerations.length()+1];
    char deleteImagesInC[deleteImages.length()+1];

    strcpy(deleteGenerationsInC, deleteGenerations.c_str());
    strcpy(deleteImagesInC, deleteImages.c_str());

    if(Utils::doesDirectoryExist("generations")) {
        system(deleteGenerationsInC);
        if(printMessages)
            std::cout << "Generations folder has been deleted sucessfully." << std::endl;
    }
    else
        if(printMessages)
            std::cout << "No generations folder found." << std::endl;

    if(Utils::doesDirectoryExist("images")) {
        system(deleteImagesInC);
        if(printMessages)
            std::cout << "Images folder has been deleted sucessfully." << std::endl;
    }
    else
        if(printMessages)
            std::cout << "No images folder found." << std::endl;
}
