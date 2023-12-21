#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <ncurses.h>
#include "string.h"
using namespace std;
class Menu {
protected:
public: 
    Menu(std::vector<string> );
    
    void setActiveItems(std::vector<string> );
    std::vector<string> getActiveItems();

    std::vector<string> activeItems;
    std::list<std::vector<string>> prevActiveItems;
    // which is selected (console || window)
    std::string colorOption;

    WINDOW* mainWindow;
    std::string* currentItem;

    int height;
    int width;
};

