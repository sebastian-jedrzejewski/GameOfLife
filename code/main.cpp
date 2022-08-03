#include <iostream>

#include "Menu.h"

int main() {
    Menu menu{};
    
    menu.show();
    do {
        menu.loadInput();
        menu.executeOption();
    } while(menu.getSelection() != '7');
    
    return 0;
}