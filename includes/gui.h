#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>
#include "menu.h"
#include "board.h"

using namespace std;
class Gui
{
private:
    string active_state;
    void rectangle(int y1 = 0, int x1 = 0, int y2 = 1, int x2 = 1);
public:
    Gui();
    ~Gui();
    void drawMenu(Menu *);
    void drawBoard(Board *);
};
