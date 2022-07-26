#include <iostream>

#include "Menu.h"

Menu::Menu() :selection{'0'} {

}

char Menu::getSelection() {
    return selection;
}

void Menu::show() {
    std::cout << "Conway's Game of Life" << std::endl << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "1. Run the chosen number of generations" << std::endl;
    std::cout << "2. Enter the file with initial generation" << std::endl;
    std::cout << "3. Adjust the number of BMP images to be generated" << std::endl;
    std::cout << "4. Switch the step-by-step mode" << std::endl;
    std::cout << "5. Delete all files with generations" << std::endl;
    std::cout << "6. Quit" << std::endl;
    std::cout << "---------------------" << std::endl << std::endl;
}

void Menu::loadInput() {
    std::cout << "Enter your choice: ";
    std::cin >> selection;

    switch(selection) {
        case '1':
            std::cout << "Option 1 chosen" << std::endl;
            break;
        case '2':
            std::cout << "Option 2 chosen" << std::endl;
            break; 
        case '3':
            std::cout << "Option 3 chosen" << std::endl;
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
        default:
            std::cout << "Invalid option" << std::endl;
            break;  
    }
}