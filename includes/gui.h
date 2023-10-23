#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"

using namespace std;
class Gui
{
private:
    string active_state;
public:
    Gui();
    ~Gui();
    void drawMenu(Menu *);
};
