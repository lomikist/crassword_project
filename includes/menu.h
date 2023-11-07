#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "string.h"
using namespace std;
class Menu
{
private:
public:
    Menu(vector<string>);
    ~Menu();
    WINDOW* mainWindow;
    vector<string> startMenuItems;
    string* startMenuActiveItem;
};
