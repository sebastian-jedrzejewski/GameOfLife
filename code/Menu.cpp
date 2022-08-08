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
    std::cout << "4. Adjust the number of BMP images to be generated" << std::endl;
    std::cout << "5. Switch the step-by-step mode" << std::endl;
    std::cout << "6. Delete generations and images folders with their content" << std::endl;
    std::cout << "7. Quit" << std::endl;
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
            option1();
            break;
        case '2':
            option2();
            break; 
        case '3':
            option3();
            break; 
        case '4':
            std::cout << "Option 4 chosen" << std::endl;
            break; 
        case '5':
            option5();
            break; 
        case '6':
            option6(true);
            break;
        case '7':
            std::cout << "Option 7 chosen" << std::endl;
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
    option6(false);
}

void Menu::option1() {
    appRunner.run();
}

void Menu::option2() {
    std::string fileName = askForFileName();
    if(fileName.length() > 0) {
        appRunner.setInitFile(fileName);
    }
}

void Menu::option3() {
    if(appRunner.getInitFile() != "") {
        appRunner.setInitFile("");
        std::cout << "The file with initial generation cleared. Now you can draw initial generation."; 
        std::cout << std::endl;
    } else {
        std::cout << "The file with initial generation has not been loaded, ";
        std::cout << "so there's nothing to clear." << std::endl;
    }
}

void Menu::option5() {
    if(appRunner.getStepByStep()) {
        std::cout << "Step-by-step mode has been switched off." << std::endl;
        appRunner.setStepByStep(false);
    } else {
        std::cout << "Step-by-step mode has been switched on." << std::endl;
        appRunner.setStepByStep(true);
    }
}

void Menu::option6(bool printMessages) {
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

    if(Utils::doesDirectoryExist("generations")) 
        system(deleteGenerationsInC);
    else
        if(printMessages)
            std::cout << "No generations folder found." << std::endl;

    if(Utils::doesDirectoryExist("images")) 
        system(deleteImagesInC);
    else
        if(printMessages)
            std::cout << "No images folder found." << std::endl;
}
