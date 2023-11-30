#pragma once
#include <iostream>
#include <vector>
#include "string.h"
#include <utility> 
#include <ncurses.h>

class Board
{
public:
    // (width, height);
    Board(int, int);
    ~Board();
    // board size (it means count of the lines and columns, its not mean a letter fileds count.)
    std::pair<int, int> sizes;
    WINDOW* mainWindow;
    WINDOW* inputWindow;
};
