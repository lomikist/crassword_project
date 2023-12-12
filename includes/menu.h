#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "string.h"
using namespace std;
class Menu {
protected:
public: 
    Menu(vector<string> );
    ~Menu();
    
    void setActiveItems(vector<string> );
    vector<string> getActiveItems();

    vector<string> activeItems;
    // is storing that items which should be shown after left arrow pressing.
    vector<string> prevActiveItems;
    // which is selected (console || window)
    string colorOption;

    WINDOW* mainWindow;
    string* currentItem;

    int height;
    int width;
};

