#include <iostream>

#include "Menu.h"

int main() {
    Menu menu{};
    
    do {
        menu.show();
        menu.loadInput();
        menu.executeOption();
    } while(menu.getSelection() != '7');
    
    return 0;
}