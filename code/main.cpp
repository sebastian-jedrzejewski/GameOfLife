#include <iostream>

#include "Menu.h"

int main() {
    Menu menu{};
    
    do {
        menu.show();
        menu.loadInput();
    } while(menu.getSelection() != '6');
    
    return 0;
}