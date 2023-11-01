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
    Menu* menu;
    Board* board;
    void rectangle();
    void drawVerticalLines();
    void drawHorizontalLines();
    void drawBoarders();
public:
    Gui();
    ~Gui();
    void drawMenu();
    void drawBoard();
    void changeItem(int );
};
