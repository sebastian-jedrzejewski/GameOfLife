#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>

#include "Menu.h"
#include "Utils.h"

Menu::Menu() :selection{'0'}, appRunner{} {
}

char Menu::getSelection() const {
    return selection;
}

void Menu::show() const {
    std::cout << "Conway's Game of Life" << std::endl << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "1. Run the chosen number of generations" << std::endl;
    std::cout << "2. Enter the file with initial generation" << std::endl;
    std::cout << "3. Clear the file with initial generation" << std::endl;
    std::cout << "4. Adjust the number of BMP images to be generated" << std::endl;
    std::cout << "5. Switch the step-by-step mode" << std::endl;
    std::cout << "6. Delete all files with generations" << std::endl;
    std::cout << "7. Quit" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
}

void Menu::loadInput() {
    std::cout << "Enter your choice: ";
    std::cin >> selection;
}

void Menu::executeOption() {
    switch(selection) {
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
            std::cout << "Option 5 chosen" << std::endl;
            break; 
        case '6':
            std::cout << "Option 6 chosen" << std::endl;
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
