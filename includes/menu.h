#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "string.h"
using namespace std;
class Menu {
public:
    Menu(vector<string>);
    ~Menu();
    WINDOW* mainWindow;
    vector<string> startMenuItems;
    string* startMenuActiveItem;
};

// class Menu : public MainMenu {
// public:
//     MainMenu();
//     void () override;
// };
